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
	printPersonInfo(info, -1);

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

int _searchPERSONALINFO(char *pName, PERSONALINFO *pBook, int *pFoundArray) {
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

void removePersonInfo(PERSONALINFO *pBook) {
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

	printf("������ �̸�: ");
	scanf("%s", name);

	foundLength = _searchPERSONALINFO(name, pBook, foundArray);

	if ( foundLength == 0 ) {
		print_error(ERROR_NOT_SEARCH);
		return ;
	}

	printHeader(TRUE);
	for ( index = 0; index < foundLength; index++ ) {
		printPersonInfo(pBook[foundArray[index]], index + 1);
	}

	printf("������ ��ȣ�� �Է��Ͻÿ�.\n");
	printf("��ȣ : ");
	scanf("%d", &removeIndex);

	fflush(stdin);
	printf("�����ϰڽ��ϱ�? (y/n) :");
	yesno = getchar();

	if ( yesno == 'y' ) {
		pBook[foundArray[removeIndex - 1]].flag = NOT_USE;
		printf("�����Ǿ����ϴ�.\n");
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

	printf("������ �̸�: ");
	scanf("%s", name);

	foundLength = _searchPERSONALINFO(name, pBook, foundArray);

	if ( foundLength == 0 ) {
		print_error(ERROR_NOT_SEARCH);
		return ;
	}

	printHeader(TRUE);
	for ( index = 0; index < foundLength; index++ ) {
		printPersonInfo(pBook[foundArray[index]], index + 1);
	}

	printf("������ ��ȣ�� �Է��Ͻÿ�.\n");
	printf("��ȣ : ");
	scanf("%d", &modifyIndex);

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
		printPersonInfo(info, -1);

		strcpy(pBook[foundArray[modifyIndex - 1]].name, info.name);
		strcpy(pBook[foundArray[modifyIndex - 1]].phone, info.phone);
		strcpy(pBook[foundArray[modifyIndex - 1]].address, info.address);

		printf("�����Ǿ����ϴ�.\n");
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

	printf("�˻��� �̸�: ");
	scanf("%s", name);

	foundLength = _searchPERSONALINFO(name, pBook, foundArray);

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
		printf("��ȣ  �̸�     ��ȭ��ȣ      �ּ�\n");
	} else {
		printf("�̸�     ��ȭ��ȣ      �ּ�\n");
	}
	printf("----------------------------------------------\n");
}

void printPersonInfo(PERSONALINFO info, int printNum) {
	if ( printNum != -1 ) {
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
	PERSONALINFO book[MAX_SIZE] = {0,};
//	PERSONALINFO book[MAX_SIZE] = {
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
