# -*- coding: utf-8 -*-

import wx

class SearchDialog(wx.Dialog):
    def __init__(self, parent):
        super(SearchDialog, self).__init__(parent, title='Search dialog', size=(400,150))
        self._name = None
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
        searchButton = wx.Button(panel, label='Search')
        hbox1.Add(searchButton, proportion=1)
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

        hbox2 = wx.BoxSizer(wx.HORIZONTAL)
        okButton = wx.Button(panel, label='Ok')
        hbox2.Add(okButton, proportion=1)

        vbox.Add(hbox2, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=5)

        panel.SetSizer(vbox)

        self.phoneTextCtrl.Disable()
        self.addressTextCtrl.Disable()

        searchButton.Bind(wx.EVT_BUTTON, self.OnSearchButton)
        okButton.Bind(wx.EVT_BUTTON, self.OnOkButton)

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, name):
        self._name = name

    def OnSearchButton(self, event):
        pass

    def OnOkButton(self, event):
        pass