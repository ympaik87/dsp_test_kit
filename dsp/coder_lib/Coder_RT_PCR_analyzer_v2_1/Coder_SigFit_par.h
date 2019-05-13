/*
 * Coder_SigFit_par.h
 *
 * Code generation for function 'Coder_SigFit_par'
 *
 */

#ifndef CODER_SIGFIT_PAR_H
#define CODER_SIGFIT_PAR_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_v2_1_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_SigFit_par(const double x_data[], const int x_size[1], const
    double ABSD_data[], double *result, double EC, const double ini_param[4],
    double SFC, double MFC2, const double perturbation_data[], double param[4],
    double f_data[], int f_size[1], double *SC);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_SigFit_par.h) */
