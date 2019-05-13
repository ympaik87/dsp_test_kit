/*
 * Coder_SigFit_par2.c
 *
 * Code generation for function 'Coder_SigFit_par2'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_SigFit_par2.h"
#include "Coder_sig.h"
#include "Coder_SigFitter_2para_part1.h"

/* Function Definitions */
void Coder_SigFit_par2(const double x_data[], const int x_size[1], const double
  ABSD_data[], double *result, double EC, const double ini_param[4], const
  double fixed_pt[2], double SFC, const double perturbation_data[], double
  param[4], double f_data[], int f_size[1], double *SC)
{
  int i84;
  int ABSD_size_tmp;
  int i85;
  int i86;
  int x_size_tmp;
  int b_x_size[1];
  double b_x_data[97];
  int ABSD_size[1];
  double b_ABSD_data[97];
  double unusedU0;
  double state;
  int i87;
  int c_x_size[1];
  int b_ABSD_size[1];
  *SC = SFC;
  if (SFC > EC) {
    i84 = 0;
    ABSD_size_tmp = 0;
    i85 = 0;
    i86 = 0;
  } else {
    i84 = (int)SFC - 1;
    ABSD_size_tmp = (int)EC;
    i85 = (int)SFC - 1;
    i86 = (int)EC;
  }

  x_size_tmp = ABSD_size_tmp - i84;
  b_x_size[0] = x_size_tmp;
  for (ABSD_size_tmp = 0; ABSD_size_tmp < x_size_tmp; ABSD_size_tmp++) {
    b_x_data[ABSD_size_tmp] = x_data[i84 + ABSD_size_tmp];
  }

  ABSD_size_tmp = i86 - i85;
  ABSD_size[0] = ABSD_size_tmp;
  for (i84 = 0; i84 < ABSD_size_tmp; i84++) {
    b_ABSD_data[i84] = ABSD_data[i85 + i84];
  }

  Coder_SigFitter_2para_part1(b_x_data, b_x_size, b_ABSD_data, ABSD_size,
    ini_param, fixed_pt, param, &unusedU0, &state);
  if ((state == 0.0) || (fabs(param[3]) > 2.0)) {
    if (SFC > EC) {
      i84 = 0;
      ABSD_size_tmp = 0;
      i85 = 0;
      i86 = 0;
      i87 = 0;
    } else {
      i84 = (int)SFC - 1;
      ABSD_size_tmp = (int)EC;
      i85 = (int)SFC - 1;
      i86 = (int)EC;
      i87 = (int)SFC - 1;
    }

    x_size_tmp = ABSD_size_tmp - i84;
    c_x_size[0] = x_size_tmp;
    for (ABSD_size_tmp = 0; ABSD_size_tmp < x_size_tmp; ABSD_size_tmp++) {
      b_x_data[ABSD_size_tmp] = x_data[i84 + ABSD_size_tmp];
    }

    ABSD_size_tmp = i86 - i85;
    b_ABSD_size[0] = ABSD_size_tmp;
    for (i84 = 0; i84 < ABSD_size_tmp; i84++) {
      b_ABSD_data[i84] = ABSD_data[i85 + i84] + perturbation_data[i87 + i84];
    }

    Coder_SigFitter_2para_part1(b_x_data, c_x_size, b_ABSD_data, b_ABSD_size,
      ini_param, fixed_pt, param, &unusedU0, &state);
  }

  if ((state == 0.0) || (fabs(param[3]) > 2.0)) {
    *result = 3.0;
  }

  Coder_sig(param, x_data, x_size, f_data, f_size);
}

/* End of code generation (Coder_SigFit_par2.c) */
