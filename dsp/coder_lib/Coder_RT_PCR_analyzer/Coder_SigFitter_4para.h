/*
 * Coder_SigFitter_4para.h
 *
 * Code generation for function 'Coder_SigFitter_4para'
 *
 */

#ifndef CODER_SIGFITTER_4PARA_H
#define CODER_SIGFITTER_4PARA_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_SigFitter_4para(const double x_data[], const int x_size[1],
    const double y_data[], const int y_size[1], const double param0[4], double
    param[4], double *iter, double *state);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_SigFitter_4para.h) */
