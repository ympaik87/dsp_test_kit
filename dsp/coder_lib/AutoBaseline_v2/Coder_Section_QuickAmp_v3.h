/*
 * Coder_Section_QuickAmp_v3.h
 *
 * Code generation for function 'Coder_Section_QuickAmp_v3'
 *
 */

#ifndef CODER_SECTION_QUICKAMP_V3_H
#define CODER_SECTION_QUICKAMP_V3_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "AutoBaseline_v2_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_Section_QuickAmp_v3(const double x_data[], const int x_size
    [1], const double RD_data[], const int RD_size[1], double SFC, double *EFC,
    double HTC, double TC, double *result_well, double AR, double FB, double
    *EFC0, double cff[2], double scd_fit_data[], int scd_fit_size[1], double
    ABSD_data[], int ABSD_size[1], double ABSD_orig_data[], int ABSD_orig_size[1],
    double *R_p2, double *SRFU);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_Section_QuickAmp_v3.h) */
