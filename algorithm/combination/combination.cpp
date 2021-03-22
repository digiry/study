#include <iostream>

using namespace std;

int ARR[4] = {1, 2, 3, 4};
int TEMP[3] = {
    0,
};
const int _N = 4;
const int PICKS = 3;

void PrintTemp(const int *pArr, const int length)
{
  for (int i = 0; i < length; i++)
  {
    cout << pArr[i] << ' ';
  }
  cout << endl;
}

void Combination(const int *pArr, const int n, const int r)
{
  if (r == 0)
  {
    PrintTemp(TEMP, PICKS);
  }
  else if (n == 0)
  {
    return;
  }
  else
  {
    TEMP[r - 1] = pArr[n - 1];
    Combination(pArr, n - 1, r - 1);
    Combination(pArr, n - 1, r);
  }
}

int main()
{
  Combination(ARR, _N, PICKS);
  return 0;
}