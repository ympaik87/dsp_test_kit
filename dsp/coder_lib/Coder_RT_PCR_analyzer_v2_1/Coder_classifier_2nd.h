/*
 * Coder_classifier_2nd.h
 *
 * Code generation for function 'Coder_classifier_2nd'
 *
 */

#ifndef CODER_CLASSIFIER_2ND_H
#define CODER_CLASSIFIER_2ND_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_v2_1_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_classifier_2nd(const double x_data[], const int x_size[1],
    const double ABSD_data[], const double f_data[], const double param[4],
    double SC, double TC, double *result_well, double *DataProcessNum, double RC,
    double Max_DRFU_Thrd, double dfM, double dfC, double PMC, double *R2, double
    *sht, double *EndRFU, double *df);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_classifier_2nd.h) */
