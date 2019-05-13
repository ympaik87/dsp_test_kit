/*
 * Coder_linear_fitting.c
 *
 * Code generation for function 'Coder_linear_fitting'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_linear_fitting.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "sum.h"
#include "power.h"
#include "combineVectorElements.h"

/* Function Definitions */
void Coder_linear_fitting(const emxArray_real_T *x, const emxArray_real_T *y,
  double *slope, double *b_const)
{
  emxArray_real_T *b_x;
  double x_mean;
  double y_mean;
  int i15;
  int loop_ub;
  emxArray_real_T *r1;
  emxInit_real_T(&b_x, 1);
  x_mean = combineVectorElements(x) / (double)x->size[0];
  y_mean = combineVectorElements(y) / (double)y->size[0];
  i15 = b_x->size[0];
  b_x->size[0] = x->size[0];
  emxEnsureCapacity_real_T(b_x, i15);
  loop_ub = x->size[0];
  for (i15 = 0; i15 < loop_ub; i15++) {
    b_x->data[i15] = x->data[i15] - x_mean;
  }

  emxInit_real_T(&r1, 1);
  power(b_x, r1);
  i15 = b_x->size[0];
  b_x->size[0] = x->size[0];
  emxEnsureCapacity_real_T(b_x, i15);
  loop_ub = x->size[0];
  for (i15 = 0; i15 < loop_ub; i15++) {
    b_x->data[i15] = (x->data[i15] - x_mean) * (y->data[i15] - y_mean);
  }

  *slope = sum(b_x) / sum(r1);
  i15 = b_x->size[0];
  b_x->size[0] = y->size[0];
  emxEnsureCapacity_real_T(b_x, i15);
  loop_ub = y->size[0];
  emxFree_real_T(&r1);
  for (i15 = 0; i15 < loop_ub; i15++) {
    b_x->data[i15] = y->data[i15] - *slope * x->data[i15];
  }

  *b_const = sum(b_x) / (double)x->size[0];
  emxFree_real_T(&b_x);
}

/* End of code generation (Coder_linear_fitting.c) */
