/*
 * Coder_SigFitter_3para.c
 *
 * Code generation for function 'Coder_SigFitter_3para'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_SigFitter_3para.h"
#include "all.h"
#include "isfinite.h"
#include "norm.h"
#include "Coder_sig.h"
#include "Coder_analytical_inverse.h"
#include "Coder_getjacobian_3para.h"

/* Function Definitions */
void Coder_SigFitter_3para(const double x_data[], const int x_size[1], const
  double y_data[], const int y_size[1], const double param0[4], double param[4],
  double *iter, double *state)
{
  double lambda;
  boolean_T breakOut;
  double r_data[100];
  int r_size[1];
  int inner;
  int coffset;
  double a_data[100];
  double sse;
  double J2_diag[9];
  int b_iter;
  boolean_T exitg1;
  double param_old[4];
  double sse_old;
  double J_data[300];
  int J_size[2];
  int a_tmp_size_idx_1;
  double a_tmp_data[300];
  int j;
  int boffset;
  double J2[9];
  int k;
  double y[3];
  int aoffset;
  double b_J2[9];
  double dv3[9];
  double step[3];
  boolean_T exitg2;
  boolean_T bv3[3];
  lambda = 0.01;

  /* eps=2.220446049250313e-16 */
  breakOut = false;
  *state = 1.0;
  param[0] = param0[0];
  param[1] = param0[1];
  param[2] = param0[2];
  param[3] = param0[3];
  Coder_sig(param0, x_data, x_size, r_data, r_size);
  r_size[0] = y_size[0];
  inner = y_size[0];
  for (coffset = 0; coffset < inner; coffset++) {
    r_data[coffset] = y_data[coffset] - r_data[coffset];
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  if (0 <= y_size[0] - 1) {
    memcpy(&a_data[0], &r_data[0], (unsigned int)(y_size[0] * (int)sizeof(double)));
  }

  if (y_size[0] == 1) {
    sse = 0.0;
    for (coffset = 0; coffset < 1; coffset++) {
      sse += a_data[0] * r_data[0];
    }
  } else {
    sse = 0.0;
    inner = y_size[0];
    for (coffset = 0; coffset < inner; coffset++) {
      sse += a_data[coffset] * r_data[coffset];
    }
  }

  memset(&J2_diag[0], 0, 9U * sizeof(double));
  *iter = 1.0;
  b_iter = 0;
  exitg1 = false;
  while ((!exitg1) && (b_iter < 200)) {
    *iter = 1.0 + (double)b_iter;
    param_old[0] = param[0];
    param_old[1] = param[1];
    param_old[2] = param[2];
    param_old[3] = param[3];
    sse_old = sse;
    Coder_getjacobian_3para(param, x_data, x_size, J_data, J_size);
    a_tmp_size_idx_1 = J_size[0];
    inner = J_size[0];
    for (coffset = 0; coffset < inner; coffset++) {
      a_tmp_data[3 * coffset] = J_data[coffset];
      a_tmp_data[1 + 3 * coffset] = J_data[coffset + J_size[0]];
      a_tmp_data[2 + 3 * coffset] = J_data[coffset + (J_size[0] << 1)];
    }

    if (J_size[0] == 1) {
      for (coffset = 0; coffset < 3; coffset++) {
        for (boffset = 0; boffset < 3; boffset++) {
          inner = coffset + 3 * boffset;
          J2[inner] = 0.0;
          for (j = 0; j < 1; j++) {
            J2[inner] += a_tmp_data[coffset] * J_data[boffset];
          }
        }
      }
    } else {
      inner = J_size[0];
      for (j = 0; j < 3; j++) {
        coffset = j * 3;
        boffset = j * inner;
        J2[coffset] = 0.0;
        J2[coffset + 1] = 0.0;
        J2[coffset + 2] = 0.0;
        for (k = 0; k < inner; k++) {
          aoffset = k * 3;
          sse = J_data[boffset + k];
          J2[coffset] += sse * a_tmp_data[aoffset];
          J2[coffset + 1] += sse * a_tmp_data[aoffset + 1];
          J2[coffset + 2] += sse * a_tmp_data[aoffset + 2];
        }
      }
    }

    J2_diag[0] = J2[0];
    J2_diag[4] = J2[4];
    J2_diag[8] = J2[8];
    if ((J_size[0] == 1) || (r_size[0] == 1)) {
      inner = J_size[0];
      for (coffset = 0; coffset < 3; coffset++) {
        y[coffset] = 0.0;
        for (boffset = 0; boffset < inner; boffset++) {
          y[coffset] += a_tmp_data[coffset + 3 * boffset] * r_data[boffset];
        }
      }
    } else {
      inner = J_size[0];
      y[0] = 0.0;
      y[1] = 0.0;
      y[2] = 0.0;
      for (k = 0; k < inner; k++) {
        aoffset = k * 3;
        y[0] += r_data[k] * a_tmp_data[aoffset];
        y[1] += r_data[k] * a_tmp_data[aoffset + 1];
        y[2] += r_data[k] * a_tmp_data[aoffset + 2];
      }
    }

    for (coffset = 0; coffset < 9; coffset++) {
      b_J2[coffset] = J2[coffset] + J2_diag[coffset] * lambda;
    }

    c_Coder_analytical_inverse(b_J2, dv3);
    for (coffset = 0; coffset < 3; coffset++) {
      step[coffset] = 0.0;
      sse = (dv3[coffset] * y[0] + dv3[coffset + 3] * y[1]) + dv3[coffset + 6] *
        y[2];
      step[coffset] = sse;
      param[1 + coffset] += sse;
    }

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Coder_sig(param, x_data, x_size, r_data, r_size);
    r_size[0] = y_size[0];
    inner = y_size[0];
    for (coffset = 0; coffset < inner; coffset++) {
      r_data[coffset] = y_data[coffset] - r_data[coffset];
    }

    if (0 <= y_size[0] - 1) {
      memcpy(&a_data[0], &r_data[0], (unsigned int)(y_size[0] * (int)sizeof
              (double)));
    }

    if (y_size[0] == 1) {
      sse = 0.0;
      for (coffset = 0; coffset < 1; coffset++) {
        sse += a_data[0] * r_data[0];
      }
    } else {
      sse = 0.0;
      inner = y_size[0];
      for (coffset = 0; coffset < inner; coffset++) {
        sse += a_data[coffset] * r_data[coffset];
      }
    }

    if (sse < sse_old) {
      lambda *= 0.1;
      if (!(lambda > 2.2204460492503131E-16)) {
        lambda = 2.2204460492503131E-16;
      }
    } else {
      exitg2 = false;
      while ((!exitg2) && (sse > sse_old)) {
        lambda *= 10.0;
        if (lambda > 1.0E+16) {
          breakOut = true;
          exitg2 = true;
        } else {
          if ((a_tmp_size_idx_1 == 1) || (r_size[0] == 1)) {
            for (coffset = 0; coffset < 3; coffset++) {
              y[coffset] = 0.0;
              for (boffset = 0; boffset < a_tmp_size_idx_1; boffset++) {
                y[coffset] += a_tmp_data[coffset + 3 * boffset] * r_data[boffset];
              }
            }
          } else {
            y[0] = 0.0;
            y[1] = 0.0;
            y[2] = 0.0;
            for (k = 0; k < a_tmp_size_idx_1; k++) {
              aoffset = k * 3;
              y[0] += r_data[k] * a_tmp_data[aoffset];
              y[1] += r_data[k] * a_tmp_data[aoffset + 1];
              y[2] += r_data[k] * a_tmp_data[aoffset + 2];
            }
          }

          for (coffset = 0; coffset < 9; coffset++) {
            b_J2[coffset] = J2[coffset] + J2_diag[coffset] * lambda;
          }

          c_Coder_analytical_inverse(b_J2, dv3);
          for (coffset = 0; coffset < 3; coffset++) {
            step[coffset] = 0.0;
            sse = (dv3[coffset] * y[0] + dv3[coffset + 3] * y[1]) + dv3[coffset
              + 6] * y[2];
            step[coffset] = sse;
            param[1 + coffset] = param_old[1 + coffset] + sse;
          }

          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          Coder_sig(param, x_data, x_size, r_data, r_size);
          r_size[0] = y_size[0];
          inner = y_size[0];
          for (coffset = 0; coffset < inner; coffset++) {
            r_data[coffset] = y_data[coffset] - r_data[coffset];
          }

          if (0 <= y_size[0] - 1) {
            memcpy(&a_data[0], &r_data[0], (unsigned int)(y_size[0] * (int)
                    sizeof(double)));
          }

          if (y_size[0] == 1) {
            sse = 0.0;
            for (coffset = 0; coffset < 1; coffset++) {
              sse += a_data[0] * r_data[0];
            }
          } else {
            sse = 0.0;
            inner = y_size[0];
            for (coffset = 0; coffset < inner; coffset++) {
              sse += a_data[coffset] * r_data[coffset];
            }
          }
        }
      }
    }

    if ((d_norm(step) < 1.0E-8 * (1.4901161193847656E-8 + d_norm(*(double (*)[3])
           &param[1]))) || (fabs(sse - sse_old) <= 1.0E-8 * sse)) {
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
      exitg1 = true;
    } else if (breakOut) {
      /* 정상계산실패하면 */
      *state = 0.0;
      exitg1 = true;
    } else {
      d_isfinite(step, bv3);
      if (!c_all(bv3)) {
        /* 정상계산실패하면 */
        *state = 0.0;
        exitg1 = true;
      } else {
        b_iter++;
      }
    }
  }
}

/* End of code generation (Coder_SigFitter_3para.c) */
