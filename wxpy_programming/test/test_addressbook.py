from unittest import TestCase, main

from wxpy_programming.model.addressbook import addressbook
from wxpy_programming.model.personInfo import personInfo

__author__ = 'ninaeros'


class TestAddressbook(TestCase):
    def setUp(self):
        self.book = addressbook()

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

        self.book.input(self.testInfo1)
        self.book.input(self.testInfo2)
        self.book.input(self.testInfo3)

    def tearDown(self):
        del self.book
        del self.testInfo1
        del self.testInfo2
        del self.testInfo3

    def test_get_length(self):
        self.assertEqual(self.book.get_length(), 3)

    def test_removeAll(self):
        self.book.removeAll()

        self.assertEqual(self.book.get_length(), 0)

    def test_isEmpty(self):
        self.book.removeAll()

        self.assertTrue(self.book.isEmpty())

    def test_input(self):
        testInfo = personInfo()
        testInfo.name = "test4"
        testInfo.phone = "0004440000"
        testInfo.address = "jkl"

        self.book.input(testInfo)
        self.assertEqual(self.book.getNode(3).data.name, testInfo.name)
        self.assertEqual(self.book.getNode(3).data.phone, testInfo.phone)
        self.assertEqual(self.book.getNode(3).data.address, testInfo.address)


    def test_remove(self):
        self.book.remove("test1")

        self.assertNotEqual(self.book.getNode(0).data.name, self.testInfo1.name)
        self.assertNotEqual(self.book.getNode(0).data.phone, self.testInfo1.phone)
        self.assertNotEqual(self.book.getNode(0).data.address, self.testInfo1.address)

    def test_modify(self):
        testInfo = personInfo()
        testInfo.name = "test4"
        testInfo.phone = "0004440000"
        testInfo.address = "jkl"

        self.book.modify("test1", testInfo)
        self.assertEqual(self.book.getNode(0).data.name, testInfo.name)
        self.assertEqual(self.book.getNode(0).data.phone, testInfo.phone)
        self.assertEqual(self.book.getNode(0).data.address, testInfo.address)


    def test_search(self):
        info = self.book.search("test2")

        self.assertEqual(info.name, self.testInfo2.name)
        self.assertEqual(info.phone, self.testInfo2.phone)
        self.assertEqual(info.address, self.testInfo2.address)

    def test_moveFirst(self):
        node = self.book.moveFirst()

        self.assertEqual(node.data.name, self.testInfo1.name)
        self.assertEqual(node.data.phone, self.testInfo1.phone)
        self.assertEqual(node.data.address, self.testInfo1.address)

    def test_moveLast(self):
        node = self.book.moveLast()

        self.assertEqual(node.data.name, self.testInfo3.name)
        self.assertEqual(node.data.phone, self.testInfo3.phone)
        self.assertEqual(node.data.address, self.testInfo3.address)

    def test_moveNext(self):
        node = self.book.moveLast()

        self.assertEqual(node.data.name, self.testInfo3.name)
        self.assertEqual(node.data.phone, self.testInfo3.phone)
        self.assertEqual(node.data.address, self.testInfo3.address)

    def test_isLast(self):
        self.book.moveLast()
        self.book.moveNext()

        self.assertTrue(self.book.isLast())

    def test_getNode(self):
        self.assertEqual(self.book.getNode(1).data.name, self.testInfo2.name)
        self.assertEqual(self.book.getNode(1).data.phone, self.testInfo2.phone)
        self.assertEqual(self.book.getNode(1).data.address, self.testInfo2.address)

    def test_viewAt(self):
        testInfo = self.book.viewAt(1)

        self.assertEqual(testInfo.name, self.testInfo2.name)
        self.assertEqual(testInfo.phone, self.testInfo2.phone)
        self.assertEqual(testInfo.address, self.testInfo2.address)


if __name__ == "__main__":
    main()