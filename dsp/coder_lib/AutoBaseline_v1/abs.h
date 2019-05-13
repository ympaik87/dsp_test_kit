/*
 * abs.h
 *
 * Code generation for function 'abs'
 *
 */

#ifndef ABS_H
#define ABS_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "AutoBaseline_v1_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void b_abs(const double x_data[], const int x_size[1], double y_data[],
                    int y_size[1]);
  extern void c_abs(const emxArray_real_T *x, emxArray_real_T *y);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (abs.h) */
