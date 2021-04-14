#include <iostream>

using namespace std;

const int NOT_FOUND = -1;
const int NULL_VALUE = -1;
const int HASH_SIZE = 12;
int HASH_TABLE[HASH_SIZE] = { 0, };
int HASH_LENGTH = 0;

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

const int MEMBERS_SIZE = 7;
User MEMBERS[MEMBERS_SIZE] = { 0, };
int MEMBERS_LENGTH = 0;

void PrintHash(const int *const pHash_table, const int hash_size) {
	for (int i = 0; i < hash_size; i++) {
		if (pHash_table[i] != NULL_VALUE) {
			cout << "[" << pHash_table[i] << "]" << MEMBERS[pHash_table[i]].mName << ":" << MEMBERS[pHash_table[i]].mWeight << endl;
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

int StrLength(const char* src) {
	int length = 0;
	while (*src != '\0') {
		src++;
		length++;
	}
	return length;
}

int StrCmp(const char* src, const char* dest) {
	while (*src != '\0' && *dest != '\0') {
		if (*src != *dest) {
			break;
		}
		src++;
		dest++;
	}

	int diff = *src - *dest;

	return diff;
}

void InitHashTable(int *const pHash_table, const int hash_size) {
	for (int i = 0; i < hash_size; i++) {
		pHash_table[i] = NULL_VALUE;
	}
}

int Hash(const char* key, const int length) {
	int degree = 1;
	int index = 0;

	for (int i = length - 1; i >= 0; i--) {
		index += key[i] * degree;
		degree *= 10;
	}

	index = index % HASH_SIZE;
	return index;
}

void Insert(const char* name, const int weight) {
	if (HASH_LENGTH == HASH_SIZE) {
		return;
	}

	int current = MEMBERS_LENGTH;
	StrCpy(name, MEMBERS[current].mName);
	MEMBERS[current].mWeight = weight;
	MEMBERS_LENGTH++;

	int name_length = StrLength(name);
	int index = Hash(name, name_length);

	while (HASH_TABLE[index] != NULL_VALUE) {
		index++;
		index = index % HASH_SIZE;
	}

	HASH_TABLE[index] = current;
	HASH_LENGTH++;
}

int Search(const char* name) {
	if (HASH_LENGTH == 0) {
		return NOT_FOUND;
	}

	int found = NOT_FOUND;
	int name_length = StrLength(name);
	int index = Hash(name, name_length);
	int count = 0;

	while (HASH_TABLE[index] != NULL_VALUE && count < HASH_SIZE) {
		if (StrCmp(MEMBERS[HASH_TABLE[index]].mName, name) == 0) {
			found = HASH_TABLE[index];
			break;
		}
		index++;
		index = index % HASH_SIZE;
		count++;
	}

	return found;
}

void Remove(const char* name) {
	if (HASH_LENGTH == 0) {
		return;
	}

	int found = NOT_FOUND;
	int name_length = StrLength(name);
	int index = Hash(name, name_length);
	int count = 0;

	while (HASH_TABLE[index] != NULL_VALUE && count < HASH_SIZE) {
		if (StrCmp(MEMBERS[HASH_TABLE[index]].mName, name) == 0) {
			HASH_TABLE[index] = NULL_VALUE;
			HASH_LENGTH--;
			break;
		}
		index++;
		index = index % HASH_SIZE;
		count++;
	}
}

int main() {
	User input_data[] = {
		{"abc", 60},
		{"def", 83},
		{"ghi", 74},
		{"jkl", 103},
		{"mno", 52},
		{"pqr", 71},
		{"stu", 98},
	};
	const int input_length = sizeof(input_data) / sizeof(input_data[0]);

	InitHashTable(HASH_TABLE, HASH_SIZE);

	for (int i = 0; i < input_length; i++) {
		Insert(input_data[i].mName, input_data[i].mWeight);
	}
	PrintHash(HASH_TABLE, HASH_SIZE);

	const char name1[] = "def";
	int found = Search(name1);
	cout << "Search:" << name1 << " => Found:[" << found << "]" << MEMBERS[found].mName << ":" << MEMBERS[found].mWeight << endl;

	const char name2[] = "pqr";
	found = Search(name2);
	cout << "Search:" << name2 << " => Found:[" << found << "]" << MEMBERS[found].mName << ":" << MEMBERS[found].mWeight << endl;

	Remove(name2);
	cout << "Remove:" << name2 << endl;
	PrintHash(HASH_TABLE, HASH_SIZE);

	return 0;
}
