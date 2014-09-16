/*
 * main.c
 *
 *  Created on: 2014. 9. 17.
 *      Author: suandkyu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MENU_INPUT 1
#define MENU_REMOVE 2
#define MENU_MODIFY 3
#define MENU_SEARCH 4
#define MENU_ALL_PRINT 5
#define MENU_FINISH 0

#define ERROR_NO_MENU 1
#define ERROR_FULL 2
#define ERROR_EMPTY 3
#define ERROR_NOT_SEARCH 4

#define USE 1
#define NOT_USE 0

#define TRUE 1
#define FALSE 0

#define MAX_SIZE 10

typedef struct _tag_personalInfo {
	char name[7];
	char phone[12];
	char address[50];
	int flag;
} personalInfo;

void printMainMenu() {
	printf("1. 주소정보를 입력한다.\n");
	printf("2. 주소정보를 삭제한다.\n");
	printf("3. 주소정보를 수정한다.\n");
	printf("4. 주소정보를 검색한다.\n");
	printf("5. 전체 주소록을 출력한다.\n");
	printf("0. 종료한다.\n");
}

void print_finish() {
	printf("프로그램을 종료합니다.\n");
}

void print_error(int error) {
	switch (error) {
	case ERROR_NO_MENU:
		printf("없는 번호를 입력하였습니다.\n");
		break;
	case ERROR_FULL:
		printf("주소록이 가득 찼습니다.\n");
		break;
	case ERROR_EMPTY:
		printf("주소록이 비어있습니다.\n");
		break;
	case ERROR_NOT_SEARCH:
		printf("주소정보를 찾을 수 없습니다.\n");
		break;
	default:
		break;
	}
}

int isEmptyAddressBook(personalInfo *pBook) {
	int isEmpty = TRUE;
	int index = 0;

	for ( index = 0; index < MAX_SIZE; index++ ) {
		if ( pBook[index].flag == USE ) {
			isEmpty = FALSE;
			break;
		}
	}
	return isEmpty;
}

int isFullAddressBook(personalInfo *pBook) {
	int isFull = TRUE;
	int index = 0;

	for ( index = 0; index < MAX_SIZE; index++ ) {
		if ( pBook[index].flag == NOT_USE ) {
			isFull = FALSE;
			break;
		}
	}
	return isFull;
}

int findFirstRecordable(personalInfo *pBook) {
	int index = 0;
	int found = -1;

	for ( index = 0; index < MAX_SIZE; index++ ) {
		if ( pBook[index].flag == NOT_USE ) {
			found = index;
			break;
		}
	}

	return found;
}

void inputPersonInfo(personalInfo *pBook) {
	int index = 0;
	personalInfo info;
	char yesno;

	if ( isFullAddressBook(pBook) == TRUE ) {
		print_error(ERROR_FULL);
		return ;
	}

	index = findFirstRecordable(pBook);

	printf("이름 : ");
	scanf("%s", info.name);
	printf("전화번호 : ");
	scanf("%s", info.phone);
	printf("주소 : ");
	scanf("%s", info.address);

	printf("입력된 정보\n");
	printHeader(FALSE);
	printPersonInfo(info, -1);

	fflush(stdin);
	printf("추가하시겠습니까 ? (y/n) :");
	yesno = getchar();

	if ( yesno == 'y' ) {
		strcpy(pBook[index].name, info.name);
		strcpy(pBook[index].phone, info.phone);
		strcpy(pBook[index].address, info.address);
		pBook[index].flag = USE;
		printf("추가되었습니다.\n");
	}
}

int _searchPersonalInfo(char *pName, personalInfo *pBook, int *pFoundArray) {
	int index = 0;
	int foundIndex = 0;

	for ( index = 0; index < MAX_SIZE; index++ ) {
		if ( pBook[index].flag == USE ) {
			if ( strcmp(pName, pBook[index].name) == 0 ) {
				pFoundArray[foundIndex] = index;
				foundIndex++;
			}
		}
	}

	return foundIndex;
}

void removePersonInfo(personalInfo *pBook) {
	char name[7];
	int foundArray[MAX_SIZE] = {-1,};
	int index = 0;
	int foundLength = 0;
	int removeIndex = -1;
	char yesno;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printf("삭제할 이름: ");
	scanf("%s", name);

	foundLength = _searchPersonalInfo(name, pBook, foundArray);

	if ( foundLength == 0 ) {
		print_error(ERROR_NOT_SEARCH);
		return ;
	}

	printHeader(TRUE);
	for ( index = 0; index < foundLength; index++ ) {
		printPersonInfo(pBook[foundArray[index]], index + 1);
	}

	printf("삭제할 번호를 입력하시오.\n");
	printf("번호 : ");
	scanf("%d", &removeIndex);

	fflush(stdin);
	printf("삭제하겠습니까? (y/n) :");
	yesno = getchar();

	if ( yesno == 'y' ) {
		pBook[foundArray[removeIndex - 1]].flag = NOT_USE;
		printf("삭제되었습니다.\n");
	}
}

void modifyPersonInfo(personalInfo *pBook) {
	char name[7];
	int foundArray[MAX_SIZE] = {-1,};
	int index = 0;
	int foundLength = 0;
	int modifyIndex = -1;
	char yesno;
	personalInfo info;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printf("수정할 이름: ");
	scanf("%s", name);

	foundLength = _searchPersonalInfo(name, pBook, foundArray);

	if ( foundLength == 0 ) {
		print_error(ERROR_NOT_SEARCH);
		return ;
	}

	printHeader(TRUE);
	for ( index = 0; index < foundLength; index++ ) {
		printPersonInfo(pBook[foundArray[index]], index + 1);
	}

	printf("수정할 번호를 입력하시오.\n");
	printf("번호 : ");
	scanf("%d", &modifyIndex);

	fflush(stdin);
	printf("수정하겠습니까? (y/n) :");
	yesno = getchar();

	if ( yesno == 'y' ) {
		printf("이름 : ");
		scanf("%s", info.name);
		printf("전화번호 : ");
		scanf("%s", info.phone);
		printf("주소 : ");
		scanf("%s", info.address);

		printf("수정된 정보\n");
		printHeader(FALSE);
		printPersonInfo(info, -1);

		strcpy(pBook[foundArray[modifyIndex - 1]].name, info.name);
		strcpy(pBook[foundArray[modifyIndex - 1]].phone, info.phone);
		strcpy(pBook[foundArray[modifyIndex - 1]].address, info.address);

		printf("수정되었습니다.\n");
	}
}

void searchPersonInfo(personalInfo *pBook) {
	char name[7];
	int foundArray[MAX_SIZE] = {-1,};
	int index = 0;
	int foundLength = 0;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printf("검색할 이름: ");
	scanf("%s", name);

	foundLength = _searchPersonalInfo(name, pBook, foundArray);

	if ( foundLength == 0 ) {
		print_error(ERROR_NOT_SEARCH);
		return ;
	}

	printHeader(TRUE);
	for ( index = 0; index < foundLength; index++ ) {
		printPersonInfo(pBook[foundArray[index]], index + 1);
	}
}

void printHeader(int printNum) {
	printf("----------------------------------------------\n");
	if ( printNum == TRUE ) {
		printf("번호  이름     전화번호      주소\n");
	} else {
		printf("이름     전화번호      주소\n");
	}
	printf("----------------------------------------------\n");
}

void printPersonInfo(personalInfo info, int printNum) {
	if ( printNum != -1 ) {
		printf("%-4d  %-7s  %-12s  %-50s\n", printNum, info.name, info.phone, info.address);
	} else {
		printf("%-8s  %-12s  %-50s\n", info.name, info.phone, info.address);
	}
}

void printAllPersonInfo(personalInfo *pBook) {
	int index = 0;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printHeader(TRUE);
	for ( index = 0; index < MAX_SIZE; index++ ) {
		if ( pBook[index].flag != NOT_USE ) {
			printPersonInfo(pBook[index], index);
		}
	}
}

int main(void) {
	int menu = -1;
	personalInfo book[MAX_SIZE] = {0,};
//	personalInfo book[MAX_SIZE] = {
//			{"aaa", "0001112222", "abc", USE},
//			{"bbb", "0001113333", "abc", USE},
//			{"ccc", "0001114444", "abc", USE},
//			{"ddd", "0001115555", "abc", USE},
//			{"eee", "0001116666", "abc", USE},
//			{"fff", "0001117777", "abc", USE},
//			{"ggg", "0001118888", "abc", USE},
//			{"hhh", "0001119999", "abc", USE},
//			{"aaa", "0001110000", "abc", USE},
//			{"jjj", "0002220000", "abc", USE}
//	};

	while ( menu != 0 ) {
		printMainMenu();

		printf("menu: ");
		scanf("%d", &menu);
		fflush(stdin);

		switch (menu) {
		case MENU_INPUT:
			inputPersonInfo(book);
			break;
		case MENU_REMOVE:
			removePersonInfo(book);
			break;
		case MENU_MODIFY:
			modifyPersonInfo(book);
			break;
		case MENU_SEARCH:
			searchPersonInfo(book);
			break;
		case MENU_ALL_PRINT:
			printAllPersonInfo(book);
			break;
		case MENU_FINISH:
			print_finish();
			break;
		default:
			print_error(ERROR_NO_MENU);
			break;
		}
		if ( menu != MENU_FINISH ) {
			fflush(stdin);
			printf("\nmenu 화면으로 돌아갑니다. (아무키나 누르세요)\n");
			getchar();
		}
	}
	return EXIT_SUCCESS;
}
