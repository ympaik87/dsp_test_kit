/*
 * _coder_Coder_RT_PCR_analyzer_v2_1_mex.c
 *
 * Code generation for function '_coder_Coder_RT_PCR_analyzer_v2_1_mex'
 *
 */

/* Include files */
#include "_coder_Coder_RT_PCR_analyzer_v2_1_api.h"
#include "_coder_Coder_RT_PCR_analyzer_v2_1_mex.h"

/* Function Declarations */
static void c_Coder_RT_PCR_analyzer_v2_1_me(int32_T nlhs, mxArray *plhs[21],
  int32_T nrhs, const mxArray *prhs[17]);

/* Function Definitions */
static void c_Coder_RT_PCR_analyzer_v2_1_me(int32_T nlhs, mxArray *plhs[21],
  int32_T nrhs, const mxArray *prhs[17])
{
  const mxArray *outputs[21];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 17) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 17, 4,
                        26, "Coder_RT_PCR_analyzer_v2_1");
  }

  if (nlhs > 21) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 26,
                        "Coder_RT_PCR_analyzer_v2_1");
  }

  /* Call the function. */
  Coder_RT_PCR_analyzer_v2_1_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(Coder_RT_PCR_analyzer_v2_1_atexit);

  /* Module initialization. */
  Coder_RT_PCR_analyzer_v2_1_initialize();

  /* Dispatch the entry-point. */
  c_Coder_RT_PCR_analyzer_v2_1_me(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  Coder_RT_PCR_analyzer_v2_1_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_Coder_RT_PCR_analyzer_v2_1_mex.c) */
