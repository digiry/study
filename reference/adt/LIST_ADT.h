// LIST_ADT
// 프로그램 명 : LIST_ADT.h
// 작 성 자 : NINAEROS.AGAFE
// 최초작성일 : 05/01/11
// 수 정 일 : 05/01/12

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

	//생성
	void CreateList(LIST *);
	//소멸
	void DestroyList(LIST *);
	// 삽입 (머리, 꼬리 ,값앞, 값뒤, 정렬)
	void InsertHead(LIST *, int );
	void InsertTail(LIST *, int );
	int InsertBefore(LIST *,int ,int );
	int InsertAfter(LIST *, int , int );
	void InsertSort(LIST *, int );
	// 삭제 (머리, 꼬리, 값앞, 값뒤, 전부)
	int DeleteHead(LIST *);
	int DeleteTail(LIST *);
	int DeleteBefore(LIST *, int );
	int DeleteAfter(LIST *, int );
	void DeleteAll(LIST *);
	// 위치이동 (후, 전, 처음, 마지막)
	void MoveNext(LIST *);
	void MovePrivious(LIST *);
	void MoveFirst(LIST *);
	void MoveLast(LIST *);
	// 읽기 쓰기
	int GetNode(LIST *, int );
	int SetNode(LIST *, int, int );
	// 검색
	int SearchNode(LIST *, int );
	// 요소개수 얻기
	int GetCount(LIST *);
	// 요소 출력
	void PrintList(LIST *);

#endif __LIST_ADT_H
