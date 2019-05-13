from dsp_coder_plot import DspCoderPlot
import matplotlib.pyplot as plt
import pathlib
import datetime
import os
import io
import xlsxwriter


def save_raw(w, parameters, result_dict, pc_check_list,
             nc_check_list, raw_data, sigmoid=False):
    position_x = {'1': 'A', '2': 'G', '3': 'M', '4': 'S', '5': 'Y',
                  '6': 'AE', '7': 'AK', '8': 'AQ', '9': 'AW',
                  '10': 'BC', '11': 'BI', '12': 'BO'}
    position_y = {'A': '1', 'B': '15', 'C': '29', 'D': '43',
                  'E': '57', 'F': '71', 'G': '85', 'H': '99'}
    _coder_plot = DspCoderPlot(parameters, result_dict, pc_check_list,
                               nc_check_list, raw_data)

    inputf = pathlib.PurePath(w.translate(str.maketrans('', '', '[]<>?|*')))
    save_path = inputf.parents[1]
    if sigmoid:
        fname = 'fig_' + inputf.name.split(' -  ')[0] + inputf.suffix
    else:
        fname = 'raw_' + inputf.name.split(' -  ')[0] + inputf.suffix
    if os.path.exists(save_path/fname):
        name, ext = fname.split('.')
        fname = name + datetime.datetime.now().strftime(
            '_%Y%m%d_%H%M%S') + inputf.suffix
    fpath = save_path/fname
    with xlsxwriter.Workbook(fpath) as writer:
        for temp in raw_data.keys():
            for dye in raw_data[temp].keys():
                if parameters['used_temp'][temp][dye] != 1:
                    continue
                sheet_name = dye + '_' + temp[0]
                ws = writer.add_worksheet(sheet_name)
                for well in raw_data[temp][dye].keys():
                    result = result_dict['result'][temp][dye][well]
                    if sigmoid and (result <= 0 or result == 4):
                        base_fig = _coder_plot.plot_sigmoid(temp, dye, well)
                    else:
                        base_fig = _coder_plot.plot_baseline(temp, dye, well)
                    base_fig_data = io.BytesIO()
                    base_fig.savefig(base_fig_data, bbox_inches='tight')
                    fig_pos = position_x[well[1:]] + position_y[well[0]]
                    ws.insert_image(fig_pos, 'base_fig.png',
                                    {'image_data': base_fig_data})
                    plt.close(base_fig)

        if not sigmoid:
            for dye in raw_data['High Temp'].keys():
                sheet_name_raw = dye + '_raw'
                ws_raw = writer.add_worksheet(sheet_name_raw)
                for well in raw_data['High Temp'][dye].keys():
                    raw_fig = _coder_plot.plot_raw(dye, well)
                    raw_fig_data = io.BytesIO()
                    raw_fig.savefig(raw_fig_data, bbox_inches='tight')
                    fig_pos = position_x[well[1:]] + position_y[well[0]]
                    ws_raw.insert_image(fig_pos, 'raw_fig.png',
                                        {'image_data': raw_fig_data})
                    plt.close(raw_fig)
