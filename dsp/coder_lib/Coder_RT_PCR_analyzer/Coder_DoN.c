/*
 * Coder_DoN.c
 *
 * Code generation for function 'Coder_DoN'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_DoN.h"
#include "sum.h"
#include "diff.h"

/* Function Definitions */
double Coder_DoN(const double RD_data[], double SFC, double TC)
{
  double LSR_val;
  int loop_ub_tmp;
  double smoothed_RD_data[100];
  int x_idx_0_tmp_tmp;
  int x_idx_0_tmp;
  int i1;
  int nx;
  int i;
  int i2;
  int i3;
  int RD_size[1];
  double b_RD_data[100];
  double x_data[198];
  int x_size[1];
  int y_size[1];
  double y_data[198];
  double ex;
  boolean_T exitg1;
  double varargin_1_data[199];
  double d1;
  double b_ex;
  emxArray_real_T b_y_data;
  loop_ub_tmp = (int)TC;
  if (0 <= loop_ub_tmp - 1) {
    memset(&smoothed_RD_data[0], 0, (unsigned int)(loop_ub_tmp * (int)sizeof
            (double)));
  }

  x_idx_0_tmp_tmp = (int)SFC;
  x_idx_0_tmp = x_idx_0_tmp_tmp - 1;
  smoothed_RD_data[x_idx_0_tmp] = (RD_data[x_idx_0_tmp] + RD_data[(int)(SFC +
    1.0) - 1]) / 2.0;
  smoothed_RD_data[(int)TC - 1] = (RD_data[(int)(TC + -1.0) - 1] + RD_data[(int)
    TC - 1]) / 2.0;
  i1 = (int)((TC - 1.0) + (1.0 - (SFC + 1.0)));
  for (nx = 0; nx < i1; nx++) {
    i = (x_idx_0_tmp_tmp + nx) + 1;
    smoothed_RD_data[i - 1] = ((RD_data[(unsigned char)(-1 + (short)i) - 1] +
      RD_data[(unsigned char)i - 1]) + RD_data[(unsigned char)(1 + (short)i) - 1])
      / 3.0;
  }

  if (SFC > TC) {
    x_idx_0_tmp = 0;
    i1 = 0;
    nx = 0;
    i2 = 1;
    loop_ub_tmp = 1;
    x_idx_0_tmp_tmp = 1;
    i3 = 1;
  } else {
    i1 = loop_ub_tmp;
    nx = (int)SFC - 1;
    i2 = x_idx_0_tmp_tmp;
    loop_ub_tmp++;
    i3 = (int)TC + 1;
  }

  i = i1 - x_idx_0_tmp;
  RD_size[0] = i;
  for (i1 = 0; i1 < i; i1++) {
    b_RD_data[i1] = RD_data[x_idx_0_tmp + i1] - smoothed_RD_data[nx + i1];
  }

  diff(b_RD_data, RD_size, x_data, x_size);
  nx = x_size[0];
  y_size[0] = (unsigned char)x_size[0];
  for (x_idx_0_tmp = 0; x_idx_0_tmp < nx; x_idx_0_tmp++) {
    y_data[x_idx_0_tmp] = fabs(x_data[x_idx_0_tmp]);
  }

  i = loop_ub_tmp - i2;
  if (i <= 2) {
    if (i == 1) {
      ex = smoothed_RD_data[i2 - 1];
    } else if ((smoothed_RD_data[i2 - 1] < smoothed_RD_data[i2]) || (rtIsNaN
                (smoothed_RD_data[i2 - 1]) && (!rtIsNaN(smoothed_RD_data[i2]))))
    {
      ex = smoothed_RD_data[i2];
    } else {
      ex = smoothed_RD_data[i2 - 1];
    }
  } else {
    ex = smoothed_RD_data[i2 - 1];
    if (!rtIsNaN(ex)) {
      nx = 1;
    } else {
      nx = 0;
      x_idx_0_tmp = 2;
      exitg1 = false;
      while ((!exitg1) && (x_idx_0_tmp <= i)) {
        if (!rtIsNaN(smoothed_RD_data[(i2 + x_idx_0_tmp) - 2])) {
          nx = x_idx_0_tmp;
          exitg1 = true;
        } else {
          x_idx_0_tmp++;
        }
      }
    }

    if (nx != 0) {
      ex = smoothed_RD_data[(i2 + nx) - 2];
      i1 = nx + 1;
      for (x_idx_0_tmp = i1; x_idx_0_tmp <= i; x_idx_0_tmp++) {
        d1 = smoothed_RD_data[(i2 + x_idx_0_tmp) - 2];
        if (ex < d1) {
          ex = d1;
        }
      }
    }
  }

  loop_ub_tmp = i3 - x_idx_0_tmp_tmp;
  for (i1 = 0; i1 < loop_ub_tmp; i1++) {
    varargin_1_data[i1] = smoothed_RD_data[(x_idx_0_tmp_tmp + i1) - 1];
  }

  if (loop_ub_tmp <= 2) {
    if (loop_ub_tmp == 1) {
      b_ex = smoothed_RD_data[x_idx_0_tmp_tmp - 1];
    } else if ((smoothed_RD_data[x_idx_0_tmp_tmp - 1] >
                smoothed_RD_data[x_idx_0_tmp_tmp]) || (rtIsNaN
                (smoothed_RD_data[x_idx_0_tmp_tmp - 1]) && (!rtIsNaN
                 (smoothed_RD_data[x_idx_0_tmp_tmp])))) {
      b_ex = smoothed_RD_data[x_idx_0_tmp_tmp];
    } else {
      b_ex = smoothed_RD_data[x_idx_0_tmp_tmp - 1];
    }
  } else {
    if (!rtIsNaN(varargin_1_data[0])) {
      nx = 1;
    } else {
      nx = 0;
      x_idx_0_tmp = 2;
      exitg1 = false;
      while ((!exitg1) && (x_idx_0_tmp <= loop_ub_tmp)) {
        if (!rtIsNaN(varargin_1_data[x_idx_0_tmp - 1])) {
          nx = x_idx_0_tmp;
          exitg1 = true;
        } else {
          x_idx_0_tmp++;
        }
      }
    }

    if (nx == 0) {
      b_ex = smoothed_RD_data[x_idx_0_tmp_tmp - 1];
    } else {
      b_ex = varargin_1_data[nx - 1];
      i1 = nx + 1;
      for (x_idx_0_tmp = i1; x_idx_0_tmp <= loop_ub_tmp; x_idx_0_tmp++) {
        d1 = varargin_1_data[x_idx_0_tmp - 1];
        if (b_ex > d1) {
          b_ex = d1;
        }
      }
    }
  }

  b_y_data.data = &y_data[0];
  b_y_data.size = &y_size[0];
  b_y_data.allocatedSize = 198;
  b_y_data.numDimensions = 1;
  b_y_data.canFreeData = false;
  LSR_val = sum(&b_y_data) / (ex - b_ex);

  /* Length Scale Ratio */
  /*  L_itv=min(EC-SFC,TC-EC); */
  /*  smoothed_ABSD=Coder_local_smoothing(ABSD); */
  /*  itv_left=ABSD(EC-L_itv:EC)-smoothed_ABSD(EC-L_itv:EC); */
  /*  itv_right=ABSD(EC:EC+L_itv)-smoothed_ABSD(EC:EC+L_itv); */
  /*  scale=max(smoothed_ABSD(SFC:TC))-min(smoothed_ABSD(SFC:TC)); */
  /*  LSR_left=sum( abs( diff(itv_left) ) )/scale; */
  /*  LSR_right=sum( abs( diff(itv_right) ) )/scale; */
  /*  LSR_right/LSR_left */
  /*  LSR_right */
  return LSR_val;
}

/* End of code generation (Coder_DoN.c) */
