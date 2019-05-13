/*
 * Coder_Section_QuickAmp_v3.c
 *
 * Code generation for function 'Coder_Section_QuickAmp_v3'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_Section_QuickAmp_v3.h"
#include "Coder_RT_PCR_analyzer_emxutil.h"
#include "combineVectorElements.h"
#include "Coder_scd_fitting.h"
#include "sum.h"
#include "diff.h"
#include "Coder_find_peak_cluster.h"

/* Function Definitions */
void Coder_Section_QuickAmp_v3(const double x_data[], const int x_size[1], const
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
  emxArray_real_T *varargin_1;
  emxArray_real_T *y;
  int i49;
  double abc;
  int i50;
  double rotated_RD_data[100];
  int n;
  int rotated_RD_size[1];
  double b_rotated_RD_data[199];
  double cff0_idx_0;
  double cff0_idx_1;
  boolean_T exitg1;
  int b_RD_size[1];
  double b_RD_data[100];
  emxArray_real_T c_RD_data;
  int c_RD_size[1];
  double b_x_data[198];
  int y_size[1];
  emxArray_real_T y_data;
  double b_y_data[198];
  int b_ABSD_size[1];
  double b_ABSD_data[100];
  emxArray_real_T c_ABSD_data;
  *result_well = 0.0;
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
  emxInit_real_T(&varargin_1, 1);
  emxInit_real_T(&y, 2);
  if ((RDS > 500.0 * AR) && (FB == 0.0)) {
    /*       if (RDS>700*AR) && (FB==0) */
    i49 = (int)HTC - 1;
    abc = RD_data[i49] - RD_data[RDS_tmp_tmp];
    if (abc > 0.0) {
      abc /= RDS;
      if (abc > 0.7) {
        quick_amp = 1;
        *EFC = 5.0;
      } else {
        if (abc > 0.4) {
          abc = RDS / (TC - SFC);
          loop_ub = RD_size[0];
          for (i50 = 0; i50 < loop_ub; i50++) {
            rotated_RD_data[i50] = (RD_data[i50] - abc * (x_data[i50] - SFC)) -
              RD_data[RDS_tmp_tmp];
          }

          if (SFC > TC) {
            i50 = 0;
            n = 0;
          } else {
            i50 = RDS_tmp_tmp;
            n = RDS_tmp;
          }

          loop_ub = n - i50;
          rotated_RD_size[0] = loop_ub;
          for (n = 0; n < loop_ub; n++) {
            b_rotated_RD_data[n] = rotated_RD_data[i50 + n];
          }

          Coder_find_peak_cluster(b_rotated_RD_data, rotated_RD_size, SFC, &abc,
            &cff0_idx_0, &cff0_idx_1);
          if ((cff0_idx_0 - abc > 10.0) && (cff0_idx_1 > 0.3) && (abc < HTC)) {
            quick_amp = 1;
            *EFC = abc - 2.0;
          }
        }
      }
    }

    if (quick_amp == 1) {
      if (HTC > TC) {
        i49 = 0;
        RDS_tmp = 0;
      }

      i50 = varargin_1->size[0];
      loop_ub = (int)(HTC - 1.0);
      varargin_1->size[0] = (loop_ub + RDS_tmp) - i49;
      emxEnsureCapacity_real_T(varargin_1, i50);
      for (i50 = 0; i50 < loop_ub; i50++) {
        varargin_1->data[i50] = rtMinusInf;
      }

      n = RDS_tmp - i49;
      for (i50 = 0; i50 < n; i50++) {
        varargin_1->data[i50 + loop_ub] = RD_data[i49 + i50];
      }

      n = varargin_1->size[0];
      if (varargin_1->size[0] <= 2) {
        if (varargin_1->size[0] == 1) {
          RDS_tmp = 1;
        } else if ((varargin_1->data[0] < varargin_1->data[1]) || (rtIsNaN
                    (varargin_1->data[0]) && (!rtIsNaN(varargin_1->data[1])))) {
          RDS_tmp = 2;
        } else {
          RDS_tmp = 1;
        }
      } else {
        if (!rtIsNaN(varargin_1->data[0])) {
          RDS_tmp = 1;
        } else {
          RDS_tmp = 0;
          loop_ub = 2;
          exitg1 = false;
          while ((!exitg1) && (loop_ub <= varargin_1->size[0])) {
            if (!rtIsNaN(varargin_1->data[loop_ub - 1])) {
              RDS_tmp = loop_ub;
              exitg1 = true;
            } else {
              loop_ub++;
            }
          }
        }

        if (RDS_tmp == 0) {
          RDS_tmp = 1;
        } else {
          abc = varargin_1->data[RDS_tmp - 1];
          i49 = RDS_tmp + 1;
          for (loop_ub = i49; loop_ub <= n; loop_ub++) {
            if (abc < varargin_1->data[loop_ub - 1]) {
              abc = varargin_1->data[loop_ub - 1];
              RDS_tmp = loop_ub;
            }
          }
        }
      }

      if (RDS_tmp_tmp_tmp > RDS_tmp) {
        i49 = 0;
        i50 = 0;
      } else {
        i49 = RDS_tmp_tmp;
        i50 = RDS_tmp;
      }

      n = i50 - i49;
      c_RD_size[0] = n;
      for (i50 = 0; i50 < n; i50++) {
        rotated_RD_data[i50] = RD_data[i49 + i50];
      }

      diff(rotated_RD_data, c_RD_size, b_x_data, rotated_RD_size);
      n = rotated_RD_size[0];
      y_size[0] = (unsigned char)rotated_RD_size[0];
      for (loop_ub = 0; loop_ub < n; loop_ub++) {
        b_y_data[loop_ub] = fabs(b_x_data[loop_ub]);
      }

      y_data.data = &b_y_data[0];
      y_data.size = &y_size[0];
      y_data.allocatedSize = 198;
      y_data.numDimensions = 1;
      y_data.canFreeData = false;
      if (sum(&y_data) / (RD_data[RDS_tmp - 1] - RD_data[RDS_tmp_tmp]) > 1.7) {
        quick_amp = 0;
        *EFC = EFC_temp;
      }

      /*  specific_logic=1; */
    }

    if (quick_amp == 1) {
      if (1.0 > *EFC) {
        loop_ub = 0;
      } else {
        loop_ub = (int)*EFC;
      }

      if (rtIsNaN(*EFC)) {
        i49 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i49);
        y->data[0] = rtNaN;
      } else if (*EFC < 1.0) {
        y->size[0] = 1;
        y->size[1] = 0;
      } else if (rtIsInf(*EFC) && (1.0 == *EFC)) {
        i49 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i49);
        y->data[0] = rtNaN;
      } else {
        i49 = y->size[0] * y->size[1];
        y->size[0] = 1;
        n = (int)floor(*EFC - 1.0);
        y->size[1] = n + 1;
        emxEnsureCapacity_real_T(y, i49);
        for (i49 = 0; i49 <= n; i49++) {
          y->data[i49] = 1.0 + (double)i49;
        }
      }

      i49 = varargin_1->size[0];
      varargin_1->size[0] = y->size[1];
      emxEnsureCapacity_real_T(varargin_1, i49);
      n = y->size[1];
      for (i49 = 0; i49 < n; i49++) {
        varargin_1->data[i49] = y->data[i49];
      }

      b_RD_size[0] = loop_ub;
      if (0 <= loop_ub - 1) {
        memcpy(&b_RD_data[0], &RD_data[0], (unsigned int)(loop_ub * (int)sizeof
                (double)));
      }

      c_RD_data.data = &b_RD_data[0];
      c_RD_data.size = &b_RD_size[0];
      c_RD_data.allocatedSize = 100;
      c_RD_data.numDimensions = 1;
      c_RD_data.canFreeData = false;
      Coder_scd_fitting(varargin_1, &c_RD_data, &cff0_idx_0, &cff0_idx_1);
      abc = (b_RDS_tmp - (cff0_idx_0 * ((TC - 50.0) * (TC - 50.0)) + cff0_idx_1))
        / RDS;
      if ((abc > 0.5) && (abc <= 1.5)) {
        *result_well = -3.0;
        cff[0] = cff0_idx_0;
        cff[1] = cff0_idx_1;
        *EFC0 = *EFC;
        scd_fit_size[0] = x_size[0];
        loop_ub = x_size[0];
        for (i49 = 0; i49 < loop_ub; i49++) {
          scd_fit_data[i49] = cff0_idx_0 * (x_data[i49] - 50.0) * (x_data[i49] -
            50.0) + cff0_idx_1;
        }

        ABSD_size[0] = RD_size[0];
        loop_ub = RD_size[0];
        for (i49 = 0; i49 < loop_ub; i49++) {
          ABSD_data[i49] = RD_data[i49] - scd_fit_data[i49];
        }

        ABSD_orig_size[0] = RD_size[0];
        if (0 <= RD_size[0] - 1) {
          memcpy(&ABSD_orig_data[0], &ABSD_data[0], (unsigned int)(RD_size[0] *
                  (int)sizeof(double)));
        }

        *R_p2 = 1.0;
        if (1.0 > *EFC) {
          loop_ub = 0;
        } else {
          loop_ub = (int)*EFC;
        }

        b_ABSD_size[0] = loop_ub;
        if (0 <= loop_ub - 1) {
          memcpy(&b_ABSD_data[0], &ABSD_data[0], (unsigned int)(loop_ub * (int)
                  sizeof(double)));
        }

        c_ABSD_data.data = &b_ABSD_data[0];
        c_ABSD_data.size = &b_ABSD_size[0];
        c_ABSD_data.allocatedSize = 100;
        c_ABSD_data.numDimensions = 1;
        c_ABSD_data.canFreeData = false;
        *SRFU = combineVectorElements(&c_ABSD_data) / (double)loop_ub;
      } else {
        if (abc > 1.5) {
          *result_well = -3.0;
          cff[0] = 0.0;
          cff[1] = RD_data[2];
          *EFC = 5.0;
          *EFC0 = 5.0;
          scd_fit_size[0] = x_size[0];
          loop_ub = x_size[0];
          for (i49 = 0; i49 < loop_ub; i49++) {
            scd_fit_data[i49] = 0.0 * (x_data[i49] - 50.0) * (x_data[i49] - 50.0)
              + cff[1];
          }

          ABSD_size[0] = RD_size[0];
          loop_ub = RD_size[0];
          for (i49 = 0; i49 < loop_ub; i49++) {
            ABSD_data[i49] = RD_data[i49] - scd_fit_data[i49];
          }

          ABSD_orig_size[0] = RD_size[0];
          if (0 <= RD_size[0] - 1) {
            memcpy(&ABSD_orig_data[0], &ABSD_data[0], (unsigned int)(RD_size[0] *
                    (int)sizeof(double)));
          }

          *R_p2 = 1.0;
          *SRFU = ABSD_data[2];
        }
      }

      /*          DataProcess(:,3)=scd_fit; */
    }
  }

  emxFree_real_T(&y);
  emxFree_real_T(&varargin_1);
}

/* End of code generation (Coder_Section_QuickAmp_v3.c) */
