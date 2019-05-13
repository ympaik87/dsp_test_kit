/*
 * Coder_classifier.c
 *
 * Code generation for function 'Coder_classifier'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_classifier.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "Coder_dsig.h"
#include "var.h"

/* Function Definitions */
void Coder_classifier(const double x_data[], const int x_size[1], const double
                      ABSD_data[], const int ABSD_size[1], const double f_data[],
                      const int f_size[1], const double param[4], double SC,
                      double TC, double *result_well, double *DataProcessNum,
                      double RC, double Max_DRFU_Thrd, double dfM, double dfC,
                      double PMC, double isPC, double *R2, double *sht, double
                      *EndRFU, double *df)
{
  double abs_param4;
  int i72;
  int n;
  int idx;
  int k;
  int i73;
  int ABSD_size_tmp;
  int b_ABSD_size[1];
  double Dev_f_data[100];
  int c_ABSD_size[1];
  emxArray_real_T *varargin_1;
  double b_ABSD_data[100];
  boolean_T exitg1;
  double rt;
  double b_x_data[198];
  double y_data[198];
  double ex;
  double u0;
  abs_param4 = fabs(param[3]);
  if (SC > TC) {
    i72 = 0;
    n = 0;
    idx = 0;
    k = 0;
    i73 = 0;
  } else {
    i72 = (int)SC - 1;
    n = (int)TC;
    idx = (int)SC - 1;
    k = (int)SC - 1;
    i73 = (int)TC;
  }

  ABSD_size_tmp = n - i72;
  b_ABSD_size[0] = ABSD_size_tmp;
  for (n = 0; n < ABSD_size_tmp; n++) {
    Dev_f_data[n] = ABSD_data[i72 + n] - f_data[idx + n];
  }

  ABSD_size_tmp = i73 - k;
  c_ABSD_size[0] = ABSD_size_tmp;
  for (i72 = 0; i72 < ABSD_size_tmp; i72++) {
    b_ABSD_data[i72] = ABSD_data[k + i72];
  }

  emxInit_real_T(&varargin_1, 1);
  *R2 = 1.0 - var(Dev_f_data, b_ABSD_size) / var(b_ABSD_data, c_ABSD_size);
  *sht = f_data[0];
  *EndRFU = f_data[(int)TC - 1] - f_data[0];
  Coder_dsig(param, x_data, x_size, Dev_f_data, b_ABSD_size);
  Coder_dsig(param, x_data, x_size, b_ABSD_data, c_ABSD_size);
  i72 = varargin_1->size[0];
  varargin_1->size[0] = c_ABSD_size[0];
  emxEnsureCapacity_real_T(varargin_1, i72);
  n = c_ABSD_size[0];
  for (i72 = 0; i72 < n; i72++) {
    varargin_1->data[i72] = b_ABSD_data[i72];
  }

  n = b_ABSD_size[0];
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
      i72 = idx + 1;
      for (k = i72; k <= n; k++) {
        rt = Dev_f_data[k - 1];
        if (*df < rt) {
          *df = rt;
        }
      }
    }
  }

  emxFree_real_T(&varargin_1);
  rt = (f_data[0] + f_data[f_size[0] - 1]) / 2.0;
  n = ABSD_size[0];
  for (i72 = 0; i72 < n; i72++) {
    b_x_data[i72] = ABSD_data[i72] - rt;
  }

  n = ABSD_size[0];
  for (k = 0; k < n; k++) {
    y_data[k] = fabs(b_x_data[k]);
  }

  n = (signed char)ABSD_size[0];
  if ((signed char)ABSD_size[0] <= 2) {
    if ((signed char)ABSD_size[0] == 1) {
      idx = 1;
    } else if ((y_data[0] > y_data[1]) || (rtIsNaN(y_data[0]) && (!rtIsNaN
                 (y_data[1])))) {
      idx = 2;
    } else {
      idx = 1;
    }
  } else {
    if (!rtIsNaN(y_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= (signed char)ABSD_size[0])) {
        if (!rtIsNaN(y_data[k - 1])) {
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
      ex = y_data[idx - 1];
      i72 = idx + 1;
      for (k = i72; k <= n; k++) {
        rt = y_data[k - 1];
        if (ex > rt) {
          ex = rt;
          idx = k;
        }
      }
    }
  }

  /* round(param(3)); */
  if ((abs_param4 > 0.5) && (idx > 3) && (idx < TC - 5.0)) {
    rt = ABSD_data[idx - 1];
    u0 = fabs((ABSD_data[idx] - rt) / (ABSD_data[idx + 1] - ABSD_data[idx]));
    ex = ABSD_data[idx - 2];
    rt = fabs((rt - ex) / (ex - ABSD_data[idx - 3]));
    if ((u0 < rt) || rtIsNaN(rt)) {
      rt = u0;
    }
  } else {
    rt = 0.0;
  }

  /*                            [sheet '_' num2str(i_Tm) '_' well ', cycle3=' num2str(cycle3) ', rt=' num2str(rt)] */
  if (*R2 <= RC) {
    *DataProcessNum = 6.0;
  } else if (abs_param4 >= 2.0) {
    *DataProcessNum = 7.0;
  } else if (*EndRFU <= Max_DRFU_Thrd) {
    /*          if (i_Tm==1) && ~ischar(cell2mat(Ct_array(i_well,2))) && ~isempty(cell2mat(Ct_array(i_well,2))) */
    /*              if EndRFU>max(DRFU,Thrd) */
    /*                  DataProcessNum=11; */
    /*              else */
    /*                  DataProcessNum=8; */
    /*              end */
    /*          else */
    *DataProcessNum = 8.0;

    /*          end */
  } else if ((abs_param4 > 0.5) && (param[2] < TC - 5.0) && (rt > 4.0)) {
    /* !!!!!!!!!!!!!!!!!!!!!!!! */
    *DataProcessNum = 7.0;
    *result_well = 4.0;

    /*                              specific_logic=1; */
  } else if (*df <= dfM) {
    *DataProcessNum = 9.0;
  } else {
    if ((*df > dfM) && (abs_param4 < PMC)) {
      /* || ( (df>dfM) && (param(3)<TC-10 ) )%190114 위양성 test */
      *DataProcessNum = 10.0;
    }
  }

  if (*result_well == 0.0) {
    if ((*R2 > RC) && (abs_param4 < 2.0) && (*EndRFU > Max_DRFU_Thrd)) {
      if (*df > dfC) {
        if ((abs_param4 < PMC) && (!(isPC != 0.0)) && (param[2] > TC - 5.0) &&
            (abs_param4 > 0.04)) {
          *result_well = -1.0;
        }
      } else if ((*df > dfM) && (abs_param4 >= PMC)) {
        /* && (param(3)>TC-10) %190114 위양성 test */
        *result_well = 0.0;
      } else {
        *result_well = 4.0;
      }
    } else {
      *result_well = 4.0;
    }
  }
}

/* End of code generation (Coder_classifier.c) */
