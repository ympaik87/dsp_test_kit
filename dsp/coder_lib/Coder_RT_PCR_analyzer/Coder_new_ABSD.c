/*
 * Coder_new_ABSD.c
 *
 * Code generation for function 'Coder_new_ABSD'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_new_ABSD.h"
#include "Coder_RT_PCR_analyzer_emxutil.h"
#include "nullAssignment.h"
#include "mod.h"
#include "diff.h"
#include "sign.h"
#include "Coder_fst_fitting.h"

/* Function Definitions */
void Coder_new_ABSD(const double x_data[], const int x_size[1], double
                    ABSD_data[], int ABSD_size[1], double *EFC, double TC,
                    double *result_well)
{
  emxArray_real_T b_x_data;
  double cc_idx_0;
  double cc_idx_1;
  double cc_idx_2;
  int nx;
  int loop_ub;
  int i64;
  int sg_size[2];
  double cNdiff_data[100];
  double sg_data[100];
  double c_data[99];
  int c_size[2];
  int idx;
  int ii_size_idx_1;
  int ii;
  boolean_T exitg1;
  signed char ii_data[99];
  int cp_size[2];
  double cp_data[99];
  boolean_T c_x_data[99];
  int tmp_size[2];
  double tmp_data[100];
  double d_data[99];
  emxArray_int8_T *r8;
  emxArray_real_T *y;
  emxArray_real_T *b_y;
  int b_x_size[2];
  double apnd;
  int n;
  double cdiff;
  double u0;
  double u1;
  signed char b_tmp_data[100];
  boolean_T exitg2;
  *result_well = -1.0;
  b_x_data.data = (double *)&x_data[0];
  b_x_data.size = (int *)&x_size[0];
  b_x_data.allocatedSize = -1;
  b_x_data.numDimensions = 1;
  b_x_data.canFreeData = false;
  Coder_fst_fitting(&b_x_data, ABSD_data, ABSD_size, TC, &cc_idx_0, &cc_idx_1,
                    &cc_idx_2);
  nx = ABSD_size[0];
  loop_ub = ABSD_size[0];
  for (i64 = 0; i64 < loop_ub; i64++) {
    cNdiff_data[i64] = ABSD_data[i64] - ((cc_idx_0 * x_data[i64] * x_data[i64] +
      cc_idx_1 * x_data[i64]) + cc_idx_2);
  }

  sg_size[0] = 1;
  sg_size[1] = nx;
  if (0 <= nx - 1) {
    memcpy(&sg_data[0], &cNdiff_data[0], (unsigned int)(nx * (int)sizeof(double)));
  }

  b_sign(sg_data, sg_size);
  b_diff(sg_data, sg_size, c_data, c_size);
  nx = c_size[1];
  idx = 0;
  ii_size_idx_1 = c_size[1];
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= nx - 1)) {
    if (c_data[ii] != 0.0) {
      idx++;
      ii_data[idx - 1] = (signed char)(ii + 1);
      if (idx >= nx) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }

  if (c_size[1] == 1) {
    if (idx == 0) {
      ii_size_idx_1 = 0;
    }
  } else if (1 > idx) {
    ii_size_idx_1 = 0;
  } else {
    ii_size_idx_1 = idx;
  }

  cp_size[0] = 1;
  cp_size[1] = ii_size_idx_1;
  for (i64 = 0; i64 < ii_size_idx_1; i64++) {
    cp_data[i64] = ii_data[i64];
  }

  /* ------ 24,25 --> 삭제 /  23,24,25 --> 24만 살림 -------- */
  b_diff(cp_data, cp_size, c_data, c_size);
  loop_ub = c_size[1];
  for (i64 = 0; i64 < loop_ub; i64++) {
    c_x_data[i64] = (c_data[i64] > 1.0);
  }

  c_x_data[c_size[1]] = true;
  nx = c_size[1] + 1;
  idx = 0;
  ii_size_idx_1 = c_size[1] + 1;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= nx - 1)) {
    if (c_x_data[ii]) {
      idx++;
      ii_data[idx - 1] = (signed char)(ii + 1);
      if (idx >= nx) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }

  if (c_size[1] + 1 == 1) {
    if (idx == 0) {
      ii_size_idx_1 = 0;
    }
  } else if (1 > idx) {
    ii_size_idx_1 = 0;
  } else {
    ii_size_idx_1 = idx;
  }

  tmp_size[0] = 1;
  tmp_size[1] = 1 + ii_size_idx_1;
  tmp_data[0] = 0.0;
  for (i64 = 0; i64 < ii_size_idx_1; i64++) {
    tmp_data[i64 + 1] = ii_data[i64];
  }

  b_diff(tmp_data, tmp_size, c_data, c_size);

  /* length of the sequences */
  loop_ub = c_size[0] * c_size[1];
  if (0 <= loop_ub - 1) {
    memcpy(&d_data[0], &c_data[0], (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  if ((c_size[1] != 0) && (c_size[1] != 1)) {
    i64 = c_size[1];
    for (ii = 0; ii <= i64 - 2; ii++) {
      d_data[ii + 1] += d_data[ii];
    }
  }

  /* endpoints of the sequences */
  i64 = c_size[1];
  emxInit_int8_T(&r8, 2);
  emxInit_real_T(&y, 2);
  emxInit_real_T(&b_y, 2);
  for (idx = 0; idx < i64; idx++) {
    cc_idx_0 = b_mod(c_data[idx]);
    if (cc_idx_0 == 0.0) {
      /* 짝수 */
      cc_idx_0 = (d_data[idx] - c_data[idx]) + 1.0;
      if (cc_idx_0 > d_data[idx]) {
        ii_size_idx_1 = 1;
        ii = 0;
      } else {
        ii_size_idx_1 = (int)cc_idx_0;
        ii = (int)d_data[idx];
      }

      nx = (signed char)ii - (signed char)ii_size_idx_1;
      for (ii = 0; ii <= nx; ii++) {
        ii_data[ii] = (signed char)((signed char)((signed char)ii_size_idx_1 +
          (signed char)ii) - 1);
      }

      for (ii_size_idx_1 = 0; ii_size_idx_1 <= nx; ii_size_idx_1++) {
        cp_data[ii_data[ii_size_idx_1]] = 0.0;
      }
    } else {
      if ((cc_idx_0 != 0.0) && (c_data[idx] > 1.0)) {
        /*  3부터 홀수 */
        cc_idx_0 = (d_data[idx] - c_data[idx]) + 1.0;
        cc_idx_1 = d_data[idx] - floor(c_data[idx] / 2.0);
        if (rtIsNaN(cc_idx_0) || rtIsNaN(cc_idx_1 - 1.0)) {
          ii_size_idx_1 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = 1;
          emxEnsureCapacity_real_T(y, ii_size_idx_1);
          y->data[0] = rtNaN;
        } else if (cc_idx_1 - 1.0 < cc_idx_0) {
          y->size[0] = 1;
          y->size[1] = 0;
        } else if ((rtIsInf(cc_idx_0) || rtIsInf(cc_idx_1 - 1.0)) && (cc_idx_0 ==
                    cc_idx_1 - 1.0)) {
          ii_size_idx_1 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = 1;
          emxEnsureCapacity_real_T(y, ii_size_idx_1);
          y->data[0] = rtNaN;
        } else if (floor(cc_idx_0) == cc_idx_0) {
          ii_size_idx_1 = y->size[0] * y->size[1];
          y->size[0] = 1;
          loop_ub = (int)floor((cc_idx_1 - 1.0) - cc_idx_0);
          y->size[1] = loop_ub + 1;
          emxEnsureCapacity_real_T(y, ii_size_idx_1);
          for (ii_size_idx_1 = 0; ii_size_idx_1 <= loop_ub; ii_size_idx_1++) {
            y->data[ii_size_idx_1] = cc_idx_0 + (double)ii_size_idx_1;
          }
        } else {
          cc_idx_2 = floor(((cc_idx_1 - 1.0) - cc_idx_0) + 0.5);
          apnd = cc_idx_0 + cc_idx_2;
          cdiff = apnd - (cc_idx_1 - 1.0);
          u0 = fabs(cc_idx_0);
          u1 = fabs(cc_idx_1 - 1.0);
          if ((u0 > u1) || rtIsNaN(u1)) {
            u1 = u0;
          }

          if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
            cc_idx_2++;
            apnd = cc_idx_1 - 1.0;
          } else if (cdiff > 0.0) {
            apnd = cc_idx_0 + (cc_idx_2 - 1.0);
          } else {
            cc_idx_2++;
          }

          if (cc_idx_2 >= 0.0) {
            n = (int)cc_idx_2;
          } else {
            n = 0;
          }

          ii_size_idx_1 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = n;
          emxEnsureCapacity_real_T(y, ii_size_idx_1);
          if (n > 0) {
            y->data[0] = cc_idx_0;
            if (n > 1) {
              y->data[n - 1] = apnd;
              nx = (n - 1) / 2;
              for (ii = 0; ii <= nx - 2; ii++) {
                y->data[1 + ii] = cc_idx_0 + (1.0 + (double)ii);
                y->data[(n - ii) - 2] = apnd - (1.0 + (double)ii);
              }

              if (nx << 1 == n - 1) {
                y->data[nx] = (cc_idx_0 + apnd) / 2.0;
              } else {
                y->data[nx] = cc_idx_0 + (double)nx;
                y->data[nx + 1] = apnd - (double)nx;
              }
            }
          }
        }

        if (rtIsNaN(cc_idx_1 + 1.0) || rtIsNaN(d_data[idx])) {
          ii_size_idx_1 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = 1;
          emxEnsureCapacity_real_T(b_y, ii_size_idx_1);
          b_y->data[0] = rtNaN;
        } else if (d_data[idx] < cc_idx_1 + 1.0) {
          b_y->size[0] = 1;
          b_y->size[1] = 0;
        } else if ((rtIsInf(cc_idx_1 + 1.0) || rtIsInf(d_data[idx])) &&
                   (cc_idx_1 + 1.0 == d_data[idx])) {
          ii_size_idx_1 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = 1;
          emxEnsureCapacity_real_T(b_y, ii_size_idx_1);
          b_y->data[0] = rtNaN;
        } else if (floor(cc_idx_1 + 1.0) == cc_idx_1 + 1.0) {
          ii_size_idx_1 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          loop_ub = (int)floor(d_data[idx] - (cc_idx_1 + 1.0));
          b_y->size[1] = loop_ub + 1;
          emxEnsureCapacity_real_T(b_y, ii_size_idx_1);
          for (ii_size_idx_1 = 0; ii_size_idx_1 <= loop_ub; ii_size_idx_1++) {
            b_y->data[ii_size_idx_1] = (cc_idx_1 + 1.0) + (double)ii_size_idx_1;
          }
        } else {
          cc_idx_2 = floor((d_data[idx] - (cc_idx_1 + 1.0)) + 0.5);
          apnd = (cc_idx_1 + 1.0) + cc_idx_2;
          cdiff = apnd - d_data[idx];
          u0 = fabs(cc_idx_1 + 1.0);
          u1 = fabs(d_data[idx]);
          if ((u0 > u1) || rtIsNaN(u1)) {
            u1 = u0;
          }

          if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
            cc_idx_2++;
            apnd = d_data[idx];
          } else if (cdiff > 0.0) {
            apnd = (cc_idx_1 + 1.0) + (cc_idx_2 - 1.0);
          } else {
            cc_idx_2++;
          }

          if (cc_idx_2 >= 0.0) {
            n = (int)cc_idx_2;
          } else {
            n = 0;
          }

          ii_size_idx_1 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = n;
          emxEnsureCapacity_real_T(b_y, ii_size_idx_1);
          if (n > 0) {
            b_y->data[0] = cc_idx_1 + 1.0;
            if (n > 1) {
              b_y->data[n - 1] = apnd;
              nx = (n - 1) / 2;
              for (ii = 0; ii <= nx - 2; ii++) {
                b_y->data[1 + ii] = (cc_idx_1 + 1.0) + (1.0 + (double)ii);
                b_y->data[(n - ii) - 2] = apnd - (1.0 + (double)ii);
              }

              if (nx << 1 == n - 1) {
                b_y->data[nx] = ((cc_idx_1 + 1.0) + apnd) / 2.0;
              } else {
                b_y->data[nx] = (cc_idx_1 + 1.0) + (double)nx;
                b_y->data[nx + 1] = apnd - (double)nx;
              }
            }
          }
        }

        ii_size_idx_1 = r8->size[0] * r8->size[1];
        r8->size[0] = 1;
        r8->size[1] = y->size[1] + b_y->size[1];
        emxEnsureCapacity_int8_T(r8, ii_size_idx_1);
        loop_ub = y->size[1];
        for (ii_size_idx_1 = 0; ii_size_idx_1 < loop_ub; ii_size_idx_1++) {
          r8->data[ii_size_idx_1] = (signed char)y->data[ii_size_idx_1];
        }

        loop_ub = b_y->size[1];
        for (ii_size_idx_1 = 0; ii_size_idx_1 < loop_ub; ii_size_idx_1++) {
          r8->data[ii_size_idx_1 + y->size[1]] = (signed char)b_y->
            data[ii_size_idx_1];
        }

        loop_ub = r8->size[0] * r8->size[1] - 1;
        for (ii_size_idx_1 = 0; ii_size_idx_1 <= loop_ub; ii_size_idx_1++) {
          cp_data[r8->data[ii_size_idx_1] - 1] = 0.0;
        }
      }
    }
  }

  emxFree_real_T(&b_y);
  emxFree_int8_T(&r8);
  b_x_size[0] = 1;
  b_x_size[1] = cp_size[1];
  loop_ub = cp_size[1];
  for (i64 = 0; i64 < loop_ub; i64++) {
    c_x_data[i64] = (cp_data[i64] == 0.0);
  }

  nullAssignment(cp_data, cp_size, c_x_data, b_x_size);

  /*  remove zeros */
  /* ----------------------------------------------------------             */
  cc_idx_2 = 0.0;
  apnd = 0.0;
  n = ABSD_size[0];
  if (ABSD_size[0] <= 2) {
    if (ABSD_size[0] == 1) {
      cdiff = ABSD_data[0];
    } else if ((ABSD_data[0] > ABSD_data[1]) || (rtIsNaN(ABSD_data[0]) &&
                (!rtIsNaN(ABSD_data[1])))) {
      cdiff = ABSD_data[1];
    } else {
      cdiff = ABSD_data[0];
    }
  } else {
    if (!rtIsNaN(ABSD_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      ii = 2;
      exitg1 = false;
      while ((!exitg1) && (ii <= ABSD_size[0])) {
        if (!rtIsNaN(ABSD_data[ii - 1])) {
          idx = ii;
          exitg1 = true;
        } else {
          ii++;
        }
      }
    }

    if (idx == 0) {
      cdiff = ABSD_data[0];
    } else {
      cdiff = ABSD_data[idx - 1];
      i64 = idx + 1;
      for (ii = i64; ii <= n; ii++) {
        cc_idx_0 = ABSD_data[ii - 1];
        if (cdiff > cc_idx_0) {
          cdiff = cc_idx_0;
        }
      }
    }
  }

  n = ABSD_size[0];
  if (ABSD_size[0] <= 2) {
    if (ABSD_size[0] == 1) {
      cc_idx_1 = ABSD_data[0];
    } else if ((ABSD_data[0] < ABSD_data[1]) || (rtIsNaN(ABSD_data[0]) &&
                (!rtIsNaN(ABSD_data[1])))) {
      cc_idx_1 = ABSD_data[1];
    } else {
      cc_idx_1 = ABSD_data[0];
    }
  } else {
    if (!rtIsNaN(ABSD_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      ii = 2;
      exitg1 = false;
      while ((!exitg1) && (ii <= ABSD_size[0])) {
        if (!rtIsNaN(ABSD_data[ii - 1])) {
          idx = ii;
          exitg1 = true;
        } else {
          ii++;
        }
      }
    }

    if (idx == 0) {
      cc_idx_1 = ABSD_data[0];
    } else {
      cc_idx_1 = ABSD_data[idx - 1];
      i64 = idx + 1;
      for (ii = i64; ii <= n; ii++) {
        cc_idx_0 = ABSD_data[ii - 1];
        if (cc_idx_1 < cc_idx_0) {
          cc_idx_1 = cc_idx_0;
        }
      }
    }
  }

  cc_idx_0 = cdiff - cc_idx_1;
  nx = 0;
  cc_idx_1 = 0.0;
  if (sg_data[sg_size[1] - 1] == 1.0) {
    idx = cp_size[1];
  } else {
    idx = cp_size[1] - 1;
  }

  exitg1 = false;
  while ((!exitg1) && (cc_idx_2 < 0.05)) {
    if (((double)idx - 1.0) - 2.0 * apnd < 1.0) {
      *result_well = 0.0;
      exitg1 = true;
    } else {
      cc_idx_1 = cp_data[(int)(((double)idx - 1.0) - 2.0 * apnd) - 1];
      if (cp_data[(int)(((double)idx - 1.0) - 2.0 * apnd) - 1] > cp_data[(int)
          ((double)idx - 2.0 * apnd) - 1]) {
        i64 = 0;
        ii_size_idx_1 = 0;
      } else {
        i64 = (int)cp_data[(int)(((double)idx - 1.0) - 2.0 * apnd) - 1] - 1;
        ii_size_idx_1 = (int)cp_data[(int)((double)idx - 2.0 * apnd) - 1];
      }

      ii = y->size[0] * y->size[1];
      y->size[0] = 1;
      loop_ub = ii_size_idx_1 - i64;
      y->size[1] = loop_ub;
      emxEnsureCapacity_real_T(y, ii);
      for (ii_size_idx_1 = 0; ii_size_idx_1 < loop_ub; ii_size_idx_1++) {
        y->data[ii_size_idx_1] = cNdiff_data[i64 + ii_size_idx_1];
      }

      n = loop_ub - 1;
      if (loop_ub <= 2) {
        if (loop_ub == 1) {
          cdiff = cNdiff_data[i64];
          nx = 1;
        } else {
          cdiff = cNdiff_data[i64 + 1];
          if ((cNdiff_data[i64] > cdiff) || (rtIsNaN(cNdiff_data[i64]) &&
               (!rtIsNaN(cdiff)))) {
            nx = 2;
          } else {
            cdiff = cNdiff_data[i64];
            nx = 1;
          }
        }
      } else {
        if (!rtIsNaN(cNdiff_data[i64])) {
          nx = 1;
        } else {
          nx = 0;
          ii = 2;
          exitg2 = false;
          while ((!exitg2) && (ii <= loop_ub)) {
            if (!rtIsNaN(y->data[ii - 1])) {
              nx = ii;
              exitg2 = true;
            } else {
              ii++;
            }
          }
        }

        if (nx == 0) {
          cdiff = cNdiff_data[i64];
          nx = 1;
        } else {
          cdiff = cNdiff_data[(i64 + nx) - 1];
          i64 = nx + 1;
          for (ii = i64; ii <= n + 1; ii++) {
            if (cdiff > y->data[ii - 1]) {
              cdiff = y->data[ii - 1];
              nx = ii;
            }
          }
        }
      }

      cc_idx_2 = cdiff / cc_idx_0;
      apnd++;
    }
  }

  emxFree_real_T(&y);
  if (*result_well == -1.0) {
    u1 = ((double)nx + cc_idx_1) - 1.0;
    if ((!(*EFC > u1)) && (!rtIsNaN(u1))) {
      *EFC = u1;
    }

    if (1.0 > *EFC) {
      i64 = 0;
    } else {
      i64 = (int)*EFC;
    }

    loop_ub = (signed char)i64 - 1;
    for (ii_size_idx_1 = 0; ii_size_idx_1 <= loop_ub; ii_size_idx_1++) {
      b_tmp_data[ii_size_idx_1] = (signed char)ii_size_idx_1;
    }

    cc_idx_0 = ABSD_data[(int)*EFC - 1];
    loop_ub = (signed char)i64;
    for (i64 = 0; i64 < loop_ub; i64++) {
      ABSD_data[b_tmp_data[i64]] = cc_idx_0;
    }
  }
}

/* End of code generation (Coder_new_ABSD.c) */
