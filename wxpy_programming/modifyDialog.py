# -*- coding: utf-8 -*-

import wx

class ModifyDialog(wx.Dialog):
    title='Modify dialog'
    size=(400,150)
    name = None
    phone = None
    address = None
    def __init__(self, parent):
        super(ModifyDialog, self).__init__(parent, title=self.title, size=self.size)
        self.init_view()

    def init_view(self):
        panel = wx.Panel(self)
        vbox = wx.BoxSizer(wx.VERTICAL)

        hbox1 = wx.BoxSizer(wx.HORIZONTAL)

        namelabel = wx.StaticText(panel, label='이        름:')
        hbox1.Add(namelabel, flag=wx.RIGHT, border=5)
        nameTextCtrl = wx.TextCtrl(panel)
        hbox1.Add(nameTextCtrl, proportion=1)
        vbox.Add(hbox1, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=5)

        hbox2 = wx.BoxSizer(wx.HORIZONTAL)
        phonelabel = wx.StaticText(panel, label='전화번호:')
        hbox2.Add(phonelabel, flag=wx.RIGHT, border=5)
        phoneTextCtrl = wx.TextCtrl(panel)
        hbox2.Add(phoneTextCtrl, proportion=1)
        vbox.Add(hbox2, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=5)

        hbox3 = wx.BoxSizer(wx.HORIZONTAL)
        addresslabel = wx.StaticText(panel, label='주        소:')
        hbox3.Add(addresslabel, flag=wx.RIGHT, border=5)
        addressTextCtrl = wx.TextCtrl(panel)
        hbox3.Add(addressTextCtrl, proportion=1)
        vbox.Add(hbox3, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=5)

        vbox.Add((-1, 10))

        hbox4 = wx.BoxSizer(wx.HORIZONTAL)
        modifyButton = wx.Button(panel, label='Modify')
        hbox4.Add(modifyButton, proportion=1)

        cancelButton = wx.Button(panel, label='Cancel')
        hbox4.Add(cancelButton, proportion=1)

        vbox.Add(hbox4, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=5)

        panel.SetSizer(vbox)

        modifyButton.Bind(wx.EVT_BUTTON, self.OnModifyClicked)
        cancelButton.Bind(wx.EVT_BUTTON, self.OnCancelClicked)

    def OnModifyClicked(self, e):
        pass

    def OnCancelClicked(self, e):
        self.Destroy()