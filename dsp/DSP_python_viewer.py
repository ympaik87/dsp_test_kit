import pandas as pd
import os
import pathlib
import time
import xlsxwriter
import datetime
from tkinter import Label, Tk, ttk, Frame, filedialog, Toplevel
from dsp_main import main
from dsp_entry import DspEntry, Checkbar, CrosstalkDropdown


def crosstalk_dropdown(tab, style, dye_li):
    _crosstalk = CrosstalkDropdown(tab, style, dye_li)
    return _crosstalk


def plot_apply_results(init_params_df, entry_dict, dye_li):
    export_parameters(init_params_df, entry_dict, dye_li)

    app_res_path = filedialog.askopenfilename(filetypes=(
        ("Excel", "Apply Result.xlsx"), ("All files", "*.*")))
    print('Apply Result path: ', app_res_path)
    app_res_df = pd.read_excel(app_res_path)
    parameters_dict = get_parameters(entry_dict, dye_li)

    res_path = pathlib.PurePath(app_res_path).parent
    res_fname = 'Plot_Apply_Results.xlsx'
    if os.path.exists(res_path/res_fname):
        name, ext = res_fname.split('.')
        res_fname = name + datetime.datetime.now().strftime(
            '_%Y%m%d_%H%M.') + ext
    with xlsxwriter.Workbook(res_path/res_fname) as writer:
        worksheets_dict = {}
        for dye in dye_li:
            ws = writer.add_worksheet(dye)
            ws.set_column('B:B', 50)
            worksheets_dict[dye] = [ws, 1]

        grouped = app_res_df.groupby(by='File Path')
        for name, group in grouped:
            filepath = pathlib.PurePath(name)
            filename = filepath.name
            for i in pathlib.Path(filepath.parent).glob('*Amplification*'):
                if 'Quant' in str(i.name) and filename.split(' - ')[0] in str(
                        i.name):
                    fname = i.name
            experiment_path = filepath.parents[1]
            file_li = [x/fname for x in pathlib.Path(experiment_path).iterdir()
                       if x.is_dir() and 'QuantStep' in x.name]
            main(str(file_li[0]), file_li[1], parameters=parameters_dict,
                 group=group, worksheets_dict=worksheets_dict)


def finish_msg(elapsed):
    msg_fin = Toplevel()
    msg_lbl = ttk.Label(msg_fin, text='DSP analysis has been finished')
    msg_lbl.grid(row=0, column=0)
    msg_lbl = ttk.Label(msg_fin, text='Time : ' + str(elapsed) + 'Minute')
    msg_lbl.grid(row=1, column=0)
    msg_btn = ttk.Button(msg_fin, text='Confirm', command=msg_fin.destroy)
    msg_btn.grid(row=2, column=0)


def insert_entries(root, param_df, dye_li, tabs, style, crosstalk_tab):
    entry_dict = {}
    _entry = DspEntry(root, param_df, dye_li, tabs, style, crosstalk_tab)

    dye_label_li = ['FAM', 'HEX', 'Cal610', 'Q670', 'Q705']
    _entry.dye_labels(dye_label_li, 2)
    for tab in tabs:
        _entry.dye_labels(dye_label_li, 3, tab=tab)

    entry_dict['bpn_cycle'] = _entry.dyeless_entries(
        1, 1, 'BPN cycle', 'bpn_cycle', 'start', end_cycle='end')

    entry_dict['pmc'] = _entry.dye_entries(3, 'PMC', 'pmc')
    entry_dict['cr'] = _entry.dye_entries(4, 'CR', 'cr')
    entry_dict['cr_pc'] = _entry.dye_entries(5, 'CR (PC)', 'cr_pc')
    entry_dict['sfc'] = _entry.dye_entries(6, 'SFC', 'sfc')
    entry_dict['sfc_pc'] = _entry.dye_entries(7, 'SFC (PC)', 'sfc_pc')
    entry_dict['mfc'] = _entry.dye_entries(8, 'MFC', 'mfc')
    entry_dict['mfc_pc'] = _entry.dye_entries(9, 'MFC (PC)', 'mfc_pc')
    entry_dict['ptp'] = _entry.dye_entries(10, 'DRFU2', 'ptp')
    entry_dict['drfu3'] = _entry.dye_entries(11, 'DRFU3', 'drfu3')

    _entry.blank(29, 2, is_tabs=True)

    entry_dict['bpn_rv1'], entry_dict['bpn_rv2'] = _entry.tab_entries(
        4, ['bpn_rv1', 'bpn_rv2'], 'BPN RV')
    entry_dict['drfu1'], entry_dict['drfu2'] = _entry.tab_entries(
        5, ['drfu1', 'drfu2'], 'DRFU')
    entry_dict['thrd1'], entry_dict['thrd2'] = _entry.tab_entries(
        6, ['thrd1', 'thrd2'], 'Thrd')
    entry_dict['rpc1'], entry_dict['rpc2'] = _entry.tab_entries(
        7, ['rpc1', 'rpc2'], 'RPC')
    entry_dict['rc1'], entry_dict['rc2'] = _entry.tab_entries(
        8, ['rc1', 'rc2'], 'RC')
    entry_dict['dfm1'], entry_dict['dfm2'] = _entry.tab_entries(
        9, ['dfm1', 'dfm2'], 'dfM')
    entry_dict['dfc1'], entry_dict['dfc2'] = _entry.tab_entries(
        10, ['dfc1', 'dfc2'], 'dfC')
    entry_dict['used_temp1'], entry_dict['used_temp2'] = _entry.tab_entries(
        11, ['used_temp1', 'used_temp2'], 'Used Temperature')
    entry_dict['cut_off1'], entry_dict['cut_off2'] = _entry.tab_entries(
        12, ['cut_off1', 'cut_off2'], 'Cut Off')
    entry_dict['cut_off_nc1'], entry_dict['cut_off_nc2'] = _entry.tab_entries(
        13, ['cut_off_nc1', 'cut_off_nc2'], 'Cut Off (NC)')

    _entry.blank(14, 1, is_tabs=True)
    _entry.blank(15, 1, is_tabs=True, text='Positive Control (PC)')

    entry_dict['drfu1_pc'], entry_dict['drfu2_pc'] = _entry.tab_entries(
        16, ['drfu1_pc', 'drfu2_pc'], 'DRFU for PC')
    entry_dict['thrd1_pc'], entry_dict['thrd2_pc'] = _entry.tab_entries(
        17, ['thrd1_pc', 'thrd2_pc'], 'Thrd for PC')
    entry_dict['rpc1_pc'], entry_dict['rpc2_pc'] = _entry.tab_entries(
        18, ['rpc1_pc', 'rpc2_pc'], 'RPC for PC')
    entry_dict['rc1_pc'], entry_dict['rc2_pc'] = _entry.tab_entries(
        19, ['rc1_pc', 'rc2_pc'], 'RC for PC')
    entry_dict['dfM1_pc'], entry_dict['dfM2_pc'] = _entry.tab_entries(
        20, ['dfM1_pc', 'dfM2_pc'], 'dfM for PC')
    entry_dict['dfC1_pc'], entry_dict['dfC2_pc'] = _entry.tab_entries(
        21, ['dfC1_pc', 'dfC2_pc'], 'dfC for PC')

    return entry_dict


def insert_parameters(root, param_df, dye_li, tabs, style, crosstalk_tab):
    entry_dict = insert_entries(root, param_df, dye_li, tabs, style,
                                crosstalk_tab)

    check_bar = Checkbar(root, ['Save raw figures', 'Save figures',
                                'Save label results'], style)
    check_bar.grid(column=8, row=13)
    check_bar_bpn = Checkbar(root, ['BPN switch on'], style)
    check_bar_bpn.grid(column=4, row=1, columnspan=2)
    check_bar.vars.extend(check_bar_bpn.vars)
    entry_dict['radio_btn'] = check_bar.vars
    return entry_dict


def import_parameters():
    path_raw = filedialog.askopenfilename(filetypes=(
        ("*", "*.xlsx"), ("All files", "*.*")))
    param = pd.read_excel(path_raw, index_col=0)

    dye_li = ['FAM', 'HEX', 'Cal Red 610', 'Quasar 670', 'Quasar 705']
    label_li = ['bpn_rv', 'dfc', 'dfm', 'drfu', 'thrd']
    param_dict = {'pmc': {}, 'sfc': {}, 'mfc': {}}
    for dye in dye_li:
        param_dict['pmc'][dye] = param.T['PCM'][0]
    for p in ['MFC', 'SFC', 'PCM']:
        if p == 'PCM':
            param_dict['pmc'] = param.T[p][0]
        else:
            param_dict[p.lower()] = param.T[p][0]
    param_dict['bpn_cycle'] = {}
    param_dict['bpn_cycle']['start'] = param.T['RC Start'][0]
    param_dict['bpn_cycle']['end'] = param.T['RC End'][0]

    for c in param.T.columns:
        if 'Low' in c:
            name = c.split(' ')[0]
            for x in label_li:
                if name in x or name.lower() in x:
                    param_dict[x.lower()+'1'] = {}
                    param_dict[x.lower()+'1'] = param.T[c]
                elif name == 'rPar^2':
                    param_dict['rpc1'] = param.T[c]
                elif name == 'R^2':
                    param_dict['rc1'] = param.T[c]
        elif 'High' in c:
            name = c.split(' ')[0]
            for x in label_li:
                if name in x or name.lower() in x:
                    param_dict[x.lower()+'2'] = {}
                    param_dict[x.lower()+'2'] = param.T[c]
                elif name == 'rPar^2':
                    param_dict['rpc2'] = param.T[c]
                elif name == 'R^2':
                    param_dict['rc2'] = param.T[c]

    params_input_df = pd.DataFrame(param_dict)
    new_ind = []
    for ind in params_input_df.index:
        if 'ch' in ind:
            new_ind.append(dye_li[list(params_input_df.index).index(ind)])
        else:
            new_ind.append(ind)
    params_input_df.index = new_ind

    path = os.getcwd()
    if os.path.exists(path + '/config/parameters.sg'):
        params_df = pd.read_csv(path + '/config/parameters.sg', index_col=0)
        params_df.update(params_input_df)
    else:
        missing_dict = {'cr': {}, 'cr_pc': {}, 'sfc_pc': {}, 'mfc': {},
                        'mfc_pc': {}, 'ptp': {}, 'drfu3': {}}
        for dye in dye_li:
            missing_dict['cr'][dye] = 1.2
            missing_dict['cr_pc'][dye] = 1.2
            missing_dict['sfc_pc'][dye] = 4
            missing_dict['ptp'][dye] = 0
            missing_dict['drfu3'][dye] = 0
        for t in ['dfM1_pc', 'dfM2_pc']:
            missing_dict[t] = {}
            for dye in dye_li:
                missing_dict[t][dye] = 5
        for t in ['rpc1_pc', 'rpc2_pc', 'rc1_pc', 'rc2_pc']:
            init_params[t] = {}
            for dye in dye_li:
                init_params[t][dye] = 0.9
        for t in ['thrd1_pc', 'thrd2_pc']:
            init_params[t] = {}
            for dye in dye_li:
                init_params[t][dye] = 110
        for t in ['dfC1_pc', 'dfC2_pc']:
            missing_dict[t] = {}
            for dye in dye_li:
                missing_dict[t][dye] = 10
        for t in ['thrd1_pc', 'thrd2_pc']:
            missing_dict[t] = {}
            for dye in dye_li:
                missing_dict[t][dye] = 110
        for t in ['used_temp1', 'used_temp2']:
            missing_dict[t] = {}
            for dye in dye_li[:-1]:
                missing_dict[t][dye] = 1
            missing_dict[t][dye_li[-1]] = 0
        for t in ['cut_off1', 'cut_off2', 'cut_off_nc1', 'cut_off_nc2']:
            missing_dict[t] = {}
            for dye in dye_li:
                missing_dict[t][dye] = 45
        missing_df = pd.DataFrame(missing_dict)
        params_df = pd.concat([params_input_df, missing_df], axis=1, sort=True)
    global entry_dict
    entry_dict.update(insert_entries(root, params_df.fillna(0), dye_li, tabs,
                                     style, crosstalk_tab))


def export_parameters(init_params_df, entry_dict, dye_li):
    for k, v in entry_dict.items():
        if isinstance(v, list) and len(v) == 5:
            for e in v:
                dye = dye_li[v.index(e)]
                init_params_df[k][dye] = e.get()
        elif isinstance(v, list) and k == 'bpn_cycle':
            init_params_df[k]['start'] = v[0].get()
            init_params_df[k]['end'] = v[1].get()

    path = os.getcwd()
    if not os.path.exists(path + '/config'):
        os.makedirs(path + '/config')
    init_params_df.to_csv(path + '/config/parameters.sg')


def get_algoritm_param(var_li):
    if 'Default' not in var_li[0]:
        if 'PC' in var_li[1]:
            pc_val = 1
            sample_val = 0
        elif 'Sample' in var_li[1]:
            pc_val = 0
            sample_val = 1
        else:
            pc_val = 1
            sample_val = 1
    else:
        pc_val = 0
        sample_val = 0
    param_dict = {
        'PC': pc_val,
        'sample': sample_val
    }
    return param_dict


def get_parameters(entry_dict, dye_li):
    params_key_map = {
        'bpn_cycle': 'BPN_used_cycle',
        'pmc': 'PMC',
        'cr': 'CR',
        'cr_pc': 'CR_pc',
        'sfc': 'SFC',
        'sfc_pc': 'SFC_pc',
        'mfc': 'MFC',
        'mfc_pc': 'MFC_pc',
        'ptp': 'PTP',
        'drfu3': 'drfu3',
        'bpn_rv1': 'BPN_rv',
        'bpn_rv2': 'BPN_rv',
        'drfu1': 'DRFU_array',
        'drfu2': 'DRFU_array',
        'thrd1': 'Thrd_array',
        'thrd2': 'Thrd_array',
        'rpc1': 'RPC_array',
        'rpc2': 'RPC_array',
        'rc1': 'RC_array',
        'rc2': 'RC_array',
        'dfm1': 'dfM_array',
        'dfm2': 'dfM_array',
        'dfc1': 'dfC_array',
        'dfc2': 'dfC_array',
        'used_temp1': 'used_temp',
        'used_temp2': 'used_temp',
        'cut_off1': 'cut',
        'cut_off2': 'cut',
        'cut_off_nc1': 'cut_nc',
        'cut_off_nc2': 'cut_nc',

        'drfu1_pc': 'drfu_array_pc',
        'drfu2_pc': 'drfu_array_pc',
        'thrd1_pc': 'Thrd_array_pc',
        'thrd2_pc': 'Thrd_array_pc',
        'rpc1_pc': 'rpc_array_pc',
        'rpc2_pc': 'rpc_array_pc',
        'rc1_pc': 'rc_array_pc',
        'rc2_pc': 'rc_array_pc',
        'dfM1_pc': 'dfM_array_pc',
        'dfM2_pc': 'dfM_array_pc',
        'dfC1_pc': 'dfC_array_pc',
        'dfC2_pc': 'dfC_array_pc',
        'radio_btn': '',
    }
    radio_btn_li = ['ind_raw', 'ind_fig', 'label_switch', 'BPN_switch']
    params_dict = {'crosstalk': {}}
    crosstalk_entry_li, algoritm_entry_li, singlewell_entry_li =\
        _crosstalk.get_entry()
    crosstalk_li = list()
    for ent_li in crosstalk_entry_li:
        li = list()
        for e in ent_li:
            li.append(e.get())
        if 'Dye' not in li:
            crosstalk_li.append(li)
    params_dict['crosstalk'] = crosstalk_li

    val_li = [ent.get() for ent in algoritm_entry_li[0]]
    params_dict['absd_corrector_ver'] = get_algoritm_param(val_li)
    val_li = [ent.get() for ent in algoritm_entry_li[1]]
    params_dict['asymm_sigfit_ver'] = get_algoritm_param(val_li)

    var = algoritm_entry_li[2].get()
    if 'V' in var:
        params_dict['gi_switch'] = 1
    else:
        params_dict['gi_switch'] = 0
    if 'B' in var:
        params_dict['gib1_switch'] = 1
    else:
        params_dict['gib1_switch'] = 0
    if 'P' in var:
        params_dict['gip'] = 1
    else:
        params_dict['gip'] = 0

    single_well_check = singlewell_entry_li[0].get()
    if single_well_check:
        _single_well = singlewell_entry_li[2].get()
        if _single_well[1] == '0':
            _single_well = _single_well[0] + _single_well[2:]
        params_dict['single_well'] = [singlewell_entry_li[1].get(),
                                      _single_well.upper()]

    for key, value in entry_dict.items():
        var_name = params_key_map[key]

        if any(c in key for c in ('1', '2')):
            if var_name not in params_dict.keys():
                params_dict[var_name] = {'Low Temp': {}, 'High Temp': {}}
            if '1' in key:
                for entry in value:
                    dye = dye_li[value.index(entry)]
                    params_dict[var_name]['Low Temp'][dye] = float(entry.get())
            elif '2' in key:
                for entry in value:
                    dye = dye_li[value.index(entry)]
                    params_dict[var_name]['High Temp'][dye] = float(
                        entry.get())
        elif key == 'bpn_cycle':
            params_dict[var_name] = range(int(float(value[0].get())),
                                          int(float(value[1].get()))+1)
        elif any(c in key for c in (
                'pmc', 'cr', 'sfc', 'mfc', 'ptp', 'drfu3')):
            params_dict[var_name] = {}
            for entry in value:
                dye = dye_li[value.index(entry)]
                if 'sfc' in key or 'mfc' in key:
                    params_dict[var_name][dye] = int(float(entry.get()))
                else:
                    params_dict[var_name][dye] = float(entry.get())
        elif key == 'radio_btn':
            params_dict[var_name] = {}
            for element in value:
                idx = value.index(element)
                params_dict[radio_btn_li[idx]] = element.get()
        else:
            params_dict[var_name] = int(float(value.get()))
        params_dict.update({'dye_li': dye_li})
    return params_dict


def call_main_fn(entry_dict, path, dye_li):
    filepath = pathlib.PurePath(path)
    filename = filepath.name
    experiment_path = filepath.parents[1]
    file_li = [x / filename for x in pathlib.Path(experiment_path).iterdir()
               if x.is_dir() and 'QuantStep' in x.name]

    parameters_dict = get_parameters(entry_dict, dye_li)
    main(str(file_li[0]), file_li[1], parameters=parameters_dict)


def file_btn(init_params_df, entry_dict, dye_li):
    tt = time.time()
    export_parameters(init_params_df, entry_dict, dye_li)

    filepath_raw = filedialog.askopenfilename(filetypes=(
        ("Excel", "*Amplification*.xlsx"), ("All files", "*.*")))
    print('filepath_raw: ', filepath_raw)
    call_main_fn(entry_dict, filepath_raw, dye_li)
    elapsed = round((time.time() - tt) / 60, 1)
    finish_msg(elapsed)


def auto_btn(init_params_df, entry_dict, dye_li):
    tt = time.time()

    export_parameters(init_params_df, entry_dict, dye_li)

    starting_path = pathlib.Path('Raw Files/')
    dir_li = [x for x in starting_path.glob('**') if 'QuantStep' in str(x)]
    if len(dir_li) > 1:
        first_dir_li = [dir_li[0]]
        for d in dir_li[1:]:
            if d.parent not in [x.parent for x in first_dir_li]:
                first_dir_li.append(d)
        for dir in first_dir_li:
            for file in dir.glob('*Amplification*'):
                if 'Quant' in str(file.name):
                    call_main_fn(entry_dict, file, dye_li)
    else:
        print('Error: more than two QuantStep folders must exist')

    elapsed = round((time.time() - tt) / 60, 1)
    finish_msg(elapsed)


if __name__ == "__main__":
    dye_li = ['FAM', 'HEX', 'Cal Red 610', 'Quasar 670', 'Quasar 705']

    path = os.getcwd()
    if os.path.exists(path + '/config/parameters.sg'):
        init_params_df = pd.read_csv(path + '/config/parameters.sg',
                                     index_col=0)
    else:
        init_params = {'pmc': {}, 'cr': {}, 'cr_pc': {}, 'sfc': {},
                       'sfc_pc': {}, 'mfc': {}, 'mfc_pc': {}, 'ptp': {},
                       'drfu3': {}}
        for dye in dye_li:
            init_params['pmc'][dye] = 0.09
            init_params['cr'][dye] = 1.2
            init_params['cr_pc'][dye] = 1.2
            init_params['sfc'][dye] = 4
            init_params['sfc_pc'][dye] = 4
            init_params['mfc'][dye] = 12
            init_params['mfc_pc'][dye] = 12
            init_params['ptp'][dye] = 0
            init_params['drfu3'][dye] = 0
        for t in ['dfm1', 'dfm2']:
            init_params[t] = {}
            for dye in dye_li:
                init_params[t][dye] = 18
        for t in ['dfc1', 'dfc2']:
            init_params[t] = {}
            for dye in dye_li:
                init_params[t][dye] = 30
        for t in ['used_temp1', 'used_temp2']:
            init_params[t] = {}
            for dye in dye_li[:-1]:
                init_params[t][dye] = 1
            init_params[t][dye_li[-1]] = 0
        init_params['bpn_cycle'] = {}
        init_params['bpn_cycle']['start'] = 3
        init_params['bpn_cycle']['end'] = 8
        for t in ['bpn_rv1', 'bpn_rv2']:
            init_params[t] = {}
            for dye in dye_li:
                init_params[t][dye] = 5000
        for t in ['drfu1', 'drfu2', 'drfu1_pc', 'drfu2_pc']:
            init_params[t] = {}
            for dye in dye_li:
                init_params[t][dye] = 110
        for t in ['thrd1', 'thrd2', 'thrd1_pc', 'thrd2_pc']:
            init_params[t] = {}
            for dye in dye_li:
                init_params[t][dye] = 110
        for t in ['rpc1', 'rpc2', 'rc1', 'rc2',
                  'rpc1_pc', 'rpc2_pc', 'rc1_pc', 'rc2_pc']:
            init_params[t] = {}
            for dye in dye_li:
                init_params[t][dye] = 0.9
        for t in ['dfM1_pc', 'dfM2_pc']:
            init_params[t] = {}
            for dye in dye_li:
                init_params[t][dye] = 5
        for t in ['dfC1_pc', 'dfC2_pc']:
            init_params[t] = {}
            for dye in dye_li:
                init_params[t][dye] = 10
        for t in ['cut_off1', 'cut_off2', 'cut_off_nc1', 'cut_off_nc2']:
            init_params[t] = {}
            for dye in dye_li:
                init_params[t][dye] = 45
        init_params_df = pd.DataFrame(init_params)

    root = Tk()

    root.title('DSP Python V14.2.1')

    lbl = Label(root, text='DSP Python V14.2.1')
    lbl.grid(row=0, column=0)

    style = ttk.Style().configure('TButton')

    nb = ttk.Notebook(root)
    tabs = [Frame(nb) for i in range(2)]
    crosstalk_tab = Frame(nb)

    nb.add(tabs[0], text='Low')
    nb.add(tabs[1], text='High')

    nb.add(crosstalk_tab, text='Algorithm Options')
    global _crosstalk
    _crosstalk = crosstalk_dropdown(crosstalk_tab, style, dye_li)

    nb.grid(column=1, row=12, columnspan=7, rowspan=16, pady=15)

    global entry_dict
    entry_dict = insert_parameters(root, init_params_df, dye_li, tabs, style,
                                   crosstalk_tab)

    btn1 = ttk.Button(root, text='1. Import Parameters', width=30,
                      command=import_parameters)
    btn1.grid(row=1, column=8)
    btn1 = ttk.Button(root, text='2. Auto Analysis', width=30,
                      command=lambda: auto_btn(init_params_df, entry_dict,
                                               dye_li))
    btn1.grid(row=2, column=8)
    btn5 = ttk.Button(root, text='3. One File Analysis', width=30,
                      command=lambda: file_btn(init_params_df, entry_dict,
                                               dye_li))
    btn5.grid(row=3, column=8)
    btn6 = ttk.Button(root, text='4. Plot from Apply Results', width=30,
                      command=lambda: plot_apply_results(init_params_df,
                                                         entry_dict, dye_li))
    btn6.grid(row=4, column=8)

    root.mainloop()
