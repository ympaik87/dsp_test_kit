import wx
from subs.dev_panel import PanelDev
from dsp.dsp_raw_plot import DspRawPlot
from subs.raw_data_table import RawDataTable


class PanelRaw(PanelDev):
    def __init__(self, parent):
        super().__init__(parent)
        self.sizer_dev.Detach(self.sizer_plot)
        self.sizer_dev.Detach(self.sizer_btm)

        self.sizer_data_dropdown.Clear(True)
        self._table = RawDataTable(self, self.dye_li)
        # self.get_baseline_choice()
        self.get_data_table()
        self.is_RV = False

        self.well_help_txt = wx.StaticText(
            self, wx.ID_ANY, f'x 10\N{SUPERSCRIPT THREE}', wx.DefaultPosition,
            wx.DefaultSize, 0)
        self.well_help_txt.Hide()
        self.sizer_well.Add(self.well_help_txt, 0, wx.ALIGN_RIGHT | wx.ALL |
                            wx.RESERVE_SPACE_EVEN_IF_HIDDEN, 5)

        self.sizer_raw = wx.BoxSizer(wx.VERTICAL)
        self.sizer_raw.Add(self.sizer_plot, 1, wx.EXPAND, 5)
        self.sizer_raw.Add(self.sizer_btm, 1, wx.EXPAND, 5)
        self.SetSizer(self.sizer_raw)
        self.Layout()
        self.sizer_raw.Fit(self)

    def get_baseline_choice(self):
        self.sizer_label = wx.BoxSizer(wx.HORIZONTAL)
        radiobox_choices = ['On', 'Off']
        self.radiobox = wx.RadioBox(self, wx.ID_ANY, 'Baseline On/Off',
                                    wx.DefaultPosition, wx.DefaultSize,
                                    radiobox_choices, 2, wx.RA_SPECIFY_COLS)
        self.radiobox.Bind(wx.EVT_RADIOBOX, self.on_radiobox)
        self.sizer_label.Add(self.radiobox, 0, wx.ALL, 5)
        self.sizer_data_dropdown.Add(
            self.sizer_label, 0, wx.ALIGN_CENTER | wx.ALL, 5)

    def on_radiobox(self, event):
        print('radio box selected >>> ', self.radiobox.GetSelection())
        if self.radiobox.GetSelection():
            print('baseline off')
        else:
            print('baseline on')

    def on_data_choice(self, event=None, is_refresh=False):
        if is_refresh:
            self.choice_select = self.choice_select_saved
        else:
            self.choice_select = self.choice.GetSelection()
            choice_label = self.choice.GetString(self.choice_select)
            if 'RV' in choice_label:
                self.is_RV = True
            else:
                self.is_RV = False
        table = self._table.set_table(
            self._raw.get_df_list(), self.choice_select)
        self.sizer_param.Clear()
        self.grid_param.SetTable(table, takeOwnership=True)
        self.grid_param.EnableEditing(False)
        self.grid_param.AutoSizeColumns()
        self.grid_param.AutoSizeRows()
        self.grid_param.SetRowLabelSize(120)
        self.sizer_param.Add(self.grid_param, 0, wx.ALL, 5)

        if len(self.selected_ch_li) == 1:
            self.display_well_single_ch(self.selected_ch_li[0][0],
                                        self.selected_ch_li[0][1],
                                        is_RV=self.is_RV)

    def on_channel_checks(self, e):
        super().on_channel_checks(e)
        if len(self.selected_ch_li) == 1:
            self.display_well_single_ch(self.selected_ch_li[0][0],
                                        self.selected_ch_li[0][1],
                                        is_RV=self.is_RV)

    def display_well_single_ch(self, temp, dye, is_RV=False):
        if is_RV:
            self.get_rv_well(temp, dye)
            self.well_help_txt.Show()
        else:
            self.get_epr_well(temp, dye)
            self.well_help_txt.Hide()

    def display_well_active(self, selected_ch=None):
        super().display_well_active(selected_ch)
        self.well_help_txt.Hide()

    def get_rv_well(self, temp, dye):
        rv_dict = self._raw.rv_dict_li[self.ind][temp][dye]
        for r in range(8):
            for c in range(12):
                well = self.row_index[r] + f'{c+1}'
                if well in self.well_li:
                    if well in rv_dict.keys():
                        rv = round(rv_dict[well]/1000, 4)
                        if 1 < rv < 2:
                            x = 255 - ((10*(rv-1))//2)*50
                        elif rv >= 2:
                            x = 0
                        else:
                            x = 255
                    else:
                        x = 0
                    color = wx.Colour(x, 255, x)
                else:
                    color = wx.WHITE
                    rv = ''
                self.grid_well.SetCellValue(r, c, str(rv))
                self.grid_well.SetCellBackgroundColour(r, c, color)

    def get_epr_well(self, temp, dye):
        epr_df = self._raw.epr_df_li[self.ind]
        label_df = self._raw.label_dict_li[self.ind][dye]
        x_end = 255
        x_start = 100
        step_num = 4
        x_range = range(x_start, x_end, int((x_end-x_start)/step_num))
        for r in range(8):
            for c in range(12):
                well = self.row_index[r] + f'{c+1}'
                if well in self.well_li:
                    if well in epr_df.index:
                        epr = epr_df[dye][well]
                        if 1 < epr < 2:
                            step = int((10*(epr-1))//(10/step_num))
                            x = x_range[step]
                        elif epr >= 2:
                            x = x_start
                        else:
                            x = x_end
                    else:
                        epr = 0

                    if label_df['High'][well] == 'POS':
                        if label_df['Low'][well] == 'POS':
                            color = wx.Colour(x, x, 255)
                        elif label_df['Low'][well] == 'NEG':
                            color = wx.Colour(255, x, x)
                        else:
                            color = wx.WHITE
                    else:
                        color = wx.WHITE
                else:
                    epr = ''
                    color = wx.WHITE
                self.grid_well.SetCellValue(r, c, str(epr))
                self.grid_well.SetCellBackgroundColour(r, c, color)

    def activate_panel(self, dsp_res_li, melt_dict, raw_res, is_refresh=False):
        if is_refresh:
            self.well_selected_saved = self.well_selected
            self.choice_select_saved = self.choice_select
            self.selected_ch_li_saved = self.selected_ch_li

        self._raw = self.GetParent().GetParent()._raw
        self.ind = self.GetParent().GetParent().ind
        self.result_dict = raw_res
        self.parameters = dsp_res_li[0]
        self.dsp_result_dict = dsp_res_li[1]
        self.pc_check_list = dsp_res_li[2]
        self.nc_check_list = dsp_res_li[3]
        self.data_raw_dic = dsp_res_li[4]
        self.well_li = dsp_res_li[5]
        self.is_active = True
        self._plot = DspRawPlot(self.parameters, self.result_dict,
                                self.pc_check_list, self.nc_check_list,
                                self.data_raw_dic, self.well_li, melt_dict)
        self.checkbox_enable(is_refresh=is_refresh)
        self.on_data_choice(is_refresh=is_refresh)

        if is_refresh:
            if len(self.selected_ch_li) == 1:
                self.display_well_single_ch(self.selected_ch_li[0][0],
                                            self.selected_ch_li[0][1])
            elif len(self.selected_ch_li) > 1:
                self.display_well_active(selected_ch=self.selected_ch_li)
            self.is_RV = False
            self.init_plot(is_refresh)
        else:
            self.display_well_active()
        self.sizer_raw.Fit(self)
        print('Raw ready!')
