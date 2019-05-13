import wx


class ParamAlgorithmPanel(wx.Panel):
    def __init__(self, notebook, dye_li):
        wx.Panel.__init__(self, notebook, wx.ID_ANY, wx.DefaultPosition,
                          wx.DefaultSize, wx.TAB_TRAVERSAL)
        sizer_panel4 = wx.BoxSizer(wx.VERTICAL)
        self.dye_li = dye_li

        sizer_crosstalk = wx.BoxSizer(wx.VERTICAL)
        txt = wx.StaticText(self, wx.ID_ANY, 'Crosstalk',
                            wx.DefaultPosition, wx.DefaultSize, 0)
        txt.Wrap(-1)
        sizer_crosstalk.Add(txt, 0, wx.ALL, 5)

        sizer_fg = wx.FlexGridSizer(4, 6, 0, 0)
        sizer_fg.SetFlexibleDirection(wx.BOTH)
        sizer_fg.SetNonFlexibleGrowMode(wx.FLEX_GROWMODE_SPECIFIED)
        sizer_fg.Add((0, 0), 1, wx.EXPAND, 5)
        txt = wx.StaticText(self, wx.ID_ANY, 'Target 1 (From)',
                            wx.DefaultPosition, wx.DefaultSize, 0)
        txt.Wrap(-1)
        sizer_fg.Add(txt, 0, wx.ALL, 5)
        sizer_fg.Add((0, 0), 1, wx.EXPAND, 5)
        txt = wx.StaticText(self, wx.ID_ANY, 'Target 2 (To)',
                            wx.DefaultPosition, wx.DefaultSize, 0)
        txt.Wrap(-1)
        sizer_fg.Add(txt, 0, wx.ALL, 5)

        for t in ['DRFU', 'Ct Thrd']:
            txt = wx.StaticText(self, wx.ID_ANY, t, wx.DefaultPosition,
                                wx.DefaultSize, 0)
            txt.Wrap(-1)
            sizer_fg.Add(txt, 0, wx.ALL, 5)

        self.crosstalk_choice_li = ['Choose channel']
        for dye in self.dye_li:
            for temp_sub in ['_L', '_H']:
                self.crosstalk_choice_li.append(dye + temp_sub)

        self.crosstalk_li = []
        for i in range(3):
            txt = wx.StaticText(self, wx.ID_ANY, f'crosstalk {i+1}',
                                wx.DefaultPosition, wx.DefaultSize, 0)
            txt.Wrap(-1)
            sizer_fg.Add(txt, 0, wx.ALL, 5)

            choice1 = wx.Choice(
                self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize,
                self.crosstalk_choice_li, 0)
            choice1.SetSelection(0)
            sizer_fg.Add(choice1, 0, wx.ALL, 5)

            txt = wx.StaticText(self, wx.ID_ANY, '➜',
                                wx.DefaultPosition, wx.DefaultSize, 0)
            txt.Wrap(-1)
            sizer_fg.Add(txt, 0, wx.ALL, 5)

            choice2 = wx.Choice(
                self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize,
                self.crosstalk_choice_li, 0)
            choice2.SetSelection(0)
            sizer_fg.Add(choice2, 0, wx.ALL, 5)

            txtctrl_drfu = wx.TextCtrl(
                self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition,
                wx.DefaultSize, 0)
            sizer_fg.Add(txtctrl_drfu, 0, wx.ALL, 5)
            txtctrl_ct = wx.TextCtrl(
                self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition,
                wx.DefaultSize, 0)
            sizer_fg.Add(txtctrl_ct, 0, wx.ALL, 5)
            self.crosstalk_li.append(
                [choice1, choice2, txtctrl_drfu, txtctrl_ct])
        sizer_crosstalk.Add(sizer_fg, 1, wx.EXPAND, 5)
        sizer_panel4.Add(sizer_crosstalk, 1, wx.EXPAND, 5)

        line = wx.StaticLine(self, wx.ID_ANY, wx.DefaultPosition,
                             wx.DefaultSize, wx.LI_HORIZONTAL)
        sizer_crosstalk.Add(line, 0, wx.EXPAND | wx.ALL, 5)

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

        # prod_al = self.algorithm_entry_li[2].GetSelection()
        prod_al = 0
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
            vals = [e.GetSelection() for e in cross_entries[:2]]
            if vals[0] and vals[1]:
                ch1 = self.crosstalk_choice_li[vals[0] - 1]
                ch2 = self.crosstalk_choice_li[vals[1] - 1]
                drfu = float(cross_entries[2].GetValue())
                ct = float(cross_entries[3].GetValue())
                crosstalk_val_li.append([ch1, ch2, drfu, ct])
        return crosstalk_val_li
