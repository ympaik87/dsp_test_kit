/*
 * Coder_SingleThresholdCt.c
 *
 * Code generation for function 'Coder_SingleThresholdCt'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_SingleThresholdCt.h"

/* Function Definitions */
double Coder_SingleThresholdCt(const double ABSD_data[], double MFC, double TC,
  double Thrd)
{
  double cycle;
  int Ct_tmp;
  int i;
  boolean_T exitg1;
  double b_i;
  cycle = MFC;
  Ct_tmp = (int)(TC + (1.0 - (MFC + 1.0)));
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i <= Ct_tmp - 1)) {
    b_i = (MFC + 1.0) + (double)i;
    if ((ABSD_data[(int)(b_i - 1.0) - 1] < Thrd) && (ABSD_data[(int)b_i - 1] >
         Thrd)) {
      cycle = b_i;
      exitg1 = true;
    } else {
      i++;
    }
  }

  Ct_tmp = (int)cycle;
  b_i = ABSD_data[Ct_tmp - 1];
  return (Thrd - b_i) / (b_i - ABSD_data[Ct_tmp - 2]) + cycle;
}

/* End of code generation (Coder_SingleThresholdCt.c) */
