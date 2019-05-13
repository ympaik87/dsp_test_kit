/*
 * diff.c
 *
 * Code generation for function 'diff'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "diff.h"

/* Function Definitions */
void b_diff(const double x_data[], const int x_size[2], double y_data[], int
            y_size[2])
{
  int dimSize;
  int ixLead;
  int iyLead;
  double work_data_idx_0;
  int m;
  double tmp1;
  dimSize = x_size[1];
  if (x_size[1] == 0) {
    y_size[0] = 1;
    y_size[1] = 0;
  } else {
    ixLead = x_size[1] - 1;
    if (ixLead >= 1) {
      ixLead = 1;
    }

    if (ixLead < 1) {
      y_size[0] = 1;
      y_size[1] = 0;
    } else {
      y_size[0] = 1;
      y_size[1] = (signed char)(x_size[1] - 1);
      if ((signed char)(x_size[1] - 1) != 0) {
        ixLead = 1;
        iyLead = 0;
        work_data_idx_0 = x_data[0];
        for (m = 2; m <= dimSize; m++) {
          tmp1 = work_data_idx_0;
          work_data_idx_0 = x_data[ixLead];
          tmp1 = x_data[ixLead] - tmp1;
          ixLead++;
          y_data[iyLead] = tmp1;
          iyLead++;
        }
      }
    }
  }
}

void c_diff(const double x[5], double y[4])
{
  y[0] = x[1] - x[0];
  y[1] = x[2] - x[1];
  y[2] = x[3] - x[2];
  y[3] = x[4] - x[3];
}

void diff(const double x_data[], const int x_size[1], double y_data[], int
          y_size[1])
{
  int dimSize;
  int ixLead;
  int iyLead;
  double work_data_idx_0;
  int m;
  double tmp1;
  dimSize = x_size[0];
  if (x_size[0] == 0) {
    y_size[0] = 0;
  } else {
    ixLead = x_size[0] - 1;
    if (ixLead >= 1) {
      ixLead = 1;
    }

    if (ixLead < 1) {
      y_size[0] = 0;
    } else {
      y_size[0] = (unsigned char)(x_size[0] - 1);
      if ((unsigned char)(x_size[0] - 1) != 0) {
        ixLead = 1;
        iyLead = 0;
        work_data_idx_0 = x_data[0];
        for (m = 2; m <= dimSize; m++) {
          tmp1 = work_data_idx_0;
          work_data_idx_0 = x_data[ixLead];
          tmp1 = x_data[ixLead] - tmp1;
          ixLead++;
          y_data[iyLead] = tmp1;
          iyLead++;
        }
      }
    }
  }
}

/* End of code generation (diff.c) */
