/*
 * rdivide.c
 *
 * Code generation for function 'rdivide'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "rdivide.h"

/* Function Definitions */
void rdivide(const double x_data[], const int x_size[1], const double y_data[],
             double z_data[], int z_size[1])
{
  int loop_ub;
  int i16;
  z_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i16 = 0; i16 < loop_ub; i16++) {
    z_data[i16] = x_data[i16] / y_data[i16];
  }
}

/* End of code generation (rdivide.c) */
