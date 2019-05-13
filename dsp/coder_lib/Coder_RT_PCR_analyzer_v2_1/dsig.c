/*
 * dsig.c
 *
 * Code generation for function 'dsig'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "dsig.h"
#include "power.h"
#include "Coder_RT_PCR_analyzer_v2_1_rtwutil.h"

/* Function Definitions */
double dsig(const double p[4], double x)
{
  double a_tmp;
  a_tmp = rt_powd_snf(10.0, p[3] * (p[2] - x));
  return p[3] * 2.3025850929940459 * (p[1] - p[0]) * a_tmp / ((1.0 + a_tmp) *
    (1.0 + a_tmp));
}

/* End of code generation (dsig.c) */
