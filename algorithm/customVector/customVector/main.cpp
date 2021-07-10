#include <iostream>

using namespace std;

#define NULL 0

const int CMD_INIT = 1;
const int CMD_ADD = 2;
const int MAX_WAIT_SIZE = 10000;
const int MAX_MACHINE_SIZE = 100;

typedef struct _Wait {
	int mId;
	int mNum;
	int mPriority;

	bool operator>(const _Wait& rhs);
	_Wait& operator=(const _Wait& rhs);
} Wait;

Wait TEMP_WAITS[MAX_WAIT_SIZE] = { 0, };

typedef struct _WaitVector {
	int mCapacity;
	int mSize;
	int mSortedIndex;
	Wait* mpWait;

	_WaitVector();
	Wait& operator[](const int index);
	void append(const int mId, const int mNum, const int mPriority);
	void sort();
	void _mergeSort(const int left, const int right);
	void _merge(const int left, const int mid, const int right);
} WaitVector;

typedef struct _Machine {
	int mId;
	int mDuration;
	int mCapacity;
	int mStart;
	int mEnd;
	int mSumWaits;
	WaitVector* mpWaitVector;

	bool operator>(const _Machine& rhs);
	_Machine& operator=(const _Machine& rhs);
	void addWait(const int mId, const int mNum, const int mPriority);
} Machine;

Machine TEMP_MACHINES[MAX_MACHINE_SIZE] = { 0, };

typedef struct _MachineVector {
	int mCapacity;
	int mSize;
	int mSortedIndex;
	Machine* mpMachine;

	_MachineVector();
	Machine& operator[](const int index);
	void append(const int mId, const int mDuration, const int mCapacity);
	void sort();
	void _mergeSort(const int left, const int right);
	void _merge(const int left, const int mid, const int right);
} MachineVector;

// initial

MachineVector MACHINES;

void printWaitVector(WaitVector& vector);
void printWaitVector(WaitVector* vector);
void printMachineVector(MachineVector& vector);

int main() {
	int Q = 0;
	int N = 0;
	int m_id = 0;
	int m_dur = 0;
	int m_cap = 0;
	int num = 0;
	int priority = 0;
	int cmd = 0;

	cin >> Q;

	for (int i = 0; i < Q; ++i) {
		cin >> cmd;
		if (cmd == CMD_INIT) {
			cin >> N;
			for (int n = 0; n < N; ++n) {
				cin >> m_id >> m_dur >> m_cap;
				MACHINES.append(m_id, m_dur, m_cap);
			}
		}
		else if (cmd == CMD_ADD) {
			// Nothing
		}
	}

	printMachineVector(MACHINES);
	MACHINES.sort();
	printMachineVector(MACHINES);

	return 0;
}

void printWaitVector(WaitVector& vector) {
	cout << "WAIT Vector: " << endl;
	for (int i = 0; i < vector.mSize; ++i) {
		cout << "[" << i << "] id:" << vector[i].mId << ", num:" << vector[i].mNum << ", priority:" << vector[i].mPriority << endl;
	}
}

void printWaitVector(WaitVector* vector) {
	cout << "WAIT Vector: " << endl;
	for (int i = 0; i < vector->mSize; ++i) {
		cout << "[" << i << "] id:" << (*vector)[i].mId << ", num:" << (*vector)[i].mNum << ", priority:" << (*vector)[i].mPriority << endl;
	}
}

void printMachineVector(MachineVector& vector) {
	cout << "MACHINE Vector: " << endl;
	for (int i = 0; i < vector.mSize; ++i) {
		cout << "[" << i << "] id:" << vector[i].mId << ", dur:" << vector[i].mDuration << ", cap:" << vector[i].mCapacity << endl;
		if (vector[i].mpWaitVector != NULL) {
			printWaitVector(vector[i].mpWaitVector);
		}
	}
}

// _Wait Implementation

bool _Wait::operator>(const _Wait& rhs) {
	if (this->mNum - rhs.mNum) {
		return (this->mNum > rhs.mNum);
	}

	return (this->mId > rhs.mId);
}

_Wait& _Wait::operator=(const _Wait& rhs) {
	this->mId = rhs.mId;
	this->mNum = rhs.mNum;
	this->mPriority = rhs.mPriority;

	return *this;
}

// _WaitVector
_WaitVector::_WaitVector() {
	this->mCapacity = 1;
	this->mSize = 0;
	this->mSortedIndex = 0;
	if (this->mpWait != NULL) {
		delete[] this->mpWait;
	}
	this->mpWait = new Wait[1];
}

Wait& _WaitVector::operator[](const int index) {
	return this->mpWait[index];
}

void _WaitVector::append(const int mId, const int mNum, const int mPriority) {
	if (this->mSize == this->mCapacity) {
		this->mCapacity = this->mCapacity << 1;
		Wait* temp = new Wait[this->mCapacity];

		for (register int i = 0; i < this->mSize; ++i) {
			temp[i] = this->mpWait[i];
		}
		delete[] this->mpWait;
		this->mpWait = temp;
		temp = NULL;
	}
	int index = this->mSize;
	this->mpWait[index].mId = mId;
	this->mpWait[index].mNum = mNum;
	this->mpWait[index].mPriority = mPriority;
	++this->mSize;
}

void _WaitVector::sort() {
	const int right = this->mSize - 1;
	if (this->mSortedIndex == 0) {
		this->_mergeSort(0, right);
		return;
	}

	this->_mergeSort(this->mSortedIndex, right);
	this->_merge(0, this->mSortedIndex + 1, right);
	this->mSortedIndex = right;
}

void _WaitVector::_mergeSort(const int left, const int right) {
	if (left == right) {
		return;
	}

	int mid = (left + right) >> 1;
	this->_mergeSort(left, mid);
	this->_mergeSort(mid + 1, right);
	this->_merge(left, mid, right);
}

void _WaitVector::_merge(const int left, const int mid, const int right) {
	int i = left;
	int j = mid + 1;
	int t_i = 0;

	while (i <= mid && j <= right) {
		if (this->mpWait[i] > this->mpWait[j]) {
			TEMP_WAITS[t_i] = this->mpWait[i];
			++t_i;
			++i;
		}
		else {
			TEMP_WAITS[t_i] = this->mpWait[j];
			++t_i;
			++j;
		}
	}

	while (i <= mid) {
		TEMP_WAITS[t_i] = this->mpWait[i];
		++t_i;
		++i;
	}

	while (j <= right) {
		TEMP_WAITS[t_i] = this->mpWait[j];
		++t_i;
		++j;
	}

	for (register int k = 0; k < t_i; ++k) {
		this->mpWait[left + k] = TEMP_WAITS[k];
	}
}

// _Machine implementation

bool _Machine::operator>(const _Machine& rhs) {
	if (this->mSumWaits - rhs.mSumWaits) {
		return (this->mSumWaits > rhs.mSumWaits);
	}

	return (this->mId > rhs.mId);
}

_Machine& _Machine::operator=(const _Machine& rhs) {
	this->mId = rhs.mId;
	this->mDuration = rhs.mDuration;
	this->mCapacity = rhs.mCapacity;
	this->mStart = rhs.mStart;
	this->mEnd = rhs.mEnd;
	this->mSumWaits = rhs.mSumWaits;
	this->mpWaitVector = rhs.mpWaitVector;

	return *this;
}

void _Machine::addWait(const int mId, const int mNum, const int mPriority) {
	this->mpWaitVector->append(mId, mNum, mPriority);
	this->mSumWaits += mNum;
}

// _MachineVector Implementation

_MachineVector::_MachineVector() {
	this->mCapacity = 1;
	this->mSize = 0;
	this->mSortedIndex = 0;
	if (this->mpMachine != NULL) {
		delete[] this->mpMachine;
	}
	this->mpMachine = new Machine[1];
}

Machine& _MachineVector::operator[](const int index) {
	return this->mpMachine[index];
}

void _MachineVector::append(const int mId, const int mDuration, const int mCapacity) {
	if (this->mSize == this->mCapacity) {
		this->mCapacity = this->mCapacity << 1;
		Machine* temp = new Machine[this->mCapacity];

		for (register int i = 0; i < this->mSize; ++i) {
			temp[i] = this->mpMachine[i];
		}
		delete[] this->mpMachine;
		this->mpMachine = temp;
		temp = NULL;
	}
	int index = this->mSize;
	this->mpMachine[index].mId = mId;
	this->mpMachine[index].mDuration = mDuration;
	this->mpMachine[index].mCapacity = mCapacity;
	this->mpMachine[index].mStart = 0;
	this->mpMachine[index].mEnd = 0;
	this->mpMachine[index].mSumWaits = 0;
	this->mpMachine[index].mpWaitVector = NULL;

	++this->mSize;
}

void _MachineVector::sort() {
	const int right = this->mSize - 1;
	if (this->mSortedIndex == 0) {
		this->_mergeSort(0, right);
		return;
	}

	this->_mergeSort(this->mSortedIndex, right);
	this->_merge(0, this->mSortedIndex + 1, right);
	this->mSortedIndex = right;
}

void _MachineVector::_mergeSort(const int left, const int right) {
	if (left == right) {
		return;
	}

	int mid = (left + right) >> 1;
	this->_mergeSort(left, mid);
	this->_mergeSort(mid + 1, right);
	this->_merge(left, mid, right);
}

void _MachineVector::_merge(const int left, const int mid, const int right) {
	int i = left;
	int j = mid + 1;
	int t_i = 0;

	while (i <= mid && j <= right) {
		if (this->mpMachine[i] > this->mpMachine[j]) {
			TEMP_MACHINES[t_i] = this->mpMachine[i];
			++t_i;
			++i;
		}
		else {
			TEMP_MACHINES[t_i] = this->mpMachine[j];
			++t_i;
			++j;
		}
	}

	while (i <= mid) {
		TEMP_MACHINES[t_i] = this->mpMachine[i];
		++t_i;
		++i;
	}

	while (j <= right) {
		TEMP_MACHINES[t_i] = this->mpMachine[j];
		++t_i;
		++j;
	}

	for (register int k = 0; k < t_i; ++k) {
		this->mpMachine[left + k] = TEMP_MACHINES[k];
	}
}
