/*
 * Coder_dsig.c
 *
 * Code generation for function 'Coder_dsig'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_dsig.h"
#include "Coder_RT_PCR_analyzer_emxutil.h"
#include "rdivide_helper.h"
#include "power.h"

/* Function Definitions */
void Coder_dsig(const double p[4], const double x_data[], const int x_size[1],
                double df_data[], int df_size[1])
{
  emxArray_real_T *b_tmp;
  int i21;
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
  i21 = b_tmp->size[0];
  b_tmp->size[0] = x_size[0];
  emxEnsureCapacity_real_T(b_tmp, i21);
  loop_ub = x_size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    b_tmp->data[i21] = p[2] - x_data[i21];
  }

  emxInit_real_T(&b_p, 1);
  a = p[3] * 2.3025850929940459 * (p[1] - p[0]);
  i21 = b_p->size[0];
  b_p->size[0] = b_tmp->size[0];
  emxEnsureCapacity_real_T(b_p, i21);
  loop_ub = b_tmp->size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    b_p->data[i21] = p[3] * b_tmp->data[i21];
  }

  b_power(b_p->data, b_p->size, tmp_data, tmp_size);
  i21 = b_p->size[0];
  b_p->size[0] = b_tmp->size[0];
  emxEnsureCapacity_real_T(b_p, i21);
  loop_ub = b_tmp->size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    b_p->data[i21] = p[3] * b_tmp->data[i21];
  }

  b_power(b_p->data, b_p->size, b_tmp_data, b_tmp_size);
  c_tmp_size[0] = b_tmp_size[0];
  loop_ub = b_tmp_size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    d_tmp_data[i21] = 1.0 + b_tmp_data[i21];
  }

  c_tmp_data.data = &d_tmp_data[0];
  c_tmp_data.size = &c_tmp_size[0];
  c_tmp_data.allocatedSize = 100;
  c_tmp_data.numDimensions = 1;
  c_tmp_data.canFreeData = false;
  power(&c_tmp_data, b_tmp);
  i21 = b_p->size[0];
  b_p->size[0] = tmp_size[0];
  emxEnsureCapacity_real_T(b_p, i21);
  loop_ub = tmp_size[0];
  for (i21 = 0; i21 < loop_ub; i21++) {
    b_p->data[i21] = a * tmp_data[i21];
  }

  rdivide_helper(b_p->data, b_p->size, b_tmp->data, df_data, df_size);
  emxFree_real_T(&b_p);
  emxFree_real_T(&b_tmp);
}

/* End of code generation (Coder_dsig.c) */
