#include <iostream>

using namespace std;

const int OVER_ROOT = 0;
const int ROOT_NODE = 1;
const int HEAP_SIZE = 20;
int HEAP[HEAP_SIZE] = { OVER_ROOT, };
int HEAP_COUNT = 0;

void PrintHeap() {
	for (int i = 1; i <= HEAP_COUNT; i++) {
		cout << HEAP[i] << ' ';
	}
	cout << endl;
}

void PrintHeapTree() {
	int pow2[] = { 1,2,4,8,16,32,64 };
	int nextlevel = 0;

	for (int i = 0; i < HEAP_SIZE; i++) {
		if (i == pow2[nextlevel]) {
			nextlevel++;
			cout << endl;
		}
		if (HEAP[i] > 0) {
			cout << HEAP[i] << ' ';
		}
	}
	cout << endl;
}

void Swap(int* const pHeap, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	pHeap[a_index] = pHeap[a_index] ^ pHeap[b_index];
	pHeap[b_index] = pHeap[a_index] ^ pHeap[b_index];
	pHeap[a_index] = pHeap[a_index] ^ pHeap[b_index];
}

void Push(const int value) {
	HEAP_COUNT++;
	HEAP[HEAP_COUNT] = value;

	int child = HEAP_COUNT;
	int parent = child >> 1;

	while (parent > OVER_ROOT && HEAP[parent] > HEAP[child]) {
		Swap(HEAP, parent, child);
		child = parent;
		parent = child >> 1;
	}
}

int Pop() {
	int minimum = HEAP[ROOT_NODE];
	int parent = ROOT_NODE;
	HEAP[parent] = HEAP[HEAP_COUNT];
	HEAP_COUNT--;

	int child = parent << 1;
	if (child + 1 <= HEAP_COUNT) {
		child = (HEAP[child] > HEAP[child + 1]) ? child + 1 : child;
	}

	while (child <= HEAP_COUNT) {
		if (HEAP[parent] > HEAP[child]) {
			Swap(HEAP, parent, child);

			parent = child;
			child = parent << 1;

			if (child + 1 <= HEAP_COUNT) {
				child = (HEAP[child] > HEAP[child + 1]) ? child + 1 : child;
			}
		}
	}

	return minimum;
}

int main() {
	int input[] = { 20,15,19,4,13,11,23 };
	int input_length = sizeof(input) / sizeof(input[0]);

	for (int i = 0; i < input_length; i++) {
		Push(input[i]);
	}
	PrintHeap();
	PrintHeapTree();

	for (int i = 0; i < input_length; i++) {
		int min = Pop();
		cout << min << ' ';
	}
	cout << endl;

	return 0;
}
