# -*- coding: utf-8 -*-

import addressbook

def main():
    menu = -1
    book = addressbook.addressbook()
    
    book.testSetup()
    
    while (menu != 0):
        book.printMainMenu()

        menu = raw_input("menu: ")

        menu = int(menu)

        if menu == book.MENU_INPUT:
            book.input()
        elif menu == book.MENU_REMOVE:
            book.remove()
        elif menu == book.MENU_MODIFY:
            book.modify()
        elif menu == book.MENU_SEARCH:
            book.search()
        elif menu == book.MENU_ALL_PRINT:
            book.printAll()
        elif menu == book.MENU_SAVE:
            book.save()
        elif menu == book.MENU_LOAD:
            book.load()
        elif menu == book.MENU_DB_LOAD:
            book.load_db()
        elif menu == book.MENU_DB_SAVE:
            book.save_db()
        elif menu == book.MENU_FINISH:
            book.print_finish()
        else:
            book.print_error(book.ERROR_NO_MENU)

        if (menu != book.MENU_FINISH):
            raw_input("menu 화면으로 돌아갑니다. (아무키나 누르세요)")

if __name__ == "__main__":
    main()
