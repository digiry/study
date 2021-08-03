#include <iostream>

using namespace std;

const int TOP_HEAP = 0;
const int HEAP_SIZE = 20;
int HEAP_COUNT = 0;

int HEAP[HEAP_SIZE] = { 0, };

void Swap(int* const pHeap, const int a_index, const int b_index);
void Push(const int value);
int Pop();

void PrintHeap(const int* const pHeap);

int main() {
	const int inputs[] = { 20,15,19,4,13,11,23 };
	const int inputs_length = sizeof(inputs) / sizeof(inputs[0]);

	for (int i = 0; i < inputs_length; ++i) {
		Push(inputs[i]);
		PrintHeap(HEAP);
	}

	int value = 0;

	value = Pop();
	cout << "pop: value=" << value << endl;
	PrintHeap(HEAP);
	value = Pop();
	cout << "pop: value=" << value << endl;
	PrintHeap(HEAP);

	return 0;
}

void PrintHeap(const int* const pHeap) {
	const int pows2[] = { 1,2,4,8,16,32 };
	int nextLevel = 0;

	for (int i = 1; i <= HEAP_COUNT; ++i) {
		if (i == pows2[nextLevel]) {
			cout << endl;
			++nextLevel;
		}
		cout << HEAP[i] << ' ';
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
	++HEAP_COUNT;
	HEAP[HEAP_COUNT] = value;
	int child = HEAP_COUNT;
	int parent = child >> 1;

	while (parent > TOP_HEAP && HEAP[parent] > HEAP[child]) {
		Swap(HEAP, parent, child);
		child = parent;
		parent = child >> 1;
	}
}

int Pop() {
	int parent = 1;
	int value = HEAP[parent];
	HEAP[parent] = HEAP[HEAP_COUNT];
	--HEAP_COUNT;
	int child = parent << 1;

	if (child + 1 <= HEAP_COUNT) {
		child = (HEAP[child] < HEAP[child + 1]) ? child : child + 1;
	}

	while (child <= HEAP_COUNT && HEAP[parent] > HEAP[child]) {
		Swap(HEAP, parent, child);
		parent = child;
		child = child << 1;

		if (child + 1 <= HEAP_COUNT) {
			child = (HEAP[child] < HEAP[child + 1]) ? child : child + 1;
		}
	}

	return value;
}
