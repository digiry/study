#include <iostream>

using namespace std;

int ARR[] = {42, 89, 63, 12, 94, 27, 78, 3, 50, 36};

void PrintArray(int *const pArr, const int length)
{
  for (int i = 0; i < length; i++)
  {
    cout << pArr[i] << ' ';
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
int Partition(int *const pArr, const int left, const int right)
{
  int i = left - 1;
  int j = left;
  int p = (left + right) >> 1;

  while (j <= right)
  {
    if (pArr[j] < pArr[p])
    {
      i++;
      Swap(pArr, i, j);
      if (i == p)
      {
        p = j;
      }
    }
    j++;
  }
  Swap(pArr, i + 1, p);

  return i + 1;
}

void QuickSort(int *const pArr, const int left, const int right)
{
  if (left >= right)
  {
    return;
  }

  int pivot = Partition(pArr, left, right);
  QuickSort(pArr, left, pivot - 1);
  QuickSort(pArr, pivot + 1, right);
}

int main()
{
  int length = sizeof(ARR) / sizeof(ARR[0]);
  int left_index = 0;
  int right_index = length - 1;

  PrintArray(ARR, length);
  QuickSort(ARR, left_index, right_index);
  PrintArray(ARR, length);

  return 0;
}