/*
 * main.c
 *
 *  Created on: 2014. 9. 17.
 *      Author: suandkyu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header/addressbook.h"
#include "header/linkedlist.h"

void printMainMenu() {
	printf("1. 주소정보를 입력한다.\n");
	printf("2. 주소정보를 삭제한다.\n");
	printf("3. 주소정보를 수정한다.\n");
	printf("4. 주소정보를 검색한다.\n");
	printf("5. 전체 주소록을 출력한다.\n");
	printf("6. 주소록 파일에 저장한다.\n");
	printf("7. 주소록 파일을 불러온다.\n");
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
	case ERROR_LOAD_FAIL:
		printf("addressbook.book 파일을 불러올수 없습니다.\n");
		break;
	default:
		break;
	}
}

int isEmptyAddressBook(LINKEDLIST *pBook) {
	int isEmpty = TRUE;

	if ( getLengthLinkedList(pBook) > 0 ) {
		isEmpty = FALSE;
	}

	return isEmpty;
}

void inputPersonInfo(LINKEDLIST *pBook) {
	int index = 0;
	PERSONALINFO info;
	char yesno;

	printf("이름 : ");
	scanf("%s", info.name);
	printf("전화번호 : ");
	scanf("%s", info.phone);
	printf("주소 : ");
	scanf("%s", info.address);

	printf("입력된 정보\n");
	printHeader(FALSE);
	printPersonInfo(info, FALSE);

	fflush(stdin);
	printf("추가하시겠습니까 ? (y/n) :");
	yesno = getchar();

	if ( yesno == 'y' ) {
		appendLinkedList(pBook, &info);
		printf("추가되었습니다.\n");
	}
}

void removePersonInfo(PERSONALINFO *pBook) {
	char name[7];
	int removeIndex = -1;
	char yesno;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printf("삭제할 이름: ");
	scanf("%s", name);

	removeIndex = findNameLinkedList(pBook, name);

	if ( removeIndex == -1 ) {
		print_error(ERROR_NOT_SEARCH);
		return ;
	}

	printHeader(FALSE);
	printPersonInfo(viewAtLinkedList(pBook, removeIndex), FALSE);

	fflush(stdin);
	printf("삭제하겠습니까? (y/n) :");
	yesno = getchar();

	if ( yesno == 'y' ) {
		deleteLinkedList(pBook, removeIndex);
		printf("삭제되었습니다.\n");
	}
}

void modifyPersonInfo(PERSONALINFO *pBook) {
	char name[7];
	int modifyIndex = -1;
	char yesno;
	PERSONALINFO info;
	NODE *target;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printf("수정할 이름: ");
	scanf("%s", name);

	modifyIndex = findNameLinkedList(pBook, name);

	if ( modifyIndex == -1 ) {
		print_error(ERROR_NOT_SEARCH);
		return ;
	}

	printHeader(FALSE);
	printPersonInfo(viewAtLinkedList(pBook, modifyIndex), FALSE);

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
		printPersonInfo(info, FALSE);

		target = getNodeLinkedList(pBook, modifyIndex);

		strcpy(target->info->name, info.name);
		strcpy(target->info->phone, info.phone);
		strcpy(target->info->address, info.address);

		printf("수정되었습니다.\n");
	}
}

void searchPersonInfo(LINKEDLIST *pBook) {
	char name[7];
	int foundIndex = -1;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printf("검색할 이름: ");
	scanf("%s", name);

	foundIndex = findNameLinkedList(pBook, name);

	if ( foundIndex == -1 ) {
		print_error(ERROR_NOT_SEARCH);
		return ;
	}

	printHeader(FALSE);
	printPersonInfo(viewAtLinkedList(pBook, foundIndex), FALSE);
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

void printPersonInfo(PERSONALINFO info, int printNum) {
	if ( printNum != FALSE ) {
		printf("%-4d  %-7s  %-12s  %-50s\n", printNum, info.name, info.phone, info.address);
	} else {
		printf("%-8s  %-12s  %-50s\n", info.name, info.phone, info.address);
	}
}

void printPersonInfoPointer(PERSONALINFO *info, int printNum) {
	if ( printNum != FALSE ) {
		printf("%-4d  %-7s  %-12s  %-50s\n", printNum, info->name, info->phone, info->address);
	} else {
		printf("%-8s  %-12s  %-50s\n", info->name, info->phone, info->address);
	}
}


void printAllPersonInfo(PERSONALINFO *pBook) {
	int number = 1;
	NODE *target;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printHeader(TRUE);
	target = moveFirstLinkedList(pBook);
	while ( isTailLinkedList(pBook) != TRUE ) {
		printPersonInfoPointer(target->info, number);
		target = nextLinkedList(pBook);
		number++;
	}
}

void saveAddressBook(LINKEDLIST *pBook) {
	FILE *fp = NULL;
	int index = 0;
	NODE *target;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	fp = fopen("addressbook.dat", "w");

	target = moveFirstLinkedList(pBook);
	while ( isTailLinkedList(pBook) != TRUE ) {
		fprintf(fp, "%s\n", target->info->name);
		fprintf(fp, "%s\n", target->info->phone);
		fprintf(fp, "%s\n", target->info->address);
		target = nextLinkedList(pBook);
	}

	fclose(fp);
	printf("addressbook.dat 파일에 저장하였습니다.\n");
}

void loadAddressBook(LINKEDLIST *pBook) {
	FILE *fp = NULL;
	PERSONALINFO info;

	deleteAllLinkedList(pBook);

	fp = fopen("addressbook.dat", "r");

	if ( fp == NULL ) {
		print_error(ERROR_LOAD_FAIL);
		return ;
	}

	while( ! feof(fp) ) {
		memset(&info, 0x00, sizeof(PERSONALINFO));
		fscanf(fp, "%s", info.name);
		fscanf(fp, "%s", info.phone);
		fscanf(fp, "%s", info.address);

		if ( strcmp(info.name, "") ==  0 ) {
			break;
		}
		appendLinkedList(pBook, &info);
	}

	fclose(fp);
	printf("addressbook.dat 파일을 불러왔습니다.\n");
}

void testSetup(LINKEDLIST *list) {
	int index = 0;
	PERSONALINFO sample[MAX_SIZE] = {
			{"aaa", "0001112222", "abc", USE},
			{"bbb", "0001113333", "abc", USE},
			{"ccc", "0001114444", "abc", USE},
			{"ddd", "0001115555", "abc", USE},
			{"eee", "0001116666", "abc", USE},
			{"fff", "0001117777", "abc", USE},
			{"ggg", "0001118888", "abc", USE},
			{"hhh", "0001119999", "abc", USE},
			{"iii", "0001110000", "abc", USE},
			{"jjj", "0002220000", "abc", USE}
	};

	for ( index = 0; index < MAX_SIZE; index++ ) {
		appendLinkedList(list, &(sample[index]));
	}
}

int main(void) {
	int menu = -1;
	LINKEDLIST *book;
	book = (LINKEDLIST*)malloc(sizeof(LINKEDLIST));

	createLinkedList(book);
//	PERSONALINFO book[MAX_SIZE] = {0,};
//	PERSONALINFO book[MAX_SIZE] = {
//			{"aaa", "0001112222", "abc", USE},
//			{"bbb", "0001113333", "abc", USE},
//			{"ccc", "0001114444", "abc", USE},
//			{"ddd", "0001115555", "abc", USE},
//			{"eee", "0001116666", "abc", USE},
//			{"fff", "0001117777", "abc", USE},
//			{"ggg", "0001118888", "abc", USE},
//			{"hhh", "0001119999", "abc", USE},
//			{"iii", "0001110000", "abc", USE},
//			{"jjj", "0002220000", "abc", USE}
//	};

	testSetup(book);

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
		case MENU_SAVE:
			saveAddressBook(book);
			break;
		case MENU_LOAD:
			loadAddressBook(book);
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
