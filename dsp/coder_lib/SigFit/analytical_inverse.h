/*
 * analytical_inverse.h
 *
 * Code generation for function 'analytical_inverse'
 *
 */

#ifndef ANALYTICAL_INVERSE_H
#define ANALYTICAL_INVERSE_H

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

  extern void analytical_inverse(const double a[16], double inv_a[16]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (analytical_inverse.h) */
