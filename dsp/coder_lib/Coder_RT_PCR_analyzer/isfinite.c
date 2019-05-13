/*
 * isfinite.c
 *
 * Code generation for function 'isfinite'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "isfinite.h"

/* Function Definitions */
void b_isfinite(const double x[4], boolean_T b[4])
{
  b[0] = ((!rtIsInf(x[0])) && (!rtIsNaN(x[0])));
  b[1] = ((!rtIsInf(x[1])) && (!rtIsNaN(x[1])));
  b[2] = ((!rtIsInf(x[2])) && (!rtIsNaN(x[2])));
  b[3] = ((!rtIsInf(x[3])) && (!rtIsNaN(x[3])));
}

void c_isfinite(const double x[2], boolean_T b[2])
{
  b[0] = ((!rtIsInf(x[0])) && (!rtIsNaN(x[0])));
  b[1] = ((!rtIsInf(x[1])) && (!rtIsNaN(x[1])));
}

void d_isfinite(const double x[3], boolean_T b[3])
{
  b[0] = ((!rtIsInf(x[0])) && (!rtIsNaN(x[0])));
  b[1] = ((!rtIsInf(x[1])) && (!rtIsNaN(x[1])));
  b[2] = ((!rtIsInf(x[2])) && (!rtIsNaN(x[2])));
}

/* End of code generation (isfinite.c) */
