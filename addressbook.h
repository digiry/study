/*
 * addressbook.h
 *
 *  Created on: 2014. 10. 15.
 *      Author: suandkyu
 */

#ifndef ADDRESSBOOK_H_
#define ADDRESSBOOK_H_

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

#define USE 1
#define NOT_USE 0

#define TRUE 1
#define FALSE 0

#define MAX_SIZE 10

typedef struct _tag_PERSONALINFO PERSONALINFO;

typedef struct _tag_PERSONALINFO {
	char name[7];
	char phone[12];
	char address[50];
	int number;
} PERSONALINFO;

#endif /* ADDRESSBOOK_H_ */
