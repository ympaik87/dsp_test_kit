/*
 * Coder_signal_corrector.c
 *
 * Code generation for function 'Coder_signal_corrector'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_signal_corrector.h"
#include "Coder_RT_PCR_analyzer_emxutil.h"
#include "Coder_linear_fitting.h"
#include "Coder_Indirect_curvature_v2.h"

/* Function Definitions */
void Coder_signal_corrector(const double x_data[], double RD_data[], double EFC0,
  double TC)
{
  double cuv_data[100];
  int cuv_size[2];
  int i67;
  int i68;
  emxArray_real_T *fit_itv;
  int i69;
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
  int i70;
  int i71;
  signed char tmp_data[100];
  Coder_Indirect_curvature_v2(RD_data, TC, cuv_data, cuv_size);
  if (EFC0 + 1.0 > cuv_size[1]) {
    i67 = 0;
    i68 = 0;
  } else {
    i67 = (int)(EFC0 + 1.0) - 1;
    i68 = cuv_size[1];
  }

  emxInit_real_T(&fit_itv, 2);
  i69 = fit_itv->size[0] * fit_itv->size[1];
  fit_itv->size[0] = 1;
  loop_ub = (int)EFC0;
  fit_itv->size[1] = (loop_ub + i68) - i67;
  emxEnsureCapacity_real_T(fit_itv, i69);
  for (i69 = 0; i69 < loop_ub; i69++) {
    fit_itv->data[i69] = rtInf;
  }

  n = i68 - i67;
  for (i68 = 0; i68 < n; i68++) {
    fit_itv->data[i68 + loop_ub] = cuv_data[i67 + i68];
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
      i67 = idx + 1;
      for (loop_ub = i67; loop_ub <= n; loop_ub++) {
        if (ex > fit_itv->data[loop_ub - 1]) {
          ex = fit_itv->data[loop_ub - 1];
          idx = loop_ub;
        }
      }
    }
  }

  if ((double)idx + 1.0 > cuv_size[1]) {
    i67 = 1;
    i68 = 0;
  } else {
    i67 = idx + 1;
    i68 = cuv_size[1];
  }

  i69 = fit_itv->size[0] * fit_itv->size[1];
  fit_itv->size[0] = 1;
  fit_itv->size[1] = ((idx + i68) - i67) + 1;
  emxEnsureCapacity_real_T(fit_itv, i69);
  for (i69 = 0; i69 < idx; i69++) {
    fit_itv->data[i69] = rtMinusInf;
  }

  loop_ub = (i68 - i67) + 1;
  for (i68 = 0; i68 < loop_ub; i68++) {
    fit_itv->data[i68 + idx] = cuv_data[(i67 + i68) - 1];
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
      i67 = b_idx + 1;
      for (loop_ub = i67; loop_ub <= n; loop_ub++) {
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
      i67 = fit_itv->size[0] * fit_itv->size[1];
      fit_itv->size[0] = 1;
      fit_itv->size[1] = 1;
      emxEnsureCapacity_real_T(fit_itv, i67);
      fit_itv->data[0] = rtNaN;
    } else if (TC < b_idx) {
      fit_itv->size[0] = 1;
      fit_itv->size[1] = 0;
    } else if (rtIsInf(TC) && (b_idx == TC)) {
      i67 = fit_itv->size[0] * fit_itv->size[1];
      fit_itv->size[0] = 1;
      fit_itv->size[1] = 1;
      emxEnsureCapacity_real_T(fit_itv, i67);
      fit_itv->data[0] = rtNaN;
    } else {
      i67 = fit_itv->size[0] * fit_itv->size[1];
      fit_itv->size[0] = 1;
      loop_ub = (int)floor(TC_minus_maxc_tmp);
      fit_itv->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(fit_itv, i67);
      for (i67 = 0; i67 <= loop_ub; i67++) {
        fit_itv->data[i67] = (double)b_idx + (double)i67;
      }
    }

    emxInit_real_T(&x, 1);
    i67 = x->size[0];
    x->size[0] = fit_itv->size[1];
    emxEnsureCapacity_real_T(x, i67);
    loop_ub = fit_itv->size[1];
    for (i67 = 0; i67 < loop_ub; i67++) {
      x->data[i67] = x_data[(int)fit_itv->data[i67] - 1];
    }

    emxInit_real_T(&RD, 1);
    i67 = RD->size[0];
    RD->size[0] = fit_itv->size[1];
    emxEnsureCapacity_real_T(RD, i67);
    loop_ub = fit_itv->size[1];
    for (i67 = 0; i67 < loop_ub; i67++) {
      RD->data[i67] = RD_data[(int)fit_itv->data[i67] - 1];
    }

    Coder_linear_fitting(x, RD, &slope, &ex);
    gap_tmp = RD_data[idx - 1];
    gap = gap_tmp - (slope * (double)idx + ex);
    emxFree_real_T(&RD);
    emxFree_real_T(&x);
    if ((gap > 0.0) && (gap < slope * TC_minus_maxc_tmp)) {
      if (idx > b_idx) {
        i67 = 0;
      } else {
        i67 = idx - 1;
      }

      a_tmp = RD_data[b_idx - 1];
      ex = (double)b_idx - (double)idx;
      a = (a_tmp - gap_tmp) / ex;
      if (idx > b_idx) {
        i68 = 0;
        i69 = 0;
      } else {
        i68 = idx - 1;
        i69 = b_idx;
      }

      loop_ub = i69 - i68;
      for (i69 = 0; i69 < loop_ub; i69++) {
        RD_seg_diff_middle_data[i69] = RD_data[i68 + i69] - (a * (x_data[i67 +
          i69] - x_data[idx - 1]) + gap_tmp);
      }

      if (idx > b_idx) {
        i67 = 0;
        i68 = 0;
      } else {
        i67 = idx - 1;
        i68 = b_idx;
      }

      a = ((a_tmp + gap) - gap_tmp) / ex;
      loop_ub = i68 - i67;
      for (i68 = 0; i68 < loop_ub; i68++) {
        segment_middle2_data[i68] = a * (x_data[i67 + i68] - x_data[idx - 1]) +
          gap_tmp;
      }

      /* RD(max_c)를 뒤에서 쓰므로 여기서 바뀌면 안됨 */
      if (b_idx > TC) {
        i67 = 0;
      } else {
        i67 = b_idx - 1;
      }

      n = (int)TC;
      ex = RD_data[n - 1] - a_tmp;
      a = ex / TC_minus_maxc_tmp;
      if (b_idx > TC) {
        i68 = 0;
        i69 = 0;
      } else {
        i68 = b_idx - 1;
        i69 = b_idx - 1;
      }

      ex = (ex - gap) / TC_minus_maxc_tmp;
      if (b_idx > TC) {
        i70 = 1;
        n = 0;
      } else {
        i70 = b_idx;
      }

      n = (signed char)n - (signed char)i70;
      loop_ub = n + 1;
      for (i71 = 0; i71 <= n; i71++) {
        tmp_data[i71] = (signed char)((signed char)((signed char)i70 + (signed
          char)i71) - 1);
      }

      for (i70 = 0; i70 < loop_ub; i70++) {
        slope = x_data[b_idx - 1];
        cuv_data[i70] = ((ex * (x_data[i69 + i70] - slope) + a_tmp) +
                         (RD_data[i68 + i70] - (a * (x_data[i67 + i70] - slope)
          + a_tmp))) + gap;
      }

      for (i67 = 0; i67 < loop_ub; i67++) {
        RD_data[tmp_data[i67]] = cuv_data[i67];
      }

      if (idx > b_idx) {
        idx = 1;
        b_idx = 0;
      }

      n = (signed char)b_idx - (signed char)idx;
      for (i67 = 0; i67 <= n; i67++) {
        tmp_data[i67] = (signed char)((signed char)((signed char)idx + (signed
          char)i67) - 1);
      }

      loop_ub = n + 1;
      for (i67 = 0; i67 < loop_ub; i67++) {
        RD_data[tmp_data[i67]] = segment_middle2_data[i67] +
          RD_seg_diff_middle_data[i67];
      }
    }
  }

  emxFree_real_T(&fit_itv);
}

/* End of code generation (Coder_signal_corrector.c) */
