# -*- coding: utf-8 -*-

import wx
import sys

from view import deleteDialog, saerchDialog, addDialog, modifyDialog
from model import addressbook


class MainFrame(wx.Frame):

    def __init__(self, parent):
        super(MainFrame, self).__init__(parent, title='AddressBook', size=(800, 400))
        self.add_diag = None
        self.search_diag = None
        self.delete_diag = None
        self.modify_diag = None
        self.listctrl = None
        self.book = addressbook.addressbook()
        self.init_ui()
        self.Centre()

    def init_ui(self):
        self.init_view()
        self.init_menu()

    def init_menu(self):
        menubar = wx.MenuBar()

        fileMenu = wx.Menu()
        saveMenu = fileMenu.Append(wx.ID_SAVE, '&Save\tCtrl+S')
        loadMenu = fileMenu.Append(wx.ID_ANY, 'L&oad\tCtrl+O')
        saveDBMenu = fileMenu.Append(wx.ID_ANY, 'S&aveDB\tCtrl+A')
        loadDBMenu = fileMenu.Append(wx.ID_ANY, '&LoadDB\tCtrl+L')
        exitMenu = fileMenu.Append(wx.ID_EXIT, 'E&xit\tCtrl+X')

        helpMenu = wx.Menu()
        aboutMenu = helpMenu.Append(wx.ID_ABOUT, 'A&bout\tCtrl+B')

        menubar.Append(fileMenu, '&File')
        menubar.Append(helpMenu, '&Help')
        self.SetMenuBar(menubar)

        self.Bind(wx.EVT_MENU, self.OnLoadMenu, loadMenu)
        self.Bind(wx.EVT_MENU, self.OnSaveMenu, saveMenu)

    def init_view(self):
        panel = wx.Panel(self, -1)

        # basic box
        hbox = wx.BoxSizer(wx.HORIZONTAL)

        # List Box
        self.listctrl = wx.ListCtrl(panel, -1, style=wx.LC_REPORT)
        self.listctrl.InsertColumn(0, 'name', width=100)
        self.listctrl.InsertColumn(1, 'phone', width=150)
        self.listctrl.InsertColumn(2, 'address', width=200)
        hbox.Add(self.listctrl, 1, wx.EXPAND | wx.ALL, 20)

        # Button box
        buttonPanel = wx.Panel(panel, -1)
        vbox = wx.BoxSizer(wx.VERTICAL)

        addButton = wx.Button(buttonPanel, label='ADD', size=(80, 30))
        addButton.Bind(wx.EVT_BUTTON, self.OnAddButton)
        vbox.Add(addButton, 0, wx.TOP, 20)

        deleteButton = wx.Button(buttonPanel, label='DELETE', size=(80, 30))
        deleteButton.Bind(wx.EVT_BUTTON, self.OnDeleteButton)
        vbox.Add(deleteButton, 0, wx.TOP, 60)

        searchButton = wx.Button(buttonPanel, label='SEARCH', size=(80, 30))
        searchButton.Bind(wx.EVT_BUTTON, self.OnSearchButton)
        vbox.Add(searchButton, 0, wx.TOP, 60)

        modifyButton = wx.Button(buttonPanel, label='MODIFY', size=(80, 30))
        modifyButton.Bind(wx.EVT_BUTTON, self.OnModifyButton)
        vbox.Add(modifyButton, 0, wx.TOP, 60)

        buttonPanel.SetSizer(vbox)
        hbox.Add(buttonPanel, 0.6, wx.EXPAND | wx.RIGHT, 20)

        panel.SetSizer(hbox)

    def show(self, showflag):
        self.Show(showflag)

    def update_addressbook_contents(self):
        self.listctrl.DeleteAllItems()
        target = self.book.moveFirst()
        while (self.book.isLast() != True):
            index = self.listctrl.InsertStringItem(sys.maxint, target.data.name)
            self.listctrl.SetStringItem(index, 1, target.data.phone)
            self.listctrl.SetStringItem(index, 2, target.data.address)
            target = self.book.moveNext()

    def OnAddButton(self, event):
        self.add_diag = addDialog.AddDialog(self, book=self.book)
        self.add_diag.ShowModal()
        self.update_addressbook_contents()

    def OnDeleteButton(self, event):
        self.delete_diag = deleteDialog.DeleteDialog(self, book=self.book)
        self.delete_diag.ShowModal()
        self.update_addressbook_contents()

    def OnSearchButton(self, event):
        self.search_diag = saerchDialog.SearchDialog(self, book=self.book)
        self.search_diag.ShowModal()

    def OnModifyButton(self, event):
        self.modify_diag = modifyDialog.ModifyDialog(self, book=self.book)
        self.modify_diag.ShowModal()
        self.update_addressbook_contents()

    def OnLoadMenu(self, event):
        self.listctrl.DeleteAllItems()
        self.book.removeAll()
        self.book.load()
        target = self.book.moveFirst()
        while (self.book.isLast() != True):
            index = self.listctrl.InsertStringItem(sys.maxint, target.data.name)
            self.listctrl.SetStringItem(index, 1, target.data.phone)
            self.listctrl.SetStringItem(index, 2, target.data.address)
            target = self.book.moveNext()

        count = self.listctrl.GetItemCount()
        wx.MessageBox('%d items is loaded' % count, 'Info', wx.OK | wx.ICON_INFORMATION)

    def OnSaveMenu(self, event):
        if not self.book.isEmpty():
            self.book.save()
            wx.MessageBox('%s items is saved' % self.book.get_length(), 'Info', wx.OK|wx.ICON_INFORMATION)

def main():
    mainApp = wx.App()
    MainFrame(None)
    mainApp.MainLoop()

if __name__ == '__main__':
    main()
