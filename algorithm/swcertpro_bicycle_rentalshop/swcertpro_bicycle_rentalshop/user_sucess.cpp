//#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#define print printf
int cmd;
#endif
 
#define USE_QUEUE
 
#define MAXN 100007
#define MAX_USER 10007
#define MAX_BIC 20007
#define MAX_STATION 101
 
#define rint register int
typedef unsigned long long ull;
 
struct NODE {
    int runTime;
    int startTime;
    int validTime;
} _Node[MAXN];
 
int nIdx;
NODE *new_node() { return &_Node[nIdx++]; }
 
struct MINHEAP {
    NODE *heap[MAX_BIC];
    int heapSize = 0;
 
    void heapInit(void)
    {
        heapSize = 0;
    }
 
    int heapPush(NODE *node)
    {
        if (heapSize + 1 > MAX_BIC)
        {
#ifdef DEBUG
            print("queue is full!");
#endif
            return 0;
        }
 
        heap[heapSize] = node;
 
        rint current = heapSize;
        while (current > 0 && heap[current]->runTime < heap[(current - 1) / 2]->runTime)
        {
            NODE *temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;
            current = (current - 1) / 2;
        }
 
        heapSize = heapSize + 1;
 
        return 1;
    }
 
    NODE *heapPop()
    {
        if (heapSize <= 0)
        {
            return 0;
        }
 
        NODE *node = heap[0];
        heapSize = heapSize - 1;
 
        heap[0] = heap[heapSize];
 
        rint current = 0;
        while (current * 2 + 1 < heapSize)
        {
            rint child;
            if (current * 2 + 2 == heapSize)
            {
                child = current * 2 + 1;
            }
            else
            {
                child = heap[current * 2 + 1]->runTime < heap[current * 2 + 2]->runTime ? current * 2 + 1 : current * 2 + 2;
            }
 
            if (heap[current]->runTime < heap[child]->runTime)
            {
                break;
            }
 
            NODE *temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
 
            current = child;
        }
        return node;
    }
};
 
#ifndef USE_QUEUE
struct WAITQ {
    NODE *heap[MAX_BIC];
    int heapSize = 0;
 
    void init(void)
    {
        heapSize = 0;
    }
 
    int push(NODE *node)
    {
        if (heapSize + 1 > MAX_BIC)
        {
#ifdef DEBUG
            print("queue is full!");
#endif
 
            return 0;
        }
 
        heap[heapSize] = node;
 
        rint current = heapSize;
        while (current > 0 && heap[current]->validTime < heap[(current - 1) / 2]->validTime)
        {
            NODE *temp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = temp;
            current = (current - 1) / 2;
        }
 
        heapSize = heapSize + 1;
 
        return 1;
    }
 
    NODE *pop()
    {
        if (heapSize <= 0)
        {
            return 0;
        }
 
        NODE *node = heap[0];
        heapSize = heapSize - 1;
 
        heap[0] = heap[heapSize];
 
        rint current = 0;
        while (current * 2 + 1 < heapSize)
        {
            rint child;
            if (current * 2 + 2 == heapSize)
            {
                child = current * 2 + 1;
            }
            else
            {
                child = heap[current * 2 + 1]->validTime < heap[current * 2 + 2]->validTime ? current * 2 + 1 : current * 2 + 2;
            }
 
            if (heap[current]->validTime < heap[child]->validTime)
            {
                break;
            }
 
            NODE *temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
 
            current = child;
        }
        return node;
    }
 
    NODE *top()
    {
        if (heapSize <= 0)
        {
            return 0;
        }
 
        NODE *node = heap[0];
        return node;
    }
};
#else
struct WAITQ {
    NODE *queue[MAX_BIC];
    int front;
    int rear;
 
    void init()
    {
        front = rear = 0;
    }
 
    void push(NODE *node)
    {
        queue[rear++] = node;
    }
 
    NODE *pop()
    {
        if (front == rear)
            return 0;
 
        return queue[front++];
    }
 
    NODE *top()
    {
        if (front == rear)
            return 0;
 
        return queue[front];
    }
};
#endif
 
struct STATION {
    int deliveryTime;
    int totalNum; // total 자전거 수
    int newNum; // 새 자전거 수
    MINHEAP usedBic; // 사용한 자전거
    WAITQ waitBic;  // 배달 중인 자전거 
};
 
STATION Station[MAX_STATION];
 
int DurableTime;
int N;
 
struct USER {
    ull id;
    int validTime;
    int endTime;
    NODE *bic;
    USER *prev;
} _User[MAX_USER];
 
USER User[MAX_USER];
 
int uIdx;
USER *new_user() { return &_User[uIdx++]; }
USER *get_user(ull id)
{
    rint key = id % MAX_USER;
 
    for (register USER *user = User[key].prev; user; user = user->prev) {
        if (user->id == id)
            return user;
    }
 
    return 0;
}
 
ull getHash(const char *str)
{
    register ull hash = 0;
    rint c;
 
    while (c = *str++)
    {
        hash = (((hash << 5) + hash) + c - 'a' + 1);
    }
 
    return hash;
}
 
void init(int _N, int durableTime, int deliveryTimes[])
{
#ifdef DEBUG
    cmd = 0;
    print("(%d) %s : N=%d, durableTime=%d\n", ++cmd, __func__, _N, durableTime);
#endif
 
    N = _N;
    DurableTime = durableTime;
    uIdx = nIdx = 0;
 
    for (rint i = 0; i <= N; i++) {
        Station[i].deliveryTime = deliveryTimes[i];
        Station[i].totalNum = Station[i].newNum = 0;
        Station[i].usedBic.heapInit();
        Station[i].waitBic.init();
    }
 
    for (rint i = 0; i < MAX_USER; i++) {
        User[i].prev = 0;
    }
}
 
void addBicycle(int cTimestamp, int pID, int bicycleNum)
{
#ifdef DEBUG
    print("(%d) %s : time=%d, pID=%d, num=%d\n", ++cmd, __func__, cTimestamp, pID, bicycleNum);
#endif
 
    Station[pID].totalNum += bicycleNum;
    Station[pID].newNum += bicycleNum;
}
 
void buyTicket(int cTimestamp, char uName[], int validTime)
{
#ifdef DEBUG
    print("(%d) %s : time=%d, name=%s, validTime=%d\n", ++cmd, __func__, cTimestamp, uName, validTime);
#endif
 
    ull id = getHash(uName);
    int key = id % MAX_USER;
    USER *user = get_user(id);
 
    if (!user) {
        user = new_user();
        user->id = id;
        user->bic = 0;
        user->validTime = 0;
        user->endTime = 0;
        user->prev = User[key].prev;
        User[key].prev = user;
    }
 
    user->validTime = validTime;
    if (user->endTime >= cTimestamp)
        user->endTime += validTime;
    else user->endTime = cTimestamp + validTime - 1;
}
 
/*
  ① 해당 고객이 반납하지 않은 빌린 자전거가 있을 때
  ② 해당 대여소에 자전거가 남아있지 않을 때
  ③ 해당 고객이 이용권을 소지하고 있지 않거나 유효기간이 지난 이용권을 소지하고 있을 때
  Returns
   대여에 성공하면 대여한 자전거의 운행 시간을 반환한다. 실패하면 -1을 반환한다.
  */
int rentBicycle(int cTimestamp, char uName[], int pID)
{
#ifdef DEBUG
    print("(%d) %s : time=%d, name=%s, pID=%d\n", ++cmd, __func__, cTimestamp, uName, pID);
#endif
 
    ull id = getHash(uName);
    USER *user = get_user(id);
 
    if (!user) return -1;
    if (user->endTime < cTimestamp) return -1;
    if (user->bic) return -1;
    if (Station[pID].totalNum == 0) return -1;
 
    if (Station[pID].newNum) {
        NODE *node = new_node();
        node->runTime = 0;
        node->startTime = cTimestamp;
        node->validTime = 0;
        user->bic = node;
        Station[pID].newNum--;
        Station[pID].totalNum--;
    }
    else {
        if (Station[pID].waitBic.top() && Station[pID].waitBic.top()->validTime <= cTimestamp) {
            user->bic = Station[pID].waitBic.pop();
            user->bic->startTime = cTimestamp;
            Station[pID].totalNum--;
        }
        else if (Station[pID].usedBic.heapSize) {
            user->bic = Station[pID].usedBic.heapPop();
            user->bic->startTime = cTimestamp;
            Station[pID].totalNum--;
        }
    }
 
    if (!user->bic) return -1;
    return user->bic->runTime;
}
 
/*
  ① 고객이 빌린 자전거가 없어 반납이 불가능한 경우 -1을 반환한다.
  ② 고객이 빌린 자전거가 있고 소지하고 있는 이용권의 유효 기간이 지나지 않은 경우 0을 반환한다.
  ③ 고객이 빌린 자전거가 있고 소지하고 있는 이용권의 유효 기간이 지난 경우 연체된 시간을 반환한다.
  Returns
   고객이 빌린 자전거가 없는 경우 -1을 반환한다.
   고객이 빌린 자전거가 있고 소지하고 있는 이용권이 만료되지 않은 경우 0을 반환한다.
   고객이 빌린 자전거가 있고 소지하고 있는 이용권이 만료된 경우 연체된 시간을 반환한다.
  */
int returnBicycle(int cTimestamp, char uName[], int pID)
{
#ifdef DEBUG
    print("(%d) %s : time=%d, name=%s, pID=%d\n", ++cmd, __func__, cTimestamp, uName, pID);
#endif
 
    ull id = getHash(uName);
    USER *user = get_user(id);
 
    if (!user) return -1;
    if (!user->bic) return -1;
 
    user->bic->runTime += cTimestamp - user->bic->startTime;
 
    if (user->bic->runTime <= DurableTime) {
        Station[pID].usedBic.heapPush(user->bic);
    }
    else {
        NODE *node = new_node();
        node->runTime = 0;
        node->startTime = 0;
        node->validTime = cTimestamp + Station[pID].deliveryTime;
        Station[pID].waitBic.push(node);
    }
 
    Station[pID].totalNum++;
    user->bic = 0;
 
    return (user->endTime >= cTimestamp) ? 0 : (cTimestamp - user->endTime);
}