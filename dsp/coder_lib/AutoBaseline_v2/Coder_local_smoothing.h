/*
 * Coder_local_smoothing.h
 *
 * Code generation for function 'Coder_local_smoothing'
 *
 */

#ifndef CODER_LOCAL_SMOOTHING_H
#define CODER_LOCAL_SMOOTHING_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "AutoBaseline_v2_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_local_smoothing(const double data[6], double smoothed_data[6]);
  extern void b_Coder_local_smoothing(const double data_data[], const int
    data_size[1], double smoothed_data_data[], int smoothed_data_size[1]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_local_smoothing.h) */
