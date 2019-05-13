/*
 * Coder_getjacobian_3para.c
 *
 * Code generation for function 'Coder_getjacobian_3para'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_getjacobian_3para.h"
#include "rdivide_helper.h"
#include "Coder_RT_PCR_analyzer_emxutil.h"
#include "power.h"

/* Function Definitions */
void Coder_getjacobian_3para(const double param[4], const double x_data[], const
  int x_size[1], double J_data[], int J_size[2])
{
  int loop_ub;
  int i32;
  int param_size[1];
  double Cmm1_tmp_data[100];
  double param_data[100];
  double Cmm1_data[100];
  int Cmm1_size[1];
  int Cmm2_size[1];
  double Cmm2_data[100];
  emxArray_real_T *r6;
  emxArray_real_T b_Cmm2_data;
  double d11;
  double d12;
  int tmp_size[1];
  double tmp_data[100];
  int b_tmp_size[1];
  J_size[0] = x_size[0];
  J_size[1] = 3;
  loop_ub = x_size[0] * 3;
  if (0 <= loop_ub - 1) {
    memset(&J_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  loop_ub = x_size[0];
  for (i32 = 0; i32 < loop_ub; i32++) {
    Cmm1_tmp_data[i32] = param[2] - x_data[i32];
  }

  param_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i32 = 0; i32 < loop_ub; i32++) {
    param_data[i32] = param[3] * Cmm1_tmp_data[i32];
  }

  b_power(param_data, param_size, Cmm1_data, Cmm1_size);

  /* common portion */
  Cmm2_size[0] = Cmm1_size[0];
  loop_ub = Cmm1_size[0];
  for (i32 = 0; i32 < loop_ub; i32++) {
    Cmm2_data[i32] = 1.0 + Cmm1_data[i32];
  }

  loop_ub = Cmm2_size[0];
  for (i32 = 0; i32 < loop_ub; i32++) {
    J_data[i32] = 1.0 / Cmm2_data[i32];
  }

  emxInit_real_T(&r6, 1);
  b_Cmm2_data.data = &Cmm2_data[0];
  b_Cmm2_data.size = &Cmm2_size[0];
  b_Cmm2_data.allocatedSize = 100;
  b_Cmm2_data.numDimensions = 1;
  b_Cmm2_data.canFreeData = false;
  power(&b_Cmm2_data, r6);
  Cmm2_size[0] = r6->size[0];
  loop_ub = r6->size[0];
  for (i32 = 0; i32 < loop_ub; i32++) {
    Cmm2_data[i32] = r6->data[i32];
  }

  emxFree_real_T(&r6);
  d11 = 2.3025850929940459 * (param[0] - param[1]);
  d12 = d11 * param[3];
  tmp_size[0] = Cmm1_size[0];
  loop_ub = Cmm1_size[0];
  for (i32 = 0; i32 < loop_ub; i32++) {
    param_data[i32] = d12 * Cmm1_data[i32];
  }

  rdivide_helper(param_data, tmp_size, Cmm2_data, tmp_data, param_size);
  loop_ub = param_size[0];
  for (i32 = 0; i32 < loop_ub; i32++) {
    J_data[i32 + J_size[0]] = tmp_data[i32];
  }

  b_tmp_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i32 = 0; i32 < loop_ub; i32++) {
    param_data[i32] = d11 * Cmm1_tmp_data[i32] * Cmm1_data[i32];
  }

  rdivide_helper(param_data, b_tmp_size, Cmm2_data, tmp_data, tmp_size);
  loop_ub = tmp_size[0];
  for (i32 = 0; i32 < loop_ub; i32++) {
    J_data[i32 + (J_size[0] << 1)] = tmp_data[i32];
  }
}

/* End of code generation (Coder_getjacobian_3para.c) */
