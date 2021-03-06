/*
 * Coder_SigFitter_2para_part2.h
 *
 * Code generation for function 'Coder_SigFitter_2para_part2'
 *
 */

#ifndef CODER_SIGFITTER_2PARA_PART2_H
#define CODER_SIGFITTER_2PARA_PART2_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_v2_1_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_SigFitter_2para_part2(const double x_data[], const int
    x_size[1], const double y_data[], const int y_size[1], const double param0[4],
    const double fixed_pt[2], double param[4], double *iter, double *state);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_SigFitter_2para_part2.h) */
