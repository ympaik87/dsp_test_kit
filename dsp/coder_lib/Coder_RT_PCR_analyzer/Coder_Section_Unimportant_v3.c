/*
 * Coder_Section_Unimportant_v3.c
 *
 * Code generation for function 'Coder_Section_Unimportant_v3'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_Section_Unimportant_v3.h"
#include "Coder_fst_fitting.h"

/* Function Definitions */
double Coder_Section_Unimportant_v3(const double x_data[], const int x_size[1],
  const double RD_data[], const int RD_size[1], double SFC, double MFC, double
  TC, double DRFU, double *result_well, double *DataProcessNum, double AR,
  double FB)
{
  double EFC;
  int i47;
  int i48;
  int n;
  int idx;
  double f_cff_idx_0;
  int k;
  boolean_T exitg1;
  int loop_ub_tmp;
  double varargin_1_data[199];
  double d19;
  double f_cff_idx_1;
  emxArray_real_T b_x_data;
  *result_well = 0.0;
  if (SFC > TC) {
    i47 = 1;
    i48 = 1;
  } else {
    i47 = (int)SFC;
    i48 = (int)TC + 1;
  }

  n = RD_size[0];
  if (RD_size[0] <= 2) {
    if (RD_size[0] == 1) {
      f_cff_idx_0 = RD_data[0];
    } else if ((RD_data[0] < RD_data[1]) || (rtIsNaN(RD_data[0]) && (!rtIsNaN
                 (RD_data[1])))) {
      f_cff_idx_0 = RD_data[1];
    } else {
      f_cff_idx_0 = RD_data[0];
    }
  } else {
    if (!rtIsNaN(RD_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= RD_size[0])) {
        if (!rtIsNaN(RD_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      f_cff_idx_0 = RD_data[0];
    } else {
      f_cff_idx_0 = RD_data[idx - 1];
      loop_ub_tmp = idx + 1;
      for (k = loop_ub_tmp; k <= n; k++) {
        d19 = RD_data[k - 1];
        if (f_cff_idx_0 < d19) {
          f_cff_idx_0 = d19;
        }
      }
    }
  }

  loop_ub_tmp = i48 - i47;
  for (i48 = 0; i48 < loop_ub_tmp; i48++) {
    varargin_1_data[i48] = RD_data[(i47 + i48) - 1];
  }

  if (loop_ub_tmp <= 2) {
    if (loop_ub_tmp == 1) {
      f_cff_idx_1 = RD_data[i47 - 1];
    } else if ((RD_data[i47 - 1] > RD_data[i47]) || (rtIsNaN(RD_data[i47 - 1]) &&
                (!rtIsNaN(RD_data[i47])))) {
      f_cff_idx_1 = RD_data[i47];
    } else {
      f_cff_idx_1 = RD_data[i47 - 1];
    }
  } else {
    if (!rtIsNaN(varargin_1_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= loop_ub_tmp)) {
        if (!rtIsNaN(varargin_1_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      f_cff_idx_1 = RD_data[i47 - 1];
    } else {
      f_cff_idx_1 = varargin_1_data[idx - 1];
      i47 = idx + 1;
      for (k = i47; k <= loop_ub_tmp; k++) {
        d19 = varargin_1_data[k - 1];
        if (f_cff_idx_1 > d19) {
          f_cff_idx_1 = d19;
        }
      }
    }
  }

  if (((f_cff_idx_0 - f_cff_idx_1 > 2.0 * DRFU * AR) && (RD_data[(int)TC - 1] -
        RD_data[0] > 0.0)) || (FB == 1.0)) {
    EFC = MFC;
  } else {
    b_x_data.data = (double *)&x_data[0];
    b_x_data.size = (int *)&x_size[0];
    b_x_data.allocatedSize = -1;
    b_x_data.numDimensions = 1;
    b_x_data.canFreeData = false;
    Coder_fst_fitting(&b_x_data, RD_data, RD_size, TC, &f_cff_idx_0,
                      &f_cff_idx_1, &d19);
    if (f_cff_idx_0 < 0.0) {
      *result_well = 1.0;
      *DataProcessNum = 3.0;
      EFC = 0.0;
    } else {
      f_cff_idx_0 = floor(-f_cff_idx_1 / f_cff_idx_0 / 2.0 - 3.0);
      if ((TC < f_cff_idx_0) || rtIsNaN(f_cff_idx_0)) {
        f_cff_idx_0 = TC;
      }

      if ((MFC > f_cff_idx_0) || rtIsNaN(f_cff_idx_0)) {
        EFC = MFC;
      } else {
        EFC = f_cff_idx_0;
      }
    }
  }

  return EFC;
}

/* End of code generation (Coder_Section_Unimportant_v3.c) */
