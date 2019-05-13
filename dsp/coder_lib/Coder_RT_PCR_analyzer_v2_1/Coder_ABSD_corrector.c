/*
 * Coder_ABSD_corrector.c
 *
 * Code generation for function 'Coder_ABSD_corrector'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_ABSD_corrector.h"
#include "sum.h"
#include "var.h"
#include "diff.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"

/* Function Definitions */
void Coder_ABSD_corrector(double SFC, double MFC, double ABSD_data[], int
  ABSD_size[1])
{
  int i66;
  int i67;
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
  double d21;
  int b_ABSD_size[1];
  emxArray_real_T b_y_data;
  int tmp_data[100];
  if (SFC > ABSD_size[0]) {
    i66 = 0;
    i67 = 0;
  } else {
    i66 = (int)SFC - 1;
    i67 = ABSD_size[0];
  }

  emxInit_real_T(&varargin_1, 1);
  n = varargin_1->size[0];
  loop_ub = (int)(SFC - 1.0);
  varargin_1->size[0] = (loop_ub + i67) - i66;
  emxEnsureCapacity_real_T(varargin_1, n);
  for (n = 0; n < loop_ub; n++) {
    varargin_1->data[n] = rtInf;
  }

  n = i67 - i66;
  for (i67 = 0; i67 < n; i67++) {
    varargin_1->data[i67 + loop_ub] = ABSD_data[i66 + i67];
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
      i66 = idx + 1;
      for (loop_ub = i66; loop_ub <= n; loop_ub++) {
        if (ex > varargin_1->data[loop_ub - 1]) {
          ex = varargin_1->data[loop_ub - 1];
          idx = loop_ub;
        }
      }
    }
  }

  emxFree_real_T(&varargin_1);

  /* if min_cycle > SFC */
  if (SFC > idx) {
    i66 = 0;
    i67 = 0;
  } else {
    i66 = (int)SFC - 1;
    i67 = idx;
  }

  corr_part_size_tmp = i67 - i66;
  corr_part_size[0] = corr_part_size_tmp;
  for (i67 = 0; i67 < corr_part_size_tmp; i67++) {
    corr_part_data[i67] = ABSD_data[i66 + i67];
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
      i66 = n + 1;
      for (loop_ub = i66; loop_ub <= corr_part_size_tmp; loop_ub++) {
        d21 = corr_part_data[loop_ub - 1];
        if (b_ex < d21) {
          b_ex = d21;
        }
      }
    }
  }

  /* Length Scale Ratio */
  if (SFC > MFC) {
    i66 = 0;
    i67 = 0;
  } else {
    i66 = (int)SFC - 1;
    i67 = (int)MFC;
  }

  n = i67 - i66;
  b_ABSD_size[0] = n;
  for (i67 = 0; i67 < n; i67++) {
    corr_part_data[i67] = ABSD_data[i66 + i67];
  }

  if (var(corr_part_data, b_ABSD_size) / var(ABSD_data, ABSD_size) < 0.05) {
    b_y_data.data = &y_data[0];
    b_y_data.size = &y_size[0];
    b_y_data.allocatedSize = 198;
    b_y_data.numDimensions = 1;
    b_y_data.canFreeData = false;
    if (sum(&b_y_data) / (b_ex - ex) < 5.0) {
      for (i66 = 0; i66 < idx; i66++) {
        tmp_data[i66] = i66;
      }

      for (i66 = 0; i66 < idx; i66++) {
        ABSD_data[tmp_data[i66]] = ex;
      }
    }
  }

  /* end */
}

/* End of code generation (Coder_ABSD_corrector.c) */
