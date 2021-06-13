#define NULL 0

const int MAX_ROOMS = 40000;
const int MAX_DAYS = 97;
const int MAX_CANDS = 5005;
const int MAX_Y = 100;
const int MAX_X = 100;

typedef struct _RoomInfo {
	int mBid;
	int mY;
	int mX;
	int mPrice;
	int mRating;

	void set(const int bid, const int y, const int x, const int price, const int rating);
	void clear();
	bool can_reserve(const int cday, const int night);
	bool operator<(const _RoomInfo& other);
	_RoomInfo& operator=(const _RoomInfo& other);
} RoomInfo;

RoomInfo TEMP[MAX_CANDS + 1] = { 0, };

typedef struct _Vector {
	int mSize;
	int mLength;
	RoomInfo* mRooms;
	int mLastSort;

	_Vector();
	~_Vector();
	void push_back(const int bid, const int y, const int x, const int price, const int rating);
	void erase();
	void sort();
	void _merge_sort(const int l, const int r);
	void _merge(const int l, const int m, const int r);
} Vector;

Vector MAP[MAX_Y][MAX_X];

int RESERVE_TABLE[MAX_ROOMS][MAX_DAYS] = { 0, };
enum {
	EMPTY = -1,
	STAY = 0,
	CHECKIN = 1
};

Vector CANDIDATES;

int MAP_SIZE = 0;

void init(int M)
{
	MAP_SIZE = M;
	for (int y = 0; y < MAP_SIZE; ++y) {
		for (int x = 0; x < MAP_SIZE; ++x) {
			MAP[y][x].erase();
		}
	}
	for (int bid = 0; bid < MAX_ROOMS; ++bid) {
		for (int day = 0; day < MAX_DAYS; ++day) {
			RESERVE_TABLE[bid][day] = EMPTY;
		}
	}
}

void add_bnb(int bid, int y, int x, int price, int rating)
{
	MAP[y][x].push_back(bid, y, x, price, rating);

	// Keep sorted Rooms up to MAX_CANDS(5,005)
	if (MAP[y][x].mLength == MAX_CANDS + 1) {
		MAP[y][x].sort();
		// ºÒÇÊ¿ä
		//MAP[y][x].mRooms[MAX_CANDS].clear();
		MAP[y][x].mLength = MAX_CANDS;
		MAP[y][x].mLastSort = MAX_CANDS;
	}
}

int reserve(int bid, int cday, int night)
{
	const int duration = cday + night;
	for (register int day = cday; day < duration; ++day) {
		if (RESERVE_TABLE[bid][day] >= STAY) {
			return 0;
		}
	}

	RESERVE_TABLE[bid][cday] = CHECKIN;
	for (register int day = cday + 1; day < duration; ++day) {
		RESERVE_TABLE[bid][day] = STAY;
	}
	return 1;
}

int cancel(int bid, int cday)
{
	if (RESERVE_TABLE[bid][cday] < CHECKIN) {
		return 0;
	}

	RESERVE_TABLE[bid][cday] = EMPTY;
	int day = cday + 1;
	while (RESERVE_TABLE[bid][day] == STAY) {
		RESERVE_TABLE[bid][day] = EMPTY;
		++day;
	}
	return 1;
}

int search(int opt, int y, int x, int cday, int night, int top5_bid[5])
{
	CANDIDATES.erase();

	if (opt == 0) {
		for (int i = 0; i < MAP[y][x].mLength; ++i) {
			if (MAP[y][x].mRooms[i].can_reserve(cday, night)) {
				CANDIDATES.push_back(
					MAP[y][x].mRooms[i].mBid,
					MAP[y][x].mRooms[i].mY,
					MAP[y][x].mRooms[i].mX,
					MAP[y][x].mRooms[i].mPrice,
					MAP[y][x].mRooms[i].mRating
				);
			}
		}
	}
	else {
		for (int dy = -1; dy < 2; ++dy) {
			for (int dx = -1; dx < 2; ++dx) {
				int py = y + dy;
				int px = x + dx;
				if (py < 0 || px < 0 || py >= MAP_SIZE || px >= MAP_SIZE) {
					continue;
				}

				for (int i = 0; i < MAP[py][px].mLength; ++i) {
					if (MAP[py][px].mRooms[i].can_reserve(cday, night)) {
						CANDIDATES.push_back(
							MAP[py][px].mRooms[i].mBid,
							MAP[py][px].mRooms[i].mY,
							MAP[py][px].mRooms[i].mX,
							MAP[py][px].mRooms[i].mPrice,
							MAP[py][px].mRooms[i].mRating
						);
					}
				}
			}
		}
	}

	if (CANDIDATES.mLength == 0) {
		return 0;
	}

	CANDIDATES.sort();
	int count = 0;
	while (count < 5) {
		top5_bid[count] = CANDIDATES.mRooms[count].mBid;
		++count;
		if (CANDIDATES.mLength == count) {
			break;
		}
	}

	return count;
}

// # _RoomInfo

void _RoomInfo::set(const int bid, const int y, const int x, const int price, const int rating) {
	this->mBid = bid;
	this->mY = y;
	this->mX = x;
	this->mPrice = price;
	this->mRating = rating;
}

void _RoomInfo::clear() {
	this->mBid = 0;
	this->mY = -1;
	this->mX = -1;
	this->mPrice = -1;
	this->mRating = 0;
}

bool _RoomInfo::can_reserve(const int cday, const int night) {
	const int bid = this->mBid;
	const int duration = cday + night;
	for (register int day = cday; day < duration; ++day) {
		if (RESERVE_TABLE[bid][day] >= STAY) {
			return false;
		}
	}

	return true;
}

bool _RoomInfo::operator<(const _RoomInfo& other) {
	if (this->mPrice - other.mPrice) {
		return this->mPrice < other.mPrice;
	}
	if (this->mRating - other.mRating) {
		return this->mRating > other.mRating;
	}
	return this->mBid > other.mBid;
}

_RoomInfo& _RoomInfo::operator=(const _RoomInfo& other) {
	this->mBid = other.mBid;
	this->mY = other.mY;
	this->mX = other.mX;
	this->mPrice = other.mPrice;
	this->mRating = other.mRating;

	return *this;
}


// # _Vector

_Vector::_Vector() {
	this->mSize = 1;
	this->mRooms = new RoomInfo[this->mSize];
	this->mLastSort = 0;
	this->mLength = 0;
}

_Vector::~_Vector() {
	if (this->mRooms != NULL) {
		delete[] this->mRooms;
	}
	this->mSize = 0;
	this->mLastSort = 0;
	this->mLength = 0;
}

void _Vector::push_back(const int bid, const int y, const int x, const int price, const int rating) {
	RoomInfo* temp = NULL;

	if (this->mLength == this->mSize) {
		this->mSize <<= 1;
		temp = new RoomInfo[this->mSize];

		for (register int i = 0; i < this->mLength; ++i) {
			temp[i] = this->mRooms[i];
		}
		delete[] this->mRooms;
		this->mRooms = temp;
	}

	this->mRooms[this->mLength].set(bid, y, x, price, rating);
	++this->mLength;
}

void _Vector::erase() {
	if (this->mRooms != NULL) {
		delete[] this->mRooms;
	}
	this->mSize = 1;
	this->mRooms = new RoomInfo[this->mSize];
	this->mLastSort = 0;
	this->mLength = 0;
}

void _Vector::sort() {
	const int r = this->mLength - 1;

	if (this->mLastSort > 0) {
		this->_merge_sort(this->mLastSort, r);
		this->_merge(0, this->mLastSort - 1, r);
	}
	else {
		this->_merge_sort(0, r);
	}
}

void _Vector::_merge_sort(const int l, const int r) {
	if (l == r) {
		return;
	}

	int m = (l + r) >> 1;
	this->_merge_sort(l, m);
	this->_merge_sort(m+1, r);
	this->_merge(l, m, r);
}

void _Vector::_merge(const int l, const int m, const int r) {
	int i = l;
	int j = m + 1;
	int t_i = 0;

	while (i <= m && j <= r) {
		if (this->mRooms[i] < this->mRooms[j]) {
			TEMP[t_i++] = this->mRooms[i++];
		}
		else {
			TEMP[t_i++] = this->mRooms[j++];
		}
	}

	while (i <= m) {
		TEMP[t_i++] = this->mRooms[i++];
	}
	while (j <= r) {
		TEMP[t_i++] = this->mRooms[j++];
	}

	for (register int k = 0; k < t_i; ++k) {
		this->mRooms[l + k] = TEMP[k];
	}
}
