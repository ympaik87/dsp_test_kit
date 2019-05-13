/*
 * Coder_scd_fitting.c
 *
 * Code generation for function 'Coder_scd_fitting'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_scd_fitting.h"
#include "AutoBaseline_v2_emxutil.h"
#include "sum.h"
#include "power.h"
#include "combineVectorElements.h"

/* Function Definitions */
void Coder_scd_fitting(const emxArray_real_T *xx, const emxArray_real_T *y,
  double *slope, double *b_const)
{
  emxArray_real_T *b_xx;
  int i15;
  int loop_ub;
  emxArray_real_T *x;
  double x_mean;
  double y_mean;
  emxArray_real_T *r0;
  emxInit_real_T(&b_xx, 1);
  i15 = b_xx->size[0];
  b_xx->size[0] = xx->size[0];
  emxEnsureCapacity_real_T(b_xx, i15);
  loop_ub = xx->size[0];
  for (i15 = 0; i15 < loop_ub; i15++) {
    b_xx->data[i15] = xx->data[i15] - 50.0;
  }

  emxInit_real_T(&x, 1);
  power(b_xx, x);
  x_mean = combineVectorElements(x) / (double)x->size[0];
  y_mean = combineVectorElements(y) / (double)y->size[0];
  i15 = b_xx->size[0];
  b_xx->size[0] = x->size[0];
  emxEnsureCapacity_real_T(b_xx, i15);
  loop_ub = x->size[0];
  for (i15 = 0; i15 < loop_ub; i15++) {
    b_xx->data[i15] = x->data[i15] - x_mean;
  }

  emxInit_real_T(&r0, 1);
  power(b_xx, r0);
  i15 = b_xx->size[0];
  b_xx->size[0] = x->size[0];
  emxEnsureCapacity_real_T(b_xx, i15);
  loop_ub = x->size[0];
  for (i15 = 0; i15 < loop_ub; i15++) {
    b_xx->data[i15] = (x->data[i15] - x_mean) * (y->data[i15] - y_mean);
  }

  *slope = sum(b_xx) / sum(r0);
  i15 = b_xx->size[0];
  b_xx->size[0] = y->size[0];
  emxEnsureCapacity_real_T(b_xx, i15);
  loop_ub = y->size[0];
  emxFree_real_T(&r0);
  for (i15 = 0; i15 < loop_ub; i15++) {
    b_xx->data[i15] = y->data[i15] - *slope * x->data[i15];
  }

  *b_const = sum(b_xx) / (double)x->size[0];
  emxFree_real_T(&b_xx);
  emxFree_real_T(&x);
}

/* End of code generation (Coder_scd_fitting.c) */
