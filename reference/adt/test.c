// LIST_ADT
// ���α׷� �� : test.c
// �� �� �� : �ں���(����) NINAEROS.AGAFE(����)
// �����ۼ��� : 05/01/11
// �� �� �� : 05/01/12

#include <stdio.h>
#include "LIST_ADT.h"

int main()
{
	LIST dll;

	CreateList(&dll);

	dll.InsertHead(&dll, 5);
	dll.InsertHead(&dll, 10);
	dll.InsertHead(&dll, 15);
	dll.InsertHead(&dll, 20);
	dll.PrintList(&dll);
	// 20 15 10 5

	dll.DeleteAll(&dll);
	
	printf("\n");

	dll.InsertTail(&dll, 7);
	dll.InsertTail(&dll, 17);
	dll.InsertTail(&dll, 27);
	dll.InsertTail(&dll, 37);
	dll.InsertTail(&dll, 47);
	dll.InsertTail(&dll, 57);
	dll.PrintList(&dll);
	// 7 17 27 37 47 57
	printf("\n");

	dll.InsertBefore(&dll, 17, 8);
	dll.PrintList(&dll);
	// 7 8 17 27 37 47 57
	printf("\n");

	dll.InsertAfter(&dll, 47, 11);	
	dll.PrintList(&dll);
	// 7 8 17 27 37 47 11 57
	printf("\n");

	dll.DeleteHead(&dll);
	dll.PrintList(&dll);
	// 8 17 27 37 47 11 57
	printf("\n");

	dll.DeleteTail(&dll);
	dll.PrintList(&dll);
	// 8 17 27 37 47 11
	printf("\n");

	dll.DeleteBefore(&dll, 47);
	dll.PrintList(&dll);
	// 8 17 27 47 11
	printf("\n");

	dll.DeleteAfter(&dll, 27);
	dll.PrintList(&dll);
	// 8 17 27 11
	printf("\n");

	dll.SetNode(&dll, 27, 15);
	dll.PrintList(&dll);
	printf("\n");
	// 8 17 15 11
	return 0;
}