/*
 * addressbook.h
 *
 *  Created on: 2014. 11. 7.
 *      Author: suandkyu
 */


#ifndef ADDRESSBOOK_H_
#define ADDRESSBOOK_H_

#include "personinfo.h"
#include "linkedlist.h"

#define MENU_INPUT 1
#define MENU_REMOVE 2
#define MENU_MODIFY 3
#define MENU_SEARCH 4
#define MENU_ALL_PRINT 5
#define MENU_SAVE 6
#define MENU_LOAD 7
#define MENU_FINISH 0

#define ERROR_NO_MENU 1
#define ERROR_FULL 2
#define ERROR_EMPTY 3
#define ERROR_NOT_SEARCH 4
#define ERROR_LOAD_FAIL 5

#define TRUE 1
#define FALSE 0

typedef struct _tag_ADDRESSBOOK ADDRESSBOOK;

typedef struct _tag_ADDRESSBOOK {
	LINKEDLIST *list;

	void (*printMainMenu)(ADDRESSBOOK *);
	void (*print_finish)(ADDRESSBOOK *);
	void (*print_error)(ADDRESSBOOK *, int);
	int (*isEmptyAddressBook)(ADDRESSBOOK *);
	void (*inputPersonInfo)(ADDRESSBOOK *);
	void (*removePersonInfo)(ADDRESSBOOK *);
	void (*modifyPersonInfo)(ADDRESSBOOK *);
	void (*searchPersonInfo)(ADDRESSBOOK *);
	void (*printHeader)(ADDRESSBOOK *, int);
	void (*printPersonInfo)(ADDRESSBOOK *, PERSONALINFO, int);
	void (*printPersonInfoPointer)(ADDRESSBOOK *, PERSONALINFO *, int );
	void (*printAllPersonInfo)(ADDRESSBOOK *);
	void (*saveAddressBook)(ADDRESSBOOK *);
	void (*loadAddressBook)(ADDRESSBOOK *);
	void (*testSetup)(ADDRESSBOOK *);
} ADDRESSBOOK;

void createAddressBook(ADDRESSBOOK *self);
void destroyAddressBook(ADDRESSBOOK *self);
void printMainMenu(ADDRESSBOOK *self);
void print_finish(ADDRESSBOOK *self);
void print_error(ADDRESSBOOK *self, int error);
int isEmptyAddressBook(ADDRESSBOOK *self);
void inputPersonInfo(ADDRESSBOOK *self);
void removePersonInfo(ADDRESSBOOK *self);
void modifyPersonInfo(ADDRESSBOOK *self);
void searchPersonInfo(ADDRESSBOOK *self);
void printHeader(ADDRESSBOOK *self, int printNum);
void printPersonInfo(ADDRESSBOOK *self, PERSONALINFO info, int printNum);
void printPersonInfoPointer(ADDRESSBOOK *self, PERSONALINFO *info, int printNum);
void printAllPersonInfo(ADDRESSBOOK *self);
void saveAddressBook(ADDRESSBOOK *self);
void loadAddressBook(ADDRESSBOOK *self);
void testSetup(ADDRESSBOOK *self);

#endif /* ADDRESSBOOK_H_ */
