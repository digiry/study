#include <iostream>

using namespace std;

const int LENGTH = 7;
int ARR[LENGTH] = {20, 15, 19, 4, 13, 11, 23};
int TEMP[LENGTH] = {
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

void Merge(int *const pArr, const int left, const int mid, const int right)
{
  int i = left;
  int j = mid + 1;
  int t_index = 0;

  while (i <= mid && j <= right)
  {
    if (pArr[i] <= pArr[j])
    {
      TEMP[t_index++] = pArr[i++];
    }
    else
    {
      TEMP[t_index++] = pArr[j++];
    }
  }

  while (i <= mid)
  {
    TEMP[t_index++] = pArr[i++];
  }

  while (j <= right)
  {
    TEMP[t_index++] = pArr[j++];
  }

  for (int k = 0; k < t_index; k++)
  {
    pArr[left + k] = TEMP[k];
  }
}

void MergeSort(int *const pArr, const int left, const int right)
{
  if (left == right)
  {
    return;
  }

  int mid = (left + right) >> 1;
  MergeSort(pArr, left, mid);
  MergeSort(pArr, mid + 1, right);

  Merge(pArr, left, mid, right);
}

int main()
{
  int left_index = 0;
  int right_index = LENGTH - 1;

  PrintArray(ARR, LENGTH);
  MergeSort(ARR, left_index, right_index);
  PrintArray(ARR, LENGTH);

  return 0;
}