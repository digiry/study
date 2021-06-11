#include <iostream>
#include <bitset>

using namespace std;

typedef unsigned long long ULLONG;
const int MAX_Y = 100;
const int MAX_X = 100;
const int MAX_ROOMS = 40000;
const int MAX_AVAILABLE_ROOMS = 10000;
const int MAX_X_LENGTH = 157;

ULLONG MAP[MAX_Y][MAX_X_LENGTH] = { 0, };
int ROOMS_TABLE[MAX_ROOMS] = { 0, };

struct RoomInfo {
	int bid;
	int y;
	int x;
	int price;
	int rating;
	bool bDeleted;
	struct RoomInfo* pNext;

	void set_info(int bid, int y, int x, int price, int rating);
	bool operator<(struct RoomInfo* other);
};

struct RoomInfo ROOMS[MAX_AVAILABLE_ROOMS];
int ROOMS_POOL_INDEX = 0;
int MAP_LENGTH = 0;

struct RoomInfo* new_room();

void set_room_bit(int bid, int y, int x);
int exists_room(int bid, int y, int x);

void init(int M)
{
	MAP_LENGTH = M;
	for (register int i = 0; i < MAP_LENGTH; ++i) {
		MAP[i][0] = 0;
		MAP[i][1] = 0;
	}
	for (register int i = 0; i < MAX_ROOMS; ++i) {
		ROOMS_TABLE[i] = 0;
	}
}

void add_bnb(int bid, int y, int x, int price, int rating)
{
	ROOMS_TABLE[bid] = ROOMS_POOL_INDEX;
	struct RoomInfo* newRoom = new_room();
	newRoom->set_info(bid, y, x, price, rating);
	set_room_bit(bid, y, x);

	for (int i = 0; i < ROOMS_POOL_INDEX; ++i) {
		// TODO
	}
}

int reserve(int bid, int cday, int night)
{
	return 1;
}

int cancel(int bid, int cday)
{
	return 1;
}

int search(int opt, int y, int x, int cday, int night, int top5_bid[5])
{
	return 0;
}

void RoomInfo::set_info(int bid, int y, int x, int price, int rating)
{
	this->bid = bid;
	this->y = y;
	this->x = x;
	this->price = price;
	this->rating = rating;
	this->bDeleted = false;
	this->pNext = NULL;
}

bool RoomInfo::operator<(struct RoomInfo* other)
{
	if (this->price != other->price) {
		return this->price < other->price;
	}
	if (this->rating != other->rating) {
		return this->rating > other->rating;
	}
	return this->bid > other->bid;
}


void set_room_bit(int bid, int y, int x) {
	int cord = x + (y * MAP_LENGTH);
	int y_index = cord / MAP_LENGTH;
	int bit_index = 63 - (cord % MAP_LENGTH);
	int room_index = ROOMS_TABLE[bid];
	
	ULLONG mask = ULLONG(1) << bit_index;
	//cout << "mask:" << bitset<64>(mask) << endl;
	MAP[room_index][y_index] |= mask;

	//cout << "room:" << bitset<64>(MAP[room_index][y_index]) << endl;
}

int exists_room(int bid, int y, int x) {
	int cord = x + (y * MAP_LENGTH);
	int y_index = cord / MAP_LENGTH;
	int bit_index = 63 - (cord % MAP_LENGTH);
	int room_index = ROOMS_TABLE[bid];

	ULLONG mask = ULLONG(1) << bit_index;

	return MAP[room_index][y_index] & mask;
}

struct RoomInfo* new_room() {
	return &(ROOMS[ROOMS_POOL_INDEX++]);
}
