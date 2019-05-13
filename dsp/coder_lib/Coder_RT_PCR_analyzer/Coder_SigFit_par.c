/*
 * Coder_SigFit_par.c
 *
 * Code generation for function 'Coder_SigFit_par'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_SigFit_par.h"
#include "Coder_sig.h"
#include "Coder_SigFitter_3para.h"

/* Function Definitions */
void Coder_SigFit_par(const double x_data[], const int x_size[1], const double
                      ABSD_data[], double *result, double EC, const double
                      ini_param[4], double SFC, double MFC2, const double
                      perturbation_data[], double param[4], double f_data[], int
                      f_size[1], double *SC)
{
  double ERR;
  double ERR2;
  double state;
  boolean_T exitg1;
  int i82;
  int ABSD_size_tmp;
  int i83;
  int i84;
  int x_size_tmp;
  int b_x_size[1];
  double b_x_data[100];
  int ABSD_size[1];
  double b_ABSD_data[100];
  int i85;
  double max_sig;
  int c_x_size[1];
  double min_ABSD;
  int b_ABSD_size[1];
  double max_ABSD;
  double ovitv_idx_0;
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
  *SC = SFC;
  state = 0.0;
  exitg1 = false;
  while ((!exitg1) && ((ERR < 0.5) || (ERR > 1.5) || (ERR2 < 0.5) || (state ==
           0.0))) {
    if (*SC > MFC2) {
      *result = 3.0;
      exitg1 = true;
    } else {
      if (*SC > EC) {
        i82 = 0;
        ABSD_size_tmp = 0;
        i83 = 0;
        i84 = 0;
      } else {
        i82 = (int)*SC - 1;
        ABSD_size_tmp = (int)EC;
        i83 = (int)*SC - 1;
        i84 = (int)EC;
      }

      x_size_tmp = ABSD_size_tmp - i82;
      b_x_size[0] = x_size_tmp;
      for (ABSD_size_tmp = 0; ABSD_size_tmp < x_size_tmp; ABSD_size_tmp++) {
        b_x_data[ABSD_size_tmp] = x_data[i82 + ABSD_size_tmp];
      }

      ABSD_size_tmp = i84 - i83;
      ABSD_size[0] = ABSD_size_tmp;
      for (i82 = 0; i82 < ABSD_size_tmp; i82++) {
        b_ABSD_data[i82] = ABSD_data[i83 + i82];
      }

      Coder_SigFitter_3para(b_x_data, b_x_size, b_ABSD_data, ABSD_size,
                            ini_param, param, &ERR2, &state);
      if (fabs(param[3]) > 2.0) {
        if (*SC > EC) {
          i82 = 0;
          ABSD_size_tmp = 0;
          i83 = 0;
          i84 = 0;
          i85 = 0;
        } else {
          i82 = (int)*SC - 1;
          ABSD_size_tmp = (int)EC;
          i83 = (int)*SC - 1;
          i84 = (int)EC;
          i85 = (int)*SC - 1;
        }

        x_size_tmp = ABSD_size_tmp - i82;
        c_x_size[0] = x_size_tmp;
        for (ABSD_size_tmp = 0; ABSD_size_tmp < x_size_tmp; ABSD_size_tmp++) {
          b_x_data[ABSD_size_tmp] = x_data[i82 + ABSD_size_tmp];
        }

        ABSD_size_tmp = i84 - i83;
        b_ABSD_size[0] = ABSD_size_tmp;
        for (i82 = 0; i82 < ABSD_size_tmp; i82++) {
          b_ABSD_data[i82] = ABSD_data[i83 + i82] + perturbation_data[i85 + i82];
        }

        Coder_SigFitter_3para(b_x_data, c_x_size, b_ABSD_data, b_ABSD_size,
                              ini_param, param, &ERR2, &state);
      }

      Coder_sig(param, x_data, x_size, f_data, f_size);

      /* ---------(B) check suitability -------- */
      if ((f_data[(int)EC - 1] < f_data[0]) || rtIsNaN(f_data[0])) {
        ERR2 = f_data[(int)EC - 1];
      } else {
        ERR2 = f_data[0];
      }

      if ((f_data[(int)EC - 1] > f_data[0]) || rtIsNaN(f_data[0])) {
        max_sig = f_data[(int)EC - 1];
      } else {
        max_sig = f_data[0];
      }

      if ((ABSD_data[(int)EC - 1] < ini_param[0]) || rtIsNaN(ini_param[0])) {
        min_ABSD = ABSD_data[(int)EC - 1];
      } else {
        min_ABSD = ini_param[0];
      }

      if ((ABSD_data[(int)EC - 1] > ini_param[0]) || rtIsNaN(ini_param[0])) {
        max_ABSD = ABSD_data[(int)EC - 1];
      } else {
        max_ABSD = ini_param[0];
      }

      ERR = (max_sig - ERR2) / (max_ABSD - min_ABSD);
      if ((max_sig < min_ABSD) || (max_ABSD < ERR2)) {
        ovitv_idx_0 = 0.0;
        ERR2 = 0.0;
      } else {
        if ((ERR2 > min_ABSD) || rtIsNaN(min_ABSD)) {
          ovitv_idx_0 = ERR2;
        } else {
          ovitv_idx_0 = min_ABSD;
        }

        if ((max_sig < max_ABSD) || rtIsNaN(max_ABSD)) {
          ERR2 = max_sig;
        } else {
          ERR2 = max_ABSD;
        }
      }

      ERR2 = (ERR2 - ovitv_idx_0) / (max_ABSD - min_ABSD);

      /* ---------(E) check sutability --------         */
      (*SC)++;
    }
  }
}

/* End of code generation (Coder_SigFit_par.c) */
