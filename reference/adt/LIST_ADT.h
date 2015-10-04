// LIST_ADT
// ���α׷� �� : LIST_ADT.h
// �� �� �� : NINAEROS.AGAFE
// �����ۼ��� : 05/01/11
// �� �� �� : 05/01/12

#include "NODE_ADT.h"

typedef struct __LIST LIST;

#ifndef __LIST_ADT_H
#define __LIST_ADT_H

typedef struct __LIST
{
	NODE *head;
	NODE *tail;
	int count;
	NODE *Currentposition;

	void (*DestroyList)(LIST *);
	void (*InsertHead)(LIST *, int );
	void (*InsertTail)(LIST *, int );
	int (*InsertBefore)(LIST *,int ,int );
	int (*InsertAfter)(LIST *, int , int );
	void (*InsertSort)(LIST *, int );
	int (*DeleteHead)(LIST *);
	int (*DeleteTail)(LIST *);
	int (*DeleteBefore)(LIST *, int );
	int (*DeleteAfter)(LIST *, int );
	void (*DeleteAll)(LIST *);
	void (*MoveNext)(LIST *);
	void (*MovePrivious)(LIST *);
	void (*MoveFirst)(LIST *);
	void (*MoveLast)(LIST *);
	int (*GetNode)(LIST *, int );
	int (*SetNode)(LIST *, int, int );
	int (*SearchNode)(LIST *, int );
	int (*GetCount)(LIST *);
	void (*PrintList)(LIST *);
} LIST;

	//����
	void CreateList(LIST *);
	//�Ҹ�
	void DestroyList(LIST *);
	// ���� (�Ӹ�, ���� ,����, ����, ����)
	void InsertHead(LIST *, int );
	void InsertTail(LIST *, int );
	int InsertBefore(LIST *,int ,int );
	int InsertAfter(LIST *, int , int );
	void InsertSort(LIST *, int );
	// ���� (�Ӹ�, ����, ����, ����, ����)
	int DeleteHead(LIST *);
	int DeleteTail(LIST *);
	int DeleteBefore(LIST *, int );
	int DeleteAfter(LIST *, int );
	void DeleteAll(LIST *);
	// ��ġ�̵� (��, ��, ó��, ������)
	void MoveNext(LIST *);
	void MovePrivious(LIST *);
	void MoveFirst(LIST *);
	void MoveLast(LIST *);
	// �б� ����
	int GetNode(LIST *, int );
	int SetNode(LIST *, int, int );
	// �˻�
	int SearchNode(LIST *, int );
	// ��Ұ��� ���
	int GetCount(LIST *);
	// ��� ���
	void PrintList(LIST *);

#endif __LIST_ADT_H
