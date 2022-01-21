#include <string>
#include <set>

using namespace std;

const int KEY_SIZE = 3;
const int MAX_STRING_SIZE = 50001;
const int MAX_POOL_SIZE = 26 * 26 * 26 + 1;
char SRC_STRING[MAX_STRING_SIZE];
int SRC_STRING_LENGTH = 0;

int gen_keyhash(const char* keystring);

set<int> KEY_MAP[MAX_POOL_SIZE];

void StrCopy(const char* src, char* dest);

void init(int N, char init_string[]) {
	StrCopy(init_string, SRC_STRING);
	SRC_STRING_LENGTH = N;

	for (register int i = 0; i < MAX_POOL_SIZE; ++i) {
		KEY_MAP[i].clear();
	}

	char* key = NULL;
	int hash = 0;

	for (int i = 0; i <= SRC_STRING_LENGTH - KEY_SIZE; ++i) {
		key = SRC_STRING + i;
		hash = gen_keyhash(key);

		KEY_MAP[hash].insert(i);
	}
}

int change(char string_A[], char string_B[]) {
	int count = 0;
	int str_a_hash = 0;
	int target_hash = 0;
	const int LAST_INDEX = SRC_STRING_LENGTH - 3;

	str_a_hash = gen_keyhash(string_A);

	if (KEY_MAP[str_a_hash].empty()) {
		return 0;
	}

	// Normarlize set
	set<int> set_to_modify;
	int target_index = *(KEY_MAP[str_a_hash].begin());
	for (int index : KEY_MAP[str_a_hash]) {
		if (index == target_index || index == target_index + 3 || index > target_index + 3) {
			set_to_modify.insert(index);
			target_index = index;
		}
	}

	count = set_to_modify.size();

	// Remove indicator before modifying
	for (int index : set_to_modify) {
		for (register int x = index - 2; x <= index + 2; ++x) {
			if (x < 0 || x > LAST_INDEX) {
				continue;
			}

			target_hash = gen_keyhash(SRC_STRING + x);
			
			if (KEY_MAP[target_hash].empty()) {
				continue;
			}

			KEY_MAP[target_hash].erase(KEY_MAP[target_hash].find(x));
		}

		// Modify sub string
		SRC_STRING[index] = string_B[0];
		SRC_STRING[index + 1] = string_B[1];
		SRC_STRING[index + 2] = string_B[2];

		for (register int x = index - 2; x <= index + 2; ++x) {
			if (x < 0 || x > LAST_INDEX) {
				continue;
			}

			target_hash = gen_keyhash(SRC_STRING + x);
			KEY_MAP[target_hash].insert(x);
		}
	}

	return count;
}

void result(char ret[]) {
	StrCopy(SRC_STRING, ret);
}

void StrCopy(const char* src, char* dest) {
	while (*src != '\0') {
		*dest++ = *src++;
	}
	*dest = '\0';
}

inline int gen_keyhash(const char* keystring) {
	int hash = 0;

	hash = (keystring[2] - 'a');
	hash += (keystring[1] - 'a') * 26;
	hash += (keystring[0] - 'a') * (26 * 26);

	return hash;
}
