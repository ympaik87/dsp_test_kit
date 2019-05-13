/*
 * Coder_SigFit.c
 *
 * Code generation for function 'Coder_SigFit'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_SigFit.h"
#include "Coder_sig.h"
#include "Coder_SigFitter_4para.h"

/* Function Definitions */
void Coder_SigFit(const double x_data[], const int x_size[1], const double
                  ABSD_data[], double *result, const double ini_param[4], double
                  *SC, double SFC, double HTC, double TC, const double
                  perturbation_data[], double param[4], double f_data[], int
                  f_size[1])
{
  double ERR;
  double ERR2;
  double state;
  boolean_T exitg1;
  int i59;
  int i60;
  int k;
  int ABSD_size_tmp;
  int idx;
  int b_x_size[1];
  double b_x_data[100];
  int ABSD_size[1];
  double b_ABSD_data[100];
  double min_sig;
  double max_sig;
  int i61;
  int c_x_size[1];
  double varargin_1_data[199];
  int b_ABSD_size[1];
  double min_ABSD;
  boolean_T exitg2;
  double max_ABSD;
  double ERR_tmp;
  param[0] = 0.0;
  param[1] = 0.0;
  param[2] = 0.0;
  param[3] = 0.0;
  f_size[0] = x_size[0];
  if (0 <= x_size[0] - 1) {
    memset(&f_data[0], 0, (unsigned int)(x_size[0] * (int)sizeof(double)));
  }

  ERR = 0.0;
  ERR2 = 0.0;
  state = 0.0;
  exitg1 = false;
  while ((!exitg1) && ((ERR < 0.5) || (ERR > 1.5) || (ERR2 < 0.5) || (state ==
           0.0))) {
    if (*SC > HTC) {
      *result = 3.0;
      exitg1 = true;
    } else {
      if (*SC > TC) {
        i59 = 0;
        i60 = 0;
      } else {
        i59 = (int)*SC - 1;
        i60 = (int)TC;
      }

      if (*SC > TC) {
        k = 0;
        ABSD_size_tmp = 0;
      } else {
        k = (int)*SC - 1;
        ABSD_size_tmp = (int)TC;
      }

      idx = i60 - i59;
      b_x_size[0] = idx;
      for (i60 = 0; i60 < idx; i60++) {
        b_x_data[i60] = x_data[i59 + i60];
      }

      ABSD_size_tmp -= k;
      ABSD_size[0] = ABSD_size_tmp;
      for (i59 = 0; i59 < ABSD_size_tmp; i59++) {
        b_ABSD_data[i59] = ABSD_data[k + i59];
      }

      Coder_SigFitter_4para(b_x_data, b_x_size, b_ABSD_data, ABSD_size,
                            ini_param, param, &ERR2, &state);
      if (fabs(param[3]) > 2.0) {
        if (*SC > TC) {
          i59 = 0;
          i60 = 0;
        } else {
          i59 = (int)*SC - 1;
          i60 = (int)TC;
        }

        if (*SC > TC) {
          k = 0;
          ABSD_size_tmp = 0;
        } else {
          k = (int)*SC - 1;
          ABSD_size_tmp = (int)TC;
        }

        if (*SC > TC) {
          i61 = 0;
        } else {
          i61 = (int)*SC - 1;
        }

        idx = i60 - i59;
        c_x_size[0] = idx;
        for (i60 = 0; i60 < idx; i60++) {
          b_x_data[i60] = x_data[i59 + i60];
        }

        ABSD_size_tmp -= k;
        b_ABSD_size[0] = ABSD_size_tmp;
        for (i59 = 0; i59 < ABSD_size_tmp; i59++) {
          b_ABSD_data[i59] = ABSD_data[k + i59] + perturbation_data[i61 + i59];
        }

        Coder_SigFitter_4para(b_x_data, c_x_size, b_ABSD_data, b_ABSD_size,
                              ini_param, param, &ERR2, &state);
      }

      Coder_sig(param, x_data, x_size, f_data, f_size);

      /* ---------(B) check suitability -------- */
      if ((f_data[(int)TC - 1] < f_data[0]) || rtIsNaN(f_data[0])) {
        min_sig = f_data[(int)TC - 1];
      } else {
        min_sig = f_data[0];
      }

      if ((f_data[(int)TC - 1] > f_data[0]) || rtIsNaN(f_data[0])) {
        max_sig = f_data[(int)TC - 1];
      } else {
        max_sig = f_data[0];
      }

      if (SFC > TC) {
        i59 = 1;
        i60 = 1;
      } else {
        i59 = (int)SFC;
        i60 = (int)TC + 1;
      }

      ABSD_size_tmp = i60 - i59;
      for (i60 = 0; i60 < ABSD_size_tmp; i60++) {
        varargin_1_data[i60] = ABSD_data[(i59 + i60) - 1];
      }

      if (ABSD_size_tmp <= 2) {
        if (ABSD_size_tmp == 1) {
          min_ABSD = ABSD_data[i59 - 1];
        } else if ((ABSD_data[i59 - 1] > ABSD_data[i59]) || (rtIsNaN
                    (ABSD_data[i59 - 1]) && (!rtIsNaN(ABSD_data[i59])))) {
          min_ABSD = ABSD_data[i59];
        } else {
          min_ABSD = ABSD_data[i59 - 1];
        }
      } else {
        if (!rtIsNaN(varargin_1_data[0])) {
          idx = 1;
        } else {
          idx = 0;
          k = 2;
          exitg2 = false;
          while ((!exitg2) && (k <= ABSD_size_tmp)) {
            if (!rtIsNaN(varargin_1_data[k - 1])) {
              idx = k;
              exitg2 = true;
            } else {
              k++;
            }
          }
        }

        if (idx == 0) {
          min_ABSD = ABSD_data[i59 - 1];
        } else {
          min_ABSD = varargin_1_data[idx - 1];
          i59 = idx + 1;
          for (k = i59; k <= ABSD_size_tmp; k++) {
            ERR2 = varargin_1_data[k - 1];
            if (min_ABSD > ERR2) {
              min_ABSD = ERR2;
            }
          }
        }
      }

      if (SFC > TC) {
        i59 = 1;
        i60 = 1;
      } else {
        i59 = (int)SFC;
        i60 = (int)TC + 1;
      }

      ABSD_size_tmp = i60 - i59;
      if (ABSD_size_tmp <= 2) {
        if (ABSD_size_tmp == 1) {
          max_ABSD = ABSD_data[i59 - 1];
        } else if ((ABSD_data[i59 - 1] < ABSD_data[i59]) || (rtIsNaN
                    (ABSD_data[i59 - 1]) && (!rtIsNaN(ABSD_data[i59])))) {
          max_ABSD = ABSD_data[i59];
        } else {
          max_ABSD = ABSD_data[i59 - 1];
        }
      } else {
        max_ABSD = ABSD_data[i59 - 1];
        if (!rtIsNaN(max_ABSD)) {
          idx = 1;
        } else {
          idx = 0;
          k = 2;
          exitg2 = false;
          while ((!exitg2) && (k <= ABSD_size_tmp)) {
            if (!rtIsNaN(ABSD_data[(i59 + k) - 2])) {
              idx = k;
              exitg2 = true;
            } else {
              k++;
            }
          }
        }

        if (idx != 0) {
          max_ABSD = ABSD_data[(i59 + idx) - 2];
          i60 = idx + 1;
          for (k = i60; k <= ABSD_size_tmp; k++) {
            ERR2 = ABSD_data[(i59 + k) - 2];
            if (max_ABSD < ERR2) {
              max_ABSD = ERR2;
            }
          }
        }
      }

      ERR_tmp = max_ABSD - min_ABSD;
      ERR = (max_sig - min_sig) / ERR_tmp;
      if ((max_sig < min_ABSD) || (max_ABSD < min_sig)) {
        min_sig = 0.0;
        ERR2 = 0.0;
      } else {
        if ((min_sig > min_ABSD) || rtIsNaN(min_ABSD)) {
        } else {
          min_sig = min_ABSD;
        }

        if ((max_sig < max_ABSD) || rtIsNaN(max_ABSD)) {
          ERR2 = max_sig;
        } else {
          ERR2 = max_ABSD;
        }
      }

      ERR2 = (ERR2 - min_sig) / ERR_tmp;

      /* ---------(E) check sutability -------- */
      (*SC)++;
    }
  }
}

/* End of code generation (Coder_SigFit.c) */
