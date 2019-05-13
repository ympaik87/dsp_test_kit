import wx


class ParamAlgorithmPanel(wx.Panel):
    def __init__(self, notebook, dye_li):
        wx.Panel.__init__(self, notebook, wx.ID_ANY, wx.DefaultPosition,
                          wx.DefaultSize, wx.TAB_TRAVERSAL)
        sizer_panel4 = wx.BoxSizer(wx.VERTICAL)
        self.dye_li = dye_li

        sizer_alg = wx.BoxSizer(wx.VERTICAL)
        txt = wx.StaticText(self, wx.ID_ANY, 'Algorithm',
                            wx.DefaultPosition, wx.DefaultSize, 0)
        txt.Wrap(-1)
        sizer_alg.Add(txt, 0, wx.ALL, 5)

        choice_li = [
            ['Default (latest ver.)', 'Old ver.'],
            ['All', 'Sample only', 'PC only'],
            ['Defualt', 'GI-V (cross-talk)',
             'GI-BI (2-CR)', 'GI-P (Q670 PC)']
        ]
        sizer_fg2 = wx.FlexGridSizer(0, 3, 0, 40)
        sizer_fg2 = wx.FlexGridSizer(0, 3, 0, 40)
        sizer_fg2.SetFlexibleDirection(wx.BOTH)
        sizer_fg2.SetNonFlexibleGrowMode(wx.FLEX_GROWMODE_SPECIFIED)
        self.algorithm_entry_li = []

        txt = wx.StaticText(self, wx.ID_ANY, '제품별 알고리즘',
                            wx.DefaultPosition, wx.DefaultSize, 0)
        txt.Wrap(-1)
        sizer_fg2.Add(txt, 0, wx.ALL, 5)
        choice = wx.Choice(self, wx.ID_ANY, wx.DefaultPosition,
                           wx.DefaultSize, choice_li[2])
        choice.SetSelection(0)
        self.algorithm_entry_li.append(choice)
        sizer_fg2.Add(choice, 0, wx.ALL, 5)
        sizer_alg.Add(sizer_fg2, 0, wx.ALIGN_CENTER, 5)
        sizer_panel4.Add(sizer_alg, 1, wx.EXPAND, 5)

        self.SetSizer(sizer_panel4)
        self.Layout()
        sizer_panel4.Fit(self)

    def set_label_file_picker(self):
        self.sizer_label = wx.BoxSizer(wx.VERTICAL)
        radiobox_choices = ['DSP result', 'From label file']
        self.radiobox = wx.RadioBox(self, wx.ID_ANY, 'Choose label type',
                                    wx.DefaultPosition, wx.DefaultSize,
                                    radiobox_choices, 2, wx.RA_SPECIFY_COLS)
        self.sizer_label.Add(self.radiobox, 0, wx.ALL, 5)

    def get_algorithm_dict(self):
        algorithm_param_dict = {}
        al_li = ['absd_corrector_ver', 'asymm_sigfit_ver']
        for i in range(2):
            # ver = self.algorithm_entry_li[i][0].GetSelection()
            # target = self.algorithm_entry_li[i][1].GetSelection()
            ver = 0
            target = 0
            if target == 1:
                target_dict = {'PC': 0, 'sample': 1}
            elif target == 2:
                target_dict = {'PC': 1, 'sample': 0}
            else:
                target_dict = {'PC': 1, 'sample': 1}
            if ver == 1:
                algorithm_param_dict[al_li[i]] = target_dict
            else:
                algorithm_param_dict[al_li[i]] = {'PC': 0, 'sample': 0}

        prod_al = self.algorithm_entry_li[2].GetSelection()
        if prod_al == 1:
            algorithm_param_dict['gi_switch'] = 1
            algorithm_param_dict['gib1_switch'] = 0
            algorithm_param_dict['gip'] = 0
        elif prod_al == 2:
            algorithm_param_dict['gi_switch'] = 0
            algorithm_param_dict['gib1_switch'] = 1
            algorithm_param_dict['gip'] = 0
        elif prod_al == 3:
            algorithm_param_dict['gi_switch'] = 0
            algorithm_param_dict['gib1_switch'] = 0
            algorithm_param_dict['gip'] = 1
        else:
            algorithm_param_dict['gi_switch'] = 0
            algorithm_param_dict['gib1_switch'] = 0
            algorithm_param_dict['gip'] = 0
        algorithm_param_dict['crosstalk'] = self.get_crosstalk()
        return algorithm_param_dict

    def get_crosstalk(self):
        crosstalk_val_li = []
        for cross_entries in self.crosstalk_li:
            vals = [None for e in cross_entries[:2]]
            if vals[0] and vals[1]:
                ch1 = self.crosstalk_choice_li[vals[0] - 1]
                ch2 = self.crosstalk_choice_li[vals[1] - 1]
                drfu = float(cross_entries[2].GetValue())
                ct = float(cross_entries[3].GetValue())
                crosstalk_val_li.append([ch1, ch2, drfu, ct])
        return crosstalk_val_li
