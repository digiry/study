#include "addressbook.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

addressbook::addressbook() {
	this->list = new linkedlist<personInfo>;
}

addressbook::~addressbook() {
	this->list->deleteAll();

	delete list;
}

void addressbook::printMainMenu() {
	cout << "1. 주소정보를 입력한다." << endl;
	cout << "2. 주소정보를 삭제한다." << endl;
	cout << "3. 주소정보를 수정한다." << endl;
	cout << "4. 주소정보를 검색한다." << endl;
	cout << "5. 전체 주소록을 출력한다." << endl;
	cout << "6. 주소록 파일에 저장한다." << endl;
	cout << "7. 주소록 파일을 불러온다." << endl;
	cout << "0. 종료한다." << endl;
}
void addressbook::print_finish() {
	cout << "프로그램을 종료합니다." << endl;
}
void addressbook::print_error(int error) {
	switch (error) {
	case ERROR_NO_MENU:
		cout << "없는 번호를 입력하였습니다." << endl;
		break;
	case ERROR_FULL:
		cout << "주소록이 가득 찼습니다." << endl;
		break;
	case ERROR_EMPTY:
		cout << "주소록이 비어있습니다." << endl;
		break;
	case ERROR_NOT_SEARCH:
		cout << "주소정보를 찾을 수 없습니다." << endl;
		break;
	case ERROR_LOAD_FAIL:
		cout << "addressbook.dat 파일을 불러올수 없습니다." << endl;
		break;
	default:
		break;
	}
}
bool addressbook::isEmpty() {
	bool isEmpty = true;

	if (this->list->get_length() > 0) {
		isEmpty = false;
	}

	return isEmpty;
}
void addressbook::input() {
	personInfo info;
	char yesno;
	string name;
	string phone;
	string address;

	cout << "이름 : ";
	cin >> name;
	info.name(name);

	cout << "전화번호 : ";
	cin >> phone;
	info.phone(phone);

	cout << "주소 : ";
	cin >> address;
	info.address(address);

	cout << "입력된 정보" << endl;
	this->printHeader(-1);
	this->printPersonInfo(info, -1);

	cin.sync();
	cout << "추가하시겠습니까 ? (y/n) :";
	cin.get(yesno);

	if (yesno == 'y') {
		this->list->append(info);
		cout << "추가되었습니다." << endl;
	}
}

void addressbook::remove() {
	personInfo info;
	string name;
	int removeIndex = -1;
	char yesno;

	if ( this->isEmpty() == true ) {
		this->print_error(ERROR_EMPTY);
		return ;
	}

	cout << "삭제할 이름: ";
	cin >> name;

	info.name(name);

	removeIndex = this->list->find(info);

	if ( removeIndex == -1 ) {
		this->print_error(ERROR_NOT_SEARCH);
		return ;
	}

	this->printHeader(-1);
	this->printPersonInfo(this->list->viewAt(removeIndex), -1);

	cin.sync();
	cout << "삭제하겠습니까? (y/n) :";
	cin.get(yesno);

	if ( yesno == 'y' ) {
		this->list->deleteNode(removeIndex);
		cout << "삭제되었습니다." << endl;
	}
}

void addressbook::modify() {
	string name;
	string phone;
	string address;
	personInfo info;
	int modifyIndex = -1;
	char yesno;
	node<personInfo> *target;

	if ( this->isEmpty() == true ) {
		this->print_error(ERROR_EMPTY);
		return ;
	}

	cout << "수정할 이름: ";
	cin >> name;

	info.name(name);
	modifyIndex = this->list->find(info);

	if ( modifyIndex == -1 ) {
		this->print_error(ERROR_NOT_SEARCH);
		return ;
	}

	this->printHeader(-1);
	this->printPersonInfo(this->list->viewAt(modifyIndex), -1);

	cin.sync();
	cout << "수정하겠습니까? (y/n) :";
	cin.get(yesno);

	if ( yesno == 'y' ) {
		cout << "이름 : ";
		cin >> name;
		cout << "전화번호 : ";
		cin >> phone;
		cout << "주소 : ";
		cin >> address;

		cout << "수정된 정보" << endl;

		target = this->list->getNode(modifyIndex);

		target->data->name(name);
		target->data->phone(phone);
		target->data->address(address);

		this->printHeader(-1);
		this->printPersonInfo(*(target->data), -1);
		cout << "수정되었습니다." << endl;
	}
}

void addressbook::search() {
	string name;
	personInfo info;
	int foundIndex = -1;

	if ( this->isEmpty() == false ) {
		this->print_error(ERROR_EMPTY);
		return ;
	}

	cout << "검색할 이름: ";
	cin >> name;

	info.name(name);

	foundIndex = this->list->find(info);

	if ( foundIndex == -1 ) {
		this->print_error(ERROR_NOT_SEARCH);
		return ;
	}

	this->printHeader(-1);
	this->printPersonInfo(this->list->viewAt(foundIndex), -1);
}

void addressbook::printHeader(int printNum) {
	cout << "----------------------------------------------" << endl;
	if ( printNum != -1 ) {
		cout << "번호  이름     전화번호      주소" << endl;
	} else {
		cout << "이름     전화번호      주소" << endl;
	}
	cout << "----------------------------------------------" << endl;
}

void addressbook::printPersonInfo(personInfo &info, int printNum) {
	if ( printNum != -1 ) {
		cout << left << setw(4);
	} 
	cout << info << endl;
}

void addressbook::printAll() {
	int number = 1;
	node<personInfo> *target;

	if ( this->isEmpty() == true ) {
		this->print_error(ERROR_EMPTY);
		return ;
	}

	this->printHeader(1);
	target = this->list->moveFirst();
	while ( this->list->isTail() != true ) {
		this->printPersonInfo(*(target->data), number);
		target = this->list->moveNext();
		number++;
	}
}

void addressbook::save() {
	ofstream fcout;
	node<personInfo> *target;

	if ( this->isEmpty() == true ) {
		this->print_error(ERROR_EMPTY);
		return ;
	}

	fcout.open("addressbook.dat", ios::out);

	target = this->list->moveFirst();

	if (fcout.is_open()) {
		while ( this->list->isTail() != true ) {
			fcout << target->data->name() << endl;
			fcout << target->data->phone() << endl;
			fcout << target->data->address() << endl;
			target = this->list->moveNext();
		}
		fcout.close();
	}

	cout << "addressbook.dat 파일에 저장하였습니다." << endl;
}

void addressbook::load() {
	ifstream fcin;
	personInfo info;
	string name;
	string phone;
	string address;

	this->list->deleteAll();

	fcin.open("addressbook.dat", ios::in);

	if (fcin.is_open() == false) {
		this->print_error(ERROR_LOAD_FAIL);
		return ;
	}

	while (!fcin.eof()) {
		getline(fcin, name);
		info.name(name);
		getline(fcin, phone);
		info.phone(phone);
		getline(fcin, address);
		info.address(address);

		if ( name == "" ) {
			break;
		}
		this->list->append(info);
	}

	fcin.close();
	cout << "addressbook.dat 파일을 불러왔습니다." << endl;
}

void addressbook::testSetup() {
	int index = 0;
	personInfo sample[10];

	sample[0].name("aaa");
	sample[0].phone("0001112222");
	sample[0].address("acb");

	sample[1].name("bbb");
	sample[1].phone("0001113333");
	sample[1].address("abc");

	sample[2].name("ccc");
	sample[2].phone("0001114444");
	sample[2].address("abc");

	sample[3].name("ddd");
	sample[3].phone("0001115555");
	sample[3].address("abc");

	sample[4].name("eee");
	sample[4].phone("0001116666");
	sample[4].address("abc");

	sample[5].name("fff");
	sample[5].phone("0001117777");
	sample[5].address("abc");

	sample[6].name("ggg");
	sample[6].phone("0001118888");
	sample[6].address("abc");

	sample[7].name("hhh");
	sample[7].phone("0001119999");
	sample[7].address("abc");

	sample[8].name("iii");
	sample[8].phone("0001110000");
	sample[8].address("abc");

	sample[9].name("jjj");
	sample[9].phone("0002220000");
	sample[9].address("abc");

	for ( index = 0; index < 10; index++ ) {
		this->list->append(sample[index]);
	}
}
