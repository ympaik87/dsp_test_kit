/*
 * Coder_find_cycle.c
 *
 * Code generation for function 'Coder_find_cycle'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_find_cycle.h"

/* Function Definitions */
double Coder_find_cycle(const double ABSD_data[], const int ABSD_size[1], double
  SC, double EC)
{
  double cycle;
  int n;
  int idx;
  double RFU_rt;
  int k;
  boolean_T exitg1;
  int i16;
  double ex;
  double i;
  n = ABSD_size[0];
  if (ABSD_size[0] <= 2) {
    if (ABSD_size[0] == 1) {
      RFU_rt = ABSD_data[0];
    } else if ((ABSD_data[0] < ABSD_data[1]) || (rtIsNaN(ABSD_data[0]) &&
                (!rtIsNaN(ABSD_data[1])))) {
      RFU_rt = ABSD_data[1];
    } else {
      RFU_rt = ABSD_data[0];
    }
  } else {
    if (!rtIsNaN(ABSD_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= ABSD_size[0])) {
        if (!rtIsNaN(ABSD_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      RFU_rt = ABSD_data[0];
    } else {
      RFU_rt = ABSD_data[idx - 1];
      i16 = idx + 1;
      for (k = i16; k <= n; k++) {
        i = ABSD_data[k - 1];
        if (RFU_rt < i) {
          RFU_rt = i;
        }
      }
    }
  }

  n = ABSD_size[0];
  if (ABSD_size[0] <= 2) {
    if (ABSD_size[0] == 1) {
      ex = ABSD_data[0];
    } else if ((ABSD_data[0] > ABSD_data[1]) || (rtIsNaN(ABSD_data[0]) &&
                (!rtIsNaN(ABSD_data[1])))) {
      ex = ABSD_data[1];
    } else {
      ex = ABSD_data[0];
    }
  } else {
    if (!rtIsNaN(ABSD_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= ABSD_size[0])) {
        if (!rtIsNaN(ABSD_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      ex = ABSD_data[0];
    } else {
      ex = ABSD_data[idx - 1];
      i16 = idx + 1;
      for (k = i16; k <= n; k++) {
        i = ABSD_data[k - 1];
        if (ex > i) {
          ex = i;
        }
      }
    }
  }

  RFU_rt = (RFU_rt + ex) / 2.0;
  cycle = SC;
  i16 = (int)(EC + (1.0 - (SC + 1.0)));
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx <= i16 - 1)) {
    i = (SC + 1.0) + (double)idx;
    if ((ABSD_data[(int)(i - 1.0) - 1] < RFU_rt) && (ABSD_data[(int)i - 1] >
         RFU_rt)) {
      cycle = i;
      exitg1 = true;
    } else {
      idx++;
    }
  }

  return cycle;
}

/* End of code generation (Coder_find_cycle.c) */
