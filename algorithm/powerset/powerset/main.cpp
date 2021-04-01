#include <iostream>

using namespace std;

int ARR[3] = {1, 2, 3};

void Powerset(const int *pArr, const int length)
{
  int i = 0;
  int j = 0;
  int powerset_length = 1 << length;
  for (i = 0; i < powerset_length; i++)
  {
    for (j = 0; j < length; j++)
    {
      if (i & (1 << j))
      {
        cout << pArr[j] << ' ';
      }
    }
    cout << endl;
  }
}

int main()
{
  int length = sizeof(ARR) / sizeof(ARR[0]);
  Powerset(ARR, length);
  return 0;
}