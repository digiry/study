#include <iostream>

using namespace std;

int HEAP[20] = { 0, };
int HEAP_SIZE = 20;
int HEAP_COUNT = 0;

void Push(int value) {
	HEAP[++HEAP_COUNT] = value;
	int child = HEAP_COUNT;
	int parent = child >> 1;
	int temp = 0;

	while (parent > 0 && HEAP[parent] > HEAP[child]) {
		temp = HEAP[parent];
		HEAP[parent] = HEAP[child];
		HEAP[child] = temp;

		child = parent;
		parent = child >> 1;
	}
}

int Pop() {
	int parent = 1;
	int result = HEAP[parent];
	int temp = 0;

	HEAP[parent] = HEAP[HEAP_COUNT];
	HEAP[HEAP_COUNT] = 0;
	HEAP_COUNT--;

	int child = parent << 1;
	if (child + 1 <= HEAP_COUNT) {
		child = (HEAP[child] > HEAP[child + 1]) ? child + 1 : child;
	}

	while (child <= HEAP_COUNT && HEAP[parent] > HEAP[child]) {
		temp = HEAP[parent];
		HEAP[parent] = HEAP[child];
		HEAP[child] = temp;

		parent = child;
		child = parent << 1;
		if (child + 1 <= HEAP_COUNT) {
			child = (HEAP[child] > HEAP[child + 1]) ? child + 1 : child;
		}
	}

	return result;
}

void PrintHeap() {
	int pow2[] = { 1, 2, 4, 8, 16, 32, 64 };
	int nextLevel = 1;

	for (int i = 1; i < HEAP_SIZE; i++) {
		if (i == pow2[nextLevel]) {
			nextLevel++;
			cout << endl;
		}
		if (HEAP[i] != 0) {
			cout << HEAP[i] << " ";
		}
	}
	cout << endl;
}

int main() {
	int inputs[] = { 20,15,19,4,13,11,23 };
	int inputs_length = sizeof(inputs) / sizeof(inputs[0]);
	int min = 0;

	for (int i = 0; i < inputs_length; i++) {
		Push(inputs[i]);
	}
	PrintHeap();

	min = Pop();
	cout << "Pop Minimum Value: " << min << endl;
	PrintHeap();

	return 0;
}