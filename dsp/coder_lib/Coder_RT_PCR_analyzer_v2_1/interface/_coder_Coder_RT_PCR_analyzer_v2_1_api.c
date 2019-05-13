/*
 * _coder_Coder_RT_PCR_analyzer_v2_1_api.c
 *
 * Code generation for function '_coder_Coder_RT_PCR_analyzer_v2_1_api'
 *
 */

/* Include files */
#include "tmwtypes.h"
#include "_coder_Coder_RT_PCR_analyzer_v2_1_api.h"
#include "_coder_Coder_RT_PCR_analyzer_v2_1_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131467U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "Coder_RT_PCR_analyzer_v2_1",        /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T **y_data, int32_T y_size[1]);
static const mxArray *b_emlrt_marshallOut(const real_T u_data[], const int32_T
  u_size[2]);
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *SFC, const
  char_T *identifier);
static const mxArray *c_emlrt_marshallOut(const real_T u_data[], const int32_T
  u_size[1]);
static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static const mxArray *d_emlrt_marshallOut(const real_T u[2]);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *ver_array,
  const char_T *identifier, real_T **y_data, int32_T y_size[1]);
static const mxArray *e_emlrt_marshallOut(const real_T u[4]);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *x, const
  char_T *identifier, real_T **y_data, int32_T y_size[1]);
static const mxArray *emlrt_marshallOut(const real_T u);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T **y_data, int32_T y_size[1]);
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T **ret_data, int32_T ret_size[1]);
static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T **ret_data, int32_T ret_size[1]);

/* Function Definitions */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T **y_data, int32_T y_size[1])
{
  real_T *r1;
  g_emlrt_marshallIn(sp, emlrtAlias(u), parentId, &r1, y_size);
  *y_data = r1;
  emlrtDestroyArray(&u);
}

static const mxArray *b_emlrt_marshallOut(const real_T u_data[], const int32_T
  u_size[2])
{
  const mxArray *y;
  const mxArray *m1;
  static const int32_T iv0[2] = { 0, 0 };

  y = NULL;
  m1 = emlrtCreateNumericArray(2, iv0, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m1, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m1, u_size, 2);
  emlrtAssign(&y, m1);
  return y;
}

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *SFC, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(SFC), &thisId);
  emlrtDestroyArray(&SFC);
  return y;
}

static const mxArray *c_emlrt_marshallOut(const real_T u_data[], const int32_T
  u_size[1])
{
  const mxArray *y;
  const mxArray *m2;
  static const int32_T iv1[1] = { 0 };

  y = NULL;
  m2 = emlrtCreateNumericArray(1, iv1, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m2, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m2, u_size, 1);
  emlrtAssign(&y, m2);
  return y;
}

static real_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static const mxArray *d_emlrt_marshallOut(const real_T u[2])
{
  const mxArray *y;
  const mxArray *m4;
  static const int32_T iv3[2] = { 0, 0 };

  static const int32_T iv4[2] = { 1, 2 };

  y = NULL;
  m4 = emlrtCreateNumericArray(2, iv3, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m4, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m4, iv4, 2);
  emlrtAssign(&y, m4);
  return y;
}

static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *ver_array,
  const char_T *identifier, real_T **y_data, int32_T y_size[1])
{
  emlrtMsgIdentifier thisId;
  real_T *r2;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(sp, emlrtAlias(ver_array), &thisId, &r2, y_size);
  *y_data = r2;
  emlrtDestroyArray(&ver_array);
}

static const mxArray *e_emlrt_marshallOut(const real_T u[4])
{
  const mxArray *y;
  const mxArray *m5;
  static const int32_T iv5[2] = { 0, 0 };

  static const int32_T iv6[2] = { 1, 4 };

  y = NULL;
  m5 = emlrtCreateNumericArray(2, iv5, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m5, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m5, iv6, 2);
  emlrtAssign(&y, m5);
  return y;
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *x, const
  char_T *identifier, real_T **y_data, int32_T y_size[1])
{
  emlrtMsgIdentifier thisId;
  real_T *r0;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(x), &thisId, &r0, y_size);
  *y_data = r0;
  emlrtDestroyArray(&x);
}

static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *y;
  const mxArray *m0;
  y = NULL;
  m0 = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m0);
  return y;
}

static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real_T **y_data, int32_T y_size[1])
{
  real_T *r3;
  i_emlrt_marshallIn(sp, emlrtAlias(u), parentId, &r3, y_size);
  *y_data = r3;
  emlrtDestroyArray(&u);
}

static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T **ret_data, int32_T ret_size[1])
{
  static const int32_T dims[1] = { 100 };

  const boolean_T bv0[1] = { true };

  int32_T iv7[1];
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims, &bv0[0],
    iv7);
  ret_size[0] = iv7[0];
  *ret_data = (real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
}

static real_T h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real_T **ret_data, int32_T ret_size[1])
{
  static const int32_T dims[1] = { 20 };

  const boolean_T bv1[1] = { true };

  int32_T iv8[1];
  emlrtCheckVsBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims, &bv1[0],
    iv8);
  ret_size[0] = iv8[0];
  *ret_data = (real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
}

void Coder_RT_PCR_analyzer_v2_1_api(const mxArray * const prhs[17], int32_T nlhs,
  const mxArray *plhs[21])
{
  real_T (*DataProcess_data)[800];
  real_T (*RD_diff_data)[100];
  real_T (*ivd_cdd_ouput_data)[100];
  real_T (*cff)[2];
  real_T (*scd_fit_data)[100];
  real_T (*ABSD_orig_data)[100];
  real_T (*ABSD_data)[100];
  real_T (*f_data)[100];
  real_T (*f_new_data)[100];
  real_T (*param)[4];
  real_T (*param_new)[4];
  const mxArray *prhs_copy_idx_0;
  const mxArray *prhs_copy_idx_1;
  real_T (*x_data)[100];
  int32_T x_size[1];
  real_T (*RD_data)[100];
  int32_T RD_size[1];
  real_T (*perturbation_data)[100];
  int32_T perturbation_size[1];
  real_T SFC;
  real_T MFC;
  real_T DRFU;
  real_T Thrd;
  real_T RPC;
  real_T RC;
  real_T dfM;
  real_T dfC;
  real_T PMC;
  real_T FB;
  real_T AR;
  real_T isPC;
  real_T (*ver_array_data)[20];
  int32_T ver_array_size[1];
  real_T DS;
  real_T result_well;
  real_T DataProcessNum;
  int32_T DataProcess_size[2];
  real_T LSR_val;
  int32_T RD_diff_size[1];
  int32_T ivd_cdd_ouput_size[2];
  int32_T scd_fit_size[1];
  real_T R_p2;
  real_T EFC;
  int32_T ABSD_orig_size[1];
  int32_T ABSD_size[1];
  int32_T f_size[1];
  int32_T f_new_size[1];
  real_T sht;
  real_T sht2;
  real_T R2;
  real_T EndRFU;
  real_T df;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  DataProcess_data = (real_T (*)[800])mxMalloc(sizeof(real_T [800]));
  RD_diff_data = (real_T (*)[100])mxMalloc(sizeof(real_T [100]));
  ivd_cdd_ouput_data = (real_T (*)[100])mxMalloc(sizeof(real_T [100]));
  cff = (real_T (*)[2])mxMalloc(sizeof(real_T [2]));
  scd_fit_data = (real_T (*)[100])mxMalloc(sizeof(real_T [100]));
  ABSD_orig_data = (real_T (*)[100])mxMalloc(sizeof(real_T [100]));
  ABSD_data = (real_T (*)[100])mxMalloc(sizeof(real_T [100]));
  f_data = (real_T (*)[100])mxMalloc(sizeof(real_T [100]));
  f_new_data = (real_T (*)[100])mxMalloc(sizeof(real_T [100]));
  param = (real_T (*)[4])mxMalloc(sizeof(real_T [4]));
  param_new = (real_T (*)[4])mxMalloc(sizeof(real_T [4]));
  prhs_copy_idx_0 = prhs[0];
  prhs_copy_idx_1 = emlrtProtectR2012b(prhs[1], 1, false, 100);

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_0), "x", (real_T **)&x_data,
                   x_size);
  emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_1), "RD", (real_T **)&RD_data,
                   RD_size);
  emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "perturbation", (real_T **)
                   &perturbation_data, perturbation_size);
  SFC = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "SFC");
  MFC = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "MFC");
  DRFU = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "DRFU");
  Thrd = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "Thrd");
  RPC = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "RPC");
  RC = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "RC");
  dfM = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[9]), "dfM");
  dfC = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[10]), "dfC");
  PMC = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[11]), "PMC");
  FB = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[12]), "FB");
  AR = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[13]), "AR");
  isPC = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[14]), "isPC");
  e_emlrt_marshallIn(&st, emlrtAlias(prhs[15]), "ver_array", (real_T **)
                     &ver_array_data, ver_array_size);
  DS = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[16]), "DS");

  /* Invoke the target function */
  Coder_RT_PCR_analyzer_v2_1(*x_data, x_size, *RD_data, RD_size,
    *perturbation_data, perturbation_size, SFC, MFC, DRFU, Thrd, RPC, RC, dfM,
    dfC, PMC, FB, AR, isPC, *ver_array_data, ver_array_size, DS, &result_well,
    &DataProcessNum, *DataProcess_data, DataProcess_size, &LSR_val,
    *RD_diff_data, RD_diff_size, *ivd_cdd_ouput_data, ivd_cdd_ouput_size, *cff, *
    scd_fit_data, scd_fit_size, &R_p2, &EFC, *ABSD_orig_data, ABSD_orig_size,
    *ABSD_data, ABSD_size, *f_data, f_size, *f_new_data, f_new_size, &sht, &sht2,
    *param, *param_new, &R2, &EndRFU, &df);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(result_well);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(DataProcessNum);
  }

  if (nlhs > 2) {
    plhs[2] = b_emlrt_marshallOut(*DataProcess_data, DataProcess_size);
  }

  if (nlhs > 3) {
    plhs[3] = emlrt_marshallOut(LSR_val);
  }

  if (nlhs > 4) {
    plhs[4] = c_emlrt_marshallOut(*RD_diff_data, RD_diff_size);
  }

  if (nlhs > 5) {
    plhs[5] = b_emlrt_marshallOut(*ivd_cdd_ouput_data, ivd_cdd_ouput_size);
  }

  if (nlhs > 6) {
    plhs[6] = d_emlrt_marshallOut(*cff);
  }

  if (nlhs > 7) {
    plhs[7] = c_emlrt_marshallOut(*scd_fit_data, scd_fit_size);
  }

  if (nlhs > 8) {
    plhs[8] = emlrt_marshallOut(R_p2);
  }

  if (nlhs > 9) {
    plhs[9] = emlrt_marshallOut(EFC);
  }

  if (nlhs > 10) {
    plhs[10] = c_emlrt_marshallOut(*ABSD_orig_data, ABSD_orig_size);
  }

  if (nlhs > 11) {
    plhs[11] = c_emlrt_marshallOut(*ABSD_data, ABSD_size);
  }

  if (nlhs > 12) {
    plhs[12] = c_emlrt_marshallOut(*f_data, f_size);
  }

  if (nlhs > 13) {
    plhs[13] = c_emlrt_marshallOut(*f_new_data, f_new_size);
  }

  if (nlhs > 14) {
    plhs[14] = emlrt_marshallOut(sht);
  }

  if (nlhs > 15) {
    plhs[15] = emlrt_marshallOut(sht2);
  }

  if (nlhs > 16) {
    plhs[16] = e_emlrt_marshallOut(*param);
  }

  if (nlhs > 17) {
    plhs[17] = e_emlrt_marshallOut(*param_new);
  }

  if (nlhs > 18) {
    plhs[18] = emlrt_marshallOut(R2);
  }

  if (nlhs > 19) {
    plhs[19] = emlrt_marshallOut(EndRFU);
  }

  if (nlhs > 20) {
    plhs[20] = emlrt_marshallOut(df);
  }
}

void Coder_RT_PCR_analyzer_v2_1_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  Coder_RT_PCR_analyzer_v2_1_xil_terminate();
}

void Coder_RT_PCR_analyzer_v2_1_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void Coder_RT_PCR_analyzer_v2_1_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_Coder_RT_PCR_analyzer_v2_1_api.c) */
