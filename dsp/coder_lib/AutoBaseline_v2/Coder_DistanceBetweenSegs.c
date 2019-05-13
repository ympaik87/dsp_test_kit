/*
 * Coder_DistanceBetweenSegs.c
 *
 * Code generation for function 'Coder_DistanceBetweenSegs'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_DistanceBetweenSegs.h"
#include "AutoBaseline_v2_emxutil.h"

/* Function Definitions */
double Coder_DistanceBetweenSegs(const double RD_data[], const int RD_size[1],
  double SC, double EC)
{
  int loop_ub;
  int i7;
  emxArray_real_T *y;
  double RD_new_data[100];
  double slope_tmp;
  int slope_tmp_tmp;
  double b_slope_tmp;
  double slope;
  double ndbl;
  double apnd;
  double cdiff;
  double u0;
  emxArray_real_T *b_y;
  emxArray_real_T *c_y;
  emxArray_real_T *d_y;
  int nm1d2;
  int k;
  double segment_data[100];
  boolean_T exitg1;
  int min_cycle;
  loop_ub = RD_size[0];
  for (i7 = 0; i7 < loop_ub; i7++) {
    RD_new_data[i7] = RD_data[i7] - RD_data[(int)SC - 1];
  }

  emxInit_real_T(&y, 2);
  slope_tmp = EC - SC;
  slope_tmp_tmp = (int)EC;
  b_slope_tmp = RD_new_data[slope_tmp_tmp - 1];
  slope = b_slope_tmp / slope_tmp;
  if (rtIsNaN(EC)) {
    i7 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i7);
    y->data[0] = rtNaN;
  } else if (EC < SC) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else if (SC == SC) {
    i7 = y->size[0] * y->size[1];
    y->size[0] = 1;
    loop_ub = (int)floor(slope_tmp);
    y->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(y, i7);
    for (i7 = 0; i7 <= loop_ub; i7++) {
      y->data[i7] = SC + (double)i7;
    }
  } else {
    ndbl = floor(slope_tmp + 0.5);
    apnd = SC + ndbl;
    cdiff = apnd - EC;
    u0 = (int)SC;
    if ((!(u0 > EC)) && (!rtIsNaN(EC))) {
      u0 = EC;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * u0) {
      ndbl++;
      apnd = EC;
    } else if (cdiff > 0.0) {
      apnd = SC + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      loop_ub = (int)ndbl;
    } else {
      loop_ub = 0;
    }

    i7 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = loop_ub;
    emxEnsureCapacity_real_T(y, i7);
    if (loop_ub > 0) {
      y->data[0] = SC;
      if (loop_ub > 1) {
        y->data[loop_ub - 1] = apnd;
        nm1d2 = (loop_ub - 1) / 2;
        for (k = 0; k <= nm1d2 - 2; k++) {
          y->data[1 + k] = SC + (1.0 + (double)k);
          y->data[(loop_ub - k) - 2] = apnd - (1.0 + (double)k);
        }

        if (nm1d2 << 1 == loop_ub - 1) {
          y->data[nm1d2] = (SC + apnd) / 2.0;
        } else {
          y->data[nm1d2] = SC + (double)nm1d2;
          y->data[nm1d2 + 1] = apnd - (double)nm1d2;
        }
      }
    }
  }

  emxInit_real_T(&b_y, 2);
  if (rtIsNaN(EC)) {
    i7 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = 1;
    emxEnsureCapacity_real_T(b_y, i7);
    b_y->data[0] = rtNaN;
  } else if (EC < SC) {
    b_y->size[0] = 1;
    b_y->size[1] = 0;
  } else if (SC == SC) {
    i7 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = (int)floor(EC - SC) + 1;
    emxEnsureCapacity_real_T(b_y, i7);
    loop_ub = (int)floor(EC - SC);
    for (i7 = 0; i7 <= loop_ub; i7++) {
      b_y->data[i7] = SC + (double)i7;
    }
  } else {
    ndbl = floor((EC - SC) + 0.5);
    apnd = SC + ndbl;
    cdiff = apnd - EC;
    u0 = (int)SC;
    if ((!(u0 > EC)) && (!rtIsNaN(EC))) {
      u0 = EC;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * u0) {
      ndbl++;
      apnd = EC;
    } else if (cdiff > 0.0) {
      apnd = SC + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      loop_ub = (int)ndbl;
    } else {
      loop_ub = 0;
    }

    i7 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = loop_ub;
    emxEnsureCapacity_real_T(b_y, i7);
    if (loop_ub > 0) {
      b_y->data[0] = SC;
      if (loop_ub > 1) {
        b_y->data[loop_ub - 1] = apnd;
        nm1d2 = (loop_ub - 1) / 2;
        for (k = 0; k <= nm1d2 - 2; k++) {
          b_y->data[1 + k] = SC + (1.0 + (double)k);
          b_y->data[(loop_ub - k) - 2] = apnd - (1.0 + (double)k);
        }

        if (nm1d2 << 1 == loop_ub - 1) {
          b_y->data[nm1d2] = (SC + apnd) / 2.0;
        } else {
          b_y->data[nm1d2] = SC + (double)nm1d2;
          b_y->data[nm1d2 + 1] = apnd - (double)nm1d2;
        }
      }
    }
  }

  emxInit_real_T(&c_y, 1);
  slope_tmp = (b_slope_tmp - RD_new_data[(int)SC - 1]) / slope_tmp;
  i7 = c_y->size[0];
  c_y->size[0] = y->size[1];
  emxEnsureCapacity_real_T(c_y, i7);
  loop_ub = y->size[1];
  for (i7 = 0; i7 < loop_ub; i7++) {
    c_y->data[i7] = y->data[i7];
  }

  emxFree_real_T(&y);
  emxInit_real_T(&d_y, 1);
  i7 = d_y->size[0];
  d_y->size[0] = b_y->size[1];
  emxEnsureCapacity_real_T(d_y, i7);
  loop_ub = b_y->size[1];
  for (i7 = 0; i7 < loop_ub; i7++) {
    d_y->data[i7] = b_y->data[i7];
  }

  emxFree_real_T(&b_y);
  loop_ub = c_y->size[0];
  for (i7 = 0; i7 < loop_ub; i7++) {
    segment_data[i7] = slope_tmp * (d_y->data[i7] - SC) + RD_new_data[(int)SC -
      1];
  }

  emxFree_real_T(&d_y);
  if (SC > EC) {
    i7 = 0;
    k = 0;
  } else {
    i7 = (int)SC - 1;
    k = slope_tmp_tmp;
  }

  nm1d2 = c_y->size[0];
  loop_ub = k - i7;
  c_y->size[0] = loop_ub;
  emxEnsureCapacity_real_T(c_y, nm1d2);
  for (k = 0; k < loop_ub; k++) {
    c_y->data[k] = RD_new_data[i7 + k] - segment_data[k];
  }

  loop_ub = c_y->size[0];
  if (c_y->size[0] <= 2) {
    if (c_y->size[0] == 1) {
      nm1d2 = 1;
    } else if ((c_y->data[0] > c_y->data[1]) || (rtIsNaN(c_y->data[0]) &&
                (!rtIsNaN(c_y->data[1])))) {
      nm1d2 = 2;
    } else {
      nm1d2 = 1;
    }
  } else {
    if (!rtIsNaN(c_y->data[0])) {
      nm1d2 = 1;
    } else {
      nm1d2 = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= c_y->size[0])) {
        if (!rtIsNaN(c_y->data[k - 1])) {
          nm1d2 = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (nm1d2 == 0) {
      nm1d2 = 1;
    } else {
      slope_tmp = c_y->data[nm1d2 - 1];
      i7 = nm1d2 + 1;
      for (k = i7; k <= loop_ub; k++) {
        if (slope_tmp > c_y->data[k - 1]) {
          slope_tmp = c_y->data[k - 1];
          nm1d2 = k;
        }
      }
    }
  }

  min_cycle = (nm1d2 + (int)SC) - 1;
  if (SC > EC) {
    i7 = 0;
    slope_tmp_tmp = 0;
  } else {
    i7 = (int)SC - 1;
  }

  k = c_y->size[0];
  loop_ub = slope_tmp_tmp - i7;
  c_y->size[0] = loop_ub;
  emxEnsureCapacity_real_T(c_y, k);
  for (k = 0; k < loop_ub; k++) {
    c_y->data[k] = RD_new_data[i7 + k] - segment_data[k];
  }

  loop_ub = c_y->size[0];
  if (c_y->size[0] <= 2) {
    if (c_y->size[0] == 1) {
      nm1d2 = 1;
    } else if ((c_y->data[0] < c_y->data[1]) || (rtIsNaN(c_y->data[0]) &&
                (!rtIsNaN(c_y->data[1])))) {
      nm1d2 = 2;
    } else {
      nm1d2 = 1;
    }
  } else {
    if (!rtIsNaN(c_y->data[0])) {
      nm1d2 = 1;
    } else {
      nm1d2 = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= c_y->size[0])) {
        if (!rtIsNaN(c_y->data[k - 1])) {
          nm1d2 = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (nm1d2 == 0) {
      nm1d2 = 1;
    } else {
      slope_tmp = c_y->data[nm1d2 - 1];
      i7 = nm1d2 + 1;
      for (k = i7; k <= loop_ub; k++) {
        if (slope_tmp < c_y->data[k - 1]) {
          slope_tmp = c_y->data[k - 1];
          nm1d2 = k;
        }
      }
    }
  }

  emxFree_real_T(&c_y);
  nm1d2 = (nm1d2 + (int)SC) - 1;
  return fabs((RD_new_data[nm1d2 - 1] - slope * (double)nm1d2) -
              (RD_new_data[min_cycle - 1] - slope * (double)min_cycle)) / sqrt
    (slope * slope + 1.0);
}

/* End of code generation (Coder_DistanceBetweenSegs.c) */
