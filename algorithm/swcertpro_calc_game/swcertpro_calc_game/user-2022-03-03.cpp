#include <deque>

using namespace std;

const int MAX_CARD = 50000;
const int LEFT = 0;
const int RIGHT = 1;
const int JOKER_RANGE = 20;
const int RESULT_RANGE = 20;

typedef struct _table {
	int joker;
	int begin, end;
	int cards[MAX_CARD * 2 + 5];
	deque<int> idxList[JOKER_RANGE][RESULT_RANGE];

	void init(int mJoker, int mNumbers[5]);
	void updateIdx(int idx, int mdir);
	void push_front(int mNumbers[5]);
	void push_back(int mNumbers[5]);
	int find(int mNum, int mNth);
	void changeJoker(int mJoker);
} Table;

Table t;

void init(int mJoker, int mNumbers[5]) {
	t.init(mJoker, mNumbers);
}

void putCards(int mDir, int mNumbers[5]) {
	if (mDir == LEFT) {
		t.push_front(mNumbers);
	}
	else {
		t.push_back(mNumbers);
	}
}

int findNumber(int mNum, int mNth, int ret[4]) {
	int idx = t.find(mNum, mNth);
	if (idx == -1) {
		return 0;
	}

	for (int i = 0; i < 4; i++) {
		ret[i] = t.cards[idx + i];
	}

	return 1;
}

void changeJoker(int mValue) {
	t.changeJoker(mValue);
}

// Implementation

void _table::updateIdx(int cardIndex, int mdir) {
	int sum = 0;
	int joker_cnt = 0;
	for (int i = 0; i < 4; i++) {
		if (cards[cardIndex + i] == -1) {
			joker_cnt++;
		}
		else {
			sum += cards[cardIndex + i];
		}
	}

	for (int joker_i = 0; joker_i < JOKER_RANGE; joker_i++) {
		int result = (sum + (joker_cnt * joker_i)) % RESULT_RANGE;
		if (mdir == LEFT) {
			idxList[joker_i][result].push_front(cardIndex);
		}
		else {
			idxList[joker_i][result].push_back(cardIndex);
		}
	}
}

void _table::init(int mJoker, int mNumbers[5]) {
	joker = mJoker % RESULT_RANGE;
	begin = end = MAX_CARD;

	for (int joker_i = 0; joker_i < JOKER_RANGE; joker_i++) {
		for (int result_i = 0; result_i < RESULT_RANGE; result_i++) {
			idxList[joker_i][result_i].clear();
		}
	}

	for (int i = 0; i < 5; i++) {
		cards[end + i] = mNumbers[i];
	}
	end += 5;
	for (int i = 0; i < 2; i++) {
		updateIdx(MAX_CARD + i, RIGHT);
	}
}

void _table::push_front(int mNumbers[5]) {
	begin -= 5;
	for (int i = 0; i < 5; i++) {
		cards[begin + i] = mNumbers[i];
	}
	int target = begin;
	for (int i = 4; i >= 0; i--) {
		updateIdx(target + i, LEFT);
	}
}

void _table::push_back(int mNumbers[5]) {
	for (int i = 0; i < 5; i++) {
		cards[end + i] = mNumbers[i];
	}
	int target = end - 3;
	end += 5;
	for (int i = 0; i < 5; i++) {
		updateIdx(target + i, RIGHT);
	}
}

int _table::find(int mNum, int mNth) {
	auto& list = idxList[joker][mNum];
	if ((size_t)mNth > list.size()) {
		return -1;
	}

	return list[mNth - 1];
}

void _table::changeJoker(int mJoker) {
	joker = mJoker % RESULT_RANGE;
}