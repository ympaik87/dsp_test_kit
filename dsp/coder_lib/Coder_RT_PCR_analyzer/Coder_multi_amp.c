/*
 * Coder_multi_amp.c
 *
 * Code generation for function 'Coder_multi_amp'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_multi_amp.h"
#include "Coder_RT_PCR_analyzer_emxutil.h"
#include "Coder_fst_fitting.h"
#include "nullAssignment.h"
#include "mod.h"
#include "diff.h"
#include "sign.h"

/* Function Definitions */
void Coder_multi_amp(const double fst_val_data[], const double ABSD_data[],
                     const int ABSD_size[1], double TC, double *EC, double
                     *diff2, double it[2])
{
  int nx;
  int i30;
  int sg_size[2];
  double cNdiff_data[100];
  double sg_data[100];
  double c_data[99];
  int c_size[2];
  int idx;
  int lastcycle;
  int ii;
  boolean_T exitg1;
  signed char ii_data[99];
  int cp_size[2];
  double cp_data[99];
  boolean_T x_data[99];
  int tmp_size[2];
  double tmp_data[100];
  double d_data[99];
  emxArray_int8_T *r5;
  emxArray_real_T *y;
  emxArray_real_T *b_y;
  double EC0;
  int x_size[2];
  double b_tmp;
  int i31;
  double ndbl;
  double apnd;
  double cdiff;
  double u0;
  double u1;
  int n;
  double ex;
  double b_ex;
  double c_ex;
  double d_ex;
  double e_ex;
  emxArray_real_T *c_y;
  int b_ABSD_size[1];
  int c_ABSD_size[1];
  nx = ABSD_size[0];
  for (i30 = 0; i30 < nx; i30++) {
    cNdiff_data[i30] = ABSD_data[i30] - fst_val_data[i30];
  }

  sg_size[0] = 1;
  sg_size[1] = ABSD_size[0];
  if (0 <= ABSD_size[0] - 1) {
    memcpy(&sg_data[0], &cNdiff_data[0], (unsigned int)(ABSD_size[0] * (int)
            sizeof(double)));
  }

  b_sign(sg_data, sg_size);
  b_diff(sg_data, sg_size, c_data, c_size);
  nx = c_size[1];
  idx = 0;
  lastcycle = c_size[1];
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
      lastcycle = 0;
    }
  } else if (1 > idx) {
    lastcycle = 0;
  } else {
    lastcycle = idx;
  }

  cp_size[0] = 1;
  cp_size[1] = lastcycle;
  for (i30 = 0; i30 < lastcycle; i30++) {
    cp_data[i30] = ii_data[i30];
  }

  /* ------ 24,25 --> 삭제 /  23,24,25 --> 24만 살림 -------- */
  b_diff(cp_data, cp_size, c_data, c_size);
  nx = c_size[1];
  for (i30 = 0; i30 < nx; i30++) {
    x_data[i30] = (c_data[i30] > 1.0);
  }

  x_data[c_size[1]] = true;
  nx = c_size[1] + 1;
  idx = 0;
  lastcycle = c_size[1] + 1;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii <= nx - 1)) {
    if (x_data[ii]) {
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
      lastcycle = 0;
    }
  } else if (1 > idx) {
    lastcycle = 0;
  } else {
    lastcycle = idx;
  }

  tmp_size[0] = 1;
  tmp_size[1] = 1 + lastcycle;
  tmp_data[0] = 0.0;
  for (i30 = 0; i30 < lastcycle; i30++) {
    tmp_data[i30 + 1] = ii_data[i30];
  }

  b_diff(tmp_data, tmp_size, c_data, c_size);

  /* length of the sequences */
  nx = c_size[0] * c_size[1];
  if (0 <= nx - 1) {
    memcpy(&d_data[0], &c_data[0], (unsigned int)(nx * (int)sizeof(double)));
  }

  if ((c_size[1] != 0) && (c_size[1] != 1)) {
    i30 = c_size[1];
    for (ii = 0; ii <= i30 - 2; ii++) {
      d_data[ii + 1] += d_data[ii];
    }
  }

  /* endpoints of the sequences */
  i30 = c_size[1];
  emxInit_int8_T(&r5, 2);
  emxInit_real_T(&y, 2);
  emxInit_real_T(&b_y, 2);
  for (lastcycle = 0; lastcycle < i30; lastcycle++) {
    EC0 = b_mod(c_data[lastcycle]);
    if (EC0 == 0.0) {
      /* 짝수 */
      EC0 = (d_data[lastcycle] - c_data[lastcycle]) + 1.0;
      if (EC0 > d_data[lastcycle]) {
        i31 = 1;
        ii = 0;
      } else {
        i31 = (int)EC0;
        ii = (int)d_data[lastcycle];
      }

      nx = (signed char)ii - (signed char)i31;
      for (ii = 0; ii <= nx; ii++) {
        ii_data[ii] = (signed char)((signed char)((signed char)i31 + (signed
          char)ii) - 1);
      }

      for (i31 = 0; i31 <= nx; i31++) {
        cp_data[ii_data[i31]] = 0.0;
      }
    } else {
      if ((EC0 != 0.0) && (c_data[lastcycle] > 1.0)) {
        /*  3부터 홀수 */
        EC0 = (d_data[lastcycle] - c_data[lastcycle]) + 1.0;
        b_tmp = d_data[lastcycle] - floor(c_data[lastcycle] / 2.0);
        if (rtIsNaN(EC0) || rtIsNaN(b_tmp - 1.0)) {
          i31 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = 1;
          emxEnsureCapacity_real_T(y, i31);
          y->data[0] = rtNaN;
        } else if (b_tmp - 1.0 < EC0) {
          y->size[0] = 1;
          y->size[1] = 0;
        } else if ((rtIsInf(EC0) || rtIsInf(b_tmp - 1.0)) && (EC0 == b_tmp - 1.0))
        {
          i31 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = 1;
          emxEnsureCapacity_real_T(y, i31);
          y->data[0] = rtNaN;
        } else if (floor(EC0) == EC0) {
          i31 = y->size[0] * y->size[1];
          y->size[0] = 1;
          nx = (int)floor((b_tmp - 1.0) - EC0);
          y->size[1] = nx + 1;
          emxEnsureCapacity_real_T(y, i31);
          for (i31 = 0; i31 <= nx; i31++) {
            y->data[i31] = EC0 + (double)i31;
          }
        } else {
          ndbl = floor(((b_tmp - 1.0) - EC0) + 0.5);
          apnd = EC0 + ndbl;
          cdiff = apnd - (b_tmp - 1.0);
          u0 = fabs(EC0);
          u1 = fabs(b_tmp - 1.0);
          if ((u0 > u1) || rtIsNaN(u1)) {
            u1 = u0;
          }

          if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
            ndbl++;
            apnd = b_tmp - 1.0;
          } else if (cdiff > 0.0) {
            apnd = EC0 + (ndbl - 1.0);
          } else {
            ndbl++;
          }

          if (ndbl >= 0.0) {
            n = (int)ndbl;
          } else {
            n = 0;
          }

          i31 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = n;
          emxEnsureCapacity_real_T(y, i31);
          if (n > 0) {
            y->data[0] = EC0;
            if (n > 1) {
              y->data[n - 1] = apnd;
              nx = (n - 1) / 2;
              for (ii = 0; ii <= nx - 2; ii++) {
                y->data[1 + ii] = EC0 + (1.0 + (double)ii);
                y->data[(n - ii) - 2] = apnd - (1.0 + (double)ii);
              }

              if (nx << 1 == n - 1) {
                y->data[nx] = (EC0 + apnd) / 2.0;
              } else {
                y->data[nx] = EC0 + (double)nx;
                y->data[nx + 1] = apnd - (double)nx;
              }
            }
          }
        }

        if (rtIsNaN(b_tmp + 1.0) || rtIsNaN(d_data[lastcycle])) {
          i31 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = 1;
          emxEnsureCapacity_real_T(b_y, i31);
          b_y->data[0] = rtNaN;
        } else if (d_data[lastcycle] < b_tmp + 1.0) {
          b_y->size[0] = 1;
          b_y->size[1] = 0;
        } else if ((rtIsInf(b_tmp + 1.0) || rtIsInf(d_data[lastcycle])) &&
                   (b_tmp + 1.0 == d_data[lastcycle])) {
          i31 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = 1;
          emxEnsureCapacity_real_T(b_y, i31);
          b_y->data[0] = rtNaN;
        } else if (floor(b_tmp + 1.0) == b_tmp + 1.0) {
          i31 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          nx = (int)floor(d_data[lastcycle] - (b_tmp + 1.0));
          b_y->size[1] = nx + 1;
          emxEnsureCapacity_real_T(b_y, i31);
          for (i31 = 0; i31 <= nx; i31++) {
            b_y->data[i31] = (b_tmp + 1.0) + (double)i31;
          }
        } else {
          ndbl = floor((d_data[lastcycle] - (b_tmp + 1.0)) + 0.5);
          apnd = (b_tmp + 1.0) + ndbl;
          cdiff = apnd - d_data[lastcycle];
          u0 = fabs(b_tmp + 1.0);
          u1 = fabs(d_data[lastcycle]);
          if ((u0 > u1) || rtIsNaN(u1)) {
            u1 = u0;
          }

          if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
            ndbl++;
            apnd = d_data[lastcycle];
          } else if (cdiff > 0.0) {
            apnd = (b_tmp + 1.0) + (ndbl - 1.0);
          } else {
            ndbl++;
          }

          if (ndbl >= 0.0) {
            n = (int)ndbl;
          } else {
            n = 0;
          }

          i31 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = n;
          emxEnsureCapacity_real_T(b_y, i31);
          if (n > 0) {
            b_y->data[0] = b_tmp + 1.0;
            if (n > 1) {
              b_y->data[n - 1] = apnd;
              nx = (n - 1) / 2;
              for (ii = 0; ii <= nx - 2; ii++) {
                b_y->data[1 + ii] = (b_tmp + 1.0) + (1.0 + (double)ii);
                b_y->data[(n - ii) - 2] = apnd - (1.0 + (double)ii);
              }

              if (nx << 1 == n - 1) {
                b_y->data[nx] = ((b_tmp + 1.0) + apnd) / 2.0;
              } else {
                b_y->data[nx] = (b_tmp + 1.0) + (double)nx;
                b_y->data[nx + 1] = apnd - (double)nx;
              }
            }
          }
        }

        i31 = r5->size[0] * r5->size[1];
        r5->size[0] = 1;
        r5->size[1] = y->size[1] + b_y->size[1];
        emxEnsureCapacity_int8_T(r5, i31);
        nx = y->size[1];
        for (i31 = 0; i31 < nx; i31++) {
          r5->data[i31] = (signed char)y->data[i31];
        }

        nx = b_y->size[1];
        for (i31 = 0; i31 < nx; i31++) {
          r5->data[i31 + y->size[1]] = (signed char)b_y->data[i31];
        }

        nx = r5->size[0] * r5->size[1] - 1;
        for (i31 = 0; i31 <= nx; i31++) {
          cp_data[r5->data[i31] - 1] = 0.0;
        }
      }
    }
  }

  emxFree_real_T(&b_y);
  emxFree_int8_T(&r5);
  x_size[0] = 1;
  x_size[1] = cp_size[1];
  nx = cp_size[1];
  for (i30 = 0; i30 < nx; i30++) {
    x_data[i30] = (cp_data[i30] == 0.0);
  }

  nullAssignment(cp_data, cp_size, x_data, x_size);

  /*  remove zeros */
  /*  fprintf('cp=[ %s, ', Double2String(cp(1))) */
  /*  for i=2:length(cp)-1 */
  /*      fprintf('%s, ', Double2String(cp(i))) */
  /*  end */
  /*  fprintf('%s]\n ', Double2String(cp(length(cp)))) */
  /* ---------------------------------------------------------- */
  if (sg_data[sg_size[1] - 1] == 1.0) {
    lastcycle = cp_size[1] - 1;
  } else {
    lastcycle = cp_size[1] - 2;
  }

  *diff2 = 0.0;
  it[0] = 0.0;
  it[1] = 0.0;
  *EC = TC;
  if (lastcycle > 0) {
    n = ABSD_size[0];
    if (ABSD_size[0] <= 2) {
      if (ABSD_size[0] == 1) {
        ex = ABSD_data[0];
      } else if ((ABSD_data[0] > ABSD_data[1]) || (rtIsNaN(ABSD_data[0]) &&
                  (!rtIsNaN(ABSD_data[1])))) {
        ex = ABSD_data[1];
      } else {
        ex = ABSD_data[0];
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
        ex = ABSD_data[0];
      } else {
        ex = ABSD_data[idx - 1];
        i30 = idx + 1;
        for (ii = i30; ii <= n; ii++) {
          EC0 = ABSD_data[ii - 1];
          if (ex > EC0) {
            ex = EC0;
          }
        }
      }
    }

    n = ABSD_size[0];
    if (ABSD_size[0] <= 2) {
      if (ABSD_size[0] == 1) {
        b_ex = ABSD_data[0];
      } else if ((ABSD_data[0] < ABSD_data[1]) || (rtIsNaN(ABSD_data[0]) &&
                  (!rtIsNaN(ABSD_data[1])))) {
        b_ex = ABSD_data[1];
      } else {
        b_ex = ABSD_data[0];
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
        b_ex = ABSD_data[0];
      } else {
        b_ex = ABSD_data[idx - 1];
        i30 = idx + 1;
        for (ii = i30; ii <= n; ii++) {
          EC0 = ABSD_data[ii - 1];
          if (b_ex < EC0) {
            b_ex = EC0;
          }
        }
      }
    }

    n = ABSD_size[0];
    if (ABSD_size[0] <= 2) {
      if (ABSD_size[0] == 1) {
        c_ex = ABSD_data[0];
      } else if ((ABSD_data[0] < ABSD_data[1]) || (rtIsNaN(ABSD_data[0]) &&
                  (!rtIsNaN(ABSD_data[1])))) {
        c_ex = ABSD_data[1];
      } else {
        c_ex = ABSD_data[0];
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
        c_ex = ABSD_data[0];
      } else {
        c_ex = ABSD_data[idx - 1];
        i30 = idx + 1;
        for (ii = i30; ii <= n; ii++) {
          EC0 = ABSD_data[ii - 1];
          if (c_ex < EC0) {
            c_ex = EC0;
          }
        }
      }
    }

    n = ABSD_size[0];
    if (ABSD_size[0] <= 2) {
      if (ABSD_size[0] == 1) {
        d_ex = ABSD_data[0];
      } else if ((ABSD_data[0] > ABSD_data[1]) || (rtIsNaN(ABSD_data[0]) &&
                  (!rtIsNaN(ABSD_data[1])))) {
        d_ex = ABSD_data[1];
      } else {
        d_ex = ABSD_data[0];
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
        d_ex = ABSD_data[0];
      } else {
        d_ex = ABSD_data[idx - 1];
        i30 = idx + 1;
        for (ii = i30; ii <= n; ii++) {
          EC0 = ABSD_data[ii - 1];
          if (d_ex > EC0) {
            d_ex = EC0;
          }
        }
      }
    }

    if (cp_data[lastcycle - 1] > cp_data[lastcycle]) {
      i30 = 0;
      i31 = 0;
    } else {
      i30 = (int)cp_data[lastcycle - 1] - 1;
      i31 = (int)cp_data[lastcycle];
    }

    ii = y->size[0] * y->size[1];
    y->size[0] = 1;
    nx = i31 - i30;
    y->size[1] = nx;
    emxEnsureCapacity_real_T(y, ii);
    for (i31 = 0; i31 < nx; i31++) {
      y->data[i31] = cNdiff_data[i30 + i31];
    }

    n = nx - 1;
    if (nx <= 2) {
      if (nx == 1) {
        e_ex = cNdiff_data[i30];
        idx = 1;
      } else {
        e_ex = cNdiff_data[i30 + 1];
        if ((cNdiff_data[i30] > e_ex) || (rtIsNaN(cNdiff_data[i30]) && (!rtIsNaN
              (e_ex)))) {
          idx = 2;
        } else {
          e_ex = cNdiff_data[i30];
          idx = 1;
        }
      }
    } else {
      if (!rtIsNaN(cNdiff_data[i30])) {
        idx = 1;
      } else {
        idx = 0;
        ii = 2;
        exitg1 = false;
        while ((!exitg1) && (ii <= nx)) {
          if (!rtIsNaN(y->data[ii - 1])) {
            idx = ii;
            exitg1 = true;
          } else {
            ii++;
          }
        }
      }

      if (idx == 0) {
        e_ex = cNdiff_data[i30];
        idx = 1;
      } else {
        e_ex = cNdiff_data[(i30 + idx) - 1];
        i30 = idx + 1;
        for (ii = i30; ii <= n + 1; ii++) {
          if (e_ex > y->data[ii - 1]) {
            e_ex = y->data[ii - 1];
            idx = ii;
          }
        }
      }
    }

    /* ------------ */
    it[0] = ((double)idx + cp_data[lastcycle - 1]) - 2.0;
    it[1] = cp_data[lastcycle];
    if (it[0] > cp_data[lastcycle]) {
      i30 = 0;
      i31 = 0;
    } else {
      i30 = (int)it[0] - 1;
      i31 = (int)cp_data[lastcycle];
    }

    if (rtIsNaN(it[0]) || rtIsNaN(cp_data[lastcycle])) {
      ii = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, ii);
      y->data[0] = rtNaN;
    } else if (cp_data[lastcycle] < it[0]) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else if ((rtIsInf(it[0]) || rtIsInf(cp_data[lastcycle])) && (it[0] ==
                cp_data[lastcycle])) {
      ii = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 1;
      emxEnsureCapacity_real_T(y, ii);
      y->data[0] = rtNaN;
    } else if (floor(it[0]) == it[0]) {
      ii = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = (int)floor(cp_data[lastcycle] - it[0]) + 1;
      emxEnsureCapacity_real_T(y, ii);
      nx = (int)floor(cp_data[lastcycle] - it[0]);
      for (ii = 0; ii <= nx; ii++) {
        y->data[ii] = it[0] + (double)ii;
      }
    } else {
      ndbl = floor((cp_data[lastcycle] - it[0]) + 0.5);
      apnd = it[0] + ndbl;
      cdiff = apnd - cp_data[lastcycle];
      u0 = fabs(it[0]);
      u1 = fabs(cp_data[lastcycle]);
      if ((u0 > u1) || rtIsNaN(u1)) {
        u1 = u0;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
        ndbl++;
        apnd = cp_data[lastcycle];
      } else if (cdiff > 0.0) {
        apnd = it[0] + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      ii = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = n;
      emxEnsureCapacity_real_T(y, ii);
      if (n > 0) {
        y->data[0] = it[0];
        if (n > 1) {
          y->data[n - 1] = apnd;
          nx = (n - 1) / 2;
          for (ii = 0; ii <= nx - 2; ii++) {
            y->data[1 + ii] = it[0] + (1.0 + (double)ii);
            y->data[(n - ii) - 2] = apnd - (1.0 + (double)ii);
          }

          if (nx << 1 == n - 1) {
            y->data[nx] = (it[0] + apnd) / 2.0;
          } else {
            y->data[nx] = it[0] + (double)nx;
            y->data[nx + 1] = apnd - (double)nx;
          }
        }
      }
    }

    emxInit_real_T(&c_y, 1);
    ii = c_y->size[0];
    c_y->size[0] = y->size[1];
    emxEnsureCapacity_real_T(c_y, ii);
    nx = y->size[1];
    for (ii = 0; ii < nx; ii++) {
      c_y->data[ii] = y->data[ii];
    }

    nx = i31 - i30;
    b_ABSD_size[0] = nx;
    for (i31 = 0; i31 < nx; i31++) {
      c_data[i31] = ABSD_data[i30 + i31];
    }

    Coder_fst_fitting(c_y, c_data, b_ABSD_size, (cp_data[lastcycle] - it[0]) +
                      1.0, diff2, &b_tmp, &EC0);
    EC0 = ((double)idx + cp_data[lastcycle - 1]) - 1.0;
    if (*diff2 < 0.0) {
      /* it=[itv(1) bend+itv(1)]; */
      it[0] = cp_data[lastcycle - 1];
      it[1] = cp_data[lastcycle];
      if (cp_data[lastcycle - 1] > cp_data[lastcycle]) {
        i30 = 0;
        i31 = 0;
      } else {
        i30 = (int)cp_data[lastcycle - 1] - 1;
        i31 = (int)cp_data[lastcycle];
      }

      if (rtIsNaN(cp_data[lastcycle - 1]) || rtIsNaN(cp_data[lastcycle])) {
        ii = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, ii);
        y->data[0] = rtNaN;
      } else if (cp_data[lastcycle] < cp_data[lastcycle - 1]) {
        y->size[0] = 1;
        y->size[1] = 0;
      } else if ((rtIsInf(cp_data[lastcycle - 1]) || rtIsInf(cp_data[lastcycle]))
                 && (cp_data[lastcycle - 1] == cp_data[lastcycle])) {
        ii = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, ii);
        y->data[0] = rtNaN;
      } else if (floor(cp_data[lastcycle - 1]) == cp_data[lastcycle - 1]) {
        ii = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = (int)floor(cp_data[lastcycle] - cp_data[lastcycle - 1]) + 1;
        emxEnsureCapacity_real_T(y, ii);
        nx = (int)floor(cp_data[lastcycle] - cp_data[lastcycle - 1]);
        for (ii = 0; ii <= nx; ii++) {
          y->data[ii] = it[0] + (double)ii;
        }
      } else {
        ndbl = floor((cp_data[lastcycle] - cp_data[lastcycle - 1]) + 0.5);
        apnd = cp_data[lastcycle - 1] + ndbl;
        cdiff = apnd - cp_data[lastcycle];
        u0 = fabs(cp_data[lastcycle - 1]);
        u1 = fabs(cp_data[lastcycle]);
        if ((u0 > u1) || rtIsNaN(u1)) {
          u1 = u0;
        }

        if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
          ndbl++;
          apnd = cp_data[lastcycle];
        } else if (cdiff > 0.0) {
          apnd = cp_data[lastcycle - 1] + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          n = (int)ndbl;
        } else {
          n = 0;
        }

        ii = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = n;
        emxEnsureCapacity_real_T(y, ii);
        if (n > 0) {
          y->data[0] = cp_data[lastcycle - 1];
          if (n > 1) {
            y->data[n - 1] = apnd;
            nx = (n - 1) / 2;
            for (ii = 0; ii <= nx - 2; ii++) {
              y->data[1 + ii] = it[0] + (1.0 + (double)ii);
              y->data[(n - ii) - 2] = apnd - (1.0 + (double)ii);
            }

            if (nx << 1 == n - 1) {
              y->data[nx] = (cp_data[lastcycle - 1] + apnd) / 2.0;
            } else {
              y->data[nx] = cp_data[lastcycle - 1] + (double)nx;
              y->data[nx + 1] = apnd - (double)nx;
            }
          }
        }
      }

      ii = c_y->size[0];
      c_y->size[0] = y->size[1];
      emxEnsureCapacity_real_T(c_y, ii);
      nx = y->size[1];
      for (ii = 0; ii < nx; ii++) {
        c_y->data[ii] = y->data[ii];
      }

      nx = i31 - i30;
      c_ABSD_size[0] = nx;
      for (i31 = 0; i31 < nx; i31++) {
        c_data[i31] = ABSD_data[i30 + i31];
      }

      Coder_fst_fitting(c_y, c_data, c_ABSD_size, (cp_data[lastcycle] -
        cp_data[lastcycle - 1]) + 1.0, diff2, &b_tmp, &EC0);
      EC0 = cp_data[lastcycle - 1];
    }

    emxFree_real_T(&c_y);

    /* ------------- */
    if ((e_ex / (ex - b_ex) >= 0.04) && (ABSD_data[(int)EC0 - 1] > (c_ex + 2.0 *
          d_ex) / 3.0) && (*diff2 > 0.0)) {
      *EC = EC0;
    }
  }

  emxFree_real_T(&y);
}

/* End of code generation (Coder_multi_amp.c) */
