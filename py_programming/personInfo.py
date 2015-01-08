# -*- coding: utf-8 -*-

class personInfo(object):
    def __init__(self, info = None):
        self._name = info._name if info else ""
        self._phone = info._phone if info else ""
        self._address = info._address if info else ""

    def __del__(self):
        self._name = ""
        self._phone = ""
        self._address = ""

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, value):
        self._name = value

    @property
    def phone(self):
        return self._phone

    @phone.setter
    def phone(self, value):
        self._phone = value

    @property
    def address(self):
        return self._address

    @address.setter
    def address(self, value):
        self._address = value

    def __eq__(self, other):
        isEqual = False

        if type(other) is personInfo:
            if (self._name == other._name):
                isEqual = True
        elif type(other) is str:
            if (self._name == other):
                isEqual = True
        else:
            isEqual = False

        return isEqual
