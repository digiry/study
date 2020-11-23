#include <iostream>

using namespace std;

int ARR[] = { 27,15,19,25,30,13,19,21 };
int TEMP_ARR[20] = { 0, };

//// �ѹ��� While loop�� �ذ������ ���ǹ��� �찥�� ������ ����.
//void Merge2(int* arr, int left, int mid, int right) {
//	int i = left;
//	int j = mid + 1;
//	int count = 0;
//
//	while (right >= left + count) {
//		if (i < mid+1 && arr[i] < arr[j] || j > right) {
//			RESULT_ARR[count++] = arr[i];
//			i++;
//		}
//		else {
//			RESULT_ARR[count++] = arr[j];
//			j++;
//		}
//	}
//
//	for (i = 0; i < count; i++) {
//		arr[left + i] = RESULT_ARR[i];
//	}
//}

// While�� �� ������ ���� 3���� ��������. 3���� �������� arr�� �ѹ��� ��ȸ��.
// �� ������ �ڵ尡 �����Ͽ� �����ϱ� ����.
void Merge(int* arr, int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int t_index = 0;

	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			TEMP_ARR[t_index++] = arr[i++];
		}
		else {
			TEMP_ARR[t_index++] = arr[j++];
		}
	}

	while (i <= mid) {
		TEMP_ARR[t_index++] = arr[i++];
	}

	while (j <= right) {
		TEMP_ARR[t_index++] = arr[j++];
	}

	t_index = 0;
	for (i = left; i <= right; i++) {
		arr[i] = TEMP_ARR[t_index++];
	}
}

void MergeSort(int* arr, int left, int right) {
	if (left >= right) {
 		return;
	}

	int middle = ((left + right) >> 1);
	MergeSort(arr, left, middle);
	MergeSort(arr, middle + 1, right);

	Merge(arr, left, middle, right);
}

void PrintArray(int* arr, int length) {
	for (int i = 0; i < length; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	int arr_length = sizeof(ARR) / sizeof(ARR[0]);
	int right = arr_length - 1;

	// ���ڴ� left, right�� ���� �迭�� index���� ��.
	MergeSort(ARR, 0, right);
	PrintArray(ARR, arr_length);

	return 0;
}
