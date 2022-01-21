const int MAX_SIZE = 100001;

const int MAX_NAME_SIZE = 11;
const int NO_INDEX = 0;

void StrCopy(const char* src, char* dest);
int StrComp(const char* a_src, const char* b_src);
void SwapHeapNodes(const int a_index, const int b_index);

typedef struct _node {
	int mIdx;
	char mName[MAX_NAME_SIZE];
	int mHeapIndex;

	bool operator<(const _node& rhs);
} Node;

Node DATA[MAX_SIZE];

const int HEAP_OVER_ROOT = 0;
const int HEAP_ROOT = 1;

int HEAP[MAX_SIZE];
int HEAP_LENGTH = 0;
const int HEAP_SIZE = MAX_SIZE;

void _upside_update(int heap_index);
void _downside_update(int heap_index);

void clear();

void init() {
	clear();
}

void clear() {
	HEAP_LENGTH = 0;
}

void _upside_update(int heap_index) {
	int child = heap_index;
	int parent = child >> 1;

	while (parent > HEAP_OVER_ROOT && DATA[HEAP[child]] < DATA[HEAP[parent]]) {
		SwapHeapNodes(parent, child);
		child = parent;
		parent = child >> 1;
	}
}

void push(int idx, char name[]) {
	HEAP_LENGTH++;
	HEAP[HEAP_LENGTH] = idx;

	DATA[idx].mIdx = idx;
	StrCopy(name, DATA[idx].mName);
	DATA[idx].mHeapIndex = HEAP_LENGTH;

	_upside_update(HEAP_LENGTH);
}

void _downside_update(int heap_index) {
	int parent = heap_index;
	int child = parent << 1;
	if (child + 1 <= HEAP_LENGTH) {
		child = (DATA[HEAP[child]] < DATA[HEAP[child + 1]]) ? child : child + 1;
	}

	while (child <= HEAP_LENGTH && DATA[HEAP[child]] < DATA[HEAP[parent]]) {
		SwapHeapNodes(parent, child);
		parent = child;
		child = parent << 1;
		if (child + 1 <= HEAP_LENGTH) {
			child = (DATA[HEAP[child]] < DATA[HEAP[child + 1]]) ? child : child + 1;
		}
	}
}

int pop() {
	int delete_idx = HEAP[HEAP_ROOT];

	HEAP[HEAP_ROOT] = HEAP[HEAP_LENGTH];
	HEAP_LENGTH--;
	DATA[delete_idx].mIdx = NO_INDEX;
	DATA[delete_idx].mName[0] = '\0';
	DATA[delete_idx].mHeapIndex = NO_INDEX;
	DATA[HEAP[HEAP_ROOT]].mHeapIndex = HEAP_ROOT;

	_downside_update(HEAP_ROOT);

	return delete_idx;
}

void mod(int idx, char name[]) {
	int modify_idx = idx;

	int target_heap_index = DATA[modify_idx].mHeapIndex;
	StrCopy(name, DATA[modify_idx].mName);

	_upside_update(target_heap_index);
	_downside_update(target_heap_index);
}

void StrCopy(const char* src, char* dest) {
	while (*src != '\0') {
		*dest++ = *src++;
	}
	*dest = '\0';
}

int StrComp(const char* a_src, const char* b_src) {
	while (*a_src != '\0' && *a_src == *b_src) {		
		a_src++;
		b_src++;
	}

	return *a_src - *b_src;
}

void SwapHeapNodes(const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	HEAP[a_index] = HEAP[a_index] ^ HEAP[b_index];
	HEAP[b_index] = HEAP[a_index] ^ HEAP[b_index];
	HEAP[a_index] = HEAP[a_index] ^ HEAP[b_index];

	DATA[HEAP[a_index]].mHeapIndex = a_index;
	DATA[HEAP[b_index]].mHeapIndex = b_index;
}

// Node

bool _node::operator<(const _node& rhs)
{
	if (StrComp(this->mName, rhs.mName) == 0) {
		return this->mIdx < rhs.mIdx;
	}

	return (StrComp(this->mName, rhs.mName) > 0);
}
