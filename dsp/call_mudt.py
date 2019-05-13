import numpy as np
import copy


def get_end_rfu(array, sfc_well):
    return array[-1] - np.min(array[sfc_well:])


def muDT(data, params, pc_check_list, fb=0, gib1_res=None):
    result_data_dict = {}
    for p in ['data_process_num', 'result', 'end_rfu']:
        result_data_dict[p] = {
            'Low Temp': {'FAM': {}, 'HEX': {}, 'Cal Red 610': {},
                         'Quasar 670': {}, 'Quasar 705': {}},
            'High Temp': {'FAM': {}, 'HEX': {}, 'Cal Red 610': {},
                          'Quasar 670': {}, 'Quasar 705': {}}
        }
    mudt_dict = copy.deepcopy(data)
    for i in data.keys():
        for j in data[i].keys():
            # if params['used_temp'][i][j] != 1:
            #     continue
            for k in data[i][j].columns:
                result_data_dict['result'][i][j][k] = 0
                result_data_dict['data_process_num'][i][j][k] = 0
                rd = data[i][j].loc[:, k].values
                if gib1_res is not None and i == 'Low Temp' and\
                        k not in pc_check_list:
                    sfc_well = params['SFC'][j]
                    drfu_well = params['DRFU_array'][i][j]
                    ct_high = gib1_res['Ct_array']['High Temp'][j][k]
                    if not isinstance(ct_high, str) and ct_high > 0 and\
                            ct_high < 35:
                        cr_well = 1.4
                    else:
                        cr_well = params['CR'][j]
                elif k in pc_check_list:
                    sfc_well = params['SFC_pc'][j]
                    drfu_well = params['drfu_array_pc'][i][j]
                    cr_well = params['CR_pc'][j]
                else:
                    sfc_well = params['SFC'][j]
                    drfu_well = params['DRFU_array'][i][j]
                    cr_well = params['CR'][j]

                if (not params['gib1_switch'] and i == 'Low Temp') or (
                        params['gib1_switch'] and gib1_res is not None):
                    if rd[-1] - np.min(rd[sfc_well:]) < drfu_well and fb == 0:
                        result_data_dict['result'][i][j][k] = 1
                        result_data_dict['data_process_num'][i][j][k] = 1
                        end_rfu = get_end_rfu(rd, sfc_well)
                    else:
                        rd_high = data['High Temp'][j].loc[:, k].values
                        mudt_rd = rd - cr_well * rd_high
                        mudt_dict[i][j].loc[:, k] = mudt_rd
                        end_rfu = get_end_rfu(mudt_rd, sfc_well)
                else:
                    end_rfu = get_end_rfu(rd, sfc_well)
                result_data_dict['end_rfu'][i][j][k] = end_rfu
    return mudt_dict, result_data_dict
