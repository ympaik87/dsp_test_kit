/*
 * SigFit.c
 *
 * Code generation for function 'SigFit'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "SigFit.h"
#include "SigFitter_4para.h"
#include "SigFit_rtwutil.h"

/* Function Definitions */
void SigFit(const double x[45], const double ABSD[45], double *result, const
            double ini_param[4], double *SC, double TC, double HTC, double SFC,
            const double perturbation[60], double param_data[],
            int param_size[2], double f[45])
{
  double ERR;
  double ERR2;
  double state;
  boolean_T exitg1;
  int i4;
  int i5;
  int ixstart;
  int n;
  int x_size[1];
  int loop_ub;
  int ABSD_size[1];
  double x_data[45];
  double ABSD_data[45];
  double param[4];
  double max_sig;
  int i6;
  int b_x_size[1];
  int b_ABSD_size[1];
  double mtmp;
  boolean_T exitg2;
  double b_mtmp;
  double ovitv[2];

  /*  global TC HTC SFC perturbation */
  ERR = 0.0;
  ERR2 = 0.0;
  state = 0.0;
  param_size[0] = 4;
  param_size[1] = 4;
  memset(&param_data[0], 0, sizeof(double) << 4);
  memset(&f[0], 0, 45U * sizeof(double));
  exitg1 = false;
  while ((!exitg1) && ((ERR < 0.5) || (ERR > 1.5) || (ERR2 < 0.5) || (state ==
           0.0))) {
    if (*SC > HTC) {
      *result = 3.0;
      exitg1 = true;
    } else {
      if (*SC > TC) {
        i4 = 0;
        i5 = 0;
      } else {
        i4 = (int)*SC - 1;
        i5 = (int)TC;
      }

      if (*SC > TC) {
        ixstart = 0;
        n = 0;
      } else {
        ixstart = (int)*SC - 1;
        n = (int)TC;
      }

      x_size[0] = i5 - i4;
      loop_ub = i5 - i4;
      for (i5 = 0; i5 < loop_ub; i5++) {
        x_data[i5] = x[i4 + i5];
      }

      ABSD_size[0] = n - ixstart;
      loop_ub = n - ixstart;
      for (i4 = 0; i4 < loop_ub; i4++) {
        ABSD_data[i4] = ABSD[ixstart + i4];
      }

      SigFitter_4para(x_data, x_size, ABSD_data, ABSD_size, ini_param, param,
                      &ERR2, &state);
      param_size[0] = 1;
      param_size[1] = 4;
      for (i4 = 0; i4 < 4; i4++) {
        param_data[i4] = param[i4];
      }

      if (fabs(param[3]) > 2.0) {
        if (*SC > TC) {
          i4 = 0;
          i5 = 0;
        } else {
          i4 = (int)*SC - 1;
          i5 = (int)TC;
        }

        if (*SC > TC) {
          ixstart = 0;
          n = 0;
        } else {
          ixstart = (int)*SC - 1;
          n = (int)TC;
        }

        if (*SC > TC) {
          i6 = 0;
        } else {
          i6 = (int)*SC - 1;
        }

        b_x_size[0] = i5 - i4;
        loop_ub = i5 - i4;
        for (i5 = 0; i5 < loop_ub; i5++) {
          x_data[i5] = x[i4 + i5];
        }

        b_ABSD_size[0] = n - ixstart;
        loop_ub = n - ixstart;
        for (i4 = 0; i4 < loop_ub; i4++) {
          ABSD_data[i4] = ABSD[ixstart + i4] + perturbation[i6 + i4];
        }

        SigFitter_4para(x_data, b_x_size, ABSD_data, b_ABSD_size, ini_param,
                        param, &ERR2, &state);
        param_size[0] = 1;
        param_size[1] = 4;
        for (i4 = 0; i4 < 4; i4++) {
          param_data[i4] = param[i4];
        }
      }

      ERR2 = param_data[1] - param_data[0];
      for (ixstart = 0; ixstart < 45; ixstart++) {
        f[ixstart] = param_data[0] + ERR2 / (1.0 + rt_powd_snf(10.0,
          (param_data[2] - x[ixstart]) * param_data[3]));
      }

      /* ---------(B) check suitability -------- */
      if ((f[(int)TC - 1] < f[0]) || rtIsNaN(f[0])) {
        ERR2 = f[(int)TC - 1];
      } else {
        ERR2 = f[0];
      }

      if ((f[(int)TC - 1] > f[0]) || rtIsNaN(f[0])) {
        max_sig = f[(int)TC - 1];
      } else {
        max_sig = f[0];
      }

      if (SFC > TC) {
        i4 = 1;
        i5 = 1;
      } else {
        i4 = (int)SFC;
        i5 = (int)TC + 1;
      }

      ixstart = 1;
      n = i5 - i4;
      mtmp = ABSD[i4 - 1];
      if (i5 - i4 > 1) {
        if (rtIsNaN(ABSD[i4 - 1])) {
          loop_ub = 2;
          exitg2 = false;
          while ((!exitg2) && (loop_ub <= n)) {
            ixstart = loop_ub;
            if (!rtIsNaN(ABSD[(i4 + loop_ub) - 2])) {
              mtmp = ABSD[(i4 + loop_ub) - 2];
              exitg2 = true;
            } else {
              loop_ub++;
            }
          }
        }

        if (ixstart < i5 - i4) {
          for (loop_ub = ixstart + 1; loop_ub <= n; loop_ub++) {
            if (ABSD[(i4 + loop_ub) - 2] < mtmp) {
              mtmp = ABSD[(i4 + loop_ub) - 2];
            }
          }
        }
      }

      if (SFC > TC) {
        i4 = 1;
        i5 = 1;
      } else {
        i4 = (int)SFC;
        i5 = (int)TC + 1;
      }

      ixstart = 1;
      n = i5 - i4;
      b_mtmp = ABSD[i4 - 1];
      if (i5 - i4 > 1) {
        if (rtIsNaN(ABSD[i4 - 1])) {
          loop_ub = 2;
          exitg2 = false;
          while ((!exitg2) && (loop_ub <= n)) {
            ixstart = loop_ub;
            if (!rtIsNaN(ABSD[(i4 + loop_ub) - 2])) {
              b_mtmp = ABSD[(i4 + loop_ub) - 2];
              exitg2 = true;
            } else {
              loop_ub++;
            }
          }
        }

        if (ixstart < i5 - i4) {
          for (loop_ub = ixstart + 1; loop_ub <= n; loop_ub++) {
            if (ABSD[(i4 + loop_ub) - 2] > b_mtmp) {
              b_mtmp = ABSD[(i4 + loop_ub) - 2];
            }
          }
        }
      }

      ERR = (max_sig - ERR2) / (b_mtmp - mtmp);
      for (i4 = 0; i4 < 2; i4++) {
        ovitv[i4] = 0.0;
      }

      if ((!(max_sig < mtmp)) || (b_mtmp < ERR2)) {
        if ((ERR2 > mtmp) || rtIsNaN(mtmp)) {
          ovitv[0] = ERR2;
        } else {
          ovitv[0] = mtmp;
        }

        if ((max_sig < b_mtmp) || rtIsNaN(b_mtmp)) {
          ovitv[1] = max_sig;
        } else {
          ovitv[1] = b_mtmp;
        }
      }

      ERR2 = (ovitv[1] - ovitv[0]) / (b_mtmp - mtmp);

      /* ---------(E) check sutability -------- */
      (*SC)++;
    }
  }
}

/* End of code generation (SigFit.c) */
