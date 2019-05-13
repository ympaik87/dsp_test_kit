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
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_jumping_correction6.h"
#include "Coder_RT_PCR_analyzer_emxutil.h"
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
  int i37;
  double ex;
  double d16;
  emxArray_real_T *jumping;
  emxArray_real_T *ivd_cdd;
  double RD_scale;
  int L_ivd_cdd_output;
  int RD_diff2_size_idx_0;
  int loop_ub;
  double RD_diff2_data[99];
  int RD_diff2_multi_size_idx_0;
  double RD_diff2_multi_data[100];
  int i38;
  int i39;
  int i40;
  int i41;
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
      i37 = idx + 1;
      for (k = i37; k <= n; k++) {
        d16 = RD_data[k - 1];
        if (min_val < d16) {
          min_val = d16;
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
      i37 = idx + 1;
      for (k = i37; k <= n; k++) {
        d16 = RD_data[k - 1];
        if (ex > d16) {
          ex = d16;
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
  RD_diff2_size_idx_0 = RD_size[0] - 1;
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

  i37 = (2 <= RD_size[0] - 1);
  if (3 > RD_size[0]) {
    i38 = 1;
    i39 = 0;
  } else {
    i38 = 3;
    i39 = RD_size[0];
  }

  if (2 > RD_size[0] - 1) {
    i40 = 1;
    i41 = 0;
  } else {
    i40 = 2;
    i41 = RD_size[0] - 1;
  }

  loop_ub_tmp = (signed char)i41 - i40;
  for (i41 = 0; i41 <= loop_ub_tmp; i41++) {
    tmp_data[i41] = (signed char)((signed char)(i40 + i41) - 1);
  }

  for (i40 = 0; i40 < loop_ub; i40++) {
    b_tmp_data[i40] = 1 + i40;
  }

  loop_ub = i39 - i38;
  for (i39 = 0; i39 <= loop_ub; i39++) {
    ii_data[i39] = i38 + i39;
  }

  loop_ub = loop_ub_tmp + 1;
  for (i38 = 0; i38 < loop_ub; i38++) {
    RD_diff2_data[tmp_data[i38]] = (RD_data[b_tmp_data[i38] - 1] - 2.0 *
      RD_data[i37 + i38]) + RD_data[ii_data[i38] - 1];
  }

  i37 = (2 <= RD_diff2_size_idx_0 - 1);
  if (3 > RD_diff2_size_idx_0) {
    i38 = 1;
    RD_diff2_size_idx_0 = 0;
  } else {
    i38 = 3;
  }

  if (2 > RD_size[0] - 2) {
    i39 = 1;
    i40 = 0;
  } else {
    i39 = 2;
    i40 = RD_size[0] - 2;
  }

  loop_ub_tmp = (signed char)i40 - i39;
  for (i40 = 0; i40 <= loop_ub_tmp; i40++) {
    c_tmp_data[i40] = (signed char)((signed char)(i39 + i40) - 1);
  }

  loop_ub = RD_diff2_size_idx_0 - i38;
  for (i39 = 0; i39 <= loop_ub; i39++) {
    d_tmp_data[i39] = i38 + i39;
  }

  loop_ub = loop_ub_tmp + 1;
  for (i38 = 0; i38 < loop_ub; i38++) {
    RD_diff2_multi_data[c_tmp_data[i38]] = RD_diff2_data[i37 + i38] *
      RD_diff2_data[d_tmp_data[i38] - 1];
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
      i37 = idx + 1;
      for (k = i37; k <= RD_diff2_multi_size_idx_0; k++) {
        d16 = RD_diff2_multi_data[k - 1];
        if (min_val > d16) {
          min_val = d16;
        }
      }
    }
  }

  cycles_size_idx_0 = 0;
  loop_ub = 0;
  if (min_val < Criterion) {
    absxk = min_val / 5.0;
    for (i37 = 0; i37 < RD_diff2_multi_size_idx_0; i37++) {
      x_data[i37] = (RD_diff2_multi_data[i37] < absxk);
    }

    idx = 0;
    k = RD_diff2_multi_size_idx_0;
    RD_diff2_size_idx_0 = 0;
    exitg1 = false;
    while ((!exitg1) && (RD_diff2_size_idx_0 <= RD_diff2_multi_size_idx_0 - 1))
    {
      if (x_data[RD_diff2_size_idx_0]) {
        idx++;
        if (idx >= RD_diff2_multi_size_idx_0) {
          exitg1 = true;
        } else {
          RD_diff2_size_idx_0++;
        }
      } else {
        RD_diff2_size_idx_0++;
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

      for (i37 = 0; i37 < RD_diff2_multi_size_idx_0; i37++) {
        x_data[i37] = (RD_diff2_multi_data[i37] < Criterion);
      }

      idx = 0;
      k = RD_diff2_multi_size_idx_0;
      RD_diff2_size_idx_0 = 0;
      exitg1 = false;
      while ((!exitg1) && (RD_diff2_size_idx_0 <= RD_diff2_multi_size_idx_0 - 1))
      {
        if (x_data[RD_diff2_size_idx_0]) {
          idx++;
          ii_data[idx - 1] = RD_diff2_size_idx_0 + 1;
          if (idx >= RD_diff2_multi_size_idx_0) {
            exitg1 = true;
          } else {
            RD_diff2_size_idx_0++;
          }
        } else {
          RD_diff2_size_idx_0++;
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

      for (i37 = 0; i37 < k; i37++) {
        RD_diff2_multi_data[i37] = ii_data[i37];
      }

      cycles_size_idx_0 = k;
      loop_ub = 1;
      for (i37 = 0; i37 < k; i37++) {
        cycles_data[i37] = (signed char)RD_diff2_multi_data[i37];
      }

      /* cycles=cycles0; */
    }
  } else {
    if (min_val < Criterion / 2.0) {
      min_val /= 3.0;
      for (i37 = 0; i37 < RD_diff2_multi_size_idx_0; i37++) {
        x_data[i37] = (RD_diff2_multi_data[i37] < min_val);
      }

      idx = 0;
      k = RD_diff2_multi_size_idx_0;
      RD_diff2_size_idx_0 = 0;
      exitg1 = false;
      while ((!exitg1) && (RD_diff2_size_idx_0 <= RD_diff2_multi_size_idx_0 - 1))
      {
        if (x_data[RD_diff2_size_idx_0]) {
          idx++;
          if (idx >= RD_diff2_multi_size_idx_0) {
            exitg1 = true;
          } else {
            RD_diff2_size_idx_0++;
          }
        } else {
          RD_diff2_size_idx_0++;
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
        for (i37 = 0; i37 < RD_diff2_multi_size_idx_0; i37++) {
          x_data[i37] = (RD_diff2_multi_data[i37] < Criterion);
        }

        idx = 0;
        k = RD_diff2_multi_size_idx_0;
        RD_diff2_size_idx_0 = 0;
        exitg1 = false;
        while ((!exitg1) && (RD_diff2_size_idx_0 <= RD_diff2_multi_size_idx_0 -
                             1)) {
          if (x_data[RD_diff2_size_idx_0]) {
            idx++;
            ii_data[idx - 1] = RD_diff2_size_idx_0 + 1;
            if (idx >= RD_diff2_multi_size_idx_0) {
              exitg1 = true;
            } else {
              RD_diff2_size_idx_0++;
            }
          } else {
            RD_diff2_size_idx_0++;
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

        for (i37 = 0; i37 < k; i37++) {
          RD_diff2_multi_data[i37] = ii_data[i37];
        }

        cycles_size_idx_0 = k;
        loop_ub = 1;
        for (i37 = 0; i37 < k; i37++) {
          cycles_data[i37] = (signed char)RD_diff2_multi_data[i37];
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
      d16 = RD_data[cycles_data[i] - 2];
      i37 = cycles_data[i] - 1;
      absxk = RD_data[i37];
      if ((fabs((d16 + RD_data[cycles_data[i]]) / 2.0 - absxk) / RD_scale < 0.03)
          && (d16 < absxk) && (absxk < RD_data[cycles_data[i]])) {
        /*  jumping 작업안 */
        LC2--;
      } else {
        if (cycles_data[i] <= HTC - 3.0) {
          min_val = 0.0;
        } else {
          min_val = 0.5;
        }

        /* --------- jump1과 jump2를 구분 --------------- */
        i38 = cycles_data[i] + 1;
        if (fabs((absxk - 2.0 * RD_data[cycles_data[i]]) + RD_data[i38]) > fabs
            ((d16 - 2.0 * absxk) + RD_data[cycles_data[i]])) {
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
          i39 = jumping->size[0];
          i40 = jumping->size[0];
          jumping->size[0] = i39 + 1;
          emxEnsureCapacity_real_T(jumping, i40);
          jumping->data[i39] = 1.0;
          dif = RD_data[cycles_data[i]] - RD_data[i37];
          i37 = b_jumping2_diff->size[0];
          b_jumping2_diff->size[0] = jumping1_diff->size[0] + 1;
          emxEnsureCapacity_real_T(b_jumping2_diff, i37);
          loop_ub = jumping1_diff->size[0];
          for (i37 = 0; i37 < loop_ub; i37++) {
            b_jumping2_diff->data[i37] = jumping1_diff->data[i37];
          }

          b_jumping2_diff->data[jumping1_diff->size[0]] = fabs(dif);
          i37 = jumping1_diff->size[0];
          jumping1_diff->size[0] = b_jumping2_diff->size[0];
          emxEnsureCapacity_real_T(jumping1_diff, i37);
          loop_ub = b_jumping2_diff->size[0];
          for (i37 = 0; i37 < loop_ub; i37++) {
            jumping1_diff->data[i37] = b_jumping2_diff->data[i37];
          }

          /* --------- (B) invalid_candidate -------- */
          if (i38 > RD_size[0]) {
            i37 = 0;
            i39 = 0;
          } else {
            i37 = cycles_data[i];
            i39 = RD_size[0];
          }

          if (i38 > RD_size[0]) {
            i40 = 0;
            i41 = 0;
          } else {
            i40 = cycles_data[i];
            i41 = RD_size[0];
          }

          loop_ub_tmp = i39 - i37;
          for (i39 = 0; i39 < loop_ub_tmp; i39++) {
            varargin_1_data[i39] = RD_data[i37 + i39];
          }

          n = loop_ub_tmp - 1;
          if (loop_ub_tmp <= 2) {
            if (loop_ub_tmp == 1) {
              min_val = RD_data[i37];
            } else {
              min_val = RD_data[i37 + 1];
              if ((RD_data[i37] > min_val) || (rtIsNaN(RD_data[i37]) &&
                   (!rtIsNaN(min_val)))) {
              } else {
                min_val = RD_data[i37];
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
              min_val = RD_data[i37];
            } else {
              min_val = varargin_1_data[idx - 1];
              i37 = idx + 1;
              for (k = i37; k <= n + 1; k++) {
                d16 = varargin_1_data[k - 1];
                if (min_val > d16) {
                  min_val = d16;
                }
              }
            }
          }

          RD_diff2_size_idx_0 = i41 - i40;
          n = RD_diff2_size_idx_0 - 1;
          if (RD_diff2_size_idx_0 <= 2) {
            if (RD_diff2_size_idx_0 == 1) {
              ex = RD_data[i40];
            } else {
              ex = RD_data[i40 + 1];
              if ((RD_data[i40] < ex) || (rtIsNaN(RD_data[i40]) && (!rtIsNaN(ex))))
              {
              } else {
                ex = RD_data[i40];
              }
            }
          } else {
            if (!rtIsNaN(RD_data[i40])) {
              idx = 1;
            } else {
              idx = 0;
              k = 2;
              exitg1 = false;
              while ((!exitg1) && (k <= RD_diff2_size_idx_0)) {
                if (!rtIsNaN(RD_data[(i40 + k) - 1])) {
                  idx = k;
                  exitg1 = true;
                } else {
                  k++;
                }
              }
            }

            if (idx == 0) {
              ex = RD_data[i40];
            } else {
              ex = RD_data[(i40 + idx) - 1];
              i37 = idx + 1;
              for (k = i37; k <= n + 1; k++) {
                d16 = RD_data[(i40 + k) - 1];
                if (ex < d16) {
                  ex = d16;
                }
              }
            }
          }

          if (dif / (min_val - ex) > 0.2) {
            i37 = ivd_cdd->size[1];
            i39 = ivd_cdd->size[0] * ivd_cdd->size[1];
            ivd_cdd->size[1] = i37 + 1;
            emxEnsureCapacity_real_T(ivd_cdd, i39);
            ivd_cdd->data[i37] = (double)cycles_data[i] + 1.0;
          }

          /* --------- (E) invalid_candidate -------- */
          if (cycles_data[i] + 1 > RD_size[0]) {
            i37 = 1;
          } else {
            i37 = cycles_data[i] + 1;
          }

          if (i38 > RD_size[0]) {
            i38 = 1;
            i39 = 0;
          } else {
            i39 = RD_size[0];
          }

          loop_ub_tmp = (signed char)i39 - (signed char)i38;
          for (i39 = 0; i39 <= loop_ub_tmp; i39++) {
            e_tmp_data[i39] = (signed char)((signed char)((signed char)i38 +
              (signed char)i39) - 1);
          }

          loop_ub_tmp++;
          for (i38 = 0; i38 < loop_ub_tmp; i38++) {
            b_RD_data[i38] = RD_data[(i37 + i38) - 1] - dif;
          }

          for (i37 = 0; i37 < loop_ub_tmp; i37++) {
            RD_data[e_tmp_data[i37]] = b_RD_data[i37];
          }
        } else {
          i37 = jumping->size[0];
          i38 = jumping->size[0];
          jumping->size[0] = i37 + 1;
          emxEnsureCapacity_real_T(jumping, i38);
          jumping->data[i37] = 2.0;
          RD[0] = RD_data[(int)(jumping2_idx->data[jumping2_idx->size[0] - 1] -
                                1.0) - 1];
          RD[1] = RD_data[(int)(jumping2_idx->data[jumping2_idx->size[0] - 1] +
                                1.0) - 1];
          d16 = fabs(RD_data[(int)jumping2_idx->data[jumping2_idx->size[0] - 1]
                     - 1] - b_mean(RD));
          i37 = b_jumping2_diff->size[0];
          b_jumping2_diff->size[0] = jumping2_diff->size[0] + 1;
          emxEnsureCapacity_real_T(b_jumping2_diff, i37);
          loop_ub = jumping2_diff->size[0];
          for (i37 = 0; i37 < loop_ub; i37++) {
            b_jumping2_diff->data[i37] = jumping2_diff->data[i37];
          }

          b_jumping2_diff->data[jumping2_diff->size[0]] = d16;
          i37 = jumping2_diff->size[0];
          jumping2_diff->size[0] = b_jumping2_diff->size[0];
          emxEnsureCapacity_real_T(jumping2_diff, i37);
          loop_ub = b_jumping2_diff->size[0];
          for (i37 = 0; i37 < loop_ub; i37++) {
            jumping2_diff->data[i37] = b_jumping2_diff->data[i37];
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
      i37 = x->size[0];
      x->size[0] = jumping1_diff->size[0];
      emxEnsureCapacity_boolean_T(x, i37);
      loop_ub = jumping1_diff->size[0];
      for (i37 = 0; i37 < loop_ub; i37++) {
        x->data[i37] = (jumping1_diff->data[i37] / absxk < 3.0);
      }

      k = (1 <= x->size[0]);
      idx = 0;
      RD_diff2_size_idx_0 = 0;
      exitg1 = false;
      while ((!exitg1) && (RD_diff2_size_idx_0 <= x->size[0] - 1)) {
        if (x->data[RD_diff2_size_idx_0]) {
          idx++;
          if (idx >= k) {
            exitg1 = true;
          } else {
            RD_diff2_size_idx_0++;
          }
        } else {
          RD_diff2_size_idx_0++;
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
        i37 = (int)LC2;
        for (i = 0; i < i37; i++) {
          if (jumping->data[i] == 1.0) {
            i38 = (int)i_jump1 - 1;
            if (jumping1_diff->data[i38] / absxk > 3.0) {
              dif = RD_data[(int)(jumping1_idx->data[i38] + 1.0) - 1] - RD_data
                [(int)jumping1_idx->data[i38] - 1];

              /* --------- (B) invalid_candidate -------- */
              if (jumping1_idx->data[i38] + 1.0 > RD_size[0]) {
                i39 = 0;
                i40 = 0;
              } else {
                i39 = (int)(jumping1_idx->data[i38] + 1.0) - 1;
                i40 = RD_size[0];
              }

              if (jumping1_idx->data[i38] + 1.0 > RD_size[0]) {
                i41 = 0;
                loop_ub = 0;
              } else {
                i41 = (int)(jumping1_idx->data[i38] + 1.0) - 1;
                loop_ub = RD_size[0];
              }

              loop_ub_tmp = i40 - i39;
              for (i40 = 0; i40 < loop_ub_tmp; i40++) {
                varargin_1_data[i40] = RD_data[i39 + i40];
              }

              n = loop_ub_tmp - 1;
              if (loop_ub_tmp <= 2) {
                if (loop_ub_tmp == 1) {
                  min_val = RD_data[i39];
                } else {
                  min_val = RD_data[i39 + 1];
                  if ((RD_data[i39] > min_val) || (rtIsNaN(RD_data[i39]) &&
                       (!rtIsNaN(min_val)))) {
                  } else {
                    min_val = RD_data[i39];
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
                  min_val = RD_data[i39];
                } else {
                  min_val = varargin_1_data[idx - 1];
                  i39 = idx + 1;
                  for (k = i39; k <= n + 1; k++) {
                    d16 = varargin_1_data[k - 1];
                    if (min_val > d16) {
                      min_val = d16;
                    }
                  }
                }
              }

              RD_diff2_size_idx_0 = loop_ub - i41;
              n = RD_diff2_size_idx_0 - 1;
              if (RD_diff2_size_idx_0 <= 2) {
                if (RD_diff2_size_idx_0 == 1) {
                  ex = RD_data[i41];
                } else {
                  ex = RD_data[i41 + 1];
                  if ((RD_data[i41] < ex) || (rtIsNaN(RD_data[i41]) && (!rtIsNaN
                        (ex)))) {
                  } else {
                    ex = RD_data[i41];
                  }
                }
              } else {
                if (!rtIsNaN(RD_data[i41])) {
                  idx = 1;
                } else {
                  idx = 0;
                  k = 2;
                  exitg1 = false;
                  while ((!exitg1) && (k <= RD_diff2_size_idx_0)) {
                    if (!rtIsNaN(RD_data[(i41 + k) - 1])) {
                      idx = k;
                      exitg1 = true;
                    } else {
                      k++;
                    }
                  }
                }

                if (idx == 0) {
                  ex = RD_data[i41];
                } else {
                  ex = RD_data[(i41 + idx) - 1];
                  i39 = idx + 1;
                  for (k = i39; k <= n + 1; k++) {
                    d16 = RD_data[(i41 + k) - 1];
                    if (ex < d16) {
                      ex = d16;
                    }
                  }
                }
              }

              if (dif / (min_val - ex) > 0.2) {
                i39 = ivd_cdd->size[1];
                i40 = ivd_cdd->size[0] * ivd_cdd->size[1];
                ivd_cdd->size[1] = i39 + 1;
                emxEnsureCapacity_real_T(ivd_cdd, i40);
                ivd_cdd->data[i39] = jumping1_idx->data[i38] + 1.0;
              }

              /* --------- (E) invalid_candidate -------- */
              if (jumping1_idx->data[(int)i_jump1 - 1] + 1.0 > RD_size[0]) {
                i39 = 0;
              } else {
                i39 = (int)(jumping1_idx->data[(int)i_jump1 - 1] + 1.0) - 1;
              }

              if (jumping1_idx->data[i38] + 1.0 > RD_size[0]) {
                i38 = 1;
                i40 = 0;
              } else {
                i38 = (int)(jumping1_idx->data[i38] + 1.0);
                i40 = RD_size[0];
              }

              loop_ub_tmp = (signed char)i40 - (signed char)i38;
              for (i40 = 0; i40 <= loop_ub_tmp; i40++) {
                e_tmp_data[i40] = (signed char)((signed char)((signed char)i38 +
                  (signed char)i40) - 1);
              }

              loop_ub_tmp++;
              for (i38 = 0; i38 < loop_ub_tmp; i38++) {
                b_RD_data[i38] = RD_data[i39 + i38] - dif;
              }

              for (i38 = 0; i38 < loop_ub_tmp; i38++) {
                RD_data[e_tmp_data[i38]] = b_RD_data[i38];
              }
            } else if (fabs((RD_data[(int)jumping1_idx->data[i38] - 1] - 2.0 *
                             RD_data[(int)(jumping1_idx->data[i38] + 1.0) - 1])
                            + RD_data[(int)(jumping1_idx->data[i38] + 2.0) - 1])
                       > fabs((RD_data[(int)(jumping1_idx->data[i38] - 1.0) - 1]
                               - 2.0 * RD_data[(int)jumping1_idx->data[i38] - 1])
                              + RD_data[(int)(jumping1_idx->data[i38] + 1.0) - 1]))
            {
              b_RD[0] = RD_data[(int)jumping1_idx->data[i38] - 1];
              b_RD[1] = RD_data[(int)(jumping1_idx->data[i38] + 1.0) - 1];
              b_RD[2] = RD_data[(int)(jumping1_idx->data[i38] + 2.0) - 1];
              RD_data[(int)(jumping1_idx->data[i38] + 1.0) - 1] =
                Coder_Jump2orNot(b_RD);
            } else {
              b_RD[0] = RD_data[(int)(jumping1_idx->data[i38] - 1.0) - 1];
              b_RD[1] = RD_data[(int)jumping1_idx->data[i38] - 1];
              b_RD[2] = RD_data[(int)(jumping1_idx->data[i38] + 1.0) - 1];
              RD_data[(int)jumping1_idx->data[i38] - 1] = Coder_Jump2orNot(b_RD);
            }

            i_jump1++;
          } else {
            RD_diff2_size_idx_0 = (int)i_jump2 - 1;
            b_RD[0] = RD_data[(int)(jumping2_idx->data[RD_diff2_size_idx_0] -
              1.0) - 1];
            b_RD[1] = RD_data[(int)jumping2_idx->data[RD_diff2_size_idx_0] - 1];
            b_RD[2] = RD_data[(int)(jumping2_idx->data[RD_diff2_size_idx_0] +
              1.0) - 1];
            RD_data[(int)jumping2_idx->data[RD_diff2_size_idx_0] - 1] =
              Coder_Jump2orNot(b_RD);
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
  d16 = RD_data[RD_size[0] - 1];
  absxk = RD_data[RD_size[0] - 2];
  if (((RD_data[RD_size[0] - 3] - 2.0 * absxk) + d16 < -Criterion_bdry) && (d16 <
       absxk)) {
    (*num_jumping)++;
    RD_data[RD_size[0] - 1] = absxk;
  }

  RD_diff2_size_idx_0 = ivd_cdd->size[1];
  if (RD_diff2_size_idx_0 < L_ivd_cdd_output) {
    L_ivd_cdd_output = RD_diff2_size_idx_0;
  }

  /*  ivd_cdd_output=zeros(L_ivd_cdd_output,1); */
  if (1 > L_ivd_cdd_output) {
    loop_ub = 0;
  } else {
    loop_ub = L_ivd_cdd_output;
  }

  ivd_cdd_output_size[0] = 1;
  ivd_cdd_output_size[1] = loop_ub;
  for (i37 = 0; i37 < loop_ub; i37++) {
    ivd_cdd_output_data[i37] = ivd_cdd->data[i37];
  }

  emxFree_real_T(&ivd_cdd);
}

/* End of code generation (Coder_jumping_correction6.c) */
