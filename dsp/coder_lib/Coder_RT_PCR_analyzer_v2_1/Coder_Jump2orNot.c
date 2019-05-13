/*
 * Coder_Jump2orNot.c
 *
 * Code generation for function 'Coder_Jump2orNot'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_Jump2orNot.h"

/* Function Definitions */
double Coder_Jump2orNot(const double A[3])
{
  double RD_cc;
  double b_A[3];
  signed char B[3];
  int i;
  int idx;
  double ex;
  int k;
  double u1;
  boolean_T exitg1;
  double b_ex;
  int i4;
  double c_ex;
  b_A[0] = A[0];
  b_A[1] = A[1];
  B[1] = 0;
  b_A[2] = A[2];
  for (i = 0; i < 3; i++) {
    if (!rtIsNaN(b_A[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k < 4)) {
        if (!rtIsNaN(b_A[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      idx = 1;
    } else {
      ex = b_A[idx - 1];
      i4 = idx + 1;
      for (k = i4; k < 4; k++) {
        u1 = b_A[k - 1];
        if (ex > u1) {
          ex = u1;
          idx = k;
        }
      }
    }

    B[idx - 1] = (signed char)(1 + i);
    b_A[idx - 1] = rtInf;
  }

  if (B[1] == 1) {
    /* RD(cc)가 최소 */
    ex = A[0] - A[1];
    u1 = A[2] - A[1];
    if ((ex < u1) || rtIsNaN(u1)) {
      b_ex = ex;
    } else {
      b_ex = u1;
    }

    if (b_ex / fabs(A[2] - A[0]) > 0.2) {
      RD_cc = (A[0] + A[2]) / 2.0;
    } else {
      RD_cc = A[1];
    }
  } else if (B[1] == 3) {
    /* RD(cc)가 최대 */
    ex = A[1] - A[0];
    u1 = A[1] - A[2];
    if ((ex < u1) || rtIsNaN(u1)) {
      c_ex = ex;
    } else {
      c_ex = u1;
    }

    if (c_ex / fabs(A[2] - A[0]) > 0.2) {
      RD_cc = (A[0] + A[2]) / 2.0;
    } else {
      RD_cc = A[1];
    }
  } else {
    RD_cc = A[1];
  }

  return RD_cc;
}

/* End of code generation (Coder_Jump2orNot.c) */
