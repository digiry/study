/*
  DO NOT USE ANY GLOBAL VARIABLE OR STATIC VARIABLE IN USER CODE.
  ONLY LOCAL VARIABLE AND CONSTANT ARE ALLOWED. ALSO, IT IS NOT
  ALLOWED TO ALLOCATE MEMORY BY CALLING malloc FUNCTION OR 'new' KEYWORD.
*/

// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.
//
// bool mstrcmp(unsigned char *a, unsigned char *b) {
//     while(*a && *a == *b)
//         ++a, ++b;
//     return *a == *b;
// }
//
// int mstrlen(unsigned char *a) {
//     int len = 0;
//     while (*a)
//         ++a, ++len;
//     return len;
// }

extern bool memread(unsigned char dest[], int pos, int len);
extern bool memwrite(unsigned char src[], int pos, int len);

#define MAXLEN 12

bool init(int N) {
	return true; // if the value of 'false' is returned, this testcase would be skipped. 
}

void put(unsigned char key_in[MAXLEN + 1], unsigned char value_in[MAXLEN + 1]) {

}

void del(unsigned char key_in[MAXLEN + 1]) {

}

void get(unsigned char key_in[MAXLEN + 1], unsigned char value_out[MAXLEN + 1]) {

}

void getkey(unsigned char value_in[MAXLEN + 1], unsigned char key_out[MAXLEN + 1]) {

}