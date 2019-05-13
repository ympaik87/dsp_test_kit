/*
 * rdivide.c
 *
 * Code generation for function 'rdivide'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "SigFit.h"
#include "rdivide.h"

/* Function Definitions */
void rdivide(const double x_data[], const int x_size[1], const double y_data[],
             double z_data[], int z_size[1])
{
  int loop_ub;
  int i2;
  z_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i2 = 0; i2 < loop_ub; i2++) {
    z_data[i2] = x_data[i2] / y_data[i2];
  }
}

/* End of code generation (rdivide.c) */
