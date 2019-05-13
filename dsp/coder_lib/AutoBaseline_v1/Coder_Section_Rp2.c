/*
 * Coder_Section_Rp2.c
 *
 * Code generation for function 'Coder_Section_Rp2'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v1.h"
#include "Coder_Section_Rp2.h"
#include "var.h"

/* Function Definitions */
void Coder_Section_Rp2(double RPC, double SFC, double EFC, const double RD_data[],
  const int RD_size[1], const double scd_fit_data[], double *result_well, double
  *DataProcessNum, double *R_p2, double ABSD_data[], int ABSD_size[1])
{
  int i40;
  int loop_ub;
  int i41;
  int RD_size_tmp;
  int b_RD_size[1];
  double b_RD_data[100];
  if (SFC > EFC) {
    i40 = 0;
    loop_ub = 0;
    i41 = 0;
  } else {
    i40 = (int)SFC - 1;
    loop_ub = (int)EFC;
    i41 = (int)SFC - 1;
  }

  RD_size_tmp = loop_ub - i40;
  b_RD_size[0] = RD_size_tmp;
  for (loop_ub = 0; loop_ub < RD_size_tmp; loop_ub++) {
    b_RD_data[loop_ub] = RD_data[i40 + loop_ub] - scd_fit_data[i41 + loop_ub];
  }

  *R_p2 = 1.0 - var(b_RD_data, b_RD_size) / var(RD_data, RD_size);
  ABSD_size[0] = (signed char)RD_size[0];
  loop_ub = (signed char)RD_size[0];
  if (0 <= loop_ub - 1) {
    memset(&ABSD_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  if (*R_p2 > RPC) {
    ABSD_size[0] = RD_size[0];
    loop_ub = RD_size[0];
    for (i40 = 0; i40 < loop_ub; i40++) {
      ABSD_data[i40] = RD_data[i40] - scd_fit_data[i40];
    }

    /*      DataProcess(:,4)=ABSD; */
  } else {
    *result_well = 2.0;
    *DataProcessNum = 4.0;
  }
}

/* End of code generation (Coder_Section_Rp2.c) */
