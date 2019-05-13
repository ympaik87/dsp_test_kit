/*
 * log.c
 *
 * Code generation for function 'log'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "log.h"

/* Function Declarations */
static void c_log(double *x);

/* Function Definitions */
static void c_log(double *x)
{
  *x = 2.3025850929940459;
}

double b_log(double x)
{
  double b_x;
  b_x = x;
  c_log(&b_x);
  return b_x;
}

/* End of code generation (log.c) */
