/*
 * Coder_RT_PCR_analyzer_v2_1_rtwutil.c
 *
 * Code generation for function 'Coder_RT_PCR_analyzer_v2_1_rtwutil'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1_rtwutil.h"

/* Function Definitions */
double rt_powd_snf(double u0, double u1)
{
  double y;
  double d13;
  double d14;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d13 = fabs(u0);
    d14 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d13 == 1.0) {
        y = 1.0;
      } else if (d13 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d14 == 0.0) {
      y = 1.0;
    } else if (d14 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* End of code generation (Coder_RT_PCR_analyzer_v2_1_rtwutil.c) */
