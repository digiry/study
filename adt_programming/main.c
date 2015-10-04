/*
 * main.c
 *
 *  Created on: 2014. 11. 7.
 *      Author: suandkyu
 */

#include <stdio.h>
#include "addressbook.h"

int main(void) {
	int menu = -1;
	ADDRESSBOOK *book;
	book = (ADDRESSBOOK*)malloc(sizeof(ADDRESSBOOK));

	createAddressBook(book);

	book->testSetup(book);

	while ( menu != 0 ) {
		book->printMainMenu(book);

		printf("menu: ");
		scanf("%d", &menu);
		fflush(stdin);

		switch (menu) {
		case MENU_INPUT:
			book->inputPersonInfo(book);
			break;
		case MENU_REMOVE:
			book->removePersonInfo(book);
			break;
		case MENU_MODIFY:
			book->modifyPersonInfo(book);
			break;
		case MENU_SEARCH:
			book->searchPersonInfo(book);
			break;
		case MENU_ALL_PRINT:
			book->printAllPersonInfo(book);
			break;
		case MENU_SAVE:
			book->saveAddressBook(book);
			break;
		case MENU_LOAD:
			book->loadAddressBook(book);
			break;
		case MENU_FINISH:
			book->print_finish(book);
			break;
		default:
			book->print_error(book, ERROR_NO_MENU);
			break;
		}
		if ( menu != MENU_FINISH ) {
			fflush(stdin);
			printf("\nmenu 화면으로 돌아갑니다. (아무키나 누르세요)\n");
			getchar();
		}
	}
	return 0;
}
