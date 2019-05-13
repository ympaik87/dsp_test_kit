/*
 * _coder_AutoBaseline_v2_mex.c
 *
 * Code generation for function '_coder_AutoBaseline_v2_mex'
 *
 */

/* Include files */
#include "_coder_AutoBaseline_v2_api.h"
#include "_coder_AutoBaseline_v2_mex.h"

/* Function Declarations */
static void AutoBaseline_v2_mexFunction(int32_T nlhs, mxArray *plhs[21], int32_T
  nrhs, const mxArray *prhs[17]);

/* Function Definitions */
static void AutoBaseline_v2_mexFunction(int32_T nlhs, mxArray *plhs[21], int32_T
  nrhs, const mxArray *prhs[17])
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
                        15, "AutoBaseline_v2");
  }

  if (nlhs > 21) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                        "AutoBaseline_v2");
  }

  /* Call the function. */
  AutoBaseline_v2_api(prhs, nlhs, outputs);

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
  mexAtExit(AutoBaseline_v2_atexit);

  /* Module initialization. */
  AutoBaseline_v2_initialize();

  /* Dispatch the entry-point. */
  AutoBaseline_v2_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  AutoBaseline_v2_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_AutoBaseline_v2_mex.c) */
