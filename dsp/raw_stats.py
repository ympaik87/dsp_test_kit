import pathlib
import pandas as pd
import numpy as np


class RawStats:
    def __init__(self, file_li, label_choice):
        self.file_li = file_li
        self.label_choice = label_choice
        self.table_type_li = ['all', 'sample', 'pc']

    def get_label_file(self, file_in):
        filename = file_in.name
        label_file = file_in.parents[1]/pathlib.PurePath(
            filename.split(' -  ')[0] + ' -  labels.xlsx')
        if pathlib.Path(label_file).exists():
            print('label file opened ', label_file.name)
            _dict = pd.read_excel(label_file, sheet_name=None)
            label_dict = {}
            for dye in _dict.keys():
                if dye == 'Info':
                    continue
                well_li = [well[0]+str(int(well[1:])) for well
                           in _dict[dye]['Well ID'].values]
                df = _dict[dye]
                df.index = well_li
                label_dict[dye] = df
        else:
            label_dict = None
        return label_dict

    def get_label_dict_li_from_dsp(self):
        self.label_dict_li = []
        for _dsp, melt in self.dsp_li:
            label_dict = self.get_label_from_dsp(_dsp)
            self.label_dict_li.append(label_dict)

    def get_stats(self, dsp_li, raw_label_dict_li=None):
        self.dsp_li = dsp_li
        if raw_label_dict_li:
            self.label_dict_li = raw_label_dict_li
        else:
            self.get_label_dict_li_from_dsp()
        self.get_EPR_df_li()
        self.get_EPR_stats()
        self.get_RV_stats()

    def get_label_from_dsp(self, _dsp):
        result_dict = _dsp.result_dict_fi['result']
        dsp_label_dict = {}
        for dye in _dsp.dye_li:
            _dict = {}
            for temp in _dsp.temp_li:
                li = []
                for well in _dsp.well_li:
                    try:
                        if result_dict[temp][dye][well] <= 0:
                            li.append('POS')
                        else:
                            li.append('NEG')
                    except KeyError:
                        li.append('NEG')
                    _dict[temp.split(' ')[0]] = li
            dsp_label_dict[dye] = pd.DataFrame(_dict, index=_dsp.well_li)
        return dsp_label_dict

    def get_label_dict_index(self, label_dict):
        try:
            return self.label_dict_li.index(label_dict)
        except ValueError:
            for i in range(len(self.label_dict_li)):
                if label_dict is self.label_dict_li[i]:
                    return i
            raise ValueError('No matched result in label_dict_index')

    def get_EPR_df_li(self):
        self.epr_df_li = []
        for label_dict in self.label_dict_li:
            ind = self.get_label_dict_index(label_dict)
            _dict = {}
            for dye in label_dict.keys():
                df = label_dict[dye]
                well_li = df.index.tolist()
                epr_li = []
                for well in well_li:
                    if df['High'][well] == 'POS':
                        epr = self.calculate_EPR(ind, dye, well)
                    else:
                        epr = 0
                    epr_li.append(epr)
                _dict[dye] = epr_li
            _df = pd.DataFrame(_dict, index=well_li).round(2)
            self.epr_df_li.append(_df)

    def calculate_EPR(self, ind, dye, well):
        _dsp = self.dsp_li[ind][0]
        try:
            _li = []
            for temp in _dsp.temp_li:
                _li.append(_dsp.result_data_dict_raw[
                    'ABSD_array'][temp][dye][well][-1])
            epr = _li[0]/_li[1]
        except KeyError:
            epr = 0
        return epr

    def get_EPR_stats(self):
        epr_ind = [
            '중복 CR Avg', '중복 CR Min', '중복 CR Max', '중복 CR SD',
            'High 단독 CR Avg', 'High 단독 CR Min', 'High 단독 CR Max',
            'High 단독 CR SD']
        epr_dict = {}
        for x in self.table_type_li:
            epr_dict[x] = {}
        for label_dict in self.label_dict_li:
            ind = self.get_label_dict_index(label_dict)
            for dye in label_dict.keys():
                df = label_dict[dye]
                for x in self.table_type_li:
                    if dye not in epr_dict[x].keys():
                        epr_dict[x][dye] = {}
                        for y in ['both', 'high']:
                            epr_dict[x][dye][y] = []
                for well in df.index:
                    epr = self.calculate_EPR(ind, dye, well)
                    if 'POS' in df.loc[well].value_counts().keys() and\
                            df.loc[well].value_counts()['POS'] == 2:
                        self.put_value(epr_dict, ind, dye, well, epr, 'both')
                    elif df['High'][well] == 'POS':
                        self.put_value(epr_dict, ind, dye, well, epr, 'high')
        self.epr_df, self.epr_sd_df, self.epr_sample_df,\
            self.epr_sd_sample_df, self.epr_pc_df, self.epr_sd_pc_df =\
            self.get_table_df(epr_dict, epr_ind)

    def get_stat_li(self, li, is_sd=False):
        std = np.std(li)
        return [[np.average(li), min(li), max(li), std],
                [np.average(li)+std, min(li)+std, max(li)+std, std]]

    def get_table_df(self, in_dict, index_li):
        res_li = []
        for kind, dic1 in in_dict.items():
            _dict = {}
            _dict_sd = {}
            for dye, dic2 in dic1.items():
                val_li = []
                val_sd_li = []
                for key, li in dic2.items():
                    if len(li) > 0:
                        _li, _sd_li = self.get_stat_li(li)
                    else:
                        _li = [np.nan for i in range(4)]
                        _sd_li = [np.nan for i in range(4)]
                    val_li.extend(_li)
                    val_sd_li.extend(_sd_li)
                _dict[dye] = val_li
                _dict_sd[dye] = val_sd_li
            df = pd.DataFrame(_dict, index=index_li).round(4)
            sd_df = pd.DataFrame(_dict_sd, index=index_li).round(4)
            res_li.extend([df, sd_df])
        return res_li

    def calculate_RV(self, ind, dye, well):
        _dsp = self.dsp_li[ind][0]
        bpn_cycle = _dsp.parameters['BPN_used_cycle']
        _li = []
        for temp in _dsp.temp_li:
            try:
                raw = _dsp.data_raw_dic[temp][dye][well]
                raw_rv = raw[list(bpn_cycle)]
                rv = raw_rv[(raw_rv.min() < raw_rv) &
                            (raw_rv.max() > raw_rv)].mean()
                _li.append(rv)
            except KeyError:
                _li.append(np.nan)
        return _li

    def put_value(self, _dict, ind, dye, well, val, key):
        _dsp = self.dsp_li[ind][0]
        _dict['all'][dye][key].append(val)
        if well in _dsp.pc_check_list:
            _dict['pc'][dye][key].append(val)
        else:
            _dict['sample'][dye][key].append(val)

    def get_RV_stats(self):
        rv_ind = [
            'Low RV Avg', 'Low RV Min', 'Low RV Max', 'Low RV SD',
            'High RV Avg', 'High RV Min', 'High RV Max', 'High RV SD']
        rv_dict = {}
        for x in self.table_type_li:
            rv_dict[x] = {}
        self.rv_dict_li = []
        for label_dict in self.label_dict_li:
            ind = self.get_label_dict_index(label_dict)
            _dict = {'Low Temp': {}, 'High Temp': {}}
            for dye in label_dict.keys():
                df = label_dict[dye]
                for x in self.table_type_li:
                    if dye not in rv_dict[x].keys():
                        rv_dict[x][dye] = {}
                        for y in ['low', 'high']:
                            rv_dict[x][dye][y] = []
                _dict['Low Temp'][dye] = {}
                _dict['High Temp'][dye] = {}
                for well in df.index:
                    low, high = self.calculate_RV(ind, dye, well)
                    if df['Low'][well] != 'GRAY' and not np.isnan(low):
                        _dict['Low Temp'][dye][well] = low
                        self.put_value(rv_dict, ind, dye, well, low, 'low')
                    else:
                        _dict['Low Temp'][dye][well] = 0

                    if df['High'][well] != 'GRAY'and not np.isnan(high):
                        self.put_value(rv_dict, ind, dye, well, high, 'high')
                        _dict['High Temp'][dye][well] = high
                    else:
                        _dict['High Temp'][dye][well] = 0
            self.rv_dict_li.append(_dict)

        self.rv_df, self.rv_sd_df, self.rv_sample_df, self.rv_sd_sample_df,\
            self.rv_pc_df, self.rv_sd_pc_df = self.get_table_df(
                rv_dict, rv_ind)

    def get_df_list(self):
        return [self.epr_df, self.epr_sd_df, self.rv_df, self.rv_sd_df,
                self.epr_sample_df, self.epr_sd_sample_df, self.rv_sample_df,
                self.rv_sd_sample_df, self.epr_pc_df, self.epr_sd_pc_df,
                self.rv_pc_df, self.rv_sd_pc_df]
