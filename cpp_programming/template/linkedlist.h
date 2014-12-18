/*
 * linkedlist.h
 *
 *  Created on: 2014. 11. 16.
 *      Author: suandkyu
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template <class TYPE>
class node {
public:
	TYPE *data;
	node *next;
};

template <class TYPE>
class linkedlist {
private:
	node<TYPE> *head;
	node<TYPE> *tail;
	node<TYPE> *next;
	node<TYPE> *pos;
	int length;
public:
	linkedlist();
	~linkedlist();
	void append(TYPE &data);
	node<TYPE>* moveToBeforeNode(int index);
	void insert(int index, TYPE &data);
	void deleteNode(int index);
	void deleteAll();
	TYPE& viewAt(int index);
	node<TYPE>* moveFirst();
	node<TYPE>* moveLast();
	node<TYPE>* moveNext();
	bool isTail();
	int get_length();
	node<TYPE>* getNode(int index);
	int find(TYPE &data);
};

template <class TYPE>
linkedlist<TYPE>::linkedlist(void) {
	this->head = new node<TYPE>;
	this->tail = new node<TYPE>;

	this->head->next = this->tail;
	this->tail->next = NULL;
	this->pos = this->head->next;
	this->length = 0;
}

template <class TYPE>
linkedlist<TYPE>::~linkedlist(void) {
	this->deleteAll();

	delete this->head;
	delete this->tail;
	this->length = 0;
}

template <class TYPE>
void linkedlist<TYPE>::append(TYPE &data) {
	node<TYPE> *last = this->moveLast();
	node<TYPE> *newNode = new node<TYPE>;

	newNode->data = new TYPE(data);

	newNode->next = last->next;
	last->next = newNode;

	this->pos = newNode;
	this->length++;
}

template <class TYPE>
node<TYPE>* linkedlist<TYPE>::moveToBeforeNode(int index) {
	node<TYPE> *target;
	int i = 0;

	if (index <= 0) {
		target = this->head;
	}
	else {
		target = this->moveFirst();
		while (i < index - 1) {
			target = this->moveNext();
			i++;
		}
	}

	return target;
}

template <class TYPE>
void linkedlist<TYPE>::insert(int index, TYPE &data) {
	node<TYPE> *target;
	node<TYPE> *newNode = new node;

	target = this->moveToBeforeNode(index);

	newNode->data = new TYPE(data);

	newNode->next = target->next;
	target->next = newNode;
	this->length++;

	this->pos = newNode;
}

template <class TYPE>
void linkedlist<TYPE>::deleteNode(int index) {
	node<TYPE> *before;
	node<TYPE> *target;

	before = this->moveToBeforeNode(index);

	target = before->next;
	before->next = target->next;

	delete target->data;
	target->next = NULL;
	delete target;

	this->pos = before;
	this->length--;
}

template <class TYPE>
void linkedlist<TYPE>::deleteAll() {
	if (this->length == 0) {
		return;
	}

	while (this->length > 0) {
		this->deleteNode(0);
	}

	this->pos = this->head->next;
}

template <class TYPE>
TYPE& linkedlist<TYPE>::viewAt(int index) {
	node<TYPE> *target;

	target = moveToBeforeNode(index)->next;

	this->pos = target;
	return *(target->data);
}

template <class TYPE>
node<TYPE>* linkedlist<TYPE>::moveFirst() {
	this->pos = this->head->next;

	return this->pos;
}

template <class TYPE>
node<TYPE>* linkedlist<TYPE>::moveLast() {
	node<TYPE> *target;

	if (this->length <= 0) {
		target = this->head;
	}
	else {
		target = this->moveToBeforeNode(this->length - 1)->next;
	}

	this->pos = target;

	return target;
}

template <class TYPE>
node<TYPE>* linkedlist<TYPE>::moveNext() {
	this->pos = this->pos->next;

	return this->pos;
}

template <class TYPE>
bool linkedlist<TYPE>::isTail() {
	bool isTail = false;

	if (this->pos->next == NULL) {
		isTail = true;
	}

	return isTail;
}

template <class TYPE>
int linkedlist<TYPE>::get_length() {
	return this->length;
}

template <class TYPE>
node<TYPE>* linkedlist<TYPE>::getNode(int index) {
	node<TYPE> *target;

	target = this->moveToBeforeNode(index)->next;

	return target;
}

template <class TYPE>
int linkedlist<TYPE>::find(TYPE &data) {
	int index = 0;
	bool isFound = false;

	this->moveFirst();
	while (this->isTail() != true) {
		if (*(this->pos->data) == data) {
			isFound = true;
			break;
		}
		this->moveNext();
		index++;
	}

	if (isFound == false) {
		index = -1;
	}

	return index;
}

#endif /* LINKEDLIST_H_ */
