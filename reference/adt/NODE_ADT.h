// LIST_ADT
// 프로그램 명 : NODE_ADT.h
// 작 성 자 : NINAEROS.AGAFE
// 최초작성일 : 05/01/11

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
