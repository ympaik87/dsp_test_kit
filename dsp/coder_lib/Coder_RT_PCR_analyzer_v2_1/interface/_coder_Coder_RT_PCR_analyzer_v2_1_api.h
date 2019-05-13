/*
 * _coder_Coder_RT_PCR_analyzer_v2_1_api.h
 *
 * Code generation for function '_coder_Coder_RT_PCR_analyzer_v2_1_api'
 *
 */

#ifndef _CODER_CODER_RT_PCR_ANALYZER_V2_1_API_H
#define _CODER_CODER_RT_PCR_ANALYZER_V2_1_API_H

/* Include files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_Coder_RT_PCR_analyzer_v2_1_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_RT_PCR_analyzer_v2_1(real_T x_data[], int32_T x_size[1],
    real_T RD_data[], int32_T RD_size[1], real_T perturbation_data[], int32_T
    perturbation_size[1], real_T SFC, real_T MFC, real_T DRFU, real_T Thrd,
    real_T RPC, real_T RC, real_T dfM, real_T dfC, real_T PMC, real_T FB, real_T
    AR, real_T isPC, real_T ver_array_data[], int32_T ver_array_size[1], real_T
    DS, real_T *result_well, real_T *DataProcessNum, real_T DataProcess_data[],
    int32_T DataProcess_size[2], real_T *LSR_val, real_T RD_diff_data[], int32_T
    RD_diff_size[1], real_T ivd_cdd_ouput_data[], int32_T ivd_cdd_ouput_size[2],
    real_T cff[2], real_T scd_fit_data[], int32_T scd_fit_size[1], real_T *R_p2,
    real_T *EFC, real_T ABSD_orig_data[], int32_T ABSD_orig_size[1], real_T
    ABSD_data[], int32_T ABSD_size[1], real_T f_data[], int32_T f_size[1],
    real_T f_new_data[], int32_T f_new_size[1], real_T *sht, real_T *sht2,
    real_T param[4], real_T param_new[4], real_T *R2, real_T *EndRFU, real_T *df);
  extern void Coder_RT_PCR_analyzer_v2_1_api(const mxArray * const prhs[17],
    int32_T nlhs, const mxArray *plhs[21]);
  extern void Coder_RT_PCR_analyzer_v2_1_atexit(void);
  extern void Coder_RT_PCR_analyzer_v2_1_initialize(void);
  extern void Coder_RT_PCR_analyzer_v2_1_terminate(void);
  extern void Coder_RT_PCR_analyzer_v2_1_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (_coder_Coder_RT_PCR_analyzer_v2_1_api.h) */
