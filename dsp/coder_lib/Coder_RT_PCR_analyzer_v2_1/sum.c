/*
 * sum.c
 *
 * Code generation for function 'sum'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "sum.h"
#include "combineVectorElements.h"

/* Function Definitions */
double b_sum(const double x[4])
{
  return ((x[0] + x[1]) + x[2]) + x[3];
}

double sum(const emxArray_real_T *x)
{
  return combineVectorElements(x);
}

/* End of code generation (sum.c) */
