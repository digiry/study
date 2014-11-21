/*
 * testmain.cpp
 *
 *  Created on: 2014. 11. 21.
 *      Author: suandkyu
 */

#include "linkedlist.h"
#include <iostream>
#include <iomanip>

using namespace std;

void printHeaderLinkedList(int printNum) {
	cout << "----------------------------------------------" << endl;
	if ( printNum != -1 ) {
		cout << "번호  이름     전화번호      주소" << endl;
	} else {
		cout << "이름     전화번호      주소" << endl;
	}
	cout << "----------------------------------------------" << endl;
}
void printPersonInfoLinkedList(personInfo *info, int printNum) {
	if ( printNum != -1 ) {
		cout << setw(4) << printNum
			 << setw(7) << info->name
			 << setw(12) << info->phone
			 << setw(50) << info->address << endl;
	} else {
		cout << setw(7) << info->name
			 << setw(12) << info->phone
			 << setw(50) << info->address << endl;
	}
}

void printLinedList(linkedlist *list) {
	int number = 1;
	node *target;

	printHeaderLinkedList(1);

	target = list->moveFirst();
	while ( list->isTail() != false ) {
		printPersonInfoLinkedList(target->info, number);
		target = list->moveNext();
		number++;
	}
}

int main() {
	linkedlist *list;

	personInfo info1 = {"aaa", "0001110000", "xxx"};
	personInfo info2 = {"aaa", "0001110000", "xxx"};
	personInfo info3 = {"aaa", "0001110000", "xxx"};

	list = new linkedlist;

	list->append(info1);
	list->append(info2);
	list->append(info3);

	printLinedList(list);

	delete list;
}
