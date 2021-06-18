#include <iostream>

using namespace std;

const int CHUNK_SIZE = 10;
const int MAX_N_SIZE = 100;
const int MAX_TABLE_SIZE = MAX_N_SIZE / CHUNK_SIZE;
const int NULL_DATA = -1;

const bool FOUND = true;
const bool NOT_FOUND = false;

typedef struct _Node {
	int mValue;
	struct _Node* mNext;
} Node;

Node NODE_POOL[MAX_N_SIZE] = { 0, };
int POOL_LENGTH = 0;

typedef struct _HashTable {
	Node* mTable[MAX_TABLE_SIZE];

	void init();
	int _hash(const int value);
	void insert(const int value);
	void deleteNode(const int value);
	bool search(const int value);
	int searchNearLeft(const int value);
	int searchNearRight(const int value);
} HashTable;

HashTable HASHTABLE;

void init();
void PrintHashTable(HashTable* const pTable);

int main() {
	init();
	int input_data[] = { 6,19,23,37,45,57,8,10,30,59,78,77,75,69 };
	const int input_size = sizeof(input_data) / sizeof(input_data[0]);

	for (int i = 0; i < input_size; ++i) {
		HASHTABLE.insert(input_data[i]);
	}
	PrintHashTable(&HASHTABLE);

	int value = NULL_DATA;

	value = 77;
	HASHTABLE.deleteNode(value);
	cout << "Delete: " << value << endl;
	PrintHashTable(&HASHTABLE);

	value = 75;
	HASHTABLE.deleteNode(value);
	cout << "Delete: " << value << endl;
	PrintHashTable(&HASHTABLE);

	value = 69;
	HASHTABLE.deleteNode(value);
	cout << "Delete: " << value << endl;
	PrintHashTable(&HASHTABLE);

	value = 69;
	HASHTABLE.deleteNode(value);
	cout << "Delete: " << value << endl;
	PrintHashTable(&HASHTABLE);

	int nearLeft = NULL_DATA;
	int nearRight = NULL_DATA;
	int search = NULL_DATA;

	search = 5;
	nearLeft = HASHTABLE.searchNearLeft(search);
	nearRight = HASHTABLE.searchNearRight(search);
	cout << "Left: " << nearLeft << " -> " << search << " -> Right: " << nearRight << endl;

	search = 6;
	nearLeft = HASHTABLE.searchNearLeft(search);
	nearRight = HASHTABLE.searchNearRight(search);
	cout << "Left: " << nearLeft << " -> " << search << " -> Right: " << nearRight << endl;

	search = 7;
	nearLeft = HASHTABLE.searchNearLeft(search);
	nearRight = HASHTABLE.searchNearRight(search);
	cout << "Left: " << nearLeft << " -> " << search << " -> Right: " << nearRight << endl;

	search = 77;
	nearLeft = HASHTABLE.searchNearLeft(search);
	nearRight = HASHTABLE.searchNearRight(search);
	cout << "Left: " << nearLeft << " -> " << search << " -> Right: " << nearRight << endl;

	search = 79;
	nearLeft = HASHTABLE.searchNearLeft(search);
	nearRight = HASHTABLE.searchNearRight(search);
	cout << "Left: " << nearLeft << " -> " << search << " -> Right: " << nearRight << endl;

	return 0;
}

void init() {
	POOL_LENGTH = 0;
	HASHTABLE.init();
}

void PrintHashTable(HashTable* const pTable) {
	Node* node = NULL;
	for (int hash_i = 0; hash_i < MAX_TABLE_SIZE; ++hash_i) {
		node = pTable->mTable[hash_i];
		cout << "Hash index: " << hash_i << " range: [" << (hash_i * CHUNK_SIZE) << "~" << (hash_i * CHUNK_SIZE) + 9 << "]" << endl;
		cout << "> Data: ";
		if (node == NULL) {
			cout << endl;
			continue;
		}
		
		while (node != NULL) {
			cout << node->mValue << ' ';
			node = node->mNext;
		}
		cout << endl;
	}
	cout << endl;
}

// _HashTable Implementation

void _HashTable::init() {
	for (int i = 0; i < MAX_TABLE_SIZE; ++i) {
		this->mTable[i] = NULL;
	}
}

int _HashTable::_hash(const int value) {
	int hash = value / CHUNK_SIZE;
	return hash;
}

void _HashTable::insert(const int value) {
	Node* newNode = &NODE_POOL[POOL_LENGTH];
	++POOL_LENGTH;
	newNode->mValue = value;
	newNode->mNext = NULL;

	int index = this->_hash(value);
	Node* node = this->mTable[index];

	if (node == NULL) {
		this->mTable[index] = newNode;
		return;
	}

	while (node->mNext != NULL) {
		node = node->mNext;
	}

	node->mNext = newNode;
}

void _HashTable::deleteNode(const int value) {
	int index = this->_hash(value);
	Node* node = this->mTable[index];

	if (node == NULL) {
		return;
	}

	if (node->mNext == NULL && node->mValue == value) {
		this->mTable[index] = NULL;
		node->mValue = NULL_DATA;
		return;
	}

	Node* prev = node;
	while (node != NULL) {
		if (node->mValue == value) {
			node->mValue = NULL_DATA;
			prev->mNext = node->mNext;
			break;
		}
		prev = node;
		node = node->mNext;
	}
}

bool _HashTable::search(const int value) {
	int index = this->_hash(value);
	Node* node = this->mTable[index];
	if (node == NULL) {
		return NOT_FOUND;
	}

	while (node != NULL) {
		if (node->mValue == value) {
			return FOUND;
		}
		node = node->mNext;
	}
	return NOT_FOUND;
}

int _HashTable::searchNearLeft(const int value) {
	int index = this->_hash(value);
	Node* node = NULL;
	int max = NULL_DATA;

	for (int i = index; i >= 0 && max <= NULL_DATA; --i) {
		node = this->mTable[i];
		if (node == NULL) {
			continue;
		}

		while (node != NULL) {
			if (node->mValue < value) {
				max = (max <= node->mValue) ? node->mValue : max;
			}
			node = node->mNext;				
		}
	}

	return max;
}

int _HashTable::searchNearRight(const int value) {
	int index = this->_hash(value);
	Node* node = NULL;
	int min = MAX_N_SIZE + 1;

	for (int i = index; i < MAX_TABLE_SIZE && min >= MAX_N_SIZE + 1; ++i) {
		node = this->mTable[i];
		if (node == NULL) {
			continue;
		}

		while (node != NULL) {
			if (node->mValue > value) {
				min = (min >= node->mValue) ? node->mValue : min;
			}
			node = node->mNext;
		}
	}

	return (min > MAX_N_SIZE) ? -1 : min;
}
