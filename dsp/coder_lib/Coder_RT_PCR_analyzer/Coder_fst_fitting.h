/*
 * Coder_fst_fitting.h
 *
 * Code generation for function 'Coder_fst_fitting'
 *
 */

#ifndef CODER_FST_FITTING_H
#define CODER_FST_FITTING_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_fst_fitting(const emxArray_real_T *x, const double y_data[],
    const int y_size[1], double n, double *coeff1, double *coeff2, double
    *coeff3);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_fst_fitting.h) */
