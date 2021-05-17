#include <iostream>

using namespace std;

const int SUCCESS = 1;
const int FAIL = 0;
const int TRUE = 1;
const int FALSE = 0;
const int BID_MAX = 40001;
const int ROOMS_MAX_LENGTH = 10000;
const int DAYS_MAX = 100;
const int NONE_BID = -1;

int MAP_LENGTH = -1;

typedef struct _RoomInfo {
	int mPrice;
	int mRating;
} RoomInfo;

RoomInfo ROOMS[BID_MAX] = { 0, };

typedef struct _HashNode {
	int mBid;
	struct _HashNode* mNext;
} HashNode;

int HASH_TABLE[ROOMS_MAX_LENGTH] = { 0, };
int NODE_LENGTH = 0;
HashNode NODE_POOL[ROOMS_MAX_LENGTH] = { 0, };

const char EMPTY_ROOM = '\0';
const char CHECKIN = 'I';
const char STAY = 'N';
char RESERVE_MAP[BID_MAX][DAYS_MAX] = { EMPTY_ROOM, };

const int OVER_ROOT = 0;
const int ROOT_INDEX = 1;
const int HEAP_SIZE = ROOMS_MAX_LENGTH + 1;
int HEAP_COUNT = 0;
int HEAP[HEAP_SIZE] = { 0, };

void Push(const int bid);
int Pop();

int CompareRooms(const int a_bid, const int b_bid);
int Hash(const int y, const int x);
void Add_HashTable(const int bid, const int y, const int x);
int CanReserve(const int bid, const int cday, const int night);


void init(int M)
{
	cout << "init: M=" << M << endl;
	HEAP_COUNT = 0;
	MAP_LENGTH = M;
	// ROOMS 초기화 불필요.
	NODE_LENGTH = 0;
	for (int i = 0; i < BID_MAX; ++i) {
		if (i < ROOMS_MAX_LENGTH) {
			//HEAP[i] = 0;
			HASH_TABLE[i] = -1;
			NODE_POOL[i].mBid = NONE_BID;
			NODE_POOL[i].mNext = NULL;
		}
		for (int j = 0; j < DAYS_MAX; ++j) {
			RESERVE_MAP[i][j] = EMPTY_ROOM;
		}
	}
	//HEAP[ROOMS_MAX_LENGTH] = 0;
}

void add_bnb(int bid, int y, int x, int price, int rating)
{
	cout << "add_bnb: bid=" << bid << " y=" << y << " x=" << x << " price=" << price << " rating=" << rating << endl;
	ROOMS[bid].mPrice = price;
	ROOMS[bid].mRating = rating;

	Add_HashTable(bid, y, x);
}

int reserve(int bid, int cday, int night)
{
	cout << "reserve: bid=" << bid << " cday=" << cday << " night=" << night << endl;
	for (int i = 0; i < night; ++i) {
		if (RESERVE_MAP[bid][cday + i] != EMPTY_ROOM) {
			return FAIL;
		}
	}

	RESERVE_MAP[bid][cday] = CHECKIN;
	for (int i = 1; i < night; ++i) {
		RESERVE_MAP[bid][cday + i] = STAY;
	}

	return SUCCESS;
}

int cancel(int bid, int cday)
{
	cout << "cancel: bid=" << bid << " cday=" << cday << endl;
	if (RESERVE_MAP[bid][cday] != CHECKIN) {
		return FAIL;
	}

	char status = RESERVE_MAP[bid][cday];
	int i = cday;
	while (status != EMPTY_ROOM) {
		RESERVE_MAP[bid][i] = EMPTY_ROOM;
		i++;
		status = RESERVE_MAP[bid][i];
	}

	return SUCCESS;
}

int search(int opt, int y, int x, int cday, int night, int top5_bid[5])
{
	cout << "search: opt=" << opt << " y=" << y << " x=" << x << " cday=" << cday << " night=" << night << endl;
	int top_length = 0;
	int min_y = (y - opt < 0) ? 0 : y - opt;
	int max_y = (y + opt >= MAP_LENGTH) ? MAP_LENGTH - 1 : y + opt;
	int min_x = (x - opt < 0) ? 0 : x - opt;
	int max_x = (x + opt >= MAP_LENGTH) ? MAP_LENGTH - 1 : x + opt;
	HashNode* pNode = NULL;
	int index = -1;
	int nodePool_index = -1;
	HEAP_COUNT = 0;

	// ROOM 순회
	for (int y_i = min_y; y_i <= max_y; ++y_i) {
		for (int x_i = min_x; x_i <= max_x; ++x_i) {
			index = Hash(y_i, x_i);
			nodePool_index = HASH_TABLE[index];

			if (nodePool_index == -1) {
				pNode = NULL;
			}
			else {
				pNode = &NODE_POOL[nodePool_index];
			}

			while (pNode != NULL) {
				int bid = pNode->mBid;
				if (CanReserve(bid, cday, night) == TRUE) {
					Push(bid);
				}
				pNode = pNode->mNext;
			}
		}
	}

	for (int i = HEAP_COUNT; i > 0 && top_length < 5; --i) {
		top5_bid[top_length] = Pop();
		top_length++;
	}

	return top_length;
}

// a == b : 0
// a > b  : 1
// a < b  : -1
int CompareRooms(const int a_bid, const int b_bid) {
	cout << "CompareRooms: a_bid=" << a_bid << " b_bid=" << b_bid << endl;
	if (a_bid == b_bid) {
		return 0;
	}

	int result = -1;

	if (ROOMS[a_bid].mPrice < ROOMS[b_bid].mPrice) {
		return -1;
	}
	else if (ROOMS[a_bid].mPrice > ROOMS[b_bid].mPrice) {
		return 1;
	}

	if (ROOMS[a_bid].mPrice == ROOMS[b_bid].mPrice) {
		if (ROOMS[a_bid].mRating > ROOMS[b_bid].mRating) {
			return -1;
		}
		else if (ROOMS[a_bid].mRating < ROOMS[b_bid].mRating) {
			return 1;
		}
	}

	if (ROOMS[a_bid].mRating == ROOMS[b_bid].mRating) {
		result = (a_bid > b_bid) ? -1 : 1;
	}

	return result;
}

int Hash(const int y, const int x) {
	cout << "Hash: y=" << y << " x=" << x << endl;
	int hash = 0;

	hash = ((y + 1) * 100 + (x + 4) * 1000) % ROOMS_MAX_LENGTH;

	return hash;
}

void Add_HashTable(const int bid, const int y, const int x) {
	cout << "Add_HashTable: bid=" << bid << " y=" << y << " x=" << x << endl;
	int index = Hash(y, x);
	int nodePool_index = HASH_TABLE[index];
	HashNode* pNode = NULL;

	// Empty Hash table
	if (nodePool_index == -1) {
		HASH_TABLE[index] = NODE_LENGTH;

		pNode = &NODE_POOL[NODE_LENGTH];
		pNode->mBid = bid;
		pNode->mNext = NULL;
		NODE_LENGTH++;

		return;
	}

	HashNode* pPrev = &NODE_POOL[nodePool_index];
	pNode = pPrev;
	int t_bid = pNode->mBid;

	while (CompareRooms(t_bid, bid) < 0) {
		pPrev = pNode;
		pNode = pNode->mNext;

		if (pNode == NULL) {
			break;
		}
		t_bid = pNode->mBid;
	}

	HashNode* pNew = &NODE_POOL[NODE_LENGTH];
	pNew->mBid = bid;
	pNew->mNext = pNode;
	NODE_LENGTH++;

	pPrev->mNext = pNew;
}

int CanReserve(const int bid, const int cday, const int night) {
	cout << "CanReserve: bid=" << bid << " cday=" << cday << " night=" << night << endl;
	for (int i = 0; i < night; ++i) {
		if (RESERVE_MAP[bid][cday + i] != EMPTY_ROOM) {
			return FALSE;
		}
	}

	return TRUE;
}

void Swap(int * const pArr, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
	pArr[b_index] = pArr[a_index] ^ pArr[b_index];
	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
}

void Push(const int bid) {
	HEAP_COUNT++;
	HEAP[HEAP_COUNT] = bid;
	int child = HEAP_COUNT;
	int parent = child >> 1;

	while (parent > OVER_ROOT && CompareRooms(HEAP[parent], HEAP[child]) > 0) {
		cout << "Pop: p=" << parent << " c=" << child << endl;
		// Swap(HEAP, parent, child);
		if (parent != child) {
			HEAP[parent] = HEAP[parent] ^ HEAP[child];
			HEAP[child] = HEAP[parent] ^ HEAP[child];
			HEAP[parent] = HEAP[parent] ^ HEAP[child];
		}

		child = parent;
		parent = child >> 1;
	}
}

int Pop() {
	int parent = ROOT_INDEX;
	int min_bid = HEAP[parent];
	HEAP[parent] = HEAP[HEAP_COUNT];
	HEAP_COUNT--;

	int child = parent << 1;
	if (child + 1 <= HEAP_COUNT) {
		child = (CompareRooms(HEAP[child], HEAP[child + 1]) < 0) ? child : child + 1;
	}

	while (child <= HEAP_COUNT) {
		cout << "Pop: p=" << parent << " c=" << child << endl;
		if (CompareRooms(HEAP[parent], HEAP[child]) > 0) {
			// Swap(HEAP, parent, child);
			if (parent != child) {
				HEAP[parent] = HEAP[parent] ^ HEAP[child];
				HEAP[child] = HEAP[parent] ^ HEAP[child];
				HEAP[parent] = HEAP[parent] ^ HEAP[child];
			}

			parent = child;
			child = parent << 1;
			if (child + 1 <= HEAP_COUNT) {
				child = (CompareRooms(HEAP[child], HEAP[child + 1]) < 0) ? child : child + 1;
			}
		}
		else {
			parent = child;
			child = parent << 1;
			if (child + 1 <= HEAP_COUNT) {
				child = (CompareRooms(HEAP[child], HEAP[child + 1]) < 0) ? child : child + 1;
			}
		}
	}

	return min_bid;
}
