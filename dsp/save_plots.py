import matplotlib.pyplot as plt
import pathlib
import datetime
import os
import io
import wx
import time
import xlsxwriter
import threading
# import multiprocessing
from dsp.save_data import save_param_info
from dsp.dsp_coder_plot import DspViewerPlot
import matplotlib
matplotlib.use('Agg')


EVT_RESULT_ID = wx.ID_ANY


def EVT_RESULT(win, func):
    """Define Result Event."""
    win.Connect(-1, -1, EVT_RESULT_ID, func)


class ResultEvent(wx.PyEvent):
    """Simple event to carry arbitrary result data."""

    def __init__(self, data):
        """Init Result Event."""
        wx.PyEvent.__init__(self)
        self.SetEventType(EVT_RESULT_ID)
        self.data = data


class DspPlotSave(DspViewerPlot):
    def __init__(self, parameters, result_dict, pc_li, nc_li, raw_data,
                 well_li, melt_dict):
        DspViewerPlot.__init__(self, parameters, result_dict, pc_li, nc_li,
                               raw_data, well_li, melt_dict)

    def plot_with_type(self, type, dye, well, temp=None):
        fig, ax = plt.subplots(1, 1, figsize=(3, 2.3))
        if type == 'sigmoid':
            self.plot_sigmoid(temp, dye, well, ax)
        elif type == 'baseline':
            self.plot_baseline(temp, dye, well, ax)
        elif type == 'raw':
            self.plot_raw(dye, well, ax)
        else:
            print('wrong type in saving plot')
        fig_data = io.BytesIO()
        fig.savefig(fig_data, bbox_inches='tight')
        plt.close(fig)
        return fig_data


class SavePlotTread(threading.Thread):
    def __init__(self, filepath, dsp_res_li, melt_dict, version_info, wxObj,
                 sigmoid=False):
        threading.Thread.__init__(self)
        self.wxObject = wxObj
        self.parameters = dsp_res_li[0]
        self.result_dict = dsp_res_li[1]
        self.pc_check_list = dsp_res_li[2]
        self.nc_check_list = dsp_res_li[3]
        self.raw_data = dsp_res_li[4]
        self.well_li = dsp_res_li[5]
        self.filepath = filepath
        self.version_info = version_info
        self.sigmoid = sigmoid
        self._plot_save = DspPlotSave(self.parameters, self.result_dict,
                                      self.pc_check_list, self.nc_check_list,
                                      self.raw_data, self.well_li, melt_dict)

    def run(self):
        t = time.time()
        position_x = {'1': 'A', '2': 'G', '3': 'M', '4': 'S', '5': 'Y',
                      '6': 'AE', '7': 'AK', '8': 'AQ', '9': 'AW',
                      '10': 'BC', '11': 'BI', '12': 'BO'}
        position_y = {'A': '1', 'B': '15', 'C': '29', 'D': '43',
                      'E': '57', 'F': '71', 'G': '85', 'H': '99'}
        step_num_total = 0
        for temp in self.raw_data.keys():
            step_num_total += len(self.raw_data[temp].keys())
        if not self.sigmoid:
            step_num_total += len(self.raw_data['High Temp'].keys())
        step_num_current = 0
        step_num = 100/step_num_total

        _fname = pathlib.PurePath(
            self.filepath.name.translate(str.maketrans('', '', '[]<>?|*')))
        inputf = self.filepath.parents[0]/_fname
        save_path = inputf.parents[1]
        if self.sigmoid:
            fname = 'fig_' + inputf.name.split(' -  ')[0] + inputf.suffix
        else:
            fname = 'raw_' + inputf.name.split(' -  ')[0] + inputf.suffix
        if os.path.exists(save_path/fname):
            name, ext = fname.split('.')
            fname = name + datetime.datetime.now().strftime(
                '_%Y%m%d_%H%M%S') + inputf.suffix
        fpath = save_path/fname
        with xlsxwriter.Workbook(fpath) as writer:
            save_param_info(writer, self.parameters, self.result_dict,
                            self.version_info)
            for temp in self.raw_data.keys():
                for dye in self.raw_data[temp].keys():
                    if self.parameters['used_temp'][temp][dye] != 1:
                        continue
                    sheet_name = dye + '_' + temp[0]
                    ws = writer.add_worksheet(sheet_name)
                    for well in self.raw_data[temp][dye].keys():
                        result = self.result_dict['result'][temp][dye][well]
                        if self.sigmoid and (result <= 0 or result == 4):
                            fig_data = self._plot_save.plot_with_type(
                                'sigmoid', dye, well, temp)
                        else:
                            fig_data = self._plot_save.plot_with_type(
                                'baseline', dye, well, temp)
                        fig_pos = position_x[well[1:]] + position_y[well[0]]
                        ws.insert_image(fig_pos, 'base_fig.png',
                                        {'image_data': fig_data})
                    step_num_current += step_num
                    progress = round(step_num_current/step_num_total, 2)
                    wx.PostEvent(self.wxObject, ResultEvent(progress))

            if not self.sigmoid:
                for dye in self.raw_data['High Temp'].keys():
                    sheet_name_raw = dye + '_raw'
                    ws_raw = writer.add_worksheet(sheet_name_raw)
                    for well in self.raw_data['High Temp'][dye].keys():
                        fig_data = self._plot_save.plot_with_type(
                            'raw', dye, well)
                        fig_pos = position_x[well[1:]] + position_y[well[0]]
                        ws_raw.insert_image(fig_pos, 'raw_fig.png',
                                            {'image_data': fig_data})
                    step_num_current += step_num
                    progress = round(step_num_current/step_num_total, 2)
                    wx.PostEvent(self.wxObject, ResultEvent(progress))
        msg = 'Finish saving plots in ' + str(round(time.time() - t, 1)) +\
            ' secs'
        wx.PostEvent(self.wxObject, ResultEvent(msg))
