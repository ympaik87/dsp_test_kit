/*
 * Coder_sig_part1.c
 *
 * Code generation for function 'Coder_sig_part1'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_sig_part1.h"
#include "Coder_RT_PCR_analyzer_emxutil.h"
#include "power.h"
#include "Coder_RT_PCR_analyzer_rtwutil.h"

/* Function Definitions */
void Coder_sig_part1(const double param[4], const double xval_data[], const int
                     xval_size[1], const double fixed_pt[2], double f_data[],
                     int f_size[1])
{
  emxArray_real_T *b_param;
  double x;
  int i25;
  int loop_ub;
  double tmp_data[100];
  int tmp_size[1];
  emxInit_real_T(&b_param, 1);
  x = (fixed_pt[1] - param[0]) * (1.0 + rt_powd_snf(10.0, (param[2] - fixed_pt[0])
    * param[3]));
  i25 = b_param->size[0];
  b_param->size[0] = xval_size[0];
  emxEnsureCapacity_real_T(b_param, i25);
  loop_ub = xval_size[0];
  for (i25 = 0; i25 < loop_ub; i25++) {
    b_param->data[i25] = (param[2] - xval_data[i25]) * param[3];
  }

  b_power(b_param->data, b_param->size, tmp_data, tmp_size);
  f_size[0] = tmp_size[0];
  loop_ub = tmp_size[0];
  emxFree_real_T(&b_param);
  for (i25 = 0; i25 < loop_ub; i25++) {
    f_data[i25] = param[0] + x / (1.0 + tmp_data[i25]);
  }
}

/* End of code generation (Coder_sig_part1.c) */
