/*
 * AutoBaseline_v1.c
 *
 * Code generation for function 'AutoBaseline_v1'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v1.h"
#include "AutoBaseline_v1_emxutil.h"
#include "Coder_linear_fitting.h"
#include "mean.h"
#include "Coder_ABSD_corrector_v3_1.h"
#include "Coder_Section_Rp2.h"
#include "Coder_Section_Baseline_v6.h"
#include "Coder_Section_QuickAmp_v4.h"
#include "Coder_Section_Unimportant_v3.h"
#include "Coder_LinearFilter_v2.h"
#include "Coder_Section_Jumping_v3_DoN.h"
#include "Coder_DoN.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

void AutoBaseline_v1(const double x_data[], const int x_size[1], double RD_data[],
                     int RD_size[1], const double perturbation_data[], const int
                     perturbation_size[1], double SFC, double MFC, double DRFU,
                     double Thrd, double RPC, double RC, double dfM, double dfC,
                     double PMC, double FB, double AR, double isPC, double
                     LinearFilter_type, double ABSD_corrector_ver, double
                     AsymmSigFit_ver, double UseStrangePatternCorrector, double *
                     result_well, double *DataProcessNum, double
                     DataProcess_data[], int DataProcess_size[2], double
                     *LSR_val, double RD_diff_data[], int RD_diff_size[1],
                     double ivd_cdd_data[], int ivd_cdd_size[2], double cff[2],
                     double scd_fit_data[], int scd_fit_size[1], double *R_p2,
                     double *EFC, double ABSD_orig_data[], int ABSD_orig_size[1],
                     double ABSD_data[], int ABSD_size[1], double f_data[], int
                     f_size[1], double f_new_data[], int f_new_size[1], double
                     *sht, double *sht2, double param[4], double param_new[4],
                     double *R2, double *EndRFU, double *df)
{
  int idx;
  int varargin_1;
  int TC;
  int HTC;
  int LinearOrNot;
  double EFC0;
  double RFUR;
  int neg_BL;
  int i0;
  signed char tmp_data[100];
  int i1;
  int cdiff;
  int n;
  double varargin_1_data[199];
  double RD_scale;
  int k;
  boolean_T exitg1;
  double apnd;
  int b_RD_size[1];
  double b_RD_data[100];
  int i2;
  int c_RD_size[1];
  int y;
  double b_cdiff;
  emxArray_real_T *xdata;
  emxArray_real_T *b_y;
  emxArray_real_T *c_y;
  emxArray_real_T *RD;
  int b_ABSD_size[1];
  double b_ABSD_data[100];
  emxArray_real_T c_ABSD_data;
  signed char b_tmp_data[100];
  (void)perturbation_data;
  (void)perturbation_size;
  (void)RC;
  (void)dfM;
  (void)PMC;
  (void)ABSD_corrector_ver;
  (void)AsymmSigFit_ver;
  (void)UseStrangePatternCorrector;

  /* ================ (B) Output initialization ===================== */
  *result_well = 0.0;
  *DataProcessNum = 0.0;
  DataProcess_size[0] = RD_size[0];
  DataProcess_size[1] = 8;
  idx = RD_size[0] << 3;
  if (0 <= idx - 1) {
    memset(&DataProcess_data[0], 0, (unsigned int)(idx * (int)sizeof(double)));
  }

  RD_diff_size[0] = RD_size[0];
  if (0 <= RD_size[0] - 1) {
    memset(&RD_diff_data[0], 0, (unsigned int)(RD_size[0] * (int)sizeof(double)));
  }

  ivd_cdd_size[0] = 1;
  ivd_cdd_size[1] = 0;
  cff[0] = 0.0;
  cff[1] = 0.0;
  scd_fit_size[0] = RD_size[0];
  if (0 <= RD_size[0] - 1) {
    memset(&scd_fit_data[0], 0, (unsigned int)(RD_size[0] * (int)sizeof(double)));
  }

  *R_p2 = 0.0;
  *EFC = 0.0;
  ABSD_orig_size[0] = RD_size[0];
  if (0 <= RD_size[0] - 1) {
    memset(&ABSD_orig_data[0], 0, (unsigned int)(RD_size[0] * (int)sizeof(double)));
  }

  ABSD_size[0] = RD_size[0];
  if (0 <= RD_size[0] - 1) {
    memset(&ABSD_data[0], 0, (unsigned int)(RD_size[0] * (int)sizeof(double)));
  }

  f_size[0] = RD_size[0];
  if (0 <= RD_size[0] - 1) {
    memset(&f_data[0], 0, (unsigned int)(RD_size[0] * (int)sizeof(double)));
  }

  f_new_size[0] = RD_size[0];
  if (0 <= RD_size[0] - 1) {
    memset(&f_new_data[0], 0, (unsigned int)(RD_size[0] * (int)sizeof(double)));
  }

  *sht = 0.0;
  *sht2 = 0.0;
  param[0] = 0.0;
  param_new[0] = 0.0;
  param[1] = 0.0;
  param_new[1] = 0.0;
  param[2] = 0.0;
  param_new[2] = 0.0;
  param[3] = 0.0;
  param_new[3] = 0.0;
  *R2 = 0.0;
  *df = 0.0;

  /* ================ (E) Output initialization ===================== */
  /* ================ (B) Local variable initialization ===================== */
  varargin_1 = RD_size[0];
  TC = RD_size[0];
  HTC = (int)floor((double)RD_size[0] / 2.0);
  LinearOrNot = 0;
  EFC0 = 0.0;
  RFUR = 0.0;
  neg_BL = 0;

  /* neg BaseLine */
  /* ================ (E) Local variable initialization ===================== */
  /* ----------- (B) save MuDT Data ------------- */
  idx = (signed char)RD_size[0] - 1;
  for (i0 = 0; i0 <= idx; i0++) {
    tmp_data[i0] = (signed char)i0;
  }

  idx = (signed char)RD_size[0];
  for (i0 = 0; i0 < idx; i0++) {
    DataProcess_data[tmp_data[i0] + DataProcess_size[0]] = RD_data[i0];
  }

  /* ----------- (E) save MuDT Data ------------- */
  *LSR_val = Coder_DoN(RD_data, SFC, RD_size[0]);

  /* ----------- (B) RFU filter ------------- */
  if (SFC > RD_size[0]) {
    i0 = 1;
    i1 = 1;
  } else {
    i0 = (int)SFC;
    i1 = RD_size[0] + 1;
  }

  cdiff = i1 - i0;
  for (i1 = 0; i1 < cdiff; i1++) {
    varargin_1_data[i1] = RD_data[(i0 + i1) - 1];
  }

  n = cdiff - 1;
  if (cdiff <= 2) {
    if (cdiff == 1) {
      RD_scale = RD_data[i0 - 1];
    } else if ((RD_data[i0 - 1] > RD_data[i0]) || (rtIsNaN(RD_data[i0 - 1]) && (
                 !rtIsNaN(RD_data[i0])))) {
      RD_scale = RD_data[i0];
    } else {
      RD_scale = RD_data[i0 - 1];
    }
  } else {
    if (!rtIsNaN(varargin_1_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= cdiff)) {
        if (!rtIsNaN(varargin_1_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      RD_scale = RD_data[i0 - 1];
    } else {
      RD_scale = varargin_1_data[idx - 1];
      i0 = idx + 1;
      for (k = i0; k <= n + 1; k++) {
        apnd = varargin_1_data[k - 1];
        if (RD_scale > apnd) {
          RD_scale = apnd;
        }
      }
    }
  }

  *EndRFU = RD_data[RD_size[0] - 1] - RD_scale;
  if (FB == 0.0) {
    RFUR = *EndRFU / DRFU;
    if (RFUR < 1.0) {
      if (RFUR >= 0.8) {
        neg_BL = 1;
      } else {
        if (SFC > RD_size[0]) {
          i0 = 1;
          i1 = 1;
        } else {
          i0 = (int)SFC;
          i1 = RD_size[0] + 1;
        }

        if (SFC > RD_size[0]) {
          i2 = 1;
          y = 1;
        } else {
          i2 = (int)SFC;
          y = RD_size[0] + 1;
        }

        cdiff = i1 - i0;
        for (i1 = 0; i1 < cdiff; i1++) {
          varargin_1_data[i1] = RD_data[(i0 + i1) - 1];
        }

        n = cdiff - 1;
        if (cdiff <= 2) {
          if (cdiff == 1) {
            RD_scale = RD_data[i0 - 1];
          } else if ((RD_data[i0 - 1] < RD_data[i0]) || (rtIsNaN(RD_data[i0 - 1])
                      && (!rtIsNaN(RD_data[i0])))) {
            RD_scale = RD_data[i0];
          } else {
            RD_scale = RD_data[i0 - 1];
          }
        } else {
          if (!rtIsNaN(varargin_1_data[0])) {
            idx = 1;
          } else {
            idx = 0;
            k = 2;
            exitg1 = false;
            while ((!exitg1) && (k <= cdiff)) {
              if (!rtIsNaN(varargin_1_data[k - 1])) {
                idx = k;
                exitg1 = true;
              } else {
                k++;
              }
            }
          }

          if (idx == 0) {
            RD_scale = RD_data[i0 - 1];
          } else {
            RD_scale = varargin_1_data[idx - 1];
            i0 = idx + 1;
            for (k = i0; k <= n + 1; k++) {
              apnd = varargin_1_data[k - 1];
              if (RD_scale < apnd) {
                RD_scale = apnd;
              }
            }
          }
        }

        cdiff = y - i2;
        for (i0 = 0; i0 < cdiff; i0++) {
          varargin_1_data[i0] = RD_data[(i2 + i0) - 1];
        }

        n = cdiff - 1;
        if (cdiff <= 2) {
          if (cdiff == 1) {
            b_cdiff = RD_data[i2 - 1];
          } else if ((RD_data[i2 - 1] > RD_data[i2]) || (rtIsNaN(RD_data[i2 - 1])
                      && (!rtIsNaN(RD_data[i2])))) {
            b_cdiff = RD_data[i2];
          } else {
            b_cdiff = RD_data[i2 - 1];
          }
        } else {
          if (!rtIsNaN(varargin_1_data[0])) {
            idx = 1;
          } else {
            idx = 0;
            k = 2;
            exitg1 = false;
            while ((!exitg1) && (k <= cdiff)) {
              if (!rtIsNaN(varargin_1_data[k - 1])) {
                idx = k;
                exitg1 = true;
              } else {
                k++;
              }
            }
          }

          if (idx == 0) {
            b_cdiff = RD_data[i2 - 1];
          } else {
            b_cdiff = varargin_1_data[idx - 1];
            i0 = idx + 1;
            for (k = i0; k <= n + 1; k++) {
              apnd = varargin_1_data[k - 1];
              if (b_cdiff > apnd) {
                b_cdiff = apnd;
              }
            }
          }
        }

        RD_scale -= b_cdiff;
        if ((RD_scale > 2.0 * DRFU) && (*EndRFU / RD_scale < 0.5)) {
          /*  일단 음성이지만 너무 튀는 신호 jumping 보정하려고 */
          neg_BL = 1;
        } else {
          *result_well = 1.0;
          *DataProcessNum = 2.0;
        }
      }
    }
  }

  /* ----------- (E) RFU filter ------------- */
  /* ----------- (B) jumping ------------- */
  if (*result_well == 0.0) {
    b_RD_size[0] = RD_size[0];
    if (0 <= RD_size[0] - 1) {
      memcpy(&b_RD_data[0], &RD_data[0], (unsigned int)(RD_size[0] * (int)sizeof
              (double)));
    }

    Coder_Section_Jumping_v3_DoN(b_RD_data, b_RD_size, DRFU, result_well,
      DataProcessNum, AR, FB, SFC, HTC, RD_size[0], RD_diff_data, RD_diff_size,
      ivd_cdd_data, ivd_cdd_size, &RD_scale);
    RD_size[0] = b_RD_size[0];
    if (0 <= b_RD_size[0] - 1) {
      memcpy(&RD_data[0], &b_RD_data[0], (unsigned int)(b_RD_size[0] * (int)
              sizeof(double)));
    }

    if (SFC > TC) {
      i0 = 1;
      i1 = 1;
    } else {
      i0 = (int)SFC;
      i1 = varargin_1 + 1;
    }

    cdiff = i1 - i0;
    for (i1 = 0; i1 < cdiff; i1++) {
      varargin_1_data[i1] = b_RD_data[(i0 + i1) - 1];
    }

    n = cdiff - 1;
    if (cdiff <= 2) {
      if (cdiff == 1) {
        RD_scale = b_RD_data[i0 - 1];
      } else if ((b_RD_data[i0 - 1] > b_RD_data[i0]) || (rtIsNaN(b_RD_data[i0 -
                   1]) && (!rtIsNaN(b_RD_data[i0])))) {
        RD_scale = b_RD_data[i0];
      } else {
        RD_scale = b_RD_data[i0 - 1];
      }
    } else {
      if (!rtIsNaN(varargin_1_data[0])) {
        idx = 1;
      } else {
        idx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= cdiff)) {
          if (!rtIsNaN(varargin_1_data[k - 1])) {
            idx = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (idx == 0) {
        RD_scale = b_RD_data[i0 - 1];
      } else {
        RD_scale = varargin_1_data[idx - 1];
        i0 = idx + 1;
        for (k = i0; k <= n + 1; k++) {
          apnd = varargin_1_data[k - 1];
          if (RD_scale > apnd) {
            RD_scale = apnd;
          }
        }
      }
    }

    *EndRFU = b_RD_data[varargin_1 - 1] - RD_scale;
    if (neg_BL == 1) {
      *DataProcessNum = 0.0;
      *result_well = 0.0;
    }
  }

  /* ----------- (E) Degree of Noise ------------- */
  /* ----------- (B) Linear Filter ------------- */
  if ((*result_well == 0.0) && (!(isPC != 0.0)) && (neg_BL == 0)) {
    *result_well = 0.0;
    c_RD_size[0] = RD_size[0];
    if (0 <= RD_size[0] - 1) {
      memcpy(&b_RD_data[0], &RD_data[0], (unsigned int)(RD_size[0] * (int)sizeof
              (double)));
    }

    Coder_LinearFilter_v2(b_RD_data, c_RD_size, result_well, SFC, MFC,
                          varargin_1);
    if (*result_well != 0.0) {
      if (LinearFilter_type == 0.0) {
        *DataProcessNum = 13.0;
      } else {
        *result_well = 0.0;
        LinearOrNot = 1;
      }
    }
  }

  /* ----------- (E) Linear Filter ------------- */
  /* ----------- (B) unimportant filter ------------- */
  if (*result_well == 0.0) {
    *result_well = 0.0;
    *EFC = Coder_Section_Unimportant_v3(x_data, x_size, RD_data, RD_size, SFC,
      MFC, varargin_1, DRFU, result_well, DataProcessNum, AR, FB);
    if (neg_BL == 1) {
      *DataProcessNum = 0.0;
      *result_well = 0.0;
    }
  }

  /* ----------- (E) unimportant filter ------------- */
  /* ----------- (B) Quick Amp ------------- */
  if ((*result_well == 0.0) && (neg_BL == 0)) {
    /*      [EFC, EFC0, cff, scd_fit, ABSD, ABSD_orig, R_p2, SRFU, result_well]=Coder_Section_QuickAmp_v3(x,RD,SFC,EFC,HTC,TC,result_well,AR,FB); */
    *result_well = 0.0;
    Coder_Section_QuickAmp_v4(x_data, x_size, RD_data, RD_size, SFC, EFC, HTC,
      varargin_1, result_well, FB, &EFC0, cff, scd_fit_data, scd_fit_size,
      ABSD_data, ABSD_size, ABSD_orig_data, ABSD_orig_size, R_p2, &RD_scale);
  }

  /* ----------- (E) Quick Amp ------------- */
  /* ----------- (B) Baseline ------------- */
  if (*result_well == 0.0) {
    /*      [EFC, EFC0, cff, scd_fit]=Coder_Section_Baseline_v4(x,RD,SFC,MFC,EFC,TC,DRFU,LinearOrNot,AR,FB); */
    /*      [EFC, EFC0, cff, scd_fit]=Coder_Section_Baseline_v5(x,RD,SFC,MFC,EFC,TC,DRFU,LinearOrNot,AR,FB,dfC); */
    Coder_Section_Baseline_v6(x_data, x_size, RD_data, RD_size, SFC, MFC, EFC,
      varargin_1, DRFU, LinearOrNot, AR, FB, dfC, &EFC0, cff, scd_fit_data,
      scd_fit_size);
    if (neg_BL == 1) {
      *result_well = 1.0;
    } else {
      idx = scd_fit_size[0];
      for (i0 = 0; i0 < idx; i0++) {
        DataProcess_data[i0 + (DataProcess_size[0] << 1)] = scd_fit_data[i0];
      }

      *EndRFU = RD_data[varargin_1 - 1] - scd_fit_data[varargin_1 - 1];
    }
  }

  /* ----------- (E) Baseline ------------- */
  /* ----------- (B) Rp2 ------------- */
  if (*result_well == 0.0) {
    Coder_Section_Rp2(RPC, SFC, *EFC, RD_data, RD_size, scd_fit_data,
                      result_well, DataProcessNum, R_p2, ABSD_data, ABSD_size);
  }

  /* ----------- (E) Rp2 ------------- */
  /* ----------- (B) ABSD corrector ------------- */
  if (*result_well == 0.0) {
    ABSD_size[0] = RD_size[0];
    idx = RD_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      ABSD_data[i0] = RD_data[i0] - scd_fit_data[i0];
    }

    ABSD_orig_size[0] = RD_size[0];
    if (0 <= RD_size[0] - 1) {
      memcpy(&ABSD_orig_data[0], &ABSD_data[0], (unsigned int)(RD_size[0] * (int)
              sizeof(double)));
    }

    idx = RD_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      DataProcess_data[i0 + DataProcess_size[0] * 3] = ABSD_data[i0];
    }

    /*  baseline 보여줄 땐 이것 까지 필요없을 듯(개발자용 뷰어 PGR raw data 분석에는 포함) */
    RD_scale = Coder_ABSD_corrector_v3_1(SFC, MFC, ABSD_data, ABSD_size, Thrd,
      RD_diff_data, varargin_1);
    b_ABSD_size[0] = (int)RD_scale;
    idx = (int)RD_scale;
    if (0 <= idx - 1) {
      memcpy(&b_ABSD_data[0], &ABSD_data[0], (unsigned int)(idx * (int)sizeof
              (double)));
    }

    c_ABSD_data.data = &b_ABSD_data[0];
    c_ABSD_data.size = &b_ABSD_size[0];
    c_ABSD_data.allocatedSize = 100;
    c_ABSD_data.numDimensions = 1;
    c_ABSD_data.canFreeData = false;
    RD_scale = c_mean(&c_ABSD_data);
    idx = ABSD_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      ABSD_data[i0] -= RD_scale;
    }

    idx = ABSD_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      ABSD_orig_data[i0] -= RD_scale;
    }

    idx = ABSD_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      DataProcess_data[i0 + (DataProcess_size[0] << 2)] = ABSD_data[i0];
    }
  }

  /* ----------- (E) ABSD corrector ------------- */
  /* ----------- (B) For Quick Amp ------------- */
  if (*result_well == -3.0) {
    *result_well = 0.0;
    idx = scd_fit_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      DataProcess_data[i0 + (DataProcess_size[0] << 1)] = scd_fit_data[i0];
    }

    idx = ABSD_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      DataProcess_data[i0 + DataProcess_size[0] * 3] = ABSD_data[i0];
    }

    idx = ABSD_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      DataProcess_data[i0 + (DataProcess_size[0] << 2)] = ABSD_data[i0];
    }
  }

  /* ----------- (E) For Quick Amp ------------- */
  emxInit_real_T(&xdata, 1);
  emxInit_real_T(&b_y, 2);
  emxInit_real_T(&c_y, 2);
  emxInit_real_T(&RD, 1);
  if ((*result_well == 1.0) || (*result_well == 2.0)) {
    if (neg_BL == 0) {
      *EFC = varargin_1;
    } else {
      *DataProcessNum = 2.0;
      if ((RFUR >= 0.8) && (*EFC > 0.0)) {
        *EFC += (*EFC - (double)varargin_1) * (RFUR - 1.0) / 0.2;
        *EFC = rt_roundd_snf(*EFC);
      } else {
        *EFC = varargin_1;
      }
    }

    if (rtIsNaN(*EFC)) {
      i0 = b_y->size[0] * b_y->size[1];
      b_y->size[0] = 1;
      b_y->size[1] = 1;
      emxEnsureCapacity_real_T(b_y, i0);
      b_y->data[0] = rtNaN;
    } else if (*EFC < SFC) {
      b_y->size[0] = 1;
      b_y->size[1] = 0;
    } else if ((rtIsInf(SFC) || rtIsInf(*EFC)) && (SFC == *EFC)) {
      i0 = b_y->size[0] * b_y->size[1];
      b_y->size[0] = 1;
      b_y->size[1] = 1;
      emxEnsureCapacity_real_T(b_y, i0);
      b_y->data[0] = rtNaN;
    } else if (floor(SFC) == SFC) {
      i0 = b_y->size[0] * b_y->size[1];
      b_y->size[0] = 1;
      idx = (int)floor(*EFC - SFC);
      b_y->size[1] = idx + 1;
      emxEnsureCapacity_real_T(b_y, i0);
      for (i0 = 0; i0 <= idx; i0++) {
        b_y->data[i0] = SFC + (double)i0;
      }
    } else {
      RD_scale = floor((*EFC - SFC) + 0.5);
      apnd = SFC + RD_scale;
      b_cdiff = apnd - *EFC;
      if ((SFC > *EFC) || rtIsNaN(*EFC)) {
        RFUR = SFC;
      } else {
        RFUR = *EFC;
      }

      if (fabs(b_cdiff) < 4.4408920985006262E-16 * RFUR) {
        RD_scale++;
        apnd = *EFC;
      } else if (b_cdiff > 0.0) {
        apnd = SFC + (RD_scale - 1.0);
      } else {
        RD_scale++;
      }

      if (RD_scale >= 0.0) {
        n = (int)RD_scale;
      } else {
        n = 0;
      }

      i0 = b_y->size[0] * b_y->size[1];
      b_y->size[0] = 1;
      b_y->size[1] = n;
      emxEnsureCapacity_real_T(b_y, i0);
      if (n > 0) {
        b_y->data[0] = SFC;
        if (n > 1) {
          b_y->data[n - 1] = apnd;
          idx = (n - 1) / 2;
          for (k = 0; k <= idx - 2; k++) {
            b_y->data[1 + k] = SFC + (1.0 + (double)k);
            b_y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
          }

          if (idx << 1 == n - 1) {
            b_y->data[idx] = (SFC + apnd) / 2.0;
          } else {
            b_y->data[idx] = SFC + (double)idx;
            b_y->data[idx + 1] = apnd - (double)idx;
          }
        }
      }
    }

    i0 = xdata->size[0];
    xdata->size[0] = b_y->size[1];
    emxEnsureCapacity_real_T(xdata, i0);
    idx = b_y->size[1];
    for (i0 = 0; i0 < idx; i0++) {
      xdata->data[i0] = b_y->data[i0];
    }

    i0 = RD->size[0];
    RD->size[0] = xdata->size[0];
    emxEnsureCapacity_real_T(RD, i0);
    idx = xdata->size[0];
    for (i0 = 0; i0 < idx; i0++) {
      RD->data[i0] = RD_data[(int)xdata->data[i0] - 1];
    }

    Coder_linear_fitting(xdata, RD, &cff[0], &cff[1]);
    scd_fit_size[0] = x_size[0];
    idx = x_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      scd_fit_data[i0] = cff[0] * x_data[i0] + cff[1];
    }

    if ((*EFC < varargin_1) && (RD_data[varargin_1 - 1] < RD_data[0]) && (cff[0]
         < 0.0) && (FB == 0.0)) {
      HTC = (int)EFC0;
      apnd = scd_fit_data[HTC - 1];
      if ((apnd - scd_fit_data[varargin_1 - 1]) / (RD_data[varargin_1 - 1] -
           apnd) > 0.2) {
        cff[0] = (apnd - (4.0 * apnd + scd_fit_data[TC - 1]) / 5.0) / (EFC0 -
          (double)varargin_1);
        cff[1] = apnd - cff[0] * EFC0;
        if (HTC > TC) {
          i0 = 1;
          i1 = 0;
        } else {
          i0 = HTC;
          i1 = varargin_1;
        }

        if (varargin_1 < HTC) {
          c_y->size[0] = 1;
          c_y->size[1] = 0;
        } else if (EFC0 == EFC0) {
          i2 = c_y->size[0] * c_y->size[1];
          c_y->size[0] = 1;
          idx = (int)floor((double)varargin_1 - EFC0);
          c_y->size[1] = idx + 1;
          emxEnsureCapacity_real_T(c_y, i2);
          for (i2 = 0; i2 <= idx; i2++) {
            c_y->data[i2] = EFC0 + (double)i2;
          }
        } else {
          idx = (int)floor(((double)varargin_1 - EFC0) + 0.5);
          LinearOrNot = HTC + idx;
          cdiff = LinearOrNot - varargin_1;
          if (HTC > varargin_1) {
            y = HTC;
          } else {
            y = varargin_1;
          }

          if (fabs((double)cdiff) < 4.4408920985006262E-16 * (double)y) {
            idx++;
            LinearOrNot = varargin_1;
          } else if (cdiff > 0) {
            LinearOrNot = (HTC + idx) - 1;
          } else {
            idx++;
          }

          if (idx >= 0) {
            n = idx;
          } else {
            n = 0;
          }

          i2 = c_y->size[0] * c_y->size[1];
          c_y->size[0] = 1;
          c_y->size[1] = n;
          emxEnsureCapacity_real_T(c_y, i2);
          if (n > 0) {
            c_y->data[0] = EFC0;
            if (n > 1) {
              c_y->data[n - 1] = LinearOrNot;
              idx = (n - 1) / 2;
              for (k = 0; k <= idx - 2; k++) {
                c_y->data[1 + k] = EFC0 + (1.0 + (double)k);
                c_y->data[(n - k) - 2] = (LinearOrNot - k) - 1;
              }

              if (idx << 1 == n - 1) {
                c_y->data[idx] = (EFC0 + (double)LinearOrNot) / 2.0;
              } else {
                c_y->data[idx] = EFC0 + (double)idx;
                c_y->data[idx + 1] = LinearOrNot - idx;
              }
            }
          }
        }

        cdiff = (signed char)i1 - (signed char)i0;
        for (i1 = 0; i1 <= cdiff; i1++) {
          b_tmp_data[i1] = (signed char)((signed char)((signed char)i0 + (signed
            char)i1) - 1);
        }

        idx = cdiff + 1;
        for (i0 = 0; i0 < idx; i0++) {
          scd_fit_data[b_tmp_data[i0]] = cff[0] * c_y->data[i0] + cff[1];
        }
      }
    }

    /*      fprintf("RD(TC):%.1f, scd_fit(TC):%.1f, EFC:%d, RFUR:%.2f, neg_BL:%d\n", RD(TC),scd_fit(TC),EFC,RFUR,neg_BL); */
    *EndRFU = RD_data[varargin_1 - 1] - scd_fit_data[varargin_1 - 1];
    ABSD_orig_size[0] = RD_size[0];
    idx = RD_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      ABSD_orig_data[i0] = RD_data[i0] - scd_fit_data[i0];
    }

    ABSD_size[0] = RD_size[0];
    if (0 <= RD_size[0] - 1) {
      memcpy(&ABSD_data[0], &ABSD_orig_data[0], (unsigned int)(RD_size[0] * (int)
              sizeof(double)));
    }

    *result_well = 2.0;
  }

  emxFree_real_T(&RD);
  emxFree_real_T(&c_y);
  emxFree_real_T(&b_y);
  emxFree_real_T(&xdata);
}

/* End of code generation (AutoBaseline_v1.c) */
