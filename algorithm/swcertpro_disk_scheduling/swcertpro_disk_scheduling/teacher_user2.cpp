#define SCALE 100
#define LEFTMIN -200000
#define RIGHTMAX 300000

typedef struct Node {
  int data;
  int next;
};

int Head[100000 / SCALE + 5];
Node List[100005];
int queue[100005], front, rear;
int N, H, M;
bool flag[100005];
bool dir;

const bool LEFT = false;
const bool RIGHT = true;

const bool DELETED = true;
const bool EXISTED = false;

int findLeft(int val);
int findRight(int val);

void add(int val) {
  List[M].data = val;
  List[M].next = Head[val / SCALE];
  Head[val / SCALE] = M++;
}

void remove(int val) {
  int prev = 0;
  int cur = Head[val / SCALE];
  
  while (cur) {
    if (List[cur].data == val) {
      if (prev == 0) {
        Head[val/SCALE] = List[cur].next;
      }
      else {
        List[prev].next = List[cur].next;
      }
      break;
    }
    
    prev = cur;
    cur = List[cur].next;
  }
}
  
void init(int track_size, int head) {
  N = track_size;
  H = head;
  M = 1;
  dir = LEFT;
  front = rear = 0;
  
  for (int i = 0; i < (100000 / SCALE + 5); ++i) {
    Head[i] = 0;
  }
  
  for (int i = 0; i <= track_size; ++i) {
    flag[i] = EXISTED;
  }
  
  while (Q.empty() == false) {
    Q.pop();
  }
}

void request(int track) {
  queue[rear++] = track;
  add(track);
}

int fcfs() {
  int qValue;
  
  while (front < rear) {
    qValue = queue[front++];
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
    int cur = Head[i];
    
    while (cur) {
      if (List[cur].data <= val) {
        if (max < List[cur].data) {
          max = List[cur].data;
        }
      }
      
      cur = List[cur].next;
    }
  }
  
  return max;
}

int findRight(int val) {
  int min = RIGHTMAX;
  
  for (int i = val / SCALE; i <= N / SCALE && min == RIGHTMAX; ++i) {
    int cur = Head[i];
    
    while (cur) {
      if (List[cur].data >= val) {
        if (min > List[cur].data) {
          min = List[cur].data;
        }
      }
      cur = List[cur].next;
    }
  }
  
  return min;
}



























