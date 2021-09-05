#define NULL 0

const int TRAINING = 0;
const int WORKING = 1;
const int BROKEN = 2;

const int NONE_ROBOT_ID = 0;
const int NONE_WORKSPACE = 0;

const int MAX_WAITPQ_SIZE = 500000;
const int MAX_JOB_SIZE = 200001;
const int OPTION_DESC = 0;
const int OPTION_ASC = 1;

const int HEAP_OVER_ROOT = 0;
const int HEAP_ROOT = 1;

const int NOT_FOUND = -1;
const int MAX_WORKSPACE_SIZE = 50000;

typedef struct _robot {
	int mID;
	int mIQ;
	int mStatus;
	int mWorkID;
	int mUpdatedTime;

	_robot();
	~_robot();

	void CalculateIQ(const int cTime);
	bool operator<(const _robot& rhs);
	bool operator>(const _robot& rhs);
} Robot;

const int MAX_ROBOTS_SIZE = 50001;
int ROBOTS_LENGTH = 0;

Robot ROBOTS[MAX_ROBOTS_SIZE];

typedef struct _waitPQ {
	int mHeap[MAX_WAITPQ_SIZE+1];
	int mLength;
	int mOption;

	_waitPQ(const int option);
	~_waitPQ();

	int GetLength();
	void Clear();
	void Push(const int rID);
	int Pop();
	int _pop();
} WaitPQ;

WaitPQ WAITPQ_ASC(OPTION_ASC);
WaitPQ WAITPQ_DESC(OPTION_DESC);

int TEMP_VECTOR[MAX_JOB_SIZE];

typedef struct _vector {
	int* mArray;
	int mCapacity;
	int mLength;
	int mLastSortedIndex;

	_vector();
	~_vector();
	void Append(const int rID);
	void Delete(const int rID);
	void Sort();
	void _mergeSort(const int left, const int right);
	void _merge(const int left, const int mid, const int right);
	int _binarySearch(const int rID);

	int operator[](const int index);
} Vector;

typedef struct _workingArray {
	Vector mVector[MAX_WORKSPACE_SIZE + 1];
	int mLength;
} WorkingArray;

WorkingArray WORKSPACES;

void Swap(const int* mHeap, const int a_index, const int b_index);

void init(int N) {
	ROBOTS_LENGTH = N;
	WAITPQ_ASC.Clear();
	WAITPQ_DESC.Clear();
	
	for (register int rID = 1; rID <= ROBOTS_LENGTH; ++rID) {
		ROBOTS[rID].mID = rID;
		ROBOTS[rID].mIQ = 0;
		ROBOTS[rID].mStatus = TRAINING;
		ROBOTS[rID].mWorkID = NONE_WORKSPACE;
		ROBOTS[rID].mUpdatedTime = 0;

		WAITPQ_ASC.Push(rID);
		WAITPQ_DESC.Push(rID);
	}

	WORKSPACES.mLength = 0;
	for (register int wID = 1; wID <= MAX_WORKSPACE_SIZE; ++wID) {
		WORKSPACES.mVector[wID].mLength = 0;
		WORKSPACES.mVector[wID].mLastSortedIndex = 0;
	}
}

int callJob(int cTime, int wID, int mNum, int mOpt) {
	if (mOpt == OPTION_ASC && WAITPQ_ASC.GetLength() == 0) {
		return 0;
	}

	if (mOpt == OPTION_DESC && WAITPQ_DESC.GetLength() == 0) {
		return 0;
	}

	int sum_IQ = 0;
	int rID = NONE_ROBOT_ID;
	for (int i = 0; i < mNum; ++i) {
		if (mOpt == OPTION_ASC) {
			rID = WAITPQ_ASC.Pop();
		} else {
			rID = WAITPQ_DESC.Pop();
		}
		ROBOTS[rID].CalculateIQ(cTime);
		WORKSPACES.mVector[wID].Append(rID);
		ROBOTS[rID].mStatus = WORKING;
		ROBOTS[rID].mWorkID = wID;

		sum_IQ += rID;
	}
	return 0;
}

void returnJob(int cTime, int wID) {
	int rID = NONE_ROBOT_ID;
	for (int i = 0; i < WORKSPACES.mVector[wID].mLength; ++i) {
		rID = WORKSPACES.mVector[wID][i];
		ROBOTS[rID].mUpdatedTime = cTime;
		ROBOTS[rID].mStatus = TRAINING;
		ROBOTS[rID].mWorkID = NONE_WORKSPACE;
		WAITPQ_ASC.Push(rID);
		WAITPQ_DESC.Push(rID);
	}
	WORKSPACES.mVector[wID].mLength = 0;
	WORKSPACES.mVector[wID].mLastSortedIndex = 0;
}

void broken(int cTime, int rID) {
	if (ROBOTS[rID].mStatus == BROKEN) {
		return;
	}

	if (ROBOTS[rID].mStatus == TRAINING) {
		ROBOTS[rID].CalculateIQ(cTime);
		return;
	}
	
	ROBOTS[rID].mStatus = BROKEN;
}

void repair(int cTime, int rID) {
	if (ROBOTS[rID].mStatus == BROKEN) {
		return;
	}

	ROBOTS[rID].mIQ = 0;
	ROBOTS[rID].mWorkID = NONE_WORKSPACE;
	ROBOTS[rID].mUpdatedTime = cTime;
	ROBOTS[rID].mStatus = TRAINING;

	WAITPQ_ASC.Push(rID);
	WAITPQ_DESC.Push(rID);
}

int check(int cTime, int rID) {
	if (ROBOTS[rID].mStatus == BROKEN) {
		return 0;
	}

	if (ROBOTS[rID].mStatus == WORKING) {
		return ROBOTS[rID].mWorkID * (-1);
	}

	ROBOTS[rID].CalculateIQ(cTime);

	return ROBOTS[rID].mIQ;
}

void Swap(int* mHeap, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	mHeap[a_index] = mHeap[a_index] ^ mHeap[b_index];
	mHeap[b_index] = mHeap[a_index] ^ mHeap[b_index];
	mHeap[a_index] = mHeap[a_index] ^ mHeap[b_index];
}

/// Robot

_robot::_robot() {
	this->mID = NONE_ROBOT_ID;
	this->mIQ = 0;
	this->mStatus = TRAINING;
	this->mUpdatedTime = 0;
	this->mWorkID = NONE_WORKSPACE;
}

_robot::~_robot() {
	// Nothing
}

void _robot::CalculateIQ(const int cTime) {
	this->mIQ = this->mIQ + (cTime - this->mUpdatedTime);
}

// ���� ���� �켱 ����
bool _robot::operator<(const _robot& rhs) {
	if (this->mIQ == rhs.mIQ) {
		return (this->mID < rhs.mID);
	}
	return (this->mIQ < rhs.mIQ);
}


// ���� ���� �켱 ����
bool _robot::operator>(const _robot& rhs) {
	if (this->mIQ == rhs.mIQ) {
		return (this->mID < rhs.mID);
	}

	return (this->mIQ > rhs.mIQ);
}

/// WAITPQ

_waitPQ::_waitPQ(const int option) {
	this->mOption = option;
	this->mLength = 0;
	this->mHeap[0] = 0;
}

_waitPQ::~_waitPQ() {
	// Nothing
}

void _waitPQ::Clear() {
	this->mLength = 0;
}

int _waitPQ::GetLength() {
	if (this->mLength == 0) {
		return 0;
	}

	int length = 0;
	for (int i = 1; i <= this->mLength; ++i) {
		if (ROBOTS[this->mHeap[i]].mStatus == WORKING) {
			++length;
		}
	}

	return length;
}

void _waitPQ::Push(const int rID) {
	++this->mLength;
	this->mHeap[this->mLength] = rID;
	int child = this->mLength;
	int parent = child >> 1;

	if (this->mOption == OPTION_ASC) {
		while (parent > HEAP_OVER_ROOT && ROBOTS[this->mHeap[parent]] > ROBOTS[this->mHeap[child]]) {
			Swap(this->mHeap, parent, child);
			child = parent;
			parent = child >> 1;
		}
	}
	else {
		while (parent > HEAP_OVER_ROOT && ROBOTS[this->mHeap[parent]] < ROBOTS[this->mHeap[child]]) {
			Swap(this->mHeap, parent, child);
			child = parent;
			parent = child >> 1;
		}
	}
}

int _waitPQ::Pop() {
	int rID = this->_pop();

	while (ROBOTS[rID].mStatus != WORKING) {
		rID = this->_pop();
	}

	return rID;
}

int _waitPQ::_pop() {
	int rID = this->mHeap[HEAP_ROOT];
	this->mHeap[HEAP_ROOT] = this->mHeap[this->mLength];
	--this->mLength;

	int parent = HEAP_ROOT;
	int child = parent << 1;

	if (this->mOption == OPTION_ASC) {
		if (child + 1 <= this->mLength) {
			child = (ROBOTS[this->mHeap[child]] < ROBOTS[this->mHeap[child + 1]]) ? child : child + 1;
		}

		while (child <= this->mLength && ROBOTS[this->mHeap[parent]] > ROBOTS[this->mHeap[child]]) {
			Swap(this->mHeap, parent, child);

			parent = child;
			child = parent << 1;
			if (child + 1 <= this->mLength) {
				child = (ROBOTS[this->mHeap[child]] < ROBOTS[this->mHeap[child + 1]]) ? child : child + 1;
			}
		}
	}
	else {
		if (child + 1 <= this->mLength) {
			child = (ROBOTS[this->mHeap[child]] > ROBOTS[this->mHeap[child + 1]]) ? child : child + 1;
		}

		while (child <= this->mLength && ROBOTS[this->mHeap[parent]] < ROBOTS[this->mHeap[child]]) {
			Swap(this->mHeap, parent, child);

			parent = child;
			child = parent << 1;
			if (child + 1 <= this->mLength) {
				child = (ROBOTS[this->mHeap[child]] > ROBOTS[this->mHeap[child + 1]]) ? child : child + 1;
			}
		}
	}
}

/// Vector

_vector::_vector() {
	this->mCapacity = 1;
	this->mLength = 0;
	this->mLastSortedIndex = 0;
	if (this->mArray != NULL) {
		delete[] this->mArray;
	}
	this->mArray = new int[this->mCapacity];
}

_vector::~_vector() {
	if (this->mArray != NULL) {
		delete[] this->mArray;
	}
	this->mLength = 0;
}

void _vector::Append(const int rID) {
	if (this->mLength == this->mCapacity) {
		this->mCapacity = this->mCapacity << 1;
		int* temp = new int[this->mCapacity];
		for (register int i = 0; i < this->mLength; ++i) {
			temp[i] = this->mArray[i];
		}
		delete[] this->mArray;
		this->mArray = temp;
	}

	this->mArray[this->mLength] = rID;
	++this->mLength;
}

void _vector::Delete(const int rID) {
	int index = this->_binarySearch(rID);
	this->mArray[index] = MAX_ROBOTS_SIZE + 1;
	
	this->mLastSortedIndex = 0;
	this->Sort();

	--this->mLength;
}

void _vector::Sort() {
	int left = 0;
	int right = this->mLength - 1;
	if (this->mLastSortedIndex == 0) {
		this->_mergeSort(left, right);
	}
	else {
		int mid = this->mLastSortedIndex;
		this->_mergeSort(mid, right);
		this->_merge(left, mid - 1, right);
	}
	this->mLastSortedIndex = this->mLength;
}

void _vector::_mergeSort(const int left, const int right) {
	if (left == right) {
		return;
	}

	int mid = (left + right) >> 1;
	this->_mergeSort(left, mid);
	this->_mergeSort(mid+1, right);
	this->_merge(left, mid, right);
}

void _vector::_merge(const int left, const int mid, const int right) {
	int i = left;
	int j = mid + 1;
	int t_i = 0;

	while (i <= mid && j <= right) {
		if (this->mArray[i] < this->mArray[j]) {
			TEMP_VECTOR[t_i++] = this->mArray[i++];
		}
		else {
			TEMP_VECTOR[t_i++] = this->mArray[j++];
		}
	}

	while (i <= mid) {
		TEMP_VECTOR[t_i++] = this->mArray[i++];
	}

	while (j <= right) {
		TEMP_VECTOR[t_i++] = this->mArray[j++];
	}

	for (register int k = 0; k < t_i; ++k) {
		this->mArray[left + k] = TEMP_VECTOR[k];
	}
}

int _vector::_binarySearch(const int rID) {
	int low = 0;
	int high = this->mLength - 1;
	int mid = 0;
	int found = NOT_FOUND;

	while (low <= high) {
		mid = (low + high) >> 1;
		if (this->mArray[mid] == rID) {
			found = mid;
			break;
		}
		else if (this->mArray[mid] < rID) {
			low = mid + 1;
		}
		else {
			high = mid;
		}
	}

	return found;
}

int _vector::operator[](const int index) {
	return this->mArray[index];
}
