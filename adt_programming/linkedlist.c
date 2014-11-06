/*
 * linkedlist.c
 *
 *  Created on: 2014. 11. 7.
 *      Author: suandkyu
 */

#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0

void printHeaderLinkedList(int printNum) {
	printf("----------------------------------------------\n");
	if ( printNum == TRUE ) {
		printf("번호  이름     전화번호      주소\n");
	} else {
		printf("이름     전화번호      주소\n");
	}
	printf("----------------------------------------------\n");
}

void printPersonInfoLinkedList(PERSONALINFO *info, int printNum) {
	if ( printNum != FALSE ) {
		printf("%-4d  %-7s  %-12s  %-50s\n", printNum, info->name, info->phone, info->address);
	} else {
		printf("%-8s  %-12s  %-50s\n", info->name, info->phone, info->address);
	}
}

void printLinedList(LINKEDLIST *self) {
	int number = 1;
	NODE *target;

	printHeaderLinkedList(TRUE);

	target = self->moveFirstLinkedList(self);
	while ( self->isTailLinkedList(self) != TRUE ) {
		printPersonInfoLinkedList(target->info, number);
		target = self->nextLinkedList(self);
		number++;
	}
}


int main(void) {
	LINKEDLIST *list;

	PERSONALINFO info1 = {"aaa", "0001110000", "xxx", USE};
	PERSONALINFO info2 = {"bbb", "0002220000", "yyy", USE};
	PERSONALINFO info3 = {"ccc", "0003330000", "zzz", USE};

	list = (LINKEDLIST*)malloc(sizeof(LINKEDLIST));

	createLinkedList(list);

	list->appendLinkedList(list, &info1);
	list->appendLinkedList(list, &info2);
	list->insertLinkedList(list, 1, &info3);

	printLinedList(list);

	destroyLinkedList(list);

	free(list);

	return 0;
}

#endif

void createLinkedList(LINKEDLIST *self) {
	self->head = (NODE*)malloc(sizeof(NODE));
	self->tail = (NODE*)malloc(sizeof(NODE));

	self->head->next = self->tail;
	self->tail->next = NULL;
	self->pos = self->head->next;
	self->length = 0;

	self->appendLinkedList = *appendLinkedList;
	self->moveToBeforeNodeLinkedList = *moveToBeforeNodeLinkedList;
	self->insertLinkedList = *insertLinkedList;
	self->deleteLinkedList = *deleteLinkedList;
	self->deleteAllLinkedList = *deleteAllLinkedList;
	self->viewAtLinkedList = *viewAtLinkedList;
	self->moveFirstLinkedList = *moveFirstLinkedList;
	self->moveLastLinkedList = *moveLastLinkedList;
	self->nextLinkedList = *nextLinkedList;
	self->isTailLinkedList = *isTailLinkedList;
	self->getLengthLinkedList = *getLengthLinkedList;
	self->getNodeLinkedList = *getNodeLinkedList;
	self->findNameLinkedList = *findNameLinkedList;
}


void destroyLinkedList(LINKEDLIST *self) {

	if ( self->length > 0 ) {
		self->deleteAllLinkedList(self);
	}

	free(self->head);
	free(self->tail);

	self->pos = NULL;
	self->length = 0;
}

void appendLinkedList(LINKEDLIST *self, PERSONALINFO* p_info) {
	NODE *last = self->moveLastLinkedList(self);
	NODE *new = (NODE*)malloc(sizeof(NODE));

	new->info = (PERSONALINFO*)malloc(sizeof(PERSONALINFO));
	strcpy(new->info->name, p_info->name);
	strcpy(new->info->phone, p_info->phone);
	strcpy(new->info->address, p_info->address);
	self->length++;

	new->next = last->next;
	last->next = new;

	self->pos = new;

	last = NULL;
	new = NULL;
}

NODE* moveToBeforeNodeLinkedList(LINKEDLIST *self, int index) {
	NODE *target;
	int i = 0;

	if ( index <= 0 ) {
		target = self->head;
	} else {
		target = self->moveFirstLinkedList(self);
		while ( i < index - 1 ) {
			target = self->nextLinkedList(self);
			i++;
		}
	}

	return target;
}

void insertLinkedList(LINKEDLIST *self, int index, PERSONALINFO* p_info) {
	NODE *target;
	NODE *new = (NODE*)malloc(sizeof(NODE));

	target = self->moveToBeforeNodeLinkedList(self, index);

	new->info = (PERSONALINFO*)malloc(sizeof(PERSONALINFO));
	strcpy(new->info->name, p_info->name);
	strcpy(new->info->phone, p_info->phone);
	strcpy(new->info->address, p_info->address);
	self->length++;

	new->next = target->next;
	target->next = new;

	self->pos = new;

	target = NULL;
	new = NULL;
}

void deleteLinkedList(LINKEDLIST *self, int index) {
	NODE *before;
	NODE *target;

	before = self->moveToBeforeNodeLinkedList(self, index);

	target = before->next;
	before->next = target->next;

	free(target->info);
	target->next = NULL;
	free(target);

	self->pos = before;
	self->length--;

	before = NULL;
	target = NULL;
}

void deleteAllLinkedList(LINKEDLIST *self) {

	if ( self->length == 0 ) {
		return ;
	}

	while ( self->getLengthLinkedList(self) > 0 ) {
		self->deleteLinkedList(self, 0);
	}

	self->pos = self->head;
}

PERSONALINFO viewAtLinkedList(LINKEDLIST *self, int index) {
	PERSONALINFO info;
	NODE *target;

	target = self->moveToBeforeNodeLinkedList(self, index)->next;

	strcpy(info.name, target->info->name);
	strcpy(info.phone, target->info->phone);
	strcpy(info.address, target->info->address);

	self->pos = target;

	target = NULL;

	return info;
}

NODE* moveFirstLinkedList(LINKEDLIST *self) {
	self->pos = self->head->next;

	return self->pos;
}

NODE* moveLastLinkedList(LINKEDLIST *self) {
	NODE *target;
	if ( self->length <= 0 ) {
		target = self->head;
	} else {
		target = self->moveToBeforeNodeLinkedList(self, self->length - 1)->next;
	}

	self->pos = target;

	return target;
}

NODE* nextLinkedList(LINKEDLIST *self) {
	self->pos = self->pos->next;

	return self->pos;
}

int isTailLinkedList(LINKEDLIST *self) {
	int isTail = FALSE;

	if ( self->pos->next == NULL ) {
		isTail = TRUE;
	}

	return isTail;
}

int getLengthLinkedList(LINKEDLIST *self) {
	return self->length;
}

NODE* getNodeLinkedList(LINKEDLIST *self, int index) {
	NODE *target;

	target = self->moveToBeforeNodeLinkedList(self, index)->next;

	return target;
}

int findNameLinkedList(LINKEDLIST *self, char* p_name) {
	int index = 0;
	int isFound = FALSE;

	self->moveFirstLinkedList(self);
	while ( self->isTailLinkedList(self) != TRUE ) {
		if ( strcmp(self->pos->info->name, p_name) == 0 ) {
			isFound = TRUE;
			break;
		}
		self->nextLinkedList(self);
		index++;
	}

	if ( isFound == FALSE ) {
		index = -1;
	}

	return index;
}
