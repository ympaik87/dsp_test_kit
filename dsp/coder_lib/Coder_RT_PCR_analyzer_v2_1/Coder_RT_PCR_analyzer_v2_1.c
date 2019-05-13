/*
 * Coder_RT_PCR_analyzer_v2_1.c
 *
 * Code generation for function 'Coder_RT_PCR_analyzer_v2_1'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_AsymmSigFit_old.h"
#include "Coder_AsymmSigFit.h"
#include "Coder_signal_corrector.h"
#include "Coder_classifier_2nd.h"
#include "Coder_SigFit.h"
#include "Coder_find_cycle.h"
#include "mean.h"
#include "Coder_new_ABSD.h"
#include "Coder_classifier.h"
#include "Coder_ABSD_corrector.h"
#include "Coder_ABSD_corrector_v3.h"
#include "Coder_Section_Rp2.h"
#include "Coder_Section_Baseline_v4.h"
#include "Coder_Section_Baseline_v5.h"
#include "Coder_Section_Baseline_v6.h"
#include "Coder_Section_QuickAmp_v3.h"
#include "Coder_Section_QuickAmp_v4.h"
#include "Coder_Section_Unimportant_v3.h"
#include "Coder_LinearFilter_v2.h"
#include "Coder_Section_Jumping_v3_DoN.h"
#include "Coder_DoN.h"

/* Function Definitions */
void Coder_RT_PCR_analyzer_v2_1(const double x_data[], const int x_size[1],
  double RD_data[], int RD_size[1], const double perturbation_data[], const int
  perturbation_size[1], double SFC, double MFC, double DRFU, double Thrd, double
  RPC, double RC, double dfM, double dfC, double PMC, double FB, double AR,
  double isPC, const double ver_array_data[], const int ver_array_size[1],
  double DS, double *result_well, double *DataProcessNum, double
  DataProcess_data[], int DataProcess_size[2], double *LSR_val, double
  RD_diff_data[], int RD_diff_size[1], double ivd_cdd_ouput_data[], int
  ivd_cdd_ouput_size[2], double cff[2], double scd_fit_data[], int scd_fit_size
  [1], double *R_p2, double *EFC, double ABSD_orig_data[], int ABSD_orig_size[1],
  double ABSD_data[], int ABSD_size[1], double f_data[], int f_size[1], double
  f_new_data[], int f_new_size[1], double *sht, double *sht2, double param[4],
  double param_new[4], double *R2, double *EndRFU, double *df)
{
  int idx;
  int ivd_cdd_size[2];
  double Max_DRFU_Thrd;
  int varargin_1;
  int TC;
  int HTC;
  int LinearOrNot;
  double SRFU;
  double SC;
  double EFC0;
  int i0;
  signed char tmp_data[100];
  int loop_ub_tmp;
  double varargin_1_data[199];
  double ex;
  int k;
  boolean_T exitg1;
  double d0;
  double ivd_cdd_data[100];
  int b_RD_size[1];
  double b_RD_data[100];
  double b_SRFU[4];
  int b_ABSD_size[1];
  int c_ABSD_size[1];
  emxArray_real_T b_ABSD_data;
  double c_ABSD_data[100];
  emxArray_real_T d_ABSD_data;
  double e_ABSD_data[100];
  (void)perturbation_size;
  (void)ver_array_size;

  /* ================ (B) Output initialization ===================== */
  *result_well = 0.0;
  *DataProcessNum = 0.0;
  DataProcess_size[0] = RD_size[0];
  DataProcess_size[1] = 8;
  idx = RD_size[0] << 3;
  if (0 <= idx - 1) {
    memset(&DataProcess_data[0], 0, (unsigned int)(idx * (int)sizeof(double)));
  }

  *LSR_val = 0.0;
  RD_diff_size[0] = RD_size[0];
  if (0 <= RD_size[0] - 1) {
    memset(&RD_diff_data[0], 0, (unsigned int)(RD_size[0] * (int)sizeof(double)));
  }

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
  if ((DRFU > Thrd) || rtIsNaN(Thrd)) {
    Max_DRFU_Thrd = DRFU;
  } else {
    Max_DRFU_Thrd = Thrd;
  }

  varargin_1 = RD_size[0];
  TC = RD_size[0];
  HTC = (int)floor((double)RD_size[0] / 2.0);
  LinearOrNot = 0;
  SRFU = 0.0;
  SC = 0.0;
  EFC0 = 0.0;

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
  /* ----------- (B) RFU filter ------------- */
  if (SFC > RD_size[0]) {
    i0 = 0;
    idx = 0;
  } else {
    i0 = (int)SFC - 1;
    idx = RD_size[0];
  }

  loop_ub_tmp = idx - i0;
  for (idx = 0; idx < loop_ub_tmp; idx++) {
    varargin_1_data[idx] = RD_data[i0 + idx];
  }

  if (loop_ub_tmp <= 2) {
    if (loop_ub_tmp == 1) {
      ex = RD_data[i0];
    } else {
      ex = RD_data[i0 + 1];
      if ((RD_data[i0] > ex) || (rtIsNaN(RD_data[i0]) && (!rtIsNaN(ex)))) {
      } else {
        ex = RD_data[i0];
      }
    }
  } else {
    if (!rtIsNaN(varargin_1_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= loop_ub_tmp)) {
        if (!rtIsNaN(varargin_1_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      ex = RD_data[i0];
    } else {
      ex = varargin_1_data[idx - 1];
      i0 = idx + 1;
      for (k = i0; k <= loop_ub_tmp; k++) {
        d0 = varargin_1_data[k - 1];
        if (ex > d0) {
          ex = d0;
        }
      }
    }
  }

  *EndRFU = RD_data[RD_size[0] - 1] - ex;
  if ((FB == 0.0) && (*EndRFU < DRFU)) {
    *result_well = 1.0;
    *DataProcessNum = 2.0;
  }

  /* ----------- (E) RFU filter ------------- */
  /* ----------- (B) Degree of Noise ------------- */
  if (*result_well == 0.0) {
    *LSR_val = Coder_DoN(RD_data, SFC, RD_size[0]);
  }

  /* ----------- (E) Degree of Noise ------------- */
  /* ----------- (B) jumping ------------- */
  if (*result_well == 0.0) {
    if (ver_array_data[3] == 3.0) {
      Coder_Section_Jumping_v3_DoN(RD_data, RD_size, DRFU, result_well,
        DataProcessNum, DS, FB, SFC, HTC, RD_size[0], RD_diff_data, RD_diff_size,
        ivd_cdd_data, ivd_cdd_size, &ex);
    }

    if (SFC > TC) {
      i0 = 0;
      idx = 0;
    } else {
      i0 = (int)SFC - 1;
      idx = varargin_1;
    }

    loop_ub_tmp = idx - i0;
    for (idx = 0; idx < loop_ub_tmp; idx++) {
      varargin_1_data[idx] = RD_data[i0 + idx];
    }

    if (loop_ub_tmp <= 2) {
      if (loop_ub_tmp == 1) {
        ex = RD_data[i0];
      } else {
        ex = RD_data[i0 + 1];
        if ((RD_data[i0] > ex) || (rtIsNaN(RD_data[i0]) && (!rtIsNaN(ex)))) {
        } else {
          ex = RD_data[i0];
        }
      }
    } else {
      if (!rtIsNaN(varargin_1_data[0])) {
        idx = 1;
      } else {
        idx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= loop_ub_tmp)) {
          if (!rtIsNaN(varargin_1_data[k - 1])) {
            idx = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (idx == 0) {
        ex = RD_data[i0];
      } else {
        ex = varargin_1_data[idx - 1];
        i0 = idx + 1;
        for (k = i0; k <= loop_ub_tmp; k++) {
          d0 = varargin_1_data[k - 1];
          if (ex > d0) {
            ex = d0;
          }
        }
      }
    }

    *EndRFU = RD_data[varargin_1 - 1] - ex;
  }

  /* ----------- (E) Degree of Noise ------------- */
  /* ----------- (B) Linear Filter ------------- */
  if ((*result_well == 0.0) && (!(isPC != 0.0))) {
    *result_well = 0.0;
    b_RD_size[0] = RD_size[0];
    if (0 <= RD_size[0] - 1) {
      memcpy(&b_RD_data[0], &RD_data[0], (unsigned int)(RD_size[0] * (int)sizeof
              (double)));
    }

    Coder_LinearFilter_v2(b_RD_data, b_RD_size, result_well, SFC, MFC,
                          varargin_1);
    if (*result_well != 0.0) {
      if (ver_array_data[4] == 0.0) {
        *DataProcessNum = 13.0;
      } else {
        *result_well = 0.0;
        LinearOrNot = 1;
      }
    }
  }

  /* ----------- (E) Linear Filter ------------- */
  /* ----------- (B) unimportant filter ------------- */
  if ((*result_well == 0.0) && (ver_array_data[5] == 3.0)) {
    *result_well = 0.0;
    *EFC = Coder_Section_Unimportant_v3(x_data, x_size, RD_data, RD_size, SFC,
      MFC, varargin_1, DRFU, result_well, DataProcessNum, AR, FB);
  }

  /* ----------- (E) unimportant filter ------------- */
  /* ----------- (B) Quick Amp ------------- */
  if (*result_well == 0.0) {
    if (ver_array_data[6] == 3.0) {
      *result_well = 0.0;
      Coder_Section_QuickAmp_v3(x_data, x_size, RD_data, RD_size, SFC, EFC, HTC,
        varargin_1, result_well, DS, FB, &EFC0, cff, scd_fit_data, scd_fit_size,
        ABSD_data, ABSD_size, ABSD_orig_data, ABSD_orig_size, R_p2, &SRFU);
    } else {
      if (ver_array_data[6] == 4.0) {
        *result_well = 0.0;
        Coder_Section_QuickAmp_v4(x_data, x_size, RD_data, RD_size, SFC, EFC,
          HTC, varargin_1, result_well, DS, FB, &EFC0, cff, scd_fit_data,
          scd_fit_size, ABSD_data, ABSD_size, ABSD_orig_data, ABSD_orig_size,
          R_p2, &SRFU);
      }
    }
  }

  /* ----------- (E) Quick Amp ------------- */
  /* ----------- (B) Baseline ------------- */
  if (*result_well == 0.0) {
    if (ver_array_data[7] == 4.0) {
      Coder_Section_Baseline_v4(x_data, x_size, RD_data, RD_size, SFC, MFC, EFC,
        varargin_1, DRFU, LinearOrNot, AR, FB, &EFC0, cff, scd_fit_data,
        scd_fit_size);
    } else if (ver_array_data[7] == 5.0) {
      Coder_Section_Baseline_v5(x_data, x_size, RD_data, RD_size, SFC, MFC, EFC,
        varargin_1, DRFU, LinearOrNot, AR, FB, dfC, &EFC0, cff, scd_fit_data,
        scd_fit_size);
    } else {
      if (ver_array_data[7] == 6.0) {
        Coder_Section_Baseline_v6(x_data, x_size, RD_data, RD_size, SFC, MFC,
          EFC, varargin_1, DRFU, LinearOrNot, AR, FB, dfC, &EFC0, cff,
          scd_fit_data, scd_fit_size);
      }
    }

    idx = scd_fit_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      DataProcess_data[i0 + (DataProcess_size[0] << 1)] = scd_fit_data[i0];
    }

    *EndRFU = RD_data[varargin_1 - 1] - scd_fit_data[varargin_1 - 1];
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

    if (ver_array_data[0] == 1.0) {
      Coder_ABSD_corrector(SFC, MFC, ABSD_data, ABSD_size);
    } else {
      if (ver_array_data[0] == 0.0) {
        Coder_ABSD_corrector_v3(SFC, MFC, ABSD_data, ABSD_size, Thrd,
          RD_diff_data, varargin_1);
      }
    }

    idx = ABSD_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      DataProcess_data[i0 + (DataProcess_size[0] << 2)] = ABSD_data[i0];
    }

    if (SFC > MFC - 2.0) {
      i0 = 0;
      idx = 0;
    } else {
      i0 = (int)SFC - 1;
      idx = (int)(MFC - 2.0);
    }

    k = idx - i0;
    b_ABSD_size[0] = k;
    for (idx = 0; idx < k; idx++) {
      c_ABSD_data[idx] = ABSD_data[i0 + idx];
    }

    b_ABSD_data.data = &c_ABSD_data[0];
    b_ABSD_data.size = &b_ABSD_size[0];
    b_ABSD_data.allocatedSize = 100;
    b_ABSD_data.numDimensions = 1;
    b_ABSD_data.canFreeData = false;
    SRFU = c_mean(&b_ABSD_data);
    SC = SFC;
  }

  /* ----------- (E) ABSD corrector ------------- */
  /* ----------- (B) For Quick Amp ------------- */
  if (*result_well == -3.0) {
    SC = 1.0;
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
  /* ----------- (B) sigmoid fitting ------------- */
  if (*result_well == 0.0) {
    b_SRFU[0] = SRFU;
    b_SRFU[1] = ABSD_data[varargin_1 - 1];
    b_SRFU[2] = Coder_find_cycle(ABSD_data, ABSD_size, MFC, varargin_1);
    b_SRFU[3] = 0.2;
    Coder_SigFit(x_data, x_size, ABSD_data, result_well, b_SRFU, &SC, SFC, HTC,
                 varargin_1, perturbation_data, param, f_data, f_size);
    if (*result_well == 3.0) {
      *DataProcessNum = 5.0;
    }

    idx = f_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      DataProcess_data[i0 + DataProcess_size[0] * 5] = f_data[i0];
    }
  }

  /* ----------- (E) sigmoid fitting ------------- */
  /* ----------- (B) 1st classifier ------------- */
  if (*result_well == 0.0) {
    Coder_classifier(x_data, x_size, ABSD_data, ABSD_size, f_data, f_size, param,
                     SC, varargin_1, result_well, DataProcessNum, RC,
                     Max_DRFU_Thrd, dfM, dfC, PMC, isPC, R2, sht, EndRFU, df);
  }

  /* ----------- (E) sigmoid fitting ------------- */
  /* ----------- (B) 2단 꺾기 ------------- */
  if (*result_well == -1.0) {
    Coder_new_ABSD(x_data, x_size, ABSD_data, ABSD_size, EFC, varargin_1,
                   result_well);
    idx = ABSD_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      DataProcess_data[i0 + DataProcess_size[0] * 6] = ABSD_data[i0];
    }
  }

  if (*result_well == -1.0) {
    if (SFC > MFC - 2.0) {
      i0 = 0;
      idx = 0;
    } else {
      i0 = (int)SFC - 1;
      idx = (int)(MFC - 2.0);
    }

    k = idx - i0;
    c_ABSD_size[0] = k;
    for (idx = 0; idx < k; idx++) {
      e_ABSD_data[idx] = ABSD_data[i0 + idx];
    }

    d_ABSD_data.data = &e_ABSD_data[0];
    d_ABSD_data.size = &c_ABSD_size[0];
    d_ABSD_data.allocatedSize = 100;
    d_ABSD_data.numDimensions = 1;
    d_ABSD_data.canFreeData = false;
    SRFU = c_mean(&d_ABSD_data);
    SC = SFC;
    *result_well = -1.0;
    b_SRFU[0] = SRFU;
    b_SRFU[1] = ABSD_data[varargin_1 - 1];
    b_SRFU[2] = Coder_find_cycle(ABSD_data, ABSD_size, MFC, varargin_1);
    b_SRFU[3] = 0.2;
    Coder_SigFit(x_data, x_size, ABSD_data, result_well, b_SRFU, &SC, SFC, HTC,
                 varargin_1, perturbation_data, param, f_data, f_size);
    if (*result_well == 3.0) {
      *DataProcessNum = 5.0;
    }

    idx = f_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      DataProcess_data[i0 + DataProcess_size[0] * 7] = f_data[i0];
    }
  }

  if (*result_well == -1.0) {
    Coder_classifier_2nd(x_data, x_size, ABSD_data, f_data, param, SC,
                         varargin_1, result_well, DataProcessNum, RC,
                         Max_DRFU_Thrd, dfM, dfC, PMC, R2, sht, EndRFU, df);
  }

  /* ----------- (E) 2단 꺾기 ------------- */
  /* ----------- (B) DataProcessNum 조정 ------------- */
  if (*result_well <= 0.0) {
    *DataProcessNum = *result_well;
  }

  /* ----------- (E) DataProcessNum 조정 ------------- */
  /* ----------- (B) Special algorithm for GIP PC ------------- */
  if ((*result_well == 0.0) && (ver_array_data[2] != 0.0)) {
    Coder_signal_corrector(x_data, ABSD_data, EFC0, varargin_1);
  }

  /* ----------- (E) Special algorithm for GIP PC ------------- */
  /* ----------- (B) Ct correction ------------- */
  if (*result_well == 0.0) {
    if (ver_array_data[1] == 1.0) {
      Coder_AsymmSigFit_old(x_data, x_size, ABSD_data, ABSD_size, f_data, f_size,
                            result_well, DataProcessNum, param, SFC, MFC, EFC0,
                            varargin_1, SRFU, Thrd, Max_DRFU_Thrd, sht,
                            perturbation_data, f_new_data, f_new_size, param_new,
                            sht2);
    } else {
      if (ver_array_data[1] == 0.0) {
        Coder_AsymmSigFit(x_data, x_size, ABSD_data, ABSD_size, f_data, f_size,
                          result_well, DataProcessNum, param, SFC, MFC, EFC0,
                          varargin_1, SRFU, Thrd, Max_DRFU_Thrd, sht,
                          perturbation_data, f_new_data, f_new_size, param_new,
                          sht2);
      }
    }
  }

  /* ----------- (E) Ct correction ------------- */
  /* ----------- (B) EndRFU 조정 ------------- */
  if (*DataProcessNum == -3.0) {
    *EndRFU = f_data[varargin_1 - 1] - f_data[0];
    idx = f_size[0];
    for (i0 = 0; i0 < idx; i0++) {
      DataProcess_data[i0 + DataProcess_size[0] * 7] = f_data[i0];
    }
  } else {
    if (*DataProcessNum == -2.0) {
      *EndRFU = f_new_data[varargin_1 - 1] - f_new_data[0];
      idx = f_new_size[0];
      for (i0 = 0; i0 < idx; i0++) {
        DataProcess_data[i0 + DataProcess_size[0] * 7] = f_new_data[i0];
      }
    }
  }

  /* ----------- (E) EndRFU 조정 ------------- */
  k = ivd_cdd_size[1];
  idx = RD_size[0];
  if (k < idx) {
    idx = k;
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

/* End of code generation (Coder_RT_PCR_analyzer_v2_1.c) */
