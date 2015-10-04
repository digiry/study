/*
 * linkedlist.h
 *
 *  Created on: 2014. 11. 7.
 *      Author: suandkyu
 */

#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#define USE 1
#define NOT_USE 0

#define TRUE 1
#define FALSE 0

#include "personinfo.h"

typedef struct _tag_NODE NODE;
typedef struct _tag_LINKEDLIST LINKEDLIST;

typedef struct _tag_NODE {
	PERSONALINFO *info;
	NODE *next;
} NODE;

typedef struct _tag_LINKEDLIST {
	NODE *head;
	NODE *tail;
	NODE *pos;
	int length;

	void (*appendLinkedList)(LINKEDLIST *, PERSONALINFO*);
	NODE* (*moveToBeforeNodeLinkedList)(LINKEDLIST *, int);
	void (*insertLinkedList)(LINKEDLIST *, int, PERSONALINFO*);
	void (*deleteLinkedList)(LINKEDLIST *, int);
	void (*deleteAllLinkedList)(LINKEDLIST *);
	PERSONALINFO (*viewAtLinkedList)(LINKEDLIST *, int);
	NODE* (*moveFirstLinkedList)(LINKEDLIST *);
	NODE* (*moveLastLinkedList)(LINKEDLIST *);
	NODE* (*nextLinkedList)(LINKEDLIST *);
	int (*isTailLinkedList)(LINKEDLIST *);
	int (*getLengthLinkedList)(LINKEDLIST *);
	NODE* (*getNodeLinkedList)(LINKEDLIST *, int);
	int (*findNameLinkedList)(LINKEDLIST *, char*);
} LINKEDLIST;

void createLinkedList(LINKEDLIST *self);

void destroyLinkedList(LINKEDLIST *self);

void appendLinkedList(LINKEDLIST *self, PERSONALINFO* p_info);

NODE* moveToBeforeNodeLinkedList(LINKEDLIST *self, int index);

void insertLinkedList(LINKEDLIST *self, int index, PERSONALINFO* p_info);

void deleteLinkedList(LINKEDLIST *self, int index);

void deleteAllLinkedList(LINKEDLIST *self);

PERSONALINFO viewAtLinkedList(LINKEDLIST *self, int index);

NODE* moveFirstLinkedList(LINKEDLIST *self);

NODE* moveLastLinkedList(LINKEDLIST *self);

NODE* nextLinkedList(LINKEDLIST *self);

int isTailLinkedList(LINKEDLIST *self);

int getLengthLinkedList(LINKEDLIST *self);

NODE* getNodeLinkedList(LINKEDLIST *self, int index);

int findNameLinkedList(LINKEDLIST *self, char* p_name);

#endif // __LINKEDLIST__
