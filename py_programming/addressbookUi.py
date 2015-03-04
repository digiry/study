# -*- coding: utf-8 -*-

import personInfo
import addressbook

class addressbookUi(object):
    def __init__(self):
        self.MENU_INPUT = 1
        self.MENU_REMOVE = 2
        self.MENU_MODIFY = 3
        self.MENU_SEARCH = 4
        self.MENU_ALL_PRINT = 5
        self.MENU_SAVE = 6
        self.MENU_LOAD = 7
        self.MENU_DB_LOAD = 8
        self.MENU_DB_SAVE = 9
        self.MENU_FINISH = 0
        self.ERROR_NO_MENU = 1
        self.ERROR_FULL = 2
        self.ERROR_EMPTY = 3
        self.ERROR_NOT_SEARCH = 4
        self.ERROR_LOAD_FAIL = 5
        self.book = addressbook.addressbook()

    def __del__(self):
        del self.book

    def printMainMenu(self):
        print """\
1. 주소정보를 입력한다.
2. 주소정보를 삭제한다.
3. 주소정보를 수정한다.
4. 주소정보를 검색한다.
5. 전체 주소록을 출력한다.
6. 주소록 파일에 저장한다.
7. 주소록 파일을 불러온다.
8. 주소록 db 에서 불러온다.
9. 주소록 db 에 저장한다.
0. 종료한다."""

    def print_finish(self):
        print "프로그램을 종료합니다."

    def print_error(self, error):
        if error == self.ERROR_NO_MENU:
            print "없는 번호를 입력하였습니다."
        elif error == self.ERROR_FULL:
            print "주소록이 가득 찼습니다."
        elif error == self.ERROR_EMPTY:
            print "주소록이 비어있습니다."
        elif error == self.ERROR_NOT_SEARCH:
            print "주소정보를 찾을 수 없습니다."
        elif error == self.ERROR_LOAD_FAIL:
            print "addressbook.dat 파일을 불러올수 없습니다."
        else:
            pass

    def input(self):
        info = personInfo.personInfo()

        info.name = raw_input("이름 : ")
        info.phone = raw_input("전화번호 : ")
        info.address = raw_input("주소 : ")

        print "입력된 정보"
        self.printHeader(-1)
        self.printPersonInfo(info, -1)

        yesno = raw_input("추가하시겠습니까 ? (y/n) :")

        if (yesno == 'y'):
            self.book.input(info)
            print "추가되었습니다."

    def remove(self):
        if (self.book.isEmpty() == True):
            self.print_error(self.ERROR_EMPTY)
            return None

        name = raw_input("삭제할 이름: ")

        removeInfo = self.book.search(name)

        if (removeInfo == None):
            self.print_error(self.ERROR_NOT_SEARCH)
            return None

        self.printHeader(-1)
        self.printPersonInfo(removeInfo, -1)

        yesno = raw_input("삭제하겠습니까? (y/n) :")

        if (yesno == 'y'):
            self.book.remove(name)
            print "삭제되었습니다."

    def modify(self):
        if (self.book.isEmpty() == True):
            self.print_error(self.ERROR_EMPTY)
            return None

        input_name = raw_input("수정할 이름: ")

        modifyInfo = self.book.search(input_name)

        if (modifyInfo == None):
            self.print_error(self.ERROR_NOT_SEARCH)
            return None

        self.printHeader(-1)
        self.printPersonInfo(modifyInfo, -1)

        yesno = raw_input("수정하겠습니까? (y/n) :")

        info = personInfo.personInfo()

        if (yesno == 'y'):
            info.name = raw_input("이름 : ")
            info.phone = raw_input("전화번호 : ")
            info.address = raw_input("주소 : ")

            print "수정된 정보"

            self.book.modify(input_name, info)

            self.printHeader(-1)
            self.printPersonInfo(info, -1)
            print "수정되었습니다."

    def search(self):
        if (self.book.isEmpty() == True):
            self.print_error(self.ERROR_EMPTY)
            return None

        name = raw_input("검색할 이름: ")

        info = self.book.search(name)

        if (info == None):
            self.print_error(self.ERROR_NOT_SEARCH)
            return None

        self.printHeader(-1)
        self.printPersonInfo(info, -1)

    def printHeader(self, printNum):
        print "----------------------------------------------"
        if (printNum != -1):
            print "번호  이름     전화번호      주소"
        else:
            print "이름     전화번호      주소"
        print "----------------------------------------------"

    def printPersonInfo(self, info, printNum):
        if (printNum != -1):
            print "%-4s" % printNum,
        print "%-7s %-14s %-50s" % (info.name, info.phone, info.address)

    def printAll(self):
        number = 1

        if (self.book.isEmpty() == True):
            self.print_error(self.ERROR_EMPTY)
            return None

        self.printHeader(1)
        target = self.book.moveFirst()
        while (self.book.isLast() != True):
            self.printPersonInfo(target.data, number)
            target = self.book.moveNext()
            number = number + 1

    def save(self):
        if (self.book.isEmpty() == True):
            self.print_error(self.ERROR_EMPTY)
            return None

        target = self.book.moveFirst()

        with open('addressbook.dat','w') as f:
            while (self.book.isLast() != True):
                f.write(target.data.name + '\n')
                f.write(target.data.phone + '\n')
                f.write(target.data.address + '\n')
                target = self.book.moveNext()

        print "addressbook.dat 파일에 저장하였습니다."

    def load(self):
        self.book.load()
        print "addressbook.dat 파일을 불러왔습니다."

    def save_db(self):
        if (self.book.isEmpty() == True):
            self.print_error(self.ERROR_EMPTY)
            return None

        self.book.save_db()
        print "addressbook db 에 저장하였습니다."

    def load_db(self):
        self.book.load_db()
        print "addressbook db 을 불러왔습니다."

    def testSetup(self):
        samples = []

        info = personInfo.personInfo()
        info.name = "aaa"
        info.phone = "0001112222"
        info.address = "acb"
        samples.append(info)

        info = personInfo.personInfo()
        info.name = "bbb"
        info.phone = "000111333"
        info.address = "acb"
        samples.append(info)

        info = personInfo.personInfo()
        info.name = "ccc"
        info.phone = "000111444"
        info.address = "acb"
        samples.append(info)

        info = personInfo.personInfo()
        info.name = "ddd"
        info.phone = "0001115555"
        info.address = "acb"
        samples.append(info)

        info = personInfo.personInfo()
        info.name = "eee"
        info.phone = "0001116666"
        info.address = "acb"
        samples.append(info)

        info = personInfo.personInfo()
        info.name = "fff"
        info.phone = "0001117777"
        info.address = "acb"
        samples.append(info)

        info = personInfo.personInfo()
        info.name = "ggg"
        info.phone = "0001118888"
        info.address = "acb"
        samples.append(info)

        info = personInfo.personInfo()
        info.name = "hhh"
        info.phone = "0001119999"
        info.address = "acb"
        samples.append(info)

        info = personInfo.personInfo()
        info.name = "iii"
        info.phone = "0002220000"
        info.address = "acb"
        samples.append(info)

        info = personInfo.personInfo()
        info.name = "jjj"
        info.phone = "0002221111"
        info.address = "acb"
        samples.append(info)

        for index in range(10):
            self.book.input(samples[index])

    def launch(self):
        menu = -1

        self.testSetup()

        while (menu != 0):
            self.printMainMenu()

            menu = raw_input("menu: ")

            menu = int(menu)

            if menu == self.MENU_INPUT:
                self.input()
            elif menu == self.MENU_REMOVE:
                self.remove()
            elif menu == self.MENU_MODIFY:
                self.modify()
            elif menu == self.MENU_SEARCH:
                self.search()
            elif menu == self.MENU_ALL_PRINT:
                self.printAll()
            elif menu == self.MENU_SAVE:
                self.save()
            elif menu == self.MENU_LOAD:
                self.load()
            elif menu == self.MENU_DB_LOAD:
                self.load_db()
            elif menu == self.MENU_DB_SAVE:
                self.save_db()
            elif menu == self.MENU_FINISH:
                self.print_finish()
            else:
                self.print_error(self.ERROR_NO_MENU)

            if (menu != self.MENU_FINISH):
                raw_input("menu 화면으로 돌아갑니다. (아무키나 누르세요)")
