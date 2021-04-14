#include <iostream>

using namespace std;

const int NULL_VALUE = -1;
const int Q_SIZE = 6;
int Q_LENGTH = 0;
int QUEUE[Q_SIZE] = { 0, };
int LEFT = 0;
int RIGHT = 0;

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[9] = {
	{"abc", 60},
	{"def", 83},
	{"ghi", 74},
	{"jkl", 103},
	{"mno", 52},
	{"pqr", 98},
	{"stu", 85},
	{"vwx", 51},
	{"yz", 77},
};

void PrintQueue(int *const pQueue, const int queue_length, const int queue_left) {
	int left = queue_left;
	int length = queue_length;
	
	cout << "QUEUE: ";
	while (length > 0) {
		cout << pQueue[left] << ' ';
		left++;
		left %= Q_SIZE;
		length--;
	}
	cout << endl;
}

void PrintArray(int* const pArr, const int length) {
	cout << "ARRAY: ";
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void PrintMembersInQueue(const int* const pQueue, const User* const pMembers, const int queue_length, const int queue_left) {
	int left = queue_left;
	int length = queue_length;

	cout << "MEM_Q: ";
	while (length > 0) {
		cout << "[" << pQueue[left] << "]" << pMembers[pQueue[left]].mName << ":" << pMembers[pQueue[left]].mWeight << ' ';
		left++;
		left %= Q_SIZE;
		length--;
	}
	cout << endl;
}

void Enqueue(const int value) {
	if (Q_LENGTH == Q_SIZE) {
		return;
	}

	QUEUE[RIGHT] = value;
	RIGHT++;
	RIGHT %= Q_SIZE;
	Q_LENGTH++;
}

int Dequeue() {
	if (Q_LENGTH == 0) {
		return NULL_VALUE;
	}

	int value = QUEUE[LEFT];
	LEFT++;
	LEFT %= Q_SIZE;
	Q_LENGTH--;

	return value;
}

int main() {
	int input_data[] = { 4,5,6,7,8,9 };
	const int input_length = sizeof(input_data) / sizeof(input_data[0]);

	for (int i = 0; i < input_length; i++) {
		Enqueue(input_data[i]);
		PrintQueue(QUEUE, Q_LENGTH, LEFT);
		PrintArray(QUEUE, Q_SIZE);
	}

	int value = Dequeue();
	cout << "DeQ:" << value << endl;
	PrintQueue(QUEUE, Q_LENGTH, LEFT);
	PrintArray(QUEUE, Q_SIZE);

	value = Dequeue();
	cout << "DeQ:" << value << endl;
	PrintQueue(QUEUE, Q_LENGTH, LEFT);
	PrintArray(QUEUE, Q_SIZE);

	Enqueue(10);
	PrintQueue(QUEUE, Q_LENGTH, LEFT);
	PrintArray(QUEUE, Q_SIZE);

	Enqueue(11);
	PrintQueue(QUEUE, Q_LENGTH, LEFT);
	PrintArray(QUEUE, Q_SIZE);

	cout << "---" << endl;
	LEFT = 0;
	RIGHT = 0;
	Q_LENGTH = 0;
	for (int i = 0; i < Q_SIZE; i++) {
		QUEUE[i] = NULL_VALUE;
	}

	for (int i = 0; i < 6; i++) {
		Enqueue(i);
		PrintMembersInQueue(QUEUE, MEMBERS, Q_LENGTH, LEFT);
		PrintArray(QUEUE, Q_SIZE);
	}

	int index = Dequeue();
	cout << "DeQ: Member[" << index << "]" << MEMBERS[index].mName << ":" << MEMBERS[index].mWeight << endl;
	PrintMembersInQueue(QUEUE, MEMBERS, Q_LENGTH, LEFT);
	PrintArray(QUEUE, Q_SIZE);

	index = Dequeue();
	cout << "DeQ: Member[" << index << "]" << MEMBERS[index].mName << ":" << MEMBERS[index].mWeight << endl;
	PrintMembersInQueue(QUEUE, MEMBERS, Q_LENGTH, LEFT);
	PrintArray(QUEUE, Q_SIZE);

	Enqueue(6);
	PrintMembersInQueue(QUEUE, MEMBERS, Q_LENGTH, LEFT);
	PrintArray(QUEUE, Q_SIZE);

	Enqueue(7);
	PrintMembersInQueue(QUEUE, MEMBERS, Q_LENGTH, LEFT);
	PrintArray(QUEUE, Q_SIZE);

	return 0;
}
