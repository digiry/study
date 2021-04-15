#include <iostream>

using namespace std;

const int NULL_VALUE = -1;

const int LLIST_SIZE = 8;
int LLIST_LENGTH = 0;
int HEAD = 0;
int LAST = -1;

typedef struct _Node {
	int mData;
	int mNext;
} Node;

Node LLIST[LLIST_SIZE] = { 0, };

const int OVER_STACK = -1;
const int STACK_SIZE = LLIST_SIZE;
int STACK_LENGTH = 0;
int STACK[STACK_SIZE] = { 0, };
int TOP = OVER_STACK;

int GetTail() {
	if (STACK_LENGTH == 0) {
		return OVER_STACK;
	}

	int index = STACK[TOP];
	--TOP;
	--STACK_LENGTH;

	return index;
}

void AddNodeToTails(const int index) {
	if (STACK_LENGTH == STACK_SIZE) {
		return;
	}

	++TOP;
	STACK[TOP] = index;
	++STACK_LENGTH;
}

void PrintLList(Node *const pLList, const int ll_length, const int head) {
	int cursor = head;
	int count = ll_length;

	cout << "LLIST :";
	while (count > 0) {
		cout << "[" << cursor << "]" << pLList[cursor].mData << ' ';
		cursor = pLList[cursor].mNext;
		count--;
	}
	cout << endl;
}

void PrintArray(Node* const pLList, const int length) {
	cout << "ARRAY :" << endl;
	cout << " HEAD :" << HEAD << endl;
	cout << " LAST :" << LAST << endl;
	for (int i = 0; i < length; i++) {
		cout << i << "- DATA:" << pLList[i].mData << " NEXT:" << pLList[i].mNext << endl;
	}
}

void Append(const int value) {
	if (LLIST_LENGTH == LLIST_SIZE) {
		return;
	}
	cout << "APPEND:" << value << endl;

	int tail = GetTail();
	LLIST[tail].mData = value;

	if (LAST != NULL_VALUE) {
		LLIST[LAST].mNext = tail;
	}
	LLIST_LENGTH++;
	LAST = tail;
}

void Remove(const int index) {
	if (LLIST_LENGTH == 0 || index >= LLIST_LENGTH || index < 0) {
		return;
	}

	cout << "REMOVE:" << index << endl;
	int count = index;
	int cursor = HEAD;
	int prev = NULL_VALUE;

	while (count > 0) {
		prev = cursor;
		cursor = LLIST[cursor].mNext;
		count--;
	}

	LLIST[prev].mNext = LLIST[cursor].mNext;
	LLIST[cursor].mNext = NULL_VALUE;
	LLIST_LENGTH--;

	if (LAST == cursor) {
		LAST = prev;
	}

	AddNodeToTails(cursor);
}

void Insert(const int index, const int value) {
	if (LLIST_LENGTH == LLIST_SIZE || index >= LLIST_LENGTH || index < 0) {
		return;
	}

	cout << "INSERT:" << index << ": v=" << value << endl;
	int count = index - 1;
	int cursor = HEAD;

	while (count > 0) {
		cursor = LLIST[cursor].mNext;
		count--;
	}

	int tail = GetTail();
	LLIST[tail].mData = value;
	LLIST[tail].mNext = LLIST[cursor].mNext;
	LLIST[cursor].mNext = tail;

	LLIST_LENGTH++;
	if (LAST == cursor) {
		LAST = tail;
	}
}

int Search(const int value) {
	if (LLIST_LENGTH == 0) {
		return NULL_VALUE;
	}

	cout << "SEARCH:" << value << endl;
	int cursor = HEAD;

	while (cursor != NULL_VALUE) {
		if (LLIST[cursor].mData == value) {
			break;
		}
		cursor = LLIST[cursor].mNext;
	}

	return cursor;
}

int main() {
	int input_data[8] = { 4,5,6,7,8,9,10,11 };

	// initialize
	for (int i = LLIST_SIZE - 1; i >= 0; i--) {
		AddNodeToTails(i);
		LLIST[i].mNext = -1;
	}

	for (int i = 0; i < 5; i++) {
		Append(input_data[i]);
		PrintLList(LLIST, LLIST_LENGTH, HEAD);
	}

	Remove(7);
	PrintLList(LLIST, LLIST_LENGTH, HEAD);

	Remove(0);
	PrintLList(LLIST, LLIST_LENGTH, HEAD);

	Remove(0);
	PrintLList(LLIST, LLIST_LENGTH, HEAD);

	Append(12);
	PrintLList(LLIST, LLIST_LENGTH, HEAD);

	Insert(3, 14);
	PrintLList(LLIST, LLIST_LENGTH, HEAD);

	Insert(3, 15);
	PrintLList(LLIST, LLIST_LENGTH, HEAD);

	int value = 15;
	int index = Search(value);
	PrintLList(LLIST, LLIST_LENGTH, HEAD);
	cout << "Found:" << "[" << index << "]" << ":" << LLIST[index].mData << endl;
	PrintArray(LLIST, LLIST_SIZE);

	return 0;
}
