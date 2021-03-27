#include <iostream>

using namespace std;

const int LENGTH = 14;
int ARR[LENGTH] = {0, 4, 2, 2, 0, 0, 1, 1, 0, 1, 0, 2, 4, 2};
int ANSWERS[LENGTH] = {
    0,
};
const int COUNTS_LENGTH = 10;
int COUNTS[COUNTS_LENGTH] = {
    0,
};

void PrintArray(int *const pArr, const int length)
{
  for (int i = 0; i < length; i++)
  {
    cout << pArr[i] << ' ';
  }
  cout << endl;
}

void CountingSort(int *const pArr, const int length)
{
  for (int i = 0; i < length; i++)
  {
    COUNTS[pArr[i]]++;
  }
  for (int i = 1; i < COUNTS_LENGTH; i++)
  {
    COUNTS[i] += COUNTS[i - 1];
  }

  for (int i = length - 1; i >= 0; i--)
  {
    --COUNTS[pArr[i]];
    ANSWERS[COUNTS[pArr[i]]] = pArr[i];
  }

  for (int i = 0; i < length; i++)
  {
    pArr[i] = ANSWERS[i];
  }
}

int main()
{
  PrintArray(ARR, LENGTH);
  CountingSort(ARR, LENGTH);
  PrintArray(ARR, LENGTH);

  return 0;
}