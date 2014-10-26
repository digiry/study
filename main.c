/*
 * main.c
 *
 *  Created on: 2014. 9. 17.
 *      Author: suandkyu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header\addressbook.h"

void printMainMenu() {
	printf("1. �ּ������� �Է��Ѵ�.\n");
	printf("2. �ּ������� �����Ѵ�.\n");
	printf("3. �ּ������� �����Ѵ�.\n");
	printf("4. �ּ������� �˻��Ѵ�.\n");
	printf("5. ��ü �ּҷ��� ����Ѵ�.\n");
	printf("6. �ּҷ� ���Ͽ� �����Ѵ�.\n");
	printf("7. �ּҷ� ������ �ҷ��´�.\n");
	printf("0. �����Ѵ�.\n");
}

void print_finish() {
	printf("���α׷��� �����մϴ�.\n");
}

void print_error(int error) {
	switch (error) {
	case ERROR_NO_MENU:
		printf("���� ��ȣ�� �Է��Ͽ����ϴ�.\n");
		break;
	case ERROR_FULL:
		printf("�ּҷ��� ���� á���ϴ�.\n");
		break;
	case ERROR_EMPTY:
		printf("�ּҷ��� ����ֽ��ϴ�.\n");
		break;
	case ERROR_NOT_SEARCH:
		printf("�ּ������� ã�� �� �����ϴ�.\n");
		break;
	case ERROR_LOAD_FAIL:
		printf("addressbook.book ������ �ҷ��ü� �����ϴ�.\n");
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
	int index = 0;
	PERSONALINFO info;
	char yesno;

	if ( isFullAddressBook(pBook) == TRUE ) {
		print_error(ERROR_FULL);
		return ;
	}

	index = findFirstRecordable(pBook);

	printf("�̸� : ");
	scanf("%s", info.name);
	printf("��ȭ��ȣ : ");
	scanf("%s", info.phone);
	printf("�ּ� : ");
	scanf("%s", info.address);

	printf("�Էµ� ����\n");
	printHeader(FALSE);
	printPersonInfo(info, FALSE);

	fflush(stdin);
	printf("�߰��Ͻðڽ��ϱ� ? (y/n) :");
	yesno = getchar();

	if ( yesno == 'y' ) {
		strcpy(pBook[index].name, info.name);
		strcpy(pBook[index].phone, info.phone);
		strcpy(pBook[index].address, info.address);
		pBook[index].flag = USE;
		printf("�߰��Ǿ����ϴ�.\n");
	}
}

int _searchPersonInfo(PERSONALINFO *pBook, char *pName) {
	int index = 0;
	int foundIndex = -1;

	for ( index = 0; index < MAX_SIZE; index++ ) {
		if ( pBook[index].flag == USE ) {
			if ( strcmp(pName, pBook[index].name) == 0 ) {
				foundIndex = index;
				break;
			}
		}
	}

	return foundIndex;
}

void removePersonInfo(PERSONALINFO *pBook) {
	char name[7];
	int removeIndex = -1;
	char yesno;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printf("������ �̸�: ");
	scanf("%s", name);

	removeIndex = _searchPersonInfo(pBook, name);

	if ( removeIndex == -1 ) {
		print_error(ERROR_NOT_SEARCH);
		return ;
	}

	printHeader(FALSE);
	printPersonInfo(pBook[removeIndex], FALSE);

	fflush(stdin);
	printf("�����ϰڽ��ϱ�? (y/n) :");
	yesno = getchar();

	if ( yesno == 'y' ) {
		pBook[removeIndex].flag = NOT_USE;
		printf("�����Ǿ����ϴ�.\n");
	}
}

void modifyPersonInfo(PERSONALINFO *pBook) {
	char name[7];
	int modifyIndex = -1;
	char yesno;
	PERSONALINFO info;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printf("������ �̸�: ");
	scanf("%s", name);

	modifyIndex = _searchPersonInfo(pBook, name);

	if ( modifyIndex == -1 ) {
		print_error(ERROR_NOT_SEARCH);
		return ;
	}

	printHeader(FALSE);
	printPersonInfo(pBook[modifyIndex], FALSE);

	fflush(stdin);
	printf("�����ϰڽ��ϱ�? (y/n) :");
	yesno = getchar();

	if ( yesno == 'y' ) {
		printf("�̸� : ");
		scanf("%s", info.name);
		printf("��ȭ��ȣ : ");
		scanf("%s", info.phone);
		printf("�ּ� : ");
		scanf("%s", info.address);

		printf("������ ����\n");
		printHeader(FALSE);
		printPersonInfo(info, FALSE);

		strcpy(pBook[modifyIndex].name, info.name);
		strcpy(pBook[modifyIndex].phone, info.phone);
		strcpy(pBook[modifyIndex].address, info.address);

		printf("�����Ǿ����ϴ�.\n");
	}
}

void searchPersonInfo(PERSONALINFO *pBook) {
	char name[7];
	int foundIndex = -1;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printf("�˻��� �̸�: ");
	scanf("%s", name);

	foundIndex = _searchPersonInfo(pBook, name);

	if ( foundIndex == -1 ) {
		print_error(ERROR_NOT_SEARCH);
		return ;
	}

	printHeader(FALSE);
	printPersonInfo(pBook[foundIndex], FALSE);
}

void printHeader(int printNum) {
	printf("----------------------------------------------\n");
	if ( printNum == TRUE ) {
		printf("��ȣ  �̸�     ��ȭ��ȣ      �ּ�\n");
	} else {
		printf("�̸�     ��ȭ��ȣ      �ּ�\n");
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

void printAllPersonInfo(PERSONALINFO *pBook) {
	int index = 0;

	if ( isEmptyAddressBook(pBook) == TRUE ) {
		print_error(ERROR_EMPTY);
		return ;
	}

	printHeader(TRUE);
	for ( index = 0; index < MAX_SIZE; index++ ) {
		if ( pBook[index].flag != NOT_USE ) {
			printPersonInfo(pBook[index], index + 1);
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
	printf("addressbook.dat ���Ͽ� �����Ͽ����ϴ�.\n");
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
	printf("addressbook.dat ������ �ҷ��Խ��ϴ�.\n");
}

int main(void) {
	int menu = -1;
//	PERSONALINFO book[MAX_SIZE] = {0,};
	PERSONALINFO book[MAX_SIZE] = {
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
			printf("\nmenu ȭ������ ���ư��ϴ�. (�ƹ�Ű�� ��������)\n");
			getchar();
		}
	}
	return EXIT_SUCCESS;
}
