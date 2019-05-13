/*
 * Coder_baseline.h
 *
 * Code generation for function 'Coder_baseline'
 *
 */

#ifndef CODER_BASELINE_H
#define CODER_BASELINE_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_baseline(const emxArray_real_T *xdata, const emxArray_real_T
    *xdata2, const double RD_data[], double joint_pt, double LinearOrNot, double
    TC, double scd_fit_data[], int scd_fit_size[1], double cff[2]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_baseline.h) */
