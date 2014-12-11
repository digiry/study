/*
* personInfoCpp.h
*
*  Created on: 2014. 11. 16.
*      Author: suandkyu
*/

#ifndef ADDRESSBOOK_H_
#define ADDRESSBOOK_H_

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

class addressbook {
public:
	linkedlist *list;

	addressbook();
	~addressbook();

	void printMainMenu();
	void print_finish();
	void print_error(int error);
	bool isEmpty();
	void input();
	void remove();
	void modify();
	void search();
	void printHeader(int printNum);
	void printPersonInfo(personInfo &info, int printNum);
	void printAll();
	void save();
	void load();
	void testSetup();
};

#endif /* ADDRESSBOOK_H_ */
