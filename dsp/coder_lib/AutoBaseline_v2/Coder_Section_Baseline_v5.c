/*
 * Coder_Section_Baseline_v5.c
 *
 * Code generation for function 'Coder_Section_Baseline_v5'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_Section_Baseline_v5.h"
#include "AutoBaseline_v2_emxutil.h"
#include "power.h"
#include "Coder_linear_fitting.h"
#include "Coder_scd_fitting.h"
#include "Coder_baseline.h"
#include "diff.h"
#include "Coder_local_smoothing.h"
#include "Coder_min5.h"
#include "Coder_SegMaxDiff.h"

/* Function Definitions */
void Coder_Section_Baseline_v5(const double x_data[], const int x_size[1], const
  double RD_data[], const int RD_size[1], double SFC, double MFC, double *EFC,
  double TC, double DRFU, double LinearOrNot, double AR, double FB, double dfC,
  double *EFC0, double cff[2], double scd_fit_data[], int scd_fit_size[1])
{
  double SC;
  emxArray_real_T *y;
  int i47;
  double ndbl;
  double apnd;
  double cdiff;
  emxArray_real_T *xdata;
  double u0;
  double u1;
  int n;
  emxArray_real_T *RD;
  int b_x_size[1];
  int nm1d2;
  emxArray_real_T *b_tmp;
  double b_x_data[100];
  int k;
  emxArray_real_T c_x_data;
  double temp_fit_data[100];
  int idx;
  boolean_T exitg1;
  int i48;
  int i49;
  double b_SC;
  double varargin_1_data[199];
  int b_RD_size[1];
  double b_RD_data[100];
  double min5_idx[5];
  double varargin_1[3];
  int b_idx;
  emxArray_real_T *b_y;
  emxArray_real_T *c_y;
  double local_smoothed_RD[6];
  double dv0[5];
  boolean_T guard1 = false;
  signed char tmp_data[100];
  int y_size[1];
  emxArray_real_T y_data;
  double b_y_data[100];

  /*  이중 증폭 모양일때 앞부분에서 baseline 잡히도록 */
  if (*EFC < MFC) {
    SC = 1.0;
  } else {
    SC = SFC;
  }

  emxInit_real_T(&y, 2);
  if (rtIsNaN(SC) || rtIsNaN(*EFC)) {
    i47 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i47);
    y->data[0] = rtNaN;
  } else if (*EFC < SC) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else if ((rtIsInf(SC) || rtIsInf(*EFC)) && (SC == *EFC)) {
    i47 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i47);
    y->data[0] = rtNaN;
  } else if (floor(SC) == SC) {
    i47 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)floor(*EFC - SC) + 1;
    emxEnsureCapacity_real_T(y, i47);
    n = (int)floor(*EFC - SC);
    for (i47 = 0; i47 <= n; i47++) {
      y->data[i47] = SC + (double)i47;
    }
  } else {
    ndbl = floor((*EFC - SC) + 0.5);
    apnd = SC + ndbl;
    cdiff = apnd - *EFC;
    u0 = fabs(SC);
    u1 = fabs(*EFC);
    if ((u0 > u1) || rtIsNaN(u1)) {
      u1 = u0;
    }

    if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
      ndbl++;
      apnd = *EFC;
    } else if (cdiff > 0.0) {
      apnd = SC + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    if (ndbl >= 0.0) {
      n = (int)ndbl;
    } else {
      n = 0;
    }

    i47 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n;
    emxEnsureCapacity_real_T(y, i47);
    if (n > 0) {
      y->data[0] = SC;
      if (n > 1) {
        y->data[n - 1] = apnd;
        nm1d2 = (n - 1) / 2;
        for (k = 0; k <= nm1d2 - 2; k++) {
          y->data[1 + k] = SC + (1.0 + (double)k);
          y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
        }

        if (nm1d2 << 1 == n - 1) {
          y->data[nm1d2] = (SC + apnd) / 2.0;
        } else {
          y->data[nm1d2] = SC + (double)nm1d2;
          y->data[nm1d2 + 1] = apnd - (double)nm1d2;
        }
      }
    }
  }

  emxInit_real_T(&xdata, 1);
  i47 = xdata->size[0];
  xdata->size[0] = y->size[1];
  emxEnsureCapacity_real_T(xdata, i47);
  n = y->size[1];
  for (i47 = 0; i47 < n; i47++) {
    xdata->data[i47] = y->data[i47];
  }

  emxInit_real_T(&RD, 1);

  /* temp fitting coeff */
  i47 = RD->size[0];
  RD->size[0] = xdata->size[0];
  emxEnsureCapacity_real_T(RD, i47);
  n = xdata->size[0];
  for (i47 = 0; i47 < n; i47++) {
    RD->data[i47] = RD_data[(int)xdata->data[i47] - 1];
  }

  Coder_scd_fitting(xdata, RD, &cff[0], &cff[1]);
  b_x_size[0] = x_size[0];
  n = x_size[0];
  for (i47 = 0; i47 < n; i47++) {
    b_x_data[i47] = x_data[i47] - 50.0;
  }

  emxInit_real_T(&b_tmp, 1);
  c_x_data.data = &b_x_data[0];
  c_x_data.size = &b_x_size[0];
  c_x_data.allocatedSize = 100;
  c_x_data.numDimensions = 1;
  c_x_data.canFreeData = false;
  power(&c_x_data, b_tmp);
  n = b_tmp->size[0];
  for (i47 = 0; i47 < n; i47++) {
    temp_fit_data[i47] = cff[0] * b_tmp->data[i47] + cff[1];
  }

  n = RD_size[0];
  if (RD_size[0] <= 2) {
    if (RD_size[0] == 1) {
      u0 = RD_data[0];
    } else if ((RD_data[0] < RD_data[1]) || (rtIsNaN(RD_data[0]) && (!rtIsNaN
                 (RD_data[1])))) {
      u0 = RD_data[1];
    } else {
      u0 = RD_data[0];
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
      u0 = RD_data[0];
    } else {
      u0 = RD_data[idx - 1];
      i47 = idx + 1;
      for (k = i47; k <= n; k++) {
        u1 = RD_data[k - 1];
        if (u0 < u1) {
          u0 = u1;
        }
      }
    }
  }

  n = RD_size[0];
  if (RD_size[0] <= 2) {
    if (RD_size[0] == 1) {
      cdiff = RD_data[0];
    } else if ((RD_data[0] > RD_data[1]) || (rtIsNaN(RD_data[0]) && (!rtIsNaN
                 (RD_data[1])))) {
      cdiff = RD_data[1];
    } else {
      cdiff = RD_data[0];
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
      cdiff = RD_data[0];
    } else {
      cdiff = RD_data[idx - 1];
      i47 = idx + 1;
      for (k = i47; k <= n; k++) {
        u1 = RD_data[k - 1];
        if (cdiff > u1) {
          cdiff = u1;
        }
      }
    }
  }

  if (cff[0] >= 0.0) {
    if (SC > TC) {
      i47 = 0;
      i48 = 0;
      i49 = 0;
    } else {
      i47 = (int)SC - 1;
      i48 = (int)TC;
      i49 = (int)SC - 1;
    }

    nm1d2 = i48 - i47;
    for (i48 = 0; i48 < nm1d2; i48++) {
      varargin_1_data[i48] = RD_data[i47 + i48] - temp_fit_data[i49 + i48];
    }

    if (nm1d2 <= 2) {
      if (nm1d2 == 1) {
        ndbl = varargin_1_data[0];
      } else if ((varargin_1_data[0] > varargin_1_data[1]) || (rtIsNaN
                  (varargin_1_data[0]) && (!rtIsNaN(varargin_1_data[1])))) {
        ndbl = varargin_1_data[1];
      } else {
        ndbl = varargin_1_data[0];
      }
    } else {
      if (!rtIsNaN(varargin_1_data[0])) {
        idx = 1;
      } else {
        idx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= nm1d2)) {
          if (!rtIsNaN(varargin_1_data[k - 1])) {
            idx = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (idx == 0) {
        ndbl = varargin_1_data[0];
      } else {
        ndbl = varargin_1_data[idx - 1];
        i47 = idx + 1;
        for (k = i47; k <= nm1d2; k++) {
          u1 = varargin_1_data[k - 1];
          if (ndbl > u1) {
            ndbl = u1;
          }
        }
      }
    }

    if (ndbl / (u0 - cdiff) > -0.15) {
      if (FB == 0.0) {
        Coder_SegMaxDiff(RD_data, SC, TC, &ndbl, &apnd);
        b_RD_size[0] = RD_size[0];
        if (0 <= RD_size[0] - 1) {
          memcpy(&b_RD_data[0], &RD_data[0], (unsigned int)(RD_size[0] * (int)
                  sizeof(double)));
        }

        Coder_min5(b_RD_data, b_RD_size, min5_idx);
        if (!rtIsNaN(min5_idx[0])) {
          idx = 1;
        } else {
          idx = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k < 6)) {
            if (!rtIsNaN(min5_idx[k - 1])) {
              idx = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (idx == 0) {
          u0 = min5_idx[0];
        } else {
          u0 = min5_idx[idx - 1];
          i47 = idx + 1;
          for (k = i47; k < 6; k++) {
            u1 = min5_idx[k - 1];
            if (u0 < u1) {
              u0 = u1;
            }
          }
        }

        varargin_1[0] = *EFC;
        varargin_1[1] = u0 - 2.0;
        varargin_1[2] = apnd - 2.0;
        if (!rtIsNaN(varargin_1[0])) {
          idx = 1;
        } else {
          idx = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k < 4)) {
            if (!rtIsNaN(varargin_1[k - 1])) {
              idx = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (idx == 0) {
          *EFC = varargin_1[0];
        } else {
          u0 = varargin_1[idx - 1];
          i47 = idx + 1;
          for (k = i47; k < 4; k++) {
            u1 = varargin_1[k - 1];
            if (u0 < u1) {
              u0 = u1;
            }
          }

          *EFC = u0;
        }
      } else {
        if (MFC > TC) {
          i47 = 0;
          i48 = 0;
        } else {
          i47 = (int)MFC - 1;
          i48 = (int)TC;
        }

        i49 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = ((int)(MFC - 1.0) + i48) - i47;
        emxEnsureCapacity_real_T(y, i49);
        n = (int)(MFC - 1.0);
        for (i49 = 0; i49 < n; i49++) {
          y->data[i49] = rtMinusInf;
        }

        n = i48 - i47;
        for (i48 = 0; i48 < n; i48++) {
          y->data[i48 + (int)(MFC - 1.0)] = RD_data[i47 + i48];
        }

        n = y->size[1];
        if (y->size[1] <= 2) {
          if (y->size[1] == 1) {
            idx = 1;
          } else if ((y->data[0] < y->data[1]) || (rtIsNaN(y->data[0]) &&
                      (!rtIsNaN(y->data[1])))) {
            idx = 2;
          } else {
            idx = 1;
          }
        } else {
          if (!rtIsNaN(y->data[0])) {
            idx = 1;
          } else {
            idx = 0;
            k = 2;
            exitg1 = false;
            while ((!exitg1) && (k <= y->size[1])) {
              if (!rtIsNaN(y->data[k - 1])) {
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
            u0 = y->data[idx - 1];
            i47 = idx + 1;
            for (k = i47; k <= n; k++) {
              if (u0 < y->data[k - 1]) {
                u0 = y->data[k - 1];
                idx = k;
              }
            }
          }
        }

        u0 = SC + 1.0;
        u1 = idx;
        if (u0 > u1) {
          u1 = u0;
        }

        Coder_SegMaxDiff(RD_data, SC, u1, &ndbl, &apnd);
        ndbl = *EFC;
        if ((ndbl < apnd - 2.0) || (rtIsNaN(ndbl) && (!rtIsNaN(apnd - 2.0)))) {
          *EFC = apnd - 2.0;
        }
      }

      if (rtIsNaN(*EFC)) {
        i47 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i47);
        y->data[0] = rtNaN;
      } else if (*EFC < SC) {
        y->size[0] = 1;
        y->size[1] = 0;
      } else if ((rtIsInf(SC) || rtIsInf(*EFC)) && (SC == *EFC)) {
        i47 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i47);
        y->data[0] = rtNaN;
      } else if (floor(SC) == SC) {
        i47 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = (int)floor(*EFC - SC) + 1;
        emxEnsureCapacity_real_T(y, i47);
        n = (int)floor(*EFC - SC);
        for (i47 = 0; i47 <= n; i47++) {
          y->data[i47] = SC + (double)i47;
        }
      } else {
        ndbl = floor((*EFC - SC) + 0.5);
        apnd = SC + ndbl;
        cdiff = apnd - *EFC;
        u0 = fabs(SC);
        u1 = fabs(*EFC);
        if ((u0 > u1) || rtIsNaN(u1)) {
          u1 = u0;
        }

        if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
          ndbl++;
          apnd = *EFC;
        } else if (cdiff > 0.0) {
          apnd = SC + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          n = (int)ndbl;
        } else {
          n = 0;
        }

        i47 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = n;
        emxEnsureCapacity_real_T(y, i47);
        if (n > 0) {
          y->data[0] = SC;
          if (n > 1) {
            y->data[n - 1] = apnd;
            nm1d2 = (n - 1) / 2;
            for (k = 0; k <= nm1d2 - 2; k++) {
              y->data[1 + k] = SC + (1.0 + (double)k);
              y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
            }

            if (nm1d2 << 1 == n - 1) {
              y->data[nm1d2] = (SC + apnd) / 2.0;
            } else {
              y->data[nm1d2] = SC + (double)nm1d2;
              y->data[nm1d2 + 1] = apnd - (double)nm1d2;
            }
          }
        }
      }

      i47 = xdata->size[0];
      xdata->size[0] = y->size[1];
      emxEnsureCapacity_real_T(xdata, i47);
      n = y->size[1];
      for (i47 = 0; i47 < n; i47++) {
        xdata->data[i47] = y->data[i47];
      }

      i47 = RD->size[0];
      RD->size[0] = xdata->size[0];
      emxEnsureCapacity_real_T(RD, i47);
      n = xdata->size[0];
      for (i47 = 0; i47 < n; i47++) {
        RD->data[i47] = RD_data[(int)xdata->data[i47] - 1];
      }

      Coder_scd_fitting(xdata, RD, &cff[0], &cff[1]);
    }
  } else {
    if (FB == 0.0) {
      u1 = TC;
    } else {
      if (MFC > TC) {
        i47 = 0;
        i48 = 0;
      } else {
        i47 = (int)MFC - 1;
        i48 = (int)TC;
      }

      i49 = y->size[0] * y->size[1];
      y->size[0] = 1;
      n = (int)(MFC - 1.0);
      y->size[1] = (n + i48) - i47;
      emxEnsureCapacity_real_T(y, i49);
      for (i49 = 0; i49 < n; i49++) {
        y->data[i49] = rtMinusInf;
      }

      nm1d2 = i48 - i47;
      for (i48 = 0; i48 < nm1d2; i48++) {
        y->data[i48 + n] = RD_data[i47 + i48];
      }

      n = y->size[1];
      if (y->size[1] <= 2) {
        if (y->size[1] == 1) {
          idx = 1;
        } else if ((y->data[0] < y->data[1]) || (rtIsNaN(y->data[0]) &&
                    (!rtIsNaN(y->data[1])))) {
          idx = 2;
        } else {
          idx = 1;
        }
      } else {
        if (!rtIsNaN(y->data[0])) {
          idx = 1;
        } else {
          idx = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= y->size[1])) {
            if (!rtIsNaN(y->data[k - 1])) {
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
          u0 = y->data[idx - 1];
          i47 = idx + 1;
          for (k = i47; k <= n; k++) {
            if (u0 < y->data[k - 1]) {
              u0 = y->data[k - 1];
              idx = k;
            }
          }
        }
      }

      u1 = idx;
    }

    if ((SC + 1.0 > u1) || rtIsNaN(u1)) {
      b_SC = SC + 1.0;
    } else {
      b_SC = u1;
    }

    Coder_SegMaxDiff(RD_data, SC, b_SC, &ndbl, &apnd);
    if (RD_data[(int)apnd - 1] > RD_data[(int)SC - 1]) {
      if ((!(*EFC > apnd - 2.0)) && (!rtIsNaN(apnd - 2.0))) {
        *EFC = apnd - 2.0;
      }

      if (rtIsNaN(*EFC)) {
        i47 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i47);
        y->data[0] = rtNaN;
      } else if (*EFC < SC) {
        y->size[0] = 1;
        y->size[1] = 0;
      } else if (rtIsInf(*EFC) && (SC == *EFC)) {
        i47 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i47);
        y->data[0] = rtNaN;
      } else if (SC == SC) {
        i47 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = (int)floor(*EFC - SC) + 1;
        emxEnsureCapacity_real_T(y, i47);
        n = (int)floor(*EFC - SC);
        for (i47 = 0; i47 <= n; i47++) {
          y->data[i47] = SC + (double)i47;
        }
      } else {
        ndbl = floor((*EFC - SC) + 0.5);
        apnd = SC + ndbl;
        cdiff = apnd - *EFC;
        u0 = (int)SC;
        u1 = fabs(*EFC);
        if ((u0 > u1) || rtIsNaN(u1)) {
          u1 = u0;
        }

        if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
          ndbl++;
          apnd = *EFC;
        } else if (cdiff > 0.0) {
          apnd = SC + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          n = (int)ndbl;
        } else {
          n = 0;
        }

        i47 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = n;
        emxEnsureCapacity_real_T(y, i47);
        if (n > 0) {
          y->data[0] = SC;
          if (n > 1) {
            y->data[n - 1] = apnd;
            nm1d2 = (n - 1) / 2;
            for (k = 0; k <= nm1d2 - 2; k++) {
              y->data[1 + k] = SC + (1.0 + (double)k);
              y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
            }

            if (nm1d2 << 1 == n - 1) {
              y->data[nm1d2] = (SC + apnd) / 2.0;
            } else {
              y->data[nm1d2] = SC + (double)nm1d2;
              y->data[nm1d2 + 1] = apnd - (double)nm1d2;
            }
          }
        }
      }

      i47 = xdata->size[0];
      xdata->size[0] = y->size[1];
      emxEnsureCapacity_real_T(xdata, i47);
      n = y->size[1];
      for (i47 = 0; i47 < n; i47++) {
        xdata->data[i47] = y->data[i47];
      }

      if (LinearOrNot == 1.0) {
        i47 = RD->size[0];
        RD->size[0] = xdata->size[0];
        emxEnsureCapacity_real_T(RD, i47);
        n = xdata->size[0];
        for (i47 = 0; i47 < n; i47++) {
          RD->data[i47] = RD_data[(int)xdata->data[i47] - 1];
        }

        Coder_linear_fitting(xdata, RD, &cff[0], &cff[1]);
        LinearOrNot = 2.0;
      } else {
        i47 = RD->size[0];
        RD->size[0] = xdata->size[0];
        emxEnsureCapacity_real_T(RD, i47);
        n = xdata->size[0];
        for (i47 = 0; i47 < n; i47++) {
          RD->data[i47] = RD_data[(int)xdata->data[i47] - 1];
        }

        Coder_scd_fitting(xdata, RD, &cff[0], &cff[1]);
      }
    } else {
      if (LinearOrNot == 1.0) {
        i47 = RD->size[0];
        RD->size[0] = xdata->size[0];
        emxEnsureCapacity_real_T(RD, i47);
        n = xdata->size[0];
        for (i47 = 0; i47 < n; i47++) {
          RD->data[i47] = RD_data[(int)xdata->data[i47] - 1];
        }

        Coder_linear_fitting(xdata, RD, &cff[0], &cff[1]);
        LinearOrNot = 2.0;
      }
    }
  }

  *EFC0 = *EFC;

  /* -------- 꺾이는 놈 baseline 잡기 -------- */
  if (LinearOrNot == 2.0) {
    i47 = xdata->size[0];
    xdata->size[0] = x_size[0];
    emxEnsureCapacity_real_T(xdata, i47);
    n = x_size[0];
    for (i47 = 0; i47 < n; i47++) {
      xdata->data[i47] = cff[0] * x_data[i47];
    }

    nm1d2 = RD_size[0];
    n = RD_size[0];
    for (i47 = 0; i47 < n; i47++) {
      temp_fit_data[i47] = RD_data[i47] - (xdata->data[i47] + cff[1]);
    }

    scd_fit_size[0] = xdata->size[0];
    n = xdata->size[0];
    for (i47 = 0; i47 < n; i47++) {
      scd_fit_data[i47] = xdata->data[i47] + cff[1];
    }
  } else {
    nm1d2 = RD_size[0];
    n = RD_size[0];
    for (i47 = 0; i47 < n; i47++) {
      temp_fit_data[i47] = RD_data[i47] - (cff[0] * b_tmp->data[i47] + cff[1]);
    }

    scd_fit_size[0] = b_tmp->size[0];
    n = b_tmp->size[0];
    for (i47 = 0; i47 < n; i47++) {
      scd_fit_data[i47] = cff[0] * b_tmp->data[i47] + cff[1];
    }
  }

  if (nm1d2 <= 2) {
    if (nm1d2 == 1) {
      u0 = temp_fit_data[0];
      idx = 1;
    } else if ((temp_fit_data[0] > temp_fit_data[1]) || (rtIsNaN(temp_fit_data[0])
                && (!rtIsNaN(temp_fit_data[1])))) {
      u0 = temp_fit_data[1];
      idx = 2;
    } else {
      u0 = temp_fit_data[0];
      idx = 1;
    }
  } else {
    if (!rtIsNaN(temp_fit_data[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= nm1d2)) {
        if (!rtIsNaN(temp_fit_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      u0 = temp_fit_data[0];
      idx = 1;
    } else {
      u0 = temp_fit_data[idx - 1];
      i47 = idx + 1;
      for (k = i47; k <= nm1d2; k++) {
        u1 = temp_fit_data[k - 1];
        if (u0 > u1) {
          u0 = u1;
          idx = k;
        }
      }
    }
  }

  if (SFC + 1.0 > *EFC) {
    i47 = 0;
    i48 = 0;
  } else {
    i47 = (int)(SFC + 1.0) - 1;
    i48 = (int)*EFC;
  }

  if (rtIsNaN(SFC)) {
    i49 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i49);
    y->data[0] = rtNaN;
  } else if (SFC < 1.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else if (rtIsInf(SFC) && (1.0 == SFC)) {
    i49 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i49);
    y->data[0] = rtNaN;
  } else {
    i49 = y->size[0] * y->size[1];
    y->size[0] = 1;
    n = (int)floor(SFC - 1.0);
    y->size[1] = n + 1;
    emxEnsureCapacity_real_T(y, i49);
    for (i49 = 0; i49 <= n; i49++) {
      y->data[i49] = 1.0 + (double)i49;
    }
  }

  i49 = xdata->size[0];
  xdata->size[0] = (y->size[1] + i48) - i47;
  emxEnsureCapacity_real_T(xdata, i49);
  n = y->size[1];
  for (i49 = 0; i49 < n; i49++) {
    xdata->data[i49] = rtMinusInf * y->data[i49];
  }

  n = i48 - i47;
  for (i48 = 0; i48 < n; i48++) {
    xdata->data[i48 + y->size[1]] = temp_fit_data[i47 + i48];
  }

  n = xdata->size[0];
  if (xdata->size[0] <= 2) {
    if (xdata->size[0] == 1) {
      cdiff = xdata->data[0];
      b_idx = 1;
    } else if ((xdata->data[0] < xdata->data[1]) || (rtIsNaN(xdata->data[0]) &&
                (!rtIsNaN(xdata->data[1])))) {
      cdiff = xdata->data[1];
      b_idx = 2;
    } else {
      cdiff = xdata->data[0];
      b_idx = 1;
    }
  } else {
    if (!rtIsNaN(xdata->data[0])) {
      b_idx = 1;
    } else {
      b_idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= xdata->size[0])) {
        if (!rtIsNaN(xdata->data[k - 1])) {
          b_idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (b_idx == 0) {
      cdiff = xdata->data[0];
      b_idx = 1;
    } else {
      cdiff = xdata->data[b_idx - 1];
      i47 = b_idx + 1;
      for (k = i47; k <= n; k++) {
        if (cdiff < xdata->data[k - 1]) {
          cdiff = xdata->data[k - 1];
          b_idx = k;
        }
      }
    }
  }

  emxInit_real_T(&b_y, 2);
  emxInit_real_T(&c_y, 2);
  if ((temp_fit_data[0] > 0.0) && (u0 / (temp_fit_data[(int)TC - 1] -
        temp_fit_data[(int)*EFC - 1]) < -0.1)) {
    if (((double)idx - 2.0 > SFC) && ((double)idx + 3.0 < TC)) {
      Coder_local_smoothing(*(double (*)[6])&RD_data[-3 + idx],
                            local_smoothed_RD);
    } else {
      for (nm1d2 = 0; nm1d2 < 6; nm1d2++) {
        local_smoothed_RD[nm1d2] = 0.0;
      }
    }

    b_diff(local_smoothed_RD, dv0);
    for (i47 = 0; i47 < 5; i47++) {
      min5_idx[i47] = dv0[i47];
    }

    if (!rtIsNaN(min5_idx[0])) {
      nm1d2 = 1;
    } else {
      nm1d2 = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k < 6)) {
        if (!rtIsNaN(min5_idx[k - 1])) {
          nm1d2 = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (nm1d2 == 0) {
      ndbl = min5_idx[0];
    } else {
      ndbl = min5_idx[nm1d2 - 1];
      i47 = nm1d2 + 1;
      for (k = i47; k < 6; k++) {
        u1 = min5_idx[k - 1];
        if (ndbl < u1) {
          ndbl = u1;
        }
      }
    }

    if (ndbl > dfC * 2.0) {
      u1 = (double)idx - 2.0;
      if (MFC > u1) {
        u1 = MFC;
      }

      *EFC = u1;
      if (rtIsNaN(*EFC)) {
        i47 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i47);
        y->data[0] = rtNaN;
      } else if (*EFC < SC) {
        y->size[0] = 1;
        y->size[1] = 0;
      } else if ((rtIsInf(SC) || rtIsInf(*EFC)) && (SC == *EFC)) {
        i47 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i47);
        y->data[0] = rtNaN;
      } else if (floor(SC) == SC) {
        i47 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = (int)floor(*EFC - SC) + 1;
        emxEnsureCapacity_real_T(y, i47);
        n = (int)floor(*EFC - SC);
        for (i47 = 0; i47 <= n; i47++) {
          y->data[i47] = SC + (double)i47;
        }
      } else {
        ndbl = floor((*EFC - SC) + 0.5);
        apnd = SC + ndbl;
        cdiff = apnd - *EFC;
        u0 = fabs(SC);
        u1 = fabs(*EFC);
        if ((u0 > u1) || rtIsNaN(u1)) {
          u1 = u0;
        }

        if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
          ndbl++;
          apnd = *EFC;
        } else if (cdiff > 0.0) {
          apnd = SC + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          n = (int)ndbl;
        } else {
          n = 0;
        }

        i47 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = n;
        emxEnsureCapacity_real_T(y, i47);
        if (n > 0) {
          y->data[0] = SC;
          if (n > 1) {
            y->data[n - 1] = apnd;
            nm1d2 = (n - 1) / 2;
            for (k = 0; k <= nm1d2 - 2; k++) {
              y->data[1 + k] = SC + (1.0 + (double)k);
              y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
            }

            if (nm1d2 << 1 == n - 1) {
              y->data[nm1d2] = (SC + apnd) / 2.0;
            } else {
              y->data[nm1d2] = SC + (double)nm1d2;
              y->data[nm1d2 + 1] = apnd - (double)nm1d2;
            }
          }
        }
      }

      i47 = xdata->size[0];
      xdata->size[0] = y->size[1];
      emxEnsureCapacity_real_T(xdata, i47);
      n = y->size[1];
      for (i47 = 0; i47 < n; i47++) {
        xdata->data[i47] = y->data[i47];
      }

      if (LinearOrNot == 1.0) {
        i47 = RD->size[0];
        RD->size[0] = xdata->size[0];
        emxEnsureCapacity_real_T(RD, i47);
        n = xdata->size[0];
        for (i47 = 0; i47 < n; i47++) {
          RD->data[i47] = RD_data[(int)xdata->data[i47] - 1];
        }

        Coder_linear_fitting(xdata, RD, &cff[0], &cff[1]);
        scd_fit_size[0] = x_size[0];
        n = x_size[0];
        for (i47 = 0; i47 < n; i47++) {
          scd_fit_data[i47] = cff[0] * x_data[i47] + cff[1];
        }
      } else {
        i47 = RD->size[0];
        RD->size[0] = xdata->size[0];
        emxEnsureCapacity_real_T(RD, i47);
        n = xdata->size[0];
        for (i47 = 0; i47 < n; i47++) {
          RD->data[i47] = RD_data[(int)xdata->data[i47] - 1];
        }

        Coder_scd_fitting(xdata, RD, &cff[0], &cff[1]);
        scd_fit_size[0] = b_tmp->size[0];
        n = b_tmp->size[0];
        for (i47 = 0; i47 < n; i47++) {
          scd_fit_data[i47] = cff[0] * b_tmp->data[i47] + cff[1];
        }
      }
    } else {
      u1 = *EFC - (double)idx;
      guard1 = false;
      if (u1 >= 8.0) {
        ndbl = (double)idx - SFC;
        if (ndbl >= 1.0) {
          if (rtIsNaN(*EFC)) {
            i47 = y->size[0] * y->size[1];
            y->size[0] = 1;
            y->size[1] = 1;
            emxEnsureCapacity_real_T(y, i47);
            y->data[0] = rtNaN;
          } else if (*EFC < idx) {
            y->size[0] = 1;
            y->size[1] = 0;
          } else if (rtIsInf(*EFC) && (idx == *EFC)) {
            i47 = y->size[0] * y->size[1];
            y->size[0] = 1;
            y->size[1] = 1;
            emxEnsureCapacity_real_T(y, i47);
            y->data[0] = rtNaN;
          } else {
            i47 = y->size[0] * y->size[1];
            y->size[0] = 1;
            n = (int)floor(u1);
            y->size[1] = n + 1;
            emxEnsureCapacity_real_T(y, i47);
            for (i47 = 0; i47 <= n; i47++) {
              y->data[i47] = (double)idx + (double)i47;
            }
          }

          if (rtIsNaN(*EFC)) {
            i47 = b_y->size[0] * b_y->size[1];
            b_y->size[0] = 1;
            b_y->size[1] = 1;
            emxEnsureCapacity_real_T(b_y, i47);
            b_y->data[0] = rtNaN;
          } else if (*EFC < idx) {
            b_y->size[0] = 1;
            b_y->size[1] = 0;
          } else if (rtIsInf(*EFC) && (idx == *EFC)) {
            i47 = b_y->size[0] * b_y->size[1];
            b_y->size[0] = 1;
            b_y->size[1] = 1;
            emxEnsureCapacity_real_T(b_y, i47);
            b_y->data[0] = rtNaN;
          } else {
            i47 = b_y->size[0] * b_y->size[1];
            b_y->size[0] = 1;
            b_y->size[1] = (int)floor(*EFC - (double)idx) + 1;
            emxEnsureCapacity_real_T(b_y, i47);
            n = (int)floor(*EFC - (double)idx);
            for (i47 = 0; i47 <= n; i47++) {
              b_y->data[i47] = (double)idx + (double)i47;
            }
          }

          if (rtIsNaN(SFC)) {
            i47 = c_y->size[0] * c_y->size[1];
            c_y->size[0] = 1;
            c_y->size[1] = 1;
            emxEnsureCapacity_real_T(c_y, i47);
            c_y->data[0] = rtNaN;
          } else if (idx < SFC) {
            c_y->size[0] = 1;
            c_y->size[1] = 0;
          } else if (rtIsInf(SFC) && (SFC == idx)) {
            i47 = c_y->size[0] * c_y->size[1];
            c_y->size[0] = 1;
            c_y->size[1] = 1;
            emxEnsureCapacity_real_T(c_y, i47);
            c_y->data[0] = rtNaN;
          } else if (floor(SFC) == SFC) {
            i47 = c_y->size[0] * c_y->size[1];
            c_y->size[0] = 1;
            n = (int)floor(ndbl);
            c_y->size[1] = n + 1;
            emxEnsureCapacity_real_T(c_y, i47);
            for (i47 = 0; i47 <= n; i47++) {
              c_y->data[i47] = SFC + (double)i47;
            }
          } else {
            ndbl = floor(ndbl + 0.5);
            apnd = SFC + ndbl;
            cdiff = apnd - (double)idx;
            u0 = fabs(SFC);
            u1 = idx;
            if (u0 > u1) {
              u1 = u0;
            }

            if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
              ndbl++;
              apnd = idx;
            } else if (cdiff > 0.0) {
              apnd = SFC + (ndbl - 1.0);
            } else {
              ndbl++;
            }

            n = (int)ndbl;
            i47 = c_y->size[0] * c_y->size[1];
            c_y->size[0] = 1;
            c_y->size[1] = n;
            emxEnsureCapacity_real_T(c_y, i47);
            if (n > 0) {
              c_y->data[0] = SFC;
              if (n > 1) {
                c_y->data[n - 1] = apnd;
                nm1d2 = (n - 1) / 2;
                for (k = 0; k <= nm1d2 - 2; k++) {
                  c_y->data[1 + k] = SFC + (1.0 + (double)k);
                  c_y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
                }

                if (nm1d2 << 1 == n - 1) {
                  c_y->data[nm1d2] = (SFC + apnd) / 2.0;
                } else {
                  c_y->data[nm1d2] = SFC + (double)nm1d2;
                  c_y->data[nm1d2 + 1] = apnd - (double)nm1d2;
                }
              }
            }
          }

          i47 = xdata->size[0];
          xdata->size[0] = y->size[1];
          emxEnsureCapacity_real_T(xdata, i47);
          n = y->size[1];
          for (i47 = 0; i47 < n; i47++) {
            xdata->data[i47] = y->data[i47];
          }

          i47 = b_tmp->size[0];
          b_tmp->size[0] = xdata->size[0];
          emxEnsureCapacity_real_T(b_tmp, i47);
          n = xdata->size[0];
          for (i47 = 0; i47 < n; i47++) {
            b_tmp->data[i47] = b_y->data[i47];
          }

          i47 = RD->size[0];
          RD->size[0] = c_y->size[1];
          emxEnsureCapacity_real_T(RD, i47);
          n = c_y->size[1];
          for (i47 = 0; i47 < n; i47++) {
            RD->data[i47] = c_y->data[i47];
          }

          Coder_baseline(b_tmp, RD, RD_data, idx, LinearOrNot, TC, scd_fit_data,
                         scd_fit_size, cff);
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        if (SFC + 1.0 > b_idx) {
          i47 = 0;
          i48 = 0;
        } else {
          i47 = (int)(SFC + 1.0) - 1;
          i48 = b_idx;
        }

        if (rtIsNaN(SFC)) {
          i49 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = 1;
          emxEnsureCapacity_real_T(y, i49);
          y->data[0] = rtNaN;
        } else if (SFC < 1.0) {
          y->size[0] = 1;
          y->size[1] = 0;
        } else if (rtIsInf(SFC) && (1.0 == SFC)) {
          i49 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = 1;
          emxEnsureCapacity_real_T(y, i49);
          y->data[0] = rtNaN;
        } else {
          i49 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = (int)floor(SFC - 1.0) + 1;
          emxEnsureCapacity_real_T(y, i49);
          n = (int)floor(SFC - 1.0);
          for (i49 = 0; i49 <= n; i49++) {
            y->data[i49] = 1.0 + (double)i49;
          }
        }

        i49 = xdata->size[0];
        xdata->size[0] = (y->size[1] + i48) - i47;
        emxEnsureCapacity_real_T(xdata, i49);
        n = y->size[1];
        for (i49 = 0; i49 < n; i49++) {
          xdata->data[i49] = rtInf * y->data[i49];
        }

        n = i48 - i47;
        for (i48 = 0; i48 < n; i48++) {
          xdata->data[i48 + y->size[1]] = temp_fit_data[i47 + i48];
        }

        n = xdata->size[0];
        if (xdata->size[0] <= 2) {
          if (xdata->size[0] == 1) {
            idx = 1;
          } else if ((xdata->data[0] > xdata->data[1]) || (rtIsNaN(xdata->data[0])
                      && (!rtIsNaN(xdata->data[1])))) {
            idx = 2;
          } else {
            idx = 1;
          }
        } else {
          if (!rtIsNaN(xdata->data[0])) {
            idx = 1;
          } else {
            idx = 0;
            k = 2;
            exitg1 = false;
            while ((!exitg1) && (k <= xdata->size[0])) {
              if (!rtIsNaN(xdata->data[k - 1])) {
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
            u0 = xdata->data[idx - 1];
            i47 = idx + 1;
            for (k = i47; k <= n; k++) {
              if (u0 > xdata->data[k - 1]) {
                u0 = xdata->data[k - 1];
                idx = k;
              }
            }
          }
        }

        if ((double)b_idx - (double)idx >= 8.0) {
          u1 = (double)idx - SFC;
          if (u1 >= 1.0) {
            *EFC = b_idx;
            if (b_idx < idx) {
              y->size[0] = 1;
              y->size[1] = 0;
            } else {
              i47 = y->size[0] * y->size[1];
              y->size[0] = 1;
              n = b_idx - idx;
              y->size[1] = n + 1;
              emxEnsureCapacity_real_T(y, i47);
              for (i47 = 0; i47 <= n; i47++) {
                y->data[i47] = idx + i47;
              }
            }

            if (rtIsNaN(SFC)) {
              i47 = b_y->size[0] * b_y->size[1];
              b_y->size[0] = 1;
              b_y->size[1] = 1;
              emxEnsureCapacity_real_T(b_y, i47);
              b_y->data[0] = rtNaN;
            } else if (idx < SFC) {
              b_y->size[0] = 1;
              b_y->size[1] = 0;
            } else if (rtIsInf(SFC) && (SFC == idx)) {
              i47 = b_y->size[0] * b_y->size[1];
              b_y->size[0] = 1;
              b_y->size[1] = 1;
              emxEnsureCapacity_real_T(b_y, i47);
              b_y->data[0] = rtNaN;
            } else if (floor(SFC) == SFC) {
              i47 = b_y->size[0] * b_y->size[1];
              b_y->size[0] = 1;
              n = (int)floor(u1);
              b_y->size[1] = n + 1;
              emxEnsureCapacity_real_T(b_y, i47);
              for (i47 = 0; i47 <= n; i47++) {
                b_y->data[i47] = SFC + (double)i47;
              }
            } else {
              ndbl = floor(u1 + 0.5);
              apnd = SFC + ndbl;
              cdiff = apnd - (double)idx;
              u0 = fabs(SFC);
              u1 = (unsigned int)fabs((double)idx);
              if (u0 > u1) {
                u1 = u0;
              }

              if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
                ndbl++;
                apnd = idx;
              } else if (cdiff > 0.0) {
                apnd = SFC + (ndbl - 1.0);
              } else {
                ndbl++;
              }

              n = (int)ndbl;
              i47 = b_y->size[0] * b_y->size[1];
              b_y->size[0] = 1;
              b_y->size[1] = n;
              emxEnsureCapacity_real_T(b_y, i47);
              if (n > 0) {
                b_y->data[0] = SFC;
                if (n > 1) {
                  b_y->data[n - 1] = apnd;
                  nm1d2 = (n - 1) / 2;
                  for (k = 0; k <= nm1d2 - 2; k++) {
                    b_y->data[1 + k] = SFC + (1.0 + (double)k);
                    b_y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
                  }

                  if (nm1d2 << 1 == n - 1) {
                    b_y->data[nm1d2] = (SFC + apnd) / 2.0;
                  } else {
                    b_y->data[nm1d2] = SFC + (double)nm1d2;
                    b_y->data[nm1d2 + 1] = apnd - (double)nm1d2;
                  }
                }
              }
            }

            i47 = b_tmp->size[0];
            b_tmp->size[0] = y->size[1];
            emxEnsureCapacity_real_T(b_tmp, i47);
            n = y->size[1];
            for (i47 = 0; i47 < n; i47++) {
              b_tmp->data[i47] = y->data[i47];
            }

            i47 = RD->size[0];
            RD->size[0] = b_y->size[1];
            emxEnsureCapacity_real_T(RD, i47);
            n = b_y->size[1];
            for (i47 = 0; i47 < n; i47++) {
              RD->data[i47] = b_y->data[i47];
            }

            Coder_baseline(b_tmp, RD, RD_data, idx, LinearOrNot, TC,
                           scd_fit_data, scd_fit_size, cff);
          }
        }
      }
    }
  } else {
    if ((temp_fit_data[0] < 0.0) && (cdiff / (temp_fit_data[(int)TC - 1] -
          temp_fit_data[(int)*EFC - 1]) > 0.1)) {
      u1 = *EFC - (double)b_idx;
      if (u1 >= 8.0) {
        ndbl = (double)b_idx - SFC;
        if (ndbl >= 1.0) {
          if (SFC > TC) {
            i47 = 0;
            i48 = 0;
          } else {
            i47 = (int)SFC - 1;
            i48 = (int)TC;
          }

          n = RD_size[0];
          if (RD_size[0] <= 2) {
            if (RD_size[0] == 1) {
              u0 = RD_data[0];
            } else if ((RD_data[0] < RD_data[1]) || (rtIsNaN(RD_data[0]) &&
                        (!rtIsNaN(RD_data[1])))) {
              u0 = RD_data[1];
            } else {
              u0 = RD_data[0];
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
              u0 = RD_data[0];
            } else {
              u0 = RD_data[idx - 1];
              i49 = idx + 1;
              for (k = i49; k <= n; k++) {
                apnd = RD_data[k - 1];
                if (u0 < apnd) {
                  u0 = apnd;
                }
              }
            }
          }

          nm1d2 = i48 - i47;
          for (i48 = 0; i48 < nm1d2; i48++) {
            varargin_1_data[i48] = RD_data[i47 + i48];
          }

          n = nm1d2 - 1;
          if (nm1d2 <= 2) {
            if (nm1d2 == 1) {
              cdiff = RD_data[i47];
            } else {
              cdiff = RD_data[i47 + 1];
              if ((RD_data[i47] > cdiff) || (rtIsNaN(RD_data[i47]) && (!rtIsNaN
                    (cdiff)))) {
              } else {
                cdiff = RD_data[i47];
              }
            }
          } else {
            if (!rtIsNaN(varargin_1_data[0])) {
              idx = 1;
            } else {
              idx = 0;
              k = 2;
              exitg1 = false;
              while ((!exitg1) && (k <= nm1d2)) {
                if (!rtIsNaN(varargin_1_data[k - 1])) {
                  idx = k;
                  exitg1 = true;
                } else {
                  k++;
                }
              }
            }

            if (idx == 0) {
              cdiff = RD_data[i47];
            } else {
              cdiff = varargin_1_data[idx - 1];
              i47 = idx + 1;
              for (k = i47; k <= n + 1; k++) {
                apnd = varargin_1_data[k - 1];
                if (cdiff > apnd) {
                  cdiff = apnd;
                }
              }
            }
          }

          if ((u0 - cdiff > 2.0 * DRFU * AR) && (RD_data[(int)TC - 1] - RD_data
               [0] > 0.0)) {
            if (rtIsNaN(*EFC)) {
              i47 = y->size[0] * y->size[1];
              y->size[0] = 1;
              y->size[1] = 1;
              emxEnsureCapacity_real_T(y, i47);
              y->data[0] = rtNaN;
            } else if (*EFC < b_idx) {
              y->size[0] = 1;
              y->size[1] = 0;
            } else if (rtIsInf(*EFC) && (b_idx == *EFC)) {
              i47 = y->size[0] * y->size[1];
              y->size[0] = 1;
              y->size[1] = 1;
              emxEnsureCapacity_real_T(y, i47);
              y->data[0] = rtNaN;
            } else {
              i47 = y->size[0] * y->size[1];
              y->size[0] = 1;
              n = (int)floor(u1);
              y->size[1] = n + 1;
              emxEnsureCapacity_real_T(y, i47);
              for (i47 = 0; i47 <= n; i47++) {
                y->data[i47] = (double)b_idx + (double)i47;
              }
            }

            if (b_idx < SFC) {
              b_y->size[0] = 1;
              b_y->size[1] = 0;
            } else if (floor(SFC) == SFC) {
              i47 = b_y->size[0] * b_y->size[1];
              b_y->size[0] = 1;
              n = (int)floor(ndbl);
              b_y->size[1] = n + 1;
              emxEnsureCapacity_real_T(b_y, i47);
              for (i47 = 0; i47 <= n; i47++) {
                b_y->data[i47] = SFC + (double)i47;
              }
            } else {
              nm1d2 = (int)floor(ndbl + 0.5);
              apnd = SFC + (double)nm1d2;
              cdiff = apnd - (double)b_idx;
              u1 = b_idx;
              if (SFC > u1) {
                u1 = SFC;
              }

              if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
                nm1d2++;
                apnd = b_idx;
              } else if (cdiff > 0.0) {
                apnd = SFC + ((double)nm1d2 - 1.0);
              } else {
                nm1d2++;
              }

              if (nm1d2 >= 0) {
                n = nm1d2;
              } else {
                n = 0;
              }

              i47 = b_y->size[0] * b_y->size[1];
              b_y->size[0] = 1;
              b_y->size[1] = n;
              emxEnsureCapacity_real_T(b_y, i47);
              if (n > 0) {
                b_y->data[0] = SFC;
                if (n > 1) {
                  b_y->data[n - 1] = apnd;
                  nm1d2 = (n - 1) / 2;
                  for (k = 0; k <= nm1d2 - 2; k++) {
                    b_y->data[1 + k] = SFC + (1.0 + (double)k);
                    b_y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
                  }

                  if (nm1d2 << 1 == n - 1) {
                    b_y->data[nm1d2] = (SFC + apnd) / 2.0;
                  } else {
                    b_y->data[nm1d2] = SFC + (double)nm1d2;
                    b_y->data[nm1d2 + 1] = apnd - (double)nm1d2;
                  }
                }
              }
            }

            i47 = b_tmp->size[0];
            b_tmp->size[0] = y->size[1];
            emxEnsureCapacity_real_T(b_tmp, i47);
            n = y->size[1];
            for (i47 = 0; i47 < n; i47++) {
              b_tmp->data[i47] = y->data[i47];
            }

            i47 = RD->size[0];
            RD->size[0] = b_y->size[1];
            emxEnsureCapacity_real_T(RD, i47);
            n = b_y->size[1];
            for (i47 = 0; i47 < n; i47++) {
              RD->data[i47] = b_y->data[i47];
            }

            Coder_baseline(b_tmp, RD, RD_data, b_idx, LinearOrNot, TC,
                           scd_fit_data, scd_fit_size, cff);
          }
        }
      }
    }
  }

  emxFree_real_T(&RD);
  emxFree_real_T(&c_y);

  /* ------------- U-sahpe신호 뻥튀기 방지 ------- */
  if ((RD_data[(int)TC - 1] < RD_data[0]) && (cff[0] > 0.0) && (LinearOrNot ==
       0.0) && (FB == 0.0)) {
    u1 = scd_fit_data[(int)*EFC0 - 1];
    if ((u1 - scd_fit_data[(int)TC - 1]) / (RD_data[(int)TC - 1] - u1) > 0.2) {
      nm1d2 = (int)(((float)*EFC0 - 50.0F) * ((float)*EFC0 - 50.0F));
      cff[0] = (u1 - (4.0 * u1 + scd_fit_data[(int)TC - 1]) / 5.0) / ((double)
        nm1d2 - (TC - 50.0) * (TC - 50.0));
      cff[1] = u1 - cff[0] * (double)nm1d2;
      if (*EFC0 > TC) {
        i47 = 1;
        i48 = 0;
      } else {
        i47 = (int)*EFC0;
        i48 = (int)TC;
      }

      if (rtIsNaN(TC)) {
        i49 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i49);
        y->data[0] = rtNaN;
        i49 = b_y->size[0] * b_y->size[1];
        b_y->size[0] = 1;
        b_y->size[1] = 1;
        emxEnsureCapacity_real_T(b_y, i49);
        b_y->data[0] = rtNaN;
      } else {
        if (TC < *EFC0) {
          y->size[0] = 1;
          y->size[1] = 0;
        } else if (*EFC0 == *EFC0) {
          i49 = y->size[0] * y->size[1];
          y->size[0] = 1;
          n = (int)floor(TC - *EFC0);
          y->size[1] = n + 1;
          emxEnsureCapacity_real_T(y, i49);
          for (i49 = 0; i49 <= n; i49++) {
            y->data[i49] = *EFC0 + (double)i49;
          }
        } else {
          ndbl = floor((TC - *EFC0) + 0.5);
          apnd = *EFC0 + ndbl;
          cdiff = apnd - TC;
          u0 = (int)*EFC0;
          if ((!(u0 > TC)) && (!rtIsNaN(TC))) {
            u0 = TC;
          }

          if (fabs(cdiff) < 4.4408920985006262E-16 * u0) {
            ndbl++;
            apnd = TC;
          } else if (cdiff > 0.0) {
            apnd = *EFC0 + (ndbl - 1.0);
          } else {
            ndbl++;
          }

          if (ndbl >= 0.0) {
            n = (int)ndbl;
          } else {
            n = 0;
          }

          i49 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = n;
          emxEnsureCapacity_real_T(y, i49);
          if (n > 0) {
            y->data[0] = *EFC0;
            if (n > 1) {
              y->data[n - 1] = apnd;
              nm1d2 = (n - 1) / 2;
              for (k = 0; k <= nm1d2 - 2; k++) {
                y->data[1 + k] = *EFC0 + (1.0 + (double)k);
                y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
              }

              if (nm1d2 << 1 == n - 1) {
                y->data[nm1d2] = (*EFC0 + apnd) / 2.0;
              } else {
                y->data[nm1d2] = *EFC0 + (double)nm1d2;
                y->data[nm1d2 + 1] = apnd - (double)nm1d2;
              }
            }
          }
        }

        if (TC < *EFC0) {
          b_y->size[0] = 1;
          b_y->size[1] = 0;
        } else if (*EFC0 == *EFC0) {
          i49 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = (int)floor(TC - *EFC0) + 1;
          emxEnsureCapacity_real_T(b_y, i49);
          n = (int)floor(TC - *EFC0);
          for (i49 = 0; i49 <= n; i49++) {
            b_y->data[i49] = *EFC0 + (double)i49;
          }
        } else {
          ndbl = floor((TC - *EFC0) + 0.5);
          apnd = *EFC0 + ndbl;
          cdiff = apnd - TC;
          u0 = (int)*EFC0;
          if ((!(u0 > TC)) && (!rtIsNaN(TC))) {
            u0 = TC;
          }

          if (fabs(cdiff) < 4.4408920985006262E-16 * u0) {
            ndbl++;
            apnd = TC;
          } else if (cdiff > 0.0) {
            apnd = *EFC0 + (ndbl - 1.0);
          } else {
            ndbl++;
          }

          if (ndbl >= 0.0) {
            n = (int)ndbl;
          } else {
            n = 0;
          }

          i49 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = n;
          emxEnsureCapacity_real_T(b_y, i49);
          if (n > 0) {
            b_y->data[0] = *EFC0;
            if (n > 1) {
              b_y->data[n - 1] = apnd;
              nm1d2 = (n - 1) / 2;
              for (k = 0; k <= nm1d2 - 2; k++) {
                b_y->data[1 + k] = *EFC0 + (1.0 + (double)k);
                b_y->data[(n - k) - 2] = apnd - (1.0 + (double)k);
              }

              if (nm1d2 << 1 == n - 1) {
                b_y->data[nm1d2] = (*EFC0 + apnd) / 2.0;
              } else {
                b_y->data[nm1d2] = *EFC0 + (double)nm1d2;
                b_y->data[nm1d2 + 1] = apnd - (double)nm1d2;
              }
            }
          }
        }
      }

      nm1d2 = (signed char)i48 - (signed char)i47;
      for (i48 = 0; i48 <= nm1d2; i48++) {
        tmp_data[i48] = (signed char)((signed char)((signed char)i47 + (signed
          char)i48) - 1);
      }

      i47 = xdata->size[0];
      xdata->size[0] = y->size[1];
      emxEnsureCapacity_real_T(xdata, i47);
      n = y->size[1];
      for (i47 = 0; i47 < n; i47++) {
        xdata->data[i47] = y->data[i47];
      }

      i47 = b_tmp->size[0];
      b_tmp->size[0] = b_y->size[1];
      emxEnsureCapacity_real_T(b_tmp, i47);
      n = b_y->size[1];
      for (i47 = 0; i47 < n; i47++) {
        b_tmp->data[i47] = b_y->data[i47];
      }

      y_size[0] = xdata->size[0];
      n = xdata->size[0];
      for (i47 = 0; i47 < n; i47++) {
        b_y_data[i47] = b_tmp->data[i47] - 50.0;
      }

      y_data.data = &b_y_data[0];
      y_data.size = &y_size[0];
      y_data.allocatedSize = 100;
      y_data.numDimensions = 1;
      y_data.canFreeData = false;
      power(&y_data, xdata);
      n = nm1d2 + 1;
      for (i47 = 0; i47 < n; i47++) {
        scd_fit_data[tmp_data[i47]] = cff[0] * xdata->data[i47] + cff[1];
      }
    }
  }

  emxFree_real_T(&b_tmp);
  emxFree_real_T(&b_y);
  emxFree_real_T(&y);
  emxFree_real_T(&xdata);

  /*  DataProcess(:,3)=scd_fit;%cff(1)*(x-50).^2+cff(2); */
}

/* End of code generation (Coder_Section_Baseline_v5.c) */
