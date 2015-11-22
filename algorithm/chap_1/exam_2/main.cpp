#include <iostream>

using namespace std;

int T;
char input_data[100] = {0,};
int input_cnt = 0;
char bin_array[1000];
int bin_cnt = 0;
int cnvt_int = 0;

char hexa_map[16][5] = {
        "0000",
        "0001",
        "0010",
        "0011",
        "0100",
        "0101",
        "0110",
        "0111",
        "1000",
        "1001",
        "1010",
        "1011",
        "1100",
        "1101",
        "1110",
        "1111"
};

void clear_data();
int get_input_length();

int main() {
    int tc;
    freopen("sample_input.txt", "r", stdin);

    cin >> T;
    for (tc = 0; tc < T; tc++) {
        cin >> input_data;
        input_cnt = get_input_length();

        for (int id=0; id<input_cnt; id++) {
            int hex_id = (input_data[id]<'A') ? (input_data[id]-'0'):(input_data[id]-'A'+10);
            bin_array[bin_cnt++] = hexa_map[hex_id][0];
            bin_array[bin_cnt++] = hexa_map[hex_id][1];
            bin_array[bin_cnt++] = hexa_map[hex_id][2];
            bin_array[bin_cnt++] = hexa_map[hex_id][3];
        }
        cnvt_int = 0;
        for (int id=0; id<bin_cnt; id++) {

            cnvt_int = cnvt_int << 1;
            if (bin_array[id] == '1') {
                cnvt_int |= 1;
            }

            if ((id % 7) == 6) {
                cout << cnvt_int << ',';
                cnvt_int = 0;
            } else if (id == bin_cnt-1) {
                cout << cnvt_int << ',';
            }
        }

        cout << endl;
        //cout << "debug:" << bin_array << endl;
        clear_data();
    }

    return 0;
}

int get_input_length() {
    int cnt;
    for (cnt = 0; input_data[cnt] != 0; ) cnt++;
    return cnt;
}

void clear_data() {
    for(int id = 0; id < input_cnt; id++) {
        input_data[id] = 0;
    }
    input_cnt = 0;
    for(int id = 0; id < bin_cnt; id++) {
        bin_array[id] = 0;
    }
    bin_cnt = 0;
}