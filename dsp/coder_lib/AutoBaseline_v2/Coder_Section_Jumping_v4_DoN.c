/*
 * Coder_Section_Jumping_v4_DoN.c
 *
 * Code generation for function 'Coder_Section_Jumping_v4_DoN'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_Section_Jumping_v4_DoN.h"
#include "mean.h"
#include "Coder_DistanceBetweenSegs.h"
#include "sum.h"
#include "abs.h"
#include "diff.h"
#include "Coder_jumping_correction6.h"
#include "Coder_medfilter.h"

/* Function Definitions */
void Coder_Section_Jumping_v4_DoN(double RD_data[], int RD_size[1], double DRFU,
  double *result_well, double *DataProcessNum, double AR, double FB, double SFC,
  double HTC, double TC, double RD_diff_data[], int RD_diff_size[1], double
  ivd_cdd_ouput_data[], int ivd_cdd_ouput_size[2], double *num_jumping)
{
  int idx;
  double RD_median_data[100];
  int RD_median_size[1];
  double begin;
  int i36;
  int b_idx;
  int RD_median_size_tmp;
  int b_RD_median_size[1];
  double ivd_cdd_data[100];
  double tmp_data[198];
  int tmp_size[1];
  int nor_diff_size[1];
  double nor_diff_data[99];
  double abs_diff_data[99];
  int n;
  double ex;
  int k;
  boolean_T exitg1;
  double d6;
  double max_diff2;
  int u1;
  int ivd_cdd_size[2];
  signed char b_tmp_data[100];
  double varargin_1_data[199];
  int RD_normalized_size[1];
  double RD_normalized_data[100];
  int b_RD_normalized_size[1];
  double b_RD_normalized_data[100];
  double c_tmp_data[198];
  int b_tmp_size[1];
  emxArray_real_T d_tmp_data;
  *result_well = 0.0;

  /* 190318 : add a median filter which detects a single jumping */
  RD_diff_size[0] = RD_size[0];
  idx = RD_size[0];
  if (0 <= idx - 1) {
    memcpy(&RD_diff_data[0], &RD_data[0], (unsigned int)(idx * (int)sizeof
            (double)));
  }

  /* --------(B) median filter which detects a single jumping -------- */
  Coder_medfilter(RD_data, RD_size, RD_median_data, RD_median_size);
  if ((3.0 > SFC) || rtIsNaN(SFC)) {
    begin = 3.0;
  } else {
    begin = SFC;
  }

  if (begin > TC) {
    i36 = 0;
    b_idx = 0;
  } else {
    i36 = (int)begin - 1;
    b_idx = (int)TC;
  }

  RD_median_size_tmp = b_idx - i36;
  b_RD_median_size[0] = RD_median_size_tmp;
  for (b_idx = 0; b_idx < RD_median_size_tmp; b_idx++) {
    ivd_cdd_data[b_idx] = RD_median_data[i36 + b_idx];
  }

  diff(ivd_cdd_data, b_RD_median_size, tmp_data, tmp_size);
  nor_diff_size[0] = tmp_size[0];
  if (0 <= tmp_size[0] - 1) {
    memcpy(&nor_diff_data[0], &tmp_data[0], (unsigned int)(tmp_size[0] * (int)
            sizeof(double)));
  }

  b_abs(nor_diff_data, nor_diff_size, tmp_data, tmp_size);
  RD_median_size_tmp = tmp_size[0];
  if (0 <= tmp_size[0] - 1) {
    memcpy(&abs_diff_data[0], &tmp_data[0], (unsigned int)(tmp_size[0] * (int)
            sizeof(double)));
  }

  n = tmp_size[0];
  if (tmp_size[0] <= 2) {
    if (tmp_size[0] == 1) {
      ex = abs_diff_data[0];
      b_idx = 1;
    } else if ((abs_diff_data[0] < abs_diff_data[1]) || (rtIsNaN(abs_diff_data[0])
                && (!rtIsNaN(abs_diff_data[1])))) {
      ex = abs_diff_data[1];
      b_idx = 2;
    } else {
      ex = abs_diff_data[0];
      b_idx = 1;
    }
  } else {
    if (!rtIsNaN(abs_diff_data[0])) {
      b_idx = 1;
    } else {
      b_idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= RD_median_size_tmp)) {
        if (!rtIsNaN(abs_diff_data[k - 1])) {
          b_idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (b_idx == 0) {
      ex = abs_diff_data[0];
      b_idx = 1;
    } else {
      ex = abs_diff_data[b_idx - 1];
      i36 = b_idx + 1;
      for (k = i36; k <= n; k++) {
        d6 = abs_diff_data[k - 1];
        if (ex < d6) {
          ex = d6;
          b_idx = k;
        }
      }
    }
  }

  abs_diff_data[b_idx - 1] = rtMinusInf;
  n = tmp_size[0];
  if (tmp_size[0] <= 2) {
    if (tmp_size[0] == 1) {
      max_diff2 = abs_diff_data[0];
    } else if ((abs_diff_data[0] < abs_diff_data[1]) || (rtIsNaN(abs_diff_data[0])
                && (!rtIsNaN(abs_diff_data[1])))) {
      max_diff2 = abs_diff_data[1];
    } else {
      max_diff2 = abs_diff_data[0];
    }
  } else {
    if (!rtIsNaN(abs_diff_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= RD_median_size_tmp)) {
        if (!rtIsNaN(abs_diff_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      max_diff2 = abs_diff_data[0];
    } else {
      max_diff2 = abs_diff_data[idx - 1];
      i36 = idx + 1;
      for (k = i36; k <= n; k++) {
        d6 = abs_diff_data[k - 1];
        if (max_diff2 < d6) {
          max_diff2 = d6;
        }
      }
    }
  }

  /*      fprintf('i=%d, max_diff1=%f, max_diff2=%f, ratio=%f\n', i, max_diff1, max_diff2, max_diff1/max_diff2); */
  d6 = nor_diff_data[b_idx - 1];
  if ((d6 > 0.0) && (ex / max_diff2 > 2.5)) {
    begin += (double)b_idx;
    if (!(d6 / (RD_data[(int)begin - 1] - RD_data[(int)(begin - 1.0) - 1]) > 0.4))
    {
      RD_size[0] = RD_median_size[0];
      if (0 <= RD_median_size[0] - 1) {
        memcpy(&RD_data[0], &RD_median_data[0], (unsigned int)(RD_median_size[0]
                * (int)sizeof(double)));
      }
    }

    if (begin > TC) {
      i36 = 0;
      b_idx = 1;
      n = 0;
    } else {
      i36 = (int)begin - 1;
      b_idx = (int)begin;
      n = (int)TC;
    }

    RD_median_size_tmp = (signed char)n - (signed char)b_idx;
    idx = RD_median_size_tmp + 1;
    for (n = 0; n <= RD_median_size_tmp; n++) {
      b_tmp_data[n] = (signed char)((signed char)((signed char)b_idx + (signed
        char)n) - 1);
    }

    d6 = RD_data[(int)begin - 1];
    begin = RD_data[(int)begin - 2];
    for (b_idx = 0; b_idx < idx; b_idx++) {
      ivd_cdd_data[b_idx] = (RD_data[i36 + b_idx] - d6) + begin;
    }

    for (i36 = 0; i36 < idx; i36++) {
      RD_data[b_tmp_data[i36]] = ivd_cdd_data[i36];
    }

    u1 = 1;
  } else {
    u1 = 0;
  }

  /*      num_jumping_single */
  /* --------(E) median filter which detects a single jumping -------- */
  RD_median_size[0] = RD_size[0];
  idx = RD_size[0];
  if (0 <= idx - 1) {
    memcpy(&RD_median_data[0], &RD_data[0], (unsigned int)(idx * (int)sizeof
            (double)));
  }

  Coder_jumping_correction6(RD_data, RD_size, -8000.0 * AR * AR, 100.0 * AR, HTC,
    &max_diff2, ivd_cdd_data, ivd_cdd_size);

  /*      num_jumping */
  if (max_diff2 > 5.0) {
    i36 = (int)TC - 1;
    if (RD_median_data[i36] > RD_median_data[0]) {
      RD_size[0] = RD_median_size[0];
      if (0 <= RD_median_size[0] - 1) {
        memcpy(&RD_data[0], &RD_median_data[0], (unsigned int)(RD_median_size[0]
                * (int)sizeof(double)));
      }

      n = RD_median_size[0];
      if (RD_median_size[0] <= 2) {
        if (RD_median_size[0] == 1) {
          ex = RD_median_data[0];
        } else if ((RD_median_data[0] < RD_median_data[1]) || (rtIsNaN
                    (RD_median_data[0]) && (!rtIsNaN(RD_median_data[1])))) {
          ex = RD_median_data[1];
        } else {
          ex = RD_median_data[0];
        }
      } else {
        if (!rtIsNaN(RD_median_data[0])) {
          b_idx = 1;
        } else {
          b_idx = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= RD_median_size[0])) {
            if (!rtIsNaN(RD_median_data[k - 1])) {
              b_idx = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (b_idx == 0) {
          ex = RD_median_data[0];
        } else {
          ex = RD_median_data[b_idx - 1];
          b_idx++;
          for (k = b_idx; k <= n; k++) {
            d6 = RD_median_data[k - 1];
            if (ex < d6) {
              ex = d6;
            }
          }
        }
      }

      n = RD_median_size[0];
      if (RD_median_size[0] <= 2) {
        if (RD_median_size[0] == 1) {
          begin = RD_median_data[0];
        } else if ((RD_median_data[0] > RD_median_data[1]) || (rtIsNaN
                    (RD_median_data[0]) && (!rtIsNaN(RD_median_data[1])))) {
          begin = RD_median_data[1];
        } else {
          begin = RD_median_data[0];
        }
      } else {
        if (!rtIsNaN(RD_median_data[0])) {
          b_idx = 1;
        } else {
          b_idx = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= RD_median_size[0])) {
            if (!rtIsNaN(RD_median_data[k - 1])) {
              b_idx = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (b_idx == 0) {
          begin = RD_median_data[0];
        } else {
          begin = RD_median_data[b_idx - 1];
          b_idx++;
          for (k = b_idx; k <= n; k++) {
            d6 = RD_median_data[k - 1];
            if (begin > d6) {
              begin = d6;
            }
          }
        }
      }

      begin = ex - begin;
      RD_normalized_size[0] = RD_median_size[0];
      idx = RD_median_size[0];
      for (b_idx = 0; b_idx < idx; b_idx++) {
        RD_normalized_data[b_idx] = RD_median_data[b_idx] / begin;
      }

      if (SFC > TC) {
        b_idx = 0;
        n = 0;
      } else {
        b_idx = (int)SFC - 1;
        n = (int)TC;
      }

      RD_median_size_tmp = n - b_idx;
      b_RD_normalized_size[0] = RD_median_size_tmp;
      for (n = 0; n < RD_median_size_tmp; n++) {
        b_RD_normalized_data[n] = RD_normalized_data[b_idx + n];
      }

      diff(b_RD_normalized_data, b_RD_normalized_size, tmp_data, tmp_size);
      b_abs(tmp_data, tmp_size, c_tmp_data, b_tmp_size);
      d_tmp_data.data = &c_tmp_data[0];
      d_tmp_data.size = &b_tmp_size[0];
      d_tmp_data.allocatedSize = 198;
      d_tmp_data.numDimensions = 1;
      d_tmp_data.canFreeData = false;
      if (sum(&d_tmp_data) / Coder_DistanceBetweenSegs(RD_normalized_data,
           RD_normalized_size, SFC, TC) < 5.0) {
        ivd_cdd_size[1] = 0;

        /* invalid_candidate */
        RD_data[0] = mean(*(double (*)[3])&RD_median_data[0]);
        RD_data[1] = d_mean(*(double (*)[4])&RD_median_data[0]);
        RD_data[(int)(TC - 1.0) - 1] = d_mean(*(double (*)[4])&RD_median_data
          [(int)(TC + -3.0) - 1]);
        RD_data[i36] = mean(*(double (*)[3])&RD_median_data[(int)(TC + -2.0) - 1]);
        i36 = (int)((TC - 2.0) + -2.0);
        for (idx = 0; idx < i36; idx++) {
          RD_data[2 + idx] = e_mean(*(double (*)[5])&RD_median_data[idx]);
        }
      }
    }
  }

  *num_jumping = u1;
  if (max_diff2 > *num_jumping) {
    *num_jumping = max_diff2;
  }

  idx = RD_diff_size[0];
  for (i36 = 0; i36 < idx; i36++) {
    RD_diff_data[i36] -= RD_data[i36];
  }

  if ((FB == 0.0) && (*num_jumping > 0.0)) {
    if (SFC > TC) {
      i36 = 0;
      b_idx = 0;
    } else {
      i36 = (int)SFC - 1;
      b_idx = (int)TC;
    }

    RD_median_size_tmp = b_idx - i36;
    for (b_idx = 0; b_idx < RD_median_size_tmp; b_idx++) {
      varargin_1_data[b_idx] = RD_data[i36 + b_idx];
    }

    if (RD_median_size_tmp <= 2) {
      if (RD_median_size_tmp == 1) {
        ex = RD_data[i36];
      } else {
        ex = RD_data[i36 + 1];
        if ((RD_data[i36] > ex) || (rtIsNaN(RD_data[i36]) && (!rtIsNaN(ex)))) {
        } else {
          ex = RD_data[i36];
        }
      }
    } else {
      if (!rtIsNaN(varargin_1_data[0])) {
        b_idx = 1;
      } else {
        b_idx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= RD_median_size_tmp)) {
          if (!rtIsNaN(varargin_1_data[k - 1])) {
            b_idx = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (b_idx == 0) {
        ex = RD_data[i36];
      } else {
        ex = varargin_1_data[b_idx - 1];
        i36 = b_idx + 1;
        for (k = i36; k <= RD_median_size_tmp; k++) {
          d6 = varargin_1_data[k - 1];
          if (ex > d6) {
            ex = d6;
          }
        }
      }
    }

    if (RD_data[(int)TC - 1] - ex < DRFU) {
      *result_well = 1.0;
      *DataProcessNum = 2.0;
    }
  }

  RD_median_size_tmp = ivd_cdd_size[1];
  idx = RD_size[0];
  if (RD_median_size_tmp < idx) {
    idx = RD_median_size_tmp;
  }

  if (1 > idx) {
    idx = 0;
  }

  ivd_cdd_ouput_size[0] = 1;
  ivd_cdd_ouput_size[1] = idx;
  if (0 <= idx - 1) {
    memcpy(&ivd_cdd_ouput_data[0], &ivd_cdd_data[0], (unsigned int)(idx * (int)
            sizeof(double)));
  }
}

/* End of code generation (Coder_Section_Jumping_v4_DoN.c) */
