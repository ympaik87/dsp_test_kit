/*
 * var.c
 *
 * Code generation for function 'var'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "AutoBaseline_v1.h"
#include "var.h"

/* Function Definitions */
double var(const double x_data[], const int x_size[1])
{
  double y;
  int n;
  double xbar;
  int k;
  double t;
  n = x_size[0];
  if (x_size[0] == 0) {
    y = rtNaN;
  } else if (x_size[0] == 1) {
    if ((!rtIsInf(x_data[0])) && (!rtIsNaN(x_data[0]))) {
      y = 0.0;
    } else {
      y = rtNaN;
    }
  } else {
    xbar = x_data[0];
    for (k = 2; k <= n; k++) {
      xbar += x_data[k - 1];
    }

    xbar /= (double)x_size[0];
    y = 0.0;
    for (k = 0; k < n; k++) {
      t = x_data[k] - xbar;
      y += t * t;
    }

    y /= (double)x_size[0] - 1.0;
  }

  return y;
}

/* End of code generation (var.c) */
