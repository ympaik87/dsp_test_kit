/*
 * Coder_Section_QuickAmp_v4.c
 *
 * Code generation for function 'Coder_Section_QuickAmp_v4'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_Section_QuickAmp_v4.h"
#include "AutoBaseline_v2_emxutil.h"
#include "mean.h"
#include "Coder_scd_fitting.h"
#include "Coder_Indirect_curvature_v3.h"
#include "Coder_min5.h"
#include "sum.h"
#include "diff.h"
#include "Coder_find_peak_cluster.h"

/* Function Definitions */
void Coder_Section_QuickAmp_v4(const double x_data[], const int x_size[1], const
  double RD_data[], const int RD_size[1], double SFC, double *EFC, double HTC,
  double TC, double *result_well, double AR, double FB, double *EFC0, double
  cff[2], double scd_fit_data[], int scd_fit_size[1], double ABSD_data[], int
  ABSD_size[1], double ABSD_orig_data[], int ABSD_orig_size[1], double *R_p2,
  double *SRFU)
{
  double EFC_temp;
  int loop_ub;
  int RDS_tmp_tmp_tmp;
  int RDS_tmp_tmp;
  int RDS_tmp;
  double b_RDS_tmp;
  double RDS;
  int quick_amp;
  emxArray_real_T *fit_intv;
  emxArray_real_T *varargin_1;
  emxArray_real_T *b_fit_intv;
  int i42;
  double ndbl;
  double abc;
  int b_RD_size[1];
  int i43;
  int n;
  double rotated_RD_data[100];
  double min5_idx[5];
  int nx;
  double cff0_idx_0;
  int idx;
  double apnd;
  int rotated_RD_size[1];
  boolean_T exitg1;
  double b_rotated_RD_data[199];
  double cdiff;
  double u0;
  double tmp_data[53];
  int tmp_size[2];
  int c_RD_size[1];
  double b_x_data[198];
  int y_size[1];
  emxArray_real_T y_data;
  double b_y_data[198];
  double b_varargin_1[3];
  signed char b_tmp_data[50];
  *result_well = 0.0;

  /*  v3대비 이른증폭의 EFC 더 정확하게 */
  EFC_temp = *EFC;

  /* ---(B) initialize --- */
  *EFC0 = 0.0;
  cff[0] = 0.0;
  cff[1] = 0.0;
  scd_fit_size[0] = (signed char)x_size[0];
  loop_ub = (signed char)x_size[0];
  if (0 <= loop_ub - 1) {
    memset(&scd_fit_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  ABSD_size[0] = (signed char)RD_size[0];
  loop_ub = (signed char)RD_size[0];
  if (0 <= loop_ub - 1) {
    memset(&ABSD_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  ABSD_orig_size[0] = (signed char)RD_size[0];
  loop_ub = (signed char)RD_size[0];
  if (0 <= loop_ub - 1) {
    memset(&ABSD_orig_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  *R_p2 = 0.0;
  *SRFU = 0.0;

  /* ---(E) initialize ---  */
  RDS_tmp_tmp_tmp = (int)SFC;
  RDS_tmp_tmp = RDS_tmp_tmp_tmp - 1;
  RDS_tmp = (int)TC;
  b_RDS_tmp = RD_data[RDS_tmp - 1];
  RDS = b_RDS_tmp - RD_data[RDS_tmp_tmp];
  quick_amp = 0;
  emxInit_real_T(&fit_intv, 2);
  emxInit_real_T(&varargin_1, 1);
  emxInit_real_T(&b_fit_intv, 1);
  if ((RDS > 500.0 * AR) && (FB == 0.0)) {
    loop_ub = (int)HTC;
    i42 = loop_ub - 1;
    ndbl = RD_data[i42] - RD_data[RDS_tmp_tmp];
    if (ndbl > 0.0) {
      ndbl /= RDS;
      if (ndbl > 0.7) {
        quick_amp = 1;
        *EFC = 5.0;
      } else {
        if (ndbl > 0.4) {
          abc = RDS / (TC - SFC);
          n = RD_size[0];
          for (i43 = 0; i43 < n; i43++) {
            rotated_RD_data[i43] = (RD_data[i43] - abc * (x_data[i43] - SFC)) -
              RD_data[RDS_tmp_tmp];
          }

          if (SFC > TC) {
            i43 = 0;
            nx = 0;
          } else {
            i43 = RDS_tmp_tmp;
            nx = RDS_tmp;
          }

          n = nx - i43;
          rotated_RD_size[0] = n;
          for (nx = 0; nx < n; nx++) {
            b_rotated_RD_data[nx] = rotated_RD_data[i43 + nx];
          }

          Coder_find_peak_cluster(b_rotated_RD_data, rotated_RD_size, SFC, &abc,
            &cff0_idx_0, &ndbl);
          if ((cff0_idx_0 - abc > 10.0) && (ndbl > 0.3) && (abc < HTC)) {
            quick_amp = 2;
            abc -= 2.0;
            if (5.0 > abc) {
              abc = 5.0;
            }

            *EFC = abc;
          }
        }
      }
    }

    if (quick_amp == 1) {
      if (HTC > TC) {
        i42 = 0;
        RDS_tmp = 0;
      }

      i43 = varargin_1->size[0];
      n = (int)(HTC - 1.0);
      varargin_1->size[0] = (n + RDS_tmp) - i42;
      emxEnsureCapacity_real_T(varargin_1, i43);
      for (i43 = 0; i43 < n; i43++) {
        varargin_1->data[i43] = rtMinusInf;
      }

      nx = RDS_tmp - i42;
      for (i43 = 0; i43 < nx; i43++) {
        varargin_1->data[i43 + n] = RD_data[i42 + i43];
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
          RDS_tmp = 2;
          exitg1 = false;
          while ((!exitg1) && (RDS_tmp <= varargin_1->size[0])) {
            if (!rtIsNaN(varargin_1->data[RDS_tmp - 1])) {
              idx = RDS_tmp;
              exitg1 = true;
            } else {
              RDS_tmp++;
            }
          }
        }

        if (idx == 0) {
          idx = 1;
        } else {
          apnd = varargin_1->data[idx - 1];
          i42 = idx + 1;
          for (RDS_tmp = i42; RDS_tmp <= n; RDS_tmp++) {
            if (apnd < varargin_1->data[RDS_tmp - 1]) {
              apnd = varargin_1->data[RDS_tmp - 1];
              idx = RDS_tmp;
            }
          }
        }
      }

      if (RDS_tmp_tmp_tmp > idx) {
        i42 = 0;
        i43 = 0;
      } else {
        i42 = RDS_tmp_tmp;
        i43 = idx;
      }

      nx = i43 - i42;
      c_RD_size[0] = nx;
      for (i43 = 0; i43 < nx; i43++) {
        rotated_RD_data[i43] = RD_data[i42 + i43];
      }

      diff(rotated_RD_data, c_RD_size, b_x_data, rotated_RD_size);
      nx = rotated_RD_size[0];
      y_size[0] = (unsigned char)rotated_RD_size[0];
      for (RDS_tmp = 0; RDS_tmp < nx; RDS_tmp++) {
        b_y_data[RDS_tmp] = fabs(b_x_data[RDS_tmp]);
      }

      y_data.data = &b_y_data[0];
      y_data.size = &y_size[0];
      y_data.allocatedSize = 198;
      y_data.numDimensions = 1;
      y_data.canFreeData = false;
      if (sum(&y_data) / (RD_data[idx - 1] - RD_data[RDS_tmp_tmp]) > 1.7) {
        quick_amp = 0;
        *EFC = EFC_temp;
      }

      /*  specific_logic=1; */
    }

    if (quick_amp >= 1) {
      b_RD_size[0] = loop_ub;
      if (0 <= loop_ub - 1) {
        memcpy(&rotated_RD_data[0], &RD_data[0], (unsigned int)(loop_ub * (int)
                sizeof(double)));
      }

      Coder_min5(rotated_RD_data, b_RD_size, min5_idx);
      if (quick_amp == 1) {
        n = RD_size[0];
        if (RD_size[0] <= 2) {
          if (RD_size[0] == 1) {
            apnd = RD_data[0];
          } else if ((RD_data[0] < RD_data[1]) || (rtIsNaN(RD_data[0]) &&
                      (!rtIsNaN(RD_data[1])))) {
            apnd = RD_data[1];
          } else {
            apnd = RD_data[0];
          }
        } else {
          if (!rtIsNaN(RD_data[0])) {
            idx = 1;
          } else {
            idx = 0;
            RDS_tmp = 2;
            exitg1 = false;
            while ((!exitg1) && (RDS_tmp <= RD_size[0])) {
              if (!rtIsNaN(RD_data[RDS_tmp - 1])) {
                idx = RDS_tmp;
                exitg1 = true;
              } else {
                RDS_tmp++;
              }
            }
          }

          if (idx == 0) {
            apnd = RD_data[0];
          } else {
            apnd = RD_data[idx - 1];
            i42 = idx + 1;
            for (RDS_tmp = i42; RDS_tmp <= n; RDS_tmp++) {
              ndbl = RD_data[RDS_tmp - 1];
              if (apnd < ndbl) {
                apnd = ndbl;
              }
            }
          }
        }

        abc = apnd - RD_data[(int)min5_idx[0] - 1];
        nx = (int)(HTC + 3.0);
        i42 = varargin_1->size[0];
        varargin_1->size[0] = nx;
        emxEnsureCapacity_real_T(varargin_1, i42);
        for (i42 = 0; i42 < nx; i42++) {
          varargin_1->data[i42] = RD_data[i42] / abc * TC;
        }

        Coder_Indirect_curvature_v3(varargin_1->data, HTC + 3.0, tmp_data,
          tmp_size);
        i42 = fit_intv->size[0] * fit_intv->size[1];
        fit_intv->size[0] = 1;
        fit_intv->size[1] = tmp_size[1];
        emxEnsureCapacity_real_T(fit_intv, i42);
        loop_ub = tmp_size[0] * tmp_size[1];
        for (i42 = 0; i42 < loop_ub; i42++) {
          fit_intv->data[i42] = tmp_data[i42];
        }

        n = fit_intv->size[1];
        if (fit_intv->size[1] <= 2) {
          if (fit_intv->size[1] == 1) {
            idx = 1;
          } else if ((fit_intv->data[0] < fit_intv->data[1]) || (rtIsNaN
                      (fit_intv->data[0]) && (!rtIsNaN(fit_intv->data[1])))) {
            idx = 2;
          } else {
            idx = 1;
          }
        } else {
          if (!rtIsNaN(fit_intv->data[0])) {
            idx = 1;
          } else {
            idx = 0;
            RDS_tmp = 2;
            exitg1 = false;
            while ((!exitg1) && (RDS_tmp <= fit_intv->size[1])) {
              if (!rtIsNaN(fit_intv->data[RDS_tmp - 1])) {
                idx = RDS_tmp;
                exitg1 = true;
              } else {
                RDS_tmp++;
              }
            }
          }

          if (idx == 0) {
            idx = 1;
          } else {
            apnd = fit_intv->data[idx - 1];
            i42 = idx + 1;
            for (RDS_tmp = i42; RDS_tmp <= n; RDS_tmp++) {
              if (apnd < fit_intv->data[RDS_tmp - 1]) {
                apnd = fit_intv->data[RDS_tmp - 1];
                idx = RDS_tmp;
              }
            }
          }
        }

        /* 190227, Coder_Indirect_curvature_v3(RD,TC,n)의 n을 3-->4 변경 */
        if (!rtIsNaN(min5_idx[0])) {
          nx = 1;
        } else {
          nx = 0;
          RDS_tmp = 2;
          exitg1 = false;
          while ((!exitg1) && (RDS_tmp < 6)) {
            if (!rtIsNaN(min5_idx[RDS_tmp - 1])) {
              nx = RDS_tmp;
              exitg1 = true;
            } else {
              RDS_tmp++;
            }
          }
        }

        if (nx == 0) {
          apnd = min5_idx[0];
        } else {
          apnd = min5_idx[nx - 1];
          i42 = nx + 1;
          for (RDS_tmp = i42; RDS_tmp < 6; RDS_tmp++) {
            ndbl = min5_idx[RDS_tmp - 1];
            if (apnd < ndbl) {
              apnd = ndbl;
            }
          }
        }

        b_varargin_1[2] = *EFC;
        cff0_idx_0 = (double)idx - 2.0;
        if ((double)idx - 2.0 < apnd - 2.0) {
          cff0_idx_0 = apnd - 2.0;
        }

        if (cff0_idx_0 < b_varargin_1[2]) {
          cff0_idx_0 = b_varargin_1[2];
        }

        *EFC = cff0_idx_0;
      }

      if (*EFC < 10.0) {
        if (rtIsNaN(*EFC)) {
          i42 = fit_intv->size[0] * fit_intv->size[1];
          fit_intv->size[0] = 1;
          fit_intv->size[1] = 1;
          emxEnsureCapacity_real_T(fit_intv, i42);
          fit_intv->data[0] = rtNaN;
        } else if (*EFC < 1.0) {
          fit_intv->size[0] = 1;
          fit_intv->size[1] = 0;
        } else if (rtIsInf(*EFC) && (1.0 == *EFC)) {
          i42 = fit_intv->size[0] * fit_intv->size[1];
          fit_intv->size[0] = 1;
          fit_intv->size[1] = 1;
          emxEnsureCapacity_real_T(fit_intv, i42);
          fit_intv->data[0] = rtNaN;
        } else {
          i42 = fit_intv->size[0] * fit_intv->size[1];
          fit_intv->size[0] = 1;
          loop_ub = (int)floor(*EFC - 1.0);
          fit_intv->size[1] = loop_ub + 1;
          emxEnsureCapacity_real_T(fit_intv, i42);
          for (i42 = 0; i42 <= loop_ub; i42++) {
            fit_intv->data[i42] = 1.0 + (double)i42;
          }
        }
      } else {
        cff0_idx_0 = *EFC - 8.0;
        if ((!(cff0_idx_0 < SFC)) && (!rtIsNaN(SFC))) {
          cff0_idx_0 = SFC;
        }

        if (rtIsNaN(cff0_idx_0) || rtIsNaN(*EFC)) {
          i42 = fit_intv->size[0] * fit_intv->size[1];
          fit_intv->size[0] = 1;
          fit_intv->size[1] = 1;
          emxEnsureCapacity_real_T(fit_intv, i42);
          fit_intv->data[0] = rtNaN;
        } else if (*EFC < cff0_idx_0) {
          fit_intv->size[0] = 1;
          fit_intv->size[1] = 0;
        } else if ((rtIsInf(cff0_idx_0) || rtIsInf(*EFC)) && (cff0_idx_0 == *EFC))
        {
          i42 = fit_intv->size[0] * fit_intv->size[1];
          fit_intv->size[0] = 1;
          fit_intv->size[1] = 1;
          emxEnsureCapacity_real_T(fit_intv, i42);
          fit_intv->data[0] = rtNaN;
        } else if (floor(cff0_idx_0) == cff0_idx_0) {
          i42 = fit_intv->size[0] * fit_intv->size[1];
          fit_intv->size[0] = 1;
          loop_ub = (int)floor(*EFC - cff0_idx_0);
          fit_intv->size[1] = loop_ub + 1;
          emxEnsureCapacity_real_T(fit_intv, i42);
          for (i42 = 0; i42 <= loop_ub; i42++) {
            fit_intv->data[i42] = cff0_idx_0 + (double)i42;
          }
        } else {
          ndbl = floor((*EFC - cff0_idx_0) + 0.5);
          apnd = cff0_idx_0 + ndbl;
          cdiff = apnd - *EFC;
          u0 = fabs(cff0_idx_0);
          abc = fabs(*EFC);
          if ((u0 > abc) || rtIsNaN(abc)) {
            abc = u0;
          }

          if (fabs(cdiff) < 4.4408920985006262E-16 * abc) {
            ndbl++;
            apnd = *EFC;
          } else if (cdiff > 0.0) {
            apnd = cff0_idx_0 + (ndbl - 1.0);
          } else {
            ndbl++;
          }

          if (ndbl >= 0.0) {
            n = (int)ndbl;
          } else {
            n = 0;
          }

          i42 = fit_intv->size[0] * fit_intv->size[1];
          fit_intv->size[0] = 1;
          fit_intv->size[1] = n;
          emxEnsureCapacity_real_T(fit_intv, i42);
          if (n > 0) {
            fit_intv->data[0] = cff0_idx_0;
            if (n > 1) {
              fit_intv->data[n - 1] = apnd;
              nx = (n - 1) / 2;
              for (RDS_tmp = 0; RDS_tmp <= nx - 2; RDS_tmp++) {
                fit_intv->data[1 + RDS_tmp] = cff0_idx_0 + (1.0 + (double)
                  RDS_tmp);
                fit_intv->data[(n - RDS_tmp) - 2] = apnd - (1.0 + (double)
                  RDS_tmp);
              }

              if (nx << 1 == n - 1) {
                fit_intv->data[nx] = (cff0_idx_0 + apnd) / 2.0;
              } else {
                fit_intv->data[nx] = cff0_idx_0 + (double)nx;
                fit_intv->data[nx + 1] = apnd - (double)nx;
              }
            }
          }
        }
      }

      i42 = b_fit_intv->size[0];
      b_fit_intv->size[0] = fit_intv->size[1];
      emxEnsureCapacity_real_T(b_fit_intv, i42);
      loop_ub = fit_intv->size[1];
      for (i42 = 0; i42 < loop_ub; i42++) {
        b_fit_intv->data[i42] = fit_intv->data[i42];
      }

      i42 = varargin_1->size[0];
      varargin_1->size[0] = fit_intv->size[1];
      emxEnsureCapacity_real_T(varargin_1, i42);
      loop_ub = fit_intv->size[1];
      for (i42 = 0; i42 < loop_ub; i42++) {
        varargin_1->data[i42] = RD_data[(int)fit_intv->data[i42] - 1];
      }

      Coder_scd_fitting(b_fit_intv, varargin_1, &cff0_idx_0, &ndbl);
      abc = (b_RDS_tmp - (cff0_idx_0 * ((TC - 50.0) * (TC - 50.0)) + ndbl)) /
        RDS;
      if ((abc > 0.5) && (abc <= 1.5)) {
        *result_well = -3.0;
        cff[0] = cff0_idx_0;
        cff[1] = ndbl;
        *EFC0 = *EFC;
        scd_fit_size[0] = x_size[0];
        loop_ub = x_size[0];
        for (i42 = 0; i42 < loop_ub; i42++) {
          scd_fit_data[i42] = cff0_idx_0 * (x_data[i42] - 50.0) * (x_data[i42] -
            50.0) + ndbl;
        }

        ABSD_size[0] = RD_size[0];
        loop_ub = RD_size[0];
        for (i42 = 0; i42 < loop_ub; i42++) {
          ABSD_data[i42] = RD_data[i42] - scd_fit_data[i42];
        }

        ABSD_orig_size[0] = RD_size[0];
        if (0 <= RD_size[0] - 1) {
          memcpy(&ABSD_orig_data[0], &ABSD_data[0], (unsigned int)(RD_size[0] *
                  (int)sizeof(double)));
        }

        *R_p2 = 1.0;
        i42 = varargin_1->size[0];
        varargin_1->size[0] = fit_intv->size[1];
        emxEnsureCapacity_real_T(varargin_1, i42);
        loop_ub = fit_intv->size[1];
        for (i42 = 0; i42 < loop_ub; i42++) {
          varargin_1->data[i42] = ABSD_data[(int)fit_intv->data[i42] - 1];
        }

        *SRFU = c_mean(varargin_1);
      } else if (abc > 1.5) {
        *result_well = -3.0;
        if (!rtIsNaN(min5_idx[0])) {
          idx = 1;
        } else {
          idx = 0;
          RDS_tmp = 2;
          exitg1 = false;
          while ((!exitg1) && (RDS_tmp < 6)) {
            if (!rtIsNaN(min5_idx[RDS_tmp - 1])) {
              idx = RDS_tmp;
              exitg1 = true;
            } else {
              RDS_tmp++;
            }
          }
        }

        if (idx == 0) {
          apnd = min5_idx[0];
        } else {
          apnd = min5_idx[idx - 1];
          i42 = idx + 1;
          for (RDS_tmp = i42; RDS_tmp < 6; RDS_tmp++) {
            ndbl = min5_idx[RDS_tmp - 1];
            if (apnd < ndbl) {
              apnd = ndbl;
            }
          }
        }

        abc = apnd - 2.0;
        n = RD_size[0];
        if (RD_size[0] <= 2) {
          if (RD_size[0] == 1) {
            cff0_idx_0 = RD_data[0];
          } else if ((RD_data[0] < RD_data[1]) || (rtIsNaN(RD_data[0]) &&
                      (!rtIsNaN(RD_data[1])))) {
            cff0_idx_0 = RD_data[1];
          } else {
            cff0_idx_0 = RD_data[0];
          }
        } else {
          if (!rtIsNaN(RD_data[0])) {
            idx = 1;
          } else {
            idx = 0;
            RDS_tmp = 2;
            exitg1 = false;
            while ((!exitg1) && (RDS_tmp <= RD_size[0])) {
              if (!rtIsNaN(RD_data[RDS_tmp - 1])) {
                idx = RDS_tmp;
                exitg1 = true;
              } else {
                RDS_tmp++;
              }
            }
          }

          if (idx == 0) {
            cff0_idx_0 = RD_data[0];
          } else {
            cff0_idx_0 = RD_data[idx - 1];
            i42 = idx + 1;
            for (RDS_tmp = i42; RDS_tmp <= n; RDS_tmp++) {
              ndbl = RD_data[RDS_tmp - 1];
              if (cff0_idx_0 < ndbl) {
                cff0_idx_0 = ndbl;
              }
            }
          }
        }

        if (RD_data[(int)(apnd - 2.0) - 1] - RD_data[(int)min5_idx[0] - 1] < 0.1
            * (cff0_idx_0 - RD_data[(int)min5_idx[0] - 1])) {
          abc = min5_idx[0];
        }

        cff[0] = 0.0;
        nx = (int)abc;
        cff[1] = RD_data[nx - 1];
        *EFC = 5.0;
        *EFC0 = 5.0;
        scd_fit_size[0] = x_size[0];
        loop_ub = x_size[0];
        for (i42 = 0; i42 < loop_ub; i42++) {
          scd_fit_data[i42] = 0.0 * (x_data[i42] - 50.0) * (x_data[i42] - 50.0)
            + cff[1];
        }

        ABSD_size[0] = RD_size[0];
        loop_ub = RD_size[0];
        for (i42 = 0; i42 < loop_ub; i42++) {
          ABSD_data[i42] = RD_data[i42] - scd_fit_data[i42];
        }

        ABSD_orig_size[0] = RD_size[0];
        if (0 <= RD_size[0] - 1) {
          memcpy(&ABSD_orig_data[0], &ABSD_data[0], (unsigned int)(RD_size[0] *
                  (int)sizeof(double)));
        }

        nx = (signed char)nx;
        loop_ub = nx - 1;
        for (i42 = 0; i42 <= loop_ub; i42++) {
          b_tmp_data[i42] = (signed char)i42;
        }

        for (i42 = 0; i42 < nx; i42++) {
          ABSD_data[b_tmp_data[i42]] = 0.0;
        }

        *R_p2 = 1.0;
      } else {
        *EFC = EFC_temp;

        /* 190227에 추가 */
      }

      /*          DataProcess(:,3)=scd_fit; */
    }
  }

  emxFree_real_T(&b_fit_intv);
  emxFree_real_T(&varargin_1);
  emxFree_real_T(&fit_intv);
}

/* End of code generation (Coder_Section_QuickAmp_v4.c) */
