#include <iostream>

using namespace std;

#define MAX_HEAP 100001

struct DATA {
    long long name;
    int idx;
    int pos;
}a[MAX_HEAP];

DATA* heap[MAX_HEAP];
int heapSize = 0;

//name이사전 순으로 큰 Data
//name이같은 경우 idx가 작은 Data를 삭제하고 idx를 반환한다.
int check(register DATA* heap1, register DATA* heap2)
{
    if (heap1->name > heap2->name || (heap1->name == heap2->name && heap1->idx < heap2->idx))
        return 1;
    return 0;
}

int heapPush(register int n)
{
    if (heapSize + 1 > MAX_HEAP)
    {
        return 0;
    }

    register int current = n;
    while (current > 0 && check(heap[current], heap[(current - 1) / 2]))
    {
        //heap에서 pos를 바꿔주자
        heap[current]->pos = (current - 1) / 2;
        heap[(current - 1) / 2]->pos = current;

        register DATA* temp = heap[(current - 1) / 2];
        heap[(current - 1) / 2] = heap[current];
        heap[current] = temp;
        current = (current - 1) / 2;
    }
    return 1;
}

int heapPop(register int n)
{
    if (heapSize <= 0)
    {
        return -1;
    }

    register int current = n;
    while (current * 2 + 1 < heapSize)
    {
        register int child;
        if (current * 2 + 2 == heapSize)
        {
            child = current * 2 + 1;
        }
        else
        {
            child = check(heap[current * 2 + 1], heap[current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
        }

        if (check(heap[current], heap[child]))
        {
            break;
        }

        //heap에서 pos를 바꿔주자
        heap[current]->pos = child;
        heap[child]->pos = current;

        register DATA* temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;

        current = child;
    }
    return 1;
}

long long str2ll(const char* str)
{
    register long long h = 0; register int i = 0;
    while (*str)
    {
        h = (h << 5) + *str++ - 'a' + 1;
        i++;
    }
    //return h;
    return h = h << (12 - i) * 5;  //사전순으로 나타내기 위해서는 길이를 따져봐야한다
}

void PrintHeap() {
    cout << "=== HEAP ===" << endl;

    for (register int i = 0; i < heapSize; ++i) {
        cout << "[" << i+1 << "] " << heap[i]->idx << " / idx: " << heap[i]->idx << " name: " << heap[i]->name << " heap_idx: " << heap[i]->pos + 1 << endl;
    }

    cout << endl;
}

void init()
{
    heapSize = 0;
}
void clear()
{
    heapSize = 0;
    PrintHeap();
}
//name은 3에서 10자리의 영어 소문자 문자열이다. long long커퍼가능 숫자로 변경하자
void push(register int idx, register char name[])
{
    register DATA* tmp = &a[idx];
    tmp->name = str2ll(name);
    tmp->idx = idx;
    tmp->pos = heapSize;

    heap[heapSize] = tmp;
    heapPush(heapSize);

    heapSize++;
    PrintHeap();
}

int pop()
{
    register DATA* value = heap[0];
    heapSize = heapSize - 1;

    heap[0] = heap[heapSize];
    heap[0]->pos = 0;
    heapPop(0);
    PrintHeap();
    return value->idx;
}
void mod(register int idx, register char name[])
{
    register int pos = a[idx].pos;
    heap[pos]->name = str2ll(name);
    heapPush(pos);
    heapPop(pos);
    PrintHeap();
}