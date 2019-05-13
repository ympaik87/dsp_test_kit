/*
 * Coder_baseline.c
 *
 * Code generation for function 'Coder_baseline'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v1.h"
#include "Coder_baseline.h"
#include "AutoBaseline_v1_emxutil.h"
#include "Coder_linear_fitting.h"
#include "power.h"
#include "Coder_scd_fitting.h"

/* Function Definitions */
void Coder_baseline(const emxArray_real_T *xdata, const emxArray_real_T *xdata2,
                    const double RD_data[], double joint_pt, double LinearOrNot,
                    double TC, double scd_fit_data[], int scd_fit_size[1],
                    double cff[2])
{
  int scd_fit_size_tmp;
  emxArray_real_T *y;
  emxArray_real_T *RD;
  emxArray_real_T *b_cff;
  int i17;
  int loop_ub;
  double cff2_idx_0;
  double cff2_idx_1;
  int i18;
  double ndbl;
  double apnd;
  double cdiff;
  int nm1d2;
  double u0;
  double u1;
  signed char tmp_data[100];
  int n;
  scd_fit_size_tmp = (int)TC;
  scd_fit_size[0] = scd_fit_size_tmp;
  if (0 <= scd_fit_size_tmp - 1) {
    memset(&scd_fit_data[0], 0, (unsigned int)(scd_fit_size_tmp * (int)sizeof
            (double)));
  }

  emxInit_real_T(&y, 2);
  emxInit_real_T(&RD, 1);
  emxInit_real_T(&b_cff, 1);
  if (LinearOrNot == 2.0) {
    i17 = RD->size[0];
    RD->size[0] = xdata->size[0];
    emxEnsureCapacity_real_T(RD, i17);
    loop_ub = xdata->size[0];
    for (i17 = 0; i17 < loop_ub; i17++) {
      RD->data[i17] = RD_data[(int)xdata->data[i17] - 1];
    }

    Coder_linear_fitting(xdata, RD, &cff[0], &cff[1]);
    i17 = RD->size[0];
    RD->size[0] = xdata2->size[0];
    emxEnsureCapacity_real_T(RD, i17);
    loop_ub = xdata2->size[0];
    for (i17 = 0; i17 < loop_ub; i17++) {
      RD->data[i17] = RD_data[(int)xdata2->data[i17] - 1];
    }

    Coder_linear_fitting(xdata2, RD, &cff2_idx_0, &cff2_idx_1);
    if (joint_pt > TC) {
      i17 = 1;
      scd_fit_size_tmp = 0;
    } else {
      i17 = (int)joint_pt;
    }

    if (rtIsNaN(joint_pt) || rtIsNaN(TC)) {
      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i18);
      y->data[0] = rtNaN;
    } else if (TC < joint_pt) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else if ((rtIsInf(joint_pt) || rtIsInf(TC)) && (joint_pt == TC)) {
      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i18);
      y->data[0] = rtNaN;
    } else if (floor(joint_pt) == joint_pt) {
      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = (int)floor(TC - joint_pt) + 1;
      emxEnsureCapacity_real_T(y, i18);
      loop_ub = (int)floor(TC - joint_pt);
      for (i18 = 0; i18 <= loop_ub; i18++) {
        y->data[i18] = joint_pt + (double)i18;
      }
    } else {
      ndbl = floor((TC - joint_pt) + 0.5);
      apnd = joint_pt + ndbl;
      cdiff = apnd - TC;
      u0 = fabs(joint_pt);
      u1 = fabs(TC);
      if ((u0 > u1) || rtIsNaN(u1)) {
        u1 = u0;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
        ndbl++;
        apnd = TC;
      } else if (cdiff > 0.0) {
        apnd = joint_pt + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = n;
      emxEnsureCapacity_real_T(y, i18);
      if (n > 0) {
        y->data[0] = joint_pt;
        if (n > 1) {
          y->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (loop_ub = 0; loop_ub <= nm1d2 - 2; loop_ub++) {
            y->data[1 + loop_ub] = joint_pt + (1.0 + (double)loop_ub);
            y->data[(n - loop_ub) - 2] = apnd - (1.0 + (double)loop_ub);
          }

          if (nm1d2 << 1 == n - 1) {
            y->data[nm1d2] = (joint_pt + apnd) / 2.0;
          } else {
            y->data[nm1d2] = joint_pt + (double)nm1d2;
            y->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }

    nm1d2 = (signed char)scd_fit_size_tmp - (signed char)i17;
    for (i18 = 0; i18 <= nm1d2; i18++) {
      tmp_data[i18] = (signed char)((signed char)((signed char)i17 + (signed
        char)i18) - 1);
    }

    i17 = b_cff->size[0];
    b_cff->size[0] = y->size[1];
    emxEnsureCapacity_real_T(b_cff, i17);
    loop_ub = y->size[1];
    for (i17 = 0; i17 < loop_ub; i17++) {
      b_cff->data[i17] = cff[0] * y->data[i17] + cff[1];
    }

    loop_ub = nm1d2 + 1;
    for (i17 = 0; i17 < loop_ub; i17++) {
      scd_fit_data[tmp_data[i17]] = b_cff->data[i17];
    }

    if (1.0 > joint_pt - 1.0) {
      i17 = 0;
    } else {
      i17 = (int)(joint_pt - 1.0);
    }

    if (rtIsNaN(joint_pt - 1.0)) {
      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i18);
      y->data[0] = rtNaN;
    } else if (joint_pt - 1.0 < 1.0) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else if (rtIsInf(joint_pt - 1.0) && (1.0 == joint_pt - 1.0)) {
      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i18);
      y->data[0] = rtNaN;
    } else {
      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = (int)floor((joint_pt - 1.0) - 1.0) + 1;
      emxEnsureCapacity_real_T(y, i18);
      loop_ub = (int)floor((joint_pt - 1.0) - 1.0);
      for (i18 = 0; i18 <= loop_ub; i18++) {
        y->data[i18] = 1.0 + (double)i18;
      }
    }

    loop_ub = (signed char)i17 - 1;
    for (i18 = 0; i18 <= loop_ub; i18++) {
      tmp_data[i18] = (signed char)i18;
    }

    i18 = b_cff->size[0];
    b_cff->size[0] = y->size[1];
    emxEnsureCapacity_real_T(b_cff, i18);
    loop_ub = y->size[1];
    for (i18 = 0; i18 < loop_ub; i18++) {
      b_cff->data[i18] = cff2_idx_0 * y->data[i18] + cff2_idx_1;
    }

    loop_ub = (signed char)i17;
    for (i17 = 0; i17 < loop_ub; i17++) {
      scd_fit_data[tmp_data[i17]] = b_cff->data[i17];
    }
  } else {
    i17 = RD->size[0];
    RD->size[0] = xdata->size[0];
    emxEnsureCapacity_real_T(RD, i17);
    loop_ub = xdata->size[0];
    for (i17 = 0; i17 < loop_ub; i17++) {
      RD->data[i17] = RD_data[(int)xdata->data[i17] - 1];
    }

    Coder_scd_fitting(xdata, RD, &cff[0], &cff[1]);
    i17 = RD->size[0];
    RD->size[0] = xdata2->size[0];
    emxEnsureCapacity_real_T(RD, i17);
    loop_ub = xdata2->size[0];
    for (i17 = 0; i17 < loop_ub; i17++) {
      RD->data[i17] = RD_data[(int)xdata2->data[i17] - 1];
    }

    Coder_scd_fitting(xdata2, RD, &cff2_idx_0, &cff2_idx_1);
    if (joint_pt > TC) {
      i17 = 1;
      scd_fit_size_tmp = 0;
    } else {
      i17 = (int)joint_pt;
    }

    if (rtIsNaN(joint_pt) || rtIsNaN(TC)) {
      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i18);
      y->data[0] = rtNaN;
    } else if (TC < joint_pt) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else if ((rtIsInf(joint_pt) || rtIsInf(TC)) && (joint_pt == TC)) {
      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i18);
      y->data[0] = rtNaN;
    } else if (floor(joint_pt) == joint_pt) {
      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      loop_ub = (int)floor(TC - joint_pt);
      y->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(y, i18);
      for (i18 = 0; i18 <= loop_ub; i18++) {
        y->data[i18] = joint_pt + (double)i18;
      }
    } else {
      ndbl = floor((TC - joint_pt) + 0.5);
      apnd = joint_pt + ndbl;
      cdiff = apnd - TC;
      u0 = fabs(joint_pt);
      u1 = fabs(TC);
      if ((u0 > u1) || rtIsNaN(u1)) {
        u1 = u0;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
        ndbl++;
        apnd = TC;
      } else if (cdiff > 0.0) {
        apnd = joint_pt + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = n;
      emxEnsureCapacity_real_T(y, i18);
      if (n > 0) {
        y->data[0] = joint_pt;
        if (n > 1) {
          y->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (loop_ub = 0; loop_ub <= nm1d2 - 2; loop_ub++) {
            y->data[1 + loop_ub] = joint_pt + (1.0 + (double)loop_ub);
            y->data[(n - loop_ub) - 2] = apnd - (1.0 + (double)loop_ub);
          }

          if (nm1d2 << 1 == n - 1) {
            y->data[nm1d2] = (joint_pt + apnd) / 2.0;
          } else {
            y->data[nm1d2] = joint_pt + (double)nm1d2;
            y->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }

    nm1d2 = (signed char)scd_fit_size_tmp - (signed char)i17;
    for (i18 = 0; i18 <= nm1d2; i18++) {
      tmp_data[i18] = (signed char)((signed char)((signed char)i17 + (signed
        char)i18) - 1);
    }

    i17 = RD->size[0];
    RD->size[0] = y->size[1];
    emxEnsureCapacity_real_T(RD, i17);
    loop_ub = y->size[1];
    for (i17 = 0; i17 < loop_ub; i17++) {
      RD->data[i17] = y->data[i17] - 50.0;
    }

    power(RD, b_cff);
    loop_ub = nm1d2 + 1;
    for (i17 = 0; i17 < loop_ub; i17++) {
      scd_fit_data[tmp_data[i17]] = cff[0] * b_cff->data[i17] + cff[1];
    }

    if (1.0 > joint_pt - 1.0) {
      i17 = 0;
    } else {
      i17 = (int)(joint_pt - 1.0);
    }

    if (rtIsNaN(joint_pt - 1.0)) {
      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i18);
      y->data[0] = rtNaN;
    } else if (joint_pt - 1.0 < 1.0) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else if (rtIsInf(joint_pt - 1.0) && (1.0 == joint_pt - 1.0)) {
      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, i18);
      y->data[0] = rtNaN;
    } else {
      i18 = y->size[0] * y->size[1];
      y->size[0] = 1;
      loop_ub = (int)floor((joint_pt - 1.0) - 1.0);
      y->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(y, i18);
      for (i18 = 0; i18 <= loop_ub; i18++) {
        y->data[i18] = 1.0 + (double)i18;
      }
    }

    loop_ub = (signed char)i17 - 1;
    for (i18 = 0; i18 <= loop_ub; i18++) {
      tmp_data[i18] = (signed char)i18;
    }

    i18 = RD->size[0];
    RD->size[0] = y->size[1];
    emxEnsureCapacity_real_T(RD, i18);
    loop_ub = y->size[1];
    for (i18 = 0; i18 < loop_ub; i18++) {
      RD->data[i18] = y->data[i18] - 50.0;
    }

    power(RD, b_cff);
    loop_ub = (signed char)i17;
    for (i17 = 0; i17 < loop_ub; i17++) {
      scd_fit_data[tmp_data[i17]] = cff2_idx_0 * b_cff->data[i17] + cff2_idx_1;
    }
  }

  emxFree_real_T(&b_cff);
  emxFree_real_T(&RD);
  emxFree_real_T(&y);
}

/* End of code generation (Coder_baseline.c) */
