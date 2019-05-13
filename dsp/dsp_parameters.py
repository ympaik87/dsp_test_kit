import os
import pandas as pd


def import_parameters(path, bpn_index, common_index, sample_index, pc_index):
    imported_df = pd.read_excel(path, index_col=[0, 1])
    bpnrv_df = imported_df.loc['BPN'].loc['BPN rv']
    bpnrv_df.index = ['BPN RV (L)', 'BPN RV (H)']
    param_df_dict = {'bpnrv_df': bpnrv_df}
    bpn_cycle = (imported_df.loc['BPN'].loc['BPN cycle']['FAM'].values[0],
                 imported_df.loc['BPN'].loc['BPN cycle']['FAM'].values[1])
    param_df_dict['bpn_cycle'] = bpn_cycle

    common_df = imported_df.loc['Common']
    common_df.index = common_index
    param_df_dict['common_df'] = common_df.fillna(0)

    sample_df = imported_df.loc['Sample']
    sample_df.index = sample_index
    param_df_dict['sample_df'] = sample_df.fillna(0)

    pc_df = imported_df.loc['PC']
    pc_df.index = pc_index
    param_df_dict['pc_df'] = pc_df.fillna(0)

    # TODO: import algorithm setting
    return param_df_dict


def autosave_parameters(df):
    path = os.getcwd()
    if not os.path.exists(path + '/config'):
        os.makedirs(path + '/config')
    df.to_csv(path + '/config/parameters.sg')


def get_init_parameters(dye_li):
    path = os.getcwd()
    if os.path.exists(path + '/config/parameters.sg'):
        init_params_df = pd.read_csv(path + '/config/parameters.sg',
                                     index_col=0, engine='python')
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
        autosave_parameters(init_params_df)
    return init_params_df.T
