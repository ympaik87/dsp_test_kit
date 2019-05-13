/*
 * sqrt.c
 *
 * Code generation for function 'sqrt'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "sqrt.h"

/* Function Declarations */
static void c_sqrt(double *x);

/* Function Definitions */
static void c_sqrt(double *x)
{
  *x = sqrt(*x);
}

double b_sqrt(double x)
{
  double b_x;
  b_x = x;
  c_sqrt(&b_x);
  return b_x;
}

/* End of code generation (sqrt.c) */
