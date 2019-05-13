/*
 * Coder_jumping_correction6.c
 *
 * Code generation for function 'Coder_jumping_correction6'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_jumping_correction6.h"
#include "AutoBaseline_v2_emxutil.h"
#include "Coder_Jump2orNot.h"
#include "mean.h"
#include "Coder_clfy.h"

/* Function Definitions */
void Coder_jumping_correction6(double RD_data[], int RD_size[1], double
  Criterion, double Criterion_bdry, double HTC, double *num_jumping, double
  ivd_cdd_output_data[], int ivd_cdd_output_size[2])
{
  int n;
  int idx;
  double min_val;
  int k;
  boolean_T exitg1;
  int i27;
  double ex;
  double d3;
  emxArray_real_T *jumping;
  emxArray_real_T *ivd_cdd;
  double RD_scale;
  int L_ivd_cdd_output;
  int loop_ub;
  double RD_diff2_data[99];
  int RD_diff2_multi_size_idx_0;
  double RD_diff2_multi_data[100];
  int i28;
  int i29;
  int i30;
  int i31;
  int loop_ub_tmp;
  signed char tmp_data[99];
  int b_tmp_data[98];
  int ii_data[100];
  signed char c_tmp_data[98];
  int d_tmp_data[99];
  int cycles_size_idx_0;
  double absxk;
  boolean_T x_data[100];
  emxArray_real_T *jumping1_idx;
  emxArray_real_T *jumping2_idx;
  emxArray_real_T *jumping1_diff;
  emxArray_real_T *jumping2_diff;
  double LC2;
  emxArray_real_T *b_jumping2_diff;
  int i;
  signed char cycles_data[100];
  emxArray_boolean_T *x;
  boolean_T tf;
  int exponent;
  boolean_T p;
  double RD[2];
  double dif;
  unsigned int i_jump1;
  unsigned int i_jump2;
  double b_RD[3];
  double varargin_1_data[199];
  signed char e_tmp_data[100];
  double b_RD_data[100];
  n = RD_size[0];
  if (RD_size[0] <= 2) {
    if (RD_size[0] == 1) {
      min_val = RD_data[0];
    } else if ((RD_data[0] < RD_data[1]) || (rtIsNaN(RD_data[0]) && (!rtIsNaN
                 (RD_data[1])))) {
      min_val = RD_data[1];
    } else {
      min_val = RD_data[0];
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
      min_val = RD_data[0];
    } else {
      min_val = RD_data[idx - 1];
      i27 = idx + 1;
      for (k = i27; k <= n; k++) {
        d3 = RD_data[k - 1];
        if (min_val < d3) {
          min_val = d3;
        }
      }
    }
  }

  n = RD_size[0];
  if (RD_size[0] <= 2) {
    if (RD_size[0] == 1) {
      ex = RD_data[0];
    } else if ((RD_data[0] > RD_data[1]) || (rtIsNaN(RD_data[0]) && (!rtIsNaN
                 (RD_data[1])))) {
      ex = RD_data[1];
    } else {
      ex = RD_data[0];
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
      ex = RD_data[0];
    } else {
      ex = RD_data[idx - 1];
      i27 = idx + 1;
      for (k = i27; k <= n; k++) {
        d3 = RD_data[k - 1];
        if (ex > d3) {
          ex = d3;
        }
      }
    }
  }

  emxInit_real_T(&jumping, 1);
  emxInit_real_T(&ivd_cdd, 2);
  RD_scale = min_val - ex;
  *num_jumping = 0.0;
  jumping->size[0] = 0;
  ivd_cdd->size[0] = 1;
  ivd_cdd->size[1] = 0;

  /* invalid_candidate */
  if (fabs((RD_data[0] - 2.0 * RD_data[1]) + RD_data[2]) > Criterion_bdry) {
    *num_jumping = 1.0;
    RD_data[0] = RD_data[1];
  }

  L_ivd_cdd_output = RD_size[0];
  n = RD_size[0] - 1;
  loop_ub = RD_size[0];
  if (0 <= loop_ub - 2) {
    memset(&RD_diff2_data[0], 0, (unsigned int)((loop_ub + -1) * (int)sizeof
            (double)));
  }

  RD_diff2_multi_size_idx_0 = RD_size[0];
  loop_ub = RD_size[0];
  if (0 <= loop_ub - 1) {
    memset(&RD_diff2_multi_data[0], 0, (unsigned int)(loop_ub * (int)sizeof
            (double)));
  }

  if (1 > RD_size[0] - 2) {
    loop_ub = 0;
  } else {
    loop_ub = RD_size[0] - 2;
  }

  i27 = (2 <= RD_size[0] - 1);
  if (3 > RD_size[0]) {
    i28 = 1;
    i29 = 0;
  } else {
    i28 = 3;
    i29 = RD_size[0];
  }

  if (2 > RD_size[0] - 1) {
    i30 = 1;
    i31 = 0;
  } else {
    i30 = 2;
    i31 = RD_size[0] - 1;
  }

  loop_ub_tmp = (signed char)i31 - i30;
  for (i31 = 0; i31 <= loop_ub_tmp; i31++) {
    tmp_data[i31] = (signed char)((signed char)(i30 + i31) - 1);
  }

  for (i30 = 0; i30 < loop_ub; i30++) {
    b_tmp_data[i30] = 1 + i30;
  }

  loop_ub = i29 - i28;
  for (i29 = 0; i29 <= loop_ub; i29++) {
    ii_data[i29] = i28 + i29;
  }

  loop_ub = loop_ub_tmp + 1;
  for (i28 = 0; i28 < loop_ub; i28++) {
    RD_diff2_data[tmp_data[i28]] = (RD_data[b_tmp_data[i28] - 1] - 2.0 *
      RD_data[i27 + i28]) + RD_data[ii_data[i28] - 1];
  }

  i27 = (2 <= n - 1);
  if (3 > n) {
    i28 = 1;
    n = 0;
  } else {
    i28 = 3;
  }

  if (2 > RD_size[0] - 2) {
    i29 = 1;
    i30 = 0;
  } else {
    i29 = 2;
    i30 = RD_size[0] - 2;
  }

  loop_ub_tmp = (signed char)i30 - i29;
  for (i30 = 0; i30 <= loop_ub_tmp; i30++) {
    c_tmp_data[i30] = (signed char)((signed char)(i29 + i30) - 1);
  }

  loop_ub = n - i28;
  for (i29 = 0; i29 <= loop_ub; i29++) {
    d_tmp_data[i29] = i28 + i29;
  }

  loop_ub = loop_ub_tmp + 1;
  for (i28 = 0; i28 < loop_ub; i28++) {
    RD_diff2_multi_data[c_tmp_data[i28]] = RD_diff2_data[i27 + i28] *
      RD_diff2_data[d_tmp_data[i28] - 1];
  }

  if (RD_diff2_multi_size_idx_0 <= 2) {
    if (RD_diff2_multi_size_idx_0 == 1) {
      min_val = RD_diff2_multi_data[0];
    } else if ((RD_diff2_multi_data[0] > RD_diff2_multi_data[1]) || (rtIsNaN
                (RD_diff2_multi_data[0]) && (!rtIsNaN(RD_diff2_multi_data[1]))))
    {
      min_val = RD_diff2_multi_data[1];
    } else {
      min_val = RD_diff2_multi_data[0];
    }
  } else {
    if (!rtIsNaN(RD_diff2_multi_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= RD_diff2_multi_size_idx_0)) {
        if (!rtIsNaN(RD_diff2_multi_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      min_val = RD_diff2_multi_data[0];
    } else {
      min_val = RD_diff2_multi_data[idx - 1];
      i27 = idx + 1;
      for (k = i27; k <= RD_diff2_multi_size_idx_0; k++) {
        d3 = RD_diff2_multi_data[k - 1];
        if (min_val > d3) {
          min_val = d3;
        }
      }
    }
  }

  cycles_size_idx_0 = 0;
  loop_ub = 0;
  if (min_val < Criterion) {
    absxk = min_val / 5.0;
    for (i27 = 0; i27 < RD_diff2_multi_size_idx_0; i27++) {
      x_data[i27] = (RD_diff2_multi_data[i27] < absxk);
    }

    idx = 0;
    k = RD_diff2_multi_size_idx_0;
    n = 0;
    exitg1 = false;
    while ((!exitg1) && (n <= RD_diff2_multi_size_idx_0 - 1)) {
      if (x_data[n]) {
        idx++;
        if (idx >= RD_diff2_multi_size_idx_0) {
          exitg1 = true;
        } else {
          n++;
        }
      } else {
        n++;
      }
    }

    if (RD_diff2_multi_size_idx_0 == 1) {
      if (idx == 0) {
        k = 0;
      }
    } else if (1 > idx) {
      k = 0;
    } else {
      k = idx;
    }

    if ((signed char)k > 5) {
      *num_jumping += (double)(signed char)k;
    } else {
      if (min_val / 5.0 < Criterion) {
        Criterion = min_val / 5.0;
      }

      for (i27 = 0; i27 < RD_diff2_multi_size_idx_0; i27++) {
        x_data[i27] = (RD_diff2_multi_data[i27] < Criterion);
      }

      idx = 0;
      k = RD_diff2_multi_size_idx_0;
      n = 0;
      exitg1 = false;
      while ((!exitg1) && (n <= RD_diff2_multi_size_idx_0 - 1)) {
        if (x_data[n]) {
          idx++;
          ii_data[idx - 1] = n + 1;
          if (idx >= RD_diff2_multi_size_idx_0) {
            exitg1 = true;
          } else {
            n++;
          }
        } else {
          n++;
        }
      }

      if (RD_diff2_multi_size_idx_0 == 1) {
        if (idx == 0) {
          k = 0;
        }
      } else if (1 > idx) {
        k = 0;
      } else {
        k = idx;
      }

      for (i27 = 0; i27 < k; i27++) {
        RD_diff2_multi_data[i27] = ii_data[i27];
      }

      cycles_size_idx_0 = k;
      loop_ub = 1;
      for (i27 = 0; i27 < k; i27++) {
        cycles_data[i27] = (signed char)RD_diff2_multi_data[i27];
      }

      /* cycles=cycles0; */
    }
  } else {
    if (min_val < Criterion / 2.0) {
      min_val /= 3.0;
      for (i27 = 0; i27 < RD_diff2_multi_size_idx_0; i27++) {
        x_data[i27] = (RD_diff2_multi_data[i27] < min_val);
      }

      idx = 0;
      k = RD_diff2_multi_size_idx_0;
      n = 0;
      exitg1 = false;
      while ((!exitg1) && (n <= RD_diff2_multi_size_idx_0 - 1)) {
        if (x_data[n]) {
          idx++;
          if (idx >= RD_diff2_multi_size_idx_0) {
            exitg1 = true;
          } else {
            n++;
          }
        } else {
          n++;
        }
      }

      if (RD_diff2_multi_size_idx_0 == 1) {
        if (idx == 0) {
          k = 0;
        }
      } else if (1 > idx) {
        k = 0;
      } else {
        k = idx;
      }

      if (k <= 5) {
        Criterion /= 2.0;
        for (i27 = 0; i27 < RD_diff2_multi_size_idx_0; i27++) {
          x_data[i27] = (RD_diff2_multi_data[i27] < Criterion);
        }

        idx = 0;
        k = RD_diff2_multi_size_idx_0;
        n = 0;
        exitg1 = false;
        while ((!exitg1) && (n <= RD_diff2_multi_size_idx_0 - 1)) {
          if (x_data[n]) {
            idx++;
            ii_data[idx - 1] = n + 1;
            if (idx >= RD_diff2_multi_size_idx_0) {
              exitg1 = true;
            } else {
              n++;
            }
          } else {
            n++;
          }
        }

        if (RD_diff2_multi_size_idx_0 == 1) {
          if (idx == 0) {
            k = 0;
          }
        } else if (1 > idx) {
          k = 0;
        } else {
          k = idx;
        }

        for (i27 = 0; i27 < k; i27++) {
          RD_diff2_multi_data[i27] = ii_data[i27];
        }

        cycles_size_idx_0 = k;
        loop_ub = 1;
        for (i27 = 0; i27 < k; i27++) {
          cycles_data[i27] = (signed char)RD_diff2_multi_data[i27];
        }

        /* cycles=find(RD_diff2_multi<Criterion/2); */
        /* cycles=cycles0; */
      }
    }
  }

  if ((cycles_size_idx_0 != 0) && (loop_ub != 0)) {
    RD_diff2_multi_size_idx_0 = RD_size[0];
    loop_ub = RD_size[0];
    if (0 <= loop_ub - 1) {
      memcpy(&RD_diff2_multi_data[0], &RD_data[0], (unsigned int)(loop_ub * (int)
              sizeof(double)));
    }

    if (cycles_size_idx_0 <= 1) {
      cycles_size_idx_0 = 1;
    }

    emxInit_real_T(&jumping1_idx, 1);
    emxInit_real_T(&jumping2_idx, 1);
    emxInit_real_T(&jumping1_diff, 1);
    emxInit_real_T(&jumping2_diff, 1);
    LC2 = cycles_size_idx_0;
    jumping1_idx->size[0] = 0;
    jumping2_idx->size[0] = 0;
    jumping1_diff->size[0] = 0;
    jumping2_diff->size[0] = 0;
    emxInit_real_T(&b_jumping2_diff, 1);
    for (i = 0; i < cycles_size_idx_0; i++) {
      d3 = RD_data[cycles_data[i] - 2];
      i27 = cycles_data[i] - 1;
      absxk = RD_data[i27];
      if ((fabs((d3 + RD_data[cycles_data[i]]) / 2.0 - absxk) / RD_scale < 0.03)
          && (d3 < absxk) && (absxk < RD_data[cycles_data[i]])) {
        /*  jumping 작업안 */
        LC2--;
      } else {
        if (cycles_data[i] <= HTC - 3.0) {
          min_val = 0.0;
        } else {
          min_val = 0.5;
        }

        /* --------- jump1과 jump2를 구분 --------------- */
        i28 = cycles_data[i] + 1;
        if (fabs((absxk - 2.0 * RD_data[cycles_data[i]]) + RD_data[i28]) > fabs
            ((d3 - 2.0 * absxk) + RD_data[cycles_data[i]])) {
          Coder_clfy(RD_data, cycles_data[i], (double)cycles_data[i] + 1.0,
                     jumping1_idx, jumping2_idx, min_val, RD_scale);
        } else {
          Coder_clfy(RD_data, cycles_data[i], cycles_data[i], jumping1_idx,
                     jumping2_idx, min_val, RD_scale);
        }

        (*num_jumping)++;
        tf = false;
        k = 0;
        exitg1 = false;
        while ((!exitg1) && (k <= jumping1_idx->size[0] - 1)) {
          absxk = jumping1_idx->data[k];
          absxk = fabs(absxk / 2.0);
          if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
            if (absxk <= 2.2250738585072014E-308) {
              absxk = 4.94065645841247E-324;
            } else {
              frexp(absxk, &exponent);
              absxk = ldexp(1.0, exponent - 53);
            }
          } else {
            absxk = rtNaN;
          }

          p = (fabs(jumping1_idx->data[k] - (double)cycles_data[i]) < absxk);
          if (p) {
            tf = true;
            exitg1 = true;
          } else {
            k++;
          }
        }

        if (tf) {
          i29 = jumping->size[0];
          i30 = jumping->size[0];
          jumping->size[0] = i29 + 1;
          emxEnsureCapacity_real_T(jumping, i30);
          jumping->data[i29] = 1.0;
          dif = RD_data[cycles_data[i]] - RD_data[i27];
          i27 = b_jumping2_diff->size[0];
          b_jumping2_diff->size[0] = jumping1_diff->size[0] + 1;
          emxEnsureCapacity_real_T(b_jumping2_diff, i27);
          loop_ub = jumping1_diff->size[0];
          for (i27 = 0; i27 < loop_ub; i27++) {
            b_jumping2_diff->data[i27] = jumping1_diff->data[i27];
          }

          b_jumping2_diff->data[jumping1_diff->size[0]] = fabs(dif);
          i27 = jumping1_diff->size[0];
          jumping1_diff->size[0] = b_jumping2_diff->size[0];
          emxEnsureCapacity_real_T(jumping1_diff, i27);
          loop_ub = b_jumping2_diff->size[0];
          for (i27 = 0; i27 < loop_ub; i27++) {
            jumping1_diff->data[i27] = b_jumping2_diff->data[i27];
          }

          /* --------- (B) invalid_candidate -------- */
          if (i28 > RD_size[0]) {
            i27 = 0;
            i29 = 0;
          } else {
            i27 = cycles_data[i];
            i29 = RD_size[0];
          }

          if (i28 > RD_size[0]) {
            i30 = 0;
            i31 = 0;
          } else {
            i30 = cycles_data[i];
            i31 = RD_size[0];
          }

          loop_ub_tmp = i29 - i27;
          for (i29 = 0; i29 < loop_ub_tmp; i29++) {
            varargin_1_data[i29] = RD_data[i27 + i29];
          }

          n = loop_ub_tmp - 1;
          if (loop_ub_tmp <= 2) {
            if (loop_ub_tmp == 1) {
              min_val = RD_data[i27];
            } else {
              min_val = RD_data[i27 + 1];
              if ((RD_data[i27] > min_val) || (rtIsNaN(RD_data[i27]) &&
                   (!rtIsNaN(min_val)))) {
              } else {
                min_val = RD_data[i27];
              }
            }
          } else {
            if (!rtIsNaN(varargin_1_data[0])) {
              idx = 1;
            } else {
              idx = 0;
              k = 2;
              exitg1 = false;
              while ((!exitg1) && (k <= loop_ub_tmp)) {
                if (!rtIsNaN(varargin_1_data[k - 1])) {
                  idx = k;
                  exitg1 = true;
                } else {
                  k++;
                }
              }
            }

            if (idx == 0) {
              min_val = RD_data[i27];
            } else {
              min_val = varargin_1_data[idx - 1];
              i27 = idx + 1;
              for (k = i27; k <= n + 1; k++) {
                d3 = varargin_1_data[k - 1];
                if (min_val > d3) {
                  min_val = d3;
                }
              }
            }
          }

          loop_ub_tmp = i31 - i30;
          for (i27 = 0; i27 < loop_ub_tmp; i27++) {
            varargin_1_data[i27] = RD_data[i30 + i27];
          }

          n = loop_ub_tmp - 1;
          if (loop_ub_tmp <= 2) {
            if (loop_ub_tmp == 1) {
              ex = RD_data[i30];
            } else {
              ex = RD_data[i30 + 1];
              if ((RD_data[i30] < ex) || (rtIsNaN(RD_data[i30]) && (!rtIsNaN(ex))))
              {
              } else {
                ex = RD_data[i30];
              }
            }
          } else {
            if (!rtIsNaN(varargin_1_data[0])) {
              idx = 1;
            } else {
              idx = 0;
              k = 2;
              exitg1 = false;
              while ((!exitg1) && (k <= loop_ub_tmp)) {
                if (!rtIsNaN(varargin_1_data[k - 1])) {
                  idx = k;
                  exitg1 = true;
                } else {
                  k++;
                }
              }
            }

            if (idx == 0) {
              ex = RD_data[i30];
            } else {
              ex = varargin_1_data[idx - 1];
              i27 = idx + 1;
              for (k = i27; k <= n + 1; k++) {
                d3 = varargin_1_data[k - 1];
                if (ex < d3) {
                  ex = d3;
                }
              }
            }
          }

          if (dif / (min_val - ex) > 0.2) {
            i27 = ivd_cdd->size[1];
            i29 = ivd_cdd->size[0] * ivd_cdd->size[1];
            ivd_cdd->size[1] = i27 + 1;
            emxEnsureCapacity_real_T(ivd_cdd, i29);
            ivd_cdd->data[i27] = (double)cycles_data[i] + 1.0;
          }

          /* --------- (E) invalid_candidate -------- */
          if (cycles_data[i] + 1 > RD_size[0]) {
            i27 = 1;
          } else {
            i27 = cycles_data[i] + 1;
          }

          if (i28 > RD_size[0]) {
            i28 = 1;
            i29 = 0;
          } else {
            i29 = RD_size[0];
          }

          loop_ub_tmp = (signed char)i29 - (signed char)i28;
          for (i29 = 0; i29 <= loop_ub_tmp; i29++) {
            e_tmp_data[i29] = (signed char)((signed char)((signed char)i28 +
              (signed char)i29) - 1);
          }

          loop_ub_tmp++;
          for (i28 = 0; i28 < loop_ub_tmp; i28++) {
            b_RD_data[i28] = RD_data[(i27 + i28) - 1] - dif;
          }

          for (i27 = 0; i27 < loop_ub_tmp; i27++) {
            RD_data[e_tmp_data[i27]] = b_RD_data[i27];
          }
        } else {
          i27 = jumping->size[0];
          i28 = jumping->size[0];
          jumping->size[0] = i27 + 1;
          emxEnsureCapacity_real_T(jumping, i28);
          jumping->data[i27] = 2.0;
          RD[0] = RD_data[(int)(jumping2_idx->data[jumping2_idx->size[0] - 1] -
                                1.0) - 1];
          RD[1] = RD_data[(int)(jumping2_idx->data[jumping2_idx->size[0] - 1] +
                                1.0) - 1];
          d3 = fabs(RD_data[(int)jumping2_idx->data[jumping2_idx->size[0] - 1] -
                    1] - b_mean(RD));
          i27 = b_jumping2_diff->size[0];
          b_jumping2_diff->size[0] = jumping2_diff->size[0] + 1;
          emxEnsureCapacity_real_T(b_jumping2_diff, i27);
          loop_ub = jumping2_diff->size[0];
          for (i27 = 0; i27 < loop_ub; i27++) {
            b_jumping2_diff->data[i27] = jumping2_diff->data[i27];
          }

          b_jumping2_diff->data[jumping2_diff->size[0]] = d3;
          i27 = jumping2_diff->size[0];
          jumping2_diff->size[0] = b_jumping2_diff->size[0];
          emxEnsureCapacity_real_T(jumping2_diff, i27);
          loop_ub = b_jumping2_diff->size[0];
          for (i27 = 0; i27 < loop_ub; i27++) {
            jumping2_diff->data[i27] = b_jumping2_diff->data[i27];
          }

          /* -----(B) v5에서 바뀌는 부분 ------ */
          b_RD[0] = RD_data[(int)(jumping2_idx->data[jumping2_idx->size[0] - 1]
            - 1.0) - 1];
          b_RD[1] = RD_data[(int)jumping2_idx->data[jumping2_idx->size[0] - 1] -
            1];
          b_RD[2] = RD_data[(int)(jumping2_idx->data[jumping2_idx->size[0] - 1]
            + 1.0) - 1];
          RD_data[(int)jumping2_idx->data[jumping2_idx->size[0] - 1] - 1] =
            Coder_Jump2orNot(b_RD);

          /* ----------------------------------                 */
        }

        /* --------- jump1과 jump2를 구분 --------------- */
      }
    }

    emxFree_real_T(&b_jumping2_diff);

    /*      jumping1_idx */
    /*  jumping2_idx */
    /* -------- 위험한 jump1보정은 최소화 --------- */
    if ((jumping1_idx->size[0] == 0) + (jumping2_idx->size[0] == 0) == 0) {
      emxInit_boolean_T(&x, 1);
      absxk = c_mean(jumping2_diff);

      /*          jumping1_idx */
      /*          jumping1_diff */
      /*          jumping2_idx */
      /*          jumping2_diff */
      /*          jumping1_diff/mean_jump2_diff       */
      i27 = x->size[0];
      x->size[0] = jumping1_diff->size[0];
      emxEnsureCapacity_boolean_T(x, i27);
      loop_ub = jumping1_diff->size[0];
      for (i27 = 0; i27 < loop_ub; i27++) {
        x->data[i27] = (jumping1_diff->data[i27] / absxk < 3.0);
      }

      k = (1 <= x->size[0]);
      idx = 0;
      n = 0;
      exitg1 = false;
      while ((!exitg1) && (n <= x->size[0] - 1)) {
        if (x->data[n]) {
          idx++;
          if (idx >= k) {
            exitg1 = true;
          } else {
            n++;
          }
        } else {
          n++;
        }
      }

      emxFree_boolean_T(&x);
      if (k == 1) {
        if (idx == 0) {
          k = 0;
        }
      } else {
        k = (1 <= idx);
      }

      if (k != 0) {
        RD_size[0] = RD_diff2_multi_size_idx_0;
        if (0 <= RD_diff2_multi_size_idx_0 - 1) {
          memcpy(&RD_data[0], &RD_diff2_multi_data[0], (unsigned int)
                 (RD_diff2_multi_size_idx_0 * (int)sizeof(double)));
        }

        i_jump1 = 1U;
        i_jump2 = 1U;
        ivd_cdd->size[0] = 1;
        ivd_cdd->size[1] = 0;
        i27 = (int)LC2;
        for (i = 0; i < i27; i++) {
          if (jumping->data[i] == 1.0) {
            i28 = (int)i_jump1 - 1;
            if (jumping1_diff->data[i28] / absxk > 3.0) {
              dif = RD_data[(int)(jumping1_idx->data[i28] + 1.0) - 1] - RD_data
                [(int)jumping1_idx->data[i28] - 1];

              /* --------- (B) invalid_candidate -------- */
              if (jumping1_idx->data[i28] + 1.0 > RD_size[0]) {
                i29 = 0;
                i30 = 0;
              } else {
                i29 = (int)(jumping1_idx->data[i28] + 1.0) - 1;
                i30 = RD_size[0];
              }

              if (jumping1_idx->data[i28] + 1.0 > RD_size[0]) {
                i31 = 0;
                loop_ub = 0;
              } else {
                i31 = (int)(jumping1_idx->data[i28] + 1.0) - 1;
                loop_ub = RD_size[0];
              }

              loop_ub_tmp = i30 - i29;
              for (i30 = 0; i30 < loop_ub_tmp; i30++) {
                varargin_1_data[i30] = RD_data[i29 + i30];
              }

              n = loop_ub_tmp - 1;
              if (loop_ub_tmp <= 2) {
                if (loop_ub_tmp == 1) {
                  min_val = RD_data[i29];
                } else {
                  min_val = RD_data[i29 + 1];
                  if ((RD_data[i29] > min_val) || (rtIsNaN(RD_data[i29]) &&
                       (!rtIsNaN(min_val)))) {
                  } else {
                    min_val = RD_data[i29];
                  }
                }
              } else {
                if (!rtIsNaN(varargin_1_data[0])) {
                  idx = 1;
                } else {
                  idx = 0;
                  k = 2;
                  exitg1 = false;
                  while ((!exitg1) && (k <= loop_ub_tmp)) {
                    if (!rtIsNaN(varargin_1_data[k - 1])) {
                      idx = k;
                      exitg1 = true;
                    } else {
                      k++;
                    }
                  }
                }

                if (idx == 0) {
                  min_val = RD_data[i29];
                } else {
                  min_val = varargin_1_data[idx - 1];
                  i29 = idx + 1;
                  for (k = i29; k <= n + 1; k++) {
                    d3 = varargin_1_data[k - 1];
                    if (min_val > d3) {
                      min_val = d3;
                    }
                  }
                }
              }

              loop_ub_tmp = loop_ub - i31;
              for (i29 = 0; i29 < loop_ub_tmp; i29++) {
                varargin_1_data[i29] = RD_data[i31 + i29];
              }

              n = loop_ub_tmp - 1;
              if (loop_ub_tmp <= 2) {
                if (loop_ub_tmp == 1) {
                  ex = RD_data[i31];
                } else {
                  ex = RD_data[i31 + 1];
                  if ((RD_data[i31] < ex) || (rtIsNaN(RD_data[i31]) && (!rtIsNaN
                        (ex)))) {
                  } else {
                    ex = RD_data[i31];
                  }
                }
              } else {
                if (!rtIsNaN(varargin_1_data[0])) {
                  idx = 1;
                } else {
                  idx = 0;
                  k = 2;
                  exitg1 = false;
                  while ((!exitg1) && (k <= loop_ub_tmp)) {
                    if (!rtIsNaN(varargin_1_data[k - 1])) {
                      idx = k;
                      exitg1 = true;
                    } else {
                      k++;
                    }
                  }
                }

                if (idx == 0) {
                  ex = RD_data[i31];
                } else {
                  ex = varargin_1_data[idx - 1];
                  i29 = idx + 1;
                  for (k = i29; k <= n + 1; k++) {
                    d3 = varargin_1_data[k - 1];
                    if (ex < d3) {
                      ex = d3;
                    }
                  }
                }
              }

              if (dif / (min_val - ex) > 0.2) {
                i29 = ivd_cdd->size[1];
                i30 = ivd_cdd->size[0] * ivd_cdd->size[1];
                ivd_cdd->size[1] = i29 + 1;
                emxEnsureCapacity_real_T(ivd_cdd, i30);
                ivd_cdd->data[i29] = jumping1_idx->data[i28] + 1.0;
              }

              /* --------- (E) invalid_candidate -------- */
              if (jumping1_idx->data[(int)i_jump1 - 1] + 1.0 > RD_size[0]) {
                i29 = 0;
              } else {
                i29 = (int)(jumping1_idx->data[(int)i_jump1 - 1] + 1.0) - 1;
              }

              if (jumping1_idx->data[i28] + 1.0 > RD_size[0]) {
                i28 = 1;
                i30 = 0;
              } else {
                i28 = (int)(jumping1_idx->data[i28] + 1.0);
                i30 = RD_size[0];
              }

              loop_ub_tmp = (signed char)i30 - (signed char)i28;
              for (i30 = 0; i30 <= loop_ub_tmp; i30++) {
                e_tmp_data[i30] = (signed char)((signed char)((signed char)i28 +
                  (signed char)i30) - 1);
              }

              loop_ub_tmp++;
              for (i28 = 0; i28 < loop_ub_tmp; i28++) {
                b_RD_data[i28] = RD_data[i29 + i28] - dif;
              }

              for (i28 = 0; i28 < loop_ub_tmp; i28++) {
                RD_data[e_tmp_data[i28]] = b_RD_data[i28];
              }
            } else if (fabs((RD_data[(int)jumping1_idx->data[i28] - 1] - 2.0 *
                             RD_data[(int)(jumping1_idx->data[i28] + 1.0) - 1])
                            + RD_data[(int)(jumping1_idx->data[i28] + 2.0) - 1])
                       > fabs((RD_data[(int)(jumping1_idx->data[i28] - 1.0) - 1]
                               - 2.0 * RD_data[(int)jumping1_idx->data[i28] - 1])
                              + RD_data[(int)(jumping1_idx->data[i28] + 1.0) - 1]))
            {
              b_RD[0] = RD_data[(int)jumping1_idx->data[i28] - 1];
              b_RD[1] = RD_data[(int)(jumping1_idx->data[i28] + 1.0) - 1];
              b_RD[2] = RD_data[(int)(jumping1_idx->data[i28] + 2.0) - 1];
              RD_data[(int)(jumping1_idx->data[i28] + 1.0) - 1] =
                Coder_Jump2orNot(b_RD);
            } else {
              b_RD[0] = RD_data[(int)(jumping1_idx->data[i28] - 1.0) - 1];
              b_RD[1] = RD_data[(int)jumping1_idx->data[i28] - 1];
              b_RD[2] = RD_data[(int)(jumping1_idx->data[i28] + 1.0) - 1];
              RD_data[(int)jumping1_idx->data[i28] - 1] = Coder_Jump2orNot(b_RD);
            }

            i_jump1++;
          } else {
            n = (int)i_jump2 - 1;
            b_RD[0] = RD_data[(int)(jumping2_idx->data[n] - 1.0) - 1];
            b_RD[1] = RD_data[(int)jumping2_idx->data[n] - 1];
            b_RD[2] = RD_data[(int)(jumping2_idx->data[n] + 1.0) - 1];
            RD_data[(int)jumping2_idx->data[n] - 1] = Coder_Jump2orNot(b_RD);
            i_jump2++;
          }
        }
      }
    }

    emxFree_real_T(&jumping2_diff);
    emxFree_real_T(&jumping1_diff);
    emxFree_real_T(&jumping2_idx);
    emxFree_real_T(&jumping1_idx);

    /* -------- 위험한 jump1보정은 최소화 --------- */
  }

  emxFree_real_T(&jumping);
  d3 = RD_data[RD_size[0] - 1];
  absxk = RD_data[RD_size[0] - 2];
  if (((RD_data[RD_size[0] - 3] - 2.0 * absxk) + d3 < -Criterion_bdry) && (d3 <
       absxk)) {
    (*num_jumping)++;
    RD_data[RD_size[0] - 1] = absxk;
  }

  n = ivd_cdd->size[1];
  if (n < L_ivd_cdd_output) {
    L_ivd_cdd_output = n;
  }

  /*  ivd_cdd_output=zeros(L_ivd_cdd_output,1); */
  if (1 > L_ivd_cdd_output) {
    loop_ub = 0;
  } else {
    loop_ub = L_ivd_cdd_output;
  }

  ivd_cdd_output_size[0] = 1;
  ivd_cdd_output_size[1] = loop_ub;
  for (i27 = 0; i27 < loop_ub; i27++) {
    ivd_cdd_output_data[i27] = ivd_cdd->data[i27];
  }

  emxFree_real_T(&ivd_cdd);
}

/* End of code generation (Coder_jumping_correction6.c) */
