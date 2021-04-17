#include <iostream>

using namespace std;

const int NOT_FOUND = -1;

int MinValue(const int a_value, const int b_value) {
	return (a_value < b_value) ? a_value : b_value;
}

int StrLen(const char* src) {
	int count = 0;
	while (*src != '\0') {
		count++;
		src++;
	}
	return count;
}

int BadCharacter(const char bad_char, const char* key, const int bad_char_key_i) {
	cout << "BadCharacter:" << bad_char << " - " << key << " [" << bad_char_key_i << "]" << endl;
	int found = NOT_FOUND;

	for (int i = bad_char_key_i; i >= 0; i--) {
		if (key[i] == bad_char) {
			found = i;
			break;
		}
	}
	cout << "found: " << found << endl;
	return found;
}

int GoodSuffix(const char* key, const int suffix_first_i) {
	cout << "GoodSuffix:" << key << "," << suffix_first_i << endl;
	int found = NOT_FOUND;
	int key_len = StrLen(key);
	const int MIN_SUFFIX_LENGTH = 2;

	cout << "i:" << key_len - MIN_SUFFIX_LENGTH << "~" << key_len - suffix_first_i - MIN_SUFFIX_LENGTH << endl;
	for (int i = key_len - MIN_SUFFIX_LENGTH; i >= key_len - suffix_first_i - MIN_SUFFIX_LENGTH; i--) {
		int j = 0;
		cout << "j:0~" << key_len - suffix_first_i - 1 << endl;
		while (j < key_len - suffix_first_i - 1) {
			if (key[i - j] != key[key_len - j - 1]) {
				break;
			}
			j++;
		}
		if (j >= key_len - suffix_first_i - 1) {
			found = i - (key_len - suffix_first_i) + 1;
			cout << "found: j=" << j << " found=" << found << endl;
			break;
		}
	}

	return found;
}

int BoyerMooreStringSearch(const char* src, const char* key) {
	int found = NOT_FOUND;
	int src_len = StrLen(src);
	int key_len = StrLen(key);

	int src_i = 0;
	while (src_i <= src_len - key_len) {
		cout << "src_i:" << src_i << endl;
		int key_i = key_len - 1;
		while (key_i >= 0 && key[key_i] == src[src_i + key_i]) {
			key_i--;
		}
		if (key_i < 0) {
			found = src_i;
			break;
		}
		int bad_char_index = BadCharacter(src[src_i + key_i], key, key_i);
		int good_suffix_index = GoodSuffix(key, key_i);
		cout << "BC:" << bad_char_index << " GS:" << good_suffix_index << endl;
		src_i = src_i + key_i - MinValue(bad_char_index, good_suffix_index);
	}

	return found;
}


int main() {
	char src[] = "GTTATAGCTGATCGCGGCGTAGCGGCGAA";
	char key[] = "GTAGCGGCG";

	int found = NOT_FOUND;

	found = BoyerMooreStringSearch(src, key);

	cout << "Text : " << src << endl;
	cout << "Key  : " << key << endl;

	if (found != NOT_FOUND) {
		cout << "Found at : " << found << endl;
		cout << "       0123456789+123456789+123456789+123456789+" << endl;
		cout << "Text : " << src << endl;
		cout << "Found: ";
		while (found > 0) {
			cout << ' ';
			found--;
		}
		cout << key << endl;
	}
	else {
		cout << "Not Found" << endl;
	}

	return 0;
}
