/*
 * linkedlist.h
 *
 *  Created on: 2014. 11. 16.
 *      Author: suandkyu
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "personInfo.h"

class node {
public:
	personInfo *info;
	node *next;
};

class linkedlist {
private:
	node *head;
	node *tail;
	node *next;
	node *pos;
	int length;
public:
	linkedlist();
	~linkedlist();
	void append(personInfo &info);
	node* moveToBeforeNode(int index);
	void insert(int index, personInfo &info);
	void deleteNode(int index);
	void deleteAll();
	personInfo viewAt(int index);
	node* moveFirst();
	node* moveLast();
	node* moveNext();
	bool isTail();
	int get_length();
	node* getNode(int index);
	int findName(string name);
};

#endif /* LINKEDLIST_H_ */
