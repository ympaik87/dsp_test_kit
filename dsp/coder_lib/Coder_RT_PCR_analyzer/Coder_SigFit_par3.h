/*
 * Coder_SigFit_par3.h
 *
 * Code generation for function 'Coder_SigFit_par3'
 *
 */

#ifndef CODER_SIGFIT_PAR3_H
#define CODER_SIGFIT_PAR3_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_SigFit_par3(const double x_data[], const int x_size[1],
    const double ABSD_data[], double *result, const double *SC, const double
    ini_param[4], const double fixed_pt[2], double TC, const double
    perturbation_data[], double param[4], double f_data[], int f_size[1]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_SigFit_par3.h) */
