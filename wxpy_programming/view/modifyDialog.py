# -*- coding: utf-8 -*-

import wx
from wxpy_programming.model import personInfo
from wxpy_programming.view import inputValidator

class ModifyDialog(wx.Dialog):

    def __init__(self, parent, book=None):
        super(ModifyDialog, self).__init__(parent, title='Modify dialog', size=(400,150))
        self.nameTextCtrl = None
        self.phoneTextCtrl = None
        self.addressTextCtrl = None
        self.book = book
        self.modifyname = ""
        self.init_view()

    def init_view(self):
        panel = wx.Panel(self)
        vbox = wx.BoxSizer(wx.VERTICAL)

        hbox1 = wx.BoxSizer(wx.HORIZONTAL)

        namelabel = wx.StaticText(panel, label='Name:')
        hbox1.Add(namelabel, flag=wx.RIGHT, border=5)
        self.nameTextCtrl = wx.TextCtrl(panel)
        hbox1.Add(self.nameTextCtrl, proportion=1)
        searchButton = wx.Button(panel, label='Search')
        hbox1.Add(searchButton, proportion=1)
        vbox.Add(hbox1, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=5)

        hbox2 = wx.BoxSizer(wx.HORIZONTAL)
        phonelabel = wx.StaticText(panel, label='Phone:')
        hbox2.Add(phonelabel, flag=wx.RIGHT, border=5)
        self.phoneTextCtrl = wx.TextCtrl(panel, validator=inputValidator.InputValidator(inputValidator.PHONE_FORMAT))
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
        modifyButton = wx.Button(panel, label='Modify')
        hbox4.Add(modifyButton, proportion=1)

        cancelButton = wx.Button(panel, label='Cancel')
        hbox4.Add(cancelButton, proportion=1)

        vbox.Add(hbox4, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=5)

        panel.SetSizer(vbox)

        self.phoneTextCtrl.Disable()
        self.addressTextCtrl.Disable()

        searchButton.Bind(wx.EVT_BUTTON, self.OnSearchButton)
        modifyButton.Bind(wx.EVT_BUTTON, self.OnModifyButton)
        cancelButton.Bind(wx.EVT_BUTTON, self.OnCancelButton)

    def OnSearchButton(self, event):
        name = self.nameTextCtrl.GetValue().encode('ascii', 'ignore')
        info = self.book.search(name)
        if info:
            self.modifyname = name
            self.phoneTextCtrl.SetValue(info.phone)
            self.addressTextCtrl.SetValue(info.address)
            self.phoneTextCtrl.Enable()
            self.addressTextCtrl.Enable()
        else:
            wx.MessageBox('Can not found : %s' % name, 'Warning', wx.OK | wx.ICON_WARNING)
            self.nameTextCtrl.Clear()
            self.phoneTextCtrl.Clear()
            self.addressTextCtrl.Clear()
            self.phoneTextCtrl.Disable()
            self.addressTextCtrl.Disable()
            self.modifyname = ""

    def OnModifyButton(self, event):
        if self.modifyname:
            ynDialog = wx.MessageBox('Do you modify searched item?', 'Yes or No', wx.YES_NO|wx.NO_DEFAULT|wx.ICON_QUESTION)
            if ynDialog == wx.YES:
                info = personInfo.personInfo()
                info.name = self.nameTextCtrl.GetValue()
                info.phone = self.phoneTextCtrl.GetValue()
                info.address = self.addressTextCtrl.GetValue()
                self.book.modify(self.modifyname, info)
                wx.MessageBox('%s is modified' % self.modifyname, 'Info', wx.OK|wx.ICON_INFORMATION)
                self.Destroy()

    def OnCancelButton(self, event):
        self.Destroy()