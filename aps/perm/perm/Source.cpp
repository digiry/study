#include<iostream>
using namespace std;
void swap(int& value1, int& value2)
{
	int temp = value1;
	value1 = value2;
	value2 = temp;
}
void printArr(int intArr[], int size, int permStart) {
	cout << "perm(" << permStart << ")=" << "=>";
	for (int i = 0; i < size; i++) {
		cout << intArr[i];
	}
	cout << endl;
}
void perm(int intArr[], int size, int permStart)
{
	// 맨 마지막 재귀함수, 즉 마지막 자리수까지 도달했을 때의 재귀함수에서만 출력을 시키는 것이 핵심.
	if (permStart == size - 1)
	{
		for (int j = 0; j<size; j++) cout << intArr[j];
		cout << endl;
	}
	for (int i = permStart; i<size; i++)
	{
		// permStart는 호출된 재귀함수 내에서 swap()의 기준이 되는 시작지점.
		// 맨 앞자리인 0이 초기 시작점이며, for문을 통해 intArr[permStart]를 intArr[i]와 swap하는 것으로
		// 서로 다른 순열항들을 만들어낸다.
		// 재귀함수 호출을 통해서 permStart+1 로 시작점을 변경하며, 이를 통하여 순환 구조 형성.

		// i는 intArr[permStart]와의 swap() 대상을 가리키는 index.
		// 언제나 해당 재귀함수의 permStart에서 시작하여 size-1까지 이동.
		//cout << "perm(" << permStart << ")=" << "[bef] swap(permStart:" << permStart << ",i:" << i << ")" << endl;
		swap(intArr[permStart], intArr[i]);
		//printArr(intArr, size, permStart);
		//cout << "perm(" << permStart << ")=" << "[mid] perm(permStart:" << permStart+1 << ")" << endl;
		perm(intArr, size, permStart + 1);
		//cout << "perm(" << permStart << ")=" << "[aft] swap(permStart:" << permStart << ",i:" << i << ")" << endl;
		swap(intArr[permStart], intArr[i]);
		//printArr(intArr, size, permStart);
	}
}
int main()
{
	int size;
	cout << "## GENERATING PERMUTATION ##" << endl
		<< "Input the number of digits (bigger than 0) :";
	cin >> size;
	int* intArr = new int[size];
	for (int k = 0; k<size; k++)
		intArr[k] = k + 1;
	//cout << "[str] perm(permStart:" << 0 << ")" << endl;
	perm(intArr, size, 0);
	delete[] intArr;
}