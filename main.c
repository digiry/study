/*
 * main.c
 *
 *  Created on: 2014. 9. 17.
 *      Author: suandkyu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "addressbook.h"
#include "linkedlist.h"

void printMainMenu();

void print_finish();

void print_error(int error);

int isEmptyAddressBook(LINKEDLIST *pBook);

int isFullAddressBook(LINKEDLIST *pBook);

int findFirstRecordable(LINKEDLIST *pBook);

void inputPersonInfo(LINKEDLIST *pBook);

int _searchPersonInfo(char *pName, LINKEDLIST *pBook, int *pFoundArray);

void removePersonInfo(LINKEDLIST *pBook);

void modifyPersonInfo(LINKEDLIST *pBook);

void searchPersonInfo(LINKEDLIST *pBook);

void printHeader(int printNum);

void printAllPersonInfo(LINKEDLIST *pBook);

void saveAddressBook(LINKEDLIST *pBook);

void loadAddressBook(LINKEDLIST *pBook);

void deletePersonInfoWith(self, removeNumber);

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

int isEmptyAddressBook(PERSONALINFO *pBook) {
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

int isFullAddressBook(PERSONALINFO *pBook) {
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

int findFirstRecordable(PERSONALINFO *pBook) {
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

void inputPersonInfo(PERSONALINFO *pBook) {
	PERSONALINFO info;
	char yesno;
	NODE *last;
	int number;

	last = moveLastLinkedList(pBook);

	if ( last->next == NULL ) {
		number = 1;
	} else {
		number = last->info->number + 1;
	}

	printf("이름 : ");
	scanf("%s", info.name);
	printf("전화번호 : ");
	scanf("%s", info.phone);
	printf("주소 : ");
	scanf("%s", info.address);

	printf("입력된 정보\n");
	printHeader();
	printPersonInfo(info);

	fflush(stdin);
	printf("추가하시겠습니까 ? (y/n) :");
	yesno = getchar();

	if ( yesno == 'y' ) {
		appendLinkedList(pBook, &info);
		printf("추가되었습니다.\n");
	}
}

void deletePersonInfoWith(self, removeNumber) {
	int index = 0;
	NODE *target;

	target = moveFirstLinkedList(self);
	while( isTailLinkedList(self) != TRUE ) {
		if ( target->info->number == removeNumber ) {
			deleteLinkedList(self, index);
			break;
		} else {
			target = nextLinkedList(self);
			index++;
		}
	}
}

void removePersonInfo(PERSONALINFO *pBook) {
	char name[7];
	int searchIndex = 0;
	int removeNumber = -1;
	char yesno;
	NODE *searchTarget;

	if ( getLengthLinkedList(pBook) == 0 ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printf("삭제할 이름: ");
	scanf("%s", name);

	printHeader();

	while ( searchIndex != NOT_FOUND ) {
		searchIndex = findNameLinkedList(pBook, searchIndex, name);
		if ( searchIndex != NOT_FOUND ) {
			searchTarget = getCurrentPosition(pBook);
			printPersonInfo(searchTarget->info);
		}
	}

	printf("삭제할 번호를 입력하시오.\n");
	printf("번호 : ");
	scanf("%d", &removeNumber);

	fflush(stdin);
	printf("삭제하겠습니까? (y/n) :");
	yesno = getchar();

	if ( yesno == 'y' ) {
		deletePersonInfoWith(pBook, removeNumber);
		printf("삭제되었습니다.\n");
	}
}

void modifyPersonInfo(PERSONALINFO *pBook) {
	char name[7];
	int foundArray[MAX_SIZE] = {-1,};
	int index = 0;
	int foundLength = 0;
	int modifyIndex = -1;
	char yesno;
	PERSONALINFO info;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printf("수정할 이름: ");
	scanf("%s", name);

	foundLength = _searchPersonInfo(name, pBook, foundArray);

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

void searchPersonInfo(PERSONALINFO *pBook) {
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

	foundLength = _searchPersonInfo(name, pBook, foundArray);

	if ( foundLength == 0 ) {
		print_error(ERROR_NOT_SEARCH);
		return ;
	}

	printHeader(TRUE);
	for ( index = 0; index < foundLength; index++ ) {
		printPersonInfo(pBook[foundArray[index]], index + 1);
	}
}

void printHeader() {
	printf("----------------------------------------------\n");
	printf("번호  이름     전화번호      주소\n");
	printf("----------------------------------------------\n");
}

void printPersonInfo(PERSONALINFO *info) {
	printf("%-4d  %-7s  %-12s  %-50s\n", info->number, info->name, info->phone, info->address);
}

void printAllPersonInfo(LINKEDLIST *pBook) {
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

void removeAll(PERSONALINFO *pBook) {
	int index = 0;

	for ( index = 0; index < MAX_SIZE; index++ ) {
		pBook[index].flag = NOT_USE;
	}
}

void saveAddressBook(PERSONALINFO *pBook) {
	FILE *fp = NULL;
	int index = 0;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	fp = fopen("addressbook.dat", "w");

	for ( index = 0; index < MAX_SIZE; index++ ) {
		if ( pBook[index].flag == USE ) {
			fprintf(fp, "%s\n", pBook[index].name);
			fprintf(fp, "%s\n", pBook[index].phone);
			fprintf(fp, "%s\n", pBook[index].address);
		}
	}

	fclose(fp);
	printf("addressbook.dat 파일에 저장하였습니다.\n");
}

void loadAddressBook(PERSONALINFO *pBook) {
	FILE *fp = NULL;
	int index = 0;

	removeAll(pBook);

	fp = fopen("addressbook.dat", "r");

	if ( fp == NULL ) {
		print_error(ERROR_LOAD_FAIL);
		return ;
	}

	while( ! feof(fp) ) {
		fscanf(fp, "%s", pBook[index].name);
		fscanf(fp, "%s", pBook[index].phone);
		fscanf(fp, "%s", pBook[index].address);
		pBook[index].flag = USE;
		index++;
	}

	fclose(fp);
	printf("addressbook.dat 파일을 불러왔습니다.\n");
}

int main(void) {
	int menu = -1;
	LINKEDLIST *book = (LINKEDLIST*)malloc(sizeof(LINKEDLIST));

	createLinkedList(book);

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

	destroyLinkedList(book);

	free(book);

	return EXIT_SUCCESS;
}
