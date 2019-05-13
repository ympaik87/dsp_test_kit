/*
 * Coder_getjacobian_par2.c
 *
 * Code generation for function 'Coder_getjacobian_par2'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_getjacobian_par2.h"
#include "rdivide_helper.h"
#include "Coder_RT_PCR_analyzer_emxutil.h"
#include "power.h"
#include "Coder_RT_PCR_analyzer_rtwutil.h"

/* Function Definitions */
void Coder_getjacobian_par2(const double param[4], const double x_data[], const
  int x_size[1], const double fixed_pt[2], double J_data[], int J_size[2])
{
  int loop_ub;
  int i26;
  int param_size[1];
  double Cmm1_tmp_data[97];
  double param_data[97];
  double tmp_data[100];
  int tmp_size[1];
  double Cmm1_data[97];
  int Cmm2_size[1];
  emxArray_real_T *r3;
  double Cmm2_data[97];
  double Cmm3_tmp;
  double Cmm3;
  emxArray_real_T b_Cmm2_data;
  double J_tmp_data[100];
  double d7;
  double d8;
  int b_tmp_size[1];
  int c_tmp_size[1];
  J_size[0] = x_size[0];
  J_size[1] = 2;
  loop_ub = x_size[0] << 1;
  if (0 <= loop_ub - 1) {
    memset(&J_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  loop_ub = x_size[0];
  for (i26 = 0; i26 < loop_ub; i26++) {
    Cmm1_tmp_data[i26] = param[2] - x_data[i26];
  }

  param_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i26 = 0; i26 < loop_ub; i26++) {
    param_data[i26] = param[3] * Cmm1_tmp_data[i26];
  }

  b_power(param_data, param_size, tmp_data, tmp_size);
  if (0 <= tmp_size[0] - 1) {
    memcpy(&Cmm1_data[0], &tmp_data[0], (unsigned int)(tmp_size[0] * (int)sizeof
            (double)));
  }

  /* common portion */
  Cmm2_size[0] = tmp_size[0];
  loop_ub = tmp_size[0];
  for (i26 = 0; i26 < loop_ub; i26++) {
    Cmm2_data[i26] = 1.0 + Cmm1_data[i26];
  }

  emxInit_real_T(&r3, 1);
  Cmm3_tmp = param[2] - fixed_pt[0];
  Cmm3 = rt_powd_snf(10.0, param[3] * Cmm3_tmp);
  b_Cmm2_data.data = &Cmm2_data[0];
  b_Cmm2_data.size = &Cmm2_size[0];
  b_Cmm2_data.allocatedSize = 97;
  b_Cmm2_data.numDimensions = 1;
  b_Cmm2_data.canFreeData = false;
  power(&b_Cmm2_data, r3);
  loop_ub = r3->size[0];
  for (i26 = 0; i26 < loop_ub; i26++) {
    J_tmp_data[i26] = r3->data[i26];
  }

  emxFree_real_T(&r3);
  d7 = 2.3025850929940459 * (fixed_pt[1] - param[0]);
  d8 = d7 * param[3];
  b_tmp_size[0] = tmp_size[0];
  loop_ub = tmp_size[0];
  for (i26 = 0; i26 < loop_ub; i26++) {
    param_data[i26] = d8 * (Cmm3 - Cmm1_data[i26]);
  }

  rdivide_helper(param_data, b_tmp_size, J_tmp_data, tmp_data, tmp_size);
  if (0 <= tmp_size[0] - 1) {
    memcpy(&J_data[0], &tmp_data[0], (unsigned int)(tmp_size[0] * (int)sizeof
            (double)));
  }

  Cmm3_tmp *= Cmm3;
  c_tmp_size[0] = Cmm2_size[0];
  loop_ub = Cmm2_size[0];
  for (i26 = 0; i26 < loop_ub; i26++) {
    param_data[i26] = d7 * (Cmm3_tmp * Cmm2_data[i26] - Cmm1_tmp_data[i26] *
      (1.0 + Cmm3) * Cmm1_data[i26]);
  }

  rdivide_helper(param_data, c_tmp_size, J_tmp_data, tmp_data, tmp_size);
  loop_ub = tmp_size[0];
  for (i26 = 0; i26 < loop_ub; i26++) {
    J_data[i26 + J_size[0]] = tmp_data[i26];
  }
}

/* End of code generation (Coder_getjacobian_par2.c) */
