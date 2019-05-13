/*
 * Coder_multi_amp.h
 *
 * Code generation for function 'Coder_multi_amp'
 *
 */

#ifndef CODER_MULTI_AMP_H
#define CODER_MULTI_AMP_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_multi_amp(const double fst_val_data[], const double
    ABSD_data[], const int ABSD_size[1], double TC, double *EC, double *diff2,
    double it[2]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_multi_amp.h) */
