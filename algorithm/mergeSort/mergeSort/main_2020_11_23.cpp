#include <iostream>

using namespace std;

int ARR[] = { 27,15,19,25,30,13,19,21 };
int TEMP_ARR[20] = { 0, };

//// 한번의 While loop로 해결되지만 조건문을 헤갈릴 위험이 있음.
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

// While이 논리 과정에 따라 3개로 나누어짐. 3개로 나눠져도 arr은 한번만 순회함.
// 논리 과정과 코드가 동일하여 이해하기 쉬임.
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

	// 인자는 left, right가 실제 배열의 index여야 함.
	MergeSort(ARR, 0, right);
	PrintArray(ARR, arr_length);

	return 0;
}
