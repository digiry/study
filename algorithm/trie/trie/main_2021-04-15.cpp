#include <iostream>

using namespace std;

const int ALPHABET_SIZE = 26;

typedef struct _Node {
	int value;
	struct _Node* children[ALPHABET_SIZE];
} Node;

typedef struct _Trie {
	Node* root;
	int count;
} Trie;

const int POOL_SIZE = 8 * ALPHABET_SIZE;
Node POOL[POOL_SIZE] = { 0, };
int POOL_INDEX = -1;

inline int charToIndex(const char letter) {
	return int(letter - 'a');
}

inline int StrLength(const char* src) {
	int length = 0;
	while (*src != '\0') {
		length++;
		src++;
	}

	return length;
}

Node* getNode() {
	Node* pNode = NULL;
	POOL_INDEX++;
	pNode = &POOL[POOL_INDEX];

	if (pNode) {
		pNode->value = 0;
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			pNode->children[i] = NULL;
		}
	}

	return pNode;
}

void InitTrie(Trie* const pTrie) {
	pTrie->root = getNode();
	pTrie->count = 0;
}

void Insert(Trie* const pTrie, const char* key) {
	int length = StrLength(key);

	pTrie->count++;
	Node* pNode = pTrie->root;

	for (int level = 0; level < length; level++) {
		int index = charToIndex(key[level]);
		if (!pNode->children[index]) {
			pNode->children[index] = getNode();
		}
		pNode = pNode->children[index];
	}

	pNode->value = pTrie->count;
}

int Search(Trie* const pTrie, const char* key) {
	int length = StrLength(key);
	Node* pNode = pTrie->root;

	for (int level = 0; level < length; level++) {
		int index = charToIndex(key[level]);
		if (!pNode->children[index]) {
			return 0;
		}

		pNode = pNode->children[index];
	}

	int found = 0;

	if (pNode != NULL && pNode->value > 0) {
		found = 1;
	}
	
	return found;
}

int main() {
	char keys[][8] = { "the", "a", "there", "answer", "any", "by", "bye", "their" };
	char output[][32] = { "Not present in trie", "Present in trie" };

	Trie trie;
	InitTrie(&trie);

	const int keys_size = sizeof(keys) / sizeof(keys[0]);
	for (int i = 0; i < keys_size; i++) {
		Insert(&trie, keys[i]);
	}

	cout << "the --- " << output[Search(&trie, "the")] << endl;
	cout << "these --- " << output[Search(&trie, "these")] << endl;
	cout << "their --- " << output[Search(&trie, "their")] << endl;
	cout << "thaw --- " << output[Search(&trie, "thaw")] << endl;

	return 0;
}
