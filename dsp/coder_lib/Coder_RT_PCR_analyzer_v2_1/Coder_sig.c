/*
 * Coder_sig.c
 *
 * Code generation for function 'Coder_sig'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_sig.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "power.h"

/* Function Definitions */
void Coder_sig(const double param[4], const double xval_data[], const int
               xval_size[1], double f_data[], int f_size[1])
{
  emxArray_real_T *b_param;
  double x;
  int i19;
  int loop_ub;
  emxInit_real_T(&b_param, 1);
  x = param[1] - param[0];
  i19 = b_param->size[0];
  b_param->size[0] = xval_size[0];
  emxEnsureCapacity_real_T(b_param, i19);
  loop_ub = xval_size[0];
  for (i19 = 0; i19 < loop_ub; i19++) {
    b_param->data[i19] = (param[2] - xval_data[i19]) * param[3];
  }

  b_power(b_param->data, b_param->size, f_data, f_size);
  loop_ub = f_size[0];
  emxFree_real_T(&b_param);
  for (i19 = 0; i19 < loop_ub; i19++) {
    f_data[i19] = param[0] + x / (1.0 + f_data[i19]);
  }
}

/* End of code generation (Coder_sig.c) */
