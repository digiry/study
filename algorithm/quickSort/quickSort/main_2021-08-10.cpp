#include <iostream>

using namespace std;

typedef struct _array {
	int* mArr;
	int mLength;

	_array(const int size);
	~_array();
	void SetValue(const int value);
	void swap(const int a_index, const int b_index);
	void Sort();
	void quickSort(const int left, const int right);
	int partition(const int left, const int right);

	int& operator[](const int index);
} Array;

//ostream& operator<<(ostream& os, const Array)
void PrintArray(Array& rArr);

int main() {
	int inputs[] = { 53,62,45,71,34,8,27,89,16 };
	const int inputs_size = sizeof(inputs) / sizeof(inputs[0]);

	Array* arr = new Array(inputs_size);

	for (int i = 0; i < inputs_size; ++i) {
		arr->SetValue(inputs[i]);
	}
	PrintArray(*arr);

	cout << endl;

	arr->Sort();
	PrintArray(*arr);

	return 0;
}

void PrintArray(Array& rArr) {
	for (int i = 0; i < rArr.mLength; ++i) {
		cout << "[" << i << "] = " << rArr[i] << endl;
	}
}

// Array

_array::_array(const int size) {
	this->mArr = new int[size];
	this->mLength = 0;
}

_array::~_array() {
	if (this->mArr != NULL) {
		delete[] this->mArr;
	}
	this->mLength = 0;
}

void _array::SetValue(const int value) {
	this->mArr[this->mLength] = value;
	++this->mLength;
}
void _array::Sort() {
	const int left = 0;
	const int right = this->mLength - 1;

	this->quickSort(left, right);
}

void _array::swap(const int a_index, const int b_index) {
	if (a_index == b_index) {
		return;
	}

	this->mArr[a_index] = this->mArr[a_index] ^ this->mArr[b_index];
	this->mArr[b_index] = this->mArr[a_index] ^ this->mArr[b_index];
	this->mArr[a_index] = this->mArr[a_index] ^ this->mArr[b_index];
}

void _array::quickSort(const int left, const int right) {
	if (left >= right) {
		return;
	}

	int pivot = this->partition(left, right);
	this->quickSort(left, pivot - 1);
	this->quickSort(pivot + 1, right);
}

int _array::partition(const int left, const int right) {
	int i = left - 1;
	int j = left;
	int pivot = (left + right) >> 1;

	while (j <= right) {
		if (this->mArr[j] < this->mArr[pivot]) {
			++i;
			this->swap(i, j);

			if (i == pivot) {
				pivot = j;
			}
		}
		++j;
	}

	this->swap(i + 1, pivot);

	return i + 1;
}

int& _array::operator[](const int index) {
	return this->mArr[index];
}
