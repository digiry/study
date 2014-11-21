#include "linkedlist.h"
#include <stddef.h>

using namespace std;

linkedlist::linkedlist() {
	this->head = new node;
	this->tail = new node;

	this->head->next = this->tail;
	this->tail->next = NULL;
	this->pos = this->head->next;
	this->length = 0;
}

linkedlist::~linkedlist() {
	this->deleteAll();

	delete this->head;
	delete this->tail;
	this->length = 0;
}

void linkedlist::append(personInfo &info) {
	node *last = this->moveLast();
	node *newNode = new node;

	newNode->info = new personInfo;
	newNode->info->name = info.name;
	newNode->info->phone = info.phone;
	newNode->info->address = info.address;

	newNode->next = last->next;
	last->next = newNode;

	this->pos = newNode;
	this->length++;
}

node* linkedlist::moveToBeforeNode(int index) {
	node *target;
	int i = 0;

	if ( index <= 0 ) {
		target = this->head;
	} else {
		target = this->moveFirst();
		while ( i < index - 1 ) {
			target = this->moveNext();
			i++;
		}
	}

	return target;
}

void linkedlist::insert(int index, personInfo &info) {
	node *target;
	node *newNode = new node;

	target = this->moveToBeforeNode(index);

	newNode->info = new personInfo;
	newNode->info->name = info.name;
	newNode->info->phone = info.phone;
	newNode->info->address = info.address;

	newNode->next = target->next;
	target->next = newNode;
	this->length++;

	this->pos = newNode;
}

void linkedlist::deleteNode(int index) {
	node *before;
	node *target;

	before = this->moveToBeforeNode(index);

	target = before->next;
	before->next = target->next;

	delete target->info;
	target->next = NULL;
	delete target;

	this->pos = before;
	this->length--;
}

void linkedlist::deleteAll() {
	if ( this->length == 0 ) {
		return ;
	}

	while ( this->length > 0 ) {
		this->deleteNode(0);
	}

	this->pos = this->head->next;
}

personInfo linkedlist::viewAt(int index) {
	personInfo info;
	node *target;

	target = moveToBeforeNode(index)->next;

	info.name = target->info->name;
	info.phone = target->info->phone;
	info.address = target->info->address;

	this->pos = target;
	target = NULL;
	return info;
}
node* linkedlist::moveFirst() {
	this->pos = this->head->next;

	return this->pos;
}

node* linkedlist::moveLast() {
	node *target;

	if ( this->length <= 0 ) {
		target = this->head;
	} else {
		target = this->moveToBeforeNode(this->length - 1)->next;
	}

	this->pos = target;

	return target;
}

node* linkedlist::moveNext() {
	this->pos = this->pos->next;

	return this->pos;
}

bool linkedlist::isTail() {
	bool isTail = false;

	if ( this->pos->next == NULL ) {
		isTail = true;
	}

	return isTail;
}

bool linkedlist::get_length() {
	return this->length;
}

node* linkedlist::getNode(int index) {
	node *target;

	target = this->moveToBeforeNode(index)->next;

	return target;
}

int linkedlist::findName(string name) {
	int index = 0;
	bool isFound = false;

	this->moveFirst();
	while ( this->isTail() != true ) {
		if ( this->pos->info->name == name ) {
			isFound = true;
			break;
		}
		this->moveNext();
		index++;
	}

	if ( isFound == false ) {
		index = -1;
	}

	return index;
}
