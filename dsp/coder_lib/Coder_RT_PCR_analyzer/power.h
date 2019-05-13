/*
 * power.h
 *
 * Code generation for function 'power'
 *
 */

#ifndef POWER_H
#define POWER_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void b_power(const double b_data[], const int b_size[1], double y_data[],
                      int y_size[1]);
  extern void power(const emxArray_real_T *a, emxArray_real_T *y);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (power.h) */
