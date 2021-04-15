#include <iostream>
#include <iomanip>

using namespace std;

const int NULL_VALUE = -1;
const int QUEUE_SIZE = 6;
int QUEUE_LENGTH = 0;
int QUEUE[QUEUE_SIZE] = { NULL_VALUE, };
int LEFT = 0;
int RIGHT = 0;


typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[6] = {
	{"abc", 60},
	{"def", 83},
	{"ghi", 72},
	{"jkl", 103},
	{"mno", 54},
	{"pqr", 77},
};


void PrintQueue(const int *const pQueue, const int length, const int left) {
	int count = length;
	int cursor = left;

	cout << "_QUEUE:";
	while (count > 0) {
		cout << "[" << cursor << "]" << setw(2) << pQueue[cursor] << ' ';
		--count;
		++cursor;
		cursor %= QUEUE_SIZE;
	}
	cout << endl;
}

void PrintQueue(const int* const pQueue, const User *const pMembers, const int length, const int left) {
	int count = length;
	int cursor = left;

	cout << "MEMBER:";
	while (count > 0) {
		cout << "[" << pQueue[cursor] << "]" << setw(2) << pMembers[pQueue[cursor]].mName << ":" << pMembers[pQueue[cursor]].mWeight << ' ';
		--count;
		++cursor;
		cursor %= QUEUE_SIZE;
	}
	cout << endl;
}

void PrintArray(const int *const pArr, const int length) {
	cout << "_ARRAY:";
	cout << " LEFT:" << LEFT << " / RIGHT:" << RIGHT << endl;
	for (int i = 0; i < length; ++i) {
		cout << "[" << i << "]" << setw(2) << pArr[i] << ' ';
	}
	cout << endl;
}

void Enqueue(const int value) {
	cout << "EN_Q  :" << value << endl;
	if (QUEUE_LENGTH == QUEUE_SIZE) {
		return;
	}

	QUEUE[RIGHT] = value;
	++RIGHT;
	RIGHT %= QUEUE_SIZE;

	QUEUE_LENGTH++;
}

int Dequeue() {
	cout << "DE_Q  :" << endl;
	if (QUEUE_LENGTH == 0) {
		return NULL_VALUE;
	}

	int value = QUEUE[LEFT];
	++LEFT;
	LEFT %= QUEUE_SIZE;
	
	QUEUE_LENGTH--;

	return value;
}

int main() {
	int input_data[6] = { 10,11,12,13,14,15 };

	for (int i = 0; i < 6; ++i) {
		Enqueue(input_data[i]);
		PrintQueue(QUEUE, QUEUE_LENGTH, LEFT);
		PrintArray(QUEUE, QUEUE_SIZE);
		cout << endl;
	}

	int value = Dequeue();
	cout << "RETURN:" << value << endl;
	PrintQueue(QUEUE, QUEUE_LENGTH, LEFT);
	PrintArray(QUEUE, QUEUE_SIZE);
	cout << endl;

	Enqueue(16);
	PrintQueue(QUEUE, QUEUE_LENGTH, LEFT);
	PrintArray(QUEUE, QUEUE_SIZE);
	cout << endl;

	cout << "----" << endl;
	QUEUE_LENGTH = 0;
	LEFT = 0;
	RIGHT = 0;
	for (int i = 0; i < 6; i++) {
		Enqueue(i);
		PrintQueue(QUEUE, MEMBERS, QUEUE_LENGTH, LEFT);
	}

	int index = Dequeue();
	cout << "RET_MR:[" << index << "]" << MEMBERS[index].mName << ":" << MEMBERS[index].mWeight << endl;
	PrintQueue(QUEUE, MEMBERS, QUEUE_LENGTH, LEFT);

	return 0;
}
