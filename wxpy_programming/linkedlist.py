# -*- coding: utf-8 -*-

class node(object):
    def __init__(self, data=None):
        self.data = data
        self.next = None

class linkedlist(object):
    def __init__(self):
        self.head = node()
        self.tail = node()
        self.pos = node()
        self.length = 0

        self.head.next = self.tail
        self.pos = self.tail

    def append(self, data):
        last = self.moveLast()
        newNode = node()

        newNode.data = data
        newNode.next = last.next
        last.next = newNode

        self.pos = newNode
        self.length = self.length + 1

    def moveToBeforeNode(self, index):
        i = 0

        if (index <= 0):
            target = self.head
        else:
            target = self.moveFirst()
            while (i < index - 1):
                target = self.moveNext()
                i = i + 1

        return target

    def insert(self, index, data):
        newNode = node(data)

        target = self.moveToBeforeNode(index)

        newNode.next = target.next
        target.next = newNode
        self.length = self.length + 1

        self.pos = newNode

    def deleteNode(self, index):
        before = self.moveToBeforeNode(index)
        target = before.next
        before.next = target.next

        del target.data
        target.next = None
        del target

        self.pos = before
        self.length = self.length - 1

    def deleteAll(self):
        if (self.length == 0):
            return None

        while (self.length > 0):
            self.deleteNode(0)

        self.pos = self.head.next

    def viewAt(self, index):
        target = self.moveToBeforeNode(index).next

        self.pos = target
        return target.data

    def moveFirst(self):
        self.pos = self.head.next

        return self.pos

    def moveLast(self):
        if (self.length <= 0):
            target = self.head
        else:
            target = self.moveToBeforeNode(self.length - 1).next

        self.pos = target

        return target

    def moveNext(self):
        self.pos = self.pos.next

        return self.pos

    def isTail(self):
        isTail = False

        if (self.pos.next == None):
            isTail = True

        return isTail

    def get_length(self):
        return self.length

    def getNode(self, index):
        return self.moveToBeforeNode(index).next

    def find(self, data):
        index = 0
        isFound = False

        self.moveFirst()
        while (self.isTail() != True):
            if (self.pos.data == data):
                isFound = True
                break
            self.moveNext()
            index = index + 1

        if (isFound == False):
            index = -1

        return index
