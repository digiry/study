//
// Created by ninaeros on 11/22/15.
//

#include <iostream>

using namespace std;

int T;
char input_data[100] = {0,};
int input_cnt = 0;

void clear_data(int cnt);
int get_data_length();

int cnvt_int = 0;

int main(void) {
    freopen("sample_input.txt", "r", stdin);

    cin >> T;
    for (int tc = 0; tc < T; tc++) {
        cin >> input_data;
        input_cnt = get_data_length();

        for (int id=0; id<input_cnt; id++) {

            cnvt_int = cnvt_int << 1;
            if (input_data[id] == '1') {
                cnvt_int |= 1;
            }

            if ((id % 7) == 6) {
                cout << cnvt_int << ',';
                cnvt_int = 0;
            } else if (id == input_cnt-1) {
                cout << cnvt_int << ',';
            }

        }

        clear_data(input_cnt);
        cout << endl;
    }

    return 0;
}

int get_data_length() {
    int cnt = 0;
    while (input_data[cnt] !=0 ) cnt++;

    return cnt;
}

void clear_data(int cnt) {
    for(int id = 0; id < cnt; id++) {
        input_data[id] = 0;
    }
}