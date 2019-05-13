import matplotlib.pyplot as plt
import numpy as np


def plot_init_empty():
    fig, axes = plt.subplots(2, 3, figsize=(10, 4.6))
    return fig


class DspViewerPlot:
    def __init__(self, params, result_dict, pc_check_list, nc_check_list,
                 raw_data, all_well_li, melt_dict):
        self.dye_color = {
            'FAM': (0, 64/255, 128/255),
            'HEX': (0, 64/255, 0),
            'Cal Red 610': (255/255, 0, 128/255),
            'Quasar 670': (128/255, 64/255, 64/255),
            'Quasar 705': (128/255, 0, 0),
            'grid': (240/255, 240/255, 240/255)
        }
        self.params = params
        self.temp_li = list(self.params['used_temp'].keys())
        self.result_dict = result_dict
        self.pc_check_list = pc_check_list
        self.nc_check_list = nc_check_list
        self.raw_data = raw_data
        self.all_well_li = all_well_li
        self.melt_dict = melt_dict
        self.crosstalk_dict = {}
        if self.params['crosstalk']:
            for parameter in self.params['crosstalk']:
                self.crosstalk_dict[parameter[1]] = float(parameter[3])
        self.plot_info = {'is_single': False, 'is_empty': False}
        self.fig = plot_init_empty()

    def plot_single_well(self, dye, well):
        plt.close(self.fig)
        self.plot_info['dye'] = dye
        self.plot_info['well'] = well
        self.plot_info['is_single'] = True
        if well not in self.all_well_li:
            self.plot_info['is_empty'] = True
            return plot_init_empty()
        self.fig, self.axes = plt.subplots(2, 3, figsize=(10, 4.6))
        col = 0
        for temp in self.temp_li:
            if self.params['used_temp'][temp][dye] != 1:
                continue
            self.result = self.result_dict['result'][temp][dye][well]
            self.plot_baseline(temp, dye, well, self.axes[0, col])
            if self.result == 4 or self.result <= 0:
                self.plot_sigmoid(temp, dye, well, self.axes[1, col])
            else:
                self.plot_baseline(temp, dye, well, self.axes[1, col])
            col += 1
        self.plot_raw(dye, well, self.axes[0, 2])
        self.plot_melt_peak(dye, well, self.axes[1, 2])
        self.fig.tight_layout()
        return self.fig

    def plot_multi_well(self, ch_li, well_li):
        plt.close(self.fig)
        if not isinstance(ch_li, list):
            ch_li = [ch_li]
        if not isinstance(well_li, list):
            well_li = [well_li]
        if len(well_li) > 1:
            is_multiple_well = True
        else:
            is_multiple_well = False
        self.plot_info['is_multiple_well'] = is_multiple_well
        self.plot_info['is_single'] = False
        self.plot_info['dye'] = ch_li
        self.plot_info['well'] = well_li
        self.fig, self.axes = plt.subplots(2, 3, figsize=(10, 4.6))
        for ch in ch_li:
            dye = ch[1]
            for well in well_li:
                if well not in self.all_well_li:
                    continue
                col = 0
                self.plot_melt_peak(
                    dye, well, self.axes[1, 2], is_multiple_well)
                for temp in self.temp_li:
                    self.result = self.result_dict[
                        'result'][temp][dye][well]
                    if self.result <= 0 and well in self.result_dict[
                            'DataProcess_array'][temp][dye].keys():
                        self.plot_sigmoid_multi(temp, dye, well,
                                                self.axes[1, col],
                                                is_multiple_well)
                    col += 1
        self.fig.tight_layout()
        return self.fig

    def _get_data(self, temp, dye, well):
        self.well = well
        self.data_process_num = self.result_dict[
            'data_process_num'][temp][dye][well]
        if self.data_process_num == 1:
            self.rd = self.raw_data[temp][dye][well].values
        else:
            self.rd = self.result_dict[
                'DataProcess_array'][temp][dye][well][1].values
        self.x = np.arange(len(self.rd)) + 1
        self.end_rfu = self.result_dict['end_rfu'][temp][dye][well]
        self.result = self.result_dict['result'][temp][dye][well]
        if well in self.result_dict['RD_diff_array'][temp][dye].keys():
            self.rd_diff = self.result_dict['RD_diff_array'][temp][dye][well]
            self.scd_fit = self.result_dict['scd_fit_array'][temp][dye][well]
            self.absd = self.result_dict['ABSD_array'][temp][dye][well]
            self.absd_orig = self.result_dict[
                'ABSD_orig_array'][temp][dye][well]
            self.f = self.result_dict['f_array'][temp][dye][well]
            self.f_new = self.result_dict['f_new_array'][temp][dye][well]
            if self.result == -2:
                self.shift = self.f_new[0]
            else:
                self.shift = self.f[0]
            self.r2 = self.result_dict['R2_array'][temp][dye][well]
            self.df = self.result_dict['df_array'][temp][dye][well]
            self.ct = self.result_dict['Ct_array_final'][temp][dye][well]
            if self.result == -2:
                self.a4 = np.absolute(self.result_dict[
                    'param_new_array'][temp][dye][well][3])
            else:
                self.a4 = np.absolute(self.result_dict[
                    'param_array'][temp][dye][well][3])
            self.r_p2 = self.result_dict['R_p2_array'][temp][dye][well]
            self.efc = self.result_dict['EFC_array'][temp][dye][well]
            self.lsr_val = self.result_dict['LSR_val_array'][temp][dye][well]
        else:
            self.r_p2 = 'N/A'
            self.r2 = 'N/A'
            self.efc = 'N/A'
            self.lsr_val = 'N/A'
            self.df = 'N/A'
            self.alpha_4 = 'N/A'
            self.ct = 'N/A'
            self.rd_diff = np.zeros(len(self.rd))
        crosstalk_key = dye + '_' + temp[0]
        if well in self.pc_check_list:
            self.thrd = self.params['Thrd_array_pc'][temp][dye]
            self.gp = '-PC'
        elif well in self.nc_check_list:
            self.thrd = self.params['Thrd_array'][temp][dye]
            self.gp = '-NC'
        elif crosstalk_key in self.crosstalk_dict.keys():
            self.thrd = self.crosstalk_dict[crosstalk_key] + self.shift
            self.gp = '-Crosstalk'
        else:
            self.thrd = self.params['Thrd_array'][temp][dye]
            self.gp = ''

    def _get_text(self, ax, coeff, text=None, text_content=None, sig_fig=5,
                  txt_num=5):
        self.bottom, top = ax.get_ylim()
        bottom_coeff = 1 - coeff

        if coeff == 0.90:
            well_no = self.well + self.gp
            return ax.text(txt_num,
                           coeff*top + bottom_coeff*self.bottom,
                           well_no + '(' + str(int(self.data_process_num)) +
                           ')')
        elif isinstance(text_content, str):
            return ax.text(txt_num,
                           coeff*top + bottom_coeff*self.bottom,
                           text + text_content)
        else:
            return ax.text(txt_num,
                           coeff*top + bottom_coeff*self.bottom,
                           text + str(np.round(text_content, sig_fig)))

    def plot_baseline(self, temp, dye, well, ax):
        self._get_data(temp, dye, well)
        if self.result in [0, -1, -2, 3, 4]:
            ax.plot(self.x, self.rd, 'y.', markersize=3)
            ax.plot(self.x, self.rd-self.rd_diff, 'k.', markersize=3)
            ax.plot(self.x, self.scd_fit, 'r')
            end_rfu_baseline = self.rd[-1] - self.scd_fit[-1]
        elif self.result == 1:
            ax.plot(self.x, self.rd, 'y.', markersize=3)
            ax.plot(self.x, self.rd-self.rd_diff, 'k.', markersize=3)
        elif self.result == 2:
            ax.plot(self.x, self.rd, 'y.', markersize=3)
            ax.plot(self.x, self.rd-self.rd_diff, 'k.', markersize=3)
            ax.plot(self.x, self.scd_fit, 'b')
        ax.set_title(temp+' Baseline')
        ax.set_xlabel('Cycles')
        ax.set_ylabel('RFU')
        ax.grid(True, color=self.dye_color['grid'])
        loc = 0.9
        self._get_text(ax, loc)
        loc = 0.8
        self._get_text(ax, loc, text=r'$R_p^2=$', text_content=self.r_p2)
        loc = 0.7
        if self.result in [0, -1, -2, 3, 4]:
            self._get_text(ax, loc, text='RFU diff=',
                           text_content=end_rfu_baseline)
            loc -= 0.1
        else:
            self._get_text(ax, loc, text='RFU diff=',
                           text_content=self.end_rfu)
            loc -= 0.1
        self._get_text(ax, loc, text='EFC=', text_content=self.efc)
        loc -= 0.1
        self._get_text(ax, loc, text='LSR=', text_content=self.lsr_val)

    def plot_sigmoid(self, temp, dye, well, ax):
        self._get_data(temp, dye, well)
        ax.plot(self.x, self.absd_orig+self.rd_diff-self.shift,
                'y.', markersize=3)
        ax.plot(self.x, self.absd_orig-self.shift, 'b.', markersize=3)
        ax.plot(self.x, self.absd-self.shift, 'k.', markersize=3)
        if self.result == 4:
            ax.plot(self.x, self.f-self.shift, 'b')
        elif self.result == -2:
            ax.plot(self.x, self.f-self.shift, 'g')
            ax.plot(self.x, self.f_new-self.shift, 'r')
        else:
            ax.plot(self.x, self.f-self.shift, 'r')
        ax.set_title(temp+' Sigmoid Fitting')
        ax.set_xlabel('Cycles')
        ax.set_ylabel('RFU')
        ax.grid(True, color=self.dye_color['grid'])
        loc = 0.9
        self._get_text(ax, loc)
        loc = 0.8
        self._get_text(ax, loc, text=r'$R^2=$', text_content=self.r2)
        loc = 0.7
        self._get_text(ax, loc, text='RFU=', text_content=self.end_rfu)
        loc = 0.6
        self._get_text(ax, loc, text='df=', text_content=self.df)
        loc = 0.5
        self._get_text(ax, loc, text=r'$\alpha_4=$', text_content=self.a4)
        if self.ct != 0 and 'N' not in str(self.ct):
            left, right = plt.xlim()
            ax.plot((left, self.ct), (self.thrd, self.thrd), 'c-')
            ax.plot((self.ct, self.ct), (self.bottom, self.thrd), 'c-')
            loc = 0.15
            self._get_text(ax, loc, text='Ct=', text_content=self.ct,
                           txt_num=30)

    def plot_sigmoid_multi(self, temp, dye, well, ax, is_multiple_well=False):
        self._get_data(temp, dye, well)
        if self.result == -2:
            ax.plot(self.x, self.f_new-self.shift, color=self.dye_color[dye])
        else:
            ax.plot(self.x, self.f-self.shift, color=self.dye_color[dye])
        # TODO: ct threshold if single channel selected
        if is_multiple_well:
            ax.set_title(f'{temp} Sigmoid Fitting Multiple')
        else:
            ax.set_title(f'{temp} Sigmoid Fitting {well}')
        ax.set_xlabel('Cycles')
        ax.set_ylabel('RFU')
        ax.grid(True, color=self.dye_color['grid'])

    def plot_raw(self, dye, well, ax):
        low = self.raw_data[self.temp_li[0]][dye][well]
        high = self.raw_data[self.temp_li[1]][dye][well]
        x = np.arange(len(low)) + 1
        used_temp_lo = self.params['used_temp'][self.temp_li[0]][dye]
        used_temp_high = self.params['used_temp'][self.temp_li[1]][dye]
        if used_temp_lo and used_temp_high:
            ax.plot(x, low, 'b')
            ax.plot(x, high, 'r')
        elif used_temp_lo:
            ax.plot(x, low, 'b')
        elif used_temp_high:
            ax.plot(x, high, 'r')
        ax.set_xlabel('Cycles')
        ax.set_ylabel('RFU')
        if well in self.pc_check_list:
            gp = '-PC'
        elif well in self.nc_check_list:
            gp = '-NC'
        else:
            gp = ''
        bottom, top = ax.get_ylim()
        well_no = well + gp
        ax.text(5, 0.9*top + 0.1*bottom, well_no)
        ax.set_title('Raw Graph')
        ax.grid(True, color=self.dye_color['grid'])

    def plot_melt_peak(self, dye, well, ax, is_multiple_well=False):
        if self.melt_dict is None:
            return
        melt_srs = self.melt_dict[dye][well]
        ax.plot(melt_srs, color=self.dye_color[dye], picker=5)
        ax.set_xlabel('Temperature (Celsius)')
        ax.set_ylabel('-d(RFU)/dT')
        if is_multiple_well:
            ax.set_title('Melt Peak Multiple')
        else:
            ax.set_title(f'Melt Peak {well}')
        ax.grid(True, color=self.dye_color['grid'])

    def get_subax_x(self, ax, temp, dye, well, y):
        if y == 1 and self.plot_info['is_single']:
            self.result = self.result_dict['result'][temp][dye][well]
            self.plot_baseline(temp, dye, well, ax)
        elif self.plot_info['is_single']:
            self.result = self.result_dict['result'][temp][dye][well]
            if self.result == 4 or self.result <= 0:
                self.plot_sigmoid(temp, dye, well, ax)
            else:
                self.plot_baseline(temp, dye, well, ax)
        else:
            for ch in dye:
                for w in well:
                    if w not in self.all_well_li:
                        continue
                    self.result = self.result_dict['result'][temp][ch[1]][w]
                    if self.result <= 0 and w in self.result_dict[
                            'DataProcess_array'][temp][ch[1]].keys():
                        self.plot_sigmoid_multi(
                            temp, ch[1], w, ax,
                            self.plot_info['is_multiple_well'])

    def get_subax(self, coordinate_x, coordinate_y):
        plt.close(self.fig)
        self.fig, ax = plt.subplots(1, 1, figsize=(3, 2.3))
        if self.plot_info['is_empty']:
            return self.fig
        dye = self.plot_info['dye']
        well = self.plot_info['well']
        if coordinate_x in [1, 2]:
            temp = self.temp_li[coordinate_x-1]
            self.get_subax_x(ax, temp, dye, well, coordinate_y)
        elif coordinate_y == 1 and self.plot_info['is_single']:
            self.plot_raw(dye, well, ax)
        elif coordinate_y == 2:
            if self.plot_info['is_single']:
                self.plot_melt_peak(dye, well, ax)
            else:
                for ch in dye:
                    for w in well:
                        if w not in self.all_well_li:
                            continue
                        self.plot_melt_peak(
                            ch[1], w, ax, self.plot_info['is_multiple_well'])
        self.fig.tight_layout()
        return self.fig
