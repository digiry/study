# -*- coding: utf-8 -*-

import personInfo
import linkedlist
import MySQLdb as mdb

class addressbook(object):
    def __init__(self):
        self.list = linkedlist.linkedlist()

    def __del__(self):
        self.list.deleteAll()

        del self.list

    def isEmpty(self):
        isEmpty = True

        if (self.list.get_length() > 0):
            isEmpty = False

        return isEmpty

    def input(self, info):
        self.list.append(info)

    def remove(self, removeIndex):
        self.list.deleteNode(removeIndex)

    def modify(self, modifyIndex, info):
        target = self.list.getNode(modifyIndex)
        target.data = info

    def search(self, name):
        foundIndex = self.list.find(name)

        if (foundIndex == -1):
            return None

        return self.list.viewAt(foundIndex)

    def save(self):
        target = self.list.moveFirst()

        with open('addressbook.dat','w') as f:
            while (self.list.isTail() != True):
                f.write(target.data.name + '\n')
                f.write(target.data.phone + '\n')
                f.write(target.data.address + '\n')
                target = self.list.moveNext()

    def load(self):
        self.list.deleteAll()

        f = open('addressbook.dat','r')
        f.seek(0,2)
        eof = f.tell()
        f.seek(0)
        while True:
            info = personInfo.personInfo()
            info.name = f.readline().rstrip('\n')
            info.phone = f.readline().rstrip('\n')
            info.address = f.readline().rstrip('\n')
            self.list.append(info)
            if eof == f.tell(): break

    def save_db(self):
        target = self.list.moveFirst()

        con = mdb.connect('localhost', 'root', 'tn3924', 'studydb')

        with con:
            cur = con.cursor()
            cur.execute("DELETE FROM addressbook")
            while (self.list.isTail() != True):
                cur.execute("INSERT INTO addressbook (name, phone, address) "
                            "VALUES (\'%s\', \'%s\', \'%s\')" %
                    (target.data.name, target.data.phone, target.data.address))
                target = self.list.moveNext()

    def load_db(self):
        self.list.deleteAll()

        con = mdb.connect('localhost', 'root', 'tn3924', 'studydb')

        with con:
            cur = con.cursor(mdb.cursors.DictCursor)
            cur.execute("SELECT * FROM addressbook")
            rows = cur.fetchall()

            for row in rows:
                info = personInfo.personInfo()
                info.name = row['name']
                info.phone = row['phone']
                info.address = row['address']
                self.list.append(info)
