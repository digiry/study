// LIST_ADT
// 프로그램 명 : LIST_ADT.c
// 작 성 자 : NINAEROS.AGAFE
// 최초작성일 : 05/01/11
// 수 정 일 : 05/01/12

#include <stdio.h>
#include <stdlib.h>
#include "NODE_ADT.h"
#include "LIST_ADT.h"

#if 0
//생성
void CreateList(LIST *self)
{
	self->head = (NODE *)malloc(sizeof(NODE));	// head 생성
	self->tail = (NODE *)malloc(sizeof(NODE));	// tail 생성
	// head link 초기화
	self->head->Llink = self->head;				
	self->head->Rlink = self->tail;
	// tail link 초기화
	self->tail->Llink = self->head;
	self->tail->Rlink = self->tail;
	// self 요소 개수 초기화
	self->count = 0;
	// self 현재위치 초기화
	self->Currentposition = self->head;

	// 함수 연결
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

//소멸
void DestroyList(LIST *self)
{
	// 요소 전부 삭제
	self->DeleteAll(self);
	// 머리 삭제
	free(self->head);
	// 꼬리 삭제
	free(self->tail);
}

// 삽입 (머리, 꼬리 ,값앞, 값뒤, 정렬)
void InsertHead(LIST *self, int data)
{
	// 삽입할 node 생성
	NODE *source;
	source = (NODE *)malloc(sizeof(NODE));
	source->data = data;
	// node 삽입
	source->Llink = self->head;
	source->Rlink = self->head->Rlink;
	self->head->Rlink = source;
	source->Rlink->Llink = source;
	
	self->Currentposition = source;

	self->count++;
}

void InsertTail(LIST *self, int data)
{
	// 삽입할 node 생성
	NODE *source;
	source = (NODE *)malloc(sizeof(NODE));
	source->data = data;
	// node 삽입
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

	dest = self->head->Rlink;	// 처음 node

	// 머리부터 꼬리까지 반복
	while( (!true_count) && (dest != self->tail) )
	{
		//key 과 비교
		if( key == dest->data )
		{
			// 삽입할 node 생성
			source = (NODE *)malloc(sizeof(NODE));
			source->data = data;
			// 삽입
			source->Llink = dest->Llink;
			source->Rlink = dest;
			dest->Llink->Rlink = source;
			
			self->Currentposition = source;
			self->count++;
			//반복 중지
			true_count = 1;
		}
		else
		{
			//node 이동
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

	// node 처음
	dest = self->head->Rlink;

	// 머리 부터 꼬리 까지 반복
	while( (!true_count) && (dest != self->tail) )
	{
		// 비교
		if( key == dest->data )
		{
			// 삽입할 node 생성
			source = (NODE *)malloc(sizeof(NODE));
			source->data = data;
			// node 삽입
			source->Llink = dest;
			source->Rlink = dest->Rlink;
			dest->Rlink->Llink = source;
			dest->Rlink = source;
			
			self->Currentposition = source;
			self->count++;
			// 반복 중지
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

	// 꼬리가 아니고 data보다 큰동안 반복(오름차순)
	while( (dest != self->tail) && (data >= dest->data) )
	{
		// 다음 node로 이동
		dest = dest->Llink;
	}
	// 삽입
	source->Llink = dest->Llink;
	source->Rlink = dest;
	dest->Llink->Rlink = source;
	dest->Llink = source;

	self->Currentposition = source;
	self->count++;
}

// 삭제 (머리, 꼬리, 값앞, 값뒤, 전부)
int DeleteHead(LIST *self)
{
	int true_count;

	NODE *temp;		//임시 node

	// 머리 다음 요소 삭제
	if( self->head->Rlink == self->tail )
	{
		true_count = 0;
	}
	else
	{
		//삭제할 node 를 temp로 삭제
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

	// 꼬리 전 요소 삭제
	if( self->tail->Llink == self->head )
	{
		true_count = 0;
	}
	else
	{
		//삭제할 node 를 temp로 삭제
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
	// key값을 찾을때까지 머리에서 꼬리까지 이동
	while( (temp->Rlink != self->tail) && (key != temp->data) )
	{
		temp = temp->Rlink;
	}
	// key값인지 아닌지 검사
	if( (key == temp->data) && (temp->Llink != self->head) )
	{
		// key 값 node 삭제
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

	// key값을 찾을때까지 이동
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

	// 머리와 꼬리 사이 요소 모두 삭제
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

// 위치이동 (후, 전, 처음, 마지막)
void MoveNext(LIST *self)
{
	// 현재위치 다음이 꼬리일경우
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
	// 요소가 없을 경우
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
	// 요소가 없을 경우
	if( self->head->Rlink == self->tail )
	{
		self->Currentposition = self->head;
	}
	else
	{
		self->Currentposition = self->tail->Llink;
	}
}

// 읽기 쓰기
int GetNode(LIST *self, int index)
{
	NODE *dest;

	int i;

	dest = self->head;
	// index 만큼 이동
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

	// key 값 을 찾을때까지 이동
	while( (dest != self->tail) && (key != dest->data) )
	{
		dest = dest->Rlink;
	}
	// key값을 찾았는지 검사
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

// 검색
int SearchNode(LIST *self, int key)
{
	int index;
	int count = 0;
	NODE *dest;

	dest = self->head->Rlink;
	index = -1;

	// key값 위치 찾기
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

// 요소개수 얻기
int GetCount(LIST *self)
{
	return self->count;
}

// 요소 출력
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
