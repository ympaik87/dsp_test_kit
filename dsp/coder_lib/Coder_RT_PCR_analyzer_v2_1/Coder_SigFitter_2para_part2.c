/*
 * Coder_SigFitter_2para_part2.c
 *
 * Code generation for function 'Coder_SigFitter_2para_part2'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_SigFitter_2para_part2.h"
#include "all.h"
#include "isfinite.h"
#include "norm.h"
#include "Coder_sig_part2.h"
#include "Coder_analytical_inverse.h"
#include "Coder_getjacobian_par3.h"

/* Function Definitions */
void Coder_SigFitter_2para_part2(const double x_data[], const int x_size[1],
  const double y_data[], const int y_size[1], const double param0[4], const
  double fixed_pt[2], double param[4], double *iter, double *state)
{
  double lambda;
  boolean_T breakOut;
  double b_param[4];
  double r_data[100];
  int r_size[1];
  int aoffset;
  int i29;
  double a_data[100];
  double sse;
  int b_iter;
  boolean_T exitg1;
  double param_old[4];
  double sse_old;
  double J_data[200];
  int J_size[2];
  int a_tmp_size_idx_1;
  int inner;
  double J2[4];
  double a_tmp_data[200];
  int k;
  double y_idx_1;
  double b_J2[4];
  double dv2[4];
  double d9;
  double step[2];
  boolean_T exitg2;
  double c_param[2];
  boolean_T bv2[2];
  lambda = 0.01;

  /* eps=2.220446049250313e-16 */
  breakOut = false;
  *state = 1.0;
  b_param[0] = param0[0];
  b_param[1] = param0[1];
  b_param[2] = param0[2];
  b_param[3] = param0[3];

  /*  fprintf('param=[ %s, ', Double2String(param(1))) */
  /*  for i=2:3 */
  /*      fprintf('%s, ', Double2String(param(i))) */
  /*  end */
  /*  fprintf('%s]\n ', Double2String(param(4))) */
  Coder_sig_part2(param0, x_data, x_size, fixed_pt, r_data, r_size);
  r_size[0] = y_size[0];
  aoffset = y_size[0];
  for (i29 = 0; i29 < aoffset; i29++) {
    r_data[i29] = y_data[i29] - r_data[i29];
  }

  /*  fprintf('x(1)=%s\n ', Double2String(x(1))) */
  /*  fprintf('fixed_pt=[%s , %s]\n ', Double2String(fixed_pt(1)), Double2String(fixed_pt(2))) */
  /*  fprintf('Sig_test=%s\n ', Double2String(param(1)+(fixed_pt(2)-param(1))*2./(1+10.^((fixed_pt(1)-x(1))*param(4)))) )  */
  /*  fprintf('Sig_test2=%s\n ', Double2String(369-Coder_sig_part2([0 709 34 0.2],34,[34 369]))) */
  /*   */
  /*  a5=Coder_sig_part2(param,x,fixed_pt); */
  /*  fprintf('Sig=[ %s, ', Double2String(a5(1))) */
  /*  for i=2:length(a5) */
  /*      fprintf('%s, ', Double2String(a5(i))) */
  /*  end */
  /*  fprintf('%s]\n ', Double2String(a5(length(r)))) */
  /*   */
  /*   */
  /*  fprintf('y(1)=%s\n ', Double2String(y(1))) */
  /*   */
  /*  fprintf('r=[ %s, ', Double2String(abs(r(1)*1000000))) */
  /*  for i=2:length(r) */
  /*      fprintf('%s, ', Double2String(abs(r(i)*1000000))) */
  /*  end */
  /*  fprintf('%s]\n ', Double2String(abs(r(length(r))*1000000))) */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  if (0 <= y_size[0] - 1) {
    memcpy(&a_data[0], &r_data[0], (unsigned int)(y_size[0] * (int)sizeof(double)));
  }

  if (y_size[0] == 1) {
    sse = 0.0;
    for (i29 = 0; i29 < 1; i29++) {
      sse += a_data[0] * r_data[0];
    }
  } else {
    sse = 0.0;
    aoffset = y_size[0];
    for (i29 = 0; i29 < aoffset; i29++) {
      sse += a_data[i29] * r_data[i29];
    }
  }

  /*  fprintf('sse=%s\n ', Double2String(sse)) */
  *iter = 1.0;
  b_iter = 0;
  exitg1 = false;
  while ((!exitg1) && (b_iter < 200)) {
    *iter = 1.0 + (double)b_iter;
    param_old[0] = b_param[0];
    param_old[3] = b_param[3];
    sse_old = sse;
    Coder_getjacobian_par3(b_param, x_data, x_size, fixed_pt, J_data, J_size);
    a_tmp_size_idx_1 = J_size[0];
    aoffset = J_size[0];
    for (i29 = 0; i29 < aoffset; i29++) {
      inner = i29 << 1;
      a_tmp_data[inner] = J_data[i29];
      a_tmp_data[1 + inner] = J_data[i29 + J_size[0]];
    }

    if (J_size[0] == 1) {
      J2[0] = 0.0;
      for (i29 = 0; i29 < 1; i29++) {
        J2[0] += a_tmp_data[0] * J_data[0];
      }

      J2[2] = 0.0;
      for (i29 = 0; i29 < 1; i29++) {
        J2[2] += a_tmp_data[0] * J_data[1];
      }

      J2[1] = 0.0;
      for (i29 = 0; i29 < 1; i29++) {
        J2[1] += a_tmp_data[1] * J_data[0];
      }

      J2[3] = 0.0;
      for (i29 = 0; i29 < 1; i29++) {
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
        i29 = k << 1;
        sse = J_data[inner + k];
        J2[2] += sse * a_tmp_data[i29];
        J2[3] += sse * a_tmp_data[i29 + 1];
      }
    }

    if ((J_size[0] == 1) || (r_size[0] == 1)) {
      aoffset = J_size[0];
      sse = 0.0;
      for (i29 = 0; i29 < aoffset; i29++) {
        sse += a_tmp_data[i29 << 1] * r_data[i29];
      }

      y_idx_1 = 0.0;
      for (i29 = 0; i29 < aoffset; i29++) {
        y_idx_1 += a_tmp_data[1 + (i29 << 1)] * r_data[i29];
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
    b_Coder_analytical_inverse(b_J2, dv2);

    /*      step=LinSysSolver_using_LUdcp(J2+lambda_diag,J'*r,p); */
    d9 = dv2[0] * sse + dv2[2] * y_idx_1;
    step[0] = d9;
    b_param[0] += d9;
    d9 = dv2[1] * sse + dv2[3] * y_idx_1;
    step[1] = d9;
    b_param[3] += d9;

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    Coder_sig_part2(b_param, x_data, x_size, fixed_pt, r_data, r_size);
    r_size[0] = y_size[0];
    aoffset = y_size[0];
    for (i29 = 0; i29 < aoffset; i29++) {
      r_data[i29] = y_data[i29] - r_data[i29];
    }

    if (0 <= y_size[0] - 1) {
      memcpy(&a_data[0], &r_data[0], (unsigned int)(y_size[0] * (int)sizeof
              (double)));
    }

    if (y_size[0] == 1) {
      sse = 0.0;
      for (i29 = 0; i29 < 1; i29++) {
        sse += a_data[0] * r_data[0];
      }
    } else {
      sse = 0.0;
      aoffset = y_size[0];
      for (i29 = 0; i29 < aoffset; i29++) {
        sse += a_data[i29] * r_data[i29];
      }
    }

    /*      if iter==2 */
    /*          fprintf('sse=%s\n ', Double2String(sse)) */
    /*      end */
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
            for (i29 = 0; i29 < a_tmp_size_idx_1; i29++) {
              sse += a_tmp_data[i29 << 1] * r_data[i29];
            }

            y_idx_1 = 0.0;
            for (i29 = 0; i29 < a_tmp_size_idx_1; i29++) {
              y_idx_1 += a_tmp_data[1 + (i29 << 1)] * r_data[i29];
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
          b_Coder_analytical_inverse(b_J2, dv2);

          /*              step=LinSysSolver_using_LUdcp(J2+lambda_diag,J'*r,p); */
          d9 = dv2[0] * sse + dv2[2] * y_idx_1;
          step[0] = d9;
          b_param[0] = param_old[0] + d9;
          d9 = dv2[1] * sse + dv2[3] * y_idx_1;
          step[1] = d9;
          b_param[3] = param_old[3] + d9;

          /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
          Coder_sig_part2(b_param, x_data, x_size, fixed_pt, r_data, r_size);
          r_size[0] = y_size[0];
          aoffset = y_size[0];
          for (i29 = 0; i29 < aoffset; i29++) {
            r_data[i29] = y_data[i29] - r_data[i29];
          }

          if (0 <= y_size[0] - 1) {
            memcpy(&a_data[0], &r_data[0], (unsigned int)(y_size[0] * (int)
                    sizeof(double)));
          }

          if (y_size[0] == 1) {
            sse = 0.0;
            for (i29 = 0; i29 < 1; i29++) {
              sse += a_data[0] * r_data[0];
            }
          } else {
            sse = 0.0;
            aoffset = y_size[0];
            for (i29 = 0; i29 < aoffset; i29++) {
              sse += a_data[i29] * r_data[i29];
            }
          }
        }
      }
    }

    c_param[0] = b_param[0];
    c_param[1] = b_param[3];
    if ((c_norm(step) < 1.0E-8 * (1.4901161193847656E-8 + c_norm(c_param))) ||
        (fabs(sse - sse_old) <= 1.0E-8 * sse)) {
      /* %%%%%%%%%%%%%%%%%%%%%%%%%%% */
      exitg1 = true;
    } else if (breakOut) {
      /* 정상계산실패하면 */
      *state = 0.0;
      exitg1 = true;
    } else {
      c_isfinite(step, bv2);
      if (!b_all(bv2)) {
        /* 정상계산실패하면 */
        *state = 0.0;
        exitg1 = true;
      } else {
        b_iter++;
      }
    }
  }

  param[0] = b_param[0];
  param[3] = b_param[3];
  param[1] = (fixed_pt[1] - b_param[0]) * 2.0 + b_param[0];
  param[2] = fixed_pt[0];

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
}

/* End of code generation (Coder_SigFitter_2para_part2.c) */
