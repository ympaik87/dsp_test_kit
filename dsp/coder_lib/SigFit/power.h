/*
 * power.h
 *
 * Code generation for function 'power'
 *
 */

#ifndef POWER_H
#define POWER_H

/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "SigFit_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void b_power(const double a_data[], const int a_size[1], double y_data[],
                      int y_size[1]);
  extern void power(const double b_data[], const int b_size[1], double y_data[],
                    int y_size[1]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (power.h) */
