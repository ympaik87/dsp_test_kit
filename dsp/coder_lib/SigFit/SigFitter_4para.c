/*
 * SigFitter_4para.c
 *
 * Code generation for function 'SigFitter_4para'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "SigFit.h"
#include "SigFitter_4para.h"
#include "norm.h"
#include "power.h"
#include "analytical_inverse.h"
#include "rdivide.h"

/* Function Declarations */
static void getjacobian(const double param[4], const double x_data[], const int
  x_size[1], double J_data[], int J_size[2]);

/* Function Definitions */
static void getjacobian(const double param[4], const double x_data[], const int
  x_size[1], double J_data[], int J_size[2])
{
  int loop_ub;
  int param_size[1];
  int i1;
  double param_data[45];
  double Cmm1_data[45];
  int Cmm1_size[1];
  int Cmm2_size[1];
  double Cmm2_data[45];
  double d0;
  int tmp_size[1];
  double tmp_data[45];
  double b_tmp_data[45];
  int b_tmp_size[1];
  J_size[0] = x_size[0];
  J_size[1] = 4;
  loop_ub = x_size[0] << 2;
  if (0 <= loop_ub - 1) {
    memset(&J_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  param_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    param_data[i1] = param[3] * (param[2] - x_data[i1]);
  }

  power(param_data, param_size, Cmm1_data, Cmm1_size);

  /* common portion */
  Cmm2_size[0] = Cmm1_size[0];
  loop_ub = Cmm1_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    Cmm2_data[i1] = 1.0 + Cmm1_data[i1];
  }

  loop_ub = Cmm1_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    J_data[i1] = 1.0 - 1.0 / Cmm2_data[i1];
  }

  loop_ub = Cmm1_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    J_data[i1 + J_size[0]] = 1.0 / Cmm2_data[i1];
  }

  b_power(Cmm2_data, Cmm2_size, param_data, param_size);
  d0 = 2.3025850929940459 * (param[0] - param[1]) * param[3];
  tmp_size[0] = Cmm1_size[0];
  loop_ub = Cmm1_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    tmp_data[i1] = d0 * Cmm1_data[i1];
  }

  rdivide(tmp_data, tmp_size, param_data, b_tmp_data, param_size);
  loop_ub = param_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    J_data[i1 + (J_size[0] << 1)] = b_tmp_data[i1];
  }

  b_power(Cmm2_data, Cmm2_size, param_data, param_size);
  d0 = 2.3025850929940459 * (param[0] - param[1]);
  b_tmp_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    tmp_data[i1] = d0 * (param[2] - x_data[i1]) * Cmm1_data[i1];
  }

  rdivide(tmp_data, b_tmp_size, param_data, b_tmp_data, param_size);
  loop_ub = param_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    J_data[i1 + J_size[0] * 3] = b_tmp_data[i1];
  }
}

void SigFitter_4para(const double x_data[], const int x_size[1], const double
                     y_data[], const int y_size[1], const double param0[4],
                     double param[4], double *iter, double *state)
{
  double lambda;
  boolean_T breakOut;
  int i0;
  double sse;
  int param0_size[1];
  int loop_ub;
  double param0_data[45];
  double r_data[45];
  int r_size[1];
  int k;
  double a_data[45];
  double J2_diag[16];
  int b_iter;
  boolean_T exitg1;
  double sse_old;
  double param_old[4];
  double J_data[180];
  int J_size[2];
  int ic;
  double J2[16];
  double b_a_data[180];
  int br;
  int ar;
  int ib;
  double y[4];
  int ia;
  double b_J2[16];
  double dv0[16];
  double step[4];
  int param_size[1];
  boolean_T exitg2;
  boolean_T b_y;
  boolean_T bv0[4];
  boolean_T bv1[4];
  int b_param_size[1];

  /* http://www.brnt.eu/phd/node10.html */
  lambda = 0.01;

  /* eps=2.220446049250313e-16 */
  breakOut = false;
  *state = 1.0;
  for (i0 = 0; i0 < 4; i0++) {
    param[i0] = param0[i0];
  }

  sse = param0[1] - param0[0];
  param0_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    param0_data[i0] = (param0[2] - x_data[i0]) * param0[3];
  }

  power(param0_data, param0_size, r_data, r_size);
  loop_ub = r_size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r_data[i0]++;
  }

  r_size[0] = y_size[0];
  loop_ub = y_size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r_data[i0] = y_data[i0] - (param0[0] + sse / r_data[i0]);
  }

  k = y_size[0];
  loop_ub = y_size[0];
  if (0 <= loop_ub - 1) {
    memcpy(&a_data[0], &r_data[0], (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  if (y_size[0] == 1) {
    sse = 0.0;
    for (i0 = 0; i0 < k; i0++) {
      sse += a_data[i0] * r_data[i0];
    }
  } else {
    sse = 0.0;
    for (i0 = 0; i0 < k; i0++) {
      sse += a_data[i0] * r_data[i0];
    }
  }

  memset(&J2_diag[0], 0, sizeof(double) << 4);
  *iter = 1.0;
  b_iter = 0;
  exitg1 = false;
  while ((!exitg1) && (b_iter < 200)) {
    *iter = 1.0 + (double)b_iter;
    for (i0 = 0; i0 < 4; i0++) {
      param_old[i0] = param[i0];
    }

    sse_old = sse;
    getjacobian(param, x_data, x_size, J_data, J_size);
    loop_ub = J_size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      for (ic = 0; ic < 4; ic++) {
        b_a_data[ic + (i0 << 2)] = J_data[i0 + J_size[0] * ic];
      }
    }

    if (J_size[0] == 1) {
      for (i0 = 0; i0 < 4; i0++) {
        for (ic = 0; ic < 4; ic++) {
          J2[i0 + (ic << 2)] = 0.0;
          for (k = 0; k < 1; k++) {
            J2[i0 + (ic << 2)] += b_a_data[i0] * J_data[ic];
          }
        }
      }
    } else {
      k = J_size[0];
      memset(&J2[0], 0, sizeof(double) << 4);
      for (loop_ub = 0; loop_ub <= 13; loop_ub += 4) {
        for (ic = loop_ub; ic + 1 <= loop_ub + 4; ic++) {
          J2[ic] = 0.0;
        }
      }

      br = 0;
      for (loop_ub = 0; loop_ub <= 13; loop_ub += 4) {
        ar = 0;
        i0 = br + k;
        for (ib = br; ib + 1 <= i0; ib++) {
          if (J_data[ib] != 0.0) {
            ia = ar;
            for (ic = loop_ub; ic + 1 <= loop_ub + 4; ic++) {
              ia++;
              J2[ic] += J_data[ib] * b_a_data[ia - 1];
            }
          }

          ar += 4;
        }

        br += k;
      }
    }

    for (k = 0; k < 4; k++) {
      J2_diag[k + (k << 2)] = J2[k + (k << 2)];
    }

    loop_ub = J_size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      for (ic = 0; ic < 4; ic++) {
        b_a_data[ic + (i0 << 2)] = J_data[i0 + J_size[0] * ic];
      }
    }

    if ((J_size[0] == 1) || (r_size[0] == 1)) {
      loop_ub = J_size[0];
      for (i0 = 0; i0 < 4; i0++) {
        y[i0] = 0.0;
        for (ic = 0; ic < loop_ub; ic++) {
          y[i0] += b_a_data[i0 + (ic << 2)] * r_data[ic];
        }
      }
    } else {
      for (ic = 0; ic < 4; ic++) {
        y[ic] = 0.0;
      }

      ar = 0;
      for (ib = 0; ib + 1 <= J_size[0]; ib++) {
        if (r_data[ib] != 0.0) {
          ia = ar;
          for (ic = 0; ic < 4; ic++) {
            ia++;
            y[ic] += r_data[ib] * b_a_data[ia - 1];
          }
        }

        ar += 4;
      }
    }

    for (i0 = 0; i0 < 16; i0++) {
      b_J2[i0] = J2[i0] + J2_diag[i0] * lambda;
    }

    analytical_inverse(b_J2, dv0);

    /*      step=LinSysSolver_using_LUdcp(J2+lambda_diag,J'*r,p); */
    /*  step=[J; sqrt(lambda_diag)]\[r; zeros(p,1)]; */
    for (i0 = 0; i0 < 4; i0++) {
      step[i0] = 0.0;
      for (ic = 0; ic < 4; ic++) {
        step[i0] += dv0[i0 + (ic << 2)] * y[ic];
      }

      param[i0] += step[i0];
    }

    sse = param[1] - param[0];
    param_size[0] = x_size[0];
    loop_ub = x_size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      param0_data[i0] = (param[2] - x_data[i0]) * param[3];
    }

    power(param0_data, param_size, r_data, r_size);
    loop_ub = r_size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      r_data[i0]++;
    }

    r_size[0] = y_size[0];
    loop_ub = y_size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      r_data[i0] = y_data[i0] - (param[0] + sse / r_data[i0]);
    }

    k = y_size[0];
    loop_ub = y_size[0];
    if (0 <= loop_ub - 1) {
      memcpy(&a_data[0], &r_data[0], (unsigned int)(loop_ub * (int)sizeof(double)));
    }

    if (y_size[0] == 1) {
      sse = 0.0;
      for (i0 = 0; i0 < k; i0++) {
        sse += a_data[i0] * r_data[i0];
      }
    } else {
      sse = 0.0;
      for (i0 = 0; i0 < k; i0++) {
        sse += a_data[i0] * r_data[i0];
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
          loop_ub = J_size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            for (ic = 0; ic < 4; ic++) {
              b_a_data[ic + (i0 << 2)] = J_data[i0 + J_size[0] * ic];
            }
          }

          if ((J_size[0] == 1) || (r_size[0] == 1)) {
            loop_ub = J_size[0];
            for (i0 = 0; i0 < 4; i0++) {
              y[i0] = 0.0;
              for (ic = 0; ic < loop_ub; ic++) {
                y[i0] += b_a_data[i0 + (ic << 2)] * r_data[ic];
              }
            }
          } else {
            for (ic = 0; ic < 4; ic++) {
              y[ic] = 0.0;
            }

            ar = 0;
            for (ib = 0; ib + 1 <= J_size[0]; ib++) {
              if (r_data[ib] != 0.0) {
                ia = ar;
                for (ic = 0; ic < 4; ic++) {
                  ia++;
                  y[ic] += r_data[ib] * b_a_data[ia - 1];
                }
              }

              ar += 4;
            }
          }

          for (i0 = 0; i0 < 16; i0++) {
            b_J2[i0] = J2[i0] + J2_diag[i0] * lambda;
          }

          analytical_inverse(b_J2, dv0);

          /*              step=LinSysSolver_using_LUdcp(J2+lambda_diag,J'*r,p); */
          for (i0 = 0; i0 < 4; i0++) {
            step[i0] = 0.0;
            for (ic = 0; ic < 4; ic++) {
              step[i0] += dv0[i0 + (ic << 2)] * y[ic];
            }

            param[i0] = param_old[i0] + step[i0];
          }

          sse = param[1] - param[0];
          b_param_size[0] = x_size[0];
          loop_ub = x_size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            param0_data[i0] = (param[2] - x_data[i0]) * param[3];
          }

          power(param0_data, b_param_size, r_data, r_size);
          loop_ub = r_size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            r_data[i0]++;
          }

          r_size[0] = y_size[0];
          loop_ub = y_size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            r_data[i0] = y_data[i0] - (param[0] + sse / r_data[i0]);
          }

          k = y_size[0];
          loop_ub = y_size[0];
          if (0 <= loop_ub - 1) {
            memcpy(&a_data[0], &r_data[0], (unsigned int)(loop_ub * (int)sizeof
                    (double)));
          }

          if (y_size[0] == 1) {
            sse = 0.0;
            for (i0 = 0; i0 < k; i0++) {
              sse += a_data[i0] * r_data[i0];
            }
          } else {
            sse = 0.0;
            for (i0 = 0; i0 < k; i0++) {
              sse += a_data[i0] * r_data[i0];
            }
          }
        }
      }
    }

    /*      iter */
    /*      ['sse_old: ' num2str(sse_old)] */
    /*      ['sse: ' num2str(sse)]  */
    /*      ['|sse-sse_old|: ' num2str(abs(sse-sse_old)) ', tol*sse:' num2str(tol*sse)]  */
    if ((norm(step) < 1.0E-8 * (1.4901161193847656E-8 + norm(param))) || (fabs
         (sse - sse_old) <= 1.0E-8 * sse)) {
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
      for (k = 0; k < 4; k++) {
        bv0[k] = !rtIsInf(step[k]);
        bv1[k] = !rtIsNaN(step[k]);
      }

      b_y = true;
      k = 0;
      exitg2 = false;
      while ((!exitg2) && (k < 4)) {
        if (!(bv0[k] && bv1[k])) {
          b_y = false;
          exitg2 = true;
        } else {
          k++;
        }
      }

      if (!b_y) {
        /* 정상계산실패하면 */
        *state = 0.0;
        exitg1 = true;
      } else {
        b_iter++;
      }
    }
  }
}

/* End of code generation (SigFitter_4para.c) */
