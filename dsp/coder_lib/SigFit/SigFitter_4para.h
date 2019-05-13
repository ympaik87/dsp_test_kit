/*
 * SigFitter_4para.h
 *
 * Code generation for function 'SigFitter_4para'
 *
 */

#ifndef SIGFITTER_4PARA_H
#define SIGFITTER_4PARA_H

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

  extern void SigFitter_4para(const double x_data[], const int x_size[1], const
    double y_data[], const int y_size[1], const double param0[4], double param[4],
    double *iter, double *state);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (SigFitter_4para.h) */
