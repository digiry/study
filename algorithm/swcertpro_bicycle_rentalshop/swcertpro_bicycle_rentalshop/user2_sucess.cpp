#define MAXN        100
#define MAXL        8
#define MAXBICYCLE ( 20000 )
#define MAXHTABLE ( 10000 + 100 )
 
typedef unsigned long long ull;
 
struct Bicycle {
 
    int cTimestamp;
    int usedTime;
 
}bicycle[MAXBICYCLE * 2];
int nBicycle;
 
struct Heap {
    Bicycle* b;
};
 
struct Waitlist {
    int pID;
    int Time;
};
 
struct Station {
 
    int ID;
    int durableTime;
    int deliveryTimes;
    int heapSize;
    int nWlist;
    Heap heap[MAXBICYCLE/2];
    Waitlist wlist[MAXBICYCLE/2];
}station[MAXN];
 
int nStation;
 
struct hTable {
    int key;
    ull name;
    int validTime;
    Bicycle* b;
}ht[MAXHTABLE];
 
bool check(Heap* h1, Heap* h2) {
    return h1->b->usedTime < h2->b->usedTime;
}
 
int heapPush(Bicycle* b, Station* s)
{
    int heapSize = s->heapSize;
    Heap* heap = s->heap;
 
    if (heapSize + 1 > MAXBICYCLE)
    {
        return 0;
    }
 
    heap[heapSize].b = b;
 
    register int current = heapSize;
    while (current > 0 && check(&heap[current], &heap[(current - 1) / 2]))
    {
        Heap temp = heap[(current - 1) / 2];
        heap[(current - 1) / 2] = heap[current];
        heap[current] = temp;
        current = (current - 1) / 2;
    }
 
    s->heapSize = s->heapSize + 1;
 
    return 1;
}
 
int heapPop(Heap* h, Station* s)
{
    int heapSize = s->heapSize;
    Heap* heap = s->heap;
 
    if (heapSize <= 0)
    {
        return -1;
    }
 
    h->b = heap[0].b;
    heapSize = heapSize - 1;
    s->heapSize -= 1;
 
    heap[0] = heap[heapSize];
 
    register int current = 0;
    while (current * 2 + 1 < heapSize)
    {
        register int child;
        if (current * 2 + 2 == heapSize)
        {
            child = current * 2 + 1;
        }
        else
        {
            child = check(&heap[current * 2 + 1], &heap[current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
        }
 
        if (check(&heap[current], &heap[child]))
        {
            break;
        }
 
        Heap temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;
 
        current = child;
    }
    return 1;
}
 
bool check2(Waitlist* w1, Waitlist* w2) {
    return w1->Time < w2->Time;
}
 
int wheapPush(Waitlist* w, Station* s)
{
    int heapSize = s->nWlist;
    Waitlist* heap = s->wlist;
 
    if (heapSize + 1 > MAXBICYCLE)
    {
        return 0;
    }
/*
    heap[heapSize].pID = w->pID;
    heap[heapSize].Time = w->Time;
*/
    heap[heapSize] = { w->pID, w->Time };
    register int current = heapSize;
    while (current > 0 && check2(&heap[current], &heap[(current - 1) / 2]))
    {
        Waitlist temp = heap[(current - 1) / 2];
        heap[(current - 1) / 2] = heap[current];
        heap[current] = temp;
        current = (current - 1) / 2;
    }
 
    s->nWlist = s->nWlist + 1;
 
    return 1;
}
 
int wheapPop(Waitlist* w, Station* s)
{
    int heapSize = s->nWlist;
    Waitlist* heap = s->wlist;
 
    if (heapSize <= 0)
    {
        return -1;
    }
/*
    w->pID = heap[0].pID;
    w->Time = heap[0].Time;
*/
    w = &heap[0];
    heapSize = heapSize - 1;
    s->nWlist -= 1;
 
    heap[0] = heap[heapSize];
 
    register int current = 0;
    while (current * 2 + 1 < heapSize)
    {
        register int child;
        if (current * 2 + 2 == heapSize)
        {
            child = current * 2 + 1;
        }
        else
        {
            child = check2(&heap[current * 2 + 1], &heap[current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
        }
 
        if (check2(&heap[current], &heap[child]))
        {
            break;
        }
 
        Waitlist temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;
 
        current = child;
    }
    return 1;
}
 
 
Bicycle* getBicycle(int cTimestamp) {
 
    Bicycle* b = &bicycle[nBicycle++];
 
    b->cTimestamp = cTimestamp;
    b->usedTime = 0;
 
    return b;
}
 
ull changestrToull(char* in) {
 
    register char* it = in;
    register ull num = 0;
 
    while (*it != '\0') {
 
        num = (num << 6) + (*it - 'a' + 1);
        it++;
    }
    return num;
}
 
/*
void Processing(int cTimestamp) {
 
    for (register int i = 0; i < nStation; i++) {
        while (station[i].nWlist > 0 && cTimestamp >= station[i].wlist[0].Time) {
            Waitlist w;
            Bicycle* b = getBicycle(cTimestamp);
            wheapPop(&w, &station[i]);
 
            b->cTimestamp = w.Time;
            b->usedTime = 0;
 
            heapPush(b, &station[i]);
        }
    }
}
*/
void Processing(int cTimestamp, int pID) {
 
    while (station[pID].nWlist > 0 && cTimestamp >= station[pID].wlist[0].Time) {
        Waitlist w;
        Bicycle* b = getBicycle(cTimestamp);
        wheapPop(&w, &station[pID]);
 
        b->cTimestamp = w.Time;
        b->usedTime = 0;
 
        heapPush(b, &station[pID]);
    }
 
}
 
 
void init(int N, int durableTime, int deliveryTimes[MAXN])
{
    nStation = N;
    nBicycle = 0;
 
    for (register int i = 0; i < N; i++) {
        station[i] = { i, durableTime,deliveryTimes[i], 0, 0 };
    }
 
    for (register int i = 0; i < MAXHTABLE; i++) {
        ht[i] = { -1, 0, 0, nullptr };
    }
}
 
void addBicycle(int cTimestamp, int pID, int bicycleNum)
{
    for (register int i = 0; i < bicycleNum; i++) {
        Bicycle* b = getBicycle(cTimestamp);
        heapPush(b, &station[pID]);
    }
}
 
void buyTicket(int cTimestamp, char uName[MAXL], int validTime)
{
    ull name = changestrToull(uName);
    register int h = name % MAXHTABLE;
 
    while (ht[h].key != -1 && ht[h].name != name) {
        h = (h + 1) % MAXHTABLE;
    }
    if (ht[h].key == -1) {
        ht[h].key = h;
        ht[h].name = name;
        ht[h].b = nullptr;
    }
 
    if (cTimestamp > ht[h].validTime) {
        ht[h].validTime = cTimestamp + validTime;
    }
    else {
        ht[h].validTime = ht[h].validTime + validTime;
    }
}
 
int rentBicycle(int cTimestamp, char uName[MAXL], int pID)
{
    ull name = changestrToull(uName);
    register int h = name % MAXHTABLE;
 
    if (ht[h].key == -1) return -1;
 
    while (ht[h].name != name) {
        if (ht[h].key == -1) return -1;
        else {
            h = (h + 1) % MAXHTABLE;
        }
    }
    //  Processing(cTimestamp);
    Processing(cTimestamp, pID);
 
    if (ht[h].b != nullptr) return -1;
    if (station[pID].heapSize == 0) return -1;
    if (ht[h].validTime <= cTimestamp) return -1;
 
    Heap tmp;
    heapPop(&tmp, &station[pID]);
 
    ht[h].b = tmp.b;
    ht[h].b->cTimestamp = cTimestamp;
 
    return ht[h].b->usedTime;
}
 
int returnBicycle(int cTimestamp, char uName[MAXL], int pID)
{
    ull name = changestrToull(uName);
    register int h = name % MAXHTABLE;
 
    if (ht[h].key == -1) return -1;
 
    while (ht[h].name != name) {
        if (ht[h].key == -1) return -1;
        else {
            h = (h + 1) % MAXHTABLE;
        }
    }
 
    if (ht[h].b == nullptr) return -1;
 
    Bicycle* b = ht[h].b;
    ht[h].b = nullptr;
    b->usedTime = b->usedTime + (cTimestamp - b->cTimestamp);
 
    if (station[pID].durableTime < b->usedTime) {
        Waitlist w;
        w.pID = pID;
        w.Time = cTimestamp + station[pID].deliveryTimes;
        wheapPush(&w, &station[pID]);
    }
    else {
        heapPush(b, &station[pID]);
    }
 
    if (cTimestamp < ht[h].validTime) return 0;
    else {
        return cTimestamp - (ht[h].validTime - 1);
    }
}