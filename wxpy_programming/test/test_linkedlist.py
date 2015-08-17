from unittest import TestCase, main

from model.linkedlist import linkedlist
from model.personInfo import personInfo

__author__ = 'ninaeros'

class TestLinkedlist(TestCase):
    def setUp(self):
        self.list = linkedlist()

        self.testInfo1 = personInfo()
        self.testInfo1.name = "test1"
        self.testInfo1.phone = "0001110000"
        self.testInfo1.address = "abc"
        self.testInfo2 = personInfo()
        self.testInfo2.name = "test2"
        self.testInfo2.phone = "0002220000"
        self.testInfo2.address = "def"
        self.testInfo3 = personInfo()
        self.testInfo3.name = "test3"
        self.testInfo3.phone = "0003330000"
        self.testInfo3.address = "ghi"

        self.list.append(self.testInfo1)
        self.list.append(self.testInfo2)
        self.list.append(self.testInfo3)

    def tearDown(self):
        del self.list
        del self.testInfo1
        del self.testInfo2
        del self.testInfo3

    def test_get_length(self):
        self.assertEqual(self.list.get_length(), 3)

    def test_getNode(self):
        self.assertEqual(self.list.getNode(1).data.name, self.testInfo2.name)
        self.assertEqual(self.list.getNode(1).data.phone, self.testInfo2.phone)
        self.assertEqual(self.list.getNode(1).data.address, self.testInfo2.address)

    def test_append(self):
        testInfo = personInfo()
        testInfo.name = "test4"
        testInfo.phone = "0004440000"
        testInfo.address = "jkl"

        self.list.append(testInfo)
        self.assertEqual(self.list.get_length(), 4)
        self.assertEqual(self.list.getNode(3).data.name, testInfo.name)
        self.assertEqual(self.list.getNode(3).data.phone, testInfo.phone)
        self.assertEqual(self.list.getNode(3).data.address, testInfo.address)


    def test_insert(self):
        testInfo = personInfo()
        testInfo.name = "test4"
        testInfo.phone = "0004440000"
        testInfo.address = "jkl"

        self.list.insert(1, testInfo)
        self.assertEqual(self.list.get_length(), 4)
        self.assertEqual(self.list.getNode(1).data.name, testInfo.name)
        self.assertEqual(self.list.getNode(1).data.phone, testInfo.phone)
        self.assertEqual(self.list.getNode(1).data.address, testInfo.address)

    def test_deleteNode(self):
        self.list.deleteNode(1)

        self.assertEqual(self.list.get_length(), 2)
        self.assertEqual(self.list.getNode(0).data.name, self.testInfo1.name)
        self.assertEqual(self.list.getNode(0).data.phone, self.testInfo1.phone)
        self.assertEqual(self.list.getNode(0).data.address, self.testInfo1.address)

    def test_deleteAll(self):
        self.list.deleteAll()

        self.assertEqual(self.list.get_length(), 0)

    def test_viewAt(self):
        testInfo = self.list.viewAt(1)

        self.assertEqual(testInfo.name, self.testInfo2.name)
        self.assertEqual(testInfo.phone, self.testInfo2.phone)
        self.assertEqual(testInfo.address, self.testInfo2.address)

    def test_moveFirst(self):
        node = self.list.moveFirst()

        self.assertEqual(node.data.name, self.testInfo1.name)
        self.assertEqual(node.data.phone, self.testInfo1.phone)
        self.assertEqual(node.data.address, self.testInfo1.address)

    def test_moveLast(self):
        node = self.list.moveLast()

        self.assertEqual(node.data.name, self.testInfo3.name)
        self.assertEqual(node.data.phone, self.testInfo3.phone)
        self.assertEqual(node.data.address, self.testInfo3.address)

    def test_moveNext(self):
        self.list.moveFirst()
        node = self.list.moveNext()

        self.assertEqual(node.data.name, self.testInfo2.name)
        self.assertEqual(node.data.phone, self.testInfo2.phone)
        self.assertEqual(node.data.address, self.testInfo2.address)

    def test_moveToBeforeNode(self):
        node = self.list.moveToBeforeNode(1)

        self.assertEqual(node.data.name, self.testInfo1.name)
        self.assertEqual(node.data.phone, self.testInfo1.phone)
        self.assertEqual(node.data.address, self.testInfo1.address)

    def test_isTail(self):
        self.list.moveLast()
        self.list.moveNext()

        self.assertTrue(self.list.isTail())


    def test_find(self):
        index = self.list.find("test2")

        self.assertEqual(index, 1)

if __name__ == '__main__':
    main()
