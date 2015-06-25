# -*- coding: utf-8 -*-

import wx

class AddDialog(wx.Dialog):

    def __init__(self, parent):
        super(AddDialog, self).__init__(parent, title='Add dialog', size=(400,150))
        self._name = None
        self._phone = None
        self._address = None
        self.nameTextCtrl = None
        self.phoneTextCtrl = None
        self.addressTextCtrl = None
        self.init_view()

    def init_view(self):
        panel = wx.Panel(self)
        vbox = wx.BoxSizer(wx.VERTICAL)

        hbox1 = wx.BoxSizer(wx.HORIZONTAL)

        namelabel = wx.StaticText(panel, label='Name:')
        hbox1.Add(namelabel, flag=wx.RIGHT, border=5)
        self.nameTextCtrl = wx.TextCtrl(panel)
        hbox1.Add(self.nameTextCtrl, proportion=1)
        vbox.Add(hbox1, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=5)

        hbox2 = wx.BoxSizer(wx.HORIZONTAL)
        phonelabel = wx.StaticText(panel, label='Phone:')
        hbox2.Add(phonelabel, flag=wx.RIGHT, border=5)
        self.phoneTextCtrl = wx.TextCtrl(panel)
        hbox2.Add(self.phoneTextCtrl, proportion=1)
        vbox.Add(hbox2, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=5)

        hbox3 = wx.BoxSizer(wx.HORIZONTAL)
        addresslabel = wx.StaticText(panel, label='Address:')
        hbox3.Add(addresslabel, flag=wx.RIGHT, border=5)
        self.addressTextCtrl = wx.TextCtrl(panel)
        hbox3.Add(self.addressTextCtrl, proportion=1)
        vbox.Add(hbox3, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=5)

        vbox.Add((-1, 10))

        hbox4 = wx.BoxSizer(wx.HORIZONTAL)
        addButton = wx.Button(panel, label='Add')
        hbox4.Add(addButton, proportion=1)

        cancelButton = wx.Button(panel, label='Cancel')
        hbox4.Add(cancelButton, proportion=1)

        vbox.Add(hbox4, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=5)

        panel.SetSizer(vbox)

        addButton.Bind(wx.EVT_BUTTON, self.OnAddButton)
        cancelButton.Bind(wx.EVT_BUTTON, self.OnCancelButton)

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, name):
        self._name = name

    @property
    def phone(self):
        return self._phone

    @phone.setter
    def phone(self, phone):
        self._phone = phone

    @property
    def address(self):
        return self._address

    @address.setter
    def address(self, address):
        self._address = address

    def OnAddButton(self, event):
        pass

    def OnCancelButton(self, event):
        self.Destroy()

def main():
    print "help"

if __name__ == '__main__':
    main()