#include <iostream>

using namespace std;

//#define SWAP(x,y,t) (t=*(x),*(x)=*(y),*(x)=t)

//int input[] = {11, 45, 23, 81, 28, 34};
//int max_length = 6;
//int input[] = {3,2,4,6,9,1,8,7,5};
//int max_length = 9;
//int input[] = {11,45,22,81,23,34,99,22,17,8};
//int max_length = 10;
int input[] = {1,1,1,1,1,0,0,0,0,0};
int max_length = 10;

void swap(int *src, int *dst);
int hoare_partition(int *data, int l_index, int r_index);
void quicksort(int *data, int l_index, int r_index);
void print_array(int *data, int size);

int main() {
    quicksort(input, 0, max_length-1);
    print_array(input, max_length);
    return 0;
}

int hoare_partition(int *data, int l_index, int r_index) {
    int pivot = data[l_index];
    int i = l_index;
    int j = r_index;

    while(i <= j) {
        while(data[i] >= pivot) {
            if(i != r_index) {
                i++;
            }
            else {
                break;
            }
        }
        while(data[j] <= pivot) {
            if(j != l_index) {
                j--;
            }
            else {
                break;
            }
        }
        if(i < j) {
            swap(&(data[i]), &(data[j]));
        }
        if((i==j) && (j==r_index)) {
            break;
        }
    }
    swap(&(data[l_index]), &(data[j]));

    return j;
}
void quicksort(int *data, int l_index, int r_index) {
    int split = 0;
    cout << ">>> L=" << l_index << " R=" << r_index << endl;
    if(l_index < r_index) {
        split = hoare_partition(data, l_index, r_index);
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