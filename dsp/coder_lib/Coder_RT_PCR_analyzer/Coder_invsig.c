/*
 * Coder_invsig.c
 *
 * Code generation for function 'Coder_invsig'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_invsig.h"

/* Function Definitions */
double Coder_invsig(const double p[4], double x)
{
  return p[2] - log10((p[1] - x) / (x - p[0])) / p[3];
}

/* End of code generation (Coder_invsig.c) */
