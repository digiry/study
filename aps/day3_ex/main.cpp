#include <iostream>

using namespace std;

#define MAX(x,y) ((x>y)?x:y)

char input[6] = {0,};
int input_length = 0;
char copy_input[6] = {0,};

int max_number = 0;

void copy_number(char *src, char *dst);

void init_c(char *src);
void itoc(int number, char *dst);
int ctoi(char *src);

int get_length(char *src);

int switch_number(char *src, int base, int target);
void find_max(char *src, int base);

int main() {
    int T;
    int N;
    int C;
    int testCase;

    cin >> T;
    for (testCase=0; testCase<T; testCase++) {
        cin >> N >> C;
        itoc(N, input);
        input_length = get_length(input);
        max_number = 0;

        for (int count=0; count<C; count++) {
            for (int index=6-input_length; index<(6-1); index++) {
                copy_number(input, copy_input);
                find_max(copy_input, index);
                itoc(max_number, copy_input);
            }
        }

        cout << "#" << testCase+1 << " " << max_number << endl;
    }
    return 0;
}

void init_c(char *src) {
    for (int index=0; index<6; index++) {
        src[index] = 0;
    }
}

void copy_number(char *src, char *dst) {
    for (int index=0; index<6; index++) {
        dst[index] = src[index];
    }
}

void itoc(int number, char *dst) {
    int letter;
    int length = 5;

    init_c(dst);
    while (number!=0) {
        letter = number%10;
        number = number/10;
        dst[length] = '0'+letter;
        length--;
    }
}

int ctoi(char *src) {
    int result = 0;
    int index = 0;

    while (index < 6) {
        if (src[index] != 0) {
            result = result*10;
            result = result+(src[index]-'0');
        }
        index++;
    }
    return result;
}

int get_length(char *src) {
    int length = 0;
    int index = 5;

    while (src[index] != 0) {
        length++;
        index--;
    }

    return length;
}

void find_max(char *src, int base) {
    if (base == 5) {
        return;
    }
    for (int index=base+1; index<6; index++) {
        int temp = switch_number(src, base, index);
        max_number = MAX(max_number, temp);
    }
    find_max(src, base+1);
}

int switch_number(char *src, int base, int target) {
    char temp[6];
    char swap;
    int number;

    copy_number(src, temp);
    swap = temp[base];
    temp[base] = temp[target];
    temp[target] = swap;

    number = ctoi(temp);

    return number;
}