# -*- coding: utf-8 -*-

import wx

class addDialog(wx.Dialog):
    title='Add dialog'
    size=(300,220)
    def __init__(self, parent):
        super(addDialog, self).__init__(parent, title=self.title, size=self.size)
        self.init_view()

    def init_view(self):
        panel = wx.Panel(self)
        hbox = wx.BoxSizer(wx.VERTICAL)

        innerpanel = wx.Panel(panel, -1)
        vbox = wx.BoxSizer(wx.HORIZONTAL)

        namelabel = wx.StaticText(innerpanel, label='이름:')
        vbox.Add(namelabel, 0, wx.TOP, 5)
        nameTextCtrl = wx.TextCtrl(innerpanel)
        vbox.Add(nameTextCtrl, 10, wx.TOP, 5)
        innerpanel.SetSizer(vbox)
        hbox.Add(innerpanel, 0.6, wx.EXPAND)

        panel.SetSizer(hbox)

    def show(self, showflag):
        self.Show(showflag)
