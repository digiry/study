#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#define USE 1
#define NOT_USE 0

#define TRUE 1
#define FALSE 0

typedef struct _tag_personalInfo {
	char name[7];
	char phone[12];
	char address[50];
	int flag;
} personalInfo;

typedef struct _tag_NODE {
	personalInfo *info;
	struct _tag_NODE *next;
} NODE;

typedef struct _tag_LINKEDLIST {
	NODE *head;
	NODE *tail;
	NODE *pos;
	int length;
} LINKEDLIST;

LINKEDLIST* createLinkedList(LINKEDLIST *self);

void destroyLinkedList(LINKEDLIST *self);

LINKEDLIST* appendLinkedList(LINKEDLIST *self, personalInfo* p_info);

NODE* moveToBeforeNodeLinkedList(LINKEDLIST *self, int index);

LINKEDLIST* insertLinkedList(LINKEDLIST *self, int index, personalInfo* p_info);

LINKEDLIST* deleteLinkedList(LINKEDLIST *self, int index);

LINKEDLIST* deleteAllLinkedList(LINKEDLIST *self);

personalInfo viewAtLinkedList(LINKEDLIST *self, int index);

NODE* moveFirstLinkedList(LINKEDLIST *self);

NODE* moveLastLinkedList(LINKEDLIST *self);

NODE* nextLinkedList(LINKEDLIST *self);

int isTailLinkedList(LINKEDLIST *self);

int getLengthLinkedList(LINKEDLIST *self);

NODE* findNameLinkedList(LINKEDLIST *self, NODE* beginNode, char* p_name);

#endif // __LINKEDLIST__
