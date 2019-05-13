/*
 * Coder_LSR2.c
 *
 * Code generation for function 'Coder_LSR2'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_LSR2.h"
#include "sum.h"
#include "diff.h"

/* Function Definitions */
double Coder_LSR2(const double data_data[], const int data_size[1], double Thrd)
{
  double tmp_data[100];
  int k;
  int nx;
  int b_data_size[1];
  double b_data_data[100];
  double x_data[198];
  int x_size[1];
  int y_size[1];
  emxArray_real_T y_data;
  double b_y_data[198];
  if (0 <= data_size[0] - 1) {
    memset(&tmp_data[0], 0, (unsigned int)(data_size[0] * (int)sizeof(double)));
  }

  tmp_data[0] = (data_data[0] + data_data[1]) / 2.0;
  tmp_data[data_size[0] - 1] = (data_data[data_size[0] - 2] + data_data[(signed
    char)data_size[0] - 1]) / 2.0;
  k = data_size[0];
  for (nx = 0; nx <= k - 3; nx++) {
    tmp_data[1 + nx] = ((data_data[(signed char)((signed char)nx + 1) - 1] +
                         data_data[(signed char)((signed char)nx + 2) - 1]) +
                        data_data[(signed char)((signed char)(1 + (signed char)
      nx) + 2) - 1]) / 3.0;
  }

  b_data_size[0] = data_size[0];
  nx = data_size[0];
  for (k = 0; k < nx; k++) {
    b_data_data[k] = data_data[k] - tmp_data[k];
  }

  diff(b_data_data, b_data_size, x_data, x_size);
  nx = x_size[0];
  y_size[0] = (unsigned char)x_size[0];
  for (k = 0; k < nx; k++) {
    b_y_data[k] = fabs(x_data[k]);
  }

  y_data.data = &b_y_data[0];
  y_data.size = &y_size[0];
  y_data.allocatedSize = 198;
  y_data.numDimensions = 1;
  y_data.canFreeData = false;
  return sum(&y_data) / Thrd;
}

/* End of code generation (Coder_LSR2.c) */
