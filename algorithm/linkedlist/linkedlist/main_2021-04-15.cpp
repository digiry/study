#include <iostream>

using namespace std;

const int NOT_VALUE = -1;
const int NOT_FOUND = -1;
const int LL_SIZE = 20;

typedef struct _Node {
	int mValue;
	struct _Node* mNext;
} Node;

typedef struct _LinkedList {
	Node* mHead;
	int mLength;
} LinkedList;

Node NODE_POOL[LL_SIZE] = { 0, };
int POOL_COUNT = 0;

LinkedList LLIST;

void Init(LinkedList* pllist) {
	LLIST.mLength = 0;
	LLIST.mHead = NULL;
	POOL_COUNT = 0;
}

void PrintList(const LinkedList* pllist) {
	Node* target = pllist->mHead;
	while (target != NULL) {
		cout << target->mValue << ' ';
		target = target->mNext;
	}

	cout << endl;
}

Node* NewNode() {
	if (POOL_COUNT == LL_SIZE) {
		return NULL;
	}

	return &NODE_POOL[POOL_COUNT++];
}

void Append(LinkedList* const pllist, int value) {
	if (pllist->mLength == LL_SIZE) {
		return;
	}

	Node* pNew = NewNode();
	pNew->mValue = value;
	pNew->mNext = NULL;

	if (pllist->mHead == NULL) {
		pllist->mHead = pNew;
		pllist->mLength++;

		return;
	}

	Node* pTemp = pllist->mHead;
	while (pTemp->mNext != NULL) {
		pTemp = pTemp->mNext;
	}

	pTemp->mNext = pNew;
	pllist->mLength++;
}

void Insert(LinkedList* const pllist, const int index, const int value) {
	if (pllist->mLength == LL_SIZE) {
		return;
	}

	Node* pNew = NewNode();
	pNew->mValue = value;
	pNew->mNext = NULL;

	if (index == 0) {
		pNew->mNext = pllist->mHead;
		pllist->mHead = pNew;
		pllist->mLength++;

		return;
	}

	int prev_count = index - 1;
	Node* pPrev = pllist->mHead;
	while (prev_count > 0 && pPrev->mNext != NULL) {
		pPrev = pPrev->mNext;
		prev_count--;
	}

	pNew->mNext = pPrev->mNext;
	pPrev->mNext = pNew;
	pllist->mLength++;
}

void Remove(LinkedList* const pllist, const int index) {
	if (pllist->mLength == 0) {
		return;
	}

	Node* del_node = NULL;

	if (index == 0) {
		del_node = pllist->mHead;
		pllist->mHead = del_node->mNext;
		pllist->mLength--;

		del_node->mValue = NOT_VALUE;
		del_node->mNext = NULL;

		return;
	}

	int prev_count = index - 1;
	Node* pPrev = pllist->mHead;
	while (prev_count > 0 && pPrev->mNext != NULL) {
		pPrev = pPrev->mNext;
		prev_count--;
	}

	del_node = pPrev->mNext;
	pPrev->mNext = del_node->mNext;
	pllist->mLength--;

	del_node->mValue = NOT_VALUE;
	del_node->mNext = NULL;
}

int Search(LinkedList* const pllist, const int value) {
	if (pllist->mLength == 0) {
		return NOT_FOUND;
	}

	int found = NOT_FOUND;
	Node* pTarget = pllist->mHead;

	while (pTarget != NULL) {
		found++;
		if (pTarget->mValue == value) {
			break;
		}

		pTarget = pTarget->mNext;
	}

	if (pTarget == NULL) {
		found = NOT_FOUND;
	}

	return found;
}

int main() {
	const int input_data[4] = { 4,5,6,7 };

	cout << "Linked List: Init()" << endl;
	Init(&LLIST);
	PrintList(&LLIST);

	cout << "Linked List: Append()" << endl;
	for (int i = 0; i < 4; ++i) {
		Append(&LLIST, input_data[i]);
	}
	PrintList(&LLIST);

	int index = 0;
	int value = 8;
	cout << "Linked List: Insert(" << index << "," << value << ")" << endl;
	Insert(&LLIST, index, value);
	PrintList(&LLIST);

	index = 2;
	value = 9;
	cout << "Linked List: Insert(" << index << "," << value << ")" << endl;
	Insert(&LLIST, index, value);
	PrintList(&LLIST);

	index = 0;
	cout << "Linked List: Remove(" << index << ")" << endl;
	Remove(&LLIST, index);
	PrintList(&LLIST);

	index = 2;
	cout << "Linked List: Remove(" << index << ")" << endl;
	Remove(&LLIST, index);
	PrintList(&LLIST);

	value = 6;
	cout << "Linked List: Search(" << value << ")" << endl;
	int found = Search(&LLIST, value);
	cout << ((found != NOT_FOUND) ? "Found: value=" : "Not found: value=") << value << " index=" << found << endl;

	value = 8;
	cout << "Linked List: Search(" << value << ")" << endl;
	found = Search(&LLIST, value);
	cout << ((found != NOT_FOUND) ? "Found: value=" : "Not found: value=") << value << " index=" << found << endl;

	return 0;
}
