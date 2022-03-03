#include <deque>

using namespace std;

#define MAX_CARD 50000

struct Table {
	int joker;
	int begin, end;
	int cards[MAX_CARD * 2 + 5];
	deque<int> idxList[20][20];

	void updateIdx(int idx, int mdir) {
		int sum = 0;
		int joker_cnt = 0;
		for (int i = 0; i < 4; i++) {
			if (cards[idx + i] == -1) {
				joker_cnt++;
			}
			else {
				sum += cards[idx + i];
			}
		}

		for (int i = 0; i < 20; i++) {
			int num = (sum + (joker_cnt * i)) % 20;
			if (mdir == 0) {
				idxList[i][num].push_front(idx);
			}
			else {
				idxList[i][num].push_back(idx);
			}
		}
	}

	void init(int mJoker, int mNumbers[5]) {
		joker = mJoker % 20;
		begin = end = MAX_CARD;

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				idxList[i][j].clear();
			}
		}

		for (int i = 0; i < 5; i++) {
			cards[end + i] = mNumbers[i];
		}
		end += 5;
		for (int i = 0; i < 2; i++) {
			updateIdx(MAX_CARD + i, 1);
		}
	}

	void push_front(int mNumbers[5]) {
		begin -= 5;
		for (int i = 0; i < 5; i++) {
			cards[begin + i] = mNumbers[i];
		}
		int target = begin;
		for (int i = 4; i >= 0; i--) {
			updateIdx(target + i, 0);
		}
	}

	void push_back(int mNumbers[5]) {
		for (int i = 0; i < 5; i++) {
			cards[end + i] = mNumbers[i];
		}
		int target = end - 3;
		end += 5;
		for (int i = 0; i < 5; i++) {
			updateIdx(target + i, 1);
		}
	}

	int find(int mNum, int mNth) {
		auto& list = idxList[joker][mNum];
		if (mNth > list.size()) {
			return -1;
		}

		return list[mNth - 1];
	}

	void changeJoker(int mJoker) {
		joker = mJoker % 20;
	}
};

Table t;

void init(int mJoker, int mNumbers[5]) {
	t.init(mJoker, mNumbers);
}

void putCards(int mDir, int mNumbers[5]) {
	if (mDir == 0) {
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