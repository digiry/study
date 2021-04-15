#include <iostream>
#include <iomanip>

using namespace std;

const int NULL_VALUE = -1;
const int HT_SIZE = 12;
int HT_LENGTH = 0;
int HASH_TABLE[HT_SIZE] = { 0, };

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

const int MEMBERS_SIZE = HT_SIZE;
User MEMBERS[MEMBERS_SIZE] = { 0, };
int NEW_MEMBER_INDEX = 0;


void PrintHashTable(const int *const pHash, const int size) {
	cout << " HASH:" << endl;
	for (int i = 0; i < size; ++i) {
		if (pHash[i] != NULL_VALUE) {
			cout << setw(2) << i << " - " << "[" << setw(2) << pHash[i] << "]" << MEMBERS[pHash[i]].mName << ":" << MEMBERS[pHash[i]].mWeight << endl;
		}
		else {
			cout << setw(2) << i << " - " << "[" << setw(2) << pHash[i] << "]" << endl;
		}
	}
}

void StrCpy(const char* src, char* dest) {
	while (*src != '\0') {
		*dest = *src;
		src++;
		dest++;
	}

	*dest = '\0';
}

int StrCmp(const char* src1, const char* src2) {
	while (*src1 == *src2 && *src1 != '\0') {
		src1++;
		src2++;
	}

	int diff = *src1 - *src2;

	return diff;
}

int StrLength(const char* src) {
	int count = 0;

	while (*src != '\0') {
		count++;
		src++;
	}

	return count;
}

int Hash(const char* src, const int length) {
	int degree = 1;
	int index = 0;

	for (int i = length - 1; i >= 0; --i) {
		index += (src[i] * degree);
		degree *= 10;
	}
	index %= HT_SIZE;

	return index;
}

void Add(const char* name, const int weight) {
	cout << " ADD:" << name << ":" << weight << endl;
	if (HT_LENGTH == HT_SIZE) {
		return;
	}

	int name_length = StrLength(name);
	int index = Hash(name, name_length);

	while (HASH_TABLE[index] != NULL_VALUE) {
		index++;
		index %= HT_SIZE;
	}

	StrCpy(name, MEMBERS[NEW_MEMBER_INDEX].mName);
	MEMBERS[NEW_MEMBER_INDEX].mWeight = weight;
	HASH_TABLE[index] = NEW_MEMBER_INDEX;

	NEW_MEMBER_INDEX++;
	HT_LENGTH++;
}

void Remove(const char* name) {
	cout << " REM:" << name << endl;
	if (HT_LENGTH == 0) {
		return;
	}

	int name_length = StrLength(name);
	int index = Hash(name, name_length);
	int count = HT_LENGTH;

	while (HASH_TABLE[index] != NULL_VALUE && count > 0) {
		if (StrCmp(name, MEMBERS[HASH_TABLE[index]].mName) == 0) {
			HASH_TABLE[index] = NULL_VALUE;
			HT_LENGTH--;
			break;
		}
		index++;
		index %= HT_SIZE;
		count--;
	}
}

int Search(const char* name) {
	cout << "SRCH:" << name << endl;
	if (HT_LENGTH == 0) {
		return NULL_VALUE;
	}

	int found = NULL_VALUE;
	int name_length = StrLength(name);
	int index = Hash(name, name_length);
	int count = HT_LENGTH;

	while (HASH_TABLE[index] != NULL_VALUE && count > 0) {
		if (StrCmp(name, MEMBERS[HASH_TABLE[index]].mName) == 0) {
			found = HASH_TABLE[index];
			break;
		}

		index++;
		index %= HT_SIZE;
		count--;
	}

	return found;
}

int main() {
	User input_data[7] = {
		{"abc", 60},
		{"def", 83},
		{"ghi", 72},
		{"jkl", 103},
		{"mno", 54},
		{"pqr", 77},
		{"stu", 98},
	};

	for (int i = 0; i < HT_SIZE; ++i) {
		HASH_TABLE[i] = NULL_VALUE;
	}

	for (int i = 0; i < 7; ++i) {
		Add(input_data[i].mName, input_data[i].mWeight);
		PrintHashTable(HASH_TABLE, HT_SIZE);
	}

	Remove("mno");
	PrintHashTable(HASH_TABLE, HT_SIZE);

	int index = Search("stu");
	cout << "FOUND:[" << index << "]" << MEMBERS[index].mName << ":" << MEMBERS[index].mWeight << endl;
	PrintHashTable(HASH_TABLE, HT_SIZE);

	return 0;
}
