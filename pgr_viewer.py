import pathlib
import time
import pandas as pd
import wx
import wx.adv
from dsp.call_dsp import CallDsp
from dsp.save_plots import SavePlotTread, EVT_RESULT
from subs.dev_panel import PanelDev
from dsp.save_data import save_data_fn


class PgrvFrame(wx.Frame):
    def __init__(self, status_bar):
        wx.Frame.__init__(self, None, id=wx.ID_ANY,
                          pos=wx.DefaultPosition,
                          size=wx.DefaultSize,
                          style=wx.DEFAULT_FRAME_STYLE | wx.TAB_TRAVERSAL)
        self.SetSizeHints(wx.DefaultSize, wx.DefaultSize)
        self.initial_title = "PGR Manager"
        self.SetTitle(self.initial_title)
        self.menubar = wx.MenuBar(0)
        self.ind = 0
        self.is_dev = False

        self.menu_export = wx.Menu()
        menu_save_data = wx.MenuItem(
            self.menu_export, wx.ID_ANY, u"Save data sheet", wx.EmptyString,
            wx.ITEM_NORMAL)
        self.Bind(wx.EVT_MENU, self.on_save_data, menu_save_data)
        self.menu_export.Append(menu_save_data)
        menu_save_sigmoid = wx.MenuItem(
            self.menu_export, wx.ID_ANY, u"Save sigmoid fitting plot",
            wx.EmptyString, wx.ITEM_NORMAL)
        self.Bind(wx.EVT_MENU, self.on_save_sigmoid, menu_save_sigmoid)
        self.menu_export.Append(menu_save_sigmoid)
        menu_save_baseline = wx.MenuItem(
            self.menu_export, wx.ID_ANY, u"Save baseline fitting plot",
            wx.EmptyString, wx.ITEM_NORMAL)
        self.Bind(wx.EVT_MENU, self.on_save_baseline, menu_save_baseline)
        self.menu_export.Append(menu_save_baseline)
        self.menubar.Append(self.menu_export, u"Export DSP Result")

        self.SetMenuBar(self.menubar)

        self.status_bar = status_bar

        self.sizer_pgrv = wx.BoxSizer(wx.VERTICAL)

        self.sizer_top = wx.BoxSizer(wx.VERTICAL)
        self.file_choices_li = [u"File1", u"File2", u"File3", u"File4"]
        self.choice_box = wx.ListBox(
            self, wx.ID_ANY, wx.DefaultPosition, wx.Size(-1, 50),
            self.file_choices_li, 0)
        self.sizer_top.Add(self.choice_box, 0, wx.ALL | wx.EXPAND, 0)
        self.sizer_pgrv.Add(self.sizer_top, 1, wx.EXPAND, 0)

        sizer_nb = wx.BoxSizer(wx.VERTICAL)
        self.notebook = wx.Notebook(
            self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, 0)
        self.panel_mudt = PanelDev(self.notebook)
        self.notebook.AddPage(self.panel_mudt, 'DSP', False)
        sizer_nb.Add(self.notebook, 1, wx.EXPAND, 5)
        self.sizer_pgrv.Add(sizer_nb, 1, wx.EXPAND, 5)

        self.SetSizer(self.sizer_pgrv)
        self.Layout()
        self.sizer_pgrv.Fit(self)
        self.Centre(wx.BOTH)

        EVT_RESULT(self, self.update_statusbar)

    def get_current_dsp(self):
        filepath = self.filepath_li[self.ind]
        _dsp, melt_dict = self._dsp_li[self.ind]
        dsp_res_li = _dsp.get_dsp_result()
        return filepath, dsp_res_li, melt_dict

    def on_save_data(self, evnt=None):
        t = time.time()
        self.status_bar.SetStatusText('Saving datasheets...')
        fpath, res_li, melt = self.get_current_dsp()
        save_data_fn(
            fpath, res_li[0], res_li[1], self.version_info, self.is_dev)
        self.status_bar.SetStatusText('Finish saving datasheets in ' +
                                      str(round(time.time() - t, 1)) + ' secs')

    def call_save_plot(self, is_sigmoid):
        fpath, res_li, melt = self.get_current_dsp()
        self.background = SavePlotTread(fpath, res_li, melt, self.version_info,
                                        self, is_sigmoid)
        self.background.start()

    def on_save_sigmoid(self, evnt=None, is_sigmoid=True):
        self.status_bar.SetStatusText('Saving plots...')
        self.call_save_plot(is_sigmoid)

    def update_statusbar(self, msg):
        txt = msg.data
        if isinstance(txt, int) or isinstance(txt, float):
            self.status_bar.SetStatusText(f'Saving plots...{txt}%')
        else:
            self.status_bar.SetStatusText(f'{txt}')

    def on_save_baseline(self, evnt):
        self.on_save_sigmoid(evnt=evnt, is_sigmoid=False)

    def activate(self, is_refresh=False):
        self.choice_box.SetSelection(self.ind)
        _dsp, melt_dict = self._dsp_li[self.ind]
        dsp_res_li = _dsp.get_dsp_result()
        self.panel_mudt.activate_panel(dsp_res_li, melt_dict, is_refresh)
        if is_refresh:
            self.panel_mudt.Refresh()
        self.SetSize(wx.Size(1110, 920))

    def set_title(self, title):
        self.SetTitle(title)

    def set_version_info(self, version_str):
        self.version_info = version_str

    def set_file_choices(self, path_input, dir=False):
        if dir:
            self.filepath_li = sorted(
                path_input.glob('*Quantitation Amplification*.xlsx'))
            self.file_choices_li = [f.name for f in self.filepath_li]
        else:
            self.filepath_li = [path_input]
            self.file_choices_li = [path_input.name]

        self.sizer_top.Clear(delete_windows=True)
        self.choice_box = wx.ListBox(
            self, wx.ID_ANY, wx.DefaultPosition, wx.Size(-1, 50),
            self.file_choices_li, 0)
        self.sizer_top.Add(self.choice_box, 0, wx.ALL | wx.EXPAND, 5)
        self.Bind(wx.EVT_LISTBOX, self.on_file_choice)
        self.Layout()

    def on_file_choice(self, evt):
        self.ind = self.choice_box.GetSelection()
        print('selected file >>> ', self.choice_box.GetString(self.ind))
        self.set_title(self.choice_box.GetString(self.ind))
        self.activate(is_refresh=True)

    def get_quant_file_pair(self, fpath):
        filename = fpath.name
        experiment_path = fpath.parents[1]
        file_pair_li = [
            x / filename for x in pathlib.Path(experiment_path).iterdir()
            if x.is_dir() and 'QuantStep' in x.name
        ]
        melt_peak_file = fpath.parent/pathlib.PurePath(
            filename.split(' -  ')[0] +
            ' -  Melt Curve Derivative Results.xlsx')
        if pathlib.Path(melt_peak_file).exists():
            melt_dict = pd.read_excel(melt_peak_file, index_col=1,
                                      sheet_name=None)
        else:
            melt_dict = None
        return file_pair_li, melt_dict

    def call_dsp(self, params_df, algorithm_param_dict, param_status_bar,
                 label_choice):
        self._dsp_li = []
        total_num = len(self.filepath_li)
        param_status_bar.SetStatusText(f'Calculating DSP... 0/{total_num}')
        for ind in range(len(self.filepath_li)):
            path_in = self.filepath_li[ind]
            file_pair_li, melt_dict = self.get_quant_file_pair(path_in)
            _dsp = CallDsp(file_pair_li, params_df, algorithm_param_dict)
            self._dsp_li.append((_dsp, melt_dict))
            param_status_bar.SetStatusText(
                f'Calculating DSP... {ind}/{total_num}')


if __name__ == "__main__":
    import wx.lib.inspection
    app = wx.App()
    frame = PgrvFrame()
    frame.Show(True)
    wx.lib.inspection.InspectionTool().Show()
    app.MainLoop()
