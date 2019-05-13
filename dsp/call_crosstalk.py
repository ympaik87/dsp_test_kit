import copy
from dsp.call_rt_pcr_analyzer import sig_inv


def temp_map(abbreviation):
    if abbreviation == 'H':
        return 'High Temp'
    else:
        return 'Low Temp'


def crosstalk(result_dict, pc_check_list, params):
    crosstalk_li = params['crosstalk']
    if crosstalk_li:
        for parameter in crosstalk_li:
            dye_from, temp_from_temp = parameter[0].split('_')
            dye_to, temp_to_temp = parameter[1].split('_')
            crosstalk_ct_thr = float(parameter[3])
            temp_from = temp_map(temp_from_temp)
            temp_to = temp_map(temp_to_temp)
            crosstalk_thr = max(float(parameter[2]),
                                params['DRFU_array'][temp_to][dye_to])
            for well in result_dict['result'][temp_from][dye_from].keys():
                crosstalk_res_from = result_dict[
                    'result'][temp_from][dye_from][well]
                crosstalk_res_to = result_dict['result'][temp_to][dye_to][well]
                if ((well not in pc_check_list) and (
                        crosstalk_res_from <= 0 and crosstalk_res_to <= 0)):
                    if result_dict[
                            'end_rfu'][temp_to][dye_to][well] <= crosstalk_thr:
                        result_dict['result'][temp_to][dye_to][well] = 4
                        result_dict['data_process_num'][temp_to][dye_to][
                            well] = 8
                        result_dict['Ct_array_final'][temp_to][dye_to][well] =\
                            'Neg'
                    else:
                        if crosstalk_res_to == -2:
                            coef = result_dict[
                                'param_new_array'][temp_to][dye_to][well]
                            shift = result_dict[
                                'f_new_array'][temp_to][dye_to][well][0]
                        else:
                            coef = result_dict[
                                'param_array'][temp_to][dye_to][well]
                            shift = result_dict[
                                'f_array'][temp_to][dye_to][well][0]
                        result_dict['Ct_array_final'][temp_to][dye_to][well] =\
                            sig_inv(crosstalk_ct_thr + shift, *coef)
    if params['gi_switch']:
        dye_from = 'FAM'
        dye_to = 'HEX'
        temp = 'High Temp'
        for well in result_dict['result'][temp][dye_from].keys():
            if well not in pc_check_list and\
                result_dict['result'][temp][dye_to][well] <= 0 and\
                    result_dict['result'][temp][dye_from][well] <= 0 and\
                    result_dict['end_rfu'][temp][dye_to][well] <= 250:
                result_dict['result'][temp][dye_to][well] = 4
                result_dict['data_process_num'][temp][dye_to][well] = 8
                result_dict['Ct_array_final'][temp][dye_to][well] = 'Neg'

    return result_dict


def crosstalk_filter(sig_fit_data, result, pos_well_dic, neg_well_dic,
                     pc_check_list, ct, sig_fit_coef, crosstalk_thr=200,
                     dye_from='Quasar 705', dye_to='Quasar 670',
                     crosstalk_temp='Low Temp', crosstalk_ct_thr=200):
    print('deprecated')
    print('>>>>>>>>>>>>>>>>>>>>>>>>>')
    print('crosstalk thresh: ', crosstalk_thr, 'crosstalk from', dye_from,
          'crosstalk to', dye_to)
    print('>>>>>>>>>>>>>>>>>>>>>>>>>')
    pos_well_dic_temp = copy.deepcopy(pos_well_dic)
    crosstalk_thr_dict = {}
    for k in pos_well_dic[crosstalk_temp][dye_from]:
        if (k not in pc_check_list) and (
            result[dye_from].loc[crosstalk_temp, k] <= 0 and
                result[dye_to].loc[crosstalk_temp, k]) <= 0:
            if sig_fit_data[crosstalk_temp][dye_to][k][-1] - sig_fit_data[
                    crosstalk_temp][dye_to][k][0] <= crosstalk_thr:
                result[dye_to].loc[crosstalk_temp, k] = 8
                neg_well_dic[crosstalk_temp][dye_to].append(k)
                ind = pos_well_dic_temp[crosstalk_temp][dye_to].index(k)
                del pos_well_dic_temp[crosstalk_temp][dye_to][ind]
            else:
                crosstalk_thr_dict[k] = crosstalk_ct_thr
                coef = sig_fit_coef[crosstalk_temp][dye_to][k]
                ct[crosstalk_temp][dye_to][k] = sig_inv(
                    sig_fit_data[crosstalk_temp][dye_to][k][0] +
                    crosstalk_ct_thr, *coef)
    return result, pos_well_dic_temp, neg_well_dic, ct, crosstalk_thr_dict
