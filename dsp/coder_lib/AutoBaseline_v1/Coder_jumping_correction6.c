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
#include "AutoBaseline_v1.h"
#include "Coder_jumping_correction6.h"
#include "AutoBaseline_v1_emxutil.h"
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
  int i23;
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
  int i24;
  int i25;
  int i26;
  int i27;
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
      i23 = idx + 1;
      for (k = i23; k <= n; k++) {
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
      i23 = idx + 1;
      for (k = i23; k <= n; k++) {
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

  i23 = (2 <= RD_size[0] - 1);
  if (3 > RD_size[0]) {
    i24 = 1;
    i25 = 0;
  } else {
    i24 = 3;
    i25 = RD_size[0];
  }

  if (2 > RD_size[0] - 1) {
    i26 = 1;
    i27 = 0;
  } else {
    i26 = 2;
    i27 = RD_size[0] - 1;
  }

  loop_ub_tmp = (signed char)i27 - i26;
  for (i27 = 0; i27 <= loop_ub_tmp; i27++) {
    tmp_data[i27] = (signed char)((signed char)(i26 + i27) - 1);
  }

  for (i26 = 0; i26 < loop_ub; i26++) {
    b_tmp_data[i26] = 1 + i26;
  }

  loop_ub = i25 - i24;
  for (i25 = 0; i25 <= loop_ub; i25++) {
    ii_data[i25] = i24 + i25;
  }

  loop_ub = loop_ub_tmp + 1;
  for (i24 = 0; i24 < loop_ub; i24++) {
    RD_diff2_data[tmp_data[i24]] = (RD_data[b_tmp_data[i24] - 1] - 2.0 *
      RD_data[i23 + i24]) + RD_data[ii_data[i24] - 1];
  }

  i23 = (2 <= n - 1);
  if (3 > n) {
    i24 = 1;
    n = 0;
  } else {
    i24 = 3;
  }

  if (2 > RD_size[0] - 2) {
    i25 = 1;
    i26 = 0;
  } else {
    i25 = 2;
    i26 = RD_size[0] - 2;
  }

  loop_ub_tmp = (signed char)i26 - i25;
  for (i26 = 0; i26 <= loop_ub_tmp; i26++) {
    c_tmp_data[i26] = (signed char)((signed char)(i25 + i26) - 1);
  }

  loop_ub = n - i24;
  for (i25 = 0; i25 <= loop_ub; i25++) {
    d_tmp_data[i25] = i24 + i25;
  }

  loop_ub = loop_ub_tmp + 1;
  for (i24 = 0; i24 < loop_ub; i24++) {
    RD_diff2_multi_data[c_tmp_data[i24]] = RD_diff2_data[i23 + i24] *
      RD_diff2_data[d_tmp_data[i24] - 1];
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
      i23 = idx + 1;
      for (k = i23; k <= RD_diff2_multi_size_idx_0; k++) {
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
    for (i23 = 0; i23 < RD_diff2_multi_size_idx_0; i23++) {
      x_data[i23] = (RD_diff2_multi_data[i23] < absxk);
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

      for (i23 = 0; i23 < RD_diff2_multi_size_idx_0; i23++) {
        x_data[i23] = (RD_diff2_multi_data[i23] < Criterion);
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

      for (i23 = 0; i23 < k; i23++) {
        RD_diff2_multi_data[i23] = ii_data[i23];
      }

      cycles_size_idx_0 = k;
      loop_ub = 1;
      for (i23 = 0; i23 < k; i23++) {
        cycles_data[i23] = (signed char)RD_diff2_multi_data[i23];
      }

      /* cycles=cycles0; */
    }
  } else {
    if (min_val < Criterion / 2.0) {
      min_val /= 3.0;
      for (i23 = 0; i23 < RD_diff2_multi_size_idx_0; i23++) {
        x_data[i23] = (RD_diff2_multi_data[i23] < min_val);
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
        for (i23 = 0; i23 < RD_diff2_multi_size_idx_0; i23++) {
          x_data[i23] = (RD_diff2_multi_data[i23] < Criterion);
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

        for (i23 = 0; i23 < k; i23++) {
          RD_diff2_multi_data[i23] = ii_data[i23];
        }

        cycles_size_idx_0 = k;
        loop_ub = 1;
        for (i23 = 0; i23 < k; i23++) {
          cycles_data[i23] = (signed char)RD_diff2_multi_data[i23];
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
      i23 = cycles_data[i] - 1;
      absxk = RD_data[i23];
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
        i24 = cycles_data[i] + 1;
        if (fabs((absxk - 2.0 * RD_data[cycles_data[i]]) + RD_data[i24]) > fabs
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
          i25 = jumping->size[0];
          i26 = jumping->size[0];
          jumping->size[0] = i25 + 1;
          emxEnsureCapacity_real_T(jumping, i26);
          jumping->data[i25] = 1.0;
          dif = RD_data[cycles_data[i]] - RD_data[i23];
          i23 = b_jumping2_diff->size[0];
          b_jumping2_diff->size[0] = jumping1_diff->size[0] + 1;
          emxEnsureCapacity_real_T(b_jumping2_diff, i23);
          loop_ub = jumping1_diff->size[0];
          for (i23 = 0; i23 < loop_ub; i23++) {
            b_jumping2_diff->data[i23] = jumping1_diff->data[i23];
          }

          b_jumping2_diff->data[jumping1_diff->size[0]] = fabs(dif);
          i23 = jumping1_diff->size[0];
          jumping1_diff->size[0] = b_jumping2_diff->size[0];
          emxEnsureCapacity_real_T(jumping1_diff, i23);
          loop_ub = b_jumping2_diff->size[0];
          for (i23 = 0; i23 < loop_ub; i23++) {
            jumping1_diff->data[i23] = b_jumping2_diff->data[i23];
          }

          /* --------- (B) invalid_candidate -------- */
          if (i24 > RD_size[0]) {
            i23 = 0;
            i25 = 0;
          } else {
            i23 = cycles_data[i];
            i25 = RD_size[0];
          }

          if (i24 > RD_size[0]) {
            i26 = 0;
            i27 = 0;
          } else {
            i26 = cycles_data[i];
            i27 = RD_size[0];
          }

          loop_ub_tmp = i25 - i23;
          for (i25 = 0; i25 < loop_ub_tmp; i25++) {
            varargin_1_data[i25] = RD_data[i23 + i25];
          }

          n = loop_ub_tmp - 1;
          if (loop_ub_tmp <= 2) {
            if (loop_ub_tmp == 1) {
              min_val = RD_data[i23];
            } else {
              min_val = RD_data[i23 + 1];
              if ((RD_data[i23] > min_val) || (rtIsNaN(RD_data[i23]) &&
                   (!rtIsNaN(min_val)))) {
              } else {
                min_val = RD_data[i23];
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
              min_val = RD_data[i23];
            } else {
              min_val = varargin_1_data[idx - 1];
              i23 = idx + 1;
              for (k = i23; k <= n + 1; k++) {
                d3 = varargin_1_data[k - 1];
                if (min_val > d3) {
                  min_val = d3;
                }
              }
            }
          }

          loop_ub_tmp = i27 - i26;
          for (i23 = 0; i23 < loop_ub_tmp; i23++) {
            varargin_1_data[i23] = RD_data[i26 + i23];
          }

          n = loop_ub_tmp - 1;
          if (loop_ub_tmp <= 2) {
            if (loop_ub_tmp == 1) {
              ex = RD_data[i26];
            } else {
              ex = RD_data[i26 + 1];
              if ((RD_data[i26] < ex) || (rtIsNaN(RD_data[i26]) && (!rtIsNaN(ex))))
              {
              } else {
                ex = RD_data[i26];
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
              ex = RD_data[i26];
            } else {
              ex = varargin_1_data[idx - 1];
              i23 = idx + 1;
              for (k = i23; k <= n + 1; k++) {
                d3 = varargin_1_data[k - 1];
                if (ex < d3) {
                  ex = d3;
                }
              }
            }
          }

          if (dif / (min_val - ex) > 0.2) {
            i23 = ivd_cdd->size[1];
            i25 = ivd_cdd->size[0] * ivd_cdd->size[1];
            ivd_cdd->size[1] = i23 + 1;
            emxEnsureCapacity_real_T(ivd_cdd, i25);
            ivd_cdd->data[i23] = (double)cycles_data[i] + 1.0;
          }

          /* --------- (E) invalid_candidate -------- */
          if (cycles_data[i] + 1 > RD_size[0]) {
            i23 = 1;
          } else {
            i23 = cycles_data[i] + 1;
          }

          if (i24 > RD_size[0]) {
            i24 = 1;
            i25 = 0;
          } else {
            i25 = RD_size[0];
          }

          loop_ub_tmp = (signed char)i25 - (signed char)i24;
          for (i25 = 0; i25 <= loop_ub_tmp; i25++) {
            e_tmp_data[i25] = (signed char)((signed char)((signed char)i24 +
              (signed char)i25) - 1);
          }

          loop_ub_tmp++;
          for (i24 = 0; i24 < loop_ub_tmp; i24++) {
            b_RD_data[i24] = RD_data[(i23 + i24) - 1] - dif;
          }

          for (i23 = 0; i23 < loop_ub_tmp; i23++) {
            RD_data[e_tmp_data[i23]] = b_RD_data[i23];
          }
        } else {
          i23 = jumping->size[0];
          i24 = jumping->size[0];
          jumping->size[0] = i23 + 1;
          emxEnsureCapacity_real_T(jumping, i24);
          jumping->data[i23] = 2.0;
          RD[0] = RD_data[(int)(jumping2_idx->data[jumping2_idx->size[0] - 1] -
                                1.0) - 1];
          RD[1] = RD_data[(int)(jumping2_idx->data[jumping2_idx->size[0] - 1] +
                                1.0) - 1];
          d3 = fabs(RD_data[(int)jumping2_idx->data[jumping2_idx->size[0] - 1] -
                    1] - b_mean(RD));
          i23 = b_jumping2_diff->size[0];
          b_jumping2_diff->size[0] = jumping2_diff->size[0] + 1;
          emxEnsureCapacity_real_T(b_jumping2_diff, i23);
          loop_ub = jumping2_diff->size[0];
          for (i23 = 0; i23 < loop_ub; i23++) {
            b_jumping2_diff->data[i23] = jumping2_diff->data[i23];
          }

          b_jumping2_diff->data[jumping2_diff->size[0]] = d3;
          i23 = jumping2_diff->size[0];
          jumping2_diff->size[0] = b_jumping2_diff->size[0];
          emxEnsureCapacity_real_T(jumping2_diff, i23);
          loop_ub = b_jumping2_diff->size[0];
          for (i23 = 0; i23 < loop_ub; i23++) {
            jumping2_diff->data[i23] = b_jumping2_diff->data[i23];
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
      i23 = x->size[0];
      x->size[0] = jumping1_diff->size[0];
      emxEnsureCapacity_boolean_T(x, i23);
      loop_ub = jumping1_diff->size[0];
      for (i23 = 0; i23 < loop_ub; i23++) {
        x->data[i23] = (jumping1_diff->data[i23] / absxk < 3.0);
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
        i23 = (int)LC2;
        for (i = 0; i < i23; i++) {
          if (jumping->data[i] == 1.0) {
            i24 = (int)i_jump1 - 1;
            if (jumping1_diff->data[i24] / absxk > 3.0) {
              dif = RD_data[(int)(jumping1_idx->data[i24] + 1.0) - 1] - RD_data
                [(int)jumping1_idx->data[i24] - 1];

              /* --------- (B) invalid_candidate -------- */
              if (jumping1_idx->data[i24] + 1.0 > RD_size[0]) {
                i25 = 0;
                i26 = 0;
              } else {
                i25 = (int)(jumping1_idx->data[i24] + 1.0) - 1;
                i26 = RD_size[0];
              }

              if (jumping1_idx->data[i24] + 1.0 > RD_size[0]) {
                i27 = 0;
                loop_ub = 0;
              } else {
                i27 = (int)(jumping1_idx->data[i24] + 1.0) - 1;
                loop_ub = RD_size[0];
              }

              loop_ub_tmp = i26 - i25;
              for (i26 = 0; i26 < loop_ub_tmp; i26++) {
                varargin_1_data[i26] = RD_data[i25 + i26];
              }

              n = loop_ub_tmp - 1;
              if (loop_ub_tmp <= 2) {
                if (loop_ub_tmp == 1) {
                  min_val = RD_data[i25];
                } else {
                  min_val = RD_data[i25 + 1];
                  if ((RD_data[i25] > min_val) || (rtIsNaN(RD_data[i25]) &&
                       (!rtIsNaN(min_val)))) {
                  } else {
                    min_val = RD_data[i25];
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
                  min_val = RD_data[i25];
                } else {
                  min_val = varargin_1_data[idx - 1];
                  i25 = idx + 1;
                  for (k = i25; k <= n + 1; k++) {
                    d3 = varargin_1_data[k - 1];
                    if (min_val > d3) {
                      min_val = d3;
                    }
                  }
                }
              }

              loop_ub_tmp = loop_ub - i27;
              for (i25 = 0; i25 < loop_ub_tmp; i25++) {
                varargin_1_data[i25] = RD_data[i27 + i25];
              }

              n = loop_ub_tmp - 1;
              if (loop_ub_tmp <= 2) {
                if (loop_ub_tmp == 1) {
                  ex = RD_data[i27];
                } else {
                  ex = RD_data[i27 + 1];
                  if ((RD_data[i27] < ex) || (rtIsNaN(RD_data[i27]) && (!rtIsNaN
                        (ex)))) {
                  } else {
                    ex = RD_data[i27];
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
                  ex = RD_data[i27];
                } else {
                  ex = varargin_1_data[idx - 1];
                  i25 = idx + 1;
                  for (k = i25; k <= n + 1; k++) {
                    d3 = varargin_1_data[k - 1];
                    if (ex < d3) {
                      ex = d3;
                    }
                  }
                }
              }

              if (dif / (min_val - ex) > 0.2) {
                i25 = ivd_cdd->size[1];
                i26 = ivd_cdd->size[0] * ivd_cdd->size[1];
                ivd_cdd->size[1] = i25 + 1;
                emxEnsureCapacity_real_T(ivd_cdd, i26);
                ivd_cdd->data[i25] = jumping1_idx->data[i24] + 1.0;
              }

              /* --------- (E) invalid_candidate -------- */
              if (jumping1_idx->data[(int)i_jump1 - 1] + 1.0 > RD_size[0]) {
                i25 = 0;
              } else {
                i25 = (int)(jumping1_idx->data[(int)i_jump1 - 1] + 1.0) - 1;
              }

              if (jumping1_idx->data[i24] + 1.0 > RD_size[0]) {
                i24 = 1;
                i26 = 0;
              } else {
                i24 = (int)(jumping1_idx->data[i24] + 1.0);
                i26 = RD_size[0];
              }

              loop_ub_tmp = (signed char)i26 - (signed char)i24;
              for (i26 = 0; i26 <= loop_ub_tmp; i26++) {
                e_tmp_data[i26] = (signed char)((signed char)((signed char)i24 +
                  (signed char)i26) - 1);
              }

              loop_ub_tmp++;
              for (i24 = 0; i24 < loop_ub_tmp; i24++) {
                b_RD_data[i24] = RD_data[i25 + i24] - dif;
              }

              for (i24 = 0; i24 < loop_ub_tmp; i24++) {
                RD_data[e_tmp_data[i24]] = b_RD_data[i24];
              }
            } else if (fabs((RD_data[(int)jumping1_idx->data[i24] - 1] - 2.0 *
                             RD_data[(int)(jumping1_idx->data[i24] + 1.0) - 1])
                            + RD_data[(int)(jumping1_idx->data[i24] + 2.0) - 1])
                       > fabs((RD_data[(int)(jumping1_idx->data[i24] - 1.0) - 1]
                               - 2.0 * RD_data[(int)jumping1_idx->data[i24] - 1])
                              + RD_data[(int)(jumping1_idx->data[i24] + 1.0) - 1]))
            {
              b_RD[0] = RD_data[(int)jumping1_idx->data[i24] - 1];
              b_RD[1] = RD_data[(int)(jumping1_idx->data[i24] + 1.0) - 1];
              b_RD[2] = RD_data[(int)(jumping1_idx->data[i24] + 2.0) - 1];
              RD_data[(int)(jumping1_idx->data[i24] + 1.0) - 1] =
                Coder_Jump2orNot(b_RD);
            } else {
              b_RD[0] = RD_data[(int)(jumping1_idx->data[i24] - 1.0) - 1];
              b_RD[1] = RD_data[(int)jumping1_idx->data[i24] - 1];
              b_RD[2] = RD_data[(int)(jumping1_idx->data[i24] + 1.0) - 1];
              RD_data[(int)jumping1_idx->data[i24] - 1] = Coder_Jump2orNot(b_RD);
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
  for (i23 = 0; i23 < loop_ub; i23++) {
    ivd_cdd_output_data[i23] = ivd_cdd->data[i23];
  }

  emxFree_real_T(&ivd_cdd);
}

/* End of code generation (Coder_jumping_correction6.c) */
