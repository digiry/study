// LIST_ADT
// ���α׷� �� : NODE_ADT.h
// �� �� �� : NINAEROS.AGAFE
// �����ۼ��� : 05/01/11

typedef struct __NODE NODE;
#ifndef __NODE_ADT_H
#define __NODE_ADT_H

typedef struct __NODE
{
	int data;
	NODE *Llink;
	NODE *Rlink;
} NODE;

#endif __NODE_ADT_H
