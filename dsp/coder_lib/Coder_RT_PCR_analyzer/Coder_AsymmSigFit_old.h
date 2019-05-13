/*
 * Coder_AsymmSigFit_old.h
 *
 * Code generation for function 'Coder_AsymmSigFit_old'
 *
 */

#ifndef CODER_ASYMMSIGFIT_OLD_H
#define CODER_ASYMMSIGFIT_OLD_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_AsymmSigFit_old(const double x_data[], const int x_size[1],
    const double ABSD_data[], const int ABSD_size[1], double f_data[], int
    f_size[1], double *result_well, double *DataProcessNum, double param[4],
    double SFC, double MFC, double EFC0, double TC, double SRFU, double Thrd,
    double Max_DRFU_Thrd, double *sht, const double perturbation_data[], double
    f_new_data[], int f_new_size[1], double param_new[4], double *sht2);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_AsymmSigFit_old.h) */
