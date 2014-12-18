#include "personInfo.h"
#include <iomanip>

using namespace std;

personInfo::personInfo() {
	this->_name = "";
	this->_phone = "";
	this->_address = "";
}
personInfo::personInfo(personInfo &info) {
	this->_name = info._name;
	this->_phone = info._phone;
	this->_address = info._address;
}
personInfo::~personInfo() {
	this->_name = "";
	this->_phone = "";
	this->_address = "";
}

string personInfo::name() {
	return this->_name;
}
void personInfo::name(string name) {
	this->_name = name;
}
string personInfo::phone() {
	return this->_phone;
}
void personInfo::phone(string phone) {
	this->_phone = phone;
}
string personInfo::address() {
	return this->_address;
}
void personInfo::address(string address) {
	this->_address = address;
}

personInfo& personInfo::operator= (personInfo& rinfo) {
	this->_name = rinfo._name;
	this->_phone = rinfo._phone;
	this->_address = rinfo._address;

	return *this;
}
bool personInfo::operator== (personInfo& rinfo) {
	bool isEqual = false;

	if (this->_name == rinfo._name) {
		isEqual = true;
	}

	return isEqual;
}
bool personInfo::operator== (string name) {
	bool isEqual = false;

	if (this->_name == name) {
		isEqual = true;
	}

	return isEqual;
}
ostream& operator<< (ostream &os, personInfo &rinfo) {
	os << left << setw(7) << rinfo.name() 
		<< left << setw(14) << rinfo.phone()
		<< left << setw(50) << rinfo.address();

	return os;
}
