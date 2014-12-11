/*
 * testmain.cpp
 *
 *  Created on: 2014. 11. 21.
 *      Author: suandkyu
 */


#include "addressbook.h"
#include <iostream>

using namespace std;

int main() {
	int menu = -1;
	addressbook *book = new addressbook;

	//book->testSetup();

	while (menu != 0) {
		book->printMainMenu();

		cout << "menu: ";
		cin >> menu;
		cin.sync();

		switch (menu) {
		case MENU_INPUT:
			book->input();
			break;
		case MENU_REMOVE:
			book->remove();
			break;
		case MENU_MODIFY:
			book->modify();
			break;
		case MENU_SEARCH:
			book->search();
			break;
		case MENU_ALL_PRINT:
			book->printAll();
			break;
		case MENU_SAVE:
			book->save();
			break;
		case MENU_LOAD:
			book->load();
			break;
		case MENU_FINISH:
			book->print_finish();
			break;
		default:
			book->print_error(ERROR_NO_MENU);
			break;
		}
		if (menu != MENU_FINISH) {
			cin.sync();
			cout << endl << "menu 화면으로 돌아갑니다. (아무키나 누르세요)" << endl;
			cin.get();
		}
	}
	return 0;
}
