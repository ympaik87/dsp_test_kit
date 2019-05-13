/*
 * sign.c
 *
 * Code generation for function 'sign'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "sign.h"

/* Function Definitions */
void b_sign(double x_data[], int x_size[2])
{
  int nx;
  int k;
  double x;
  nx = x_size[1];
  for (k = 0; k < nx; k++) {
    x = x_data[k];
    if (x_data[k] < 0.0) {
      x = -1.0;
    } else if (x_data[k] > 0.0) {
      x = 1.0;
    } else {
      if (x_data[k] == 0.0) {
        x = 0.0;
      }
    }

    x_data[k] = x;
  }
}

/* End of code generation (sign.c) */
