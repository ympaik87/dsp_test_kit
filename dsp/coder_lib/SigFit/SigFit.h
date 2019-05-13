/*
 * SigFit.h
 *
 * Code generation for function 'SigFit'
 *
 */

#ifndef SIGFIT_H
#define SIGFIT_H

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

  extern void SigFit(const double x[45], const double ABSD[45], double *result,
                     const double ini_param[4], double *SC, double TC, double
                     HTC, double SFC, const double perturbation[60], double
                     param_data[], int param_size[2], double f[45]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (SigFit.h) */
