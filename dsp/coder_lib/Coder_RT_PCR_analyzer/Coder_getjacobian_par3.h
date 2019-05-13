/*
 * Coder_getjacobian_par3.h
 *
 * Code generation for function 'Coder_getjacobian_par3'
 *
 */

#ifndef CODER_GETJACOBIAN_PAR3_H
#define CODER_GETJACOBIAN_PAR3_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "Coder_RT_PCR_analyzer_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void Coder_getjacobian_par3(const double param[4], const double x_data[],
    const int x_size[1], const double fixed_pt[2], double J_data[], int J_size[2]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (Coder_getjacobian_par3.h) */
