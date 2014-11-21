// CList CLASS
// 프로그램명 : CList_test.cpp
// 작  성  자 : NINAEROS.AGAFE
// 작  성  일 : 05/01/25

#include "CList.h"

int main()
{
	CList<int> test1;

	test1.InsertTail(10);
	test1.InsertTail(11);
	test1.InsertTail(12);
	test1.InsertTail(13);
	test1.InsertTail(14);

	cout << test1 << endl;

	return 1;
}
