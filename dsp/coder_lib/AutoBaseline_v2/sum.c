/*
 * sum.c
 *
 * Code generation for function 'sum'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "sum.h"
#include "combineVectorElements.h"

/* Function Definitions */
double sum(const emxArray_real_T *x)
{
  return combineVectorElements(x);
}

/* End of code generation (sum.c) */
