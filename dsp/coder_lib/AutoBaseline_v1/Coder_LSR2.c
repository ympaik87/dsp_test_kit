/*
 * Coder_LSR2.c
 *
 * Code generation for function 'Coder_LSR2'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v1.h"
#include "Coder_LSR2.h"
#include "sum.h"
#include "diff.h"
#include "Coder_local_smoothing.h"

/* Function Definitions */
double Coder_LSR2(const double data_data[], const int data_size[1], double Thrd)
{
  double tmp_data[100];
  int tmp_size[1];
  int b_data_size[1];
  int nx;
  int k;
  double b_data_data[100];
  double x_data[198];
  int y_size[1];
  emxArray_real_T y_data;
  double b_y_data[198];
  b_Coder_local_smoothing(data_data, data_size, tmp_data, tmp_size);
  b_data_size[0] = data_size[0];
  nx = data_size[0];
  for (k = 0; k < nx; k++) {
    b_data_data[k] = data_data[k] - tmp_data[k];
  }

  diff(b_data_data, b_data_size, x_data, tmp_size);
  nx = tmp_size[0];
  y_size[0] = (unsigned char)tmp_size[0];
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
