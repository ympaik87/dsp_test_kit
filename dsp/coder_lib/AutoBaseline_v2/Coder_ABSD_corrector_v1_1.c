/*
 * Coder_ABSD_corrector_v1_1.c
 *
 * Code generation for function 'Coder_ABSD_corrector_v1_1'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_ABSD_corrector_v1_1.h"
#include "sum.h"
#include "var.h"
#include "diff.h"
#include "AutoBaseline_v2_emxutil.h"

/* Function Definitions */
double Coder_ABSD_corrector_v1_1(double SFC, double MFC, double ABSD_data[], int
  ABSD_size[1])
{
  double min_cycle;
  int i55;
  int i56;
  emxArray_real_T *varargin_1;
  int n;
  int loop_ub;
  int idx;
  double ex;
  boolean_T exitg1;
  int corr_part_size_tmp;
  int corr_part_size[1];
  double corr_part_data[100];
  double x_data[198];
  int x_size[1];
  int y_size[1];
  double y_data[198];
  double b_ex;
  double d8;
  int b_ABSD_size[1];
  emxArray_real_T b_y_data;
  int tmp_data[100];

  /* raw data 분석용으로 Coder_ABSD_corrector 대비 min_cycle이 output */
  if (SFC > ABSD_size[0]) {
    i55 = 0;
    i56 = 0;
  } else {
    i55 = (int)SFC - 1;
    i56 = ABSD_size[0];
  }

  emxInit_real_T(&varargin_1, 1);
  n = varargin_1->size[0];
  loop_ub = (int)(SFC - 1.0);
  varargin_1->size[0] = (loop_ub + i56) - i55;
  emxEnsureCapacity_real_T(varargin_1, n);
  for (n = 0; n < loop_ub; n++) {
    varargin_1->data[n] = rtInf;
  }

  n = i56 - i55;
  for (i56 = 0; i56 < n; i56++) {
    varargin_1->data[i56 + loop_ub] = ABSD_data[i55 + i56];
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
      loop_ub = 2;
      exitg1 = false;
      while ((!exitg1) && (loop_ub <= varargin_1->size[0])) {
        if (!rtIsNaN(varargin_1->data[loop_ub - 1])) {
          idx = loop_ub;
          exitg1 = true;
        } else {
          loop_ub++;
        }
      }
    }

    if (idx == 0) {
      ex = varargin_1->data[0];
      idx = 1;
    } else {
      ex = varargin_1->data[idx - 1];
      i55 = idx + 1;
      for (loop_ub = i55; loop_ub <= n; loop_ub++) {
        if (ex > varargin_1->data[loop_ub - 1]) {
          ex = varargin_1->data[loop_ub - 1];
          idx = loop_ub;
        }
      }
    }
  }

  emxFree_real_T(&varargin_1);
  min_cycle = idx;

  /* if min_cycle > SFC */
  if (SFC > idx) {
    i55 = 0;
    i56 = 0;
  } else {
    i55 = (int)SFC - 1;
    i56 = idx;
  }

  corr_part_size_tmp = i56 - i55;
  corr_part_size[0] = corr_part_size_tmp;
  for (i56 = 0; i56 < corr_part_size_tmp; i56++) {
    corr_part_data[i56] = ABSD_data[i55 + i56];
  }

  diff(corr_part_data, corr_part_size, x_data, x_size);
  n = x_size[0];
  y_size[0] = (unsigned char)x_size[0];
  for (loop_ub = 0; loop_ub < n; loop_ub++) {
    y_data[loop_ub] = fabs(x_data[loop_ub]);
  }

  if (corr_part_size_tmp <= 2) {
    if (corr_part_size_tmp == 1) {
      b_ex = corr_part_data[0];
    } else if ((corr_part_data[0] < corr_part_data[1]) || (rtIsNaN
                (corr_part_data[0]) && (!rtIsNaN(corr_part_data[1])))) {
      b_ex = corr_part_data[1];
    } else {
      b_ex = corr_part_data[0];
    }
  } else {
    if (!rtIsNaN(corr_part_data[0])) {
      n = 1;
    } else {
      n = 0;
      loop_ub = 2;
      exitg1 = false;
      while ((!exitg1) && (loop_ub <= corr_part_size_tmp)) {
        if (!rtIsNaN(corr_part_data[loop_ub - 1])) {
          n = loop_ub;
          exitg1 = true;
        } else {
          loop_ub++;
        }
      }
    }

    if (n == 0) {
      b_ex = corr_part_data[0];
    } else {
      b_ex = corr_part_data[n - 1];
      i55 = n + 1;
      for (loop_ub = i55; loop_ub <= corr_part_size_tmp; loop_ub++) {
        d8 = corr_part_data[loop_ub - 1];
        if (b_ex < d8) {
          b_ex = d8;
        }
      }
    }
  }

  /* Length Scale Ratio */
  if (SFC > MFC) {
    i55 = 0;
    i56 = 0;
  } else {
    i55 = (int)SFC - 1;
    i56 = (int)MFC;
  }

  n = i56 - i55;
  b_ABSD_size[0] = n;
  for (i56 = 0; i56 < n; i56++) {
    corr_part_data[i56] = ABSD_data[i55 + i56];
  }

  if (var(corr_part_data, b_ABSD_size) / var(ABSD_data, ABSD_size) < 0.05) {
    b_y_data.data = &y_data[0];
    b_y_data.size = &y_size[0];
    b_y_data.allocatedSize = 198;
    b_y_data.numDimensions = 1;
    b_y_data.canFreeData = false;
    if (sum(&b_y_data) / (b_ex - ex) < 5.0) {
      for (i55 = 0; i55 < idx; i55++) {
        tmp_data[i55] = i55;
      }

      for (i55 = 0; i55 < idx; i55++) {
        ABSD_data[tmp_data[i55]] = ex;
      }
    }
  }

  /* end */
  return min_cycle;
}

/* End of code generation (Coder_ABSD_corrector_v1_1.c) */
