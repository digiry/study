#include <iostream>

using namespace std;

const int LENGTH = 7;
int ARR[LENGTH] = {329, 457, 657, 839, 436, 720, 355};
const int DIGITS_LENGTH = 3;
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

void CountingSortByDigit(int *const pArr, const int length, const int digit)
{
  int pows10[] = {1, 10, 100, 1000, 10000};
  int bigMask = pows10[digit];
  int smallMask = pows10[digit - 1];

  for (int i = 0; i < COUNTS_LENGTH; i++)
  {
    COUNTS[i] = 0;
  }
  for (int i = 0; i < length; i++)
  {
    int index = pArr[i] % bigMask / smallMask;
    COUNTS[index]++;
  }
  for (int i = 1; i < COUNTS_LENGTH; i++)
  {
    COUNTS[i] += COUNTS[i - 1];
  }
  cout << "COUNTS:  ";
  PrintArray(COUNTS, COUNTS_LENGTH);
  for (int i = length - 1; i >= 0; i--)
  {
    int index = pArr[i] % bigMask / smallMask;
    --COUNTS[index];
    ANSWERS[COUNTS[index]] = pArr[i];
  }
  cout << "ANSWERS:";
  PrintArray(ANSWERS, LENGTH);
}

void RadixSort(int *const pArr, const int length)
{
  for (int digit = 1; digit <= DIGITS_LENGTH; digit++)
  {
    CountingSortByDigit(pArr, length, digit);
    for (int i = 0; i < length; i++)
    {
      pArr[i] = ANSWERS[i];
    }
  }
}

int main()
{
  PrintArray(ARR, LENGTH);
  cout << "----" << endl;
  RadixSort(ARR, LENGTH);
  cout << "----" << endl;
  PrintArray(ARR, LENGTH);

  return 0;
}