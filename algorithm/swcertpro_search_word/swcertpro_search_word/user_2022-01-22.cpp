#define NULL 0

const int ALPHABET_SIZE = 27;
const int NOT_WORD = 0;
const char WILDCARD = '?';

typedef struct _trienode {
	int mCount;
	_trienode* mAlphabets[ALPHABET_SIZE];
} TrieNode;

typedef struct _trie {
	TrieNode* mRoot;

	_trie();
	void Init();
	TrieNode* Add(char* keyword);
	TrieNode* Search(char* keyword);
} Trie;

const int TRIE_NODE_POOL_SIZE = (30*20000) + 1;
int TRIE_NODE_POOL_LENGTH = 0;
TrieNode TRIE_NODE_POOL[TRIE_NODE_POOL_SIZE];

TrieNode* GetNewTrieNode();
int CharToIndex(char letter);
char IndexToChar(int index);

const int MAX_WORD_SIZE = 31;
const int MAX_STACK_SIZE = 20000;

typedef struct _stacknode {
	TrieNode* mpTrieNode;
} StackNode;

typedef struct _stack {
	StackNode* mArray[MAX_STACK_SIZE];
	int mLength;

	_stack();
	void Init();
	void Push(TrieNode* pTrieNode);
	void Pop();
	StackNode* Top();
	bool Empty();
} Stack;

const int STACK_NODE_POOL_SIZE = MAX_STACK_SIZE * 2;
int STACK_NODE_POOL_LENGTH = 0;
StackNode STACK_NODE_POOL[STACK_NODE_POOL_SIZE];

StackNode* GetNewStackNode();
Stack* SearchByPatternInTrie(Trie* pTrie, char* keyword);

Trie TRIE;
Stack STACK_1;
Stack STACK_2;

void init() {
	TRIE.Init();
	STACK_NODE_POOL_LENGTH = 0;
}

int add(char str[]) {
	TrieNode* pNode = TRIE.Add(str);
	int count = 0;

	if (pNode != NULL) {
		count = pNode->mCount;
	}

	return count;
}

int remove(char str[]) {
	Stack* pStack = SearchByPatternInTrie(&TRIE, str);
	StackNode* pStackNode = NULL;
	TrieNode* pTrieNode = NULL;
	int removedCount = 0;

	while (pStack->Empty() == false) {
		pStackNode = pStack->Top();
		pTrieNode = pStackNode->mpTrieNode;
		pStack->Pop();

		removedCount += pTrieNode->mCount;
		pTrieNode->mCount = 0;
	}
	return removedCount;
}

int search(char str[]) {
	Stack* pStack = SearchByPatternInTrie(&TRIE, str);
	StackNode* pStackNode = NULL;
	TrieNode* pTrieNode = NULL;
	int foundCount = 0;

	while (pStack->Empty() == false) {
		pStackNode = pStack->Top();
		pTrieNode = pStackNode->mpTrieNode;
		pStack->Pop();

		foundCount += pTrieNode->mCount;
	}
	return foundCount;
}

// Trie

inline TrieNode* GetNewTrieNode() {
	TrieNode* newNode = &TRIE_NODE_POOL[TRIE_NODE_POOL_LENGTH];

	newNode->mCount = NOT_WORD;
	for (register int i = 0; i < ALPHABET_SIZE; ++i) {
		newNode->mAlphabets[i] = NULL;
	}

	TRIE_NODE_POOL_LENGTH++;

	return newNode;
}
inline int CharToIndex(char letter) {
	int index = letter - 'a' + 1;
	return index;
}
inline char IndexToChar(int index) {
	char letter = 'a' + index - 1;
	return letter;
}

_trie::_trie() {
	this->Init();
}
void _trie::Init() {
	TRIE_NODE_POOL_LENGTH = 0;
	this->mRoot = GetNewTrieNode();
}
TrieNode* _trie::Add(char* keyword) {
	TrieNode* pNode = this->mRoot;
	int letter_i = 0;

	while (*keyword != '\0') {
		letter_i = CharToIndex(*keyword);
		if (pNode->mAlphabets[letter_i] == NULL) {
			pNode->mAlphabets[letter_i] = GetNewTrieNode();
		}

		pNode = pNode->mAlphabets[letter_i];
		keyword++;
	}

	pNode->mCount++;

	return pNode;
}
TrieNode* _trie::Search(char* keyword) {
	TrieNode* pNode = this->mRoot;
	TrieNode* foundNode = NULL;
	int letter_i = 0;

	while (*keyword != '\0') {
		letter_i = CharToIndex(*keyword);
		foundNode = pNode->mAlphabets[letter_i];
		if (foundNode == NULL) {
			return NULL;
		}

		pNode = foundNode;
		keyword++;
	}

	if (foundNode->mCount == NOT_WORD) {
		foundNode = NULL;
	}

	return foundNode;
}

// Stack

inline StackNode* GetNewStackNode() {
	StackNode* newNode = &STACK_NODE_POOL[STACK_NODE_POOL_LENGTH];
	
	newNode->mpTrieNode = NULL;

	STACK_NODE_POOL_LENGTH++;

	return newNode;
}

_stack::_stack() {
	this->Init();
}
void _stack::Init() {
	this->mLength = 0;
	for (register int i = 0; i < MAX_STACK_SIZE; ++i) {
		this->mArray[i] = NULL;
	}
}
void _stack::Push(TrieNode* pTrieNode) {
	if (pTrieNode == NULL) {
		return;
	}

	StackNode* newNode = GetNewStackNode();
	newNode->mpTrieNode = pTrieNode;
	
	this->mArray[this->mLength] = newNode;
	this->mLength++;
}
void _stack::Pop() {
	if (this->mLength == 0) {
		return;
	}

	StackNode* pNode = this->mArray[this->mLength - 1];
	pNode->mpTrieNode = NULL;

	this->mLength--;
}
StackNode* _stack::Top() {
	if (this->mLength == 0) {
		return NULL;
	}
	StackNode* pNode = this->mArray[this->mLength - 1];
	return pNode;
}
bool _stack::Empty() {
	return this->mLength == 0;
}

// Main

Stack* SearchByPatternInTrie(Trie* pTrie, char* keyword) {
	Stack* pWorkingStack = &STACK_1;
	Stack* pResultStack = &STACK_2;
	Stack* pTempStack = NULL;
	StackNode* pStackNode = NULL;
	pWorkingStack->Init();
	pResultStack->Init();
	TrieNode* pTrieNode = pTrie->mRoot;
	register int letter_i = 0;

	if (*keyword != WILDCARD) {
		letter_i = CharToIndex(*keyword);
		if (pTrieNode->mAlphabets[letter_i] != NULL) {
			pWorkingStack->Push(pTrieNode->mAlphabets[letter_i]);
		}
	}
	else {
		for (letter_i = 1; letter_i < ALPHABET_SIZE; ++letter_i) {
			if (pTrieNode->mAlphabets[letter_i] != NULL) {
				pWorkingStack->Push(pTrieNode->mAlphabets[letter_i]);
			}
		}
	}

	keyword++;

	while (*keyword != '\0') {
		while (pWorkingStack->Empty() == false) {
			pStackNode = pWorkingStack->Top();
			pTrieNode = pStackNode->mpTrieNode;
			pWorkingStack->Pop();

			if (*keyword != WILDCARD) {
				letter_i = CharToIndex(*keyword);
				if (pTrieNode->mAlphabets[letter_i] != NULL) {
					pResultStack->Push(pTrieNode->mAlphabets[letter_i]);
				}
			}
			else {
				for (letter_i = 1; letter_i < ALPHABET_SIZE; ++letter_i) {
					if (pTrieNode->mAlphabets[letter_i] != NULL) {
						pResultStack->Push(pTrieNode->mAlphabets[letter_i]);
					}
				}
			}
		}

		keyword++;
		pTempStack = pWorkingStack;
		pWorkingStack = pResultStack;
		pResultStack = pTempStack;
	}

	return pWorkingStack;
}