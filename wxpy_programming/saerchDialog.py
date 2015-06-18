# -*- coding: utf-8 -*-

import wx

class SearchDialog(wx.Dialog):
    title='Search dialog'
    size=(300,80)
    name = None

    def __init__(self, parent):
        super(SearchDialog, self).__init__(parent, title=self.title, size=self.size)
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

        vbox.Add((-1, 10))

        hbox2 = wx.BoxSizer(wx.HORIZONTAL)
        searchButton = wx.Button(panel, label='Search')
        hbox2.Add(searchButton, proportion=1)

        cancelButton = wx.Button(panel, label='Cancel')
        hbox2.Add(cancelButton, proportion=1)

        vbox.Add(hbox2, flag=wx.EXPAND|wx.LEFT|wx.RIGHT|wx.TOP, border=5)

        panel.SetSizer(vbox)

        searchButton.Bind(wx.EVT_BUTTON, self.OnSearchClicked)
        cancelButton.Bind(wx.EVT_BUTTON, self.OnCancelClicked)

    def OnSearchClicked(self, e):
        pass

    def OnCancelClicked(self, e):
        self.Destroy()