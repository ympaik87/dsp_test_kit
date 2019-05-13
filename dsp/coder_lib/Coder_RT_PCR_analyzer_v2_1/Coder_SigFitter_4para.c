/*
 * Coder_SigFitter_4para.c
 *
 * Code generation for function 'Coder_SigFitter_4para'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_SigFitter_4para.h"
#include "all.h"
#include "isfinite.h"
#include "norm.h"
#include "Coder_sig.h"
#include "Coder_analytical_inverse.h"
#include "Coder_getjacobian_4para.h"

/* Function Definitions */
void Coder_SigFitter_4para(const double x_data[], const int x_size[1], const
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
  double J2_diag[16];
  int b_iter;
  boolean_T exitg1;
  double param_old[4];
  double sse_old;
  double J_data[400];
  int J_size[2];
  int a_tmp_size_idx_1;
  int a_tmp_data_tmp;
  double a_tmp_data[400];
  double J2[16];
  int boffset;
  int k;
  double y_idx_1;
  int aoffset;
  double y_idx_2;
  double y_idx_3;
  double b_J2[16];
  double dv0[16];
  double step[4];
  double d3;
  boolean_T exitg2;
  boolean_T bv0[4];

  /* http://www.brnt.eu/phd/node10.html */
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

  memset(&J2_diag[0], 0, sizeof(double) << 4);
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
    Coder_getjacobian_4para(param, x_data, x_size, J_data, J_size);
    a_tmp_size_idx_1 = J_size[0];
    inner = J_size[0];
    for (coffset = 0; coffset < inner; coffset++) {
      a_tmp_data_tmp = coffset << 2;
      a_tmp_data[a_tmp_data_tmp] = J_data[coffset];
      a_tmp_data[1 + a_tmp_data_tmp] = J_data[coffset + J_size[0]];
      a_tmp_data[2 + a_tmp_data_tmp] = J_data[coffset + (J_size[0] << 1)];
      a_tmp_data[3 + a_tmp_data_tmp] = J_data[coffset + J_size[0] * 3];
    }

    if (J_size[0] == 1) {
      for (coffset = 0; coffset < 4; coffset++) {
        J2[coffset] = 0.0;
        for (inner = 0; inner < 1; inner++) {
          J2[coffset] += a_tmp_data[coffset] * J_data[0];
        }

        J2[coffset + 4] = 0.0;
        for (inner = 0; inner < 1; inner++) {
          J2[coffset + 4] += a_tmp_data[coffset] * J_data[1];
        }

        J2[coffset + 8] = 0.0;
        for (inner = 0; inner < 1; inner++) {
          J2[coffset + 8] += a_tmp_data[coffset] * J_data[2];
        }

        J2[coffset + 12] = 0.0;
        for (inner = 0; inner < 1; inner++) {
          J2[coffset + 12] += a_tmp_data[coffset] * J_data[3];
        }
      }
    } else {
      inner = J_size[0];
      for (a_tmp_data_tmp = 0; a_tmp_data_tmp < 4; a_tmp_data_tmp++) {
        coffset = a_tmp_data_tmp << 2;
        boffset = a_tmp_data_tmp * inner;
        J2[coffset] = 0.0;
        J2[coffset + 1] = 0.0;
        J2[coffset + 2] = 0.0;
        J2[coffset + 3] = 0.0;
        for (k = 0; k < inner; k++) {
          aoffset = k << 2;
          sse = J_data[boffset + k];
          J2[coffset] += sse * a_tmp_data[aoffset];
          J2[coffset + 1] += sse * a_tmp_data[aoffset + 1];
          J2[coffset + 2] += sse * a_tmp_data[aoffset + 2];
          J2[coffset + 3] += sse * a_tmp_data[aoffset + 3];
        }
      }
    }

    J2_diag[0] = J2[0];
    J2_diag[5] = J2[5];
    J2_diag[10] = J2[10];
    J2_diag[15] = J2[15];
    if ((J_size[0] == 1) || (r_size[0] == 1)) {
      inner = J_size[0];
      sse = 0.0;
      for (coffset = 0; coffset < inner; coffset++) {
        sse += a_tmp_data[coffset << 2] * r_data[coffset];
      }

      y_idx_1 = 0.0;
      for (coffset = 0; coffset < inner; coffset++) {
        y_idx_1 += a_tmp_data[1 + (coffset << 2)] * r_data[coffset];
      }

      y_idx_2 = 0.0;
      for (coffset = 0; coffset < inner; coffset++) {
        y_idx_2 += a_tmp_data[2 + (coffset << 2)] * r_data[coffset];
      }

      y_idx_3 = 0.0;
      for (coffset = 0; coffset < inner; coffset++) {
        y_idx_3 += a_tmp_data[3 + (coffset << 2)] * r_data[coffset];
      }
    } else {
      inner = J_size[0];
      sse = 0.0;
      y_idx_1 = 0.0;
      y_idx_2 = 0.0;
      y_idx_3 = 0.0;
      for (k = 0; k < inner; k++) {
        aoffset = k << 2;
        sse += r_data[k] * a_tmp_data[aoffset];
        y_idx_1 += r_data[k] * a_tmp_data[aoffset + 1];
        y_idx_2 += r_data[k] * a_tmp_data[aoffset + 2];
        y_idx_3 += r_data[k] * a_tmp_data[aoffset + 3];
      }
    }

    for (coffset = 0; coffset < 16; coffset++) {
      b_J2[coffset] = J2[coffset] + J2_diag[coffset] * lambda;
    }

    Coder_analytical_inverse(b_J2, dv0);

    /*      step=LinSysSolver_using_LUdcp(J2+lambda_diag,J'*r,p); */
    /*  step=[J; sqrt(lambda_diag)]\[r; zeros(p,1)]; */
    for (coffset = 0; coffset < 4; coffset++) {
      step[coffset] = 0.0;
      d3 = ((dv0[coffset] * sse + dv0[coffset + 4] * y_idx_1) + dv0[coffset + 8]
            * y_idx_2) + dv0[coffset + 12] * y_idx_3;
      step[coffset] = d3;
      param[coffset] += d3;
    }

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

      /*          'way1' */
    } else {
      /*          'way2' */
      exitg2 = false;
      while ((!exitg2) && (sse > sse_old)) {
        lambda *= 10.0;
        if (lambda > 1.0E+16) {
          breakOut = true;
          exitg2 = true;
        } else {
          if ((a_tmp_size_idx_1 == 1) || (r_size[0] == 1)) {
            sse = 0.0;
            for (coffset = 0; coffset < a_tmp_size_idx_1; coffset++) {
              sse += a_tmp_data[coffset << 2] * r_data[coffset];
            }

            y_idx_1 = 0.0;
            for (coffset = 0; coffset < a_tmp_size_idx_1; coffset++) {
              y_idx_1 += a_tmp_data[1 + (coffset << 2)] * r_data[coffset];
            }

            y_idx_2 = 0.0;
            for (coffset = 0; coffset < a_tmp_size_idx_1; coffset++) {
              y_idx_2 += a_tmp_data[2 + (coffset << 2)] * r_data[coffset];
            }

            y_idx_3 = 0.0;
            for (coffset = 0; coffset < a_tmp_size_idx_1; coffset++) {
              y_idx_3 += a_tmp_data[3 + (coffset << 2)] * r_data[coffset];
            }
          } else {
            sse = 0.0;
            y_idx_1 = 0.0;
            y_idx_2 = 0.0;
            y_idx_3 = 0.0;
            for (k = 0; k < a_tmp_size_idx_1; k++) {
              aoffset = k << 2;
              sse += r_data[k] * a_tmp_data[aoffset];
              y_idx_1 += r_data[k] * a_tmp_data[aoffset + 1];
              y_idx_2 += r_data[k] * a_tmp_data[aoffset + 2];
              y_idx_3 += r_data[k] * a_tmp_data[aoffset + 3];
            }
          }

          for (coffset = 0; coffset < 16; coffset++) {
            b_J2[coffset] = J2[coffset] + J2_diag[coffset] * lambda;
          }

          Coder_analytical_inverse(b_J2, dv0);

          /*              step=LinSysSolver_using_LUdcp(J2+lambda_diag,J'*r,p); */
          for (coffset = 0; coffset < 4; coffset++) {
            step[coffset] = 0.0;
            d3 = ((dv0[coffset] * sse + dv0[coffset + 4] * y_idx_1) +
                  dv0[coffset + 8] * y_idx_2) + dv0[coffset + 12] * y_idx_3;
            step[coffset] = d3;
            param[coffset] = param_old[coffset] + d3;
          }

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

    /*      iter */
    /*      ['sse_old: ' num2str(sse_old)] */
    /*      ['sse: ' num2str(sse)]  */
    /*      ['|sse-sse_old|: ' num2str(abs(sse-sse_old)) ', tol*sse:' num2str(tol*sse)]  */
    if ((b_norm(step) < 1.0E-8 * (1.4901161193847656E-8 + b_norm(param))) ||
        (fabs(sse - sse_old) <= 1.0E-8 * sse)) {
      /*          'step' */
      /*          setp */
      /*          'sse' */
      /*          sse */
      exitg1 = true;
    } else if (breakOut) {
      /* 정상계산실패하면 */
      /*          'c' */
      *state = 0.0;
      exitg1 = true;
    } else {
      b_isfinite(step, bv0);
      if (!all(bv0)) {
        /* 정상계산실패하면 */
        *state = 0.0;
        exitg1 = true;
      } else {
        b_iter++;
      }
    }
  }
}

/* End of code generation (Coder_SigFitter_4para.c) */
