import time
import wx
import wx.grid
from subs.figcanvas import DspFigCanvas
from subs.param_table_grid import ParamGrid
from dsp.dsp_coder_plot import DspViewerPlot, plot_init_empty
from subs.data_table import DspDataTable


class PanelDev(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent=parent, id=wx.ID_ANY,
                          pos=wx.DefaultPosition,
                          size=wx.DefaultSize, style=wx.TAB_TRAVERSAL)
        self.status_bar = parent.GetParent().status_bar
        self.is_active = False
        self.dye_color = {
            'FAM': (0, 64, 128),
            'HEX': (0, 64, 0),
            'Cal Red 610': (255, 0, 128),
            'Quasar 670': (128, 64, 64),
            'Quasar 705': (128, 0, 0)
        }
        self.dye_li = ['FAM', 'HEX', 'Cal Red 610', 'Quasar 670', 'Quasar 705']
        self.temp_li = ['Low Temp', 'High Temp']
        self.well_selected = []
        self.cell_color_dict = {}
        self.checkbox_li = []
        self.is_ctrl = False
        self._table = DspDataTable(self, self.dye_li)
        self.sizer_dev = wx.BoxSizer(wx.VERTICAL)

        self.sizer_plot = wx.BoxSizer()
        figure = plot_init_empty()
        self.canvas = DspFigCanvas(self, -1, figure)
        self.sizer_plot.Add(self.canvas, 1, wx.TOP | wx.LEFT | wx.EXPAND)
        self.sizer_dev.Add(self.sizer_plot, 1, wx.EXPAND, 5)

        self.sizer_btm = wx.FlexGridSizer(0, 2, 0, 0)
        self.sizer_btm.SetFlexibleDirection(wx.BOTH)
        self.sizer_btm.SetNonFlexibleGrowMode(wx.FLEX_GROWMODE_SPECIFIED)

        sizer_checkbar = wx.BoxSizer(wx.VERTICAL)
        for temp in ['Low ', 'High']:
            sizer = wx.BoxSizer()
            lbl = wx.StaticText(
                self, wx.ID_ANY, temp, wx.DefaultPosition, wx.DefaultSize, 0)
            lbl.Wrap(-1)
            sizer.Add(lbl, 0, wx.ALL, 5)
            li = []
            cb_li = []
            for dye in self.dye_li:
                checkbox = wx.CheckBox(self, wx.ID_ANY, dye,
                                       wx.DefaultPosition, wx.DefaultSize, 0)
                checkbox.Enable(False)
                li.append((checkbox, 0, wx.ALL, 5))
                cb_li.append(checkbox)
            sizer.AddMany(li)
            self.checkbox_li.append(cb_li)
            sizer_checkbar.Add(sizer, 1, wx.EXPAND, 5)
        self.Bind(wx.EVT_CHECKBOX, self.on_channel_checks)
        self.sizer_btm.Add(sizer_checkbar, 1, wx.EXPAND, 5)

        self.sizer_data_dropdown = wx.BoxSizer(wx.HORIZONTAL)
        self.get_data_table()
        self.sizer_btm.Add(self.sizer_data_dropdown, 1, wx.EXPAND, 5)

        self.sizer_well = wx.BoxSizer(wx.VERTICAL)
        self.make_grid_well()
        self.sizer_well.Add(self.grid_well, 0, wx.ALL, 5)
        self.sizer_btm.Add(self.sizer_well, 1, wx.EXPAND, 5)

        self.sizer_param = wx.BoxSizer(wx.VERTICAL)
        self.grid_param = ParamGrid(self)
        self.sizer_param.Add(self.grid_param, 0, wx.ALL, 5)

        self.sizer_btm.Add(self.sizer_param, 1, wx.EXPAND, 5)
        self.sizer_dev.Add(self.sizer_btm, 1, wx.EXPAND, 5)
        self.SetSizer(self.sizer_dev)
        self.Layout()
        self.sizer_dev.Fit(self)

    def get_data_table(self):
        label_data, self.choice = self._table.data_selection()
        self.choice.Bind(wx.EVT_CHOICE, self.on_data_choice)
        self.choice_select = 1
        self.sizer_data_dropdown.Add(
            label_data, 0, wx.ALIGN_CENTER | wx.ALL, 5)
        self.sizer_data_dropdown.Add(
            self.choice, 0, wx.ALIGN_CENTER | wx.ALL, 5)

    def make_grid_well(self):
        self.grid_well = wx.grid.Grid(
            self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, 0)
        self.grid_well.CreateGrid(8, 12)
        self.grid_well.EnableEditing(False)
        self.grid_well.EnableGridLines(True)
        self.grid_well.EnableDragGridSize(False)
        self.grid_well.SetMargins(0, 0)

        self.grid_well.EnableDragColMove(False)
        self.grid_well.EnableDragColSize(False)
        self.grid_well.SetColLabelSize(30)
        for i in range(12):
            self.grid_well.SetColLabelValue(i, f'{i+1}')
            self.grid_well.SetColSize(i, 40)
        self.grid_well.SetColLabelAlignment(wx.ALIGN_CENTER, wx.ALIGN_CENTER)

        self.grid_well.AutoSizeRows()
        self.grid_well.EnableDragRowSize(False)
        self.grid_well.SetRowLabelSize(30)
        self.row_index = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']
        for i in range(8):
            self.grid_well.SetRowLabelValue(i, self.row_index[i])
        self.grid_well.SetRowLabelAlignment(wx.ALIGN_CENTER, wx.ALIGN_CENTER)

        self.grid_well.SetDefaultCellTextColour(
            wx.SystemSettings.GetColour(wx.SYS_COLOUR_INACTIVECAPTION))
        self.grid_well.SetDefaultCellFont(
            wx.Font(wx.NORMAL_FONT.GetPointSize(), wx.FONTFAMILY_DEFAULT,
                    wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL, False,
                    "@Arial Unicode MS"))
        self.grid_well.SetDefaultCellAlignment(wx.ALIGN_CENTER,
                                               wx.ALIGN_CENTER)
        self.grid_well.Bind(wx.grid.EVT_GRID_RANGE_SELECT, self.on_well_drag)
        # self.grid_well.Bind(wx.grid.EVT_GRID_SELECT_CELL, self.on_well_select)
        self.grid_well.Bind(wx.grid.EVT_GRID_CELL_LEFT_CLICK, self.on_well_left_click)
        # self.grid_well.Bind(wx.grid.EVT_GRID_CELL_LEFT_CLICK, self.on_well_lb)

    def on_data_choice(self, event=None, is_refresh=False):
        if is_refresh:
            self.choice_select = self.choice_select_saved
        else:
            self.choice_select = self.choice.GetSelection() + 1
        table = self._table.set_table(self.result_dict, self.choice_select)
        self.sizer_param.Clear()
        self.grid_param.SetTable(table, takeOwnership=True)
        self.grid_param.EnableEditing(False)
        self.grid_param.AutoSizeColumns()
        self.grid_param.AutoSizeRows()
        self.grid_param.SetRowLabelSize(30)
        self.grid_param.SetColLabelSize(30)
        self.sizer_param.Add(self.grid_param, 0, wx.ALL, 5)

    def on_well_left_click(self, event):
        row = event.GetRow()
        col = event.GetCol()
        print('row', row, 'col', col)
        well = self.row_index[row] + str(range(12)[col] + 1)
        if event.ShiftDown():
            prev_well = self.well_selected[-1]
            prev_row = self.row_index.index(prev_well[0])
            prev_col = int(prev_well[1:]) - 1
            top_row = max(prev_row, row)
            btm_row = min(prev_row, row)
            right_col = max(prev_col, col)
            left_col = min(prev_col, col)
            self.grid_well.SelectBlock(top_row, left_col, btm_row, right_col)
        elif event.ControlDown():
            self.grid_well.ClearSelection()
            self.grid_well.SetGridCursor(row, col)
            if well in self.well_selected:
                self.well_selected.remove(well)
            else:
                self.well_selected.append(well)
            self.plot_well()
            print('ctrl+ >>>', self.well_selected)
        else:
            self.grid_well.ClearSelection()
            self.grid_well.SetGridCursor(row, col)
            self.well_selected = [well]
            if well in self.well_li:
                self.plot_well()
            else:
                wx.MessageBox(f'The well {well} is not in use', 'Warning',
                              wx.OK | wx.ICON_WARNING)
        print('one well clicked >>> ', self.well_selected)

    def on_well_lb(self, event):
        print('label clicked: ', event.GetRow(), event.GetCol())

    def on_well_drag(self, event):
        if self.grid_well.GetSelectionBlockTopLeft():
            top_left = self.grid_well.GetSelectionBlockTopLeft()[0]
            bottom_right = self.grid_well.GetSelectionBlockBottomRight()[0]
            self.get_selected_wells(top_left, bottom_right)
            self.plot_well()

    def plot_well(self, is_refresh=False):
        if is_refresh:
            self.status_bar.SetStatusText('Refreshed')
        else:
            self.status_bar.SetStatusText('Plotting...')
        t = time.time()
        self.get_checked()
        if len(self.selected_ch_li) > 1 or len(self.well_selected) > 1:
            self._plot.plot_multi_well(self.selected_ch_li, self.well_selected)
        elif len(self.selected_ch_li) == 1:
            dye = self.selected_ch_li[0][1]
            if len(self.well_selected) > 0:
                self._plot.plot_single_well(dye, self.well_selected[0])
            else:
                pass
        elif is_refresh:
            pass
        else:
            self.status_bar.SetStatusText('None of channels is selected')
            return
        self.sizer_plot.Clear()
        self.canvas.Destroy()
        self.canvas = DspFigCanvas(self, -1, self._plot.fig, self._plot)
        self.canvas.draw()
        self.sizer_plot.Add(self.canvas, 1, wx.TOP | wx.LEFT | wx.EXPAND)
        self.status_bar.SetStatusText(
            'Plotted in ' + str(round(time.time() - t, 1)) + ' secs')

    def get_selected_wells(self, top_left, bottom_right):
        self.cells_li = []
        rows_start = top_left[0]
        rows_end = bottom_right[0]
        cols_start = top_left[1]
        cols_end = bottom_right[1]

        rows = range(rows_start, rows_end + 1)
        cols = range(cols_start, cols_end + 1)

        self.cells_li.extend([(row, col) for row in rows for col in cols])
        print("You selected the following cells: ", self.cells_li)
        self.well_selected = [self.row_index[row] + str(range(12)[col] + 1)
                              for (row, col) in self.cells_li]
        print("You selected the following wells: ", self.well_selected)

    def get_checked(self):
        self.selected_ch_li = []
        for cb_li in self.checkbox_li:
            for c in cb_li:
                if c.GetValue():
                    temp_idx = self.checkbox_li.index(cb_li)
                    dye_idx = cb_li.index(c)
                    self.selected_ch_li.append(
                        [self.temp_li[temp_idx], self.dye_li[dye_idx]])
        print('get_checked >>> ', self.selected_ch_li)

    def on_channel_checks(self, e):
        cb = e.GetEventObject()
        print(cb.GetLabel(), ' is clicked', cb.GetValue())
        self.get_checked()
        if len(self.selected_ch_li) == 1:
            self.display_well_single_ch(
                self.selected_ch_li[0][0], self.selected_ch_li[0][1])
        elif len(self.selected_ch_li) > 1:
            self.display_well_active(selected_ch=self.selected_ch_li)
        else:
            self.display_well_active()

        if self.well_selected:
            self.plot_well()

    def checkbox_enable(self, is_refresh=False):
        used_temp = self.parameters['used_temp']
        for temp in used_temp.keys():
            if 'Low' in temp:
                i = 0
            else:
                i = 1
            for dye in used_temp[temp].keys():
                j = self.dye_li.index(dye)
                cb = self.checkbox_li[i][j]
                if used_temp[temp][dye]:
                    cb.Enable(True)
                    if is_refresh and [temp, dye] in self.selected_ch_li_saved:
                        cb.SetValue(True)
                else:
                    cb.SetValue(False)
                    cb.Enable(False)
                if is_refresh:
                    cb.Update()
        self.get_checked()

    def display_well_active(self, selected_ch=None):
        self.grid_well.SetDefaultCellTextColour(
            wx.SystemSettings.GetColour(wx.SYS_COLOUR_BTNTEXT))
        for r in range(8):
            for c in range(12):
                well = self.row_index[r] + f'{c+1}'
                if well in self.well_li:
                    self.grid_well.SetCellValue(r, c, well)
                if selected_ch is not None and well in self.well_li:
                    res_li = []
                    for ch in selected_ch:
                        temp = ch[0]
                        dye = ch[1]
                        if well in\
                                self.result_dict['result'][temp][dye].keys():
                            res_li.append(self.result_dict['result'][temp]
                                          [dye][well] <= 0)
                    if any(res_li):
                        color = wx.RED
                    else:
                        color = wx.WHITE
                elif well not in self.well_li:
                    color = wx.WHITE
                else:
                    color = wx.WHITE
                self.grid_well.SetCellBackgroundColour(r, c, color)
        # self.grid_well.Update()

    def display_well_single_ch(self, temp, dye):
        for r in range(8):
            for c in range(12):
                well = self.row_index[r] + f'{c+1}'
                if well in self.well_li:
                    if well in self.result_dict[
                            'Ct_array_final'][temp][dye].keys():
                        ct = self.result_dict[
                            'Ct_array_final'][temp][dye][well]
                        if not isinstance(ct, str):
                            ct = round(ct, 2)
                    else:
                        ct = 'Neg'
                    self.grid_well.SetCellValue(r, c, str(ct))
                if well in self.result_dict['result'][temp][dye].keys() and\
                        well in self.well_li:
                    result = self.result_dict['result'][temp][dye][well]
                    if result <= 0:
                        if not isinstance(ct, str):
                            gb = int(50*(ct//10))
                            color = wx.Colour(255, gb, gb)
                        else:
                            color = wx.RED
                    else:
                        color = wx.WHITE
                elif well not in self.well_li:
                    color = wx.WHITE
                else:
                    color = wx.WHITE
                self.grid_well.SetCellBackgroundColour(r, c, color)

    def get_plot_obj(self, melt_dict):
        self._plot = DspViewerPlot(self.parameters, self.result_dict,
                                   self.pc_check_list, self.nc_check_list,
                                   self.data_raw_dic, self.well_li, melt_dict)

    def activate_panel(self, dsp_res_li, melt_dict, is_refresh=False):
        if is_refresh:
            self.well_selected_saved = self.well_selected
            self.choice_select_saved = self.choice_select
            self.selected_ch_li_saved = self.selected_ch_li

        self.parameters = dsp_res_li[0]
        self.result_dict = dsp_res_li[1]
        self.pc_check_list = dsp_res_li[2]
        self.nc_check_list = dsp_res_li[3]
        self.data_raw_dic = dsp_res_li[4]
        self.well_li = dsp_res_li[5]
        self.is_active = True
        self.get_plot_obj(melt_dict)
        self.checkbox_enable(is_refresh=is_refresh)
        self.on_data_choice(is_refresh=is_refresh)

        if is_refresh:
            if len(self.selected_ch_li) == 1:
                self.display_well_single_ch(self.selected_ch_li[0][0],
                                            self.selected_ch_li[0][1])
            elif len(self.selected_ch_li) > 1:
                self.display_well_active(selected_ch=self.selected_ch_li)
            self.init_plot(is_refresh)
        else:
            self.display_well_active()
        print('DSP ready!')

    def select_well(self, wells):
        if isinstance(wells, str):
            row = self.row_index.index(wells[0])
            col = int(wells[1:]) - 1
            self.grid_well.GoToCell(row, col)

    def init_plot(self, is_refresh):
        if len(self.well_selected) == 1:
            self.select_well(self.well_selected_saved[0])
        else:
            self.well_selected = self.well_selected_saved
            self.plot_well(is_refresh)
