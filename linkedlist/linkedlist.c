/*
 * linkedlist.c
 *
 *  Created on: 2014. 10. 10.
 *      Author: suandkyu
 */
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printHeader(int printNum) {
	printf("----------------------------------------------\n");
	if ( printNum == TRUE ) {
		printf("번호  이름     전화번호      주소\n");
	} else {
		printf("이름     전화번호      주소\n");
	}
	printf("----------------------------------------------\n");
}

void printPersonInfo(personalInfo *info, int printNum) {
	if ( printNum != -1 ) {
		printf("%-4d  %-7s  %-12s  %-50s\n", printNum, info->name, info->phone, info->address);
	} else {
		printf("%-8s  %-12s  %-50s\n", info->name, info->phone, info->address);
	}
}

void printLinedList(LINKEDLIST *self) {
	int number = 1;
	NODE *target;

	printHeader(TRUE);

	target = moveFirstLinkedList(self);
	while ( isTailLinkedList(self) != TRUE ) {
		printPersonInfo(target->info, number);
		target = nextLinkedList(self);
		number++;
	}
}


int main(void) {
	LINKEDLIST *list;

	personalInfo info1 = {"aaa", "0001110000", "xxx", USE};
	personalInfo info2 = {"bbb", "0002220000", "yyy", USE};
	personalInfo info3 = {"ccc", "0003330000", "zzz", USE};

	list = createLinkedList(list);

	list = appendLinkedList(list, &info1);
	list = appendLinkedList(list, &info2);
	list = insertLinkedList(list, 1, &info3);

	printLinedList(list);

	destroyLinkedList(list);
	return 0;
}

LINKEDLIST* createLinkedList(LINKEDLIST *self) {
	self = (LINKEDLIST*)malloc(sizeof(LINKEDLIST));
	self->head = (NODE*)malloc(sizeof(NODE));
	self->tail = (NODE*)malloc(sizeof(NODE));

	self->head->next = self->tail;
	self->tail->next = NULL;
	self->pos = self->head;
	self->length = 0;

	return self;
}

void destroyLinkedList(LINKEDLIST *self) {

	if ( self->length > 0 ) {
		self = deleteAllLinkedList(self);
	}

	free(self->head);
	free(self->tail);

	self->pos = NULL;
	self->length = 0;

	free(self);
}

LINKEDLIST* appendLinkedList(LINKEDLIST *self, personalInfo* p_info) {
	NODE *last = moveLastLinkedList(self);
	NODE *new = (NODE*)malloc(sizeof(NODE));

	new->info = (personalInfo*)malloc(sizeof(personalInfo));
	strcpy(new->info->name, p_info->name);
	strcpy(new->info->phone, p_info->phone);
	strcpy(new->info->address, p_info->address);
	new->info->flag = p_info->flag;
	self->length++;

	new->next = last->next;
	last->next = new;

	self->pos = new;

	last = NULL;
	new = NULL;

	return self;
}

NODE* moveToBeforeNodeLinkedList(LINKEDLIST *self, int index) {
	NODE *target;
	int i = 0;

	if ( index <= 0 ) {
		target = self->head;
	} else {
		target = moveFirstLinkedList(self);
		while ( i < index - 1 ) {
			target = nextLinkedList(self);
			i++;
		}
	}

	return target;
}

LINKEDLIST* insertLinkedList(LINKEDLIST *self, int index, personalInfo* p_info) {
	NODE *target;
	NODE *new = (NODE*)malloc(sizeof(NODE));

	target = moveToBeforeNodeLinkedList(self, index);

	new->info = (personalInfo*)malloc(sizeof(personalInfo));
	strcpy(new->info->name, p_info->name);
	strcpy(new->info->phone, p_info->phone);
	strcpy(new->info->address, p_info->address);
	new->info->flag = p_info->flag;
	self->length++;

	new->next = target->next;
	target->next = new;

	self->pos = new;

	target = NULL;
	new = NULL;

	return self;
}

LINKEDLIST* deleteLinkedList(LINKEDLIST *self, int index) {
	NODE *before;
	NODE *target;
	NODE *next;

	before = moveToBeforeNodeLinkedList(self, index);

	target = before->next;
	next = target->next;

	before->next = next;

	free(target->info);
	free(target);
	target->next = NULL;

	self->pos = before;
	self->length--;

	before = NULL;
	target = NULL;
	next = NULL;

	return self;

}

LINKEDLIST* deleteAllLinkedList(LINKEDLIST *self) {
	int index = 0;

	if ( self->length == 0 ) {
		return self;
	}

	//index error, please change while root or index=0
	for ( index = 0; index < self->length; index++ ) {
		self = deleteLinkedList(self, index);
	}

	self->pos = self->head;

	return self;
}

// pointer로 반환형 변환필요
personalInfo viewAtLinkedList(LINKEDLIST *self, int index) {
	personalInfo info;
	NODE *target;

	target = moveToBeforeNodeLinkedList(self, index)->next;

	// pointer로 변경되면 주석처리
	strcpy(info.name, target->info->name);
	strcpy(info.phone, target->info->phone);
	strcpy(info.address, target->info->address);
	info.flag = target->info->flag;

	self->pos = target;

	target = NULL;

	return info;
	//return target->next->personalInfo;
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
		target = moveToBeforeNodeLinkedList(self, self->length - 1)->next;
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

	if ( self->pos == self->tail ) {
		isTail = TRUE;
	}

	return isTail;
}

int getLengthLinkedList(LINKEDLIST *self) {
	return self->length;
}

NODE* findNameLinkedList(LINKEDLIST *self, NODE* beginNode, char* p_name) {
	self->pos = beginNode;

	while ( isTailLinkedList(self) != TRUE ) {
		if ( strcmp(self->pos->info->name, p_name) == 0 ) {
			break;
		}
		nextLinkedList(self);
	}

	return self->pos;
}
