/*
 * Coder_Section_Jumping_v3_DoN.c
 *
 * Code generation for function 'Coder_Section_Jumping_v3_DoN'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v1.h"
#include "Coder_Section_Jumping_v3_DoN.h"
#include "mean.h"
#include "Coder_DistanceBetweenSegs.h"
#include "sum.h"
#include "abs.h"
#include "diff.h"
#include "Coder_jumping_correction6.h"

/* Function Definitions */
void Coder_Section_Jumping_v3_DoN(double RD_data[], int RD_size[1], double DRFU,
  double *result_well, double *DataProcessNum, double AR, double FB, double SFC,
  double HTC, double TC, double RD_diff_data[], int RD_diff_size[1], double
  ivd_cdd_ouput_data[], int ivd_cdd_ouput_size[2], double *num_jumping)
{
  int idx;
  double ivd_cdd_data[100];
  int ivd_cdd_size[2];
  int i20;
  int i21;
  int n;
  double ex;
  int k;
  boolean_T exitg1;
  double varargin_1_data[199];
  int i22;
  double b_ex;
  double d2;
  int RD_normalized_size[1];
  double RD_normalized_data[100];
  int b_RD_normalized_size[1];
  double b_RD_normalized_data[100];
  double tmp_data[198];
  int tmp_size[1];
  double b_tmp_data[198];
  int b_tmp_size[1];
  emxArray_real_T c_tmp_data;
  *result_well = 0.0;
  RD_diff_size[0] = RD_size[0];
  idx = RD_size[0];
  if (0 <= idx - 1) {
    memcpy(&RD_diff_data[0], &RD_data[0], (unsigned int)(idx * (int)sizeof
            (double)));
  }

  Coder_jumping_correction6(RD_data, RD_size, -8000.0 * AR * AR, 100.0 * AR, HTC,
    num_jumping, ivd_cdd_data, ivd_cdd_size);

  /*      [RD,num_jumping,ivd_cdd]=Coder_jumping_correction6(RD,-8000*100^2,100*100,HTC); */
  if (*num_jumping > 5.0) {
    i20 = (int)TC;
    i21 = i20 - 1;
    if (RD_diff_data[i21] > RD_diff_data[0]) {
      RD_size[0] = RD_diff_size[0];
      if (0 <= RD_diff_size[0] - 1) {
        memcpy(&RD_data[0], &RD_diff_data[0], (unsigned int)(RD_diff_size[0] *
                (int)sizeof(double)));
      }

      n = RD_diff_size[0];
      if (RD_diff_size[0] <= 2) {
        if (RD_diff_size[0] == 1) {
          ex = RD_diff_data[0];
        } else if ((RD_diff_data[0] < RD_diff_data[1]) || (rtIsNaN(RD_diff_data
                     [0]) && (!rtIsNaN(RD_diff_data[1])))) {
          ex = RD_diff_data[1];
        } else {
          ex = RD_diff_data[0];
        }
      } else {
        if (!rtIsNaN(RD_diff_data[0])) {
          idx = 1;
        } else {
          idx = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= RD_diff_size[0])) {
            if (!rtIsNaN(RD_diff_data[k - 1])) {
              idx = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (idx == 0) {
          ex = RD_diff_data[0];
        } else {
          ex = RD_diff_data[idx - 1];
          i22 = idx + 1;
          for (k = i22; k <= n; k++) {
            d2 = RD_diff_data[k - 1];
            if (ex < d2) {
              ex = d2;
            }
          }
        }
      }

      n = RD_diff_size[0];
      if (RD_diff_size[0] <= 2) {
        if (RD_diff_size[0] == 1) {
          b_ex = RD_diff_data[0];
        } else if ((RD_diff_data[0] > RD_diff_data[1]) || (rtIsNaN(RD_diff_data
                     [0]) && (!rtIsNaN(RD_diff_data[1])))) {
          b_ex = RD_diff_data[1];
        } else {
          b_ex = RD_diff_data[0];
        }
      } else {
        if (!rtIsNaN(RD_diff_data[0])) {
          idx = 1;
        } else {
          idx = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= RD_diff_size[0])) {
            if (!rtIsNaN(RD_diff_data[k - 1])) {
              idx = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (idx == 0) {
          b_ex = RD_diff_data[0];
        } else {
          b_ex = RD_diff_data[idx - 1];
          i22 = idx + 1;
          for (k = i22; k <= n; k++) {
            d2 = RD_diff_data[k - 1];
            if (b_ex > d2) {
              b_ex = d2;
            }
          }
        }
      }

      ex -= b_ex;
      RD_normalized_size[0] = RD_diff_size[0];
      idx = RD_diff_size[0];
      for (i22 = 0; i22 < idx; i22++) {
        RD_normalized_data[i22] = RD_diff_data[i22] / ex;
      }

      if (SFC > TC) {
        i22 = 0;
        i20 = 0;
      } else {
        i22 = (int)SFC - 1;
      }

      n = i20 - i22;
      b_RD_normalized_size[0] = n;
      for (i20 = 0; i20 < n; i20++) {
        b_RD_normalized_data[i20] = RD_normalized_data[i22 + i20];
      }

      diff(b_RD_normalized_data, b_RD_normalized_size, tmp_data, tmp_size);
      b_abs(tmp_data, tmp_size, b_tmp_data, b_tmp_size);
      c_tmp_data.data = &b_tmp_data[0];
      c_tmp_data.size = &b_tmp_size[0];
      c_tmp_data.allocatedSize = 198;
      c_tmp_data.numDimensions = 1;
      c_tmp_data.canFreeData = false;
      if (sum(&c_tmp_data) / Coder_DistanceBetweenSegs(RD_normalized_data,
           RD_normalized_size, SFC, TC) < 5.0) {
        ivd_cdd_size[1] = 0;

        /* invalid_candidate */
        RD_data[0] = mean(*(double (*)[3])&RD_diff_data[0]);
        RD_data[1] = d_mean(*(double (*)[4])&RD_diff_data[0]);
        RD_data[(int)(TC - 1.0) - 1] = d_mean(*(double (*)[4])&RD_diff_data[(int)
          (TC + -3.0) - 1]);
        RD_data[i21] = mean(*(double (*)[3])&RD_diff_data[(int)(TC + -2.0) - 1]);
        i20 = (int)((TC - 2.0) + -2.0);
        for (idx = 0; idx < i20; idx++) {
          RD_data[2 + idx] = e_mean(*(double (*)[5])&RD_diff_data[idx]);
        }
      }
    }
  }

  idx = RD_diff_size[0];
  for (i20 = 0; i20 < idx; i20++) {
    RD_diff_data[i20] -= RD_data[i20];
  }

  if ((FB == 0.0) && (*num_jumping > 0.0)) {
    if (SFC > TC) {
      i20 = 0;
      i21 = 0;
    } else {
      i20 = (int)SFC - 1;
      i21 = (int)TC;
    }

    n = i21 - i20;
    for (i21 = 0; i21 < n; i21++) {
      varargin_1_data[i21] = RD_data[i20 + i21];
    }

    if (n <= 2) {
      if (n == 1) {
        ex = RD_data[i20];
      } else {
        ex = RD_data[i20 + 1];
        if ((RD_data[i20] > ex) || (rtIsNaN(RD_data[i20]) && (!rtIsNaN(ex)))) {
        } else {
          ex = RD_data[i20];
        }
      }
    } else {
      if (!rtIsNaN(varargin_1_data[0])) {
        idx = 1;
      } else {
        idx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= n)) {
          if (!rtIsNaN(varargin_1_data[k - 1])) {
            idx = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (idx == 0) {
        ex = RD_data[i20];
      } else {
        ex = varargin_1_data[idx - 1];
        i20 = idx + 1;
        for (k = i20; k <= n; k++) {
          d2 = varargin_1_data[k - 1];
          if (ex > d2) {
            ex = d2;
          }
        }
      }
    }

    if (RD_data[(int)TC - 1] - ex < DRFU) {
      *result_well = 1.0;
      *DataProcessNum = 2.0;
    }
  }

  idx = ivd_cdd_size[1];
  n = RD_size[0];
  if (idx < n) {
    n = idx;
  }

  if (1 > n) {
    idx = 0;
  } else {
    idx = n;
  }

  ivd_cdd_ouput_size[0] = 1;
  ivd_cdd_ouput_size[1] = idx;
  if (0 <= idx - 1) {
    memcpy(&ivd_cdd_ouput_data[0], &ivd_cdd_data[0], (unsigned int)(idx * (int)
            sizeof(double)));
  }
}

/* End of code generation (Coder_Section_Jumping_v3_DoN.c) */
