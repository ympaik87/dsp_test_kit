/*
 * power.c
 *
 * Code generation for function 'power'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "power.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "Coder_RT_PCR_analyzer_v2_1_rtwutil.h"

/* Function Definitions */
void b_power(const double b_data[], const int b_size[1], double y_data[], int
             y_size[1])
{
  int nx;
  int k;
  y_size[0] = (signed char)b_size[0];
  nx = (signed char)b_size[0];
  for (k = 0; k < nx; k++) {
    y_data[k] = rt_powd_snf(10.0, b_data[k]);
  }
}

void power(const emxArray_real_T *a, emxArray_real_T *y)
{
  unsigned int a_idx_0;
  int nx;
  int k;
  a_idx_0 = (unsigned int)a->size[0];
  nx = y->size[0];
  y->size[0] = (int)a_idx_0;
  emxEnsureCapacity_real_T(y, nx);
  a_idx_0 = (unsigned int)a->size[0];
  nx = (int)a_idx_0;
  for (k = 0; k < nx; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

/* End of code generation (power.c) */
