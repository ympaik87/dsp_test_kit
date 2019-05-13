/*
 * mean.h
 *
 * Code generation for function 'mean'
 *
 */

#ifndef MEAN_H
#define MEAN_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern double b_mean(const double x[2]);
  extern double c_mean(const emxArray_real_T *x);
  extern double d_mean(const double x[4]);
  extern double e_mean(const double x[5]);
  extern double mean(const double x[3]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (mean.h) */
