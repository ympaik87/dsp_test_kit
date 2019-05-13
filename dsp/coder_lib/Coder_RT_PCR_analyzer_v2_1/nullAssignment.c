/*
 * nullAssignment.c
 *
 * Code generation for function 'nullAssignment'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "nullAssignment.h"

/* Function Definitions */
void nullAssignment(double x_data[], int x_size[2], const boolean_T idx_data[],
                    const int idx_size[2])
{
  int nxin;
  int nxout;
  int k0;
  int k;
  nxin = x_size[1];
  nxout = 0;
  k0 = idx_size[1];
  for (k = 0; k < k0; k++) {
    nxout += idx_data[k];
  }

  nxout = x_size[1] - nxout;
  k0 = -1;
  for (k = 0; k < nxin; k++) {
    if ((k + 1 > idx_size[1]) || (!idx_data[k])) {
      k0++;
      x_data[k0] = x_data[k];
    }
  }

  if (1 > nxout) {
    x_size[1] = 0;
  } else {
    x_size[1] = nxout;
  }
}

/* End of code generation (nullAssignment.c) */
