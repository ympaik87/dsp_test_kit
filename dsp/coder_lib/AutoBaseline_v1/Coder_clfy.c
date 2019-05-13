/*
 * Coder_clfy.c
 *
 * Code generation for function 'Coder_clfy'
 *
 */

/* Include files */
#include <math.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v1.h"
#include "Coder_clfy.h"
#include "AutoBaseline_v1_emxutil.h"

/* Function Definitions */
void Coder_clfy(const double RD_data[], double cc, double i, emxArray_real_T
                *jumping1_idx, emxArray_real_T *jumping2_idx, double ratio,
                double RD_scale)
{
  double A_tmp;
  double A[3];
  double b_A_tmp;
  double c_A_tmp;
  signed char B[3];
  int b_i;
  double RD_diff;
  int idx;
  int k;
  boolean_T exitg1;
  int i28;
  double cri;
  A_tmp = RD_data[(int)(i - 1.0) - 1];
  A[0] = A_tmp;
  b_A_tmp = RD_data[(int)i - 1];
  A[1] = b_A_tmp;
  c_A_tmp = RD_data[(int)(i + 1.0) - 1];
  A[2] = c_A_tmp;
  B[0] = 0;
  B[1] = 0;
  B[2] = 0;
  for (b_i = 0; b_i < 3; b_i++) {
    if (!rtIsNaN(A[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k < 4)) {
        if (!rtIsNaN(A[k - 1])) {
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
      cri = A[idx - 1];
      i28 = idx + 1;
      for (k = i28; k < 4; k++) {
        RD_diff = A[k - 1];
        if (cri > RD_diff) {
          cri = RD_diff;
          idx = k;
        }
      }
    }

    B[idx - 1] = (signed char)(1 + b_i);
    A[idx - 1] = rtInf;
  }

  RD_diff = RD_data[(int)(cc + 1.0) - 1] - RD_data[(int)cc - 1];
  if (B[1] == 1) {
    /* RD(i)가 최소일때 */
    if (B[0] > B[2]) {
      /* RD(i-1)>RD(i+1) */
      if (i == cc) {
        cri = (A_tmp + b_A_tmp) / 2.0;

        /* cc<cc+1, cc+1을 jump1로 내려도 됨 */
      } else {
        /* i==cc+1 */
        cri = (A_tmp + 2.0 * RD_data[(int)i - 1]) / 3.0;

        /* cc>cc+1인 경우 최대한 jump1을 자제 */
      }

      if ((fabs(RD_diff) / RD_scale > ratio) && (c_A_tmp < cri)) {
        i28 = jumping1_idx->size[0];
        b_i = jumping1_idx->size[0];
        jumping1_idx->size[0] = i28 + 1;
        emxEnsureCapacity_real_T(jumping1_idx, b_i);
        jumping1_idx->data[i28] = cc;
      } else {
        i28 = jumping2_idx->size[0];
        b_i = jumping2_idx->size[0];
        jumping2_idx->size[0] = i28 + 1;
        emxEnsureCapacity_real_T(jumping2_idx, b_i);
        jumping2_idx->data[i28] = i;

        /* 올림 */
      }
    } else {
      /* RD(i-1)<RD(i+1) */
      if (i == cc) {
        cri = (RD_data[(int)i - 1] + RD_data[(int)(i + 1.0) - 1]) / 2.0;

        /* cc<cc+1, cc+1을 jump1로 내려도 됨 */
      } else {
        /* i==cc+1 */
        cri = (2.0 * RD_data[(int)i - 1] + RD_data[(int)(i + 1.0) - 1]) / 3.0;

        /* cc>cc+1인 경우 최대한 jump1을 자제 */
      }

      if ((fabs(RD_diff) / RD_scale > ratio) && (A_tmp < cri)) {
        i28 = jumping1_idx->size[0];
        b_i = jumping1_idx->size[0];
        jumping1_idx->size[0] = i28 + 1;
        emxEnsureCapacity_real_T(jumping1_idx, b_i);
        jumping1_idx->data[i28] = cc;
      } else {
        i28 = jumping2_idx->size[0];
        b_i = jumping2_idx->size[0];
        jumping2_idx->size[0] = i28 + 1;
        emxEnsureCapacity_real_T(jumping2_idx, b_i);
        jumping2_idx->data[i28] = i;

        /* 올림 */
      }
    }
  } else if (B[1] == 3) {
    /* RD(i)가 최대일때 */
    if (B[0] > B[2]) {
      /* RD(i-1)>RD(i+1) */
      if (i == cc) {
        cri = (2.0 * RD_data[(int)i - 1] + c_A_tmp) / 3.0;

        /* cc>cc+1인 경우 최대한 jump1을 자제 */
      } else {
        cri = (b_A_tmp + c_A_tmp) / 2.0;
      }

      if ((fabs(RD_diff) / RD_scale > ratio) && (A_tmp > cri)) {
        i28 = jumping1_idx->size[0];
        b_i = jumping1_idx->size[0];
        jumping1_idx->size[0] = i28 + 1;
        emxEnsureCapacity_real_T(jumping1_idx, b_i);
        jumping1_idx->data[i28] = cc;
      } else {
        i28 = jumping2_idx->size[0];
        b_i = jumping2_idx->size[0];
        jumping2_idx->size[0] = i28 + 1;
        emxEnsureCapacity_real_T(jumping2_idx, b_i);
        jumping2_idx->data[i28] = i;

        /* 내림 */
      }
    } else {
      /* RD(i-1)<RD(i+1) */
      if (i == cc) {
        cri = (2.0 * b_A_tmp + A_tmp) / 3.0;

        /* cc>cc+1인 경우 최대한 jump1을 자제 */
      } else {
        cri = (b_A_tmp + A_tmp) / 2.0;
      }

      if ((fabs(RD_diff) / RD_scale > ratio) && (c_A_tmp > cri)) {
        i28 = jumping1_idx->size[0];
        b_i = jumping1_idx->size[0];
        jumping1_idx->size[0] = i28 + 1;
        emxEnsureCapacity_real_T(jumping1_idx, b_i);
        jumping1_idx->data[i28] = cc;
      } else {
        i28 = jumping2_idx->size[0];
        b_i = jumping2_idx->size[0];
        jumping2_idx->size[0] = i28 + 1;
        emxEnsureCapacity_real_T(jumping2_idx, b_i);
        jumping2_idx->data[i28] = i;

        /* 내림 */
      }
    }
  } else if (fabs(RD_diff) / RD_scale > ratio) {
    i28 = jumping1_idx->size[0];
    b_i = jumping1_idx->size[0];
    jumping1_idx->size[0] = i28 + 1;
    emxEnsureCapacity_real_T(jumping1_idx, b_i);
    jumping1_idx->data[i28] = cc;
  } else {
    i28 = jumping2_idx->size[0];
    b_i = jumping2_idx->size[0];
    jumping2_idx->size[0] = i28 + 1;
    emxEnsureCapacity_real_T(jumping2_idx, b_i);
    jumping2_idx->data[i28] = i;
  }
}

/* End of code generation (Coder_clfy.c) */
