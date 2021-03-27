#include <iostream>

using namespace std;

const int NOT_FOUND = -1;
int ARR[] = {1, 2, 3, 4, 5, 11, 12, 13, 14, 15};
int ARR4BOUND[] = {1, 2, 3, 4, 7, 7, 9, 9, 10, 10};

int BinarySearch(int *const pArr, const int low, const int high, const int key)
{
  int found = NOT_FOUND;
  int l = low;
  int h = high;
  int m = 0;

  while (l < h)
  {
    m = (l + h) >> 1;

    if (pArr[m] == key)
    {
      found = m;
      break;
    }

    if (pArr[m] < key)
    {
      l = m + 1;
    }
    else
    {
      h = m;
    }
  }

  return found;
}

int BinarySearchLower(int *const pArr, const int low, const int high, const int key)
{
  int found = NOT_FOUND;
  int l = low;
  int h = high;
  int m = 0;

  while (l < h)
  {
    m = (l + h) >> 1;
    if (pArr[m] >= key)
    {
      h = m;
    }
    else
    {
      l = m + 1;
    }
  }

  if (pArr[l] == key)
  {
    found = l;
  }

  return found;
}

int BinarySearchUpper(int *const pArr, const int low, const int high, const int key)
{
  int found = NOT_FOUND;
  int l = low;
  int h = high;
  int m = 0;

  while (l < h)
  {
    m = (l + h) >> 1;
    if (pArr[m] <= key)
    {
      l = m + 1;
    }
    else
    {
      h = m;
    }
  }

  if (pArr[l - 1] == key)
  {
    found = l;
  }

  return found;
}

int main()
{
  int length = sizeof(ARR) / sizeof(ARR[0]);
  int left_index = 0;
  int right_index = length - 1;
  int key = 0;
  int key_find = 12;
  int key_notfind = 10;
  int found = 0;

  cout << "BinarySearch" << endl;
  key = key_find;
  found = BinarySearch(ARR, left_index, right_index, key);
  cout << "key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not found: ") << found << endl;
  key = key_notfind;
  found = BinarySearch(ARR, left_index, right_index, key);
  cout << "key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not found: ") << found << endl;

  key_find = 9;
  key_notfind = 5;
  cout << "BinarySearch Lower" << endl;
  key = key_find;
  found = BinarySearchLower(ARR4BOUND, left_index, right_index, key);
  cout << "key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not found: ") << found << endl;
  key = key_notfind;
  found = BinarySearchLower(ARR4BOUND, left_index, right_index, key);
  cout << "key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not found: ") << found << endl;

  cout << "BinarySearch Upper" << endl;
  key = key_find;
  found = BinarySearchUpper(ARR4BOUND, left_index, right_index, key);
  cout << "key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not found: ") << found << endl;
  key = key_notfind;
  found = BinarySearchUpper(ARR4BOUND, left_index, right_index, key);
  cout << "key: " << key << ((found != NOT_FOUND) ? " Found: " : " Not found: ") << found << endl;

  return 0;
}