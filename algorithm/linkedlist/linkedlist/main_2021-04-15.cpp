#include <iostream>

using namespace std;

const int NULL_VALUE = -1;
const int LLIST_SIZE = 8;
int LLIST_LENGTH = 0;
int HEAD = 0;
int LAST = NULL_VALUE;

typedef struct _Node {
	int mData;
	int mNext;
} Node;

Node LLIST[LLIST_SIZE] = { 0, };

const int OVER_STACK = -1;
const int STACK_SIZE = LLIST_SIZE;
int STACK_LENGTH = 0;
int TOP = OVER_STACK;
int STACK[STACK_SIZE] = { 0, };

int GetNewNode() {
	if (STACK_LENGTH == 0) {
		return NULL_VALUE;
	}

	int index = STACK[TOP];
	--TOP;
	--STACK_LENGTH;

	return index;
}

void AddToNewNodes(const int index) {
	if (STACK_LENGTH == STACK_SIZE) {
		return;
	}

	++TOP;
	STACK[TOP] = index;
	++STACK_LENGTH;
}

void PrintLList(const Node *const pList, const int head) {
	int cursor = head;

	cout << "LLIST :";
	while (cursor != NULL_VALUE) {
		cout << "[" << cursor << "]:" << pList[cursor].mData << ' ';
		cursor = pList[cursor].mNext;
	}
	cout << endl;
}

void PrintArray(const Node* const pList, const int size) {
	cout << "ARRAY :" << endl;
	cout << " HEAD :" << HEAD << " LAST :" << LAST << endl;
	for (int i = 0; i < size; ++i) {
		cout << i << " - DATA:" << pList[i].mData << " NEXT:" << pList[i].mNext << endl;
	}
}

void InitLinkedList(const int llist_size) {
	TOP = OVER_STACK;
	STACK_LENGTH = 0;
	LLIST_LENGTH = 0;

	for (int i = llist_size - 1; i >= 0; --i) {
		AddToNewNodes(i);
		LLIST[i].mNext = NULL_VALUE;
	}
}

void Append(const int value) {
	cout << "APPEND:" << value << endl;
	if (LLIST_LENGTH == LLIST_SIZE) {
		return;
	}

	int tail = GetNewNode();
	LLIST[tail].mData = value;

	if (LAST != NULL_VALUE) {
		LLIST[LAST].mNext = tail;
	}
	LAST = tail;
	++LLIST_LENGTH;
}

void Remove(const int index) {
	cout << "REMOVE:" << index << endl;
	if (LLIST_LENGTH == 0 || index >= LLIST_SIZE || index < 0) {
		return;
	}

	int count = index - 1;
	int prev = HEAD;
	while (count > 0) {
		prev = LLIST[prev].mNext;
		--count;
	}

	int target = NULL_VALUE;
	
	if (index == 0) {
		target = HEAD;
		HEAD = LLIST[target].mNext;
	}
	else {
		target = LLIST[prev].mNext;
	}
	LLIST[prev].mNext = LLIST[target].mNext;
	LLIST[target].mNext = NULL_VALUE;
	--LLIST_LENGTH;

	if (target == LAST) {
		LAST = prev;
	}

	AddToNewNodes(target);
}

void Insert(const int index, const int value) {
	cout << "INSERT:" << index << " " << value << endl;
	if (LLIST_LENGTH == LLIST_SIZE || index >= LLIST_SIZE || index < 0) {
		return;
	}

	int count = index - 1;
	int cursor = HEAD;
	int prev = NULL_VALUE;
	while (count > 0) {
		prev = cursor;
		cursor = LLIST[cursor].mNext;
		--count;
	}

	int tail = GetNewNode();
	LLIST[tail].mData = value;
	LLIST[tail].mNext = cursor;
	LLIST[prev].mNext = tail;
	++LLIST_LENGTH;

	if (prev == HEAD) {
		HEAD = tail;
	}
}

int Search(const int value) {
	cout << "SEARCH:" << value << endl;
	if (LLIST_LENGTH == 0) {
		return NULL_VALUE;
	}

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
	int input_data[8] = { 10,11,12,13,14,15,16,17 };

	InitLinkedList(LLIST_SIZE);

	for (int i = 0; i < 8; ++i) {
		Append(input_data[i]);
		PrintLList(LLIST, HEAD);
	}

	Remove(0);
	PrintLList(LLIST, HEAD);
	PrintArray(LLIST, LLIST_SIZE);

	Remove(1);
	PrintLList(LLIST, HEAD);
	PrintArray(LLIST, LLIST_SIZE);

	Remove(5);
	PrintLList(LLIST, HEAD);
	PrintArray(LLIST, LLIST_SIZE);

	Insert(0, 18);
	PrintLList(LLIST, HEAD);
	PrintArray(LLIST, LLIST_SIZE);

	Insert(5, 19);
	PrintLList(LLIST, HEAD);
	PrintArray(LLIST, LLIST_SIZE);

	int index = Search(18);
	cout << "FOUND :[" << index << "]" << LLIST[index].mData << endl;
	PrintLList(LLIST, HEAD);

	index = Search(16);
	cout << "FOUND :[" << index << "]" << LLIST[index].mData << endl;
	PrintLList(LLIST, HEAD);

	Remove(0);
	PrintLList(LLIST, HEAD);
	PrintArray(LLIST, LLIST_SIZE);

	return 0;
}
