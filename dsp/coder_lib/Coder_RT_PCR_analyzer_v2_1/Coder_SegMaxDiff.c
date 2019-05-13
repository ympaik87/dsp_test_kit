/*
 * Coder_SegMaxDiff.c
 *
 * Code generation for function 'Coder_SegMaxDiff'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_SegMaxDiff.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"

/* Function Definitions */
void Coder_SegMaxDiff(const double RD_data[], double SC, double EC, double
                      *max_val, double *max_cycle)
{
  emxArray_real_T *y;
  int i14;
  double ndbl;
  double apnd;
  double cdiff;
  int nm1d2;
  double u0;
  double u1;
  emxArray_real_T *varargin_1;
  int n;
  int k;
  boolean_T exitg1;
  emxInit_real_T(&y, 2);
  if (rtIsNaN(SC) || rtIsNaN(EC)) {
    i14 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i14);
    y->data[0] = rtNaN;
  } else if (EC < SC) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else if ((rtIsInf(SC) || rtIsInf(EC)) && (SC == EC)) {
    i14 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i14);
    y->data[0] = rtNaN;
  } else if (floor(SC) == SC) {
    i14 = y->size[0] * y->size[1];
    y->size[0] = 1;
    nm1d2 = (int)floor(EC - SC);
    y->size[1] = nm1d2 + 1;
    emxEnsureCapacity_real_T(y, i14);
    for (i14 = 0; i14 <= nm1d2; i14++) {
      y->data[i14] = SC + (double)i14;
    }
  } else {
    ndbl = floor((EC - SC) + 0.5);
    apnd = SC + ndbl;
    cdiff = apnd - EC;
    u0 = fabs(SC);
    u1 = fabs(EC);
    if ((u0 > u1) || rtIsNaN(u1)) {
      u1 = u0;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
      ndbl++;
      apnd = EC;
    } else if (cdiff > 0.0) {
      apnd = SC + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }

    i14 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n;
    emxEnsureCapacity_real_T(y, i14);
    if (n > 0) {
      y->data[0] = SC;
      if (n > 1) {
        y->data[n - 1] = apnd;
        nm1d2 = (n - 1) / 2;
        for (k = 0; k <= nm1d2 - 2; k++) {
          y->data[1 + k] = SC + (1.0 + (double)k);
          y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
        }

        if (nm1d2 << 1 == n - 1) {
          y->data[nm1d2] = (SC + apnd) / 2.0;
        } else {
          y->data[nm1d2] = SC + (double)nm1d2;
          y->data[nm1d2 + 1] = apnd - (double)nm1d2;
        }
      }
    }
  }

  ndbl = RD_data[(int)SC - 1];
  apnd = (RD_data[(int)EC - 1] - ndbl) / (EC - SC);
  if (SC > EC) {
    i14 = 0;
  } else {
    i14 = (int)SC - 1;
  }

  emxInit_real_T(&varargin_1, 1);
  n = varargin_1->size[0];
  varargin_1->size[0] = y->size[1];
  emxEnsureCapacity_real_T(varargin_1, n);
  nm1d2 = y->size[1];
  for (n = 0; n < nm1d2; n++) {
    varargin_1->data[n] = (apnd * (y->data[n] - SC) + ndbl) - RD_data[i14 + n];
  }

  emxFree_real_T(&y);
  n = varargin_1->size[0];
  if (varargin_1->size[0] <= 2) {
    if (varargin_1->size[0] == 1) {
      *max_val = varargin_1->data[0];
      nm1d2 = 1;
    } else if ((varargin_1->data[0] < varargin_1->data[1]) || (rtIsNaN
                (varargin_1->data[0]) && (!rtIsNaN(varargin_1->data[1])))) {
      *max_val = varargin_1->data[1];
      nm1d2 = 2;
    } else {
      *max_val = varargin_1->data[0];
      nm1d2 = 1;
    }
  } else {
    if (!rtIsNaN(varargin_1->data[0])) {
      nm1d2 = 1;
    } else {
      nm1d2 = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= varargin_1->size[0])) {
        if (!rtIsNaN(varargin_1->data[k - 1])) {
          nm1d2 = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (nm1d2 == 0) {
      *max_val = varargin_1->data[0];
      nm1d2 = 1;
    } else {
      *max_val = varargin_1->data[nm1d2 - 1];
      i14 = nm1d2 + 1;
      for (k = i14; k <= n; k++) {
        if (*max_val < varargin_1->data[k - 1]) {
          *max_val = varargin_1->data[k - 1];
          nm1d2 = k;
        }
      }
    }
  }

  emxFree_real_T(&varargin_1);
  *max_cycle = (SC + (double)nm1d2) - 1.0;
}

/* End of code generation (Coder_SegMaxDiff.c) */
