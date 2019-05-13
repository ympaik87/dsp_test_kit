import pandas as pd
import copy
from dsp.call_mudt import muDT
from dsp.call_rt_pcr_analyzer import rt_pcr_analyzer
from dsp.call_process_result import process_result
from dsp.call_crosstalk import crosstalk
from dsp.dsp_parameters import autosave_parameters


class CallDsp:
    def __init__(self, filepath, params_df, algorithm_param_dict):
        self.temp_li = ['Low Temp', 'High Temp']
        self.dye_li = ['FAM', 'HEX', 'Cal Red 610', 'Quasar 670', 'Quasar 705']
        parameters = self.get_parameters(params_df, algorithm_param_dict)
        self.parameters = parameters
        quant_num1 = int(filepath[0].parent.name.split('QuantStep')[1])
        quant_num2 = int(filepath[1].parent.name.split('QuantStep')[1])

        if quant_num2 < quant_num1:
            self.dsp_main(str(filepath[1]), filepath[0], parameters)
        else:
            self.dsp_main(str(filepath[0]), filepath[1], parameters)

    def get_well_li(self, well_info_file):
        well_li_orig = well_info_file['Well'].tolist()
        self.well_li = [well[0]+str(int(well[1:])) for well in well_li_orig]

    def dsp_main(self, w, file_high, parameters):
        data_dic = {}
        data_dic['Low Temp'] = pd.read_excel(
            w, sheet_name=None, index_col=1)
        data_dic['High Temp'] = pd.read_excel(
            file_high, sheet_name=None, index_col=1)
        data_raw_dic = self.data_pol(data_dic)

        # PC NC recognition
        try:
            w.split('Quantitation Amplification')[1]
            filepath_pc = w.split('Quantitation Amplification')[
                0] + 'End Point Results.xlsx'
        except IndexError:
            filepath_pc = w.split('Quantification Amplification')[
                0] + 'End Point Results.xlsx'

        # parameter claim
        pc_list = {}
        nc_list = {}
        well_info_file = pd.ExcelFile(filepath_pc).parse()
        self.get_well_li(well_info_file)
        pc_list[w] = well_info_file[well_info_file['Content'].str.contains(
            "Pos")]['Well'].tolist()
        nc_list[w] = well_info_file[well_info_file['Content'].str.contains(
            "Neg")]['Well'].tolist()

        try:
            if 'Quantitaion' in w:
                pc_check_list = pc_list[w]
                for i in pc_check_list:
                    if i[1] == '0':
                        pc_check_list[pc_check_list.index(i)] = i[0] + i[2:]
                nc_check_list = nc_list[w]
                for i in nc_check_list:
                    if i[1] == '0':
                        nc_check_list[nc_check_list.index(i)] = i[0] + i[2:]
            else:
                pc_check_list = pc_list[w]
                for i in pc_check_list:
                    if i[1] == '0':
                        pc_check_list[pc_check_list.index(i)] = i[0] + i[2:]
                nc_check_list = nc_list[w]
                for i in nc_check_list:
                    if i[1] == '0':
                        nc_check_list[nc_check_list.index(i)] = i[0] + i[2:]
        except KeyError:
            pc_check_list = []

        # BPN
        data_bpn_dict = self.BPN(data_raw_dic, parameters)
        # MuDT
        mudt_dict, result_data_dict = muDT(
            data_bpn_dict, parameters, pc_check_list)

        mudt_dict_orig = copy.deepcopy(mudt_dict)
        result_data_dict_orig = copy.deepcopy(result_data_dict)
        result_data_dict_anal = rt_pcr_analyzer(mudt_dict, pc_check_list,
                                                result_data_dict, parameters)
        self.result_data_dict_raw = rt_pcr_analyzer(
            mudt_dict_orig, pc_check_list, result_data_dict_orig, parameters,
            is_raw=True)
        result_dict_proc = process_result(result_data_dict_anal, nc_check_list,
                                          parameters, pc_check_list)

        self.result_dict_fi = crosstalk(
            result_dict_proc, pc_check_list, parameters)

        self.pc_check_list = pc_check_list
        self.nc_check_list = nc_check_list
        self.data_raw_dic = data_raw_dic

    def get_dsp_result(self):
        return (self.parameters, self.result_dict_fi, self.pc_check_list,
                self.nc_check_list, self.data_raw_dic, self.well_li)

    def data_pol(self, data_dic):
        for temp in data_dic.keys():
            for dye in data_dic[temp].keys():
                data_dic[temp][dye] = data_dic[temp][dye].dropna(
                    axis=1, how='all')
        return data_dic

    # # BPN module
    def BPN(self, data, parameters):
        df_bpn = copy.deepcopy(data)
        df_bpn_fin = {'Low Temp': {}, 'High Temp': {}}
        BPN_used_cycle = parameters['BPN_used_cycle']

        for i in data['Low Temp'].keys():
            df_bpn_fin['Low Temp'][i] = {}
            df_bpn_fin['High Temp'][i] = {}
        for i in data.keys():
            for j in data[i].keys():
                df_mean_raw = data[i][j].loc[BPN_used_cycle, :].mean()
                df_max = data[i][j].loc[BPN_used_cycle, :].max(axis=0)
                df_min = data[i][j].loc[BPN_used_cycle, :].min(axis=0)
                df_mean_fin = (df_mean_raw * len(BPN_used_cycle) /
                               (len(BPN_used_cycle) - 2) - (df_max + df_min) /
                               (len(BPN_used_cycle) - 2))
                bpn_rv = parameters['BPN_rv'][i][j]
                if parameters['BPN_switch'] and bpn_rv != 0.0:
                    df_bpn_fin[i][j] = df_bpn[i][j] * bpn_rv / df_mean_fin
                else:
                    df_bpn_fin[i][j] = df_bpn[i][j]
        return df_bpn_fin

    def get_parameters(self, init_params_df, algorithm_param_dict):
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
        autosave_parameters(init_params_df)
        init_params_dict = init_params_df.to_dict()
        params_dict = {}
        for key in init_params_dict.keys():
            var_name = params_key_map[key]
            if key == 'bpn_cycle':
                params_dict[var_name] = range(
                    int(init_params_dict[key]['start']),
                    int(init_params_dict[key]['end'])+1)
            else:
                if any(c in key for c in ('1', '2')):
                    if var_name not in params_dict.keys():
                        params_dict[var_name] = {'Low Temp': {},
                                                 'High Temp': {}}
                    if '1' in key:
                        for dye in self.dye_li:
                            params_dict[var_name]['Low Temp'][dye] =\
                                float(init_params_dict[key][dye])
                    elif '2' in key:
                        for dye in self.dye_li:
                            params_dict[var_name]['High Temp'][dye] =\
                                float(init_params_dict[key][dye])
                elif any(c in key for c in (
                        'pmc', 'cr', 'sfc', 'mfc', 'ptp', 'drfu3')):
                    params_dict[var_name] = {}
                    for dye in self.dye_li:
                        if 'sfc' in key or 'mfc' in key:
                            params_dict[var_name][dye] =\
                                int(float(init_params_dict[key][dye]))
                        else:
                            params_dict[var_name][dye] =\
                                float(init_params_dict[key][dye])
                else:
                    params_dict[var_name] = int(float(init_params_dict[key]))
        params_dict.update({'dye_li': self.dye_li})
        params_dict.update(algorithm_param_dict)
        return params_dict
