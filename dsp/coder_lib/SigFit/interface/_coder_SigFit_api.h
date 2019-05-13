/*
 * _coder_SigFit_api.h
 *
 * Code generation for function '_coder_SigFit_api'
 *
 */

#ifndef _CODER_SIGFIT_API_H
#define _CODER_SIGFIT_API_H

/* Include files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_SigFit_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void SigFit(real_T x[45], real_T ABSD[45], real_T *result, real_T
                     ini_param[4], real_T *SC, real_T TC, real_T HTC, real_T SFC,
                     real_T perturbation[60], real_T param_data[], int32_T
                     param_size[2], real_T f[45]);
  extern void SigFit_api(const mxArray * const prhs[9], const mxArray *plhs[4]);
  extern void SigFit_atexit(void);
  extern void SigFit_initialize(void);
  extern void SigFit_terminate(void);
  extern void SigFit_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (_coder_SigFit_api.h) */
