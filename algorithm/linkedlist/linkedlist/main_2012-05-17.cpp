#include <iostream>
#include <string>

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

const int MEMBERS_SIZE = 9;
typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[MEMBERS_SIZE] = {
	{"abc", 60},
	{"def", 83},
	{"ghi", 74},
	{"jkl", 103},
	{"mno", 93},
	{"pqr", 52},
	{"stu", 71},
	{"vwx", 89},
	{"yz", 100},
};


void PrintList(const LinkedList* pllist) {
	Node* pTarget = pllist->mHead;
	while (pTarget != NULL) {
		cout << pTarget->mValue << ' ';
		pTarget = pTarget->mNext;
	}

	cout << endl;
}

void PrintList(const LinkedList* const pllist, const User* const pMembers) {
	Node* pTarget = pllist->mHead;
	while (pTarget != NULL) {
		cout << "[" << pTarget->mValue << "]" << pMembers[pTarget->mValue].mName << ":" << pMembers[pTarget->mValue].mWeight << ' ';
		pTarget = pTarget->mNext;
	}

	cout << endl;
}

void PrintMembers(const User* const pMembers, const int length) {
	for (int i = 0; i < length; i++) {
		cout << "[" << i << "]" << pMembers[i].mName << ":" << pMembers[i].mWeight << ' ';
	}

	cout << endl;
}

Node* NewNode() {
	if (POOL_COUNT == LL_SIZE) {
		return NULL;
	}

	return &NODE_POOL[POOL_COUNT++];
}

void Init(LinkedList* pllist) {
	LLIST.mLength = 0;
	LLIST.mHead = NULL;
	POOL_COUNT = 0;
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

void Remove(LinkedList * const pllist, const int index) {
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

int Search(LinkedList * const pllist, const int value) {
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

int Search(LinkedList* const pllist, const User* const pMembers, const char * name) {
	if (pllist->mLength == 0) {
		return NOT_FOUND;
	}

	int found = NOT_FOUND;
	Node* pTarget = pllist->mHead;

	while (pTarget != NULL) {
		found++;
		if (strcmp(pMembers[pTarget->mValue].mName, name) == 0) {
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

	cout << endl;

	cout << "Linked List with MEMBERS" << endl;
	PrintMembers(MEMBERS, MEMBERS_SIZE);

	cout << "Linked List with MEMBERS: Init()" << endl;
	Init(&LLIST);
	PrintList(&LLIST);

	cout << "Linked List with MEMBERS: Append()" << endl;
	for (int i = 0; i < 4; ++i) {
		Append(&LLIST, i);
	}
	PrintList(&LLIST, MEMBERS);

	index = 0;
	value = 4;
	cout << "Linked List with MEMBERS: Insert(" << index << "," << value << ")" << endl;
	Insert(&LLIST, index, value);
	PrintList(&LLIST, MEMBERS);

	index = 2;
	value = 5;
	cout << "Linked List with MEMBERS: Insert(" << index << "," << value << ")" << endl;
	Insert(&LLIST, index, value);
	PrintList(&LLIST, MEMBERS);

	index = 0;
	cout << "Linked List with MEMBERS: Remove(" << index << ")" << endl;
	Remove(&LLIST, index);
	PrintList(&LLIST, MEMBERS);

	index = 2;
	cout << "Linked List with MEMBERS: Remove(" << index << ")" << endl;
	Remove(&LLIST, index);
	PrintList(&LLIST, MEMBERS);

	cout << "Linked List: Search(" << "abc" << ")" << endl;
	found = Search(&LLIST, MEMBERS, "abc");
	cout << ((found != NOT_FOUND) ? "Found: value=" : "Not found: value=") << value << " index=" << found << endl;

	value = 8;
	cout << "Linked List: Search(" << "123" << ")" << endl;
	found = Search(&LLIST, MEMBERS, "123");
	cout << ((found != NOT_FOUND) ? "Found: value=" : "Not found: value=") << value << " index=" << found << endl;

	return 0;
}
