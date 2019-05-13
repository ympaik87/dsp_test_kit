/*
 * Coder_SigFitter_2para_part1.c
 *
 * Code generation for function 'Coder_SigFitter_2para_part1'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_SigFitter_2para_part1.h"
#include "power.h"
#include "all.h"
#include "isfinite.h"
#include "norm.h"
#include "Coder_sig_part1.h"
#include "Coder_analytical_inverse.h"
#include "Coder_getjacobian_par2.h"
#include "Coder_RT_PCR_analyzer_rtwutil.h"

/* Function Definitions */
void Coder_SigFitter_2para_part1(const double x_data[], const int x_size[1],
  const double y_data[], const int y_size[1], const double param0[4], const
  double fixed_pt[2], double param[4], double *iter, double *state)
{
  double lambda;
  boolean_T breakOut;
  double b_param[4];
  double r_data[97];
  int r_size[1];
  int aoffset;
  int i24;
  double a_data[100];
  double sse;
  int b_iter;
  boolean_T exitg1;
  double param_old[4];
  double sse_old;
  double J_data[194];
  int J_size[2];
  int a_tmp_size_idx_1;
  int inner;
  double J2[4];
  double a_tmp_data[200];
  int k;
  double y_idx_1;
  double b_J2[4];
  double dv1[4];
  double d6;
  double step[2];
  boolean_T exitg2;
  boolean_T bv1[2];
  lambda = 0.01;

  /* eps=2.220446049250313e-16 */
  breakOut = false;
  *state = 1.0;
  b_param[0] = param0[0];
  b_param[1] = param0[1];
  b_param[2] = param0[2];
  b_param[3] = param0[3];
  Coder_sig_part1(param0, x_data, x_size, fixed_pt, r_data, r_size);
  r_size[0] = y_size[0];
  aoffset = y_size[0];
  for (i24 = 0; i24 < aoffset; i24++) {
    r_data[i24] = y_data[i24] - r_data[i24];
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  if (0 <= y_size[0] - 1) {
    memcpy(&a_data[0], &r_data[0], (unsigned int)(y_size[0] * (int)sizeof(double)));
  }

  if (y_size[0] == 1) {
    sse = 0.0;
    for (i24 = 0; i24 < 1; i24++) {
      sse += a_data[0] * r_data[0];
    }
  } else {
    sse = 0.0;
    aoffset = y_size[0];
    for (i24 = 0; i24 < aoffset; i24++) {
      sse += a_data[i24] * r_data[i24];
    }
  }

  *iter = 1.0;
  b_iter = 0;
  exitg1 = false;
  while ((!exitg1) && (b_iter < 200)) {
    *iter = 1.0 + (double)b_iter;
    param_old[2] = b_param[2];
    param_old[3] = b_param[3];
    sse_old = sse;
    Coder_getjacobian_par2(b_param, x_data, x_size, fixed_pt, J_data, J_size);
    a_tmp_size_idx_1 = J_size[0];
    aoffset = J_size[0];
    for (i24 = 0; i24 < aoffset; i24++) {
      inner = i24 << 1;
      a_tmp_data[inner] = J_data[i24];
      a_tmp_data[1 + inner] = J_data[i24 + J_size[0]];
    }

    if (J_size[0] == 1) {
      J2[0] = 0.0;
      for (i24 = 0; i24 < 1; i24++) {
        J2[0] += a_tmp_data[0] * J_data[0];
      }

      J2[2] = 0.0;
      for (i24 = 0; i24 < 1; i24++) {
        J2[2] += a_tmp_data[0] * J_data[1];
      }

      J2[1] = 0.0;
      for (i24 = 0; i24 < 1; i24++) {
        J2[1] += a_tmp_data[1] * J_data[0];
      }

      J2[3] = 0.0;
      for (i24 = 0; i24 < 1; i24++) {
        J2[3] += a_tmp_data[1] * J_data[1];
      }
    } else {
      inner = J_size[0];
      J2[0] = 0.0;
      J2[1] = 0.0;
      for (k = 0; k < inner; k++) {
        aoffset = k << 1;
        J2[0] += J_data[k] * a_tmp_data[aoffset];
        J2[1] += J_data[k] * a_tmp_data[aoffset + 1];
      }

      J2[2] = 0.0;
      J2[3] = 0.0;
      for (k = 0; k < inner; k++) {
        i24 = k << 1;
        sse = J_data[inner + k];
        J2[2] += sse * a_tmp_data[i24];
        J2[3] += sse * a_tmp_data[i24 + 1];
      }
    }

    if ((J_size[0] == 1) || (r_size[0] == 1)) {
      aoffset = J_size[0];
      sse = 0.0;
      for (i24 = 0; i24 < aoffset; i24++) {
        sse += a_tmp_data[i24 << 1] * r_data[i24];
      }

      y_idx_1 = 0.0;
      for (i24 = 0; i24 < aoffset; i24++) {
        y_idx_1 += a_tmp_data[1 + (i24 << 1)] * r_data[i24];
      }
    } else {
      inner = J_size[0];
      sse = 0.0;
      y_idx_1 = 0.0;
      for (k = 0; k < inner; k++) {
        aoffset = k << 1;
        sse += r_data[k] * a_tmp_data[aoffset];
        y_idx_1 += r_data[k] * a_tmp_data[aoffset + 1];
      }
    }

    b_J2[0] = J2[0] + J2[0] * lambda;
    b_J2[1] = J2[1] + 0.0 * lambda;
    b_J2[2] = J2[2] + 0.0 * lambda;
    b_J2[3] = J2[3] + J2[3] * lambda;
    b_Coder_analytical_inverse(b_J2, dv1);

    /*      step=LinSysSolver_using_LUdcp(J2+lambda_diag,J'*r,p); */
    d6 = dv1[0] * sse + dv1[2] * y_idx_1;
    step[0] = d6;
    b_param[2] += d6;
    d6 = dv1[1] * sse + dv1[3] * y_idx_1;
    step[1] = d6;
    b_param[3] += d6;

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Coder_sig_part1(b_param, x_data, x_size, fixed_pt, r_data, r_size);
    r_size[0] = y_size[0];
    aoffset = y_size[0];
    for (i24 = 0; i24 < aoffset; i24++) {
      r_data[i24] = y_data[i24] - r_data[i24];
    }

    if (0 <= y_size[0] - 1) {
      memcpy(&a_data[0], &r_data[0], (unsigned int)(y_size[0] * (int)sizeof
              (double)));
    }

    if (y_size[0] == 1) {
      sse = 0.0;
      for (i24 = 0; i24 < 1; i24++) {
        sse += a_data[0] * r_data[0];
      }
    } else {
      sse = 0.0;
      aoffset = y_size[0];
      for (i24 = 0; i24 < aoffset; i24++) {
        sse += a_data[i24] * r_data[i24];
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
            sse = 0.0;
            for (i24 = 0; i24 < a_tmp_size_idx_1; i24++) {
              sse += a_tmp_data[i24 << 1] * r_data[i24];
            }

            y_idx_1 = 0.0;
            for (i24 = 0; i24 < a_tmp_size_idx_1; i24++) {
              y_idx_1 += a_tmp_data[1 + (i24 << 1)] * r_data[i24];
            }
          } else {
            sse = 0.0;
            y_idx_1 = 0.0;
            for (k = 0; k < a_tmp_size_idx_1; k++) {
              aoffset = k << 1;
              sse += r_data[k] * a_tmp_data[aoffset];
              y_idx_1 += r_data[k] * a_tmp_data[aoffset + 1];
            }
          }

          b_J2[0] = J2[0] + J2[0] * lambda;
          b_J2[1] = J2[1];
          b_J2[2] = J2[2];
          b_J2[3] = J2[3] + J2[3] * lambda;
          b_Coder_analytical_inverse(b_J2, dv1);

          /*              step=LinSysSolver_using_LUdcp(J2+lambda_diag,J'*r,p); */
          d6 = dv1[0] * sse + dv1[2] * y_idx_1;
          step[0] = d6;
          b_param[2] = param_old[2] + d6;
          d6 = dv1[1] * sse + dv1[3] * y_idx_1;
          step[1] = d6;
          b_param[3] = param_old[3] + d6;

          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          Coder_sig_part1(b_param, x_data, x_size, fixed_pt, r_data, r_size);
          r_size[0] = y_size[0];
          aoffset = y_size[0];
          for (i24 = 0; i24 < aoffset; i24++) {
            r_data[i24] = y_data[i24] - r_data[i24];
          }

          if (0 <= y_size[0] - 1) {
            memcpy(&a_data[0], &r_data[0], (unsigned int)(y_size[0] * (int)
                    sizeof(double)));
          }

          if (y_size[0] == 1) {
            sse = 0.0;
            for (i24 = 0; i24 < 1; i24++) {
              sse += a_data[0] * r_data[0];
            }
          } else {
            sse = 0.0;
            aoffset = y_size[0];
            for (i24 = 0; i24 < aoffset; i24++) {
              sse += a_data[i24] * r_data[i24];
            }
          }
        }
      }
    }

    /*          iter */
    /*      ['sse_old: ' num2str(sse_old)] */
    /*      ['sse: ' num2str(sse)]  */
    /*      ['|sse-sse_old|: ' num2str(abs(sse-sse_old)) ', tol*sse:' num2str(tol*sse)]  */
    if ((c_norm(step) < 1.0E-8 * (1.4901161193847656E-8 + c_norm(*(double (*)[2])
           &b_param[2]))) || (fabs(sse - sse_old) <= 1.0E-8 * sse)) {
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%% */
      exitg1 = true;
    } else if (breakOut) {
      /* 정상계산실패하면 */
      *state = 0.0;
      exitg1 = true;
    } else {
      c_isfinite(step, bv1);
      if (!b_all(bv1)) {
        /* 정상계산실패하면 */
        *state = 0.0;
        exitg1 = true;
      } else {
        b_iter++;
      }
    }
  }

  param[0] = param0[0];
  param[2] = b_param[2];
  param[3] = b_param[3];
  param[1] = (fixed_pt[1] - param0[0]) * (1.0 + rt_powd_snf(10.0, b_param[3] *
    (b_param[2] - fixed_pt[0]))) + param0[0];
}

/* End of code generation (Coder_SigFitter_2para_part1.c) */
