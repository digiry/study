# -*- coding: utf-8 -*-

import wx

import addDialog
import saerchDialog
import modifyDialog

class MainFrame(wx.Frame):
    title = 'AddressBook'
    size = (500, 400)
    add_diag = None
    search_diag = None
    modify_diag = None

    def __init__(self, parent):
        super(MainFrame, self).__init__(parent, title=self.title, size=self.size)
        self.init_ui()
        self.Centre()

    def init_ui(self):
        self.init_menu()
        self.init_view()

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

    def init_view(self):
        panel = wx.Panel(self, -1)

        # basic box
        hbox = wx.BoxSizer(wx.HORIZONTAL)

        # List Box
        self.listbox = wx.ListBox(panel, -1)
        hbox.Add(self.listbox, 1, wx.EXPAND | wx.ALL, 20)

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

    def OnAddButton(self, e):
        self.add_diag = addDialog.AddDialog(self)
        self.add_diag.ShowModal()
        self.add_diag.Destroy()

    def OnDeleteButton(self, e):
        pass

    def OnSearchButton(self, e):
        self.search_diag = saerchDialog.SearchDialog(self)
        self.search_diag.ShowModal()
        self.search_diag.Destroy()

    def OnModifyButton(self, e):
        self.modify_diag = modifyDialog.ModifyDialog(self)
        self.modify_diag.ShowModal()
        self.modify_diag.Destroy()

def main():
    mainApp = wx.App()
    MainFrame(None)
    mainApp.MainLoop()

if __name__ == '__main__':
    main()