#include <iostream>

using namespace std;

const int STACK_SIZE = 6;
const int OVER_STACK = -1;
int STACK_LENGTH = 0;
int STACK[STACK_SIZE] = { 0, };
int TOP = OVER_STACK;

typedef struct _User {
	char mName[20];
	int mWeight;
} User;

User MEMBERS[8] = {
	{"abc", 60},
	{"def", 83},
	{"ghi", 74},
	{"jkl", 103},
	{"mno", 52},
	{"pqr", 98},
	{"stu", 44},
	{"vwx", 77},
};

void PrintStack(int *const pStack, const int length) {
	cout << "STACK:";
	for (int i = 0; i < length; i++) {
		cout << pStack[i] << ' ';
	}
	cout << endl;
}

void PrintMembersInStack(int* const pStack, const User* const pMembers, const int length) {
	cout << "MEM_S:";
	for (int i = 0; i < length; i++) {
		cout << "[" << pStack[i] << "]" << pMembers[pStack[i]].mName << ":" << pMembers[pStack[i]].mWeight << ' ';
	}
	cout << endl;
}

void Push(const int value) {
	if (STACK_LENGTH == STACK_SIZE) {
		return;
	}

	++TOP;
	STACK[TOP] = value;
	++STACK_LENGTH;
}

int Pop() {
	if (STACK_LENGTH == 0) {
		return OVER_STACK;
	}

	int value = STACK[TOP];
	--TOP;
	--STACK_LENGTH;

	return value;
}

int main() {
	int input_data[] = { 4,5,6,7,8,9,10,11,12 };
	const int input_length = sizeof(input_data) / sizeof(input_data[0]);

	for (int i = 0; i < 6; i++) {
		cout << "_PUSH:" << input_data[i] << endl;
		Push(input_data[i]);
		PrintStack(STACK, STACK_LENGTH);
	}

	int value = Pop();
	cout << "__POP:" << value << endl;
	PrintStack(STACK, STACK_LENGTH);

	value = Pop();
	cout << "__POP:" << value << endl;
	PrintStack(STACK, STACK_LENGTH);

	value = input_data[6];
	cout << "_PUSH:" << value << endl;
	Push(value);
	PrintStack(STACK, STACK_LENGTH);

	value = input_data[7];
	cout << "_PUSH:" << value << endl;
	Push(value);
	PrintStack(STACK, STACK_LENGTH);

	cout << "---" << endl;
	TOP = OVER_STACK;
	STACK_LENGTH = 0;
	for (int i = 0; i < STACK_SIZE; i++) {
		STACK[i] = -1;
	}

	for (int i = 0; i < 6; i++) {
		cout << "_PUSH:[" << i << "]" << MEMBERS[i].mName << ":" << MEMBERS[i].mWeight << endl;
		Push(i);
		PrintMembersInStack(STACK, MEMBERS, STACK_LENGTH);
	}

	int index = Pop();
	cout << "__POP:[" << index << "]" << MEMBERS[index].mName << ":" << MEMBERS[index].mWeight << endl;
	PrintMembersInStack(STACK, MEMBERS, STACK_LENGTH);

	index = Pop();
	cout << "__POP:[" << index << "]" << MEMBERS[index].mName << ":" << MEMBERS[index].mWeight << endl;
	PrintMembersInStack(STACK, MEMBERS, STACK_LENGTH);

	value = 6;
	cout << "_PUSH:[" << value << "]" << MEMBERS[value].mName << ":" << MEMBERS[value].mWeight << endl;
	Push(value);
	PrintMembersInStack(STACK, MEMBERS, STACK_LENGTH);

	value = 7;
	cout << "_PUSH:[" << value << "]" << MEMBERS[value].mName << ":" << MEMBERS[value].mWeight << endl;
	Push(value);
	PrintMembersInStack(STACK, MEMBERS, STACK_LENGTH);

	return 0;
}
