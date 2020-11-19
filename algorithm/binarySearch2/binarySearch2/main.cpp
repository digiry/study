/*
# ����Ž������ �ߺ� �����Ͱ� ���� ��� �˻��ϴ� �˰���

**������������ �̹� �����ʹ� ���ĵǾ� �ִ�.**

�Ʒ� �˰����� ����ϴ� ���

## �ߺ��� ���� ã�� ���

### Lower bound

* �ߺ��� ���� �� ù ��ġ�� �˰� ���� �� ���

### Upper bound

* �ߺ��� ���� �� ������ ��ġ�� �˰� ���� �� ���
* ��, ��ȯ�� ��� ��ġ�� ������ ��ġ �ٷ� ���� �ε����̴�.

�Ʒ� �ڵ带 �����ϸ� 9�� ã�� ��� �ε��� 8�� ���´�.
�ߺ��� �� 9 �߿� ������ ��ġ�� 8 - 1�� �� �ε��� 7�� �ִ�.

## low, high�� ���� ����

### �� �Լ� ��� ���� ����

* Value > Data[mid] �̸� low = mid+1 �� �ű��.
* Value < Data[mid] �̸� high = mid �� �ű��.

### �� �Լ��� �ٸ� ����

`Upper bound`

* Value == Data[mid] �̸� low = mid+1 �� �ű��.

`Lower bound`

* Value == Data[mid] �̸� high = mid �� �ű��.

*/

#include <iostream>

using namespace std;

int datas[10] = { 1, 3, 4, 5, 7, 7, 9, 9, 10, 10 };

/*


*/
int search_lower_bound(int value) {
	int low = 0;
	int high = sizeof(datas) / sizeof(datas[0]);
	int mid = 0;

	while (low < high) {
		mid = int((low + high) * 0.5);
		if (value <= datas[mid]) {
			high = mid;
		}
		else {
			low = mid + 1;
		}
	}
	
	return low;
}

int search_upper_bound(int value) {
	int low = 0;
	int high = sizeof(datas) / sizeof(datas[0]);
	int mid = 0;

	while (low < high) {
		mid = int((low + high) * 0.5);
		if (value >= datas[mid]) {
			low = mid + 1;
		}
		else {
			high = mid;
		}
	}

	return low;
}

int main() {
	int lower_bound = 0;
	int upper_bound = 0;

	lower_bound = search_lower_bound(9);
	upper_bound = search_upper_bound(9);

	cout << "lower_bound: " << lower_bound << endl;
	cout << "upper_bound: " << upper_bound << endl;

	return 0;
}
