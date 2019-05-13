/*
 * power.c
 *
 * Code generation for function 'power'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "SigFit.h"
#include "power.h"
#include "SigFit_rtwutil.h"

/* Function Definitions */
void b_power(const double a_data[], const int a_size[1], double y_data[], int
             y_size[1])
{
  int k;
  y_size[0] = (signed char)a_size[0];
  for (k = 0; k + 1 <= (signed char)a_size[0]; k++) {
    y_data[k] = rt_powd_snf(a_data[k], 2.0);
  }
}

void power(const double b_data[], const int b_size[1], double y_data[], int
           y_size[1])
{
  int k;
  y_size[0] = (signed char)b_size[0];
  for (k = 0; k + 1 <= (signed char)b_size[0]; k++) {
    y_data[k] = rt_powd_snf(10.0, b_data[k]);
  }
}

/* End of code generation (power.c) */
