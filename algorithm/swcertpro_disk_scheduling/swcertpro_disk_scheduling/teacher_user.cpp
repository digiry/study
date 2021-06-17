#include <vector>
#include <queue>

#define SCALE 100
#define LEFTMIN -200000
#define RIGHTMAX 300000

using namespace std;

vector<int> disks[100000 / SCALE +5];
queue<int> Q;

const bool LEFT = false;
const bool RIGHT = true;

const bool DELETED = true;
const bool EXISTED = false;

int N, H;
bool dir, flag[100005];

void remove(int val) {
  for (int i = 0; i < disks[val / SCALE].size(); ++i) {
    if (disks[val / SCALE][i] == val) {
      disks[val / SCALE].erase(disks[val / SCALE].begin() + i);
      break;
    }
  }
}

int findLeft(int val);
int findRight(int val);
  
void init(int track_size, int head) {
  N = track_size;
  H = head;
  dir = LEFT;
  
  for (int i = 0; i < (100000 / SCALE + 5); ++i) {
    disks[i].clear();
  }
  
  for (int i = 0; i <= track_size; ++i) {
    flag[i] = EXISTED;
  }
  
  while (Q.empty() == false) {
    Q.pop();
  }
}

void request(int track) {
  Q.push(track);
  disks[track / SCALE].push_back(track);
}

int fcfs() {
  int qValue;
  
  while (Q.empty() == false) {
    qValue = Q.front();
    Q.pop();
    
    if (flag[qValue] == EXISTED) {
      break;
    }
  }
  
  flag[qValue] = DELETED;
  remove(qValue);
  
  return H = qValue;
}

int sstf() {
  int left = findLeft(H);
  int right = findRight(H);
  
  // #define LEFTMIN -200000
  // #define RIGHTMAX 300000
  // 아래 조건처리로 매우 작은 값, 매우 큰 값으로 함
  // left를 못찾으면 H-left는 어떤 right-H 보다 크다.
  if (H - left <= right - H) {
    H = left;
  }
  else {
    H = right;
  }
  
  flag[H] = DELETED;
  remove(H);
  
  return H;
}

int look() {
  int left = findLeft(H);
  int right = findRight(H);
  
  if (dir == LEFT) {
    H = left;
    
    if (left == LEFTMIN) {
      dir = RIGHT;
      H = right;
    }
  }
  else {
    H = right;
    
    if (right == RIGHTMAX) {
      dir = LEFT;
      H = left;
    }
  }
  
  flag[H] = DELETED;
  remove(H);
  
  return H;
}

int clook() {
  int left = findLeft(H);
  
  if (left == LEFTMIN) {
    left = findLeft(N);
  }
  
  H = left;
  flag[H] = DELETED;
  remove(H);
  
  return H;
}

int findLeft(int val) {
  int max = LEFTMIN;
  
  for (int i = val / SCALE; i >= 0 && max == LEFTMIN; --i) {
    for (int j = 0; j < disks[i].size(); ++j) {
      if (disks[i][j] <= val) {
        if (max < disks[i][j]) {
          max = disks[i][j];
        }
      }
    }
  }
  
  return max;
}

int findRight(int val) {
  int min = RIGHTMAX;
  
  for (int i = val / SCALE; i <= N / SCALE && min == RIGHTMAX; ++i) {
    for (int j = 0; j < disks[i].size(); ++j) {
      if (disks[i][j] >= val) {
        if (min > disks[i][j]) {
          min = disks[i][j];
        }
      }
    }
  }
  
  return min;
}



























