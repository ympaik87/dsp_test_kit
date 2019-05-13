/*
 * Coder_local_smoothing.c
 *
 * Code generation for function 'Coder_local_smoothing'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_local_smoothing.h"

/* Function Definitions */
void Coder_local_smoothing(const double data[5], double smoothed_data[5])
{
  int i;
  smoothed_data[0] = (data[0] + data[1]) / 2.0;
  smoothed_data[4] = (data[3] + data[4]) / 2.0;
  for (i = 0; i < 3; i++) {
    smoothed_data[i + 1] = ((data[i] + data[i + 1]) + data[i + 2]) / 3.0;
  }
}

/* End of code generation (Coder_local_smoothing.c) */
