// CList CLASS
// 프로그램명 : CList.cpp
// 작  성  자 : NINAEROS.AGAFE
// 작  성  일 : 05/01/25


#include "CList.h"

// Default 생성자
CList::CList()
{
	this->head = new NODE;	// head 생성
	this->tail = new NODE;	// tail 생성

	// head tail 연결
	this->head->Llink = this->head;
	this->head->Rlink = this->tail;
	this->tail->Llink = this->head;
	this->tail->Rlink = this->tail;

	this->count = 0;

	this->CurrentPosition = this->head;
}

// 복사 생성자
CList::CList(const CList& rCList)
{
	NODE* pNode = rCList.head->Rlink;

	this->head = new NODE;	// head 생성
	this->tail = new NODE;	// tail 생성

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
CList::~CList()
{
	this->DeleteAll(); // 요소 전부 삭제
	delete this->head; // 머리 삭제
	delete this->tail; // 꼬리 삭제
	this->count = 0;
}

// 삽입 ( 머리, 꼬리, 값앞, 값뒤, 정렬 )
void CList::InsertHead(const int data)
{
	// 삽입할 node 생성
	NODE* temp;	

	temp = new NODE;
	temp->data = data;
	
	// node 삽입 연결
	temp->Llink = this->head;
	temp->Rlink = this->head->Rlink;
	this->head->Rlink = temp;
	temp->Rlink->Llink = temp;

	this->CurrentPosition = temp;

	this->count++;
}
void CList::InsertTail(const int data)
{
	// 삽입할 node 생성
	NODE* temp;

	temp = new NODE;
	temp->data = data;

	// node 삽입 연결
	temp->Llink = this->tail->Llink;
	temp->Rlink = this->tail;
	this->tail->Llink->Rlink = temp;
	this->tail->Llink = temp;

	this->CurrentPosition = temp;

	this->count++;
}
bool CList::InsertBefore(const int key, const int data)
{
	bool retVal = false;

	NODE* source;
	NODE* dest;

	dest = this->head->Rlink;	// 처음 node

	// 머리부터 꼬리까지 반복
	while( !retVal && dest != this->tail )
	{
		// key 와 비교
		if( key == dest->data )
		{
			// 삽입할 node 생성
			source = new NODE;
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
bool CList::InsertAfter(const int key, const int data)
{
	bool retVal = false;

	NODE* source;
	NODE* dest;

	// node 처음
	dest = this->head->Rlink;

	// 머리부터 꼬리까지 반복
	while( !retVal && dest != this->tail )
	{
		// 비교 key == dest->data
		if( key == dest->data )
		{
			// 삽입할 node 생성
			source = new NODE;
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
void CList::InsertSort(const int data)
{
	NODE* source;
	NODE* dest;

	source = new NODE;

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
bool CList::DeleteHead()
{
	bool retVal;

	NODE* temp = this->head->Rlink;

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
		temp->Llink = '\0';
		temp->Rlink = '\0';
		
		delete temp;

		this->CurrentPosition = this->head->Rlink;

		this->count--;
		retVal = true;
	}
	return retVal;
}

bool CList::DeleteTail()
{
	bool retVal;

	NODE* temp;

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
		temp->Llink = '\0';
		temp->Rlink = '\0';

		delete temp;

		this->CurrentPosition = this->tail->Llink;
		this->count--;

		retVal = true;
	}
	return retVal;
}

bool CList::DeleteBefore(const int key)
{
	bool retVal = false;
	NODE* temp;
	NODE* pSource;

	temp = this->head->Rlink;
	
	//key값을 찾을때까지 머리에서 꼬리까지 이동
	while( (temp != this->tail) && (key != temp->data) )
	{
		temp = temp->Rlink;
	}
	// key값인지 아닌지 검사
	if( (temp->Llink != this->head) && (key == temp->data) )
	{
		// key 값 node 삭제
		pSource = temp->Llink;
		pSource->Rlink->Llink = pSource;
		pSource->Llink->Rlink = pSource->Rlink;
		this->CurrentPosition = pSource->Rlink;
		
		delete pSource;

		this->count--;
		retVal = true;
	}
	return retVal;
}

bool CList::DeleteAfter(const int key)
{
	bool retVal = false;

	NODE* temp;

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
		temp->Llink = '\0';
		temp->Rlink = '\0';

		delete temp;

		this->count--;
		retVal = true;
	}
	return retVal;
}

void CList::DeleteAll()
{
	// 머리와 꼬리 사이 요소 모두 삭제
	while( this->head->Rlink != this->tail )
	{
		NODE* temp;

		temp = this->head->Rlink;
		temp->Rlink->Llink = this->head;
		this->head->Rlink = temp->Rlink;

		delete temp;
	}
	this->CurrentPosition = this->head;
	this->count = 0;
}

bool CList::DeleteAt(const int index)
{
	bool retVal = false;

	NODE* dest;

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
void CList::MoveNext()
{
	// 현재위치 다음이 꼬리일 경우
	if( this->CurrentPosition->Rlink == this->tail )
	{
		this->CurrentPosition = this->head;
	}
	else
	{
		this->CurrentPosition = this->CurrentPosition->Rlink;
	}
}

void CList::MovePrivious()
{
	this->CurrentPosition = this->CurrentPosition->Llink;
}

void CList::MoveFirst()
{
	// 요소가 없을 경우
	if( this->head->Rlink == this->tail )
	{
		this->CurrentPosition = this->head;
	}
	else
	{
		this->CurrentPosition = this->head->Rlink;
	}
}

void CList::MoveLast()
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
int CList::GetNode(const int index)
{
	NODE* dest;

	dest = this->head;
	
	// index 만큼이동
	for( int i = 0; i < index; i++ )
	{
		dest = dest->Rlink;
	}
	return dest->data;
}

bool CList::SetNode(const int key, const int data)
{
	bool retVal = false;
	NODE* dest;

	dest = this->head->Rlink;

	// key갑을 찾을때까지 이동
	while( (dest != this->tail) && (key != dest->data) )
	{
		dest = dest->Rlink;
	}
	// key 값을 찾았는지 검사
	if( key == dest->data )
	{
		dest->data = data;
		retVal = true;
		this->CurrentPosition = dest;
	}
	return retVal;
}

// 검색
int CList::SearchNode(const int key)
{
	int index;
	int count = 0;
	NODE* dest;

	dest = this->head->Rlink;
	index = -1;

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
int CList::GetCount() const
{
	return this->count;
}

// 요소 출력
void CList::PrintList()
{
	NODE* temp;

	temp = this->head->Rlink;

	while( temp != this->tail )
	{
		cout << temp->data << " ";
		temp = temp->Rlink;
	}
	cout << endl;
}

// 연산자 재정의
// CList = CList
CList& CList::operator = (CList& rCList)
{
	NODE* pNode = rCList.head->Rlink;

	this->head = new NODE;	// head 생성
	this->tail = new NODE;	// tail 생성

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
bool CList::operator == (CList& rCList)
{
	bool retVal = false;

	if(this->count == rCList.count)
	{
		int true_count = 1;

		NODE* pSource = this->head->Rlink;
		NODE* pDest = rCList.head->Rlink;
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
CList& operator + (CList& rLeft, CList& rRight)
{
	CList* temp;
	temp = new CList;

	NODE* pLeftList = rLeft.head->Rlink;
	NODE* pRightList = rRight.head->Rlink;

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
CList& CList::operator += (CList& rCList)
{
	NODE* pRight = rCList.head->Rlink;
	while( pRight != rCList.tail )
	{
		this->InsertTail(pRight->data);
		pRight = pRight->Rlink;
	}
	return *this;
}

// cin <<
ostream& operator << (ostream& Output, CList& rCList)
{
	NODE* pSource = rCList.head->Rlink;
	while( pSource != rCList.tail )
	{
		Output << pSource->data << " ";
		pSource = pSource->Rlink;
	}
	return Output;
}
