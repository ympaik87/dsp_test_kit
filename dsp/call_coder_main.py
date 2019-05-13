import numpy as np


def coder_main(ffi, lib, rd, sfc, mfc, drfu, thrd, rpc, rc, dfm, dfc, pmc, fb,
               ar, isPC, ver_array, ds, linear_filter_type=0,
               absd_corrector_ver=0, asymm_sigfit_ver=0,
               use_strange_pattern_corr=0, is_raw=False, is_dev=False):
    tc = len(rd)
    x = np.arange(tc, dtype=np.double) + 1
    x_size = np.array(tc, dtype=np.int)
    rd_double = rd.astype(np.double)
    rd_size = np.array(tc, dtype=np.int)
    perturbation = [-0.973887413504278, -0.110752218653671, 0.160699562466992,
                    -0.644889274473602, -0.018125281526274, 0.590554975652358,
                    -0.625871042861732, -0.290699579405774, 0.707632183035461,
                    0.493605590018377, -0.962878742214856, -0.443471247668919,
                    -0.847794438782257, -0.857560273531816, 0.967830592458299,
                    0.116745163748027, 0.969532659394824, -0.981055506702110,
                    0.050028697239221, -0.245296519153717, 0.626082481392944,
                    0.203827850667666, -0.302623248607972, 0.804378454357277,
                    0.890148861159393, -0.274586077266959, -0.279877290719269,
                    0.147205471435370, -0.291978057354608, 0.964218805023992,
                    0.551823868826120, 0.052402395588429, -0.361970815404932,
                    0.860029768957567, 0.636182425493212, 0.581817944259895,
                    -0.910055071542625, -0.177627328575209, 0.414410507056751,
                    0.291525994457497, 0.732757144429248, -0.596450357440851,
                    -0.642559842170460, 0.504304538661243, 0.968906790541170,
                    0.092792879205106, 0.146682672383501, 0.257989040987623,
                    -0.149529273282368, -0.170386694574138, -0.446112073194293,
                    0.463943469623122, -0.815304004788998, -0.584392468847689,
                    -0.557109060608796, -0.709415933086974, 0.005138064334786,
                    -0.790579900074406, -0.760640900404956, -0.899048492331474]
    perturbation_double = np.array(perturbation[:tc], dtype=np.double)
    perturbation_size = np.array(tc, dtype=np.int)
    sfc_double = np.array(sfc, dtype=np.double)
    mfc_double = np.array(mfc, dtype=np.double)
    drfu_double = np.array(drfu, dtype=np.double)
    thrd_double = np.array(thrd, dtype=np.double)
    rpc_double = np.array(rpc, dtype=np.double)
    rc_double = np.array(rc, dtype=np.double)
    dfm_double = np.array(dfm, dtype=np.double)
    dfc_double = np.array(dfc, dtype=np.double)
    pmc_double = np.array(pmc, dtype=np.double)
    fb_double = np.array(fb, dtype=np.double)
    ar_double = np.array(ar, dtype=np.double)
    isPC_double = np.array(isPC, dtype=np.double)
    ver_array_double = np.array(ver_array, dtype=np.double)
    ver_array_size_int = np.array(20, dtype=np.int)
    ds_double = np.array(ds, dtype=np.double)
    if is_raw and not is_dev:
        linear_filter_type_double = np.array(linear_filter_type,
                                             dtype=np.double)
        absd_corrector_ver_double = np.array(absd_corrector_ver,
                                             dtype=np.double)
        asymm_sigfit_ver_double = np.array(asymm_sigfit_ver, dtype=np.double)
        use_strange_pattern_corr_double = np.array(use_strange_pattern_corr,
                                                   dtype=np.double)
    result_double = np.array(0, dtype=np.double)
    data_process_num_double = np.array(0, dtype=np.double)
    data_process_data = np.zeros([8, tc], dtype=np.double)
    data_process_size = np.zeros(2, dtype=np.int)
    lsr_val = np.array(0, dtype=np.double)
    rd_diff = np.zeros(tc, dtype=np.double)
    rd_diff_size = np.array(tc, dtype=np.int)
    ivd_cdd = np.zeros(100).astype(np.double)
    ivd_cdd_size = np.array([1, 100], dtype=np.int)
    cff = np.zeros(2, dtype=np.double)
    scd_fit = np.zeros(tc, dtype=np.double)
    scd_fit_size = np.array(tc, dtype=np.int)
    r_p2 = np.array(0, dtype=np.double)
    efc = np.array(0, dtype=np.double)
    absd_orig = np.zeros(tc, dtype=np.double)
    absd_orig_size = np.array(tc, dtype=np.int)
    absd = np.zeros(tc, dtype=np.double)
    absd_size = np.array(tc, dtype=np.int)
    f = np.zeros(tc, dtype=np.double)
    f_size = np.array(tc, dtype=np.int)
    f_new = np.zeros(tc, dtype=np.double)
    f_new_size = np.array(tc, dtype=np.int)
    sht = np.array(0, dtype=np.double)
    sht2 = np.array(0, dtype=np.double)
    param = np.zeros(4, dtype=np.double)
    param_new = np.zeros(4, dtype=np.double)
    r2 = np.array(0, dtype=np.double)
    end_rfu = np.array(0, dtype=np.double)
    df = np.array(0, dtype=np.double)

    pointer_x = ffi.cast('double*', ffi.from_buffer(x))
    pointer_x_size = ffi.cast('int*', ffi.from_buffer(x_size))
    pointer_rd = ffi.cast('double*', ffi.from_buffer(rd_double))
    pointer_rd_size = ffi.cast('int*', ffi.from_buffer(rd_size))
    pointer_perturbation = ffi.cast('double*',
                                    ffi.from_buffer(perturbation_double))
    pointer_perturbation_size = ffi.cast('int*',
                                         ffi.from_buffer(perturbation_size))
    pointer_ver_array = ffi.cast('double*', ffi.from_buffer(ver_array_double))
    pointer_ver_array_size = ffi.cast(
        'int*', ffi.from_buffer(ver_array_size_int))
    pointer_result = ffi.cast('double*', ffi.from_buffer(result_double))
    pointer_data_process_num = ffi.cast(
        'double*', ffi.from_buffer(data_process_num_double))
    pointer_data_process_data = ffi.cast(
        'double*', ffi.from_buffer(data_process_data))
    pointer_data_process_size = ffi.cast(
        'int*', ffi.from_buffer(data_process_size))
    pointer_lsr_val = ffi.cast('double*', ffi.from_buffer(lsr_val))
    pointer_rd_diff = ffi.cast('double*', ffi.from_buffer(rd_diff))
    pointer_rd_diff_size = ffi.cast('int*', ffi.from_buffer(rd_diff_size))
    pointer_ivd_cdd = ffi.cast('double*', ffi.from_buffer(ivd_cdd))
    pointer_ivd_cdd_size = ffi.cast('int*', ffi.from_buffer(ivd_cdd_size))
    pointer_cff = ffi.cast('double*', ffi.from_buffer(cff))
    pointer_scd_fit_data = ffi.cast('double*', ffi.from_buffer(scd_fit))
    pointer_scd_fit_size = ffi.cast('int*', ffi.from_buffer(scd_fit_size))
    pointer_r_p2 = ffi.cast('double*', ffi.from_buffer(r_p2))
    pointer_efc = ffi.cast('double*', ffi.from_buffer(efc))
    pointer_absd_orig_data = ffi.cast('double*', ffi.from_buffer(absd_orig))
    pointer_absd_orig_size = ffi.cast('int*', ffi.from_buffer(absd_orig_size))
    pointer_absd = ffi.cast('double*', ffi.from_buffer(absd))
    pointer_absd_size = ffi.cast('int*', ffi.from_buffer(absd_size))
    pointer_f = ffi.cast('double*', ffi.from_buffer(f))
    pointer_f_size = ffi.cast('int*', ffi.from_buffer(f_size))
    pointer_f_new = ffi.cast('double*', ffi.from_buffer(f_new))
    pointer_f_new_size = ffi.cast('int*', ffi.from_buffer(f_new_size))
    pointer_sht = ffi.cast('double*', ffi.from_buffer(sht))
    pointer_sht2 = ffi.cast('double*', ffi.from_buffer(sht2))
    pointer_param = ffi.cast('double*', ffi.from_buffer(param))
    pointer_param_new = ffi.cast('double*', ffi.from_buffer(param_new))
    pointer_r2 = ffi.cast('double*', ffi.from_buffer(r2))
    pointer_end_rfu = ffi.cast('double*', ffi.from_buffer(end_rfu))
    pointer_df = ffi.cast('double*', ffi.from_buffer(df))

    if is_dev and is_raw:
        lib.AutoBaseline_v2_initialize()
        lib.AutoBaseline_v2(
            pointer_x, pointer_x_size, pointer_rd, pointer_rd_size,
            pointer_perturbation, pointer_perturbation_size, sfc_double,
            mfc_double, drfu_double, thrd_double, rpc_double, rc_double,
            dfm_double, dfc_double, pmc_double, fb_double, ar_double,
            isPC_double, pointer_ver_array, pointer_ver_array_size, ds_double,
            pointer_result, pointer_data_process_num,
            pointer_data_process_data, pointer_data_process_size,
            pointer_lsr_val, pointer_rd_diff, pointer_rd_diff_size,
            pointer_ivd_cdd, pointer_ivd_cdd_size, pointer_cff,
            pointer_scd_fit_data, pointer_scd_fit_size, pointer_r_p2,
            pointer_efc, pointer_absd_orig_data, pointer_absd_orig_size,
            pointer_absd, pointer_absd_size, pointer_f, pointer_f_size,
            pointer_f_new, pointer_f_new_size, pointer_sht, pointer_sht2,
            pointer_param, pointer_param_new, pointer_r2, pointer_end_rfu,
            pointer_df)
        lib.AutoBaseline_v2_terminate()
    elif is_raw:
        lib.AutoBaseline_v1_initialize()
        lib.AutoBaseline_v1(
            pointer_x, pointer_x_size, pointer_rd, pointer_rd_size,
            pointer_perturbation, pointer_perturbation_size, sfc_double,
            mfc_double, drfu_double, thrd_double, rpc_double, rc_double,
            dfm_double, dfc_double, pmc_double, fb_double, ar_double,
            isPC_double, linear_filter_type_double, absd_corrector_ver_double,
            asymm_sigfit_ver_double, use_strange_pattern_corr_double,
            pointer_result, pointer_data_process_num,
            pointer_data_process_data, pointer_data_process_size,
            pointer_lsr_val, pointer_rd_diff, pointer_rd_diff_size,
            pointer_ivd_cdd, pointer_ivd_cdd_size, pointer_cff,
            pointer_scd_fit_data, pointer_scd_fit_size, pointer_r_p2,
            pointer_efc, pointer_absd_orig_data, pointer_absd_orig_size,
            pointer_absd, pointer_absd_size, pointer_f, pointer_f_size,
            pointer_f_new, pointer_f_new_size, pointer_sht, pointer_sht2,
            pointer_param, pointer_param_new, pointer_r2, pointer_end_rfu,
            pointer_df)
        lib.AutoBaseline_v1_terminate()
    else:
        lib.Coder_RT_PCR_analyzer_v2_1_initialize()
        lib.Coder_RT_PCR_analyzer_v2_1(
            pointer_x, pointer_x_size, pointer_rd, pointer_rd_size,
            pointer_perturbation, pointer_perturbation_size, sfc_double,
            mfc_double, drfu_double, thrd_double, rpc_double, rc_double,
            dfm_double, dfc_double, pmc_double, fb_double, ar_double,
            isPC_double, pointer_ver_array, pointer_ver_array_size, ds_double,
            pointer_result, pointer_data_process_num,
            pointer_data_process_data, pointer_data_process_size,
            pointer_lsr_val, pointer_rd_diff, pointer_rd_diff_size,
            pointer_ivd_cdd, pointer_ivd_cdd_size, pointer_cff,
            pointer_scd_fit_data, pointer_scd_fit_size, pointer_r_p2,
            pointer_efc, pointer_absd_orig_data, pointer_absd_orig_size,
            pointer_absd, pointer_absd_size, pointer_f, pointer_f_size,
            pointer_f_new, pointer_f_new_size, pointer_sht, pointer_sht2,
            pointer_param, pointer_param_new, pointer_r2, pointer_end_rfu,
            pointer_df)
        lib.Coder_RT_PCR_analyzer_v2_1_terminate()
    return (result_double, data_process_num_double, data_process_data, lsr_val,
            rd_diff, ivd_cdd, cff, scd_fit, r_p2, efc, absd_orig, absd, f,
            f_new, sht, sht2, param, param_new, r2, end_rfu, df)


if __name__ == '__main__':
    import pathlib
    from cffi import FFI, verifier
    from shutil import copyfile
    c_fun = r'''
void Coder_RT_PCR_analyzer_initialize();
void Coder_RT_PCR_analyzer_terminate();
void Coder_RT_PCR_analyzer(const double *x_data, const int *x_size, double
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

    filepath = r'\\14.32.167.236\기술혁신팀$\06-1. 데이터 분석관리_DSP\00_DSP_matalb_코드백업\00_sigmoid_fitting\DSP_subroutines\codegen\dll\Coder_RT_PCR_analyzer\Coder_RT_PCR_analyzer.dll'
    path = pathlib.Path(filepath)

    lib = ffi.dlopen(filepath)
    # copyfile(filepath, pathlib.Path('coder_lib')/path.name)
    rd = np.array([
        5.312380000000000, 5.307580000000000, 5.313250000000000,
        5.324199999999999, 5.330160000000000, 5.324910000000000,
        5.333620000000000, 5.339689999999999, 5.348560000000000,
        5.339340000000000, 5.350550000000000, 5.358310000000000,
        5.367560000000000, 5.396150000000000, 5.396240000000000,
        5.435510000000000, 5.469210000000000, 5.505280000000000,
        5.544070000000000, 5.589740000000000, 5.645070000000000,
        5.693250000000000, 5.754380000000000, 5.796680000000000,
        5.840109999999999, 5.892710000000000, 5.937370000000000,
        5.986140000000001, 6.010120000000000, 6.062690000000000,
        6.104080000000000, 6.145220000000000, 6.162730000000000,
        6.205620000000000, 6.233310000000000, 6.261150000000000,
        6.286359999999999, 6.310100000000000, 6.327529999999999,
        6.353569999999999
    ]) * 1000
    linear_filter_type = 1
    drfu = 110
    thrd = 110
    sfc = 4
    mfc = 12
    rpc = 0.85
    rc = 0.85
    dfm = 18
    dfc = 25
    pmc = 0.09
    ar = 1
    fb = 0
    isPC = 0
    (result_double, data_process_num_double, data_process_data, lsr_val,
     rd_diff, ivd_cdd, cff, scd_fit, r_p2, efc, absd_orig, absd, f, f_new, sht,
     sht2, param, param_new, r2, end_rfu, df) =\
        coder_main(rd, sfc, mfc, drfu, thrd, rpc, rc, dfm, dfc, pmc, fb, ar,
                   isPC, linear_filter_type, 0, 0, 0, lib)
    print('result out: ', result_double)
    print('data process num: ', data_process_num_double)
    print('data process data: ', data_process_data)
    print('lsr: ', lsr_val)
    print('rd_diff: ', rd_diff)
    print('ivd_cdd: ', ivd_cdd)
    print('cff: ', cff)
    print('scd_fit: ', scd_fit)
    print('r_p2: ', r_p2)
    print('efc: ', efc)
    print('absd orig: ', absd_orig)
    print('absd: ', absd)
    print('f: ', f)
    print('f_new: ', f_new)
    print('sht: ', sht)
    print('sht2: ', sht2)
    print('param: ', param)
    print('param new: ', param_new)
    print('r2: ', r2)
    print('end rfu: ', end_rfu)
    print('df: ', df)
    verifier.cleanup_tmpdir()
