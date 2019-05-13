/*
 * isfinite.h
 *
 * Code generation for function 'isfinite'
 *
 */

#ifndef ISFINITE_H
#define ISFINITE_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void b_isfinite(const double x[4], boolean_T b[4]);
  extern void c_isfinite(const double x[2], boolean_T b[2]);
  extern void d_isfinite(const double x[3], boolean_T b[3]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (isfinite.h) */
