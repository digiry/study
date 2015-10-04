// LIST_ADT
// ���α׷� �� : LIST_ADT.c
// �� �� �� : NINAEROS.AGAFE
// �����ۼ��� : 05/01/11
// �� �� �� : 05/01/12

#include <stdio.h>
#include <stdlib.h>
#include "NODE_ADT.h"
#include "LIST_ADT.h"

#if 0
//����
void CreateList(LIST *self)
{
	self->head = (NODE *)malloc(sizeof(NODE));	// head ����
	self->tail = (NODE *)malloc(sizeof(NODE));	// tail ����
	// head link �ʱ�ȭ
	self->head->Llink = self->head;				
	self->head->Rlink = self->tail;
	// tail link �ʱ�ȭ
	self->tail->Llink = self->head;
	self->tail->Rlink = self->tail;
	// self ��� ���� �ʱ�ȭ
	self->count = 0;
	// self ������ġ �ʱ�ȭ
	self->Currentposition = self->head;

	// �Լ� ����
	self->DestroyList = *DestroyList;
	self->InsertHead = *InsertHead;
	self->InsertTail = *InsertTail;
	self->InsertBefore = *InsertBefore;
	self->InsertAfter = *InsertAfter;
	self->InsertSort = *InsertSort;
	self->DeleteHead = *DeleteHead;
	self->DeleteTail = *DeleteTail;
	self->DeleteBefore = *DeleteBefore;
	self->DeleteAfter = *DeleteAfter;
	self->DeleteAll = *DeleteAll;
	self->MoveNext = *MoveNext;
	self->MovePrivious = *MovePrivious;
	self->MoveFirst = *MoveFirst;
	self->MoveLast = *MoveLast;
	self->GetNode = *GetNode;
	self->SetNode = *SetNode;
	self->SearchNode = *SearchNode;
	self->GetCount = *GetCount;
	self->PrintList = *PrintList;
}

//�Ҹ�
void DestroyList(LIST *self)
{
	// ��� ���� ����
	self->DeleteAll(self);
	// �Ӹ� ����
	free(self->head);
	// ���� ����
	free(self->tail);
}

// ���� (�Ӹ�, ���� ,����, ����, ����)
void InsertHead(LIST *self, int data)
{
	// ������ node ����
	NODE *source;
	source = (NODE *)malloc(sizeof(NODE));
	source->data = data;
	// node ����
	source->Llink = self->head;
	source->Rlink = self->head->Rlink;
	self->head->Rlink = source;
	source->Rlink->Llink = source;
	
	self->Currentposition = source;

	self->count++;
}

void InsertTail(LIST *self, int data)
{
	// ������ node ����
	NODE *source;
	source = (NODE *)malloc(sizeof(NODE));
	source->data = data;
	// node ����
	source->Llink = self->tail->Llink;
	source->Rlink = self->tail;
	self->tail->Llink->Rlink = source;
	self->tail->Llink = source;

	self->Currentposition = source;
	
	self->count++;
}

int InsertBefore(LIST *self, int key, int data)
{
	int true_count;

	NODE *source;
	NODE *dest;

	true_count = 0;

	dest = self->head->Rlink;	// ó�� node

	// �Ӹ����� �������� �ݺ�
	while( (!true_count) && (dest != self->tail) )
	{
		//key �� ��
		if( key == dest->data )
		{
			// ������ node ����
			source = (NODE *)malloc(sizeof(NODE));
			source->data = data;
			// ����
			source->Llink = dest->Llink;
			source->Rlink = dest;
			dest->Llink->Rlink = source;
			
			self->Currentposition = source;
			self->count++;
			//�ݺ� ����
			true_count = 1;
		}
		else
		{
			//node �̵�
			dest = dest->Rlink;
		}
	}
	return true_count;
}

int InsertAfter(LIST *self, int key, int data)
{
	int true_count;

	NODE *source;
	NODE *dest;

	true_count = 0;

	// node ó��
	dest = self->head->Rlink;

	// �Ӹ� ���� ���� ���� �ݺ�
	while( (!true_count) && (dest != self->tail) )
	{
		// ��
		if( key == dest->data )
		{
			// ������ node ����
			source = (NODE *)malloc(sizeof(NODE));
			source->data = data;
			// node ����
			source->Llink = dest;
			source->Rlink = dest->Rlink;
			dest->Rlink->Llink = source;
			dest->Rlink = source;
			
			self->Currentposition = source;
			self->count++;
			// �ݺ� ����
			true_count = 1;
		}
		else
		{
			dest = dest->Rlink;
		}
	}
	return true_count;
}

void InsertSort(LIST *self, int data)
{
	NODE *source;
	NODE *dest;

	source = (NODE*)malloc(sizeof(NODE));
	source->data = data;

	dest = self->head->Rlink;

	// ������ �ƴϰ� data���� ū���� �ݺ�(��������)
	while( (dest != self->tail) && (data >= dest->data) )
	{
		// ���� node�� �̵�
		dest = dest->Llink;
	}
	// ����
	source->Llink = dest->Llink;
	source->Rlink = dest;
	dest->Llink->Rlink = source;
	dest->Llink = source;

	self->Currentposition = source;
	self->count++;
}

// ���� (�Ӹ�, ����, ����, ����, ����)
int DeleteHead(LIST *self)
{
	int true_count;

	NODE *temp;		//�ӽ� node

	// �Ӹ� ���� ��� ����
	if( self->head->Rlink == self->tail )
	{
		true_count = 0;
	}
	else
	{
		//������ node �� temp�� ����
		temp = self->head->Rlink;
		self->head->Rlink = temp->Rlink;
		temp->Rlink->Llink = self->head;
		free(temp);

		self->Currentposition = self->head->Rlink;
		self->count--;
		true_count = 1;
	}
	return true_count;
}

int DeleteTail(LIST *self)
{
	int true_count;

	NODE *temp;

	// ���� �� ��� ����
	if( self->tail->Llink == self->head )
	{
		true_count = 0;
	}
	else
	{
		//������ node �� temp�� ����
		temp = self->tail->Llink;
		self->tail->Llink = temp->Llink;
		temp->Llink->Rlink = self->tail;
		free(temp);

		self->Currentposition = self->tail->Llink;
		self->count--;
		true_count = 1;
	}
	return true_count;
}

int DeleteBefore(LIST *self, int key)
{
	int true_count;
	NODE *temp;

	true_count = 0;
	temp = self->head->Rlink;
	// key���� ã�������� �Ӹ����� �������� �̵�
	while( (temp->Rlink != self->tail) && (key != temp->data) )
	{
		temp = temp->Rlink;
	}
	// key������ �ƴ��� �˻�
	if( (key == temp->data) && (temp->Llink != self->head) )
	{
		// key �� node ����
		temp = temp->Llink;
		temp->Rlink->Llink = temp->Llink;
		temp->Llink->Rlink = temp->Rlink;

		self->Currentposition = temp->Rlink;
		free(temp);

		self->count--;
		true_count = 1;
	}
	return true_count;
}

int DeleteAfter(LIST *self, int key)
{
	int true_count;
	NODE *temp;

	true_count = 0;

	temp = self->head->Rlink;

	// key���� ã�������� �̵�
	while( (temp != self->tail) && (key != temp->data) )
	{
		temp = temp->Rlink;
	}
	if( (key == temp->data) && (temp->Rlink != self->tail) )
	{
		temp = temp->Rlink;
		temp->Rlink->Llink = temp->Llink;
		temp->Llink->Rlink = temp->Rlink;
		self->Currentposition = temp->Llink;

		free(temp);

		self->count--;
		true_count = 1;
	}
	return true_count;
}

void DeleteAll(LIST *self)
{
	NODE *temp;

	// �Ӹ��� ���� ���� ��� ��� ����
	while( self->head->Rlink != self->tail )
	{
		temp = self->head->Rlink;
		temp->Rlink->Llink = self->head;
		self->head->Rlink = temp->Rlink;
		free(temp);
	}
	self->Currentposition = self->head;
	self->count = 0;
}

// ��ġ�̵� (��, ��, ó��, ������)
void MoveNext(LIST *self)
{
	// ������ġ ������ �����ϰ��
	if( self->Currentposition->Rlink == self->tail )
	{
		self->Currentposition = self->head;
	}
	else
	{
		self->Currentposition = self->Currentposition->Rlink;
	}
}

void MovePrivious(LIST *self)
{
	self->Currentposition = self->Currentposition->Llink;
}

void MoveFirst(LIST *self)
{
	// ��Ұ� ���� ���
	if( self->head->Rlink == self->tail )
	{
		self->Currentposition = self->head;
	}
	else
	{
		self->Currentposition = self->head->Rlink;
	}
}

void MoveLast(LIST *self)
{
	// ��Ұ� ���� ���
	if( self->head->Rlink == self->tail )
	{
		self->Currentposition = self->head;
	}
	else
	{
		self->Currentposition = self->tail->Llink;
	}
}

// �б� ����
int GetNode(LIST *self, int index)
{
	NODE *dest;

	int i;

	dest = self->head;
	// index ��ŭ �̵�
	for( i = 0; i < index; i++ )
	{
		dest = dest->Rlink;
	}
	return dest->data;
}

int SetNode(LIST *self, int key, int data)
{
	int true_count;
	NODE *dest;

	dest = self->head->Rlink;

	// key �� �� ã�������� �̵�
	while( (dest != self->tail) && (key != dest->data) )
	{
		dest = dest->Rlink;
	}
	// key���� ã�Ҵ��� �˻�
	if( key == dest->data )
	{
		dest->data = data;
		true_count = 1;
		self->Currentposition = dest;
	}
	else
	{
		true_count = 0;
	}
	return true_count;
}

// �˻�
int SearchNode(LIST *self, int key)
{
	int index;
	int count = 0;
	NODE *dest;

	dest = self->head->Rlink;
	index = -1;

	// key�� ��ġ ã��
	while( (dest != self->tail) && (key != dest->data) )
	{
		dest = dest->Rlink;
		count++;
	}
	if( key == dest->data )
	{
		index = count;
	}
	return index;
}

// ��Ұ��� ���
int GetCount(LIST *self)
{
	return self->count;
}

// ��� ���
void PrintList(LIST *self)
{
	NODE *dest;
	dest = self->head->Rlink;

	while( dest != self->tail )
	{
		printf(" %d ", dest->data );
		dest = dest->Rlink;
	}
}

#endif
