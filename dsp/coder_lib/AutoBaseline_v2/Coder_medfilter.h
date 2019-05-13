/*
 * Coder_medfilter.h
 *
 * Code generation for function 'Coder_medfilter'
 *
 */

#ifndef CODER_MEDFILTER_H
#define CODER_MEDFILTER_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "AutoBaseline_v2_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_medfilter(const double data_data[], const int data_size[1],
    double smoothed_data_data[], int smoothed_data_size[1]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_medfilter.h) */
