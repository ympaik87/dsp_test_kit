import io
import pathlib
import matplotlib.pyplot as plt
from dsp_coder_plot import DspCoderPlot
import xlsxwriter
import datetime
import os


def single_well_plot(w, parameters, result_dict, pc_check_list,
                     nc_check_list, raw_data):
    _coder_plot = DspCoderPlot(parameters, result_dict, pc_check_list,
                               nc_check_list, raw_data)
    dye, well = parameters['single_well']

    inputf = pathlib.PurePath(w.translate(str.maketrans('', '', '[]<>?|*')))
    save_path = inputf.parents[1]
    fname = 'single_' + inputf.name.split(' -  ')[0] + '_' + dye + '_' + well +\
        inputf.suffix
    if os.path.exists(save_path/fname):
        name, ext = fname.split('.')
        fname = name + datetime.datetime.now().strftime(
            '_%Y%m%d_%H%M%S') + inputf.suffix
    fpath = save_path/fname
    with xlsxwriter.Workbook(fpath) as writer:
        ws = writer.add_worksheet(dye)
        ws.set_column('B:B', 50)

        raw_fig = _coder_plot.plot_raw(dye, well)
        fig3_data = io.BytesIO()
        raw_fig.savefig(fig3_data, bbox_inches='tight')
        fig3_data.seek(0)
        ws.insert_image('C1', 'raw_fig.png', {'image_data': fig3_data})
        plt.close(raw_fig)
        row = 1
        for temp in raw_data.keys():
            result_well = result_dict['result'][temp][dye][well]
            base_fig = _coder_plot.plot_baseline(temp, dye, well)

            fig1_data = io.BytesIO()
            if result_well == 4 or result_well <= 0:
                fig = _coder_plot.plot_sigmoid(temp, dye, well)
                fig.savefig(fig1_data, bbox_inches='tight')
            else:
                base_fig.savefig(fig1_data, bbox_inches='tight')
            fig1_data.seek(0)
            ws.insert_image('M'+str(row), 'sigmoid_fig.png',
                            {'image_data': fig1_data})

            fig2_data = io.BytesIO()
            base_fig.savefig(fig2_data, bbox_inches='tight')
            fig2_data.seek(0)
            ws.insert_image('H'+str(row), 'base_fig.png',
                            {'image_data': fig2_data})

            plt.close(base_fig)
            if result_well == 4 or result_well <= 0:
                plt.close(fig)

            row += 1
            ws.write('A'+str(row), 'File Name')
            ws.write('B'+str(row), w)
            row += 1
            ws.write('A'+str(row), 'Temperature')
            ws.write('B'+str(row), temp)
            row += 1
            ws.write('A'+str(row), 'Dye')
            ws.write('B'+str(row), dye)
            row += 1
            ws.write('A'+str(row), 'Well')
            ws.write('B'+str(row), well)
            row += 10
