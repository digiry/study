#include <iostream>

using namespace std;

const int NULL_VALUE = -1;
const int UNDER_STACK = -1;
const int STACK_SIZE = 6;
int STACK_LENGTH = 0;
int TOP = UNDER_STACK;
int STACK[STACK_SIZE] = { 0, };

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[6] = {
	{"abc", 60},
	{"def", 83},
	{"ghi", 72},
	{"jkl", 103},
	{"mno", 54},
	{"pqr", 77},
};


void PrintStack(const int *const pStack, const int length, const int top) {
	cout << "STACK:";
	for (int i = 0; i < length; ++i) {
		cout << pStack[i] << ' ';
	}
	cout << endl;
}

void PrintStack(const int *const pStack, const User *const pMembers, const int length, const int top) {
	cout << "ST_MR:";
	for (int i = 0; i < length; ++i) {
		cout << "[" << pStack[i] << "]" << pMembers[pStack[i]].mName << ":" << pMembers[pStack[i]].mWeight << ' ';
	}
	cout << endl;
}

void Push(const int value) {
	cout << " PUSH:" << value << endl;
	if (STACK_LENGTH == STACK_SIZE) {
		return;
	}

	++TOP;
	STACK[TOP] = value;
	++STACK_LENGTH;
}

int Pop() {
	cout << "  POP:" << endl;
	if (STACK_LENGTH == 0) {
		return NULL_VALUE;
	}

	int value = STACK[TOP];
	--TOP;
	--STACK_LENGTH;

	return value;
}

int main() {
	int input_data[6] = { 4,5,6,7,8,9 };

	for (int i = 0; i < 6; ++i) {
		Push(input_data[i]);
		PrintStack(STACK, STACK_LENGTH, TOP);
	}

	int value = Pop();
	cout << "RETURN:" << value << endl;
	PrintStack(STACK, STACK_LENGTH, TOP);

	value = Pop();
	cout << "RETURN:" << value << endl;
	PrintStack(STACK, STACK_LENGTH, TOP);
	
	cout << "------" << endl;
	STACK_LENGTH = 0;
	TOP = UNDER_STACK;
	for (int i = 0; i < 6; ++i) {
		Push(i);
		PrintStack(STACK, MEMBERS, STACK_LENGTH, TOP);
	}

	int index = Pop();
	cout << "RET_MR:[" << index << "]" << MEMBERS[index].mName << ":" << MEMBERS[index].mWeight << endl;
	PrintStack(STACK, MEMBERS, STACK_LENGTH, TOP);

	index = Pop();
	cout << "RET_MR:[" << index << "]" << MEMBERS[index].mName << ":" << MEMBERS[index].mWeight << endl;
	PrintStack(STACK, MEMBERS, STACK_LENGTH, TOP);

	return 0;
}
