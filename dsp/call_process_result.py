import numpy as np
import copy
from dsp.call_rt_pcr_analyzer import sig_inv


def process_result(result_dict, nc_check_list, params, pc_check_list):
    result_dict['Ct_array_final'] = copy.deepcopy(result_dict['Ct_array'])
    result_dict['result_array_orig'] = copy.deepcopy(result_dict['result'])
    for temp in result_dict['result'].keys():
        for dye in result_dict['result'][temp].keys():
            if params['used_temp'][temp][dye] != 1:
                continue
            for well in result_dict['result'][temp][dye].keys():
                result = result_dict['result'][temp][dye][well]
                if result > 0:
                    continue

                if well in nc_check_list:
                    cco = params['cut_nc'][temp][dye]
                else:
                    cco = params['cut'][temp][dye]

                if cco > 0 and result_dict['Ct_array'][temp][dye][well] > cco:
                    result_dict['result'][temp][dye][well] = 4
                    result_dict['data_process_num'][temp][dye][well] = 12
                    result_dict['Ct_array_final'][temp][dye][well] = 'Neg'

                if well not in pc_check_list and temp == 'Low Temp' and\
                        result_dict['result']['High Temp'][dye][well] <= 0 and\
                        result_dict['end_rfu'][temp][dye][well] < params[
                            'PTP'][dye]:
                    result_dict['result'][temp][dye][well] = 4
                    result_dict['data_process_num'][temp][dye][well] = 11
                    result_dict['Ct_array_final'][temp][dye][well] = 'Neg'

                if well not in pc_check_list and temp == 'High Temp' or (
                    temp == 'Low Temp' and params['used_temp'][temp][dye] == 1
                        and params['used_temp']['High Temp'][dye] == 0):
                    if result_dict['Ct_array'][temp][dye][well] < 30 and\
                        result_dict['end_rfu'][temp][dye][well] < params[
                            'drfu3'][dye]:
                        result_dict['result'][temp][dye][well] = 4
                        result_dict['data_process_num'][temp][dye][well] = 15
                        result_dict['Ct_array_final'][temp][dye][well] = 'Neg'

                ivd_cdd = result_dict['ivd_cdd_array'][temp][dye][well]
                if np.any(ivd_cdd):
                    if result == -2:
                        y = result_dict['end_rfu'][temp][dye][well] * 0.05 +\
                            result_dict['f_new_array'][temp][dye][well][0]
                        p = result_dict['param_new_array'][temp][dye][well]
                        psd_ct = sig_inv(y, *p)
                    else:
                        y = result_dict['end_rfu'][temp][dye][well] * 0.05 +\
                            result_dict['f_array'][temp][dye][well][0]
                        p = result_dict['param_array'][temp][dye][well]
                        psd_ct = sig_inv(y, *p)
                    if np.min(np.absolute(ivd_cdd - psd_ct)) < 10:
                        result_dict['result'][temp][dye][well] = 4
                        result_dict['data_process_num'][temp][dye][well] = 14
                        result_dict['Ct_array_final'][temp][dye][well] =\
                            'N-invalid'

    return result_dict
