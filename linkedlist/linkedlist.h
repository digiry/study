#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#define USE 1
#define NOT_USE 0

#define TRUE 1
#define FALSE 0

typedef struct _tag_PERSONALINFO PERSONALINFO;
typedef struct _tag_NODE NODE;
typedef struct _tag_LINKEDLIST LINKEDLIST;

typedef struct _tag_PERSONALINFO {
	char name[7];
	char phone[12];
	char address[50];
	int flag;
} PERSONALINFO;

typedef struct _tag_NODE {
	PERSONALINFO *info;
	NODE *next;
} NODE;

typedef struct _tag_LINKEDLIST {
	NODE *head;
	NODE *tail;
	NODE *pos;
	int length;
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

NODE* findNameLinkedList(LINKEDLIST *self, NODE* beginNode, char* p_name);

#endif // __LINKEDLIST__
