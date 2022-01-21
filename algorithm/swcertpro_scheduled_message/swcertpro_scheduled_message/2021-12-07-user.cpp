#define MAXM	3

const int MAX_MESSAGES_SIZE = 100001;
const int MAX_QUEUE_SIZE = MAXM + 1;
const int NO_ID = -1;
const int NO_TS = 0;
const int READ = 1;
const int UNREAD = 0;

typedef struct _message {
	int mMId;
	int mSchTs;
	int mSenderId;
	int mReceiverId;
	int mReadable;

	_message();
	bool operator<(const _message& rhs);
} Message;

Message MESSAGE_ARRAY[MAX_MESSAGES_SIZE];

const int PQ_ROOT_OVER = 0;
const int PQ_ROOT = 1;

typedef struct _priority_q {
	int mMIds[MAX_MESSAGES_SIZE];
	int mLength;

	_priority_q();
	void _Swap(const int a_index, const int b_index);
	void Clear();
	int GetFirst();
	void Push(const int mId);
	int Pop();
} PQ;

PQ INBOX_PQ;
PQ SENTBOX_PQ;

typedef struct _fixedarray {
	int mMIds[MAX_QUEUE_SIZE];
	int mLength;

	_fixedarray();
	void PushBack(const int mId);
	bool Delete(const int mId);
	void Sort();
	void Clear();
	int operator[](const int index);
} FixedArray;

typedef struct _user {
	int mUId;
	FixedArray mSentbox;
	FixedArray mInbox;
} User;

const int MAX_USERS_SIZE = 1001;

User USER_ARRAY[MAX_USERS_SIZE];

int USER_LENGTH = 0;

void UpdateMessages(const int currentTs);

void init(int N)
{
	USER_LENGTH = N;
	for (register int i = 1; i <= USER_LENGTH; ++i) {
		USER_ARRAY[i].mUId = i;
		USER_ARRAY[i].mInbox.Clear();
		USER_ARRAY[i].mSentbox.Clear();
	}
	for (register int i = 1; i < MAX_MESSAGES_SIZE; ++i) {
		MESSAGE_ARRAY[i].mMId = i;
		MESSAGE_ARRAY[i].mSenderId = NO_ID;
		MESSAGE_ARRAY[i].mReceiverId = NO_ID;
		MESSAGE_ARRAY[i].mSchTs = NO_TS;
		MESSAGE_ARRAY[i].mReadable = UNREAD;
	}
	INBOX_PQ.Clear();
	SENTBOX_PQ.Clear();
}

void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp)
{
	MESSAGE_ARRAY[mID].mSchTs = scheduleTimestamp;
	MESSAGE_ARRAY[mID].mSenderId = uID1;
	MESSAGE_ARRAY[mID].mReceiverId = uID2;

	SENTBOX_PQ.Push(mID);

	USER_ARRAY[uID1].mSentbox.PushBack(mID);
}

int retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
	UpdateMessages(cTimestamp);

	int count = USER_ARRAY[uID].mSentbox.mLength;
	int mId = NO_ID;

	for (register int i = 0; i < count; ++i) {
		mId = USER_ARRAY[uID].mSentbox[i];
		mIDList[i] = mId;
		uIDList[i] = MESSAGE_ARRAY[mId].mReceiverId;
		readList[i] = MESSAGE_ARRAY[mId].mReadable;
	}
	return count;
}

int retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
	UpdateMessages(cTimestamp);

	int count = USER_ARRAY[uID].mInbox.mLength;
	int mId = NO_ID;

	for (register int i = 0; i < count; ++i) {
		mId = USER_ARRAY[uID].mInbox[i];
		mIDList[i] = mId;
		uIDList[i] = MESSAGE_ARRAY[mId].mSenderId;
		readList[i] = MESSAGE_ARRAY[mId].mReadable;
	}

	return count;
}

int readMessage(int cTimestamp, int uID, int mID)
{
	//UpdateMessages(cTimestamp);

	if (cTimestamp < MESSAGE_ARRAY[mID].mSchTs) {
		if (uID == MESSAGE_ARRAY[mID].mSenderId) {
			MESSAGE_ARRAY[mID].mReadable = READ;
			return 1;
		}

		return 0;
	}

	if (MESSAGE_ARRAY[mID].mSenderId == NO_ID && MESSAGE_ARRAY[mID].mReceiverId == NO_ID) {
		return 0;
	}

	MESSAGE_ARRAY[mID].mReadable = READ;

	return 1;
}

int deleteMessage(int cTimestamp, int uID, int mID)
{
	bool deleted = false;
	UpdateMessages(cTimestamp);

	if (USER_ARRAY[uID].mInbox.Delete(mID)) {
		MESSAGE_ARRAY[mID].mReceiverId = NO_ID;
		deleted = true;
	}
	
	if (USER_ARRAY[uID].mSentbox.Delete(mID)) {
		MESSAGE_ARRAY[mID].mSenderId = NO_ID;
		deleted = true;
	}

	return (deleted == true);
}

// Message

_message::_message() {
	this->mReadable = UNREAD;
}

bool _message::operator<(const _message& rhs) {
	return (this->mSchTs < rhs.mSchTs);
}

// Priority Queue

_priority_q::_priority_q() {
	this->Clear();
	this->mLength = 0;
}

void _priority_q::_Swap(const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	this->mMIds[a_index] = this->mMIds[a_index] ^ this->mMIds[b_index];
	this->mMIds[b_index] = this->mMIds[a_index] ^ this->mMIds[b_index];
	this->mMIds[a_index] = this->mMIds[a_index] ^ this->mMIds[b_index];
}

void _priority_q::Clear() {
	for (register int i = 0; i < MAX_MESSAGES_SIZE; ++i) {
		this->mMIds[i] = NO_ID;
	}
	this->mLength = 0;
}

int _priority_q::GetFirst() {
	return this->mMIds[PQ_ROOT];
}

void _priority_q::Push(const int mId) {
	this->mLength++;
	this->mMIds[this->mLength] = mId;
	
	int child = this->mLength;
	int parent = child >> 1;

	// MAX_HEAP
	while (parent > PQ_ROOT_OVER && MESSAGE_ARRAY[this->mMIds[child]] < MESSAGE_ARRAY[this->mMIds[parent]]) {
		this->_Swap(parent, child);
		child = parent;
		parent = child >> 1;
	}
}

int _priority_q::Pop() {
	int last_mId = this->mMIds[PQ_ROOT];
	
	this->mMIds[PQ_ROOT] = this->mMIds[this->mLength];
	this->mLength--;

	int parent = PQ_ROOT;
	int child = parent << 1;
	if (child + 1 <= this->mLength) {
		// MAX_HEAP
		child = (MESSAGE_ARRAY[this->mMIds[child]] < MESSAGE_ARRAY[this->mMIds[child + 1]]) ? child : child + 1;
	}

	while (child <= this->mLength && MESSAGE_ARRAY[this->mMIds[child]] < MESSAGE_ARRAY[this->mMIds[parent]]) {
		this->_Swap(parent, child);
		parent = child;
		child = parent << 1;
		if (child + 1 <= this->mLength) {
			// MAX_HEAP
			child = (MESSAGE_ARRAY[this->mMIds[child]] < MESSAGE_ARRAY[this->mMIds[child + 1]]) ? child : child + 1;
		}
	}

	return last_mId;
}

// FIXED Array

_fixedarray::_fixedarray() {
	this->mLength = 0;
}

void _fixedarray::PushBack(const int mId) {
	if (this->mLength == MAXM) {
		this->mMIds[MAXM] = mId;
		return;
	}

	this->mMIds[this->mLength] = mId;
	this->mLength++;

	this->Sort();
}

bool _fixedarray::Delete(const int mId) {
	int found = -1;

	for (int i = 0; i < MAXM; ++i) {
		if (this->mMIds[i] == mId) {
			found = i;
			break;
		}
	}

	if (found != -1) {
		this->mMIds[found] = this->mMIds[2];
		this->mLength--;

		this->Sort();

		return 1;
	}

	return 0;
}

void _fixedarray::Sort() {
	if (this->mLength < 2) {
		return;
	}

	for (register int i = 0; i < this->mLength; ++i) {
		for (register int j = i + 1; j < this->mLength; ++j) {
			if (MESSAGE_ARRAY[this->mMIds[i]] < MESSAGE_ARRAY[this->mMIds[j]]) {
				this->mMIds[i] = this->mMIds[i] ^ this->mMIds[j];
				this->mMIds[j] = this->mMIds[i] ^ this->mMIds[j];
				this->mMIds[i] = this->mMIds[i] ^ this->mMIds[j];
			}
		}
	}
}

void _fixedarray::Clear() {
	this->mLength = 0;
}

int _fixedarray::operator[](const int index) {
	return this->mMIds[index];
}


void UpdateMessages(const int currentTs) {
	if (SENTBOX_PQ.mLength == 0) {
		return;
	}
	int mId = SENTBOX_PQ.GetFirst();
	int scheduledTs = MESSAGE_ARRAY[mId].mSchTs;
	int nextMid = NO_ID;
	int uId = NO_ID;

	while (scheduledTs <= currentTs) {
		mId = SENTBOX_PQ.Pop();
		INBOX_PQ.Push(mId);

		uId = MESSAGE_ARRAY[mId].mReceiverId;
		USER_ARRAY[uId].mInbox.PushBack(mId);

		nextMid = SENTBOX_PQ.GetFirst();
		scheduledTs = MESSAGE_ARRAY[nextMid].mSchTs;
	}
}