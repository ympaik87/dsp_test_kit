/*
 * Coder_min5.c
 *
 * Code generation for function 'Coder_min5'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_min5.h"

/* Function Definitions */
void Coder_min5(double RD_data[], int RD_size[1], double min5_idx[5])
{
  int n;
  int i;
  int idx;
  int k;
  boolean_T exitg1;
  double ex;
  int i11;
  double d2;
  n = RD_size[0];
  for (i = 0; i < 5; i++) {
    if (RD_size[0] <= 2) {
      if (RD_size[0] == 1) {
        idx = 1;
      } else if ((RD_data[0] > RD_data[1]) || (rtIsNaN(RD_data[0]) && (!rtIsNaN
                   (RD_data[1])))) {
        idx = 2;
      } else {
        idx = 1;
      }
    } else {
      if (!rtIsNaN(RD_data[0])) {
        idx = 1;
      } else {
        idx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= RD_size[0])) {
          if (!rtIsNaN(RD_data[k - 1])) {
            idx = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (idx == 0) {
        idx = 1;
      } else {
        ex = RD_data[idx - 1];
        i11 = idx + 1;
        for (k = i11; k <= n; k++) {
          d2 = RD_data[k - 1];
          if (ex > d2) {
            ex = d2;
            idx = k;
          }
        }
      }
    }

    min5_idx[i] = idx;
    RD_data[idx - 1] = rtInf;
  }
}

/* End of code generation (Coder_min5.c) */
