/*
 * Coder_LinearFilter_v2.c
 *
 * Code generation for function 'Coder_LinearFilter_v2'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_LinearFilter_v2.h"
#include "Coder_RT_PCR_analyzer_emxutil.h"
#include "Coder_find_peak_cluster.h"
#include "Coder_DistanceBetweenSegs_v2.h"

/* Function Definitions */
void Coder_LinearFilter_v2(double RD_data[], int RD_size[1], double *result_well,
  double SFC, double MFC, double TC)
{
  int n;
  int idx;
  double ex;
  int k;
  boolean_T exitg1;
  int i46;
  double Early;
  double RD_scale;
  double SC;
  int Early_tmp;
  emxArray_real_T *r7;
  emxArray_real_T *y;
  emxArray_real_T *varargin_1;
  double rotated_RD_data[100];
  int rotated_RD_size[1];
  double b_rotated_RD_data[199];
  double b_Early;
  *result_well = 0.0;
  n = RD_size[0];
  if (RD_size[0] <= 2) {
    if (RD_size[0] == 1) {
      ex = RD_data[0];
    } else if ((RD_data[0] < RD_data[1]) || (rtIsNaN(RD_data[0]) && (!rtIsNaN
                 (RD_data[1])))) {
      ex = RD_data[1];
    } else {
      ex = RD_data[0];
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
      ex = RD_data[0];
    } else {
      ex = RD_data[idx - 1];
      i46 = idx + 1;
      for (k = i46; k <= n; k++) {
        RD_scale = RD_data[k - 1];
        if (ex < RD_scale) {
          ex = RD_scale;
        }
      }
    }
  }

  n = RD_size[0];
  if (RD_size[0] <= 2) {
    if (RD_size[0] == 1) {
      Early = RD_data[0];
    } else if ((RD_data[0] > RD_data[1]) || (rtIsNaN(RD_data[0]) && (!rtIsNaN
                 (RD_data[1])))) {
      Early = RD_data[1];
    } else {
      Early = RD_data[0];
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
      Early = RD_data[0];
    } else {
      Early = RD_data[idx - 1];
      i46 = idx + 1;
      for (k = i46; k <= n; k++) {
        RD_scale = RD_data[k - 1];
        if (Early > RD_scale) {
          Early = RD_scale;
        }
      }
    }
  }

  RD_scale = ex - Early;
  n = RD_size[0];
  for (i46 = 0; i46 < n; i46++) {
    RD_data[i46] /= RD_scale;
  }

  SC = SFC;
  Early_tmp = (int)SFC;
  Early = RD_data[0] - RD_data[Early_tmp - 1];
  emxInit_real_T(&r7, 1);
  emxInit_real_T(&y, 2);
  if (Early > 0.2) {
    if (rtIsNaN(TC)) {
      i46 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i46);
      y->data[0] = rtNaN;
    } else if (TC < 1.0) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else if (rtIsInf(TC) && (1.0 == TC)) {
      i46 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i46);
      y->data[0] = rtNaN;
    } else {
      i46 = y->size[0] * y->size[1];
      y->size[0] = 1;
      n = (int)floor(TC - 1.0);
      y->size[1] = n + 1;
      emxEnsureCapacity_real_T(y, i46);
      for (i46 = 0; i46 <= n; i46++) {
        y->data[i46] = 1.0 + (double)i46;
      }
    }

    i46 = r7->size[0];
    r7->size[0] = y->size[1];
    emxEnsureCapacity_real_T(r7, i46);
    n = y->size[1];
    for (i46 = 0; i46 < n; i46++) {
      r7->data[i46] = y->data[i46];
    }

    emxInit_real_T(&varargin_1, 1);
    RD_scale = (RD_data[(int)TC - 1] - RD_data[0]) / (TC - 1.0);
    i46 = varargin_1->size[0];
    varargin_1->size[0] = r7->size[0];
    emxEnsureCapacity_real_T(varargin_1, i46);
    n = r7->size[0];
    for (i46 = 0; i46 < n; i46++) {
      varargin_1->data[i46] = (RD_scale * (r7->data[i46] - 1.0) + RD_data[0]) -
        RD_data[i46];
    }

    n = varargin_1->size[0];
    if (varargin_1->size[0] <= 2) {
      if (varargin_1->size[0] == 1) {
        idx = 1;
      } else if ((varargin_1->data[0] < varargin_1->data[1]) || (rtIsNaN
                  (varargin_1->data[0]) && (!rtIsNaN(varargin_1->data[1])))) {
        idx = 2;
      } else {
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
        idx = 1;
      } else {
        ex = varargin_1->data[idx - 1];
        i46 = idx + 1;
        for (k = i46; k <= n; k++) {
          if (ex < varargin_1->data[k - 1]) {
            ex = varargin_1->data[k - 1];
            idx = k;
          }
        }
      }
    }

    emxFree_real_T(&varargin_1);
    if (idx > Early_tmp) {
      if (Early > 0.3) {
        b_Early = MFC + 3.0;
      } else {
        b_Early = (50.0 * (Early - 0.2) + MFC) - 2.0;
      }

      if ((1.0 + (double)idx) - 1.0 <= b_Early) {
        SC = (1.0 + (double)idx) - 1.0;
      }
    }

    /*       if (max_cycle0>SFC) */
    /*           SC=min(max_cycle0,floor(cycle)); */
    /*       end */
  }

  Coder_DistanceBetweenSegs_v2(RD_data, RD_size, SC, TC, &RD_scale, &Early);
  if (RD_scale < 0.2) {
    if (rtIsNaN(TC)) {
      i46 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i46);
      y->data[0] = rtNaN;
    } else if (TC < 1.0) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else if (rtIsInf(TC) && (1.0 == TC)) {
      i46 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i46);
      y->data[0] = rtNaN;
    } else {
      i46 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = (int)floor(TC - 1.0) + 1;
      emxEnsureCapacity_real_T(y, i46);
      n = (int)floor(TC - 1.0);
      for (i46 = 0; i46 <= n; i46++) {
        y->data[i46] = 1.0 + (double)i46;
      }
    }

    i46 = r7->size[0];
    r7->size[0] = y->size[1];
    emxEnsureCapacity_real_T(r7, i46);
    n = y->size[1];
    for (i46 = 0; i46 < n; i46++) {
      r7->data[i46] = y->data[i46];
    }

    n = RD_size[0];
    for (i46 = 0; i46 < n; i46++) {
      rotated_RD_data[i46] = (RD_data[i46] - Early * (r7->data[i46] - SC)) -
        RD_data[(int)SC - 1];
    }

    if (SC > TC) {
      i46 = 0;
      n = 0;
    } else {
      i46 = (int)SC - 1;
      n = (int)TC;
    }

    idx = n - i46;
    rotated_RD_size[0] = idx;
    for (n = 0; n < idx; n++) {
      b_rotated_RD_data[n] = rotated_RD_data[i46 + n];
    }

    Coder_find_peak_cluster(b_rotated_RD_data, rotated_RD_size, SC, &RD_scale,
      &Early, &ex);
    if ((Early - RD_scale > 10.0) && (ex > 0.2)) {
      /* 중복증폭 */
    } else {
      *result_well = 1.0;

      /* 선형증가 */
    }
  }

  emxFree_real_T(&y);
  emxFree_real_T(&r7);
}

/* End of code generation (Coder_LinearFilter_v2.c) */
