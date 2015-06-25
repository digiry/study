# -*- coding: utf-8 -*-

import wx

from wxpy_programming.view import mainFrame


def main():
    mainApp = wx.App()
    mainscreen = mainFrame.MainFrame(None)
    mainscreen.show(True)
    mainApp.MainLoop()

if __name__ == '__main__':
    main()