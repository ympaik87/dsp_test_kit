/*
 * Coder_signal_corrector.c
 *
 * Code generation for function 'Coder_signal_corrector'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_signal_corrector.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "Coder_linear_fitting.h"
#include "Coder_Indirect_curvature_v2.h"

/* Function Definitions */
void Coder_signal_corrector(const double x_data[], double RD_data[], double EFC0,
  double TC)
{
  double cuv_data[100];
  int cuv_size[2];
  int i77;
  int i78;
  emxArray_real_T *fit_itv;
  int i79;
  int loop_ub;
  int n;
  int idx;
  boolean_T exitg1;
  double ex;
  int b_idx;
  double TC_minus_maxc_tmp;
  emxArray_real_T *x;
  emxArray_real_T *RD;
  double slope;
  double gap_tmp;
  double gap;
  double a_tmp;
  double a;
  double RD_seg_diff_middle_data[100];
  double segment_middle2_data[100];
  int i80;
  int i81;
  signed char tmp_data[100];
  Coder_Indirect_curvature_v2(RD_data, TC, cuv_data, cuv_size);
  if (EFC0 + 1.0 > cuv_size[1]) {
    i77 = 0;
    i78 = 0;
  } else {
    i77 = (int)(EFC0 + 1.0) - 1;
    i78 = cuv_size[1];
  }

  emxInit_real_T(&fit_itv, 2);
  i79 = fit_itv->size[0] * fit_itv->size[1];
  fit_itv->size[0] = 1;
  loop_ub = (int)EFC0;
  fit_itv->size[1] = (loop_ub + i78) - i77;
  emxEnsureCapacity_real_T(fit_itv, i79);
  for (i79 = 0; i79 < loop_ub; i79++) {
    fit_itv->data[i79] = rtInf;
  }

  n = i78 - i77;
  for (i78 = 0; i78 < n; i78++) {
    fit_itv->data[i78 + loop_ub] = cuv_data[i77 + i78];
  }

  n = fit_itv->size[1];
  if (fit_itv->size[1] <= 2) {
    if (fit_itv->size[1] == 1) {
      idx = 1;
    } else if ((fit_itv->data[0] > fit_itv->data[1]) || (rtIsNaN(fit_itv->data[0])
                && (!rtIsNaN(fit_itv->data[1])))) {
      idx = 2;
    } else {
      idx = 1;
    }
  } else {
    if (!rtIsNaN(fit_itv->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      loop_ub = 2;
      exitg1 = false;
      while ((!exitg1) && (loop_ub <= fit_itv->size[1])) {
        if (!rtIsNaN(fit_itv->data[loop_ub - 1])) {
          idx = loop_ub;
          exitg1 = true;
        } else {
          loop_ub++;
        }
      }
    }

    if (idx == 0) {
      idx = 1;
    } else {
      ex = fit_itv->data[idx - 1];
      i77 = idx + 1;
      for (loop_ub = i77; loop_ub <= n; loop_ub++) {
        if (ex > fit_itv->data[loop_ub - 1]) {
          ex = fit_itv->data[loop_ub - 1];
          idx = loop_ub;
        }
      }
    }
  }

  if ((double)idx + 1.0 > cuv_size[1]) {
    i77 = 1;
    i78 = 0;
  } else {
    i77 = idx + 1;
    i78 = cuv_size[1];
  }

  i79 = fit_itv->size[0] * fit_itv->size[1];
  fit_itv->size[0] = 1;
  fit_itv->size[1] = ((idx + i78) - i77) + 1;
  emxEnsureCapacity_real_T(fit_itv, i79);
  for (i79 = 0; i79 < idx; i79++) {
    fit_itv->data[i79] = rtMinusInf;
  }

  loop_ub = (i78 - i77) + 1;
  for (i78 = 0; i78 < loop_ub; i78++) {
    fit_itv->data[i78 + idx] = cuv_data[(i77 + i78) - 1];
  }

  n = fit_itv->size[1];
  if (fit_itv->size[1] <= 2) {
    if (fit_itv->size[1] == 1) {
      b_idx = 1;
    } else if ((fit_itv->data[0] < fit_itv->data[1]) || (rtIsNaN(fit_itv->data[0])
                && (!rtIsNaN(fit_itv->data[1])))) {
      b_idx = 2;
    } else {
      b_idx = 1;
    }
  } else {
    if (!rtIsNaN(fit_itv->data[0])) {
      b_idx = 1;
    } else {
      b_idx = 0;
      loop_ub = 2;
      exitg1 = false;
      while ((!exitg1) && (loop_ub <= fit_itv->size[1])) {
        if (!rtIsNaN(fit_itv->data[loop_ub - 1])) {
          b_idx = loop_ub;
          exitg1 = true;
        } else {
          loop_ub++;
        }
      }
    }

    if (b_idx == 0) {
      b_idx = 1;
    } else {
      ex = fit_itv->data[b_idx - 1];
      i77 = b_idx + 1;
      for (loop_ub = i77; loop_ub <= n; loop_ub++) {
        if (ex < fit_itv->data[loop_ub - 1]) {
          ex = fit_itv->data[loop_ub - 1];
          b_idx = loop_ub;
        }
      }
    }
  }

  TC_minus_maxc_tmp = TC - (double)b_idx;
  if (TC_minus_maxc_tmp >= 5.0) {
    if (rtIsNaN(TC)) {
      i77 = fit_itv->size[0] * fit_itv->size[1];
      fit_itv->size[0] = 1;
      fit_itv->size[1] = 1;
      emxEnsureCapacity_real_T(fit_itv, i77);
      fit_itv->data[0] = rtNaN;
    } else if (TC < b_idx) {
      fit_itv->size[0] = 1;
      fit_itv->size[1] = 0;
    } else if (rtIsInf(TC) && (b_idx == TC)) {
      i77 = fit_itv->size[0] * fit_itv->size[1];
      fit_itv->size[0] = 1;
      fit_itv->size[1] = 1;
      emxEnsureCapacity_real_T(fit_itv, i77);
      fit_itv->data[0] = rtNaN;
    } else {
      i77 = fit_itv->size[0] * fit_itv->size[1];
      fit_itv->size[0] = 1;
      loop_ub = (int)floor(TC_minus_maxc_tmp);
      fit_itv->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(fit_itv, i77);
      for (i77 = 0; i77 <= loop_ub; i77++) {
        fit_itv->data[i77] = (double)b_idx + (double)i77;
      }
    }

    emxInit_real_T(&x, 1);
    i77 = x->size[0];
    x->size[0] = fit_itv->size[1];
    emxEnsureCapacity_real_T(x, i77);
    loop_ub = fit_itv->size[1];
    for (i77 = 0; i77 < loop_ub; i77++) {
      x->data[i77] = x_data[(int)fit_itv->data[i77] - 1];
    }

    emxInit_real_T(&RD, 1);
    i77 = RD->size[0];
    RD->size[0] = fit_itv->size[1];
    emxEnsureCapacity_real_T(RD, i77);
    loop_ub = fit_itv->size[1];
    for (i77 = 0; i77 < loop_ub; i77++) {
      RD->data[i77] = RD_data[(int)fit_itv->data[i77] - 1];
    }

    Coder_linear_fitting(x, RD, &slope, &ex);
    gap_tmp = RD_data[idx - 1];
    gap = gap_tmp - (slope * (double)idx + ex);
    emxFree_real_T(&RD);
    emxFree_real_T(&x);
    if ((gap > 0.0) && (gap < slope * TC_minus_maxc_tmp)) {
      if (idx > b_idx) {
        i77 = 0;
      } else {
        i77 = idx - 1;
      }

      a_tmp = RD_data[b_idx - 1];
      ex = (double)b_idx - (double)idx;
      a = (a_tmp - gap_tmp) / ex;
      if (idx > b_idx) {
        i78 = 0;
        i79 = 0;
      } else {
        i78 = idx - 1;
        i79 = b_idx;
      }

      loop_ub = i79 - i78;
      for (i79 = 0; i79 < loop_ub; i79++) {
        RD_seg_diff_middle_data[i79] = RD_data[i78 + i79] - (a * (x_data[i77 +
          i79] - x_data[idx - 1]) + gap_tmp);
      }

      if (idx > b_idx) {
        i77 = 0;
        i78 = 0;
      } else {
        i77 = idx - 1;
        i78 = b_idx;
      }

      a = ((a_tmp + gap) - gap_tmp) / ex;
      loop_ub = i78 - i77;
      for (i78 = 0; i78 < loop_ub; i78++) {
        segment_middle2_data[i78] = a * (x_data[i77 + i78] - x_data[idx - 1]) +
          gap_tmp;
      }

      /* RD(max_c)를 뒤에서 쓰므로 여기서 바뀌면 안됨 */
      if (b_idx > TC) {
        i77 = 0;
      } else {
        i77 = b_idx - 1;
      }

      n = (int)TC;
      ex = RD_data[n - 1] - a_tmp;
      a = ex / TC_minus_maxc_tmp;
      if (b_idx > TC) {
        i78 = 0;
        i79 = 0;
      } else {
        i78 = b_idx - 1;
        i79 = b_idx - 1;
      }

      ex = (ex - gap) / TC_minus_maxc_tmp;
      if (b_idx > TC) {
        i80 = 1;
        n = 0;
      } else {
        i80 = b_idx;
      }

      n = (signed char)n - (signed char)i80;
      loop_ub = n + 1;
      for (i81 = 0; i81 <= n; i81++) {
        tmp_data[i81] = (signed char)((signed char)((signed char)i80 + (signed
          char)i81) - 1);
      }

      for (i80 = 0; i80 < loop_ub; i80++) {
        slope = x_data[b_idx - 1];
        cuv_data[i80] = ((ex * (x_data[i79 + i80] - slope) + a_tmp) +
                         (RD_data[i78 + i80] - (a * (x_data[i77 + i80] - slope)
          + a_tmp))) + gap;
      }

      for (i77 = 0; i77 < loop_ub; i77++) {
        RD_data[tmp_data[i77]] = cuv_data[i77];
      }

      if (idx > b_idx) {
        idx = 1;
        b_idx = 0;
      }

      n = (signed char)b_idx - (signed char)idx;
      for (i77 = 0; i77 <= n; i77++) {
        tmp_data[i77] = (signed char)((signed char)((signed char)idx + (signed
          char)i77) - 1);
      }

      loop_ub = n + 1;
      for (i77 = 0; i77 < loop_ub; i77++) {
        RD_data[tmp_data[i77]] = segment_middle2_data[i77] +
          RD_seg_diff_middle_data[i77];
      }
    }
  }

  emxFree_real_T(&fit_itv);
}

/* End of code generation (Coder_signal_corrector.c) */
