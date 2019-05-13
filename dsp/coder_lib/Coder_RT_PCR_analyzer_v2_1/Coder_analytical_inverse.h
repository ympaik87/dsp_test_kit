/*
 * Coder_analytical_inverse.h
 *
 * Code generation for function 'Coder_analytical_inverse'
 *
 */

#ifndef CODER_ANALYTICAL_INVERSE_H
#define CODER_ANALYTICAL_INVERSE_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_v2_1_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_analytical_inverse(const double a[16], double inv_a[16]);
  extern void b_Coder_analytical_inverse(const double a[4], double inv_a[4]);
  extern void c_Coder_analytical_inverse(const double a[9], double inv_a[9]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_analytical_inverse.h) */
