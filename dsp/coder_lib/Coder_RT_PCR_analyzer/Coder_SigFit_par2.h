/*
 * Coder_SigFit_par2.h
 *
 * Code generation for function 'Coder_SigFit_par2'
 *
 */

#ifndef CODER_SIGFIT_PAR2_H
#define CODER_SIGFIT_PAR2_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_SigFit_par2(const double x_data[], const int x_size[1],
    const double ABSD_data[], double *result, double EC, const double ini_param
    [4], const double fixed_pt[2], double SFC, const double perturbation_data[],
    double param[4], double f_data[], int f_size[1], double *SC);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_SigFit_par2.h) */
