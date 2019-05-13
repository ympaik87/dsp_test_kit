/*
 * Coder_classifier_2nd.c
 *
 * Code generation for function 'Coder_classifier_2nd'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_classifier_2nd.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "Coder_dsig.h"
#include "var.h"

/* Function Definitions */
void Coder_classifier_2nd(const double x_data[], const int x_size[1], const
  double ABSD_data[], const double f_data[], const double param[4], double SC,
  double TC, double *result_well, double *DataProcessNum, double RC, double
  Max_DRFU_Thrd, double dfM, double dfC, double PMC, double *R2, double *sht,
  double *EndRFU, double *df)
{
  double abs_param4;
  int i75;
  int idx;
  int n;
  int k;
  int i76;
  int ABSD_size_tmp;
  int ABSD_size[1];
  double Dev_f_data[100];
  int b_ABSD_size[1];
  emxArray_real_T *varargin_1;
  double b_ABSD_data[100];
  boolean_T exitg1;
  double d22;
  *result_well = -1.0;
  abs_param4 = fabs(param[3]);
  if (SC > TC) {
    i75 = 0;
    idx = 0;
    n = 0;
    k = 0;
    i76 = 0;
  } else {
    i75 = (int)SC - 1;
    idx = (int)TC;
    n = (int)SC - 1;
    k = (int)SC - 1;
    i76 = (int)TC;
  }

  ABSD_size_tmp = idx - i75;
  ABSD_size[0] = ABSD_size_tmp;
  for (idx = 0; idx < ABSD_size_tmp; idx++) {
    Dev_f_data[idx] = ABSD_data[i75 + idx] - f_data[n + idx];
  }

  ABSD_size_tmp = i76 - k;
  b_ABSD_size[0] = ABSD_size_tmp;
  for (i75 = 0; i75 < ABSD_size_tmp; i75++) {
    b_ABSD_data[i75] = ABSD_data[k + i75];
  }

  emxInit_real_T(&varargin_1, 1);
  *R2 = 1.0 - var(Dev_f_data, ABSD_size) / var(b_ABSD_data, b_ABSD_size);
  *sht = f_data[0];
  *EndRFU = f_data[(int)TC - 1] - f_data[0];
  Coder_dsig(param, x_data, x_size, Dev_f_data, ABSD_size);
  Coder_dsig(param, x_data, x_size, b_ABSD_data, b_ABSD_size);
  i75 = varargin_1->size[0];
  varargin_1->size[0] = b_ABSD_size[0];
  emxEnsureCapacity_real_T(varargin_1, i75);
  idx = b_ABSD_size[0];
  for (i75 = 0; i75 < idx; i75++) {
    varargin_1->data[i75] = b_ABSD_data[i75];
  }

  n = ABSD_size[0];
  if (varargin_1->size[0] <= 2) {
    if (varargin_1->size[0] == 1) {
      *df = Dev_f_data[0];
    } else if ((Dev_f_data[0] < Dev_f_data[1]) || (rtIsNaN(Dev_f_data[0]) &&
                (!rtIsNaN(Dev_f_data[1])))) {
      *df = Dev_f_data[1];
    } else {
      *df = Dev_f_data[0];
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
      *df = Dev_f_data[0];
    } else {
      *df = Dev_f_data[idx - 1];
      i75 = idx + 1;
      for (k = i75; k <= n; k++) {
        d22 = Dev_f_data[k - 1];
        if (*df < d22) {
          *df = d22;
        }
      }
    }
  }

  emxFree_real_T(&varargin_1);
  if (*R2 <= RC) {
    *DataProcessNum = 106.0;
  } else if (abs_param4 >= 2.0) {
    *DataProcessNum = 107.0;
  } else if (*EndRFU <= Max_DRFU_Thrd) {
    *DataProcessNum = 108.0;
  } else if (*df <= dfM) {
    *DataProcessNum = 109.0;
  } else {
    if ((*df > dfM) && (abs_param4 < PMC)) {
      *DataProcessNum = 110.0;
    }
  }

  if ((*R2 > RC) && (abs_param4 < 2.0) && (*EndRFU > Max_DRFU_Thrd)) {
    if ((!(*df > dfC)) && ((!(*df > dfM)) || (!(abs_param4 >= PMC)))) {
      *result_well = 4.0;
    }
  } else {
    *result_well = 4.0;
  }
}

/* End of code generation (Coder_classifier_2nd.c) */
