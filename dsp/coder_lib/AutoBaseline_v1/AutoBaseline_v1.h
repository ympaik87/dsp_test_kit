/*
 * AutoBaseline_v1.h
 *
 * Code generation for function 'AutoBaseline_v1'
 *
 */

#ifndef AUTOBASELINE_V1_H
#define AUTOBASELINE_V1_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "AutoBaseline_v1_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void AutoBaseline_v1(const double x_data[], const int x_size[1], double
    RD_data[], int RD_size[1], const double perturbation_data[], const int
    perturbation_size[1], double SFC, double MFC, double DRFU, double Thrd,
    double RPC, double RC, double dfM, double dfC, double PMC, double FB, double
    AR, double isPC, double LinearFilter_type, double ABSD_corrector_ver, double
    AsymmSigFit_ver, double UseStrangePatternCorrector, double *result_well,
    double *DataProcessNum, double DataProcess_data[], int DataProcess_size[2],
    double *LSR_val, double RD_diff_data[], int RD_diff_size[1], double
    ivd_cdd_data[], int ivd_cdd_size[2], double cff[2], double scd_fit_data[],
    int scd_fit_size[1], double *R_p2, double *EFC, double ABSD_orig_data[], int
    ABSD_orig_size[1], double ABSD_data[], int ABSD_size[1], double f_data[],
    int f_size[1], double f_new_data[], int f_new_size[1], double *sht, double
    *sht2, double param[4], double param_new[4], double *R2, double *EndRFU,
    double *df);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (AutoBaseline_v1.h) */
