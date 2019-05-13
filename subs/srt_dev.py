import wx
import re


class SrtDevPanel(wx.Panel):
    def __init__(self, notebook):
        super().__init__(notebook, wx.ID_ANY, wx.DefaultPosition,
                         wx.DefaultSize, wx.TAB_TRAVERSAL)
        sizer_panel5 = wx.BoxSizer(wx.VERTICAL)
        txt = wx.StaticText(self, wx.ID_ANY, 'Filter Versions',
                            wx.DefaultPosition, wx.DefaultSize, 0)
        txt.Wrap(-1)
        sizer_panel5.Add(txt, 0, wx.ALL, 5)
        sizer_panel5.Add(self.get_ver_array_li(), 1, wx.ALL | wx.EXPAND, 20)

        line = wx.StaticLine(self, wx.ID_ANY, wx.DefaultPosition,
                             wx.DefaultSize, wx.LI_HORIZONTAL)
        sizer_panel5.Add(line, 0, wx.EXPAND | wx.ALL, 5)

        sizer_ds = wx.BoxSizer(wx.HORIZONTAL)
        txt = wx.StaticText(self, wx.ID_ANY, 'Data Scale',
                            wx.DefaultPosition, wx.DefaultSize, 0)
        txt.Wrap(-1)
        sizer_ds.Add(txt, 0, wx.ALL, 5)
        self.txtctrl_ds = wx.TextCtrl(
            self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition,
            wx.DefaultSize, 0)
        sizer_ds.Add(self.txtctrl_ds, 0, wx.ALL, 5)
        sizer_panel5.Add(sizer_ds, 1, wx.ALL | wx.EXPAND, 20)

        self.baseline_checkbox = wx.CheckBox(
            self, wx.ID_ANY, 'Enable latest baseline filter version',
            wx.DefaultPosition, wx.DefaultSize, 0)
        self.baseline_checkbox.SetValue(True)
        sizer_panel5.Add(self.baseline_checkbox, 0, wx.ALL, 5)

        self.SetSizer(sizer_panel5)
        self.Layout()
        sizer_panel5.Fit(self)

    def get_ver_array_li(self):
        self.ver_choice_li = [
            ['Default (Ver. 3)'],
            ['Default (Ver. 0)', 'Ver. 1'],
            ['Default (Ver. 3)'],
            ['Default (Ver. 4)', 'Ver. 3'],
            ['Defualt (Ver. 6)', 'Ver. 4', 'Ver. 5']
        ]
        sizer_fg2 = wx.FlexGridSizer(0, 2, 0, 40)
        sizer_fg2.SetFlexibleDirection(wx.BOTH)
        sizer_fg2.SetNonFlexibleGrowMode(wx.FLEX_GROWMODE_SPECIFIED)
        self.filter_entry_li = []
        for i, txt in enumerate([
                'Jumping 보정 Version', 'Linear Filter Type',
                'Unimportant Filter Version', '이른 증폭 Filter Version',
                'Baseline Filter Version']):
            txt = wx.StaticText(self, wx.ID_ANY, txt,
                                wx.DefaultPosition, wx.DefaultSize, 0)
            txt.Wrap(-1)
            sizer_fg2.Add(txt, 0, wx.ALL, 5)
            choice = wx.Choice(self, wx.ID_ANY, wx.DefaultPosition,
                               wx.DefaultSize, self.ver_choice_li[i])
            choice.SetSelection(0)
            sizer_fg2.Add(choice, 0, wx.ALL, 5)
            self.filter_entry_li.append(choice)
        return sizer_fg2

    def get_partial_ver_array(self):
        ver_array = []
        for i, ver in enumerate(self.filter_entry_li):
            val_ind = ver.GetSelection()
            val_str = self.ver_choice_li[i][val_ind]
            ver_array.append(int(re.findall(r'(?<=Ver. )\d', val_str)[0]))
        return ver_array

    def get_ds(self):
        try:
            return float(self.txtctrl_ds.GetValue())
        except ValueError:
            return 1

    def get_baseline_choice(self):
        return self.baseline_checkbox.GetValue()
