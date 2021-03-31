#include <iostream>

using namespace std;

int ARR[3] = {1, 2, 3};
int TEMP[2] = {
    0,
};
const int _N = 3;
const int PICKS = 2;

void PrintTemp(const int *pTemp, const int length)
{
  for (int i = 0; i < length; i++)
  {
    cout << pTemp[i] << ' ';
  }

  cout << endl;
}

void CombinationRept(const int *pArr, const int n, const int r)
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
    CombinationRept(pArr, n, r - 1);
    CombinationRept(pArr, n - 1, r);
  }
}

int main()
{
  CombinationRept(ARR, _N, PICKS);
  return 0;
}