/*
 * mean.c
 *
 * Code generation for function 'mean'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "mean.h"
#include "combineVectorElements.h"

/* Function Definitions */
double b_mean(const double x[2])
{
  return (x[0] + x[1]) / 2.0;
}

double c_mean(const emxArray_real_T *x)
{
  return combineVectorElements(x) / (double)x->size[0];
}

double d_mean(const double x[4])
{
  return (((x[0] + x[1]) + x[2]) + x[3]) / 4.0;
}

double e_mean(const double x[5])
{
  return ((((x[0] + x[1]) + x[2]) + x[3]) + x[4]) / 5.0;
}

double mean(const double x[3])
{
  return ((x[0] + x[1]) + x[2]) / 3.0;
}

/* End of code generation (mean.c) */
