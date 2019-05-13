/*
 * Coder_find_peak_cluster.h
 *
 * Code generation for function 'Coder_find_peak_cluster'
 *
 */

#ifndef CODER_FIND_PEAK_CLUSTER_H
#define CODER_FIND_PEAK_CLUSTER_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_v2_1_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_find_peak_cluster(double rotated_RD_data[], int
    rotated_RD_size[1], double SC, double *peak_cycle1, double *peak_cycle2,
    double *height);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_find_peak_cluster.h) */
