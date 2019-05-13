/*
 * Coder_getjacobian_4para.c
 *
 * Code generation for function 'Coder_getjacobian_4para'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_getjacobian_4para.h"
#include "rdivide_helper.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "power.h"

/* Function Definitions */
void Coder_getjacobian_4para(const double param[4], const double x_data[], const
  int x_size[1], double J_data[], int J_size[2])
{
  int loop_ub;
  int i20;
  int param_size[1];
  double Cmm1_tmp_data[100];
  double param_data[100];
  double Cmm1_data[100];
  int Cmm1_size[1];
  int Cmm2_size[1];
  int tmp_size_idx_0;
  double Cmm2_data[100];
  double tmp_data[100];
  emxArray_real_T *r2;
  emxArray_real_T b_Cmm2_data;
  double d4;
  double d5;
  int tmp_size[1];
  int b_tmp_size[1];
  J_size[0] = x_size[0];
  J_size[1] = 4;
  loop_ub = x_size[0] << 2;
  if (0 <= loop_ub - 1) {
    memset(&J_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  loop_ub = x_size[0];
  for (i20 = 0; i20 < loop_ub; i20++) {
    Cmm1_tmp_data[i20] = param[2] - x_data[i20];
  }

  param_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i20 = 0; i20 < loop_ub; i20++) {
    param_data[i20] = param[3] * Cmm1_tmp_data[i20];
  }

  b_power(param_data, param_size, Cmm1_data, Cmm1_size);

  /* common portion */
  Cmm2_size[0] = Cmm1_size[0];
  loop_ub = Cmm1_size[0];
  for (i20 = 0; i20 < loop_ub; i20++) {
    Cmm2_data[i20] = 1.0 + Cmm1_data[i20];
  }

  tmp_size_idx_0 = Cmm2_size[0];
  loop_ub = Cmm2_size[0];
  for (i20 = 0; i20 < loop_ub; i20++) {
    tmp_data[i20] = 1.0 / Cmm2_data[i20];
  }

  for (i20 = 0; i20 < tmp_size_idx_0; i20++) {
    J_data[i20] = 1.0 - tmp_data[i20];
  }

  for (i20 = 0; i20 < tmp_size_idx_0; i20++) {
    J_data[i20 + J_size[0]] = tmp_data[i20];
  }

  emxInit_real_T(&r2, 1);
  b_Cmm2_data.data = &Cmm2_data[0];
  b_Cmm2_data.size = &Cmm2_size[0];
  b_Cmm2_data.allocatedSize = 100;
  b_Cmm2_data.numDimensions = 1;
  b_Cmm2_data.canFreeData = false;
  power(&b_Cmm2_data, r2);
  Cmm2_size[0] = r2->size[0];
  loop_ub = r2->size[0];
  for (i20 = 0; i20 < loop_ub; i20++) {
    Cmm2_data[i20] = r2->data[i20];
  }

  emxFree_real_T(&r2);
  d4 = 2.3025850929940459 * (param[0] - param[1]);
  d5 = d4 * param[3];
  tmp_size[0] = Cmm1_size[0];
  loop_ub = Cmm1_size[0];
  for (i20 = 0; i20 < loop_ub; i20++) {
    tmp_data[i20] = d5 * Cmm1_data[i20];
  }

  rdivide_helper(tmp_data, tmp_size, Cmm2_data, param_data, param_size);
  loop_ub = param_size[0];
  for (i20 = 0; i20 < loop_ub; i20++) {
    J_data[i20 + (J_size[0] << 1)] = param_data[i20];
  }

  b_tmp_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i20 = 0; i20 < loop_ub; i20++) {
    tmp_data[i20] = d4 * Cmm1_tmp_data[i20] * Cmm1_data[i20];
  }

  rdivide_helper(tmp_data, b_tmp_size, Cmm2_data, param_data, tmp_size);
  loop_ub = tmp_size[0];
  for (i20 = 0; i20 < loop_ub; i20++) {
    J_data[i20 + J_size[0] * 3] = param_data[i20];
  }
}

/* End of code generation (Coder_getjacobian_4para.c) */
