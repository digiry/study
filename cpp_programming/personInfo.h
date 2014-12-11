/*
* personInfoCpp.h
*
*  Created on: 2014. 11. 16.
*      Author: suandkyu
*/

#ifndef PERSONINFO_H_
#define PERSONINFO_H_

#include <string>

using namespace std;

class personInfo {
private:
	string _name;
	string _phone;
	string _address;
public:
	personInfo();
	personInfo(personInfo &info);
	~personInfo();

	string name();
	void name(string name);
	string phone();
	void phone(string phone);
	string address();
	void address(string address);

	personInfo& operator= (personInfo& rinfo);
	bool operator== (personInfo& rinfo);
	bool operator== (string name);
	friend ostream& operator<< (ostream &os, personInfo &rinfo);
};

#endif /* PERSONINFO_H_ */
