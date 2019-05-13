/*
 * Coder_dsig.c
 *
 * Code generation for function 'Coder_dsig'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_dsig.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "rdivide_helper.h"
#include "power.h"

/* Function Definitions */
void Coder_dsig(const double p[4], const double x_data[], const int x_size[1],
                double df_data[], int df_size[1])
{
  emxArray_real_T *b_tmp;
  int i23;
  int loop_ub;
  emxArray_real_T *b_p;
  double a;
  double tmp_data[100];
  int tmp_size[1];
  double b_tmp_data[100];
  int b_tmp_size[1];
  int c_tmp_size[1];
  emxArray_real_T c_tmp_data;
  double d_tmp_data[100];
  emxInit_real_T(&b_tmp, 1);
  i23 = b_tmp->size[0];
  b_tmp->size[0] = x_size[0];
  emxEnsureCapacity_real_T(b_tmp, i23);
  loop_ub = x_size[0];
  for (i23 = 0; i23 < loop_ub; i23++) {
    b_tmp->data[i23] = p[2] - x_data[i23];
  }

  emxInit_real_T(&b_p, 1);
  a = p[3] * 2.3025850929940459 * (p[1] - p[0]);
  i23 = b_p->size[0];
  b_p->size[0] = b_tmp->size[0];
  emxEnsureCapacity_real_T(b_p, i23);
  loop_ub = b_tmp->size[0];
  for (i23 = 0; i23 < loop_ub; i23++) {
    b_p->data[i23] = p[3] * b_tmp->data[i23];
  }

  b_power(b_p->data, b_p->size, tmp_data, tmp_size);
  i23 = b_p->size[0];
  b_p->size[0] = b_tmp->size[0];
  emxEnsureCapacity_real_T(b_p, i23);
  loop_ub = b_tmp->size[0];
  for (i23 = 0; i23 < loop_ub; i23++) {
    b_p->data[i23] = p[3] * b_tmp->data[i23];
  }

  b_power(b_p->data, b_p->size, b_tmp_data, b_tmp_size);
  c_tmp_size[0] = b_tmp_size[0];
  loop_ub = b_tmp_size[0];
  for (i23 = 0; i23 < loop_ub; i23++) {
    d_tmp_data[i23] = 1.0 + b_tmp_data[i23];
  }

  c_tmp_data.data = &d_tmp_data[0];
  c_tmp_data.size = &c_tmp_size[0];
  c_tmp_data.allocatedSize = 100;
  c_tmp_data.numDimensions = 1;
  c_tmp_data.canFreeData = false;
  power(&c_tmp_data, b_tmp);
  i23 = b_p->size[0];
  b_p->size[0] = tmp_size[0];
  emxEnsureCapacity_real_T(b_p, i23);
  loop_ub = tmp_size[0];
  for (i23 = 0; i23 < loop_ub; i23++) {
    b_p->data[i23] = a * tmp_data[i23];
  }

  rdivide_helper(b_p->data, b_p->size, b_tmp->data, df_data, df_size);
  emxFree_real_T(&b_p);
  emxFree_real_T(&b_tmp);
}

/* End of code generation (Coder_dsig.c) */
