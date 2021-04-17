#include <stdio.h>
#include <string.h>

const int ASCII_NUM = 256;

int compare(int a, int b) {
    return a > b ? a : b;
}

// Bad Character skip 테이블 셋팅 (skip, key, key_length)
void setSkipCount_BC(int* dest, char* source, const int n) {
    int len = strlen(source);

    int i;

    for (i = 0; i < ASCII_NUM; ++i) {
        dest[i] = n;
    }

    for (i = 0; i < n - 1; ++i) {
        dest[source[i]] = len - 1 - i;
    }
}

// Suffix 테이블 셋팅 (suffix, key, key_length)
void setSuffix(int* dest, char* source, const int n) {
    int f, g, i;

    dest[n - 1] = n;

    g = n - 1;

    for (i = n - 2; i >= 0; --i) {
        if (i > g && dest[i + n - 1 - f] < i - g) {
            dest[i] = dest[i + n - 1 - f];
        }
        else {
            if (i < g) {
                g = i;
            }
            f = i;
            while (g >= 0 && source[g] == source[g + n - 1 - f]) {
                --g;
            }
            dest[i] = f - g;
        }
    }
}

// Good Suffix 테이블 셋팅 (skip, key, key_length)
void setSkipCount_GS(int* dest, char* source, const int n) {
    int suffix[ASCII_NUM];
    int i, j;

    setSuffix(suffix, source, n);
    printf("\nSuffix\n");
    for (int k = n-1; k >= 0; --k) {
        printf("[%d]%d ", k, suffix[k]);
    }
    printf("\n");
    for (i = 0; i < n; ++i) {
        dest[i] = n;
    }

    for (i = n - 1; i >= 0; --i) {
        if (suffix[i] == i + 1) {
            for (j = 0; j < n - i - 1; ++j) {
                if (dest[j] == n) {
                    dest[j] = n - i - 1;
                }
            }
        }
    }

    for (i = 0; i <= n - 2; ++i) {
        dest[n - 1 - suffix[i]] = n - i - 1;
    }
}

// str : 문자열, key : 찾는 문자열
// 문자열 찾기 성공시 매칭된 위치를 반환, 실패 시 -1 반환
int boyerMoore(char* str, char* key) {
    int skip_bc[ASCII_NUM];
    int skip_gs[ASCII_NUM];
    int len_str = strlen(str);
    int len_key = strlen(key);
    int i = 0;
    int j = 0;

    setSkipCount_BC(skip_bc, key, len_key);
    printf("Bad characters\n");
    for (int k = 0; k < ASCII_NUM; k++) {
        if (k >= 32 && k <= 127) {
            printf("[%c]%d ", k, skip_bc[k]);
        }
    }
    printf("\n\n");
    printf("Good skip\n");
    setSkipCount_GS(skip_gs, key, len_key);
    for (int k = 0; k < ASCII_NUM; k++) {
        if (k >= 32 && k <= 127) {
            printf("[%c]%d ", k, skip_gs[k]);
        }
    }
    printf("\n\n");

    while (i <= len_str - len_key) {
        for (j = len_key - 1; j >= 0 && key[j] == str[i + j]; --j) {
            // Nothing
        }
        if (j < 0) {
            return i;
        }
        else {
            i += compare(skip_gs[j], skip_bc[str[i + j]] - len_key + j + 1);
        }
    }

    return -1;
}

int main() {
    char str[] = "A STRING SEARCHING EXAMPLE CCNSISTING CF";
    char key[] = "STRING";
    int index;

    printf("       01234567890+123456789+123456789+123456789+\n");
    printf("Text : %s\n", str);
    printf("Key  : %s\n", key);
    index = boyerMoore(str, key);

    printf("Find at : %d\n", index);

    return 0;
}
