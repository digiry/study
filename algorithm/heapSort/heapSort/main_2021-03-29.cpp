#include <iostream>

using namespace std;

const int HEAP_SIZE = 20;
const int OVER_ROOT = 0;
const int ROOT_INDEX = 1;
int HEAP[HEAP_SIZE] = { OVER_ROOT, };
int HEAP_COUNTS = 0;

void PrintArray(int *const pArr, const int length) {
	for (int i = 0; i < length; i++) {
		cout << pArr[i] << ' ';
	}
	cout << endl;
}

void PrintHeap() {
	int pows2[] = { 1,2,4,8,16,32,64 };
	int nextLevel = 0;

	for (int i = 0; i < HEAP_SIZE; i++) {
		if (i == pows2[nextLevel]) {
			nextLevel++;
			cout << endl;
		}
		if (HEAP[i] > 0) {
			cout << HEAP[i] << ' ';
		}
	}
	cout << endl;
}

void Swap(int *const pHeap, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}
	pHeap[a_index] = pHeap[a_index] ^ pHeap[b_index];
	pHeap[b_index] = pHeap[a_index] ^ pHeap[b_index];
	pHeap[a_index] = pHeap[a_index] ^ pHeap[b_index];
}

void Push(const int value) {
	HEAP_COUNTS++;
	HEAP[HEAP_COUNTS] = value;
	
	int child = HEAP_COUNTS;
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
	HEAP[parent] = HEAP[HEAP_COUNTS];
	HEAP_COUNTS--;

	int child = parent << 1;
	if (child + 1 <= HEAP_COUNTS) {
		child = (HEAP[child] < HEAP[child + 1]) ? child : child + 1;
	}

	while (child <= HEAP_COUNTS) {
		if (HEAP[parent] > HEAP[child]) {
			Swap(HEAP, parent, child);
			parent = child;
			child = parent << 1;

			if (child + 1 <= HEAP_COUNTS) {
				child = (HEAP[child] < HEAP[child + 1]) ? child : child + 1;
			}
		}
	}

	return min;
}

int main() {
	int input[] = { 20,15,19,4,13,11,23 };
	const int input_length = sizeof(input) / sizeof(input[0]);

	PrintArray(input, input_length);
	for (int i = 0; i < input_length; i++) {
		Push(input[i]);
	}
	PrintHeap();

	for (int i = HEAP_COUNTS; i > 0; i--) {
		int min = Pop();
		cout << min << ' ';
	}
	cout << endl;

	return 0;
}