from cffi import FFI
import copy
import platform
import numpy as np
import pandas as pd
from dsp.call_coder_main import coder_main
from dsp.call_mudt import muDT


# # Inverse of Logistic Function - calculate Ct
def sig_inv(X, a, b, c, d):
    return c - np.log10((b - X) / (X - a)) / d


def load_lib(is_raw, is_dev):
    if is_dev and is_raw:
        c_fun = r'''
void AutoBaseline_v2_initialize();
void AutoBaseline_v2_terminate();
void AutoBaseline_v2(const double *x_data, const int *x_size, double *RD_data,
                 int *RD_size, const double *perturbation_data, const int
                 *perturbation_size, double SFC, double MFC, double DRFU,
                 double Thrd, double RPC, double RC, double dfM, double dfC,
                 double PMC, double FB, double AR, double isPC, const double
                 *ver_array_data, const int *ver_array_size, double DS,
                 double *result_well, double *DataProcessNum, double
                 *DataProcess_data, int *DataProcess_size, double
                 *LSR_val, double *RD_diff_data, int *RD_diff_size,
                 double *ivd_cdd_data, int *ivd_cdd_size, double *cff,
                 double *scd_fit_data, int *scd_fit_size, double *R_p2,
                 double *EFC, double *ABSD_orig_data, int *ABSD_orig_size,
                 double *ABSD_data, int *ABSD_size, double *f_data, int
                 *f_size, double *f_new_data, int *f_new_size, double
                 *sht, double *sht2, double *param, double *param_new,
                 double *R2, double *EndRFU, double *df);
'''
        ffi = FFI()
        ffi.cdef(c_fun)
        if '32bit' in platform.architecture():
            lib = ffi.dlopen(
                'dsp/coder_lib/AutoBaseline_v2/AutoBaseline_v2.so')
        else:
            lib = ffi.dlopen(
                'dsp/coder_lib/AutoBaseline_v2/AutoBaseline_v2.dll')
    elif is_raw:
        c_fun = r'''
void AutoBaseline_v1_initialize();
void AutoBaseline_v1_terminate();
void AutoBaseline_v1(const double *x_data, const int *x_size, double
  *RD_data, int *RD_size, const double *perturbation_data, const int
  *perturbation_size, double SFC, double MFC, double DRFU, double Thrd, double
  RPC, double RC, double dfM, double dfC, double PMC, double FB, double AR,
  double isPC, double LinearFilter_type, double ABSD_corrector_ver, double
  AsymmSigFit_ver, double UseStrangePatternCorrector, double *result_well,
  double *DataProcessNum, double *DataProcess_data, int *DataProcess_size,
  double *LSR_val, double *RD_diff_data, int *RD_diff_size, double
  *ivd_cdd_ouput_data, int *ivd_cdd_ouput_size, double *cff, double
  *scd_fit_data, int *scd_fit_size, double *R_p2, double *EFC, double
  *ABSD_orig_data, int *ABSD_orig_size, double *ABSD_data, int *ABSD_size,
  double *f_data, int *f_size, double *f_new_data, int *f_new_size, double
  *sht, double *sht2, double *param, double *param_new, double *R2, double
  *EndRFU, double *df);
'''

        ffi = FFI()
        ffi.cdef(c_fun)
        if '32bit' in platform.architecture():
            lib = ffi.dlopen(
                'dsp/coder_lib/AutoBaseline_v1/AutoBaseline_v1.so')
        else:
            lib = ffi.dlopen(
                'dsp/coder_lib/AutoBaseline_v1/AutoBaseline_v1.dll')
    else:
        c_fun = r'''
void Coder_RT_PCR_analyzer_v2_1_initialize();
void Coder_RT_PCR_analyzer_v2_1_terminate();
void Coder_RT_PCR_analyzer_v2_1(const double *x_data, const int *x_size, double
  *RD_data, int *RD_size, const double *perturbation_data, const int
  *perturbation_size, double SFC, double MFC, double DRFU, double Thrd, double
  RPC, double RC, double dfM, double dfC, double PMC, double FB, double AR,
  double isPC, const double *ver_array_data, const int *ver_array_size,
  double DS, double *result_well, double *DataProcessNum,
  double *DataProcess_data, int *DataProcess_size, double *LSR_val,
  double *RD_diff_data, int *RD_diff_size, double *ivd_cdd_ouput_data,
  int *ivd_cdd_ouput_size, double *cff, double *scd_fit_data,
  int *scd_fit_size, double *R_p2, double *EFC, double *ABSD_orig_data,
  int *ABSD_orig_size, double *ABSD_data, int *ABSD_size, double *f_data,
  int *f_size, double *f_new_data, int *f_new_size, double *sht,
  double *sht2, double *param, double *param_new, double *R2, double *EndRFU,
  double *df);
'''

        ffi = FFI()
        ffi.cdef(c_fun)
        if '32bit' in platform.architecture():
            lib = ffi.dlopen('dsp/coder_lib/Coder_RT_PCR_analyzer_v2_1/'
                             'Coder_RT_PCR_analyzer_v2_1.so')
        else:
            lib = ffi.dlopen('dsp/coder_lib/Coder_RT_PCR_analyzer_v2_1/'
                             'Coder_RT_PCR_analyzer_v2_1.dll')
    return ffi, lib


def rt_pcr_analyzer(mudt_dict, pc_check_list, result_data_dict, params, ar=1,
                    linear_filter_type=0, is_raw=False):
    is_dev = params['is_dev']
    ffi, lib = load_lib(is_raw, is_dev)
    ver_array = params['ver_array']
    ds = params['ds']
    print('ver_array >>> ', ver_array, 'ds >>> ', ds)
    for p in ['DataProcess_array', 'LSR_val_array', 'RD_diff_array',
              'ivd_cdd_array', 'cff_array', 'scd_fit_array', 'R_p2_array',
              'EFC_array', 'ABSD_orig_array', 'ABSD_array', 'f_array',
              'f_new_array', 'param_array', 'param_new_array', 'R2_array',
              'df_array', 'Ct_array', 'Qt_array']:
        result_data_dict[p] = {
            'Low Temp': {'FAM': {}, 'HEX': {}, 'Cal Red 610': {},
                         'Quasar 670': {}, 'Quasar 705': {}},
            'High Temp': {'FAM': {}, 'HEX': {}, 'Cal Red 610': {},
                          'Quasar 670': {}, 'Quasar 705': {}}
        }
    for i in ['High Temp', 'Low Temp']:
        if params['gib1_switch'] and i == 'Low Temp':
            mudt_dict, gi_low_result_dict = muDT(mudt_dict, params,
                                                 pc_check_list,
                                                 gib1_res=result_data_dict)
            for key in gi_low_result_dict.keys():
                result_data_dict[key]['Low Temp'] =\
                    gi_low_result_dict[key]['Low Temp']
        for j in mudt_dict[i].keys():
            if params['used_temp'][i][j] != 1:
                continue
            pmc_well = params['PMC'][j]
            for k in mudt_dict[i][j].columns:
                if result_data_dict['result'][i][j][k] != 0 and not is_raw:
                    continue
                rd = mudt_dict[i][j].loc[:, k].values
                if k in pc_check_list:
                    sfc_well = params['SFC_pc'][j]
                    mfc_well = params['MFC_pc'][j]
                    drfu_well = params['drfu_array_pc'][i][j]
                    thrd_well = params['Thrd_array_pc'][i][j]
                    rpc_well = params['rpc_array_pc'][i][j]
                    rc_well = params['rc_array_pc'][i][j]
                    dfm_well = params['dfM_array_pc'][i][j]
                    dfc_well = params['dfC_array_pc'][i][j]
                    isPC = 1
                    if is_dev:
                        ver_array[0] = params['absd_corrector_ver']['PC']
                        ver_array[1] = params['asymm_sigfit_ver']['PC']
                    else:
                        absd_corrector_ver = params['absd_corrector_ver']['PC']
                        asymm_sigfit_ver = params['asymm_sigfit_ver']['PC']
                    if sfc_well != params['SFC'][j] or\
                            mfc_well != params['MFC'][j]:
                        fb = 1
                    else:
                        fb = 0
                else:
                    sfc_well = params['SFC'][j]
                    mfc_well = params['MFC'][j]
                    drfu_well = params['DRFU_array'][i][j]
                    thrd_well = params['Thrd_array'][i][j]
                    rpc_well = params['RPC_array'][i][j]
                    rc_well = params['RC_array'][i][j]
                    dfm_well = params['dfM_array'][i][j]
                    dfc_well = params['dfC_array'][i][j]
                    if is_dev:
                        ver_array[0] = params['absd_corrector_ver']['sample']
                        ver_array[1] = params['asymm_sigfit_ver']['sample']
                    else:
                        absd_corrector_ver = params[
                            'absd_corrector_ver']['sample']
                        asymm_sigfit_ver = params['asymm_sigfit_ver']['sample']
                    isPC = 0
                    fb = 0
                if params['gip'] and k in pc_check_list and\
                        j == params['dye_li'][3] and i == 'Low Temp':
                    if is_dev:
                        ver_array[2] = 1
                    else:
                        use_strange_pattern_corr = 1
                else:
                    if is_dev:
                        ver_array[2] = 0
                    else:
                        use_strange_pattern_corr = 0
                if is_raw and not is_dev:
                    (result, data_process_num, data_process, lsr_val, rd_diff,
                     ivd_cdd, cff, scd_fit, r_p2, efc, absd_orig, absd, f,
                     f_new, sht, sht2, param, param_new, r2, end_rfu,
                     df) = coder_main(
                         ffi, lib, rd, sfc_well, mfc_well, drfu_well,
                         thrd_well, rpc_well, rc_well, dfm_well, dfc_well,
                         pmc_well, fb, ar, isPC, ver_array, ds,
                         linear_filter_type=linear_filter_type,
                         absd_corrector_ver=absd_corrector_ver,
                         asymm_sigfit_ver=asymm_sigfit_ver,
                         use_strange_pattern_corr=use_strange_pattern_corr,
                         is_raw=is_raw, is_dev=is_dev)
                else:
                    (result, data_process_num, data_process, lsr_val, rd_diff,
                     ivd_cdd, cff, scd_fit, r_p2, efc, absd_orig, absd, f,
                     f_new, sht, sht2, param, param_new, r2, end_rfu,
                     df) = coder_main(
                        ffi, lib, rd, sfc_well, mfc_well, drfu_well,
                        thrd_well, rpc_well, rc_well, dfm_well, dfc_well,
                        pmc_well, fb, ar, isPC, ver_array, ds,
                        is_raw=is_raw, is_dev=is_dev)

                if result <= 0 and is_raw is False:
                    if result == -2:
                        ct = sig_inv(thrd_well+sht2, *param_new)
                    else:
                        ct = sig_inv(thrd_well+sht, *param)
                else:
                    ct = 'Neg'

                result_data_dict['result'][i][j][k] = result
                result_data_dict['data_process_num'][i][j][k] =\
                    data_process_num
                result_data_dict['DataProcess_array'][i][j][k] =\
                    pd.DataFrame(data_process).T
                result_data_dict['LSR_val_array'][i][j][k] = lsr_val
                result_data_dict['RD_diff_array'][i][j][k] = rd_diff
                result_data_dict['ivd_cdd_array'][i][j][k] = ivd_cdd
                result_data_dict['cff_array'][i][j][k] = cff
                result_data_dict['scd_fit_array'][i][j][k] = scd_fit
                result_data_dict['R_p2_array'][i][j][k] = r_p2
                result_data_dict['EFC_array'][i][j][k] = efc
                result_data_dict['ABSD_orig_array'][i][j][k] = absd_orig
                result_data_dict['ABSD_array'][i][j][k] = absd
                result_data_dict['f_array'][i][j][k] = f
                result_data_dict['f_new_array'][i][j][k] = f_new
                result_data_dict['param_array'][i][j][k] = param
                result_data_dict['param_new_array'][i][j][k] = param_new
                result_data_dict['R2_array'][i][j][k] = r2
                result_data_dict['end_rfu'][i][j][k] = end_rfu
                result_data_dict['df_array'][i][j][k] = df
                result_data_dict['Ct_array'][i][j][k] = ct
    if is_raw:
        result_data_dict['Ct_array_final'] = copy.deepcopy(
            result_data_dict['Ct_array'])
    return result_data_dict
