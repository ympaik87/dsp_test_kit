/*
 * Coder_Section_Unimportant_v3.c
 *
 * Code generation for function 'Coder_Section_Unimportant_v3'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_Section_Unimportant_v3.h"
#include "AutoBaseline_v2_emxutil.h"
#include "power.h"

/* Function Definitions */
double Coder_Section_Unimportant_v3(const double x_data[], const int x_size[1],
  const double RD_data[], const int RD_size[1], double SFC, double MFC, double
  TC, double DRFU, double *result_well, double *DataProcessNum, double AR,
  double FB)
{
  double EFC;
  int i38;
  int i39;
  int n;
  int idx;
  double x2_sum;
  int k;
  boolean_T exitg1;
  int loop_ub_tmp;
  double varargin_1_data[199];
  double x_sum;
  double x_mean;
  emxArray_real_T *r3;
  emxArray_real_T b_x_data;
  int x2_size[1];
  double x2_data[100];
  double y_sum;
  double x2_mean;
  double S_11;
  double c_x_data[100];
  double y;
  double S_12;
  emxArray_real_T b_x2_data;
  double S_22;
  double S_y1;
  *result_well = 0.0;
  if (SFC > TC) {
    i38 = 1;
    i39 = 1;
  } else {
    i38 = (int)SFC;
    i39 = (int)TC + 1;
  }

  n = RD_size[0];
  if (RD_size[0] <= 2) {
    if (RD_size[0] == 1) {
      x2_sum = RD_data[0];
    } else if ((RD_data[0] < RD_data[1]) || (rtIsNaN(RD_data[0]) && (!rtIsNaN
                 (RD_data[1])))) {
      x2_sum = RD_data[1];
    } else {
      x2_sum = RD_data[0];
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
      x2_sum = RD_data[0];
    } else {
      x2_sum = RD_data[idx - 1];
      idx++;
      for (k = idx; k <= n; k++) {
        x_sum = RD_data[k - 1];
        if (x2_sum < x_sum) {
          x2_sum = x_sum;
        }
      }
    }
  }

  loop_ub_tmp = i39 - i38;
  for (i39 = 0; i39 < loop_ub_tmp; i39++) {
    varargin_1_data[i39] = RD_data[(i38 + i39) - 1];
  }

  n = loop_ub_tmp - 1;
  if (loop_ub_tmp <= 2) {
    if (loop_ub_tmp == 1) {
      x_mean = RD_data[i38 - 1];
    } else if ((RD_data[i38 - 1] > RD_data[i38]) || (rtIsNaN(RD_data[i38 - 1]) &&
                (!rtIsNaN(RD_data[i38])))) {
      x_mean = RD_data[i38];
    } else {
      x_mean = RD_data[i38 - 1];
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
      x_mean = RD_data[i38 - 1];
    } else {
      x_mean = varargin_1_data[idx - 1];
      i38 = idx + 1;
      for (k = i38; k <= n + 1; k++) {
        x_sum = varargin_1_data[k - 1];
        if (x_mean > x_sum) {
          x_mean = x_sum;
        }
      }
    }
  }

  emxInit_real_T(&r3, 1);
  if (((x2_sum - x_mean > 2.0 * DRFU * AR) && (RD_data[(int)TC - 1] - RD_data[0]
        > 0.0)) || (FB == 1.0)) {
    EFC = MFC;
  } else {
    b_x_data.data = (double *)&x_data[0];
    b_x_data.size = (int *)&x_size[0];
    b_x_data.allocatedSize = -1;
    b_x_data.numDimensions = 1;
    b_x_data.canFreeData = false;
    power(&b_x_data, r3);
    x2_size[0] = r3->size[0];
    idx = r3->size[0];
    for (i38 = 0; i38 < idx; i38++) {
      x2_data[i38] = r3->data[i38];
    }

    idx = x_size[0];
    if (x_size[0] == 0) {
      x_sum = 0.0;
    } else {
      x_sum = x_data[0];
      for (k = 2; k <= idx; k++) {
        x_sum += x_data[k - 1];
      }
    }

    idx = x2_size[0];
    if (x2_size[0] == 0) {
      x2_sum = 0.0;
    } else {
      x2_sum = x2_data[0];
      for (k = 2; k <= idx; k++) {
        x2_sum += x2_data[k - 1];
      }
    }

    idx = RD_size[0];
    if (RD_size[0] == 0) {
      y_sum = 0.0;
    } else {
      y_sum = RD_data[0];
      for (k = 2; k <= idx; k++) {
        y_sum += RD_data[k - 1];
      }
    }

    x_mean = x_sum / TC;
    x2_mean = x2_sum / TC;
    S_11 = x2_sum - x_mean * x_sum;
    loop_ub_tmp = x_size[0];
    idx = x_size[0];
    for (i38 = 0; i38 < idx; i38++) {
      c_x_data[i38] = x_data[i38] * x2_data[i38];
    }

    if (loop_ub_tmp == 0) {
      y = 0.0;
    } else {
      y = c_x_data[0];
      for (k = 2; k <= loop_ub_tmp; k++) {
        y += c_x_data[k - 1];
      }
    }

    S_12 = y - x_sum * x2_mean;
    b_x2_data.data = &x2_data[0];
    b_x2_data.size = &x2_size[0];
    b_x2_data.allocatedSize = 100;
    b_x2_data.numDimensions = 1;
    b_x2_data.canFreeData = false;
    power(&b_x2_data, r3);
    loop_ub_tmp = r3->size[0];
    idx = r3->size[0];
    for (i38 = 0; i38 < idx; i38++) {
      c_x_data[i38] = r3->data[i38];
    }

    if (loop_ub_tmp == 0) {
      y = 0.0;
    } else {
      y = c_x_data[0];
      for (k = 2; k <= loop_ub_tmp; k++) {
        y += c_x_data[k - 1];
      }
    }

    S_22 = y - x2_mean * x2_sum;
    idx = RD_size[0];
    for (i38 = 0; i38 < idx; i38++) {
      c_x_data[i38] = RD_data[i38] * x_data[i38];
    }

    idx = RD_size[0];
    if (RD_size[0] == 0) {
      y = 0.0;
    } else {
      y = c_x_data[0];
      for (k = 2; k <= idx; k++) {
        y += c_x_data[k - 1];
      }
    }

    S_y1 = y - y_sum * x_mean;
    x2_size[0] = RD_size[0];
    idx = RD_size[0];
    for (i38 = 0; i38 < idx; i38++) {
      x2_data[i38] *= RD_data[i38];
    }

    idx = x2_size[0];
    if (x2_size[0] == 0) {
      y = 0.0;
    } else {
      y = x2_data[0];
      for (k = 2; k <= idx; k++) {
        y += x2_data[k - 1];
      }
    }

    x_mean = y - y_sum * x2_mean;

    /*  y=coeff1*x^2 + coeff2*x + coeff3 */
    x_sum = S_22 * S_11 - S_12 * S_12;
    x2_sum = (x_mean * S_11 - S_y1 * S_12) / x_sum;
    if (x2_sum < 0.0) {
      *result_well = 1.0;
      *DataProcessNum = 3.0;
      EFC = 0.0;
    } else {
      x2_sum = floor(-((S_y1 * S_22 - x_mean * S_12) / x_sum) / x2_sum / 2.0 -
                     3.0);
      if ((TC < x2_sum) || rtIsNaN(x2_sum)) {
        x2_sum = TC;
      }

      if ((MFC > x2_sum) || rtIsNaN(x2_sum)) {
        EFC = MFC;
      } else {
        EFC = x2_sum;
      }
    }
  }

  emxFree_real_T(&r3);
  return EFC;
}

/* End of code generation (Coder_Section_Unimportant_v3.c) */
