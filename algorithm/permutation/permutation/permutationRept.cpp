#include <iostream>

using namespace std;

int ARR[3] = {1, 2, 3};
int TEMP[2] = {
    0,
};
const int _N = 3;
const int PICKS = 2;

void PrintTempReserve(const int *pTemp, const int picks)
{
  for (int i = picks - 1; i >= 0; i--)
  {
    cout << pTemp[i] << ' ';
  }
  cout << endl;
}

void Swap(int *pArr, const int a_index, const int b_index)
{
  if (a_index == b_index)
  {
    return;
  }

  pArr[a_index] = pArr[a_index] ^ pArr[b_index];
  pArr[b_index] = pArr[a_index] ^ pArr[b_index];
  pArr[a_index] = pArr[a_index] ^ pArr[b_index];
}

void PermutationRept(int *pArr, const int n, const int r)
{
  if (r == 0)
  {
    PrintTempReserve(TEMP, PICKS);
  }
  else
  {
    for (int i = n - 1; i >= 0; i--)
    {
      Swap(pArr, i, n - 1);
      TEMP[r - 1] = pArr[n - 1];
      PermutationRept(pArr, n, r - 1);
      Swap(pArr, i, n - 1);
    }
  }
}

int main()
{
  int length = sizeof(ARR) / sizeof(ARR[0]);

  PermutationRept(ARR, _N, PICKS);
  return 0;
}