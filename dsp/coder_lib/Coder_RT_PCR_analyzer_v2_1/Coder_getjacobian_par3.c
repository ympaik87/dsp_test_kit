/*
 * Coder_getjacobian_par3.c
 *
 * Code generation for function 'Coder_getjacobian_par3'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_getjacobian_par3.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "rdivide_helper.h"
#include "power.h"

/* Function Definitions */
void Coder_getjacobian_par3(const double param[4], const double x_data[], const
  int x_size[1], const double fixed_pt[2], double J_data[], int J_size[2])
{
  int loop_ub;
  int i31;
  int param_size[1];
  double Cmm1_tmp_data[100];
  double param_data[100];
  double Cmm1_data[100];
  int Cmm1_size[1];
  int Cmm2_size[1];
  double Cmm2_data[100];
  emxArray_real_T *r4;
  emxArray_real_T b_Cmm2_data;
  double d10;
  int tmp_size[1];
  double tmp_data[100];
  J_size[0] = x_size[0];
  J_size[1] = 2;
  loop_ub = x_size[0] << 1;
  if (0 <= loop_ub - 1) {
    memset(&J_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  loop_ub = x_size[0];
  for (i31 = 0; i31 < loop_ub; i31++) {
    Cmm1_tmp_data[i31] = fixed_pt[0] - x_data[i31];
  }

  param_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i31 = 0; i31 < loop_ub; i31++) {
    param_data[i31] = param[3] * Cmm1_tmp_data[i31];
  }

  b_power(param_data, param_size, Cmm1_data, Cmm1_size);

  /* common portion */
  Cmm2_size[0] = Cmm1_size[0];
  loop_ub = Cmm1_size[0];
  for (i31 = 0; i31 < loop_ub; i31++) {
    Cmm2_data[i31] = 1.0 + Cmm1_data[i31];
  }

  loop_ub = Cmm2_size[0];
  for (i31 = 0; i31 < loop_ub; i31++) {
    J_data[i31] = 1.0 - 2.0 / Cmm2_data[i31];
  }

  emxInit_real_T(&r4, 1);
  b_Cmm2_data.data = &Cmm2_data[0];
  b_Cmm2_data.size = &Cmm2_size[0];
  b_Cmm2_data.allocatedSize = 100;
  b_Cmm2_data.numDimensions = 1;
  b_Cmm2_data.canFreeData = false;
  power(&b_Cmm2_data, r4);
  d10 = 4.6051701859880918 * (param[0] - fixed_pt[1]);
  tmp_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i31 = 0; i31 < loop_ub; i31++) {
    tmp_data[i31] = d10 * Cmm1_tmp_data[i31] * Cmm1_data[i31];
  }

  rdivide_helper(tmp_data, tmp_size, r4->data, param_data, param_size);
  loop_ub = param_size[0];
  emxFree_real_T(&r4);
  for (i31 = 0; i31 < loop_ub; i31++) {
    J_data[i31 + J_size[0]] = param_data[i31];
  }
}

/* End of code generation (Coder_getjacobian_par3.c) */
