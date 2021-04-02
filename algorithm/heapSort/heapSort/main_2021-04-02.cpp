#include <iostream>

using namespace std;

const int HEAP_SIZE = 20;
const int OVER_ROOT = 0;
const int ROOT_INDEX = 1;

int HEAP[HEAP_SIZE] = {
    -1,
};
int HEAP_COUNT = 0;

typedef struct _User
{
  char mName[20];
  int mWeight;
} User;

User MEMBERS[20] = {
    {"abc", 6},
    {"efg", 28},
    {"hij", 3},
    {"klm", 2},
    {"nop", 50},
    {"qst", 15},
    {"uvw", 30},
};

const int MEMBERS_LENGTH = 7;

void PrintHeap()
{
  const int pows2[] = {1, 2, 4, 8, 16, 32, 64};
  int nextLevel = 0;

  for (int i = 1; i <= HEAP_COUNT; i++)
  {
    if (i == pows2[nextLevel])
    {
      cout << endl;
      nextLevel++;
    }

    cout << HEAP[i] << "-" << MEMBERS[HEAP[i]].mWeight << ' ';
  }
  cout << endl;
}

void Swap(int *const pArr, const int a_index, const int b_index)
{
  if (a_index == b_index)
  {
    return;
  }

  pArr[a_index] = pArr[a_index] ^ pArr[b_index];
  pArr[b_index] = pArr[a_index] ^ pArr[b_index];
  pArr[a_index] = pArr[a_index] ^ pArr[b_index];
}

void Push(const int user_index)
{
  HEAP_COUNT++;
  HEAP[HEAP_COUNT] = user_index;
  int child = HEAP_COUNT;
  int parent = child >> 1;

  while (parent > OVER_ROOT && MEMBERS[HEAP[parent]].mWeight > MEMBERS[HEAP[child]].mWeight)
  {
    Swap(HEAP, parent, child);
    child = parent;
    parent = child >> 1;
  }
}

int Pop()
{
  int parent = ROOT_INDEX;
  int min_index = HEAP[parent];
  HEAP[parent] = HEAP[HEAP_COUNT];
  HEAP_COUNT--;

  int child = parent << 1;
  if (child + 1 <= HEAP_COUNT)
  {
    child = (MEMBERS[HEAP[child]].mWeight < MEMBERS[HEAP[child + 1]].mWeight) ? child : child + 1;
  }

  while (child <= HEAP_COUNT)
  {
    if (MEMBERS[HEAP[parent]].mWeight > MEMBERS[HEAP[child]].mWeight)
    {
      Swap(HEAP, parent, child);
      parent = child;
      child = parent << 1;

      if (child + 1 <= HEAP_COUNT)
      {
        child = (MEMBERS[HEAP[child]].mWeight < MEMBERS[HEAP[child + 1]].mWeight) ? child : child + 1;
      }
    }
  }

  return min_index;
}

int main()
{
  // int input[] = {3, 2, 5, 1, 4};
  // const int input_length = sizeof(input) / sizeof(input[0]);

  for (int i = 0; i < MEMBERS_LENGTH; i++)
  {
    Push(i);
  }

  PrintHeap();
  cout << "---" << endl;

  for (int i = HEAP_COUNT; i > 0; i--)
  {
    int min_index = Pop();
    cout << "Pop() = [" << min_index << "] " << MEMBERS[min_index].mName << ":" << MEMBERS[min_index].mWeight << ' ' << endl;
    cout << "---" << endl;
    PrintHeap();
    cout << "---" << endl;
  }
  cout << endl;

  return 0;
}