/*
 * Coder_medfilter.c
 *
 * Code generation for function 'Coder_medfilter'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_medfilter.h"
#include "vmedian.h"

/* Function Definitions */
void Coder_medfilter(const double data_data[], const int data_size[1], double
                     smoothed_data_data[], int smoothed_data_size[1])
{
  int i8;
  int i9;
  int i10;
  int loop_ub;
  int i;
  int x_size[1];
  int i11;
  double x_data[100];

  /* n>=2 */
  smoothed_data_size[0] = data_size[0];
  if (0 <= data_size[0] - 1) {
    memset(&smoothed_data_data[0], 0, (unsigned int)(data_size[0] * (int)sizeof
            (double)));
  }

  smoothed_data_data[0] = data_data[0];
  smoothed_data_data[1] = data_data[1];
  if (data_size[0] - 1 > data_size[0]) {
    i8 = 1;
    i9 = 0;
    i10 = 1;
  } else {
    i8 = data_size[0] - 1;
    i9 = data_size[0];
    i10 = data_size[0] - 1;
  }

  loop_ub = i9 - i8;
  for (i9 = 0; i9 <= loop_ub; i9++) {
    smoothed_data_data[(i10 + i9) - 1] = data_data[(i8 + i9) - 1];
  }

  i8 = data_size[0];
  for (i = 0; i <= i8 - 5; i++) {
    if (i + 1 > i + 5) {
      i9 = 1;
      i10 = 1;
    } else {
      i9 = i + 1;
      i10 = i + 6;
    }

    loop_ub = i10 - i9;
    if (loop_ub == 0) {
      smoothed_data_data[2 + i] = rtNaN;
    } else {
      x_size[0] = loop_ub;
      for (i11 = 0; i11 < loop_ub; i11++) {
        x_data[i11] = data_data[(i9 + i11) - 1];
      }

      smoothed_data_data[2 + i] = vmedian(x_data, x_size, i10 - i9);
    }
  }

  i = data_size[0] - 1;
  if ((double)i - 1.0 > (double)i + 1.0) {
    i8 = 1;
    i9 = 1;
  } else {
    i8 = (int)((double)i - 1.0);
    i9 = (i + 1) + 1;
  }

  loop_ub = i9 - i8;
  if (loop_ub == 0) {
    smoothed_data_data[i - 1] = rtNaN;
  } else {
    x_size[0] = loop_ub;
    for (i10 = 0; i10 < loop_ub; i10++) {
      x_data[i10] = data_data[(i8 + i10) - 1];
    }

    smoothed_data_data[i - 1] = vmedian(x_data, x_size, i9 - i8);
  }
}

/* End of code generation (Coder_medfilter.c) */
