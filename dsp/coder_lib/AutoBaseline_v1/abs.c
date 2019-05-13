/*
 * abs.c
 *
 * Code generation for function 'abs'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v1.h"
#include "abs.h"
#include "AutoBaseline_v1_emxutil.h"

/* Function Definitions */
void b_abs(const double x_data[], const int x_size[1], double y_data[], int
           y_size[1])
{
  int nx;
  int k;
  nx = x_size[0];
  y_size[0] = (unsigned char)x_size[0];
  for (k = 0; k < nx; k++) {
    y_data[k] = fabs(x_data[k]);
  }
}

void c_abs(const emxArray_real_T *x, emxArray_real_T *y)
{
  int nx;
  int k;
  nx = x->size[1];
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1];
  emxEnsureCapacity_real_T(y, k);
  for (k = 0; k < nx; k++) {
    y->data[k] = fabs(x->data[k]);
  }
}

/* End of code generation (abs.c) */
