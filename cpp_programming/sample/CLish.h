// CList CLASS
// 프로그램명 : CList.h
// 작  성  자 : NINAEROS.AGAFE
// 작  성  일 : 05/01/25
// 수  정  일 : 05/01/28

#ifndef __CLIST_H
#define __CLIST_H

#include <iostream>
#include <cassert>
#include "CNode.h"

using namespace std;

template <class Type>
class CList
{
// 외부연산
public:
	// Default 생성자
	CList();

	// 복사 생성자
	CList( const CList& );

	// 소멸자
	~CList();

	// 삽입 ( 머리, 꼬리, 값앞, 값뒤, 정렬 )
	void InsertHead(const Type);
	void InsertTail(const Type);
	bool InsertBefore(const Type, const Type);
	bool InsertAfter(const Type, const Type);
	void InsertSort(const Type);

	// 삭제 ( 머리, 꼬리, 값앞, 값뒤, 전부, 특정위치 )
	bool DeleteHead();
	bool DeleteTail();
	bool DeleteBefore(const Type);
	bool DeleteAfter(const Type);
	void DeleteAll();
	bool DeleteAt(const int);

	// 위치이동 ( 전, 후, 처음, 마지막 )
	void MoveNext();
	void MovePrivious();
	void MoveFirst();
	void MoveLast();

	// 읽기 쓰기
	Type& GetNode(const int);
	
	// 검색
	int SearchNode(const Type);

	// 요소 개수 얻기
	int GetCount() const;

// 연산자 재정의
	// CList = CList
	CList& operator = (CList&);

	// CList == CList
	bool operator == (CList&);

	// CList + CList
	friend CList& operator + (CList&, CList&);

	//  CList += CList
	CList& operator += (CList&);

	// cout <<
	friend ostream& operator << (ostream&, CList&);

	// [] Lvalue , Rvalue
	Type& operator [] (const int);
	const Type& operator [] (const int) const;

// 저장구조
private:

	NODE<Type>* head;
	NODE<Type>* tail;
	int count;
	NODE<Type>* CurrentPosition;
};

// ==================================================
// 정 의 부

// Default 생성자
template <class Type>
CList<Type>::CList()
{
	this->head = new NODE<Type>;	// head 생성
	this->tail = new NODE<Type>;	// tail 생성

	// head tail 연결
	this->head->Llink = this->head;
	this->head->Rlink = this->tail;
	this->tail->Llink = this->head;
	this->tail->Rlink = this->tail;

	this->count = 0;

	this->CurrentPosition = this->head;
}

// 복사 생성자
template <class Type>
CList<Type>::CList(const CList<Type>& rCList)
{
	NODE<Type>* pNode = rCList.head->Rlink;

	this->head = new NODE<Type>;	// head 생성
	this->tail = new NODE<Type>;	// tail 생성

	// head tail 연결
	this->head->Llink = this->head;
	this->head->Rlink = this->tail;
	this->tail->Llink = this->head;
	this->tail->Rlink = this->tail;

	this->count = 0;

	this->CurrentPosition = this->head;
	
	while( pNode != rCList.tail )
	{
		this->InsertTail(pNode->data);
		pNode = pNode->Rlink;
	}
}

// 소멸자
template <class Type>
CList<Type>::~CList()
{
	this->DeleteAll(); // 요소 전부 삭제
	delete this->head; // 머리 삭제
	delete this->tail; // 꼬리 삭제
	this->count = 0;
}

// 삽입 ( 머리, 꼬리, 값앞, 값뒤, 정렬 )
template <class Type>
void CList<Type>::InsertHead(const Type data)
{
	// 삽입할 node 생성
	NODE<Type>* temp;	

	temp = new NODE<Type>;
	temp->data = data;
	
	// node 삽입 연결
	temp->Llink = this->head;
	temp->Rlink = this->head->Rlink;
	this->head->Rlink = temp;
	temp->Rlink->Llink = temp;

	this->CurrentPosition = temp;

	this->count++;
}

template <class Type>
void CList<Type>::InsertTail(const Type data)
{
	// 삽입할 node 생성
	NODE<Type>* temp;

	temp = new NODE<Type>;
	temp->data = data;

	// node 삽입 연결
	temp->Llink = this->tail->Llink;
	temp->Rlink = this->tail;
	this->tail->Llink->Rlink = temp;
	this->tail->Llink = temp;

	this->CurrentPosition = temp;

	this->count++;
}

template <class Type>
bool CList<Type>::InsertBefore(const Type key, const Type data)
{
	bool retVal = false;

	NODE<Type>* source;
	NODE<Type>* dest;

	dest = this->head->Rlink;	// 처음 node

	// 머리부터 꼬리까지 반복
	while( !retVal && dest != this->tail )
	{
		// key 와 비교
		if( key == dest->data )
		{
			// 삽입할 node 생성
			source = new NODE<Type>;
			source->data = data;

			// 삽입연결
			source->Llink = dest->Llink;
			source->Rlink = dest;
			dest->Llink->Rlink = source;
			dest->Llink = source;

			this->CurrentPosition = source;
			this->count++;

			retVal = true;
		}
		else
		{
			dest = dest->Rlink;
		}
	}
	return retVal;
}

template <class Type>
bool CList<Type>::InsertAfter(const Type key, const Type data)
{
	bool retVal = false;

	NODE<Type>* source;
	NODE<Type>* dest;

	// node 처음
	dest = this->head->Rlink;

	// 머리부터 꼬리까지 반복
	while( !retVal && dest != this->tail )
	{
		// 비교 key == dest->data
		if( key == dest->data )
		{
			// 삽입할 node 생성
			source = new NODE<Type>;
			source->data = data;

			// node 삽입 연결
			source->Llink = dest;
			source->Rlink = dest->Rlink;
			dest->Rlink->Llink = source;
			dest->Rlink = source;

			this->CurrentPosition =source;
			this->count++;

			retVal = true;
		}
		else
		{
			dest = dest->Rlink;
		}
	}
	return retVal;
}

template <class Type>
void CList<Type>::InsertSort(const Type data)
{
	NODE<Type>* source;
	NODE<Type>* dest;

	source = new NODE<Type>;

	source->data = data;

	dest = this->head->Rlink;

	while( (dest != this->tail) && (data >= dest->data) )
	{
		dest = dest->Rlink;
	}
	// 삽입
	source->Llink = dest->Llink;
	source->Rlink = dest;
	dest->Llink->Rlink = source;
	dest->Llink = source;

	this->CurrentPosition = source;
	this->count++;
}

// 삭제 ( 머리, 꼬리, 값앞, 값뒤, 전부, 특정위치 )
template <class Type>
bool CList<Type>::DeleteHead()
{
	bool retVal;

	NODE<Type>* temp = this->head->Rlink;

	// 머리 다음요소 삭제
	if( temp == this->tail )
	{
		retVal = false;
	}
	else
	{
		// 삭제할 node를 temp로 삭제
		this->head->Rlink = temp->Rlink;
		temp->Rlink->Llink = this->head;
		
		delete temp;

		this->CurrentPosition = this->head->Rlink;

		this->count--;
		retVal = true;
	}
	return retVal;
}

template <class Type>
bool CList<Type>::DeleteTail()
{
	bool retVal;

	NODE<Type>* temp;

	// 꼬리전 요소 삭제
	if( this->tail->Llink == this->head )
	{
		retVal = false;
	}
	else
	{
		// 삭제할 node를 temp로 삭제
		temp = this->tail->Llink;
		this->tail->Llink = temp->Llink;
		temp->Llink->Rlink = this->tail;

		delete temp;

		this->CurrentPosition = this->tail->Llink;
		this->count--;

		retVal = true;
	}
	return retVal;
}

template <class Type>
bool CList<Type>::DeleteBefore(const Type key)
{
	bool retVal = false;
	NODE<Type>* temp;

	temp = this->head->Rlink;

	// key 값을 찾을때까지 머리에서 꼬리까지 이동
	while( (temp != this->tal) && (key != temp->data) )
	{
		// key 값 node 삭제
		temp = temp->Llink;
		temp->Rlink->Llink = temp->Llink;
		temp->Llink->Rlink = temp->Rlink;
		this->CurrentPosition = temp->Rlink;

		delete temp;

		this->count--;
		retVal =true;
	}
	return retVal;
}

template <class Type>
bool CList<Type>::DeleteAfter(const Type key)
{
	bool retVal = false;

	NODE<Type>* temp;

	temp = this->head->Rlink;

	// key값을 찾을때까지 이동
	while( (temp != this->tail) && (key != temp->data) )
	{
		temp = temp->Rlink;
	}
	if( (key == temp->data) && (temp->Rlink != this->tail) )
	{
		temp = temp->Rlink;
		temp->Rlink->Llink = temp->Llink;
		temp->Llink->Rlink = temp->Rlink;

		this->CurrentPosition = temp->Llink;

		delete temp;

		this->count--;
		retVal = true;
	}
	return retVal;
}

template <class Type>
void CList<Type>::DeleteAll()
{
	// 머리와 꼬리 사이 요소 모두 삭제
	while( this->head->Rlink != this->tail )
	{
		NODE<Type>* temp;

		temp = this->head->Rlink;
		temp->Rlink->Llink = this->head;
		this->head->Rlink = temp->Rlink;

		delete temp;
	}
	this->CurrentPosition = this->head;
	this->count = 0;
}

template <class Type>
bool CList<Type>::DeleteAt(const int index)
{
	bool retVal = false;

	NODE<Type>* dest;

	dest = this->head;	// index만큼이동
	for( int i = 0; i < index; i++ )
	{
		dest = dest->Rlink;
	}
	if( dest != this->tail )
	{
		// 삭제 연결
		dest->Rlink->Llink = dest->Llink;
		dest->Llink->Rlink = dest->Rlink;
		delete dest;
		this->count--;
		retVal = true;
	}
	return retVal;
}

// 위치이동 ( 전, 후, 처음, 마지막 )
template <class Type>
void CList<Type>::MoveNext()
{
	// 현재위치 다음이 꼬리일 경우
	if( this->CurrentPosition->Rlink != this->tail )
	{
		this->CurrentPosition = this->CurrentPosition->Rlink;
	}
}

template <class Type>
void CList<Type>::MovePrivious()
{
	if( this->CurrentPosition->Llink != this->head )
	{
		this->CurrentPostion = this->CurrentPosition->Llink;
	}
	if( this->CurrentPosition == this->tail )
	{
		this->CurrentPosition = this->head;
	}
}

template <class Type>
void CList<Type>::MoveFirst()
{
	// 요소가 없을 경우
	if( (this->head->Rlink == this->tail) || (this->CurrentPosition == this->tail) )
	{
		this->CurrentPosition = this->head;
	}
	else
	{
		this->CurrentPosition = this->head->Rlink;
	}
}

template <class Type>
void CList<Type>::MoveLast()
{
	// 요소가 없을 경우
	if( this->head->Rlink == this->tail )
	{
		this->CurrentPosition = this->head;
	}
	else
	{
		this->CurrentPosition = this->tail->Llink;
	}
}

// 읽기 쓰기
template <class Type>
Type& CList<Type>::GetNode(const int index)
{
	NODE<Type>* dest;

	dest = this->head;
	
	// index 만큼이동
	for( int i = 0; i < index; i++ )
	{
		dest = dest->Rlink;
	}
	return dest->data;
}

// 검색
template <class Type>
int CList<Type>::SearchNode(const Type key)
{
	int index = -1;
	int count = 1;
	NODE<Type>* dest;

	dest = this->head->Rlink;
	
	// key값 위치 찾기 
	while( (dest != this->tail) && (key != dest->data) )
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

// 요소 개수 얻기
template <class Type>
int CList<Type>::GetCount() const
{
	return this->count;
}

// 연산자 재정의
// CList = CList
template <class Type>
CList<Type>& CList<Type>::operator = (CList<Type>& rCList)
{
	NODE<Type>* pNode = rCList.head->Rlink;

	this->head = new NODE<Type>;	// head 생성
	this->tail = new NODE<Type>;	// tail 생성

	// head tail 연결
	this->head->Llink = this->head;
	this->head->Rlink = this->tail;
	this->tail->Llink = this->head;
	this->tail->Rlink = this->tail;

	this->count = 0;

	this->CurrentPosition = this->head;
	
	while( pNode != rCList.tail )
	{
		this->InsertTail(pNode->data);
		pNode = pNode->Rlink;
	}
	return *this;
}

// CList == CList
template <class Type>
bool CList<Type>::operator == (CList<Type>& rCList)
{
	bool retVal = false;

	if(this->count == rCList.count)
	{
		int true_count = 1;

		NODE<Type>* pSource = this->head->Rlink;
		NODE<Type>* pDest = rCList.head->Rlink;
		while( true_count != 0 && pSource != this->tail )
		{
			if( pSource->data == pDest->data )
			{
				true_count *= true_count;
			}
			else
			{
				true_count = 0;
			}
		}
		if( true_count )
		{
			retVal = true;
		}
	}
	return retVal;
}

// CList + CList
template <class Type>
CList<Type>& operator + (CList<Type>& rLeft, CList<Type>& rRight)
{
	CList<Type>* temp;
	temp = new CList<Type>;

	NODE<Type>* pLeftList = rLeft.head->Rlink;
	NODE<Type>* pRightList = rRight.head->Rlink;

	while( pLeftList != rLeft.tail )
	{
		temp->InsertTail(pLeftList->data);
		pLeftList = pLeftList->Rlink;
	}
	while( pRightList != rRight.tail )
	{
		temp->InsertTail(pRightList->data);
		pRightList = pRightList->Rlink;
	}
	return *temp;
}

//  CList += CList
template <class Type>
CList<Type>& CList<Type>::operator += (CList<Type>& rCList)
{
	NODE<Type>* pRight = rCList.head->Rlink;
	while( pRight != rCList.tail )
	{
		this->InsertTail(pRight->data);
		pRight = pRight->Rlink;
	}
	return *this;
}

// cout <<
template <class Type>
ostream& operator << (ostream& Output, CList<Type>& rCList)
{
	NODE<Type>* pSource = rCList.head->Rlink;
	while( pSource != rCList.tail )
	{
		Output << pSource->data << " ";
		pSource = pSource->Rlink;
	}
	return Output;
}

// [] Lvalue , Rvalue
template <class Type>
Type& CList<Type>::operator [] (const int index)
{
	assert( index > 0 && index <= this->count );

	return this->GetNode(index);
}

template <class Type>
const Type& CList<Type>::operator [] (const int index) const
{
	assert( index > 0 && index <= this->count );

	return this->GetNode(index);	
}

#endif __CLIST_H


