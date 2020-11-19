/*
# 이진탐색에서 중복 데이터가 있을 경우 검색하는 알고리즘

**전제조건으로 이미 데이터는 정렬되어 있다.**

아래 알고리즘을 사용하는 사례

## 중복된 값을 찾을 경우

### Lower bound

* 중복된 값들 중 첫 위치를 알고 싶을 때 사용

### Upper bound

* 중복된 값들 중 마지막 위치를 알고 싶을 때 사용
* 단, 반환된 결과 위치는 마지막 위치 바로 다음 인덱스이다.

아래 코드를 실행하면 9를 찾을 경우 인덱스 8이 나온다.
중복된 값 9 중에 마지막 위치는 8 - 1인 즉 인덱스 7에 있다.

## low, high를 수정 로직

### 두 함수 모두 같은 로직

* Value > Data[mid] 이면 low = mid+1 로 옮긴다.
* Value < Data[mid] 이면 high = mid 로 옮긴다.

### 두 함수가 다른 로직

`Upper bound`

* Value == Data[mid] 이면 low = mid+1 로 옮긴다.

`Lower bound`

* Value == Data[mid] 이면 high = mid 로 옮긴다.

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
