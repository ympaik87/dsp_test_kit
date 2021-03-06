/*
 * Coder_ABSD_corrector_v3_1.c
 *
 * Code generation for function 'Coder_ABSD_corrector_v3_1'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_ABSD_corrector_v3_1.h"
#include "AutoBaseline_v2_emxutil.h"
#include "Coder_local_smoothing.h"
#include "Coder_LSR2.h"
#include "var.h"
#include "sum.h"
#include "abs.h"
#include "diff.h"

/* Function Definitions */
double Coder_ABSD_corrector_v3_1(double SFC, double MFC, double ABSD_data[], int
  ABSD_size[1], double Thrd, const double RD_diff_data[], double TC)
{
  double min_cycle;
  int i57;
  int k;
  emxArray_real_T *varargin_1;
  int n;
  int loop_ub;
  int idx;
  double ex;
  boolean_T exitg1;
  int corr_part_size[1];
  double corr_part_data[100];
  int b_idx;
  double b_ex;
  double scale_corr_part;
  double tmp_data[198];
  int tmp_size[1];
  double b_tmp_data[198];
  int b_tmp_size[1];
  emxArray_real_T c_tmp_data;
  double amp_ratio;
  double LSR;
  int b_ABSD_size[1];
  double b_ABSD_data[100];
  double c_idx;
  double d_idx;
  int c_ABSD_size[1];
  int d_ABSD_size[1];
  int d_tmp_data[100];

  /* v3과 다른점 : ABSD(1:min_cycle)=ABSD(1:min_cycle)-Coder_local_smoothing(ABSD(1:min_cycle))+min_val;  */
  if (SFC > ABSD_size[0]) {
    i57 = 0;
    k = 0;
  } else {
    i57 = (int)SFC - 1;
    k = ABSD_size[0];
  }

  emxInit_real_T(&varargin_1, 1);
  n = varargin_1->size[0];
  loop_ub = (int)(SFC - 1.0);
  varargin_1->size[0] = (loop_ub + k) - i57;
  emxEnsureCapacity_real_T(varargin_1, n);
  for (n = 0; n < loop_ub; n++) {
    varargin_1->data[n] = rtInf;
  }

  n = k - i57;
  for (k = 0; k < n; k++) {
    varargin_1->data[k + loop_ub] = ABSD_data[i57 + k];
  }

  n = varargin_1->size[0];
  if (varargin_1->size[0] <= 2) {
    if (varargin_1->size[0] == 1) {
      ex = varargin_1->data[0];
      idx = 1;
    } else if ((varargin_1->data[0] > varargin_1->data[1]) || (rtIsNaN
                (varargin_1->data[0]) && (!rtIsNaN(varargin_1->data[1])))) {
      ex = varargin_1->data[1];
      idx = 2;
    } else {
      ex = varargin_1->data[0];
      idx = 1;
    }
  } else {
    if (!rtIsNaN(varargin_1->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= varargin_1->size[0])) {
        if (!rtIsNaN(varargin_1->data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      ex = varargin_1->data[0];
      idx = 1;
    } else {
      ex = varargin_1->data[idx - 1];
      i57 = idx + 1;
      for (k = i57; k <= n; k++) {
        if (ex > varargin_1->data[k - 1]) {
          ex = varargin_1->data[k - 1];
          idx = k;
        }
      }
    }
  }

  min_cycle = idx;
  if (SFC > idx) {
    i57 = 0;
    k = 0;
  } else {
    i57 = (int)SFC - 1;
    k = idx;
  }

  n = k - i57;
  corr_part_size[0] = n;
  for (k = 0; k < n; k++) {
    corr_part_data[k] = ABSD_data[i57 + k];
  }

  if (n <= 2) {
    if (n == 1) {
      b_ex = corr_part_data[0];
    } else if ((corr_part_data[0] < corr_part_data[1]) || (rtIsNaN
                (corr_part_data[0]) && (!rtIsNaN(corr_part_data[1])))) {
      b_ex = corr_part_data[1];
    } else {
      b_ex = corr_part_data[0];
    }
  } else {
    if (!rtIsNaN(corr_part_data[0])) {
      b_idx = 1;
    } else {
      b_idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= n)) {
        if (!rtIsNaN(corr_part_data[k - 1])) {
          b_idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (b_idx == 0) {
      b_ex = corr_part_data[0];
    } else {
      b_ex = corr_part_data[b_idx - 1];
      i57 = b_idx + 1;
      for (k = i57; k <= n; k++) {
        amp_ratio = corr_part_data[k - 1];
        if (b_ex < amp_ratio) {
          b_ex = amp_ratio;
        }
      }
    }
  }

  scale_corr_part = b_ex - ex;
  diff(corr_part_data, corr_part_size, tmp_data, tmp_size);
  b_abs(tmp_data, tmp_size, b_tmp_data, b_tmp_size);
  c_tmp_data.data = &b_tmp_data[0];
  c_tmp_data.size = &b_tmp_size[0];
  c_tmp_data.allocatedSize = 198;
  c_tmp_data.numDimensions = 1;
  c_tmp_data.canFreeData = false;
  LSR = sum(&c_tmp_data) / scale_corr_part;

  /* Length Scale Ratio */
  if (SFC > MFC) {
    i57 = 0;
    k = 0;
  } else {
    i57 = (int)SFC - 1;
    k = (int)MFC;
  }

  b_idx = k - i57;
  b_ABSD_size[0] = b_idx;
  for (k = 0; k < b_idx; k++) {
    b_ABSD_data[k] = ABSD_data[i57 + k];
  }

  if ((var(b_ABSD_data, b_ABSD_size) / var(ABSD_data, ABSD_size) < 0.05) && (LSR
       < 5.0) && ((ABSD_data[idx - 2] - ABSD_data[idx - 1]) / scale_corr_part <
                  0.7)) {
    /*          (ABSD(min_cycle-1)-ABSD(min_cycle))/scale_corr_part */
    if (SFC > ABSD_size[0]) {
      i57 = 0;
      k = 0;
    } else {
      i57 = (int)SFC - 1;
      k = ABSD_size[0];
    }

    n = varargin_1->size[0];
    varargin_1->size[0] = (loop_ub + k) - i57;
    emxEnsureCapacity_real_T(varargin_1, n);
    for (n = 0; n < loop_ub; n++) {
      varargin_1->data[n] = rtMinusInf;
    }

    n = k - i57;
    for (k = 0; k < n; k++) {
      varargin_1->data[k + loop_ub] = ABSD_data[i57 + k];
    }

    n = varargin_1->size[0];
    if (varargin_1->size[0] <= 2) {
      if (varargin_1->size[0] == 1) {
        b_ex = varargin_1->data[0];
      } else if ((varargin_1->data[0] < varargin_1->data[1]) || (rtIsNaN
                  (varargin_1->data[0]) && (!rtIsNaN(varargin_1->data[1])))) {
        b_ex = varargin_1->data[1];
      } else {
        b_ex = varargin_1->data[0];
      }
    } else {
      if (!rtIsNaN(varargin_1->data[0])) {
        b_idx = 1;
      } else {
        b_idx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= varargin_1->size[0])) {
          if (!rtIsNaN(varargin_1->data[k - 1])) {
            b_idx = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (b_idx == 0) {
        b_ex = varargin_1->data[0];
      } else {
        b_ex = varargin_1->data[b_idx - 1];
        i57 = b_idx + 1;
        for (k = i57; k <= n; k++) {
          if (b_ex < varargin_1->data[k - 1]) {
            b_ex = varargin_1->data[k - 1];
          }
        }
      }
    }

    /*                  scale_corr_part/Thrd */
    b_ex -= ex;
    if (((double)idx + 5.0 < TC) || rtIsNaN(TC)) {
      c_idx = (double)idx + 5.0;
    } else {
      c_idx = TC;
    }

    if (((double)idx + 1.0 < TC) || rtIsNaN(TC)) {
      d_idx = (double)idx + 1.0;
    } else {
      d_idx = TC;
    }

    amp_ratio = (ABSD_data[(int)c_idx - 1] - ABSD_data[(int)d_idx - 1]) / b_ex;
    if (amp_ratio > 0.2) {
      amp_ratio = 0.05;
    } else if (amp_ratio > 0.05) {
      if (scale_corr_part / Thrd > 0.5) {
        /*                  LSR */
        if (LSR > 2.5) {
          amp_ratio = 0.2;
        } else {
          if (SFC > idx) {
            i57 = 0;
            k = 0;
            n = 0;
          } else {
            i57 = (int)SFC - 1;
            k = idx;
            n = (int)SFC - 1;
          }

          b_idx = k - i57;
          d_ABSD_size[0] = b_idx;
          for (k = 0; k < b_idx; k++) {
            b_ABSD_data[k] = ABSD_data[i57 + k] + RD_diff_data[n + k];
          }

          if (Coder_LSR2(b_ABSD_data, d_ABSD_size, Thrd) < 2.0) {
            amp_ratio = 0.05;
          } else {
            amp_ratio = 0.15;
          }
        }
      } else {
        if (SFC > idx) {
          i57 = 0;
          k = 0;
          n = 0;
        } else {
          i57 = (int)SFC - 1;
          k = idx;
          n = (int)SFC - 1;
        }

        b_idx = k - i57;
        d_ABSD_size[0] = b_idx;
        for (k = 0; k < b_idx; k++) {
          b_ABSD_data[k] = ABSD_data[i57 + k] + RD_diff_data[n + k];
        }

        if (Coder_LSR2(b_ABSD_data, d_ABSD_size, Thrd / 2.0) < 2.0) {
          amp_ratio = 0.05;
        } else {
          amp_ratio = 0.1;
        }
      }
    } else {
      amp_ratio = 0.15;
    }

    /*          scale_corr_part/(max_val-min_val) */
    /*          ratio */
    if (scale_corr_part / b_ex > amp_ratio) {
      c_ABSD_size[0] = idx;
      if (0 <= idx - 1) {
        memcpy(&b_ABSD_data[0], &ABSD_data[0], (unsigned int)(idx * (int)sizeof
                (double)));
      }

      b_Coder_local_smoothing(b_ABSD_data, c_ABSD_size, corr_part_data,
        corr_part_size);
      for (i57 = 0; i57 < idx; i57++) {
        d_tmp_data[i57] = i57;
      }

      for (i57 = 0; i57 < idx; i57++) {
        b_ABSD_data[i57] = (ABSD_data[i57] - corr_part_data[i57]) + ex;
      }

      for (i57 = 0; i57 < idx; i57++) {
        ABSD_data[d_tmp_data[i57]] = b_ABSD_data[i57];
      }

      /* v3과 다른점 */
    }
  }

  emxFree_real_T(&varargin_1);
  return min_cycle;
}

/* End of code generation (Coder_ABSD_corrector_v3_1.c) */
