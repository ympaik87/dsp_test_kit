/*
 * Coder_Section_Baseline_v4.h
 *
 * Code generation for function 'Coder_Section_Baseline_v4'
 *
 */

#ifndef CODER_SECTION_BASELINE_V4_H
#define CODER_SECTION_BASELINE_V4_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_Section_Baseline_v4(const double x_data[], const int x_size
    [1], const double RD_data[], const int RD_size[1], double SFC, double MFC,
    double *EFC, double TC, double DRFU, double LinearOrNot, double AR, double
    FB, double *EFC0, double cff[2], double scd_fit_data[], int scd_fit_size[1]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_Section_Baseline_v4.h) */
