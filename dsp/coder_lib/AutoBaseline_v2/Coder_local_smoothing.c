/*
 * Coder_local_smoothing.c
 *
 * Code generation for function 'Coder_local_smoothing'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_local_smoothing.h"

/* Function Definitions */
void Coder_local_smoothing(const double data[6], double smoothed_data[6])
{
  int i;
  smoothed_data[0] = (data[0] + data[1]) / 2.0;
  smoothed_data[5] = (data[4] + data[5]) / 2.0;
  for (i = 0; i < 4; i++) {
    smoothed_data[i + 1] = ((data[i] + data[i + 1]) + data[i + 2]) / 3.0;
  }
}

void b_Coder_local_smoothing(const double data_data[], const int data_size[1],
  double smoothed_data_data[], int smoothed_data_size[1])
{
  int i23;
  int i;
  smoothed_data_size[0] = data_size[0];
  if (0 <= data_size[0] - 1) {
    memset(&smoothed_data_data[0], 0, (unsigned int)(data_size[0] * (int)sizeof
            (double)));
  }

  smoothed_data_data[0] = (data_data[0] + data_data[1]) / 2.0;
  smoothed_data_data[data_size[0] - 1] = (data_data[data_size[0] - 2] +
    data_data[(signed char)data_size[0] - 1]) / 2.0;
  i23 = data_size[0];
  for (i = 0; i <= i23 - 3; i++) {
    smoothed_data_data[1 + i] = ((data_data[(signed char)((signed char)i + 1) -
      1] + data_data[(signed char)((signed char)i + 2) - 1]) + data_data[(signed
      char)((signed char)(1 + (signed char)i) + 2) - 1]) / 3.0;
  }
}

/* End of code generation (Coder_local_smoothing.c) */
