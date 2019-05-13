/*
 * Coder_Section_Jumping_v3_DoN.c
 *
 * Code generation for function 'Coder_Section_Jumping_v3_DoN'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
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
  int i36;
  int i37;
  int n;
  double ex;
  int k;
  boolean_T exitg1;
  double varargin_1_data[199];
  int i38;
  double b_ex;
  double d15;
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
    i36 = (int)TC;
    i37 = i36 - 1;
    if (RD_diff_data[i37] > RD_diff_data[0]) {
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
          i38 = idx + 1;
          for (k = i38; k <= n; k++) {
            d15 = RD_diff_data[k - 1];
            if (ex < d15) {
              ex = d15;
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
          i38 = idx + 1;
          for (k = i38; k <= n; k++) {
            d15 = RD_diff_data[k - 1];
            if (b_ex > d15) {
              b_ex = d15;
            }
          }
        }
      }

      ex -= b_ex;
      RD_normalized_size[0] = RD_diff_size[0];
      idx = RD_diff_size[0];
      for (i38 = 0; i38 < idx; i38++) {
        RD_normalized_data[i38] = RD_diff_data[i38] / ex;
      }

      if (SFC > TC) {
        i38 = 0;
        i36 = 0;
      } else {
        i38 = (int)SFC - 1;
      }

      n = i36 - i38;
      b_RD_normalized_size[0] = n;
      for (i36 = 0; i36 < n; i36++) {
        b_RD_normalized_data[i36] = RD_normalized_data[i38 + i36];
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
        RD_data[i37] = mean(*(double (*)[3])&RD_diff_data[(int)(TC + -2.0) - 1]);
        i36 = (int)((TC - 2.0) + -2.0);
        for (idx = 0; idx < i36; idx++) {
          RD_data[2 + idx] = e_mean(*(double (*)[5])&RD_diff_data[idx]);
        }
      }
    }
  }

  idx = RD_diff_size[0];
  for (i36 = 0; i36 < idx; i36++) {
    RD_diff_data[i36] -= RD_data[i36];
  }

  if ((FB == 0.0) && (*num_jumping > 0.0)) {
    if (SFC > TC) {
      i36 = 0;
      i37 = 0;
    } else {
      i36 = (int)SFC - 1;
      i37 = (int)TC;
    }

    n = i37 - i36;
    for (i37 = 0; i37 < n; i37++) {
      varargin_1_data[i37] = RD_data[i36 + i37];
    }

    if (n <= 2) {
      if (n == 1) {
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
        ex = RD_data[i36];
      } else {
        ex = varargin_1_data[idx - 1];
        i36 = idx + 1;
        for (k = i36; k <= n; k++) {
          d15 = varargin_1_data[k - 1];
          if (ex > d15) {
            ex = d15;
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
