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
	// �� ������ ����Լ�, �� ������ �ڸ������� �������� ���� ����Լ������� ����� ��Ű�� ���� �ٽ�.
	if (permStart == size - 1)
	{
		for (int j = 0; j<size; j++) cout << intArr[j];
		cout << endl;
	}
	for (int i = permStart; i<size; i++)
	{
		// permStart�� ȣ��� ����Լ� ������ swap()�� ������ �Ǵ� ��������.
		// �� ���ڸ��� 0�� �ʱ� �������̸�, for���� ���� intArr[permStart]�� intArr[i]�� swap�ϴ� ������
		// ���� �ٸ� �����׵��� ������.
		// ����Լ� ȣ���� ���ؼ� permStart+1 �� �������� �����ϸ�, �̸� ���Ͽ� ��ȯ ���� ����.

		// i�� intArr[permStart]���� swap() ����� ����Ű�� index.
		// ������ �ش� ����Լ��� permStart���� �����Ͽ� size-1���� �̵�.
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