/*
 * Coder_fst_fitting.c
 *
 * Code generation for function 'Coder_fst_fitting'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_fst_fitting.h"
#include "sum.h"
#include "Coder_RT_PCR_analyzer_emxutil.h"
#include "power.h"

/* Function Definitions */
void Coder_fst_fitting(const emxArray_real_T *x, const double y_data[], const
  int y_size[1], double n, double *coeff1, double *coeff2, double *coeff3)
{
  emxArray_real_T *x2;
  emxArray_real_T *b_x;
  double x_sum;
  double x2_sum;
  emxArray_real_T b_y_data;
  double y_sum;
  double x_mean;
  double x2_mean;
  double S_11;
  int i9;
  int loop_ub;
  double S_12;
  int b_y_size[1];
  emxArray_real_T c_y_data;
  double d_y_data[100];
  int c_y_size[1];
  double e_y_data[100];
  emxArray_real_T f_y_data;
  double S_y2;
  double coeff1_tmp;
  emxInit_real_T(&x2, 1);
  emxInit_real_T(&b_x, 1);
  power(x, x2);
  x_sum = sum(x);
  x2_sum = sum(x2);
  b_y_data.data = (double *)&y_data[0];
  b_y_data.size = (int *)&y_size[0];
  b_y_data.allocatedSize = -1;
  b_y_data.numDimensions = 1;
  b_y_data.canFreeData = false;
  y_sum = sum(&b_y_data);
  x_mean = x_sum / n;
  x2_mean = x2_sum / n;
  S_11 = x2_sum - x_mean * x_sum;
  i9 = b_x->size[0];
  b_x->size[0] = x->size[0];
  emxEnsureCapacity_real_T(b_x, i9);
  loop_ub = x->size[0];
  for (i9 = 0; i9 < loop_ub; i9++) {
    b_x->data[i9] = x->data[i9] * x2->data[i9];
  }

  S_12 = sum(b_x) - x_sum * x2_mean;
  power(x2, b_x);
  x_sum = sum(b_x) - x2_mean * x2_sum;
  b_y_size[0] = y_size[0];
  loop_ub = y_size[0];
  emxFree_real_T(&b_x);
  for (i9 = 0; i9 < loop_ub; i9++) {
    d_y_data[i9] = y_data[i9] * x->data[i9];
  }

  c_y_data.data = &d_y_data[0];
  c_y_data.size = &b_y_size[0];
  c_y_data.allocatedSize = 100;
  c_y_data.numDimensions = 1;
  c_y_data.canFreeData = false;
  x2_sum = sum(&c_y_data) - y_sum * x_mean;
  c_y_size[0] = y_size[0];
  loop_ub = y_size[0];
  for (i9 = 0; i9 < loop_ub; i9++) {
    e_y_data[i9] = y_data[i9] * x2->data[i9];
  }

  emxFree_real_T(&x2);
  f_y_data.data = &e_y_data[0];
  f_y_data.size = &c_y_size[0];
  f_y_data.allocatedSize = 100;
  f_y_data.numDimensions = 1;
  f_y_data.canFreeData = false;
  S_y2 = sum(&f_y_data) - y_sum * x2_mean;

  /*  y=coeff1*x^2 + coeff2*x + coeff3 */
  coeff1_tmp = x_sum * S_11 - S_12 * S_12;
  *coeff1 = (S_y2 * S_11 - x2_sum * S_12) / coeff1_tmp;
  *coeff2 = (x2_sum * x_sum - S_y2 * S_12) / coeff1_tmp;
  *coeff3 = (y_sum / n - *coeff2 * x_mean) - *coeff1 * x2_mean;
}

/* End of code generation (Coder_fst_fitting.c) */
