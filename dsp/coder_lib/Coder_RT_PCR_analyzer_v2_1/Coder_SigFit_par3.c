/*
 * Coder_SigFit_par3.c
 *
 * Code generation for function 'Coder_SigFit_par3'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_SigFit_par3.h"
#include "Coder_sig.h"
#include "Coder_SigFitter_2para_part2.h"

/* Function Definitions */
void Coder_SigFit_par3(const double x_data[], const int x_size[1], const double
  ABSD_data[], double *result, const double *SC, const double ini_param[4],
  const double fixed_pt[2], double TC, const double perturbation_data[], double
  param[4], double f_data[], int f_size[1])
{
  double ERR;
  double ERR2;
  double EC;
  double state;
  boolean_T exitg1;
  int i88;
  int ABSD_size_tmp;
  int i89;
  int i90;
  int x_size_tmp;
  int b_x_size[1];
  double b_x_data[100];
  int ABSD_size[1];
  double b_ABSD_data[100];
  int i91;
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
  EC = TC;
  state = 0.0;
  exitg1 = false;
  while ((!exitg1) && ((ERR < 0.5) || (ERR > 1.5) || (ERR2 < 0.5) || (state ==
           0.0))) {
    if (EC < floor((*SC + TC) / 2.0)) {
      *result = 3.0;
      exitg1 = true;
    } else {
      /*      fprintf('fit_itv=[%s , %s]\n ', Double2String(SC), Double2String(EC)) */
      /*      fprintf('fixed_pt=[%s , %s]\n ', Double2String(fixed_pt(1)), Double2String(fixed_pt(2))) */
      /*      fprintf('x_val=%s ~ %s\n ', Double2String(x(SC)), Double2String(x(EC))) */
      /*      fprintf('ABSD_val=%s ~ %s\n ', Double2String(ABSD(SC)), Double2String(ABSD(EC))) */
      if (*SC > EC) {
        i88 = 0;
        ABSD_size_tmp = 0;
        i89 = 0;
        i90 = 0;
      } else {
        i88 = (int)*SC - 1;
        ABSD_size_tmp = (int)EC;
        i89 = (int)*SC - 1;
        i90 = (int)EC;
      }

      x_size_tmp = ABSD_size_tmp - i88;
      b_x_size[0] = x_size_tmp;
      for (ABSD_size_tmp = 0; ABSD_size_tmp < x_size_tmp; ABSD_size_tmp++) {
        b_x_data[ABSD_size_tmp] = x_data[i88 + ABSD_size_tmp];
      }

      ABSD_size_tmp = i90 - i89;
      ABSD_size[0] = ABSD_size_tmp;
      for (i88 = 0; i88 < ABSD_size_tmp; i88++) {
        b_ABSD_data[i88] = ABSD_data[i89 + i88];
      }

      Coder_SigFitter_2para_part2(b_x_data, b_x_size, b_ABSD_data, ABSD_size,
        ini_param, fixed_pt, param, &ERR2, &state);

      /*      fprintf('state=%s\n ', Double2String(state)) */
      if (fabs(param[3]) > 2.0) {
        if (*SC > EC) {
          i88 = 0;
          ABSD_size_tmp = 0;
          i89 = 0;
          i90 = 0;
          i91 = 0;
        } else {
          i88 = (int)*SC - 1;
          ABSD_size_tmp = (int)EC;
          i89 = (int)*SC - 1;
          i90 = (int)EC;
          i91 = (int)*SC - 1;
        }

        x_size_tmp = ABSD_size_tmp - i88;
        c_x_size[0] = x_size_tmp;
        for (ABSD_size_tmp = 0; ABSD_size_tmp < x_size_tmp; ABSD_size_tmp++) {
          b_x_data[ABSD_size_tmp] = x_data[i88 + ABSD_size_tmp];
        }

        ABSD_size_tmp = i90 - i89;
        b_ABSD_size[0] = ABSD_size_tmp;
        for (i88 = 0; i88 < ABSD_size_tmp; i88++) {
          b_ABSD_data[i88] = ABSD_data[i89 + i88] + perturbation_data[i91 + i88];
        }

        Coder_SigFitter_2para_part2(b_x_data, c_x_size, b_ABSD_data, b_ABSD_size,
          ini_param, fixed_pt, param, &ERR2, &state);
      }

      Coder_sig(param, x_data, x_size, f_data, f_size);

      /* ---------(B) check suitability -------- */
      if ((f_data[(int)TC - 1] < f_data[(int)*SC - 1]) || rtIsNaN(f_data[(int)*
           SC - 1])) {
        ERR2 = f_data[(int)TC - 1];
      } else {
        ERR2 = f_data[(int)*SC - 1];
      }

      if ((f_data[(int)TC - 1] > f_data[(int)*SC - 1]) || rtIsNaN(f_data[(int)*
           SC - 1])) {
        max_sig = f_data[(int)TC - 1];
      } else {
        max_sig = f_data[(int)*SC - 1];
      }

      if ((ABSD_data[(int)TC - 1] < fixed_pt[1]) || rtIsNaN(fixed_pt[1])) {
        min_ABSD = ABSD_data[(int)TC - 1];
      } else {
        min_ABSD = fixed_pt[1];
      }

      if ((ABSD_data[(int)TC - 1] > fixed_pt[1]) || rtIsNaN(fixed_pt[1])) {
        max_ABSD = ABSD_data[(int)TC - 1];
      } else {
        max_ABSD = fixed_pt[1];
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
      /*      fprintf('param=[ %s, ', Double2String(param(1))) */
      /*      for i=2:3 */
      /*          fprintf('%s, ', Double2String(param(i))) */
      /*      end */
      /*      fprintf('%s]\n ', Double2String(param(4))) */
      /*      fprintf('TC=%s\n ', Double2String(TC)) */
      /*      fprintf('SC=%s\n ', Double2String(SC)) */
      /*      fprintf('ERR=%s\n ', Double2String(ERR*10)) */
      /*      fprintf('ERR2=%s\n ', Double2String(ERR2*10)) */
      EC--;
    }
  }
}

/* End of code generation (Coder_SigFit_par3.c) */
