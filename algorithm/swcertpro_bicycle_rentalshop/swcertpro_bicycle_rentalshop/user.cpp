#define MAXN		100
#define MAXL		8

#define NULL 0

const int NOT_RENT = 0;
const int MAX_BICYCLES = 20000;

int BICYCLE_DURABLETIME = 0;
int STATION_COUNT = 0;

typedef struct _bicycle {
	int mRideTime;
	int mRentTime;
	int mStationIndex;
	int mStartTime;
	bool mDeleted;

	bool operator<(const _bicycle& rhs);
} Bicycle;

Bicycle BICYCLES[MAX_BICYCLES];

const int MAX_NAME_LENGTH = MAXL;
const int NO_BICYCLE = -1;
int BICYCLES_LAST_INDEX = 0;

typedef struct _user {
	char mName[MAX_NAME_LENGTH];
	int mTicketBuyTime;
	int mTicketValidTime;
	int mRentBicycleIndex;
} User;


const int MAX_HASH_TABLE = 20000;
const unsigned long NO_USER = -1;
User USERS_HASHTABLE[MAX_HASH_TABLE];

unsigned long hash(const char* name);
void add_user_hashtable(const char* name, const int buyTime, const int validTime);
unsigned long search_user_index(const char* name);

void StrCpy(char* dest, const char* src);
int StrCmp(const char* src, const char* dest);

typedef struct _vector {
	int mCapacity;
	int mSize;
	int mLastSortedIndex;
	int* mpBicycles;

	_vector();
	~_vector();
	void Clear();
	void Append(const int bicycle_index);
	void Delete(const int bicycle_index);
	void Sort();
	void _mergeSort(const int left, const int right);
	void _merge(const int left, const int mid, const int right);
	int operator[](const int index);
} Vector;

const int MAX_STATIONS = 100;
const int NO_STATION = -1;
const int NO_TIME = 0;
const int NO_VALIDTIME = 0;

typedef struct _station {
	int mDeliverytime;
	int mRentableBicycles;
	Vector mBicycleVector;

	_station() :mDeliverytime(0), mRentableBicycles(0) {}
	int GetBicycle(const int currentTime);
} Station;

Station STATIONS[MAX_STATIONS];

void init(int N, int durableTime, int deliveryTimes[MAXN])
{
	STATION_COUNT = N;
	BICYCLE_DURABLETIME = durableTime;
	BICYCLES_LAST_INDEX = 0;
	// init USERS
	for (register int i = 0; i < MAX_HASH_TABLE; ++i) {
		USERS_HASHTABLE[i].mName[0] = '\0';
		USERS_HASHTABLE[i].mRentBicycleIndex = NO_BICYCLE;
		USERS_HASHTABLE[i].mTicketBuyTime = NO_TIME;
		USERS_HASHTABLE[i].mTicketValidTime = NO_VALIDTIME;
	}
	// init Station
	for (register int i = 0; i < N; ++i) {
		STATIONS[i].mDeliverytime = deliveryTimes[i];
		STATIONS[i].mBicycleVector.Clear();
		STATIONS[i].mRentableBicycles = 0;
	}
}

void addBicycle(int cTimestamp, int pID, int bicycleNum)
{
	for (int i = 0; i < bicycleNum; ++i) {
		BICYCLES[BICYCLES_LAST_INDEX].mStationIndex = pID;
		BICYCLES[BICYCLES_LAST_INDEX].mRideTime = 0;
		BICYCLES[BICYCLES_LAST_INDEX].mRentTime = NOT_RENT;
		BICYCLES[BICYCLES_LAST_INDEX].mDeleted = false;
		BICYCLES[BICYCLES_LAST_INDEX].mStartTime = cTimestamp;
		
		STATIONS[pID].mBicycleVector.Append(BICYCLES_LAST_INDEX);
		STATIONS[pID].mRentableBicycles++;
		++BICYCLES_LAST_INDEX;
	}

	STATIONS[pID].mBicycleVector.Sort();
}

void buyTicket(int cTimestamp, char uName[MAXL], int validTime)
{
	unsigned long index = search_user_index(uName);

	if (index == NO_USER) {
		add_user_hashtable(uName, cTimestamp, validTime);
		return;
	}

	int expired = USERS_HASHTABLE[index].mTicketBuyTime + USERS_HASHTABLE[index].mTicketValidTime;
	if (expired <= cTimestamp) {
		USERS_HASHTABLE[index].mTicketValidTime += validTime;
	}
	else {
		USERS_HASHTABLE[index].mTicketBuyTime = cTimestamp;
		USERS_HASHTABLE[index].mTicketValidTime = validTime;
	}
}

int rentBicycle(int cTimestamp, char uName[MAXL], int pID)
{
	unsigned long user_index = search_user_index(uName);
	if (user_index == NO_USER) {
		return -1;
	}
	if (USERS_HASHTABLE[user_index].mRentBicycleIndex != NO_BICYCLE) {
		return -1;
	}

	if (STATIONS[pID].mRentableBicycles == 0) {
		return -1;
	}

	int expired = USERS_HASHTABLE[user_index].mTicketBuyTime + USERS_HASHTABLE[user_index].mTicketValidTime;
	if (expired <= cTimestamp) {
		return -1;
	}

	int bicycle_index = STATIONS[pID].GetBicycle(cTimestamp);

	USERS_HASHTABLE[user_index].mRentBicycleIndex = bicycle_index;
	STATIONS[pID].mRentableBicycles--;
	BICYCLES[bicycle_index].mRentTime = cTimestamp;

	return BICYCLES[bicycle_index].mRideTime;
}

int returnBicycle(int cTimestamp, char uName[MAXL], int pID)
{
	unsigned long user_index = search_user_index(uName);
	if (USERS_HASHTABLE[user_index].mRentBicycleIndex == NO_BICYCLE) {
		return -1;
	}

	int delayed = cTimestamp - (USERS_HASHTABLE[user_index].mTicketBuyTime + USERS_HASHTABLE[user_index].mTicketValidTime - 1);
	if (delayed <= 0) {
		delayed = 0;
	}

	int bicycle_index = USERS_HASHTABLE[user_index].mRentBicycleIndex;
	int ride_time = cTimestamp - BICYCLES[bicycle_index].mRentTime;
	USERS_HASHTABLE[user_index].mRentBicycleIndex = NO_BICYCLE;

	if (ride_time > BICYCLE_DURABLETIME) {
		BICYCLES[bicycle_index].mDeleted = false;
		BICYCLES[bicycle_index].mRentTime = NOT_RENT;
		BICYCLES[bicycle_index].mRideTime = 0;
		BICYCLES[bicycle_index].mStationIndex = pID;
		BICYCLES[bicycle_index].mStartTime = cTimestamp + STATIONS[pID].mDeliverytime;
	}
	else {
		BICYCLES[bicycle_index].mRentTime = ride_time;
	}
	STATIONS[pID].mBicycleVector.mLastSortedIndex = 0;
	STATIONS[pID].mBicycleVector.Sort();

	return delayed;
}

// User Hash

unsigned long hash(const char* name) {
	unsigned long index = 5381;
	int character = *name;

	while (character > 0) {
		index = index << 5;
		index = index + character;
		index = index % MAX_HASH_TABLE;
		character = *(++name);
	}
	return index;
}

void add_user_hashtable(const char* name, const int buyTime, const int validTime) {
	unsigned long user_index = hash(name);

	while (USERS_HASHTABLE[user_index].mName[0] != NULL) {
		if (StrCmp(USERS_HASHTABLE[user_index].mName, name) == 0) {
			return;
		}
		user_index = (user_index+1) % MAX_HASH_TABLE;
	}
	StrCpy(USERS_HASHTABLE[user_index].mName, name);
	USERS_HASHTABLE[user_index].mTicketBuyTime = buyTime;
	USERS_HASHTABLE[user_index].mTicketValidTime = validTime;
	USERS_HASHTABLE[user_index].mRentBicycleIndex = NO_BICYCLE;
}

unsigned long search_user_index(const char* name) {
	unsigned long user_index = hash(name);
	int count = 0;

	while (count < MAX_HASH_TABLE && USERS_HASHTABLE[user_index].mName[0] != NULL) {
		if (StrCmp(USERS_HASHTABLE[user_index].mName, name) == 0) {
			return user_index;
		}
		user_index = (user_index + 1) % MAX_HASH_TABLE;
		++count;
	}

	return NO_USER;
}

// Stirng

void StrCpy(char* dest, const char* src) {
	while (*src != '\0') {
		*dest++ = *src++;
	}
	*dest = '\0';	
}

int StrCmp(const char* src, const char* dest) {
	while (*src != '\0' && *src == *dest) {
		src++;
		dest++;
	}

	return *src - *dest;
}

// Bicycle

bool _bicycle::operator<(const _bicycle& rhs)
{
	// 삭제된 bicycle은 무조건 큼
	if (this->mDeleted) {
		return false;
	}

	if (rhs.mDeleted) {
		return true;
	}

	if (this->mRideTime - rhs.mRideTime) {
		return this->mRentTime < rhs.mRideTime;
	}

	return this->mStartTime < rhs.mStartTime;
}

// Vector

_vector::_vector() {
	this->mCapacity = 1;
	this->mSize = 0;
	this->mLastSortedIndex = 0;
	if (this->mpBicycles != NULL) {
		delete[] this->mpBicycles;
	}
	this->mpBicycles = new int[this->mCapacity];
}

_vector::~_vector() {
	if (this->mpBicycles != NULL) {
		delete[] this->mpBicycles;
	}
}

void _vector::Clear()
{
	this->mSize = 0;
}

void _vector::Append(const int bicycle_index) {
	int index = this->mSize;
	if (this->mSize == this->mCapacity) {
		this->mCapacity = this->mCapacity << 1;
		int* temp = new int[this->mCapacity];

		for (register int i = 0; i < this->mSize; ++i) {
			temp[i] = this->mpBicycles[i];
		}
		delete[] this->mpBicycles;
		this->mpBicycles = temp;
	}
	this->mpBicycles[index] = bicycle_index;
	++this->mSize;
}

void _vector::Delete(const int bicycle_index) {
	BICYCLES[bicycle_index].mDeleted = true;
	this->mLastSortedIndex = 0;
	this->Sort();
}

void _vector::Sort() {
	const int left = 0;
	const int right = this->mSize - 1;

	if (this->mLastSortedIndex == 0) {
		this->_mergeSort(left, right);
		return;
	}

	this->_mergeSort(this->mLastSortedIndex, right);
	this->_merge(left, this->mLastSortedIndex - 1, right);
}

void _vector::_mergeSort(const int left, const int right) {
	if (left == right) {
		return;
	}

	int mid = (left + right) >> 1;
	this->_mergeSort(left, mid);
	this->_mergeSort(mid + 1, right);
	this->_merge(left, mid, right);
}

int temp[MAX_BICYCLES] = { 0, };

void _vector::_merge(const int left, const int mid, const int right) {
	int i = left;
	int j = mid + 1;
	int t_i = 0;

	while (i <= mid && j <= right) {
		if (BICYCLES[i] < BICYCLES[j]) {
			temp[t_i++] = this->mpBicycles[i++];
		}
		else {
			temp[t_i++] = this->mpBicycles[j++];
		}
	}

	while (i <= mid) {
		temp[t_i++] = this->mpBicycles[i++];
	}
	while (j <= right) {
		temp[t_i++] = this->mpBicycles[j++];
	}

	for (register int k = 0; k < t_i; ++k) {
		this->mpBicycles[left + k] = temp[k];
	}
}

int _vector::operator[](const int index) {
	int bicycle_index = this->mpBicycles[index];
	return bicycle_index;
}

int _station::GetBicycle(const int currentTime)
{
	int index = this->mBicycleVector[0];
	if (BICYCLES[index].mDeleted == true) {
		return NO_BICYCLE;
	}

	if (BICYCLES[index].mStartTime > currentTime) {
		return NO_BICYCLE;
	}

	return index;
}
