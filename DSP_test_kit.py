import wx
import wx.xrc
import wx.grid
import pathlib
import time
import csv
import pandas as pd
import logging
from subs.data_table import DataTable
from subs.param_algorithm import ParamAlgorithmPanel
from dsp.dsp_parameters import get_init_parameters, import_parameters
from pgr_viewer import PgrvFrame


class FrameParam(wx.Frame):
    def __init__(self, parent=None):
        wx.Frame.__init__(self, parent, id=wx.ID_ANY, title=wx.EmptyString,
                          pos=wx.DefaultPosition, size=wx.Size(730, 530),
                          style=wx.DEFAULT_FRAME_STYLE | wx.TAB_TRAVERSAL)
        self.version = wx.VersionInfo(
            name='DSP test kit', major=1, minor=0, micro=0)
        self.dye_li = ['FAM', 'HEX', 'Cal Red 610', 'Quasar 670', 'Quasar 705']
        self.param_df = get_init_parameters(self.dye_li)
        self.filepath = None
        self.initial_title = 'DSP test kit'
        self.status_bar = self.CreateStatusBar(1, wx.STB_SIZEGRIP, wx.ID_ANY)
        self._pgrv = PgrvFrame(self.status_bar)
        self._pgrv.Show(False)
        self._pgrv.set_version_info(self.version.GetVersionString())

        self.SetSizeHints(wx.DefaultSize, wx.DefaultSize)
        self.SetTitle(self.initial_title)
        self.menubar = wx.MenuBar(0)
        menu = wx.Menu()
        menu_open = wx.MenuItem(
            menu, wx.ID_ANY, 'Open a file', wx.EmptyString, wx.ITEM_NORMAL)
        menu.Append(menu_open)
        self.Bind(wx.EVT_MENU, self.on_open, menu_open)
        menu.AppendSeparator()
        menu_exit = wx.MenuItem(
            menu, wx.ID_ANY, 'Exit', wx.EmptyString, wx.ITEM_NORMAL)
        menu.Append(menu_exit)
        self.menubar.Append(menu, "File")
        self.Bind(wx.EVT_MENU, self.on_quit, menu_exit)
        self.SetMenuBar(self.menubar)

        sizer_frame = wx.BoxSizer(wx.VERTICAL)
        panel_mother = wx.Panel(self, wx.ID_ANY, wx.DefaultPosition,
                                wx.DefaultSize, wx.TAB_TRAVERSAL)
        sizer_panel = wx.WrapSizer(wx.HORIZONTAL, wx.WRAPSIZER_DEFAULT_FLAGS)

        sizer_notebook = wx.BoxSizer(wx.VERTICAL)
        notebook = wx.Notebook(
            panel_mother, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, 0)

        nb_panel1 = wx.Panel(notebook, wx.ID_ANY, wx.DefaultPosition,
                             wx.DefaultSize, wx.TAB_TRAVERSAL)
        sizer_panel1 = wx.BoxSizer(wx.VERTICAL)
        sizer_bpn = wx.WrapSizer(wx.VERTICAL, wx.WRAPSIZER_DEFAULT_FLAGS)
        bpn_text = wx.StaticText(
            nb_panel1, wx.ID_ANY, 'BPN', wx.DefaultPosition, wx.DefaultSize, 0)
        bpn_text.Wrap(-1)
        sizer_bpn.Add(bpn_text, 0, wx.ALL, 5)

        sizer_bpn_cycle = wx.BoxSizer(wx.HORIZONTAL)
        cycle_text = wx.StaticText(nb_panel1, wx.ID_ANY, 'BPN Cycle',
                                   wx.DefaultPosition, wx.DefaultSize, 0)
        cycle_text.Wrap(-1)
        sizer_bpn_cycle.Add(cycle_text, 0, wx.ALIGN_CENTER | wx.ALL, 5)
        self.textctrl_start = wx.TextCtrl(
            nb_panel1, wx.ID_ANY, wx.EmptyString,
            wx.DefaultPosition, wx.DefaultSize, 0)
        start = self.param_df['start']['bpn_cycle']
        self.textctrl_start.SetValue(str(start))
        sizer_bpn_cycle.Add(self.textctrl_start, 0, wx.ALL, 5)

        self.textctrl_end = wx.TextCtrl(nb_panel1, wx.ID_ANY, wx.EmptyString,
                                        wx.DefaultPosition, wx.DefaultSize, 0)
        end = self.param_df['end']['bpn_cycle']
        self.textctrl_end.SetValue(str(end))
        sizer_bpn_cycle.Add(self.textctrl_end, 0, wx.ALL, 5)
        sizer_bpn.Add(sizer_bpn_cycle, 1, wx.EXPAND, 5)

        self.bpn_checkbox = wx.CheckBox(nb_panel1, wx.ID_ANY, 'BPN switch on',
                                        wx.DefaultPosition, wx.DefaultSize, 0)
        sizer_bpn_cycle.Add(self.bpn_checkbox, 0, wx.ALIGN_CENTER | wx.ALL, 5)

        self.bpn_grid = wx.grid.Grid(
            nb_panel1, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, 0)
        self.bpn_table = self.get_bpnrv()
        self.bpn_grid.SetTable(self.bpn_table, takeOwnership=True)
        sizer_bpn.Add(self.bpn_grid, 0, wx.ALL, 5)
        sizer_panel1.Add(sizer_bpn, 1, wx.EXPAND, 5)

        sizer_common = wx.WrapSizer(wx.VERTICAL, wx.WRAPSIZER_DEFAULT_FLAGS)
        txt_common = wx.StaticText(nb_panel1, wx.ID_ANY, 'Common',
                                   wx.DefaultPosition, wx.DefaultSize, 0)
        txt_common.Wrap(-1)
        sizer_common.Add(txt_common, 0, wx.ALL, 5)
        self.common_grid = wx.grid.Grid(
            nb_panel1, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, 0)
        self.common_table = self.get_common()
        self.common_grid.SetTable(self.common_table, takeOwnership=True)
        sizer_common.Add(self.common_grid, 0, wx.ALL, 5)
        sizer_panel1.Add(sizer_common)

        nb_panel1.SetSizer(sizer_panel1)
        nb_panel1.Layout()
        sizer_panel1.Fit(nb_panel1)
        notebook.AddPage(nb_panel1, 'Common Parameters', True)

        nb_panel2 = wx.Panel(notebook, wx.ID_ANY, wx.DefaultPosition,
                             wx.DefaultSize, wx.TAB_TRAVERSAL)
        sizer_panel2 = wx.WrapSizer(wx.VERTICAL, wx.WRAPSIZER_DEFAULT_FLAGS)
        text = wx.StaticText(nb_panel2, wx.ID_ANY, 'Sample',
                             wx.DefaultPosition, wx.DefaultSize, 0)
        text.Wrap(-1)
        sizer_panel2.Add(text, 0, wx.ALL, 5)
        self.sample_grid = wx.grid.Grid(
            nb_panel2, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, 0)
        self.sample_table = self.get_sample()
        self.sample_grid.SetTable(self.sample_table, takeOwnership=True)
        sizer_panel2.Add(self.sample_grid, 0, wx.ALL, 5)

        nb_panel2.SetSizer(sizer_panel2)
        nb_panel2.Layout()
        sizer_panel2.Fit(nb_panel2)
        notebook.AddPage(nb_panel2, 'Sample', False)

        nb_panel3 = wx.Panel(notebook, wx.ID_ANY, wx.DefaultPosition,
                             wx.DefaultSize, wx.TAB_TRAVERSAL)
        sizer_panel3 = wx.WrapSizer(wx.VERTICAL, wx.WRAPSIZER_DEFAULT_FLAGS)
        text = wx.StaticText(nb_panel3, wx.ID_ANY, 'Positive Control',
                             wx.DefaultPosition, wx.DefaultSize, 0)
        text.Wrap(-1)
        sizer_panel3.Add(text, 0, wx.ALL, 5)
        self.pc_grid = wx.grid.Grid(
            nb_panel3, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, 0)
        self.pc_table = self.get_pc()
        self.pc_grid.SetTable(self.pc_table, takeOwnership=True)
        sizer_panel3.Add(self.pc_grid, 0, wx.ALL, 5)

        nb_panel3.SetSizer(sizer_panel3)
        nb_panel3.Layout()
        sizer_panel3.Fit(nb_panel3)
        notebook.AddPage(nb_panel3, 'PC', False)

        self.nb_panel4 = ParamAlgorithmPanel(notebook, self.dye_li)
        notebook.AddPage(self.nb_panel4, 'Crosstalk', False)

        sizer_notebook.Add(notebook, 1, 0, 0)
        sizer_panel.Add(sizer_notebook, 1, 0, 0)

        sizer_button = wx.BoxSizer(wx.VERTICAL)
        button_apply = wx.Button(panel_mother, wx.ID_ANY, "Apply",
                                 wx.DefaultPosition, wx.DefaultSize, 0)
        self.Bind(wx.EVT_BUTTON, self.on_apply, button_apply)
        sizer_button.Add(button_apply, 0, wx.ALL, 5)
        sizer_panel.Add(sizer_button, 1, wx.EXPAND, 5)

        panel_mother.SetSizer(sizer_panel)
        panel_mother.Layout()
        sizer_panel.Fit(panel_mother)
        sizer_frame.Add(panel_mother, 1, wx.EXPAND | wx.ALL, 0)

        self.SetSizer(sizer_frame)
        self.Layout()
        self.Centre(wx.BOTH)

    def on_import(self, event):
        with wx.FileDialog(
            self, "Open a Parameter file",
            wildcard="Excel Files (.xlsx)|*.xlsx",
                style=wx.FD_OPEN | wx.FD_FILE_MUST_EXIST) as fileDialog:

            if fileDialog.ShowModal() == wx.ID_CANCEL:
                return     # the user changed their mind

            # Proceed loading the file chosen by the user
            path = fileDialog.GetPath()
            print(path)
            logging.info('Parameter file imported >>> ', path)
        self.status_bar.SetStatusText('Parameters are imported!')

        param_df_dict = import_parameters(path, self.bpn_index_display,
                                          self.common_index_display,
                                          self.sample_index_display,
                                          self.pc_index_display)
        self.bpn_table = DataTable(param_df_dict['bpnrv_df'])
        self.bpn_grid.SetTable(self.bpn_table, takeOwnership=True)
        self.bpn_grid.ForceRefresh()
        self.common_table = DataTable(param_df_dict['common_df'])
        self.common_grid.SetTable(self.common_table, takeOwnership=True)
        self.common_grid.ForceRefresh()
        self.sample_table = DataTable(param_df_dict['sample_df'])
        self.sample_grid.SetTable(self.sample_table, takeOwnership=True)
        self.sample_grid.ForceRefresh()
        self.pc_table = DataTable(param_df_dict['pc_df'])
        self.pc_grid.SetTable(self.pc_table, takeOwnership=True)
        self.pc_grid.ForceRefresh()
        start = param_df_dict['bpn_cycle'][0]
        end = param_df_dict['bpn_cycle'][1]
        self.textctrl_start.SetValue(str(start))
        self.textctrl_end.SetValue(str(end))
        if start and end and start < end:
            self.bpn_checkbox.SetValue(True)
            self.bpn_checkbox.Update()

    def on_open_dir(self, event):
        self.filepath = None
        dlg = wx.DirDialog(self, "Choose input directory", "",
                           wx.DD_DEFAULT_STYLE | wx.DD_DIR_MUST_EXIST)
        if dlg.ShowModal() == wx.ID_OK:
            print('You selected: %s\n' % dlg.GetPath())
            self.dir_path = pathlib.Path(dlg.GetPath())
            self.title = self.initial_title + ' - ' + self.dir_path.parent.name
            self.SetTitle(self.title)
            self.status_bar.SetStatusText('A directory is opened!')
        dlg.Destroy()

    def get_bpnrv(self):
        self.bpn_index = ['bpn_rv1', 'bpn_rv2']
        bpn_df = self.param_df.loc[self.bpn_index][self.dye_li]
        self.bpn_index_display = [
            t.upper().replace('_', ' ').replace('1', ' (L)')
            .replace('2', ' (H)') for t in self.bpn_index]
        bpn_df.index = self.bpn_index_display
        return DataTable(bpn_df)

    def get_common(self):
        self.common_index = ['used_temp1', 'used_temp2', 'cut_off1',
                             'cut_off2', 'cut_off_nc1', 'cut_off_nc2', 'pmc']
        common_df = self.param_df.loc[self.common_index][self.dye_li]
        self.common_index_display = [
            t.replace('_', ' ').replace('1', ' (L)').replace('2',  ' (H)')
            for t in self.common_index]
        common_df.index = self.common_index_display
        return DataTable(common_df)

    def get_sample(self):
        self.sample_index = ['sfc', 'mfc', 'cr', 'drfu1', 'drfu2', 'thrd1',
                             'thrd2', 'rpc1', 'rpc2', 'rc1', 'rc2', 'dfm1',
                             'dfm2', 'dfc1', 'dfc2', 'ptp', 'drfu3']
        sample_df = self.param_df.loc[self.sample_index][self.dye_li]
        index = [t.upper() for t in self.sample_index]
        index_temp = [t.replace('1', ' (L)').replace('2', ' (H)')
                      for t in index[:-2]]
        self.sample_index_display = index_temp + ['DRFU2', 'DRFU3']
        sample_df.index = self.sample_index_display
        return DataTable(sample_df)

    def get_pc(self):
        self.pc_index = ['sfc_pc', 'mfc_pc', 'cr_pc', 'drfu1_pc', 'drfu2_pc',
                         'thrd1_pc', 'thrd2_pc', 'rpc1_pc', 'rpc2_pc',
                         'rc1_pc', 'rc2_pc', 'dfM1_pc', 'dfM2_pc', 'dfC1_pc',
                         'dfC2_pc']
        pc_df = self.param_df.loc[self.pc_index][self.dye_li]
        self.pc_index_display = [
            t.replace('_pc', '').replace('1', ' (L)').replace('2', ' (H)')
            .upper() for t in self.pc_index]
        pc_df.index = self.pc_index_display
        return DataTable(pc_df)

    def on_open(self, event):
        self.dir_path = None
        with wx.FileDialog(self, "Open Amplification file",
                           wildcard="Amplication files (.xlsx)|"
                           "*Quantitation Amplification*.xlsx| All files |*.*",
                           style=wx.FD_OPEN | wx.FD_FILE_MUST_EXIST
                           ) as fileDialog:

            if fileDialog.ShowModal() == wx.ID_CANCEL:
                return     # the user changed their mind

            # Proceed loading the file chosen by the user
            pathname = fileDialog.GetPath()
            self.filepath = pathlib.Path(pathname)
            print(self.filepath)
            logging.info('filepath >>> ' + pathname)
            self.title = self.initial_title + ' - ' +\
                self.filepath.name.split(' -  ')[0]
            self.SetTitle(self.title)
        self.status_bar.SetStatusText('file is opened!')

    def grid_to_df(self, grid, index):
        col = []
        for r in range(len(index)):
            row = []
            for c in range(5):
                row.append(grid.GetCellValue(r, c))
            col.append(row)
        df = pd.DataFrame(col, index=index, columns=self.dye_li)
        return df

    def get_params(self):
        bpn_df = self.grid_to_df(self.bpn_grid, self.bpn_index)
        common_df = self.grid_to_df(self.common_grid, self.common_index)
        sample_df = self.grid_to_df(self.sample_grid, self.sample_index)
        pc_df = self.grid_to_df(self.pc_grid, self.pc_index)
        bpn_cycle_df = pd.DataFrame(
            [[int(float(self.textctrl_start.GetValue())),
              int(float(self.textctrl_end.GetValue()))]],
            index=['bpn_cycle'], columns=['start', 'end'])
        params_df = pd.concat(
            [bpn_df, common_df, sample_df, pc_df, bpn_cycle_df], sort=False).T
        return params_df

    def get_ver_array(self):
        with open('ver_array.csv', newline='') as f:
            row = csv.reader(f, delimiter=',')
            row_li = []
            for i in row:
                row_li.append(i)
        return [int(i) for i in row_li[0]]

    def call_main_fn(self):
        if self.filepath:
            self._pgrv.set_file_choices(self.filepath)
        else:
            self._pgrv.set_file_choices(self.dir_path, dir=True)
        self.status_bar.SetStatusText('Calculating... ')

        t = time.time()
        params_df = self.get_params()
        algorithm_param_dict = self.nb_panel4.get_algorithm_dict()
        algorithm_param_dict['ds'] = 1
        algorithm_param_dict['is_dev'] = False
        algorithm_param_dict['ver_array'] = self.get_ver_array()
        algorithm_param_dict['BPN_switch'] = self.bpn_checkbox.GetValue()

        label_choice = 0

        self._pgrv.call_dsp(params_df, algorithm_param_dict,
                            self.status_bar, label_choice)
        self.status_bar.SetStatusText(
            'DSP Analysis is ready in ' + str(round(time.time() - t, 1)) +
            'secs')
        self._pgrv.activate()
        self._pgrv.on_save_data()
        self.status_bar.SetStatusText('Saving datasheets...')
        self._pgrv.on_save_sigmoid()
        self.status_bar.SetStatusText('Saving plots...')
        self._pgrv.on_save_sigmoid(is_sigmoid=False)

    def on_apply(self, e):
        if self.filepath or self.dir_path:
            try:
                self.call_main_fn()
            except Exception as e:
                wx.MessageBox('An error occured in DSP analysis', 'Error',
                              wx.OK | wx.ICON_ERROR)
                self.status_bar.SetStatusText('An error occured')
                print(e)
                logging.exception('  << Error in on_apply >>')
        else:
            wx.MessageBox(
                'A data file nor a directory has not been opened yet', 'Error',
                wx.OK | wx.ICON_ERROR)

    def on_quit(self, e):
        self.Close()


if __name__ == "__main__":
    app = wx.App()
    frame = FrameParam()
    frame.Show(True)
    app.MainLoop()
