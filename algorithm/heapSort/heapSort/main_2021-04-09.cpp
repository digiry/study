#include <iostream>

using namespace std;

const int HEAP_SIZE = 20;
const int OVER_ROOT = 0;
const int ROOT_INDEX = 1;
int HEAP_COUNT = 0;
int HEAP[HEAP_SIZE] = { OVER_ROOT, };

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

const int LENGTH = 7;
User MEMBERS[LENGTH] = {
	{"abc", 20},
	{"def", 15},
	{"ghi", 19},
	{"jkl", 4},
	{"mno", 13},
	{"pqr", 11},
	{"stu", 23},
};

void PrintHeap() {
	int pows2[] = { 1,2,4,8,16,32,64 };
	int nextLevel = 0;

	for (int i = 1; i <= HEAP_COUNT; i++) {
		if (i == pows2[nextLevel]) {
			nextLevel++;
			cout << endl;
		}

		if (HEAP[i] > 0) {
			cout << "[" << HEAP[i] << "] " << MEMBERS[HEAP[i]].mName << ": " << MEMBERS[HEAP[i]].mWeight << ' ';
		}
	}
	cout << endl;
}

void Swap(int *const pArr, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
	pArr[b_index] = pArr[a_index] ^ pArr[b_index];
	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
}

void Push(const int id) {
	HEAP_COUNT++;
	HEAP[HEAP_COUNT] = id;
	int child = HEAP_COUNT;
	int parent = child >> 1;

	while (parent > 0 && MEMBERS[HEAP[parent]].mWeight > MEMBERS[HEAP[child]].mWeight) {
		Swap(HEAP, parent, child);

		child = parent;
		parent = child >> 1;
	}
}

int Pop() {
	int parent = ROOT_INDEX;
	int min = HEAP[parent];
	HEAP[parent] = HEAP[HEAP_COUNT];
	HEAP_COUNT--;

	int child = parent << 1;
	if (child + 1 <= HEAP_COUNT) {
		child = (MEMBERS[HEAP[child]].mWeight < MEMBERS[HEAP[child + 1]].mWeight) ? child : child + 1;
	}

	while (child <= HEAP_COUNT) {
		if (MEMBERS[HEAP[parent]].mWeight > MEMBERS[HEAP[child]].mWeight) {
			Swap(HEAP, parent, child);
			parent = child;
			child = parent << 1;
			if (child + 1 <= HEAP_COUNT) {
				child = (MEMBERS[HEAP[child]].mWeight < MEMBERS[HEAP[child + 1]].mWeight) ? child : child + 1;
			}
		}
	}

	return min;
}

int main() {
	for (int i = 0; i < LENGTH; i++) {
		Push(i);
	}
	PrintHeap();

	cout << "---" << endl;

	for (int i = HEAP_COUNT; i > 0; i--) {
		int min = Pop();
		cout << "[" << HEAP[min] << "] " << MEMBERS[min].mName << ": " << MEMBERS[min].mWeight << ' ';
	}

	return 0;
}
