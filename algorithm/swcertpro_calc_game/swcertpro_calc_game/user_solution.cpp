#define OFFSET  50000
#define MOD     20

int number[OFFSET * 2 + 5];
int num_front, num_rear;

int position[MOD][MOD][2000];
int pos_front[MOD][MOD], pos_rear[MOD][MOD];

int joker;

void add_position(int num[], int pos, int dir) {
  int n_joker = 0;
  int sum = 0;
  
  for (register int i = 0; i < 4; i++) {
    if (num[i] == -1) {
      n_joker++;
    }
    else {
      sum += num[i];
    }
  }
  
  for (register int i = 0; i < MOD; i++) {
    int n = (sum + n_joker * i) % 20;
    if (dir == 0) {
      position[n][i][--pos_rear[n][i]] = pos;
    }
    else {
      position[n][i][pos_front[n][i]++] = pos;
    }
  }
}

void init(int mJoker, int mNumbers[5]) {
  joker = mJoker % 20;
  
  num_front = num_rear = OFFSET;
  for (register int i = 0; i < MOD; i++) {
    for (register int j = 0; j < MOD; j++) {
      pos_front[i][j] = pos_rear[i][j] = 1000;
    }
  }
  
  for (register int i = 0; i < 5; i++) {
    number[num_front++] = mNumbers[i];
  }
  
  add_position(&number[OFFSET], OFFSET, 1);
  add_position(&number[OFFSET + 1], OFFSET + 1, 1);
}

void putCards(int mDir, int mNumbers[5]) {
  if (mDir == 0) {
    for (register int i = 4; i >= 0; i--) {
      number[--num_rear] = mNumbers[i];
      add_position(&number[num_rear], num_rear, 0);
    }
  }
  else {
    for (register int i = 0; i < 5; i++) {
      number[num_front++] = mNumbers[i];
      add_position(&number[num_front - 4], num_front - 4, 1);
    }
  }
}

int findNumber(int mNum, int mNth, int ret[4]) {
  if (pos_front[mNum][joker] - pos_rear[mNum][joker] < mNth) {
    return 0;
  }
  
  int pos = position[mNum][joker][pos_rear[mNum][joker] + mNth - 1];
  for (register int i = 0; i < 4; i++) {
    ret[i] = number[pos + i];
  }
  
  return 1;
}

void changeJoker(int mValue) {
  joker = mValue % 20;
}