#include <string>
#include <map>
#include <set>

using namespace std;
typedef unsigned int UINT;

const int KEY_SIZE = 3;
const int MAX_STRING_SIZE = 50001;
char SRC_STRING[MAX_STRING_SIZE];
int SRC_STRING_LENGTH = 0;

UINT gen_keyhash(const char* keystring);
string gen_key(const char* keystring);

map<string, set<int>*> KEY_MAP;

set<int> INDICATOR_SET_POOL[MAX_STRING_SIZE];
int INDICATOR_SET_POOL_LENGTH = 0;

void StrCopy(const char* src, char* dest);

void StrCopy(const char* src, char* dest) {
	while (*src != '\0') {
		*dest++ = *src++;
	}
	*dest = '\0';
}

void init(int N, char init_string[]) {
	StrCopy(init_string, SRC_STRING);
	SRC_STRING_LENGTH = N;
	KEY_MAP.clear();
	INDICATOR_SET_POOL_LENGTH = 0;

	char* key = NULL;
	UINT hash = 0;
	string key_str;

	for (int i = 0; i <= SRC_STRING_LENGTH - KEY_SIZE; ++i) {
		key = SRC_STRING + i;
		// hash = gen_keyhash(key);
		key_str = gen_key(key);

		auto it = KEY_MAP.find(key_str);
		if (it != KEY_MAP.end()) {
			auto pSet = it->second;
			pSet->insert(i);
		}
		else {
			auto pSet = &INDICATOR_SET_POOL[INDICATOR_SET_POOL_LENGTH++];

			pSet->clear();
			pSet->insert(i);
			KEY_MAP.insert(make_pair(key_str, pSet));
		}
	}
}

int change(char string_A[], char string_B[]) {
	int count = 0;
	UINT str_a_hash = 0;
	string str_a_key;
	UINT target_hash = 0;
	string target_key;
	const int LAST_INDEX = SRC_STRING_LENGTH - 3;

	//str_a_hash = gen_keyhash(string_A);
	str_a_key = gen_key(string_A);
	auto str_a_it = KEY_MAP.find(str_a_key);
	if (str_a_it == KEY_MAP.end()) {
		return 0;
	}

	auto str_a_set = str_a_it->second;
	if (str_a_set->empty()) {
		return 0;
	}

	// Normarlize set
	set<int> set_to_modify;
	int target_index = *(str_a_set->begin());
	for (int index : *str_a_set) {
		if (index == target_index || index == target_index + 3 || index > target_index + 3) {
			set_to_modify.insert(index);
			target_index = index;
		}
	}

	count = set_to_modify.size();

	// Remove indicator before modifying
	for (int index : set_to_modify) {
		for (int x = index - 2; x <= index + 2; ++x) {
			if (x < 0 || x > LAST_INDEX) {
				continue;
			}

			// target_hash = gen_keyhash(SRC_STRING + x);
			target_key = gen_key(SRC_STRING + x);
			auto target_it = KEY_MAP.find(target_key);
			if (target_it == KEY_MAP.end()) {
				continue;
			}

			auto target_set = target_it->second;
			if (target_set->empty()) {
				continue;
			}

			target_set->erase(target_set->find(x));
		}

		// Modify sub string
		SRC_STRING[index] = string_B[0];
		SRC_STRING[index + 1] = string_B[1];
		SRC_STRING[index + 2] = string_B[2];

		for (int x = index - 2; x <= index + 2; ++x) {
			if (x < 0 || x > LAST_INDEX) {
				continue;
			}

			// target_hash = gen_keyhash(SRC_STRING + x);
			target_key = gen_key(SRC_STRING + x);
			auto target_it = KEY_MAP.find(target_key);
			if (target_it != KEY_MAP.end()) {
				auto target_set = target_it->second;
				target_set->insert(x);
			}
			else {
				auto target_set = &INDICATOR_SET_POOL[INDICATOR_SET_POOL_LENGTH++];

				target_set->clear();
				target_set->insert(x);
				KEY_MAP.insert(make_pair(target_key, target_set));
			}
		}
	}

	return count;
}

void result(char ret[]) {
	StrCopy(SRC_STRING, ret);
}

UINT gen_keyhash(const char* keystring) {
	UINT hash = 0;

	hash = keystring[0] - 'a';
	hash = (hash << 5) + keystring[1] - 'a';
	hash = (hash << 5) + keystring[2] - 'a';

	return hash;
}

string gen_key(const char* keystring) {
	string key;

	key = keystring[0];
	key += keystring[1];
	key += keystring[2];

	return key;
}
