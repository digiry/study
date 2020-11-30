#include <iostream>

using namespace std;

int ARR[3] = {1, 2, 3};
int TEMP[2] = {
    0,
};
const int _N = 3;
const int PICKS = 2;

void PrintTempReserver(const int *pTemp, const int picks)
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

void Permutation(int *pArr, const int n, const int r)
{
  int i = 0;
  if (r == 0)
  {
    PrintTempReserver(TEMP, PICKS);
  }
  else
  {
    for (i = n - 1; i >= 0; i--)
    {
      Swap(pArr, i, n - 1);
      TEMP[r - 1] = pArr[n - 1];
      Permutation(pArr, n - 1, r - 1);
      Swap(pArr, i, n - 1);
    }
  }
}

int main()
{
  int length = sizeof(ARR) / sizeof(ARR[0]);

  Permutation(ARR, _N, PICKS);
  return 0;
}
