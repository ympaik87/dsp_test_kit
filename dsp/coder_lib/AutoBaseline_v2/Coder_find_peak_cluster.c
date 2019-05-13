/*
 * Coder_find_peak_cluster.c
 *
 * Code generation for function 'Coder_find_peak_cluster'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_find_peak_cluster.h"
#include "AutoBaseline_v2_emxutil.h"
#include "sum.h"
#include "diff.h"
#include "abs.h"
#include "sort1.h"

/* Function Definitions */
void Coder_find_peak_cluster(double rotated_RD_data[], int rotated_RD_size[1],
  double SC, double *peak_cycle1, double *peak_cycle2, double *height)
{
  emxArray_real_T *set2;
  int n;
  double ndbl;
  int set1_cycle_right;
  double y_data[99];
  double apnd;
  int idx;
  double u0;
  int i13;
  int k;
  boolean_T exitg1;
  double set2_LM_scale;
  int nm1d2;
  double set2_data[199];
  emxArray_real_T *x;
  emxArray_int32_T *iidx;
  int si_data[199];
  emxArray_int32_T *set1;
  int j;
  emxArray_real_T *varargin_1;
  emxArray_real_T *b_set1;
  int i;
  int i14;
  emxArray_int32_T *b_set2;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  double b_ndbl;
  double set2_MR_scale;
  static const signed char iv0[5] = { -2, -1, 0, 1, 2 };

  int b_rotated_RD_size[1];
  double x_data[198];
  int x_size[1];
  int y_size[1];
  emxArray_real_T b_y_data;
  double c_y_data[198];
  int c_rotated_RD_size[1];
  emxArray_real_T d_y_data;
  double u1;
  int d_rotated_RD_size[1];
  emxArray_real_T e_y_data;
  double set2_LM_LSR;
  int e_rotated_RD_size[1];
  emxArray_real_T f_y_data;
  double set2_MR_LSR;
  double b_u0;
  double b_set2_LM_LSR;
  double b_varargin_1[4];
  *peak_cycle1 = 0.0;
  *peak_cycle2 = 0.0;
  *height = 0.0;
  emxInit_real_T(&set2, 2);
  if (SC > 1.0) {
    if (rtIsInf(SC - 1.0) && (SC - 1.0 == 1.0)) {
      n = 1;
      y_data[0] = rtNaN;
    } else if (floor(SC - 1.0) == SC - 1.0) {
      set1_cycle_right = (int)floor(-(1.0 - (SC - 1.0)));
      n = set1_cycle_right + 1;
      for (i13 = 0; i13 <= set1_cycle_right; i13++) {
        y_data[i13] = (SC - 1.0) - (double)i13;
      }
    } else {
      ndbl = floor((1.0 - (SC - 1.0)) / -1.0 + 0.5);
      apnd = (SC - 1.0) + -ndbl;
      u0 = SC - 1.0;
      if (!(u0 > 1.0)) {
        u0 = 1.0;
      }

      if (fabs(1.0 - apnd) < 4.4408920985006262E-16 * u0) {
        ndbl++;
        apnd = 1.0;
      } else if (1.0 - apnd > 0.0) {
        apnd = (SC - 1.0) + -(ndbl - 1.0);
      } else {
        ndbl++;
      }

      n = (int)ndbl;
      if (n > 0) {
        y_data[0] = SC - 1.0;
        if (n > 1) {
          y_data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (k = 0; k <= nm1d2 - 2; k++) {
            y_data[1 + k] = (SC - 1.0) + -(1.0 + (double)k);
            y_data[(n - k) - 2] = apnd - (-(1.0 + (double)k));
          }

          if (nm1d2 << 1 == n - 1) {
            y_data[nm1d2] = ((SC - 1.0) + apnd) / 2.0;
          } else {
            y_data[nm1d2] = (SC - 1.0) + -(double)nm1d2;
            y_data[nm1d2 + 1] = apnd - (-(double)nm1d2);
          }
        }
      }
    }

    i13 = set2->size[0] * set2->size[1];
    set2->size[0] = 1;
    set2->size[1] = n;
    emxEnsureCapacity_real_T(set2, i13);
    for (i13 = 0; i13 < n; i13++) {
      set2->data[i13] = 1.0E-5 * y_data[i13];
    }

    if (rotated_RD_data[0] < rotated_RD_data[1]) {
      nm1d2 = set2->size[1] + rotated_RD_size[0];
      set1_cycle_right = set2->size[1];
      for (i13 = 0; i13 < set1_cycle_right; i13++) {
        set2_data[i13] = -set2->data[i13];
      }

      set1_cycle_right = rotated_RD_size[0];
      for (i13 = 0; i13 < set1_cycle_right; i13++) {
        set2_data[i13 + set2->size[1]] = rotated_RD_data[i13];
      }

      rotated_RD_size[0] = nm1d2;
      if (0 <= nm1d2 - 1) {
        memcpy(&rotated_RD_data[0], &set2_data[0], (unsigned int)(nm1d2 * (int)
                sizeof(double)));
      }
    } else {
      nm1d2 = set2->size[1] + rotated_RD_size[0];
      set1_cycle_right = set2->size[1];
      for (i13 = 0; i13 < set1_cycle_right; i13++) {
        set2_data[i13] = set2->data[i13];
      }

      set1_cycle_right = rotated_RD_size[0];
      for (i13 = 0; i13 < set1_cycle_right; i13++) {
        set2_data[i13 + set2->size[1]] = rotated_RD_data[i13];
      }

      rotated_RD_size[0] = nm1d2;
      if (0 <= nm1d2 - 1) {
        memcpy(&rotated_RD_data[0], &set2_data[0], (unsigned int)(nm1d2 * (int)
                sizeof(double)));
      }
    }
  }

  n = rotated_RD_size[0];
  if (rotated_RD_size[0] <= 2) {
    if (rotated_RD_size[0] == 1) {
      ndbl = rotated_RD_data[0];
    } else if ((rotated_RD_data[0] < rotated_RD_data[1]) || (rtIsNaN
                (rotated_RD_data[0]) && (!rtIsNaN(rotated_RD_data[1])))) {
      ndbl = rotated_RD_data[1];
    } else {
      ndbl = rotated_RD_data[0];
    }
  } else {
    if (!rtIsNaN(rotated_RD_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= rotated_RD_size[0])) {
        if (!rtIsNaN(rotated_RD_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      ndbl = rotated_RD_data[0];
    } else {
      ndbl = rotated_RD_data[idx - 1];
      i13 = idx + 1;
      for (k = i13; k <= n; k++) {
        apnd = rotated_RD_data[k - 1];
        if (ndbl < apnd) {
          ndbl = apnd;
        }
      }
    }
  }

  n = rotated_RD_size[0];
  if (rotated_RD_size[0] <= 2) {
    if (rotated_RD_size[0] == 1) {
      set2_LM_scale = rotated_RD_data[0];
    } else if ((rotated_RD_data[0] > rotated_RD_data[1]) || (rtIsNaN
                (rotated_RD_data[0]) && (!rtIsNaN(rotated_RD_data[1])))) {
      set2_LM_scale = rotated_RD_data[1];
    } else {
      set2_LM_scale = rotated_RD_data[0];
    }
  } else {
    if (!rtIsNaN(rotated_RD_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= rotated_RD_size[0])) {
        if (!rtIsNaN(rotated_RD_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      set2_LM_scale = rotated_RD_data[0];
    } else {
      set2_LM_scale = rotated_RD_data[idx - 1];
      i13 = idx + 1;
      for (k = i13; k <= n; k++) {
        apnd = rotated_RD_data[k - 1];
        if (set2_LM_scale > apnd) {
          set2_LM_scale = apnd;
        }
      }
    }
  }

  ndbl -= set2_LM_scale;
  set1_cycle_right = rotated_RD_size[0];
  for (i13 = 0; i13 < set1_cycle_right; i13++) {
    rotated_RD_data[i13] /= ndbl;
  }

  emxInit_real_T(&x, 1);
  i13 = x->size[0];
  x->size[0] = rotated_RD_size[0];
  emxEnsureCapacity_real_T(x, i13);
  set1_cycle_right = rotated_RD_size[0];
  for (i13 = 0; i13 < set1_cycle_right; i13++) {
    x->data[i13] = rotated_RD_data[i13];
  }

  emxInit_int32_T(&iidx, 1);
  sort(x, iidx);
  i13 = x->size[0];
  x->size[0] = iidx->size[0];
  emxEnsureCapacity_real_T(x, i13);
  set1_cycle_right = iidx->size[0];
  for (i13 = 0; i13 < set1_cycle_right; i13++) {
    x->data[i13] = iidx->data[i13];
  }

  set1_cycle_right = iidx->size[0];
  for (i13 = 0; i13 < set1_cycle_right; i13++) {
    si_data[i13] = iidx->data[i13];
  }

  emxFree_int32_T(&iidx);
  emxInit_int32_T(&set1, 2);
  set2->size[0] = 1;
  set2->size[1] = 0;
  j = 1;
  i13 = set1->size[0] * set1->size[1];
  set1->size[0] = 1;
  set1->size[1] = 1;
  emxEnsureCapacity_int32_T(set1, i13);
  set1->data[0] = (int)x->data[0];
  i13 = x->size[0];
  emxInit_real_T(&varargin_1, 2);
  emxInit_real_T(&b_set1, 2);
  for (i = 0; i <= i13 - 2; i++) {
    if (j == 1) {
      /* min(abs(set1-si(i)),[],2) */
      i14 = b_set1->size[0] * b_set1->size[1];
      b_set1->size[0] = 1;
      b_set1->size[1] = set1->size[1];
      emxEnsureCapacity_real_T(b_set1, i14);
      nm1d2 = (int)x->data[1 + i];
      set1_cycle_right = set1->size[0] * set1->size[1];
      for (i14 = 0; i14 < set1_cycle_right; i14++) {
        b_set1->data[i14] = (double)set1->data[i14] - (double)nm1d2;
      }

      c_abs(b_set1, varargin_1);
      n = varargin_1->size[1];
      if (varargin_1->size[1] <= 2) {
        if (varargin_1->size[1] == 1) {
          ndbl = varargin_1->data[0];
        } else if ((varargin_1->data[0] > varargin_1->data[1]) || (rtIsNaN
                    (varargin_1->data[0]) && (!rtIsNaN(varargin_1->data[1])))) {
          ndbl = varargin_1->data[1];
        } else {
          ndbl = varargin_1->data[0];
        }
      } else {
        if (!rtIsNaN(varargin_1->data[0])) {
          idx = 1;
        } else {
          idx = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= varargin_1->size[1])) {
            if (!rtIsNaN(varargin_1->data[k - 1])) {
              idx = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (idx == 0) {
          ndbl = varargin_1->data[0];
        } else {
          ndbl = varargin_1->data[idx - 1];
          i14 = idx + 1;
          for (k = i14; k <= n; k++) {
            if (ndbl > varargin_1->data[k - 1]) {
              ndbl = varargin_1->data[k - 1];
            }
          }
        }
      }

      if (ndbl <= 3.0) {
        i14 = set1->size[1];
        nm1d2 = set1->size[0] * set1->size[1];
        set1->size[1] = i14 + 1;
        emxEnsureCapacity_int32_T(set1, nm1d2);
        set1->data[i14] = (int)x->data[1 + i];
      } else {
        n = set1->size[1];
        if (set1->size[1] <= 2) {
          if (set1->size[1] == 1) {
            nm1d2 = set1->data[0];
          } else if (set1->data[0] < set1->data[1]) {
            nm1d2 = set1->data[1];
          } else {
            nm1d2 = set1->data[0];
          }
        } else {
          nm1d2 = set1->data[0];
          for (k = 2; k <= n; k++) {
            if (nm1d2 < set1->data[k - 1]) {
              nm1d2 = set1->data[k - 1];
            }
          }
        }

        guard1 = false;
        if ((double)(int)x->data[1 + i] - (double)nm1d2 > 6.0) {
          guard1 = true;
        } else {
          n = set1->size[1];
          if (set1->size[1] <= 2) {
            if (set1->size[1] == 1) {
              nm1d2 = set1->data[0];
            } else if (set1->data[0] > set1->data[1]) {
              nm1d2 = set1->data[1];
            } else {
              nm1d2 = set1->data[0];
            }
          } else {
            nm1d2 = set1->data[0];
            for (k = 2; k <= n; k++) {
              if (nm1d2 > set1->data[k - 1]) {
                nm1d2 = set1->data[k - 1];
              }
            }
          }

          if ((double)nm1d2 - (double)(int)x->data[1 + i] > 6.0) {
            guard1 = true;
          } else {
            i14 = set1->size[1];
            nm1d2 = set1->size[0] * set1->size[1];
            set1->size[1] = i14 + 1;
            emxEnsureCapacity_int32_T(set1, nm1d2);
            set1->data[i14] = (int)x->data[1 + i];
          }
        }

        if (guard1 && (((int)x->data[1 + i] > 2) && ((int)x->data[1 + i] <
              x->size[0] - 1))) {
          i14 = (int)x->data[1 + i] - 4;
          nm1d2 = si_data[i + 1];
          if (!rtIsNaN(rotated_RD_data[nm1d2 - 3])) {
            idx = 1;
          } else {
            idx = 0;
            k = 2;
            exitg1 = false;
            while ((!exitg1) && (k < 6)) {
              if (!rtIsNaN(rotated_RD_data[(k + nm1d2) - 4])) {
                idx = k;
                exitg1 = true;
              } else {
                k++;
              }
            }
          }

          if (idx == 0) {
            nm1d2 = (int)x->data[i + 1] - 3;
            ndbl = rotated_RD_data[nm1d2];
          } else {
            nm1d2 = (int)x->data[i + 1] - 4;
            ndbl = rotated_RD_data[idx + nm1d2];
            nm1d2 = idx + 1;
            for (k = nm1d2; k < 6; k++) {
              if (ndbl > rotated_RD_data[(iv0[k - 1] + i14) + 3]) {
                ndbl = rotated_RD_data[k + i14];
              }
            }
          }

          if (rotated_RD_data[(int)x->data[1 + i] - 1] <= ndbl) {
            i14 = set2->size[0] * set2->size[1];
            set2->size[0] = 1;
            set2->size[1] = 1;
            emxEnsureCapacity_real_T(set2, i14);
            set2->data[0] = (int)x->data[1 + i];
            j = 2;
          }
        }
      }
    } else {
      i14 = b_set1->size[0] * b_set1->size[1];
      b_set1->size[0] = 1;
      b_set1->size[1] = set1->size[1];
      emxEnsureCapacity_real_T(b_set1, i14);
      nm1d2 = (int)x->data[1 + i];
      set1_cycle_right = set1->size[0] * set1->size[1];
      for (i14 = 0; i14 < set1_cycle_right; i14++) {
        b_set1->data[i14] = (double)set1->data[i14] - (double)nm1d2;
      }

      c_abs(b_set1, varargin_1);
      n = varargin_1->size[1];
      if (varargin_1->size[1] <= 2) {
        if (varargin_1->size[1] == 1) {
          ndbl = varargin_1->data[0];
          idx = 1;
        } else if ((varargin_1->data[0] > varargin_1->data[1]) || (rtIsNaN
                    (varargin_1->data[0]) && (!rtIsNaN(varargin_1->data[1])))) {
          ndbl = varargin_1->data[1];
          idx = 2;
        } else {
          ndbl = varargin_1->data[0];
          idx = 1;
        }
      } else {
        if (!rtIsNaN(varargin_1->data[0])) {
          idx = 1;
        } else {
          idx = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= varargin_1->size[1])) {
            if (!rtIsNaN(varargin_1->data[k - 1])) {
              idx = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (idx == 0) {
          ndbl = varargin_1->data[0];
          idx = 1;
        } else {
          ndbl = varargin_1->data[idx - 1];
          i14 = idx + 1;
          for (k = i14; k <= n; k++) {
            if (ndbl > varargin_1->data[k - 1]) {
              ndbl = varargin_1->data[k - 1];
              idx = k;
            }
          }
        }
      }

      i14 = b_set1->size[0] * b_set1->size[1];
      b_set1->size[0] = 1;
      b_set1->size[1] = set2->size[1];
      emxEnsureCapacity_real_T(b_set1, i14);
      nm1d2 = (int)x->data[1 + i];
      set1_cycle_right = set2->size[0] * set2->size[1];
      for (i14 = 0; i14 < set1_cycle_right; i14++) {
        b_set1->data[i14] = set2->data[i14] - (double)nm1d2;
      }

      c_abs(b_set1, varargin_1);
      n = varargin_1->size[1];
      if (varargin_1->size[1] <= 2) {
        if (varargin_1->size[1] == 1) {
          set2_LM_scale = varargin_1->data[0];
          nm1d2 = 1;
        } else if ((varargin_1->data[0] > varargin_1->data[1]) || (rtIsNaN
                    (varargin_1->data[0]) && (!rtIsNaN(varargin_1->data[1])))) {
          set2_LM_scale = varargin_1->data[1];
          nm1d2 = 2;
        } else {
          set2_LM_scale = varargin_1->data[0];
          nm1d2 = 1;
        }
      } else {
        if (!rtIsNaN(varargin_1->data[0])) {
          nm1d2 = 1;
        } else {
          nm1d2 = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= varargin_1->size[1])) {
            if (!rtIsNaN(varargin_1->data[k - 1])) {
              nm1d2 = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (nm1d2 == 0) {
          set2_LM_scale = varargin_1->data[0];
          nm1d2 = 1;
        } else {
          set2_LM_scale = varargin_1->data[nm1d2 - 1];
          i14 = nm1d2 + 1;
          for (k = i14; k <= n; k++) {
            if (set2_LM_scale > varargin_1->data[k - 1]) {
              set2_LM_scale = varargin_1->data[k - 1];
              nm1d2 = k;
            }
          }
        }
      }

      if ((ndbl < set2_LM_scale) || rtIsNaN(set2_LM_scale)) {
        b_ndbl = ndbl;
      } else {
        b_ndbl = set2_LM_scale;
      }

      if (b_ndbl <= 3.0) {
        if (ndbl == set2_LM_scale) {
          if (ndbl == 1.0) {
            i14 = set1->size[1];
            nm1d2 = set1->size[0] * set1->size[1];
            set1->size[1] = i14 + 1;
            emxEnsureCapacity_int32_T(set1, nm1d2);
            set1->data[i14] = (int)x->data[1 + i];
            i14 = set2->size[1];
            nm1d2 = set2->size[0] * set2->size[1];
            set2->size[1] = i14 + 1;
            emxEnsureCapacity_real_T(set2, nm1d2);
            set2->data[i14] = (int)x->data[1 + i];
          } else if (rotated_RD_data[set1->data[idx - 1] - 1] > rotated_RD_data
                     [(int)set2->data[nm1d2 - 1] - 1]) {
            /* Temp�� ������ ������, dRFU/dT�� ����� set�� ���� */
            i14 = set1->size[1];
            nm1d2 = set1->size[0] * set1->size[1];
            set1->size[1] = i14 + 1;
            emxEnsureCapacity_int32_T(set1, nm1d2);
            set1->data[i14] = (int)x->data[1 + i];
          } else {
            i14 = set2->size[1];
            nm1d2 = set2->size[0] * set2->size[1];
            set2->size[1] = i14 + 1;
            emxEnsureCapacity_real_T(set2, nm1d2);
            set2->data[i14] = (int)x->data[1 + i];
          }
        } else if (ndbl < set2_LM_scale) {
          i14 = set1->size[1];
          nm1d2 = set1->size[0] * set1->size[1];
          set1->size[1] = i14 + 1;
          emxEnsureCapacity_int32_T(set1, nm1d2);
          set1->data[i14] = (int)x->data[1 + i];
        } else {
          i14 = set2->size[1];
          nm1d2 = set2->size[0] * set2->size[1];
          set2->size[1] = i14 + 1;
          emxEnsureCapacity_real_T(set2, nm1d2);
          set2->data[i14] = (int)x->data[1 + i];
        }
      }
    }
  }

  emxFree_real_T(&b_set1);
  emxFree_real_T(&varargin_1);
  emxFree_real_T(&x);

  /*   set1 */
  /*   set2 */
  if (set2->size[1] != 0) {
    emxInit_int32_T(&b_set2, 2);
    guard1 = false;
    guard2 = false;
    if (set1->data[0] < (int)set2->data[0]) {
      n = set2->size[1];
      if (set2->size[1] <= 2) {
        if (set2->size[1] == 1) {
          nm1d2 = (int)set2->data[0];
        } else if ((int)set2->data[0] > (int)set2->data[1]) {
          nm1d2 = (int)set2->data[1];
        } else {
          nm1d2 = (int)set2->data[0];
        }
      } else {
        nm1d2 = (int)set2->data[0];
        for (k = 2; k <= n; k++) {
          if (nm1d2 > (int)set2->data[k - 1]) {
            nm1d2 = (int)set2->data[k - 1];
          }
        }
      }

      if (rotated_RD_data[nm1d2 - 1] - rotated_RD_data[(int)set2->data[0] - 1] <
          0.1) {
        guard2 = true;
      } else {
        n = set1->size[1];
        if (set1->size[1] <= 2) {
          if (set1->size[1] == 1) {
            nm1d2 = set1->data[0];
          } else if (set1->data[0] < set1->data[1]) {
            nm1d2 = set1->data[1];
          } else {
            nm1d2 = set1->data[0];
          }
        } else {
          nm1d2 = set1->data[0];
          for (k = 2; k <= n; k++) {
            if (nm1d2 < set1->data[k - 1]) {
              nm1d2 = set1->data[k - 1];
            }
          }
        }

        if ((double)(int)set2->data[0] - (double)nm1d2 <= 3.0) {
          guard2 = true;
        }
      }
    } else {
      /*  set2(1)<set1(1) */
      n = set2->size[1];
      if (set2->size[1] <= 2) {
        if (set2->size[1] == 1) {
          nm1d2 = (int)set2->data[0];
        } else if ((int)set2->data[0] < (int)set2->data[1]) {
          nm1d2 = (int)set2->data[1];
        } else {
          nm1d2 = (int)set2->data[0];
        }
      } else {
        nm1d2 = (int)set2->data[0];
        for (k = 2; k <= n; k++) {
          if (nm1d2 < (int)set2->data[k - 1]) {
            nm1d2 = (int)set2->data[k - 1];
          }
        }
      }

      if (rotated_RD_data[nm1d2 - 1] - rotated_RD_data[(int)set2->data[0] - 1] <
          0.1) {
        guard1 = true;
      } else {
        n = set1->size[1];
        if (set1->size[1] <= 2) {
          if (set1->size[1] == 1) {
            nm1d2 = set1->data[0];
          } else if (set1->data[0] > set1->data[1]) {
            nm1d2 = set1->data[1];
          } else {
            nm1d2 = set1->data[0];
          }
        } else {
          nm1d2 = set1->data[0];
          for (k = 2; k <= n; k++) {
            if (nm1d2 > set1->data[k - 1]) {
              nm1d2 = set1->data[k - 1];
            }
          }
        }

        if ((double)nm1d2 - (double)(int)set2->data[0] <= 3.0) {
          guard1 = true;
        }
      }
    }

    if (guard2) {
      i13 = set1->size[1];
      i14 = b_set2->size[0] * b_set2->size[1];
      b_set2->size[0] = 1;
      b_set2->size[1] = set2->size[1];
      emxEnsureCapacity_int32_T(b_set2, i14);
      set1_cycle_right = set2->size[0] * set2->size[1];
      for (i14 = 0; i14 < set1_cycle_right; i14++) {
        b_set2->data[i14] = (int)set2->data[i14];
      }

      set1_cycle_right = b_set2->size[1];
      i14 = set1->size[0] * set1->size[1];
      set1->size[1] = i13 + set1_cycle_right;
      emxEnsureCapacity_int32_T(set1, i14);
      for (i14 = 0; i14 < set1_cycle_right; i14++) {
        set1->data[i13 + i14] = (int)set2->data[i14];
      }

      set2->size[0] = 1;
      set2->size[1] = 0;
    }

    if (guard1) {
      i13 = set1->size[1];
      i14 = b_set2->size[0] * b_set2->size[1];
      b_set2->size[0] = 1;
      b_set2->size[1] = set2->size[1];
      emxEnsureCapacity_int32_T(b_set2, i14);
      set1_cycle_right = set2->size[0] * set2->size[1];
      for (i14 = 0; i14 < set1_cycle_right; i14++) {
        b_set2->data[i14] = (int)set2->data[i14];
      }

      set1_cycle_right = b_set2->size[1];
      i14 = set1->size[0] * set1->size[1];
      set1->size[1] = i13 + set1_cycle_right;
      emxEnsureCapacity_int32_T(set1, i14);
      for (i14 = 0; i14 < set1_cycle_right; i14++) {
        set1->data[i13 + i14] = (int)set2->data[i14];
      }

      set2->size[0] = 1;
      set2->size[1] = 0;
    }

    emxFree_int32_T(&b_set2);
  }

  /* ------- ���� ���� data ----- */
  /*   sorted_set1=sort(set1) */
  /*   sorted_set2=sort(set2) */
  if (set2->size[1] != 0) {
    n = set1->size[1];
    if (set1->size[1] <= 2) {
      if (set1->size[1] == 1) {
        nm1d2 = set1->data[0];
      } else if (set1->data[0] > set1->data[1]) {
        nm1d2 = set1->data[1];
      } else {
        nm1d2 = set1->data[0];
      }
    } else {
      nm1d2 = set1->data[0];
      for (k = 2; k <= n; k++) {
        if (nm1d2 > set1->data[k - 1]) {
          nm1d2 = set1->data[k - 1];
        }
      }
    }

    n = set1->size[1];
    if (set1->size[1] <= 2) {
      if (set1->size[1] == 1) {
        set1_cycle_right = set1->data[0];
      } else if (set1->data[0] < set1->data[1]) {
        set1_cycle_right = set1->data[1];
      } else {
        set1_cycle_right = set1->data[0];
      }
    } else {
      set1_cycle_right = set1->data[0];
      for (k = 2; k <= n; k++) {
        if (set1_cycle_right < set1->data[k - 1]) {
          set1_cycle_right = set1->data[k - 1];
        }
      }
    }

    n = set2->size[1];
    if (set2->size[1] <= 2) {
      if (set2->size[1] == 1) {
        idx = (int)set2->data[0];
      } else if ((int)set2->data[0] > (int)set2->data[1]) {
        idx = (int)set2->data[1];
      } else {
        idx = (int)set2->data[0];
      }
    } else {
      idx = (int)set2->data[0];
      for (k = 2; k <= n; k++) {
        if (idx > (int)set2->data[k - 1]) {
          idx = (int)set2->data[k - 1];
        }
      }
    }

    n = set2->size[1];
    if (set2->size[1] <= 2) {
      if (set2->size[1] == 1) {
        j = (int)set2->data[0];
      } else if ((int)set2->data[0] < (int)set2->data[1]) {
        j = (int)set2->data[1];
      } else {
        j = (int)set2->data[0];
      }
    } else {
      j = (int)set2->data[0];
      for (k = 2; k <= n; k++) {
        if (j < (int)set2->data[k - 1]) {
          j = (int)set2->data[k - 1];
        }
      }
    }

    ndbl = rotated_RD_data[nm1d2 - 1] - rotated_RD_data[set1->data[0] - 1];
    apnd = rotated_RD_data[set1_cycle_right - 1] - rotated_RD_data[set1->data[0]
      - 1];
    set2_LM_scale = rotated_RD_data[idx - 1] - rotated_RD_data[(int)set2->data[0]
      - 1];
    set2_MR_scale = rotated_RD_data[j - 1] - rotated_RD_data[(int)set2->data[0]
      - 1];
    if (nm1d2 > set1->data[0]) {
      i13 = 0;
      i14 = 0;
    } else {
      i13 = nm1d2 - 1;
      i14 = set1->data[0];
    }

    nm1d2 = i14 - i13;
    b_rotated_RD_size[0] = nm1d2;
    for (i14 = 0; i14 < nm1d2; i14++) {
      set2_data[i14] = rotated_RD_data[i13 + i14];
    }

    diff(set2_data, b_rotated_RD_size, x_data, x_size);
    nm1d2 = x_size[0];
    y_size[0] = (unsigned char)x_size[0];
    for (k = 0; k < nm1d2; k++) {
      c_y_data[k] = fabs(x_data[k]);
    }

    b_y_data.data = &c_y_data[0];
    b_y_data.size = &y_size[0];
    b_y_data.allocatedSize = 198;
    b_y_data.numDimensions = 1;
    b_y_data.canFreeData = false;
    u0 = sum(&b_y_data) / ndbl;
    if (set1->data[0] > set1_cycle_right) {
      i13 = 0;
      set1_cycle_right = 0;
    } else {
      i13 = set1->data[0] - 1;
    }

    nm1d2 = set1_cycle_right - i13;
    c_rotated_RD_size[0] = nm1d2;
    for (i14 = 0; i14 < nm1d2; i14++) {
      set2_data[i14] = rotated_RD_data[i13 + i14];
    }

    diff(set2_data, c_rotated_RD_size, x_data, x_size);
    nm1d2 = x_size[0];
    y_size[0] = (unsigned char)x_size[0];
    for (k = 0; k < nm1d2; k++) {
      c_y_data[k] = fabs(x_data[k]);
    }

    d_y_data.data = &c_y_data[0];
    d_y_data.size = &y_size[0];
    d_y_data.allocatedSize = 198;
    d_y_data.numDimensions = 1;
    d_y_data.canFreeData = false;
    u1 = sum(&d_y_data) / apnd;
    if (idx > (int)set2->data[0]) {
      i13 = 0;
      i14 = 0;
    } else {
      i13 = idx - 1;
      i14 = (int)set2->data[0];
    }

    nm1d2 = i14 - i13;
    d_rotated_RD_size[0] = nm1d2;
    for (i14 = 0; i14 < nm1d2; i14++) {
      set2_data[i14] = rotated_RD_data[i13 + i14];
    }

    diff(set2_data, d_rotated_RD_size, x_data, x_size);
    nm1d2 = x_size[0];
    y_size[0] = (unsigned char)x_size[0];
    for (k = 0; k < nm1d2; k++) {
      c_y_data[k] = fabs(x_data[k]);
    }

    e_y_data.data = &c_y_data[0];
    e_y_data.size = &y_size[0];
    e_y_data.allocatedSize = 198;
    e_y_data.numDimensions = 1;
    e_y_data.canFreeData = false;
    set2_LM_LSR = sum(&e_y_data) / set2_LM_scale;
    if ((int)set2->data[0] > j) {
      i13 = 0;
      j = 0;
    } else {
      i13 = (int)set2->data[0] - 1;
    }

    nm1d2 = j - i13;
    e_rotated_RD_size[0] = nm1d2;
    for (i14 = 0; i14 < nm1d2; i14++) {
      set2_data[i14] = rotated_RD_data[i13 + i14];
    }

    diff(set2_data, e_rotated_RD_size, x_data, x_size);
    nm1d2 = x_size[0];
    y_size[0] = (unsigned char)x_size[0];
    for (k = 0; k < nm1d2; k++) {
      c_y_data[k] = fabs(x_data[k]);
    }

    f_y_data.data = &c_y_data[0];
    f_y_data.size = &y_size[0];
    f_y_data.allocatedSize = 198;
    f_y_data.numDimensions = 1;
    f_y_data.canFreeData = false;
    set2_MR_LSR = sum(&f_y_data) / set2_MR_scale;
    if ((u0 > u1) || rtIsNaN(u1)) {
      b_u0 = u0;
    } else {
      b_u0 = u1;
    }

    if (b_u0 < 2.0) {
      if ((set2_LM_LSR > set2_MR_LSR) || rtIsNaN(set2_MR_LSR)) {
        b_set2_LM_LSR = set2_LM_LSR;
      } else {
        b_set2_LM_LSR = set2_MR_LSR;
      }

      if (b_set2_LM_LSR < 2.0) {
        b_varargin_1[0] = ndbl;
        b_varargin_1[1] = apnd;
        b_varargin_1[2] = set2_LM_scale;
        b_varargin_1[3] = set2_MR_scale;
        if (!rtIsNaN(ndbl)) {
          idx = 1;
        } else {
          idx = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k < 5)) {
            if (!rtIsNaN(b_varargin_1[k - 1])) {
              idx = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (idx == 0) {
          *height = ndbl;
        } else {
          *height = b_varargin_1[idx - 1];
          i13 = idx + 1;
          for (k = i13; k < 5; k++) {
            apnd = b_varargin_1[k - 1];
            if (*height > apnd) {
              *height = apnd;
            }
          }
        }

        nm1d2 = set1->size[1];
        set1_cycle_right = set2->size[1];
        if (nm1d2 < set1_cycle_right) {
          set1_cycle_right = nm1d2;
        }

        if (set1_cycle_right > 5) {
          if (set1->data[0] < (int)set2->data[0]) {
            *peak_cycle1 = set1->data[0];
          } else {
            *peak_cycle1 = (int)set2->data[0];
          }

          if (set1->data[0] > (int)set2->data[0]) {
            *peak_cycle2 = set1->data[0];
          } else {
            *peak_cycle2 = (int)set2->data[0];
          }
        }
      }
    }
  }

  emxFree_real_T(&set2);
  emxFree_int32_T(&set1);
}

/* End of code generation (Coder_find_peak_cluster.c) */
