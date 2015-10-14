#include <iostream>

using namespace std;

//int input[] = {11, 45, 23, 81, 28, 34};
//int max_length = 6;
//int input[] = {3,2,4,6,9,1,8,7,5};
//int max_length = 9;
//int input[] = {11,45,22,81,23,34,99,22,17,8};
//int max_length = 10;
int input[] = {1,1,1,1,1,0,0,0,0,0};
int max_length = 10;

void swap(int *src, int *dst);
int lomuto_partition(int *data, int p_index, int r_index);
void quicksort(int *data, int l_index, int r_index);
void print_array(int *data, int size);

int main() {
    quicksort(input, 0, max_length-1);
    print_array(input, max_length);
    return 0;
}

int lomuto_partition(int *data, int p_index, int r_index) {
    int temp = data[r_index];
    int i = p_index-1;
    int j = 0;

    for(j=p_index; j<r_index; j++) {
        if(data[j] <= temp) {
            i++;
            swap(&(data[i]), &(data[j]));
        }
    }

    swap(&(data[i+1]), &(data[r_index]));
    return i+1;
}

void quicksort(int *data, int l_index, int r_index) {
    int split = 0;
    cout << ">>> L=" << l_index << " R=" << r_index << endl;
    if(l_index < r_index) {
        split = lomuto_partition(data, l_index, r_index);
        quicksort(data, l_index, split-1);
        quicksort(data, split+1, r_index);
    }
}

void print_array(int *data, int size) {
    int i;
    for(i=0; i<size; i++) {
        cout << data[i] << ' ';
    }
    cout << endl;
}

void swap(int *src, int *dst) {
    int temp = 0;
    temp = *(src);
    *(src) = *(dst);
    *(dst) = temp;
    print_array(input, max_length);
}