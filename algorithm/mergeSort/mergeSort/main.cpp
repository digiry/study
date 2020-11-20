#include <iostream>

using namespace std;

int result[20] = { 0, };

// right는 실제 배열index이므로 조건식 주의
void merge(int* arr, int left, int mid, int right) {
	int t_idx = 0;
	int i = left;
	int j = mid + 1;

	while (i <= mid && j <= right) {
		if (arr[i] < arr[j]) {
			result[t_idx++] = arr[i++];
		}
		else {
			result[t_idx++] = arr[j++];
		}
	}

	while (i <= mid) {
		result[t_idx++] = arr[i++];
	}
	while (j <= right) {
		result[t_idx++] = arr[j++];
	}

	t_idx = 0;
	// right는 실제 배열index이므로 조건식 주의
	for (i = left; i <= right; i++) {
		arr[i] = result[t_idx++];
	}
}

void merge_sort(int* arr, int left, int right) {
	if (left == right) {
		return ;
	}

	int mid = (left + right) >> 1;

	merge_sort(arr, left, mid);
	merge_sort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

void merge_sort2(int* arr, int left, int right) {

	if (left == right) {
		return;
	}

	int mid = (left + right) >> 1;

	merge_sort(arr, left, mid);
	merge_sort(arr, mid + 1, right);
	// merge(arr, left, mid, right);

	int t_idx = 0;
	int i = left;
	int j = mid + 1;

	// 이미 정렬되어 있으면 merge 생략
	if (arr[mid] > arr[mid+1]) {
		while (i <= mid && j <= right) {
			if (arr[i] < arr[j]) {
				result[t_idx++] = arr[i++];
			}
			else {
				result[t_idx++] = arr[j++];
			}
		}

		while (i <= mid) {
			result[t_idx++] = arr[i++];
		}
		while (j <= right) {
			result[t_idx++] = arr[j++];
		}

		t_idx = 0;
		// right는 실제 배열index이므로 조건식 주의
		for (i = left; i <= right; i++) {
			arr[i] = result[t_idx++];
		}
	}
}

void print_array(int* arr, int length) {

	for (int i = 0; i < length; i++) {
		cout << arr[i] << ' ';
	}
}


int main() {
	int arr[] = { 27,15,19,25,30,13,19,21 };
	int length = sizeof(arr) / sizeof(arr[0]);
	// right는 실제 배열index이므로 조건식 주의
	int right = length - 1;

	merge_sort2(arr, 0, right);
	print_array(arr, length);

	return 0;
}