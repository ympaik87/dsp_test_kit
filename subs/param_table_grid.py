from subs.custom_grid import CustomGrid
import wx


class ParamGrid(CustomGrid):
    def __init__(self, parent):
        super().__init__(parent)

    def on_label_right_click(self, event):
        menus = [(wx.NewId(), "Copy", self.copy), None]
        popup_menu = wx.Menu()
        for menu in menus:
            if menu is None:
                popup_menu.AppendSeparator()
                continue
            popup_menu.Append(menu[0], menu[1])
            self.Bind(wx.EVT_MENU, menu[2], id=menu[0])

        self.PopupMenu(popup_menu, event.GetPosition())
        popup_menu.Destroy()
        return

    def on_cell_right_click(self, event):
        menus = [(wx.NewId(), "Copy", self.copy)]
        popup_menu = wx.Menu()
        for menu in menus:
            if menu is None:
                popup_menu.AppendSeparator()
                continue
            popup_menu.Append(menu[0], menu[1])
            self.Bind(wx.EVT_MENU, menu[2], id=menu[0])

        self.PopupMenu(popup_menu, event.GetPosition())
        popup_menu.Destroy()
        return

    def paste(self, event):
        event.Skip()

    def delete(self, event):
        event.Skip()

    def cut(self, event):
        event.Skip()
