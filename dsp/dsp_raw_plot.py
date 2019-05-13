from dsp.dsp_coder_plot import DspViewerPlot, plot_init_empty
import matplotlib.pyplot as plt


class DspRawPlot(DspViewerPlot):
    def __init__(self, params, result_dict, pc_check_list, nc_check_list,
                 raw_data, all_well_li, melt_dict):
        super().__init__(params, result_dict, pc_check_list, nc_check_list,
                         raw_data, all_well_li, melt_dict)

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
            self.plot_sigmoid(temp, dye, well, self.axes[1, col])
            col += 1
        self.plot_raw(dye, well, self.axes[0, 2])
        self.plot_melt_peak(dye, well, self.axes[1, 2])
        self.fig.tight_layout()
        return self.fig

    def plot_baseline(self, temp, dye, well, ax):
        self._get_data(temp, dye, well)
        if self.result in [0, -1, -2, 3, 4]:
            ax.plot(self.x, self.rd, 'y.', markersize=3)
            ax.plot(self.x, self.rd-self.rd_diff, 'k.', markersize=3)
            ax.plot(self.x, self.scd_fit, 'r')
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
        self._get_text(ax, loc, text='EFC=', text_content=self.efc)
        loc -= 0.1
        self._get_text(ax, loc, text='LSR=', text_content=self.lsr_val)

    def plot_sigmoid(self, temp, dye, well, ax):
        self._get_data(temp, dye, well)
        ax.plot(self.x, self.absd_orig+self.rd_diff-self.shift,
                'y.', markersize=3)
        ax.plot(self.x, self.absd_orig-self.shift, 'b.', markersize=3)
        ax.plot(self.x, self.absd-self.shift, 'k.', markersize=3)
        ax.plot(self.x, self.absd-self.shift, 'k')
        ax.set_title(f'{temp} Substracted Baseline')
        ax.set_xlabel('Cycles')
        ax.set_ylabel('RFU')
        ax.grid(True, color=self.dye_color['grid'])
        ax.hlines(self.thrd, self.x[0], self.x[-1], color='c')
        loc = 0.9
        self._get_text(ax, loc)
        loc -= 0.1
        self._get_text(ax, loc, text='Thrd=', text_content=self.thrd)
        loc -= 0.1
        rfu_end = round(self.absd[-1], 4)
        self._get_text(ax, loc, text='RFU diff=', text_content=rfu_end)

    def plot_sigmoid_multi(self, temp, dye, well, ax, is_multiple_well=False):
        self._get_data(temp, dye, well)
        ax.plot(self.x, self.absd-self.shift, 'k', color=self.dye_color[dye])
        if is_multiple_well:
            ax.set_title(f'{temp} Baseline Multiple')
        else:
            ax.set_title(f'{temp} Substracted Baseline {well}')
        ax.set_xlabel('Cycles')
        ax.set_ylabel('RFU')
        ax.grid(True, color=self.dye_color['grid'])

    def get_subax_x(self, ax, temp, dye, well, y):
        if y == 1 and self.plot_info['is_single']:
            self.result = self.result_dict['result'][temp][dye][well]
            self.plot_baseline(temp, dye, well, ax)
        elif self.plot_info['is_single']:
            self.plot_sigmoid(temp, dye, well, ax)
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
