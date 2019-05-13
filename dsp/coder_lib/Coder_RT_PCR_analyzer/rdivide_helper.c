/*
 * rdivide_helper.c
 *
 * Code generation for function 'rdivide_helper'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "rdivide_helper.h"

/* Function Definitions */
void rdivide_helper(const double x_data[], const int x_size[1], const double
                    y_data[], double z_data[], int z_size[1])
{
  int loop_ub;
  int i19;
  z_size[0] = x_size[0];
  loop_ub = x_size[0];
  for (i19 = 0; i19 < loop_ub; i19++) {
    z_data[i19] = x_data[i19] / y_data[i19];
  }
}

/* End of code generation (rdivide_helper.c) */
