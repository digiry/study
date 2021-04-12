#include <iostream>

using namespace std;

const int NOT_FOUND = -1;
const int LENGTH = 9;
int ARR[LENGTH] = { 1,2,3,4,5,11,12,13,14 };


typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[LENGTH] = {
	{"abc", 60},	// 0
	{"def", 98},	// 1
	{"ghi", 72},	// 2
	{"jkl", 53},	// 3
	{"mno", 103},	// 4
	{"pqr", 82},	// 5
	{"stu", 54},	// 6
	{"vwx", 25},	// 7
	{"yz",  18},	// 8
};

int ARR4MEMBER[LENGTH] = { 8,7,3,6,0,2,5,1,4 };

User MEMBERS4BOUND[LENGTH] = {
	{"abc", 60},	// 0
	{"def", 98},	// 1
	{"ghi", 72},	// 2
	{"jkl", 53},	// 3
	{"mno", 103},	// 4
	{"pqr", 72},	// 5
	{"stu", 72},	// 6
	{"vwx", 25},	// 7
	{"yz",  18},	// 8
};

int ARR4BOUND[LENGTH] = { 8,7,3,0,2,5,6,1,4 };

void PrintArray(int *const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void PrintUsers(const int *const pArr, const User *const pMembers, const int length) {
	for (int i = 0; i < length; i++) {
		cout << " [" << pArr[i] << "] " << pMembers[pArr[i]].mName << " :" << pMembers[pArr[i]].mWeight << endl;
	}
}

int BinarySearch(int *const pArr, const int low, const int high, const int key) {
	int l = low;
	int h = high;
	int found = NOT_FOUND;

	while (l <= h) {
		int m = (l + h) >> 1;
		if (pArr[m] == key) {
			found = m;
			break;
		}
		else if (pArr[m] < key) {
			l = m + 1;
		}
		else {
			h = m - 1;
		}
	}

	return found;
}

int BinarySearchInMembers(int *const pArr, const User *const pMembers, const int low, const int high, const int key) {
	int l = low;
	int h = high;
	int found = NOT_FOUND;

	while (l <= h) {
		int m = (l + h) >> 1;
		if (pMembers[pArr[m]].mWeight == key) {
			found = m;
			break;
		}
		else if (pMembers[pArr[m]].mWeight < key) {
			l = m + 1;
		}
		else {
			h = m - 1;
		}
	}

	return found;
}

int BinarySearchUpperBound(int *const pArr, const User *const pMembers, const int low, const int high, const int key) {
	int l = low;
	int h = high;
	int found = NOT_FOUND;

	while (l < h) {
		int m = (l + h) >> 1;

		if (pMembers[pArr[m]].mWeight <= key) {
			l = m + 1;
		}
		else {
			h = m;
		}
	}

	if (pMembers[pArr[l - 1]].mWeight == key) {
		found = l;
	}

	return found;
}

int BinarySearchLowerBound(int *const pArr, const User *const pMembers, const int low, const int high, const int key) {
	int l = low;
	int h = high;
	int found = NOT_FOUND;

	while (l < h) {
		int m = (l + h) >> 1;

		if (pMembers[pArr[m]].mWeight >= key) {
			h = m;
		}
		else {
			l = m + 1;
		}
	}

	if (pMembers[pArr[l]].mWeight == key) {
		found = l;
	}

	return found;
}

int main() {
	const int low = 0;
	const int high = LENGTH - 1;
	PrintArray(ARR, LENGTH);
	int found = NOT_FOUND;

	int key = 12;
	found = BinarySearch(ARR, low, high, key);
	cout << "Key:" << key << ((found != NOT_FOUND) ? " FOUND=" : " NOT_FOUND=") << found << endl;

	key = 9;
	found = BinarySearch(ARR, low, high, key);
	cout << "Key:" << key << ((found != NOT_FOUND) ? " FOUND=" : " NOT_FOUND=") << found << endl;

	cout << endl;
	cout << "BinarySearch in Members" << endl;

	PrintUsers(ARR4MEMBER, MEMBERS, LENGTH);

	key = 54;
	found = BinarySearchInMembers(ARR4MEMBER, MEMBERS, low, high, key);
	if (found != NOT_FOUND) {
		cout << "Key:" << key << ((found != NOT_FOUND) ? " FOUND=" : " NOT_FOUND=") << MEMBERS[ARR4MEMBER[found]].mWeight << " [" << ARR4MEMBER[found] << "] " << MEMBERS[ARR4MEMBER[found]].mName << endl;
	}
	else {
		cout << "Key:" << key << " NOT_FOUND" << endl;
	}

	key = 9;
	found = BinarySearchInMembers(ARR4MEMBER, MEMBERS, low, high, key);
	if (found != NOT_FOUND) {
		cout << "Key:" << key << ((found != NOT_FOUND) ? " FOUND=" : " NOT_FOUND=") << MEMBERS[ARR4MEMBER[found]].mWeight << " [" << ARR4MEMBER[found] << "] " << MEMBERS[ARR4MEMBER[found]].mName << endl;
	}
	else {
		cout << "Key:" << key << " NOT_FOUND" << endl;
	}

	cout << endl;
	cout << "BinarySearch UpperBound and LowerBound" << endl;

	PrintUsers(ARR4BOUND, MEMBERS4BOUND, LENGTH);

	key = 72;
	found = BinarySearchUpperBound(ARR4BOUND, MEMBERS4BOUND, low, high, key);
	if (found != NOT_FOUND) {
		cout << "Key:" << key << ((found != NOT_FOUND) ? " FOUND=" : " NOT_FOUND=") << MEMBERS4BOUND[ARR4BOUND[found]].mWeight << " [" << ARR4BOUND[found] << "] " << MEMBERS4BOUND[ARR4BOUND[found]].mName << endl;
	}
	else {
		cout << "Key:" << key << " NOT_FOUND" << endl;
	}

	key = 80;
	found = BinarySearchUpperBound(ARR4BOUND, MEMBERS4BOUND, low, high, key);
	if (found != NOT_FOUND) {
		cout << "Key:" << key << ((found != NOT_FOUND) ? " FOUND=" : " NOT_FOUND=") << MEMBERS4BOUND[ARR4BOUND[found]].mWeight << " [" << ARR4BOUND[found] << "] " << MEMBERS4BOUND[ARR4BOUND[found]].mName << endl;
	}
	else {
		cout << "Key:" << key << " NOT_FOUND" << endl;
	}

	key = 72;
	found = BinarySearchLowerBound(ARR4BOUND, MEMBERS4BOUND, low, high, key);
	if (found != NOT_FOUND) {
		cout << "Key:" << key << ((found != NOT_FOUND) ? " FOUND=" : " NOT_FOUND=") << MEMBERS4BOUND[ARR4BOUND[found]].mWeight << " [" << ARR4BOUND[found] << "] " << MEMBERS4BOUND[ARR4BOUND[found]].mName << endl;
	}
	else {
		cout << "Key:" << key << " NOT_FOUND" << endl;
	}

	key = 80;
	found = BinarySearchLowerBound(ARR4BOUND, MEMBERS4BOUND, low, high, key);
	if (found != NOT_FOUND) {
		cout << "Key:" << key << ((found != NOT_FOUND) ? " FOUND=" : " NOT_FOUND=") << MEMBERS4BOUND[ARR4BOUND[found]].mWeight << " [" << ARR4BOUND[found] << "] " << MEMBERS4BOUND[ARR4BOUND[found]].mName << endl;
	}
	else {
		cout << "Key:" << key << " NOT_FOUND" << endl;
	}

	return 0;
}