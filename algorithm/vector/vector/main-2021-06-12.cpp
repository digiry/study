#include <iostream>
#include <string>

using namespace std;

const int NULL_VALUE = -1;
int TEMP[1000] = { 0, };

typedef struct _User {
	char mName[10];
	int mWeight;
	
	void set_user(char name[10], const int weight);
	bool operator<(const struct _User& other);
	struct _User& operator=(const struct _User& other);
} User;

const int MEMBERS_LENGTH = 9;
User MEMBERS[MEMBERS_LENGTH] = {
	{"abc", 20},
	{"def", 15},
	{"ghi", 19},
	{"jkl", 4},
	{"mno", 13},
	{"pqr", 11},
	{"stu", 23},
	{"vwx", 17},
	{"yz", 10},
};

User TEMP_USERS[MEMBERS_LENGTH] = { 0, };

typedef struct _Vector {
	int* mBuffer;
	int mSize;
	int mLength;
	int mLastSort;

	_Vector();
	~_Vector();
	int length() {
		return this->mLength;
	}
	int size() {
		return this->mSize;
	}
	void push_back(const int value);
	int& operator[](const int index);
	void sort();
	void _merge_sort(const int l, const int r);
	void _merge(const int l, const int m, const int r);
} Vector;

typedef struct _VectorUser {
	User* mBuffer;
	int mSize;
	int mLength;
	int mLastSort;

	_VectorUser();
	~_VectorUser();
	int length() {
		return this->mLength;
	}
	int size() {
		return this->mSize;
	}
	void push_back(const User& value);
	User& operator[](const int index);
	void sort();
	void _merge_sort(const int l, const int r);
	void _merge(const int l, const int m, const int r);
} VectorUser;


void printVector(Vector& v) {
	for (int i = 0; i < v.length(); ++i) {
		cout << v[i] << ' ';
	}
	cout << endl;
}

void printVectorUser(VectorUser& vu) {
	for (int i = 0; i < vu.length(); ++i) {
		cout << "name:" << vu[i].mName << " weight:" << vu[i].mWeight << endl;
	}
	cout << endl;
}

int main() {
	int input_data[] = { 20,15,19,4,13,11,23,17,10 };
	const int input_length = sizeof(input_data) / sizeof(input_data[0]);

	Vector v1;
	for (int i = 0; i < input_length; ++i) {
		v1.push_back(input_data[i]);
		printVector(v1);
	}
	
	v1.sort();
	printVector(v1);

	v1.push_back(32);
	v1.push_back(2);
	v1.push_back(18);
	v1.push_back(25);
	printVector(v1);
	v1.sort();
	printVector(v1);

	VectorUser vu1;
	for (int i = 0; i < 5; ++i) {
		vu1.push_back(MEMBERS[i]);
		printVectorUser(vu1);
	}
	vu1.sort();
	printVectorUser(vu1);
	for (int i = 5; i < MEMBERS_LENGTH; ++i) {
		vu1.push_back(MEMBERS[i]);
		printVectorUser(vu1);
	}
	vu1.sort();
	printVectorUser(vu1);

	return 0;
}

void _User::set_user(char name[10], const int weight) {
	strcpy_s(this->mName, name);
	this->mWeight = weight;
}

bool _User::operator<(const struct _User& other) {
	if (this->mWeight - other.mWeight) {
		return this->mWeight < other.mWeight;
	}

	if (strcmp(this->mName, other.mName) <= 0) {
		return true;
	}

	return false;
}

struct _User& _User::operator=(const struct _User& other) {
	strcpy_s(this->mName, other.mName);
	this->mWeight = other.mWeight;

	return *this;
}

_Vector::_Vector() {
	this->mSize = 1;
	this->mLength = 0;
	this->mBuffer = new int[this->mSize];
	this->mLastSort = 0;
}

_Vector::~_Vector() {
	if (this->mBuffer != NULL) {
		delete[] this->mBuffer;
	}

	this->mSize = 0;
	this->mLength = 0;
	this->mLastSort = 0;
}

void _Vector::push_back(const int value) {
	int* temp = NULL;
	if (this->mLength == this->mSize) {
		this->mSize <<= 1;
		temp = new int[this->mSize];

		for (register int i = 0; i < this->mLength; ++i) {
			temp[i] = this->mBuffer[i];
		}

		delete[] this->mBuffer;
		this->mBuffer = temp;
	}

	this->mBuffer[this->mLength] = value;
	this->mLength++;
}

int& _Vector::operator[](const int index) {
	if (index < 0 && index >= this->mLastSort) {
		exit(0);
	}
	return this->mBuffer[index];
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
	
	this->mLastSort = r;
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
		if (this->mBuffer[i] <= this->mBuffer[j]) {
			TEMP[t_i++] = this->mBuffer[i++];
		}
		else {
			TEMP[t_i++] = this->mBuffer[j++];
		}
	}

	while (i <= m) {
		TEMP[t_i++] = this->mBuffer[i++];
	}
	while (j <= r) {
		TEMP[t_i++] = this->mBuffer[j++];
	}

	for (register int k = 0; k < t_i; ++k) {
		this->mBuffer[l + k] = TEMP[k];
	}
}

_VectorUser::_VectorUser() {
	this->mSize = 1;
	this->mLength = 0;
	this->mBuffer = new User[this->mSize];
	this->mLastSort = 0;
}
_VectorUser::~_VectorUser() {
	if (this->mBuffer != NULL) {
		delete[] this->mBuffer;
	}

	this->mSize = 0;
	this->mLength = 0;
	this->mLastSort = 0;
}
void _VectorUser::push_back(const User& value) {
	User* temp = NULL;
	if (this->mLength == this->mSize) {
		this->mSize <<= 1;
		temp = new User[this->mSize];

		for (register int i = 0; i < this->mLength; ++i) {
			temp[i] = this->mBuffer[i];
		}

		delete[] this->mBuffer;
		this->mBuffer = temp;
	}

	this->mBuffer[this->mLength] = value;
	this->mLength++;
}
User& _VectorUser::operator[](const int index) {
	if (index < 0 && index >= this->mLastSort) {
		exit(0);
	}
	return this->mBuffer[index];
}
void _VectorUser::sort() {
	const int r = this->mLength - 1;

	if (this->mLastSort > 0) {
		this->_merge_sort(this->mLastSort, r);
		this->_merge(0, this->mLastSort - 1, r);
	}
	else {
		this->_merge_sort(0, r);
	}

	this->mLastSort = r;
}
void _VectorUser::_merge_sort(const int l, const int r) {
	if (l == r) {
		return;
	}

	int m = (l + r) >> 1;
	this->_merge_sort(l, m);
	this->_merge_sort(m + 1, r);

	this->_merge(l, m, r);
}
void _VectorUser::_merge(const int l, const int m, const int r) {
	int i = l;
	int j = m + 1;
	int t_i = 0;

	while (i <= m && j <= r) {
		if (this->mBuffer[i] < this->mBuffer[j]) {
			TEMP_USERS[t_i++] = this->mBuffer[i++];
		}
		else {
			TEMP_USERS[t_i++] = this->mBuffer[j++];
		}
	}

	while (i <= m) {
		TEMP_USERS[t_i++] = this->mBuffer[i++];
	}
	while (j <= r) {
		TEMP_USERS[t_i++] = this->mBuffer[j++];
	}

	for (register int k = 0; k < t_i; ++k) {
		this->mBuffer[l + k] = TEMP_USERS[k];
	}
}