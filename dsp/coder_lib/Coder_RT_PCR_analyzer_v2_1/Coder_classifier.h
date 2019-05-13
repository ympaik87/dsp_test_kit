/*
 * Coder_classifier.h
 *
 * Code generation for function 'Coder_classifier'
 *
 */

#ifndef CODER_CLASSIFIER_H
#define CODER_CLASSIFIER_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_v2_1_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_classifier(const double x_data[], const int x_size[1], const
    double ABSD_data[], const int ABSD_size[1], const double f_data[], const int
    f_size[1], const double param[4], double SC, double TC, double *result_well,
    double *DataProcessNum, double RC, double Max_DRFU_Thrd, double dfM, double
    dfC, double PMC, double isPC, double *R2, double *sht, double *EndRFU,
    double *df);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_classifier.h) */
