#include <iostream>

using namespace std;

#define NULL 0

const int MAX_SIZE = 50001;

const unsigned int MASK = 32767; // 7FFF
unsigned int convert_3chars(char* src);
unsigned int convert_1char(const char* src, const unsigned int hash);

int SRC_LENGTH = 0;
char SRC_STRING[MAX_SIZE];

typedef struct _node {
	_node* mPrev;
	_node* mNext;
	int mIndicator;

	bool operator<(const int indicator);
	bool operator>(const int indicator);
	bool operator==(const int indicator);
} Node;

const int MAX_INDICATOR_HASH = 40000;
const int MAX_POOL_SIZE = 200001;
const int NOT_FOUND = -1;

Node NODE_POOL[MAX_POOL_SIZE];
int NODE_POOL_LENGTH = 0;

Node* NewNode();

typedef struct _dllist {
	Node* mHead;
	Node* mTail;
	int mLength;

	void Init();
	void Add(const int indicator);
	void Remove(const int indicator);
	int Pop();
	int GetFirstElement();
} DLList;

DLList INDICATOR_HASH[MAX_INDICATOR_HASH];

void mark_all_indicator();
void mark_indicator(const int position);
void unmark_indicator(const int position);

void StrCopy(const char* src, char* dest) {
	while (*src != '\0') {
		*dest++ = *src++;
	}
	*dest = '\0';
}

void init(int N, char init_string[])
{
	//cout << "INIT>>>" << " init_str: " << endl << init_string << endl;
	NODE_POOL_LENGTH = 0;
	for (register int i = 0; i < MAX_INDICATOR_HASH; ++i) {
		INDICATOR_HASH[i].Init();
	}

	SRC_LENGTH = N;
	
	StrCopy(init_string, SRC_STRING);

	mark_all_indicator();
}

int change(char string_A[], char string_B[])
{
	//cout << "CHANGE>>>" << " A:" << string_A << " B:" << string_B << endl;

	unsigned int a_hash = convert_3chars(string_A);
	if (INDICATOR_HASH[a_hash].mLength == 0) {
		return 0;
	}

	int count = 0;
	int previous = NOT_FOUND;
	int position = NOT_FOUND;

	previous = INDICATOR_HASH[a_hash].Pop();

	for (register int i = 0; i < INDICATOR_HASH[a_hash].mLength; ++i) {
		position = INDICATOR_HASH[a_hash].GetFirstElement();

		if (position <= previous + 2) {
			INDICATOR_HASH[a_hash].Pop();
		}
		else {
			break;
		}
	}

	INDICATOR_HASH[a_hash].Add(previous);

	for (register int i = 0; i < INDICATOR_HASH[a_hash].mLength; ++i) {
		position = INDICATOR_HASH[a_hash].Pop();

		unmark_indicator(position);

		*(SRC_STRING + position) = string_B[0];
		*(SRC_STRING + position + 1) = string_B[1];
		*(SRC_STRING + position + 2) = string_B[2];
		count++;

		//cout << "Init_str: " << endl << SRC_STRING << endl;
		mark_indicator(position);
	}

	return count;
}

void result(char ret[])
{
	StrCopy(SRC_STRING, ret);
}

unsigned int convert_3chars(char* src) {
	unsigned int value = 0;
	char* key = src;
	for (register int i = 0; i < 3; ++i) {
		value = (value << 5) + *key - 'a';
		key++;
	}
	return value;
}

unsigned int convert_1char(const char* src, const unsigned int hash) {
	unsigned int value = hash;
	value = (value << 5) & MASK;
	value = value + *src - 'a';

	return value;
}

Node* NewNode() {
	return &(NODE_POOL[NODE_POOL_LENGTH++]);
}

// Node

bool _node::operator<(const int indicator) {
	return (this->mIndicator < indicator);
}

bool _node::operator>(const int indicator) {
	return (this->mIndicator > indicator);
}

bool _node::operator==(const int indicator) {
	return (this->mIndicator == indicator);
}

// DDList

void _dllist::Init() {
	this->mHead = NewNode();
	this->mTail = NewNode();

	this->mHead->mNext = this->mTail;
	this->mHead->mPrev = NULL;
	this->mTail->mPrev = this->mHead;
	this->mTail->mNext = NULL;

	this->mLength = 0;
}

void _dllist::Add(const int indicator) {
	Node* cursor = this->mHead->mNext;

	while (cursor != this->mTail && *cursor < indicator) {
		cursor = cursor->mNext;
	}

	Node* node = NewNode();
	node->mIndicator = indicator;

	Node* prev = cursor->mPrev;

	prev->mNext = node;
	node->mPrev = prev;

	node->mNext = cursor;
	cursor->mPrev = node;

	this->mLength++;

	//cout << "   List.Add: " << indicator << endl;
}

void _dllist::Remove(const int indicator) {
	if (this->mLength == 0) {
		return;
	}

	Node* cursor = this->mHead->mNext;
	bool found = false;

	while (cursor != this->mTail && found != true) {
		if (*cursor == indicator) {
			found = true;
		}
		else {
			cursor = cursor->mNext;
		}
	}

	if (found == true) {
		Node* prev = cursor->mPrev;
		Node* next = cursor->mNext;

		prev->mNext = next;
		next->mPrev = prev;

		cursor->mIndicator = NOT_FOUND;
		cursor->mPrev = NULL;
		cursor->mNext = NULL;

		this->mLength--;

		//cout << "   List.Remove: " << indicator << endl;
	}
}

int _dllist::Pop() {
	if (this->mLength == 0) {
		return NOT_FOUND;
	}

	Node* cursor = this->mHead->mNext;
	int indicator = cursor->mIndicator;
	
	Node* next = cursor->mNext;

	this->mHead->mNext = next;
	next->mPrev = this->mHead;

	cursor->mNext = NULL;
	cursor->mPrev = NULL;
	cursor->mIndicator = NOT_FOUND;
	this->mLength--;

	//cout << "   List.Pop: " << indicator << endl;

	return indicator;
}

int _dllist::GetFirstElement() {
	if (this->mLength == 0) {
		return NOT_FOUND;
	}

	Node* cursor = this->mHead->mNext;

	return cursor->mIndicator;
}

void mark_all_indicator() {
	for (register int i = 0; i <= SRC_LENGTH - 3; ++i) {
		unsigned int hash = convert_3chars((SRC_STRING + i));
		//cout << "MARK: " << * (SRC_STRING + i) << *(SRC_STRING + i + 1) << *(SRC_STRING + i + 2) << " - hash: " << hash << endl;
		INDICATOR_HASH[hash].Add(i);
	}
}

void mark_indicator(const int position) {
	for (register int i = position - 2; i <= position + 2; ++i) {
		if (i < 0 || i > SRC_LENGTH - 2) {
			continue;
		}
		unsigned int hash = convert_3chars((SRC_STRING + i));
		//cout << "MARK: " << * (SRC_STRING + i) << *(SRC_STRING + i + 1) << *(SRC_STRING + i + 2) << " - hash: " << hash << endl;
		INDICATOR_HASH[hash].Add(i);

	}
}

void unmark_indicator(const int position) {
	for (register int i = position - 2; i <= position + 2; ++i) {
		if (i < 0 || i > SRC_LENGTH - 2) {
			continue;
		}
		unsigned int hash = convert_3chars((SRC_STRING + i));
		//cout << "UNMK: " << *(SRC_STRING + i) << *(SRC_STRING + i + 1) << *(SRC_STRING + i + 2) << " - hash: " << hash << endl;
		INDICATOR_HASH[hash].Remove(i);

	}
}