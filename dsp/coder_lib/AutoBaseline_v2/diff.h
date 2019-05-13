/*
 * diff.h
 *
 * Code generation for function 'diff'
 *
 */

#ifndef DIFF_H
#define DIFF_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "AutoBaseline_v2_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void b_diff(const double x[6], double y[5]);
  extern void diff(const double x_data[], const int x_size[1], double y_data[],
                   int y_size[1]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (diff.h) */
