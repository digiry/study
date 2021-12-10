#define MAXM	3
#define NULL	0

const int MAX_MESSAGE_SIZE = 100001;
const int NO_ID = -1;
const int NO_TS = -1;
const int PASS = 1;
const int FAIL = 0;

typedef struct _message {
	int mMsgId;
	int mSenderId;
	int mReceiverId;
	int mScheduleTs;
	bool mBeingSentbox;
	bool mBeingInbox;
	bool mReadReceiver;

	bool operator<(const _message& rhs);
	bool operator>(const _message& rhs);
} Message;

Message MESSAGE_ARRAY[MAX_MESSAGE_SIZE];

typedef struct _node {
	int mMsgId;
	_node* mPrev;
	_node* mNext;
} Node;

const int MAX_NODE_POOL_SIZE = MAX_MESSAGE_SIZE;

Node NODE_POOL[MAX_NODE_POOL_SIZE];
int NODE_POOL_LENGTH = 0;

Node* NewNode();

typedef struct _stack {
	Node mHead;
	Node* mTop;
	int mLength;

	_stack();
	void Clear();
	void Push(const int msgId);
	int Pop();
	int Top();
	int operator[](const int index);
} Stack;

typedef struct _userboxes {
	int mUserId;
	Stack mSentbox;
	Stack mInbox;
} Userboxes;

const int MAX_USERS = 1001;

Userboxes USER_BOXES_ARRAY[MAX_USERS];
int USER_BOXES_LENGTH = 0;

const int HEAP_OVER_ROOT = 0;
const int HEAP_ROOT = 1;

typedef struct _schedulerheap {
	int mArray[MAX_MESSAGE_SIZE];
	int mLength;

	void Clear();
	void Swap(const int a_index, const int b_index);
	void Push(const int msgId);
	int Pop();
	int GetAtRoot();
} SchedulerHeap;

SchedulerHeap SCHEDULER_HEAP;

void updateAllSentboxes(const int currentTS);


void init(int N) {
	register int i = 0;
	for (i = 0; i <= N; ++i) {
		USER_BOXES_ARRAY[i].mUserId = i;
		USER_BOXES_ARRAY[i].mSentbox.Clear();
		USER_BOXES_ARRAY[i].mInbox.Clear();
	}
	USER_BOXES_LENGTH = N;

	for (i = 0; i < MAX_NODE_POOL_SIZE; ++i) {
		NODE_POOL[i].mMsgId = i;
		NODE_POOL[i].mPrev = NULL;
		NODE_POOL[i].mNext = NULL;
	}
	NODE_POOL_LENGTH = 0;

	SCHEDULER_HEAP.Clear();
}


void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp) {
	MESSAGE_ARRAY[mID].mMsgId = mID;
	MESSAGE_ARRAY[mID].mScheduleTs = scheduleTimestamp;
	MESSAGE_ARRAY[mID].mBeingInbox = false;
	MESSAGE_ARRAY[mID].mBeingSentbox = true;
	MESSAGE_ARRAY[mID].mSenderId = uID1;
	MESSAGE_ARRAY[mID].mReceiverId = uID2;
	MESSAGE_ARRAY[mID].mReadReceiver = false;

	USER_BOXES_ARRAY[uID1].mSentbox.Push(mID);
	SCHEDULER_HEAP.Push(mID);
	
	updateAllSentboxes(cTimestamp);
}


void SortList(int* pList, int count) {
	for (register int i = 0; i < count; ++i) {
		for (register int j = i + 1; j < count; ++j) {
			if (MESSAGE_ARRAY[pList[i]] < MESSAGE_ARRAY[pList[j]]) {
				if (i == j) {
					continue;
				}
				pList[i] = pList[i] ^ pList[j];
				pList[j] = pList[i] ^ pList[j];
				pList[i] = pList[i] ^ pList[j];
			}
		}
	}
}

int retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM]) {
	register int count = 0;
	register int msgId = NO_ID;

	updateAllSentboxes(cTimestamp);

	while (count < MAXM && USER_BOXES_ARRAY[uID].mSentbox.mLength != 0) {
		msgId = USER_BOXES_ARRAY[uID].mSentbox.Pop();
		if (MESSAGE_ARRAY[msgId].mSenderId == uID && MESSAGE_ARRAY[msgId].mBeingSentbox == false) {
			continue;
		}

		mIDList[count] = msgId;		

		count++;
	}

	SortList(mIDList, count);

	for (register int i = 0; i < count; ++i) {
		uIDList[i] = MESSAGE_ARRAY[mIDList[i]].mReceiverId;
		readList[i] = MESSAGE_ARRAY[mIDList[i]].mReadReceiver;
		USER_BOXES_ARRAY[uID].mSentbox.Push(mIDList[i]);
	}

	return count;
}


int retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM]) {
	register int count = 0;
	register int msgId = NO_ID;

	updateAllSentboxes(cTimestamp);

	while (count < MAXM && USER_BOXES_ARRAY[uID].mInbox.mLength != 0) {
		msgId = USER_BOXES_ARRAY[uID].mInbox.Pop();
		if (MESSAGE_ARRAY[msgId].mReceiverId == uID && MESSAGE_ARRAY[msgId].mBeingInbox == false) {
			continue;
		}

		mIDList[count] = msgId;
		
		count++;
	}
	SortList(mIDList, count);

	for (register int i = 0; i < count; ++i) {
		uIDList[i] = MESSAGE_ARRAY[mIDList[i]].mSenderId;
		readList[i] = MESSAGE_ARRAY[mIDList[i]].mReadReceiver;
		USER_BOXES_ARRAY[uID].mInbox.Push(mIDList[i]);
	}

	return count;
}


int readMessage(int cTimestamp, int uID, int mID) {
	updateAllSentboxes(cTimestamp);

	if (MESSAGE_ARRAY[mID].mReceiverId == uID && MESSAGE_ARRAY[mID].mBeingInbox && MESSAGE_ARRAY[mID].mScheduleTs <= cTimestamp) {
		MESSAGE_ARRAY[mID].mReadReceiver = true;
		return PASS;
	}

	if (MESSAGE_ARRAY[mID].mSenderId == uID && MESSAGE_ARRAY[mID].mBeingSentbox) {
		return PASS;
	}

	return FAIL;
}


int deleteMessage(int cTimestamp, int uID, int mID) {
	updateAllSentboxes(cTimestamp);

	if (MESSAGE_ARRAY[mID].mSenderId == uID && MESSAGE_ARRAY[mID].mBeingSentbox == true) {
		MESSAGE_ARRAY[mID].mBeingSentbox = false;
		return PASS;
	}

	if (MESSAGE_ARRAY[mID].mReceiverId == uID && MESSAGE_ARRAY[mID].mBeingInbox == true) {
		MESSAGE_ARRAY[mID].mBeingInbox = false;
		return PASS;
	}

	return FAIL;
}


inline void updateAllSentboxes(const int currentTS) {
	register int msgId = NO_ID;
	register int userId = NO_ID;

	msgId = SCHEDULER_HEAP.GetAtRoot();
	register int timestamp = MESSAGE_ARRAY[msgId].mScheduleTs;
	while (timestamp <= currentTS && SCHEDULER_HEAP.mLength > 0) {
		SCHEDULER_HEAP.Pop();

		if (MESSAGE_ARRAY[msgId].mBeingSentbox && MESSAGE_ARRAY[msgId].mBeingInbox == false) {
			MESSAGE_ARRAY[msgId].mBeingInbox = true;
			userId = MESSAGE_ARRAY[msgId].mReceiverId;
			USER_BOXES_ARRAY[userId].mInbox.Push(msgId);
		}

		msgId = SCHEDULER_HEAP.GetAtRoot();
		timestamp = MESSAGE_ARRAY[msgId].mScheduleTs;
	}
}


// Message

bool _message::operator<(const _message& rhs) {
	if (this->mScheduleTs == rhs.mScheduleTs) {
		return this->mMsgId < rhs.mMsgId;
	}

	return this->mScheduleTs < rhs.mScheduleTs;
}

bool _message::operator>(const _message& rhs) {
	if (this->mScheduleTs == rhs.mScheduleTs) {
		return this->mMsgId > rhs.mMsgId;
	}

	return this->mScheduleTs > rhs.mScheduleTs;
}


// Stack

_stack::_stack() {
	this->mHead.mMsgId = NO_ID;
	this->mHead.mNext = NULL;
	this->mHead.mPrev = &this->mHead;
	this->mTop = &this->mHead;
	this->mLength = 0;
}

void _stack::Clear() {
	this->mHead.mPrev = &this->mHead;
	this->mHead.mNext = NULL;
	this->mLength = 0;
}

void _stack::Push(const int msgId) {
	Node* new_node = NewNode();
	new_node->mMsgId = msgId;

	new_node->mNext = this->mTop->mNext;
	new_node->mPrev = this->mTop;
	this->mTop->mNext = new_node;
	
	this->mTop = new_node;

	this->mLength++;
}

int _stack::Pop() {
	int value = this->mTop->mMsgId;

	Node* mPrevious = this->mTop->mPrev;
	mPrevious->mNext = this->mTop->mNext;

	if (this->mTop == &this->mHead) {
		return  NO_ID;
	}

	this->mTop->mPrev = NULL;

	this->mTop = mPrevious;
	this->mLength--;

	return value;
}

int _stack::Top() {
	return this->mTop->mMsgId;
}

int _stack::operator[](const int index) {
	Node* pNode = this->mHead.mNext;
	for (register int i = 0; i < index; ++i) {
		pNode = pNode->mNext;
	}

	return pNode->mMsgId;
}

inline Node* NewNode() {
	return &NODE_POOL[NODE_POOL_LENGTH++];
}

// SchedulerHeap

void _schedulerheap::Clear() {
	for (register int i = 0; i < this->mLength; ++i) {
		this->mArray[i] = NO_ID;
	}

	this->mLength = 0;
}

void _schedulerheap::Swap(const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	this->mArray[a_index] = this->mArray[a_index] ^ this->mArray[b_index];
	this->mArray[b_index] = this->mArray[a_index] ^ this->mArray[b_index];
	this->mArray[a_index] = this->mArray[a_index] ^ this->mArray[b_index];
}

void _schedulerheap::Push(const int msgId) {
	this->mLength++;
	this->mArray[this->mLength] = msgId;
	int child = this->mLength;
	int parent = child >> 1;

	while (parent > HEAP_OVER_ROOT && MESSAGE_ARRAY[this->mArray[parent]] > MESSAGE_ARRAY[this->mArray[child]]) {
		this->Swap(parent, child);
		child = parent;
		parent = child >> 1;
	}
}

int _schedulerheap::Pop() {
	int root_value = this->mArray[HEAP_ROOT];

	this->mArray[HEAP_ROOT] = this->mArray[this->mLength];
	this->mLength--;
	
	int parent = HEAP_ROOT;
	int child = parent << 1;
	if (child + 1 <= this->mLength) {
		child = (MESSAGE_ARRAY[this->mArray[child]] < MESSAGE_ARRAY[this->mArray[child + 1]]) ? child : child + 1;
	}

	while (child <= this->mLength && MESSAGE_ARRAY[this->mArray[parent]] > MESSAGE_ARRAY[this->mArray[child]]) {
		this->Swap(parent, child);
		parent = child;
		child = parent << 1;
		if (child + 1 <= this->mLength) {
			child = (MESSAGE_ARRAY[this->mArray[child]] < MESSAGE_ARRAY[this->mArray[child + 1]]) ? child : child + 1;
		}
	}

	return root_value;
}

int _schedulerheap::GetAtRoot() {
	return this->mArray[HEAP_ROOT];
}
