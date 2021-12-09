#define NULL 0

const int MAX_STRING_SIZE = 50000;
const int ALPHA_LENGTH = 26;
const int KEY_SIZE = 3;

typedef struct _indexNode {
	int mIndex;
	_indexNode* mPrev;
	_indexNode* mNext;
} IndexNode;

IndexNode INDEX_NODE_POOL[MAX_STRING_SIZE + 1];
int NODE_POOL_LENGTH = 0;

char SRC_STRING[MAX_STRING_SIZE + 1];
int SRC_STRING_LENGTH = 0;

typedef struct _keyNode {
	IndexNode mHead;

	void AddNode(IndexNode* pNode);
} KeyNode;

KeyNode KEY_MAP[ALPHA_LENGTH][ALPHA_LENGTH][ALPHA_LENGTH];

IndexNode* NewNode();
IndexNode* GetNodeByIndex(const int index);
void DeleteNodeByIndex(const int index);

void StrCopy(const char* src, char* dest);
void Swap(int* pArray, const int a_index, const int b_index);
void QuickSort(int* pArray, const int left, const int right);
int Partition(int* pArray, const int left, const int right);

void init(int N, char init_string[]) {
	SRC_STRING_LENGTH = N;
	StrCopy(init_string, SRC_STRING);

	NODE_POOL_LENGTH = 0;
	for (register int i = 0; i < ALPHA_LENGTH; ++i) {
		for (register int j = 0; j < ALPHA_LENGTH; ++j) {
			for (register int k = 0; k < ALPHA_LENGTH; ++k) {
				KEY_MAP[i][j][k].mHead.mNext = NULL;
				KEY_MAP[i][j][k].mHead.mPrev = NULL;
			}
		}
	}

	for (register int i = 0; i < MAX_STRING_SIZE; ++i) {
		INDEX_NODE_POOL[i].mPrev = NULL;
		INDEX_NODE_POOL[i].mNext = NULL;
	}

	register int first = 0;
	register int second = 0;
	register int third = 0;

	for (register int i = 0; i <= SRC_STRING_LENGTH - KEY_SIZE; ++i) {
		first = SRC_STRING[i] - 'a';
		second = SRC_STRING[i + 1] - 'a';
		third = SRC_STRING[i + 2] - 'a';

		register IndexNode* new_node = NewNode();
		new_node->mIndex = i;
		KEY_MAP[first][second][third].AddNode(new_node);
	}
}

int change(char string_A[], char string_B[]) {
	register int count = 0;
	register int candidates[MAX_STRING_SIZE] = { 0, };
	register int candidates_length = 0;

	register int first = string_A[0] - 'a';
	register int second = string_A[1] - 'a';
	register int third = string_A[2] - 'a';

	register IndexNode* pNode = KEY_MAP[first][second][third].mHead.mNext;
	//if (pNode == NULL) {
	//	return 0;
	//}

	while (pNode != NULL) {
		candidates[candidates_length++] = pNode->mIndex;
		pNode = pNode->mNext;
	}

	QuickSort(candidates, 0, candidates_length - 1);

	register int previous = -3;
	register int index = 0;
	for (register int i = 0; i < candidates_length; ++i) {
		index = candidates[i];
		if (index - previous < 3) {
			continue;
		}

		*(SRC_STRING + index) = string_B[0];
		*(SRC_STRING + index + 1) = string_B[1];
		*(SRC_STRING + index + 2) = string_B[2];

		count++;

		for (register int x = index - 2; x <= index + 2; ++x) {
			if (x < 0 || x > SRC_STRING_LENGTH - 3) {
				continue;
			}

			DeleteNodeByIndex(x);

			pNode = GetNodeByIndex(x);

			first = SRC_STRING[x] - 'a';
			second = SRC_STRING[x + 1] - 'a';
			third = SRC_STRING[x + 2] - 'a';
			KEY_MAP[first][second][third].AddNode(pNode);
		}
		previous = index;
	}

	return count;
}

void result(char ret[]) {
	StrCopy(SRC_STRING, ret);
}

inline IndexNode* NewNode() {
	return &INDEX_NODE_POOL[NODE_POOL_LENGTH++];
}

inline IndexNode* GetNodeByIndex(const int index) {
	return &INDEX_NODE_POOL[index];
}

inline void Swap(int* pArray, const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	pArray[a_index] = pArray[a_index] ^ pArray[b_index];
	pArray[b_index] = pArray[a_index] ^ pArray[b_index];
	pArray[a_index] = pArray[a_index] ^ pArray[b_index];
}

void QuickSort(int* pArray, const int left, const int right) {
	if (left >= right) {
		return;
	}

	register int pivot = Partition(pArray, left, right);
	QuickSort(pArray, left, pivot - 1);
	QuickSort(pArray, pivot + 1, right);
}

inline int Partition(int* pArray, const int left, const int right) {
	register int i = left;
	register int j = left - 1;
	register int pivot = (left + right) >> 1;

	while (i <= right) {
		if (pArray[i] < pArray[pivot]) {
			j++;
			Swap(pArray, i, j);

			if (j == pivot) {
				pivot = i;
			}
		}
		i++;
	}
	
	Swap(pArray, j + 1, pivot);

	return j + 1;
}

void StrCopy(const char* src, char* dest) {
	while (*src != NULL) {
		*dest++ = *src++;
	}
	*dest = NULL;
}

// KeyNode

void _keyNode::AddNode(IndexNode* pNode) {
	register IndexNode* firstNode = this->mHead.mNext;

	if (firstNode) {
		pNode->mNext = firstNode;
		firstNode->mPrev = pNode;
	}
	pNode->mPrev = &(this->mHead);
	this->mHead.mNext = pNode;
}

inline void DeleteNodeByIndex(const int index) {
	register IndexNode* targetNode = &INDEX_NODE_POOL[index];
	register IndexNode* prevNode = targetNode->mPrev;
	register IndexNode* nextNode = targetNode->mNext;

	prevNode->mNext = nextNode;
	if (nextNode) {
		nextNode->mPrev = prevNode;
	}

	targetNode->mPrev = NULL;
	targetNode->mNext = NULL;
}
