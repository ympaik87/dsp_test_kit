/*
 * Coder_SigFit_par2.c
 *
 * Code generation for function 'Coder_SigFit_par2'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_SigFit_par2.h"
#include "Coder_sig.h"
#include "Coder_SigFitter_2para_part1.h"

/* Function Definitions */
void Coder_SigFit_par2(const double x_data[], const int x_size[1], const double
  ABSD_data[], double *result, double EC, const double ini_param[4], const
  double fixed_pt[2], double SFC, const double perturbation_data[], double
  param[4], double f_data[], int f_size[1], double *SC)
{
  int i74;
  int ABSD_size_tmp;
  int i75;
  int i76;
  int x_size_tmp;
  int b_x_size[1];
  double b_x_data[97];
  int ABSD_size[1];
  double b_ABSD_data[97];
  double unusedU0;
  double state;
  int i77;
  int c_x_size[1];
  int b_ABSD_size[1];
  *SC = SFC;
  if (SFC > EC) {
    i74 = 0;
    ABSD_size_tmp = 0;
    i75 = 0;
    i76 = 0;
  } else {
    i74 = (int)SFC - 1;
    ABSD_size_tmp = (int)EC;
    i75 = (int)SFC - 1;
    i76 = (int)EC;
  }

  x_size_tmp = ABSD_size_tmp - i74;
  b_x_size[0] = x_size_tmp;
  for (ABSD_size_tmp = 0; ABSD_size_tmp < x_size_tmp; ABSD_size_tmp++) {
    b_x_data[ABSD_size_tmp] = x_data[i74 + ABSD_size_tmp];
  }

  ABSD_size_tmp = i76 - i75;
  ABSD_size[0] = ABSD_size_tmp;
  for (i74 = 0; i74 < ABSD_size_tmp; i74++) {
    b_ABSD_data[i74] = ABSD_data[i75 + i74];
  }

  Coder_SigFitter_2para_part1(b_x_data, b_x_size, b_ABSD_data, ABSD_size,
    ini_param, fixed_pt, param, &unusedU0, &state);
  if ((state == 0.0) || (fabs(param[3]) > 2.0)) {
    if (SFC > EC) {
      i74 = 0;
      ABSD_size_tmp = 0;
      i75 = 0;
      i76 = 0;
      i77 = 0;
    } else {
      i74 = (int)SFC - 1;
      ABSD_size_tmp = (int)EC;
      i75 = (int)SFC - 1;
      i76 = (int)EC;
      i77 = (int)SFC - 1;
    }

    x_size_tmp = ABSD_size_tmp - i74;
    c_x_size[0] = x_size_tmp;
    for (ABSD_size_tmp = 0; ABSD_size_tmp < x_size_tmp; ABSD_size_tmp++) {
      b_x_data[ABSD_size_tmp] = x_data[i74 + ABSD_size_tmp];
    }

    ABSD_size_tmp = i76 - i75;
    b_ABSD_size[0] = ABSD_size_tmp;
    for (i74 = 0; i74 < ABSD_size_tmp; i74++) {
      b_ABSD_data[i74] = ABSD_data[i75 + i74] + perturbation_data[i77 + i74];
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
