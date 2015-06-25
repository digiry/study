__author__ = 'ninaeros'

import wx
import string
import re

PHONE_FORMAT = 0

class InputValidator(wx.PyValidator):
    def __init__(self, flag=None):
        wx.PyValidator.__init__(self)
        self.flag = flag
        self.Bind(wx.EVT_CHAR, self.OnInputPhone)

    def Clone(self):
        return InputValidator(self.flag)

    def Validate(self, win):
        isvalid = True
        targetWindow = self.GetWindow()

        if type(targetWindow) is wx.ListCtrl:
            values = targetWindow.GetValue()

            if self.flag == PHONE_FORMAT:
                phonepattern = re.compile(r"^\d{3}[-]\d{3,4}[-]\d{4}")
                if not phonepattern.findall(values):
                    isvalid = False

        return isvalid

    def OnInputPhone(self, event):
        key = event.GetKeyCode()

        if key < wx.WXK_SPACE or key == wx.WXK_DELETE or key > 255:
            event.Skip()
            return

        if self.flag == PHONE_FORMAT and (chr(key) in string.digits or chr(key) == '-'):
            event.Skip()
            return

        return