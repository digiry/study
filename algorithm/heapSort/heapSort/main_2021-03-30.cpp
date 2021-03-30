#include <iostream>

using namespace std;

const int HEAP_SIZE = 20;
const int OVER_ROOT = 0;
const int ROOT_INDEX = 1;
int HEAP[HEAP_SIZE] = { 0, };
int HEAP_COUNT = 0;

void Swap(int *const pArr, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
	pArr[b_index] = pArr[a_index] ^ pArr[b_index];
	pArr[a_index] = pArr[a_index] ^ pArr[b_index];
}

void Push(const int value) {
	HEAP_COUNT++;
	HEAP[HEAP_COUNT] = value;
	int child = HEAP_COUNT;
	int parent = child >> 1;

	while (parent > 0 && HEAP[parent] > HEAP[child]) {
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
		child = (HEAP[child] < HEAP[child + 1]) ? child : child + 1;
	}

	while (child <= HEAP_COUNT) {
		if (HEAP[parent] > HEAP[child]) {
			Swap(HEAP, parent, child);
			parent = child;
			child = parent << 1;
			if (child + 1 <= HEAP_COUNT) {
				child = (HEAP[child] < HEAP[child + 1]) ? child : child + 1;
			}
		}
	}

	return min;
}

int main() {
	int input[] = { 20,15,19,4,13,11,23 };
	const int input_length = sizeof(input) / sizeof(input[0]);

	for (int i = 0; i < input_length; i++) {
		Push(input[i]);
	}

	for (int i = HEAP_COUNT; i > 0; i--) {
		int min = Pop();
		cout << min << ' ';
	}
	cout << endl;

	return 0;
}