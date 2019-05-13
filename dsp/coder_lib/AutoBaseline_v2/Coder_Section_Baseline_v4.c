/*
 * Coder_Section_Baseline_v4.c
 *
 * Code generation for function 'Coder_Section_Baseline_v4'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_Section_Baseline_v4.h"
#include "AutoBaseline_v2_emxutil.h"
#include "power.h"
#include "Coder_baseline.h"
#include "Coder_scd_fitting.h"
#include "Coder_min5.h"
#include "Coder_SegMaxDiff.h"
#include "Coder_linear_fitting.h"

/* Function Definitions */
void Coder_Section_Baseline_v4(const double x_data[], const int x_size[1], const
  double RD_data[], const int RD_size[1], double SFC, double MFC, double *EFC,
  double TC, double DRFU, double LinearOrNot, double AR, double FB, double *EFC0,
  double cff[2], double scd_fit_data[], int scd_fit_size[1])
{
  double SC;
  emxArray_real_T *y;
  int i44;
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
  int i45;
  int i46;
  double b_SC;
  double varargin_1_data[199];
  int b_RD_size[1];
  double b_RD_data[100];
  double min5_idx[5];
  double varargin_1[3];
  int b_idx;
  emxArray_real_T *b_y;
  emxArray_real_T *c_y;
  boolean_T guard1 = false;
  signed char tmp_data[100];
  int y_size[1];
  emxArray_real_T y_data;
  double b_y_data[100];
  if (*EFC < MFC) {
    SC = 1.0;
  } else {
    SC = SFC;
  }

  emxInit_real_T(&y, 2);
  if (rtIsNaN(SC) || rtIsNaN(*EFC)) {
    i44 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i44);
    y->data[0] = rtNaN;
  } else if (*EFC < SC) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else if ((rtIsInf(SC) || rtIsInf(*EFC)) && (SC == *EFC)) {
    i44 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i44);
    y->data[0] = rtNaN;
  } else if (floor(SC) == SC) {
    i44 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)floor(*EFC - SC) + 1;
    emxEnsureCapacity_real_T(y, i44);
    n = (int)floor(*EFC - SC);
    for (i44 = 0; i44 <= n; i44++) {
      y->data[i44] = SC + (double)i44;
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

    i44 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = n;
    emxEnsureCapacity_real_T(y, i44);
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
  i44 = xdata->size[0];
  xdata->size[0] = y->size[1];
  emxEnsureCapacity_real_T(xdata, i44);
  n = y->size[1];
  for (i44 = 0; i44 < n; i44++) {
    xdata->data[i44] = y->data[i44];
  }

  emxInit_real_T(&RD, 1);

  /* temp fitting coeff */
  i44 = RD->size[0];
  RD->size[0] = xdata->size[0];
  emxEnsureCapacity_real_T(RD, i44);
  n = xdata->size[0];
  for (i44 = 0; i44 < n; i44++) {
    RD->data[i44] = RD_data[(int)xdata->data[i44] - 1];
  }

  Coder_scd_fitting(xdata, RD, &cff[0], &cff[1]);
  b_x_size[0] = x_size[0];
  n = x_size[0];
  for (i44 = 0; i44 < n; i44++) {
    b_x_data[i44] = x_data[i44] - 50.0;
  }

  emxInit_real_T(&b_tmp, 1);
  c_x_data.data = &b_x_data[0];
  c_x_data.size = &b_x_size[0];
  c_x_data.allocatedSize = 100;
  c_x_data.numDimensions = 1;
  c_x_data.canFreeData = false;
  power(&c_x_data, b_tmp);
  n = b_tmp->size[0];
  for (i44 = 0; i44 < n; i44++) {
    temp_fit_data[i44] = cff[0] * b_tmp->data[i44] + cff[1];
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
      i44 = idx + 1;
      for (k = i44; k <= n; k++) {
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
      i44 = idx + 1;
      for (k = i44; k <= n; k++) {
        u1 = RD_data[k - 1];
        if (cdiff > u1) {
          cdiff = u1;
        }
      }
    }
  }

  if (cff[0] >= 0.0) {
    if (SC > TC) {
      i44 = 0;
      i45 = 0;
      i46 = 0;
    } else {
      i44 = (int)SC - 1;
      i45 = (int)TC;
      i46 = (int)SC - 1;
    }

    nm1d2 = i45 - i44;
    for (i45 = 0; i45 < nm1d2; i45++) {
      varargin_1_data[i45] = RD_data[i44 + i45] - temp_fit_data[i46 + i45];
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
        i44 = idx + 1;
        for (k = i44; k <= nm1d2; k++) {
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
          i44 = idx + 1;
          for (k = i44; k < 6; k++) {
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
          i44 = idx + 1;
          for (k = i44; k < 4; k++) {
            u1 = varargin_1[k - 1];
            if (u0 < u1) {
              u0 = u1;
            }
          }

          *EFC = u0;
        }
      } else {
        if (MFC > TC) {
          i44 = 0;
          i45 = 0;
        } else {
          i44 = (int)MFC - 1;
          i45 = (int)TC;
        }

        i46 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = ((int)(MFC - 1.0) + i45) - i44;
        emxEnsureCapacity_real_T(y, i46);
        n = (int)(MFC - 1.0);
        for (i46 = 0; i46 < n; i46++) {
          y->data[i46] = rtMinusInf;
        }

        n = i45 - i44;
        for (i45 = 0; i45 < n; i45++) {
          y->data[i45 + (int)(MFC - 1.0)] = RD_data[i44 + i45];
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
            i44 = idx + 1;
            for (k = i44; k <= n; k++) {
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
        i44 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i44);
        y->data[0] = rtNaN;
      } else if (*EFC < SC) {
        y->size[0] = 1;
        y->size[1] = 0;
      } else if ((rtIsInf(SC) || rtIsInf(*EFC)) && (SC == *EFC)) {
        i44 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i44);
        y->data[0] = rtNaN;
      } else if (floor(SC) == SC) {
        i44 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = (int)floor(*EFC - SC) + 1;
        emxEnsureCapacity_real_T(y, i44);
        n = (int)floor(*EFC - SC);
        for (i44 = 0; i44 <= n; i44++) {
          y->data[i44] = SC + (double)i44;
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

        i44 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = n;
        emxEnsureCapacity_real_T(y, i44);
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

      i44 = xdata->size[0];
      xdata->size[0] = y->size[1];
      emxEnsureCapacity_real_T(xdata, i44);
      n = y->size[1];
      for (i44 = 0; i44 < n; i44++) {
        xdata->data[i44] = y->data[i44];
      }

      i44 = RD->size[0];
      RD->size[0] = xdata->size[0];
      emxEnsureCapacity_real_T(RD, i44);
      n = xdata->size[0];
      for (i44 = 0; i44 < n; i44++) {
        RD->data[i44] = RD_data[(int)xdata->data[i44] - 1];
      }

      Coder_scd_fitting(xdata, RD, &cff[0], &cff[1]);
    }
  } else {
    if (FB == 0.0) {
      u1 = TC;
    } else {
      if (MFC > TC) {
        i44 = 0;
        i45 = 0;
      } else {
        i44 = (int)MFC - 1;
        i45 = (int)TC;
      }

      i46 = y->size[0] * y->size[1];
      y->size[0] = 1;
      n = (int)(MFC - 1.0);
      y->size[1] = (n + i45) - i44;
      emxEnsureCapacity_real_T(y, i46);
      for (i46 = 0; i46 < n; i46++) {
        y->data[i46] = rtMinusInf;
      }

      nm1d2 = i45 - i44;
      for (i45 = 0; i45 < nm1d2; i45++) {
        y->data[i45 + n] = RD_data[i44 + i45];
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
          i44 = idx + 1;
          for (k = i44; k <= n; k++) {
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
        i44 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i44);
        y->data[0] = rtNaN;
      } else if (*EFC < SC) {
        y->size[0] = 1;
        y->size[1] = 0;
      } else if (rtIsInf(*EFC) && (SC == *EFC)) {
        i44 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i44);
        y->data[0] = rtNaN;
      } else if (SC == SC) {
        i44 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = (int)floor(*EFC - SC) + 1;
        emxEnsureCapacity_real_T(y, i44);
        n = (int)floor(*EFC - SC);
        for (i44 = 0; i44 <= n; i44++) {
          y->data[i44] = SC + (double)i44;
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

        i44 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = n;
        emxEnsureCapacity_real_T(y, i44);
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

      i44 = xdata->size[0];
      xdata->size[0] = y->size[1];
      emxEnsureCapacity_real_T(xdata, i44);
      n = y->size[1];
      for (i44 = 0; i44 < n; i44++) {
        xdata->data[i44] = y->data[i44];
      }

      if (LinearOrNot == 1.0) {
        i44 = RD->size[0];
        RD->size[0] = xdata->size[0];
        emxEnsureCapacity_real_T(RD, i44);
        n = xdata->size[0];
        for (i44 = 0; i44 < n; i44++) {
          RD->data[i44] = RD_data[(int)xdata->data[i44] - 1];
        }

        Coder_linear_fitting(xdata, RD, &cff[0], &cff[1]);
        LinearOrNot = 2.0;
      } else {
        i44 = RD->size[0];
        RD->size[0] = xdata->size[0];
        emxEnsureCapacity_real_T(RD, i44);
        n = xdata->size[0];
        for (i44 = 0; i44 < n; i44++) {
          RD->data[i44] = RD_data[(int)xdata->data[i44] - 1];
        }

        Coder_scd_fitting(xdata, RD, &cff[0], &cff[1]);
      }
    } else {
      if (LinearOrNot == 1.0) {
        i44 = RD->size[0];
        RD->size[0] = xdata->size[0];
        emxEnsureCapacity_real_T(RD, i44);
        n = xdata->size[0];
        for (i44 = 0; i44 < n; i44++) {
          RD->data[i44] = RD_data[(int)xdata->data[i44] - 1];
        }

        Coder_linear_fitting(xdata, RD, &cff[0], &cff[1]);
        LinearOrNot = 2.0;
      }
    }
  }

  *EFC0 = *EFC;

  /* -------- ≤™¿Ã¥¬ ≥ baseline ¿‚±‚ -------- */
  if (LinearOrNot == 2.0) {
    i44 = xdata->size[0];
    xdata->size[0] = x_size[0];
    emxEnsureCapacity_real_T(xdata, i44);
    n = x_size[0];
    for (i44 = 0; i44 < n; i44++) {
      xdata->data[i44] = cff[0] * x_data[i44];
    }

    nm1d2 = RD_size[0];
    n = RD_size[0];
    for (i44 = 0; i44 < n; i44++) {
      temp_fit_data[i44] = RD_data[i44] - (xdata->data[i44] + cff[1]);
    }

    scd_fit_size[0] = xdata->size[0];
    n = xdata->size[0];
    for (i44 = 0; i44 < n; i44++) {
      scd_fit_data[i44] = xdata->data[i44] + cff[1];
    }
  } else {
    nm1d2 = RD_size[0];
    n = RD_size[0];
    for (i44 = 0; i44 < n; i44++) {
      temp_fit_data[i44] = RD_data[i44] - (cff[0] * b_tmp->data[i44] + cff[1]);
    }

    scd_fit_size[0] = b_tmp->size[0];
    n = b_tmp->size[0];
    for (i44 = 0; i44 < n; i44++) {
      scd_fit_data[i44] = cff[0] * b_tmp->data[i44] + cff[1];
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
      i44 = idx + 1;
      for (k = i44; k <= nm1d2; k++) {
        u1 = temp_fit_data[k - 1];
        if (u0 > u1) {
          u0 = u1;
          idx = k;
        }
      }
    }
  }

  if (SFC + 1.0 > *EFC) {
    i44 = 0;
    i45 = 0;
  } else {
    i44 = (int)(SFC + 1.0) - 1;
    i45 = (int)*EFC;
  }

  if (rtIsNaN(SFC)) {
    i46 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i46);
    y->data[0] = rtNaN;
  } else if (SFC < 1.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else if (rtIsInf(SFC) && (1.0 == SFC)) {
    i46 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i46);
    y->data[0] = rtNaN;
  } else {
    i46 = y->size[0] * y->size[1];
    y->size[0] = 1;
    n = (int)floor(SFC - 1.0);
    y->size[1] = n + 1;
    emxEnsureCapacity_real_T(y, i46);
    for (i46 = 0; i46 <= n; i46++) {
      y->data[i46] = 1.0 + (double)i46;
    }
  }

  i46 = xdata->size[0];
  xdata->size[0] = (y->size[1] + i45) - i44;
  emxEnsureCapacity_real_T(xdata, i46);
  n = y->size[1];
  for (i46 = 0; i46 < n; i46++) {
    xdata->data[i46] = rtMinusInf * y->data[i46];
  }

  n = i45 - i44;
  for (i45 = 0; i45 < n; i45++) {
    xdata->data[i45 + y->size[1]] = temp_fit_data[i44 + i45];
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
      i44 = b_idx + 1;
      for (k = i44; k <= n; k++) {
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
    u1 = *EFC - (double)idx;
    guard1 = false;
    if (u1 >= 8.0) {
      ndbl = (double)idx - SFC;
      if (ndbl >= 1.0) {
        if (rtIsNaN(*EFC)) {
          i44 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = 1;
          emxEnsureCapacity_real_T(y, i44);
          y->data[0] = rtNaN;
        } else if (*EFC < idx) {
          y->size[0] = 1;
          y->size[1] = 0;
        } else if (rtIsInf(*EFC) && (idx == *EFC)) {
          i44 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = 1;
          emxEnsureCapacity_real_T(y, i44);
          y->data[0] = rtNaN;
        } else {
          i44 = y->size[0] * y->size[1];
          y->size[0] = 1;
          n = (int)floor(u1);
          y->size[1] = n + 1;
          emxEnsureCapacity_real_T(y, i44);
          for (i44 = 0; i44 <= n; i44++) {
            y->data[i44] = (double)idx + (double)i44;
          }
        }

        if (rtIsNaN(*EFC)) {
          i44 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = 1;
          emxEnsureCapacity_real_T(b_y, i44);
          b_y->data[0] = rtNaN;
        } else if (*EFC < idx) {
          b_y->size[0] = 1;
          b_y->size[1] = 0;
        } else if (rtIsInf(*EFC) && (idx == *EFC)) {
          i44 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = 1;
          emxEnsureCapacity_real_T(b_y, i44);
          b_y->data[0] = rtNaN;
        } else {
          i44 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = (int)floor(*EFC - (double)idx) + 1;
          emxEnsureCapacity_real_T(b_y, i44);
          n = (int)floor(*EFC - (double)idx);
          for (i44 = 0; i44 <= n; i44++) {
            b_y->data[i44] = (double)idx + (double)i44;
          }
        }

        if (rtIsNaN(SFC)) {
          i44 = c_y->size[0] * c_y->size[1];
          c_y->size[0] = 1;
          c_y->size[1] = 1;
          emxEnsureCapacity_real_T(c_y, i44);
          c_y->data[0] = rtNaN;
        } else if (idx < SFC) {
          c_y->size[0] = 1;
          c_y->size[1] = 0;
        } else if (rtIsInf(SFC) && (SFC == idx)) {
          i44 = c_y->size[0] * c_y->size[1];
          c_y->size[0] = 1;
          c_y->size[1] = 1;
          emxEnsureCapacity_real_T(c_y, i44);
          c_y->data[0] = rtNaN;
        } else if (floor(SFC) == SFC) {
          i44 = c_y->size[0] * c_y->size[1];
          c_y->size[0] = 1;
          n = (int)floor(ndbl);
          c_y->size[1] = n + 1;
          emxEnsureCapacity_real_T(c_y, i44);
          for (i44 = 0; i44 <= n; i44++) {
            c_y->data[i44] = SFC + (double)i44;
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
          i44 = c_y->size[0] * c_y->size[1];
          c_y->size[0] = 1;
          c_y->size[1] = n;
          emxEnsureCapacity_real_T(c_y, i44);
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

        i44 = xdata->size[0];
        xdata->size[0] = y->size[1];
        emxEnsureCapacity_real_T(xdata, i44);
        n = y->size[1];
        for (i44 = 0; i44 < n; i44++) {
          xdata->data[i44] = y->data[i44];
        }

        i44 = b_tmp->size[0];
        b_tmp->size[0] = xdata->size[0];
        emxEnsureCapacity_real_T(b_tmp, i44);
        n = xdata->size[0];
        for (i44 = 0; i44 < n; i44++) {
          b_tmp->data[i44] = b_y->data[i44];
        }

        i44 = RD->size[0];
        RD->size[0] = c_y->size[1];
        emxEnsureCapacity_real_T(RD, i44);
        n = c_y->size[1];
        for (i44 = 0; i44 < n; i44++) {
          RD->data[i44] = c_y->data[i44];
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
        i44 = 0;
        i45 = 0;
      } else {
        i44 = (int)(SFC + 1.0) - 1;
        i45 = b_idx;
      }

      if (rtIsNaN(SFC)) {
        i46 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i46);
        y->data[0] = rtNaN;
      } else if (SFC < 1.0) {
        y->size[0] = 1;
        y->size[1] = 0;
      } else if (rtIsInf(SFC) && (1.0 == SFC)) {
        i46 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i46);
        y->data[0] = rtNaN;
      } else {
        i46 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = (int)floor(SFC - 1.0) + 1;
        emxEnsureCapacity_real_T(y, i46);
        n = (int)floor(SFC - 1.0);
        for (i46 = 0; i46 <= n; i46++) {
          y->data[i46] = 1.0 + (double)i46;
        }
      }

      i46 = xdata->size[0];
      xdata->size[0] = (y->size[1] + i45) - i44;
      emxEnsureCapacity_real_T(xdata, i46);
      n = y->size[1];
      for (i46 = 0; i46 < n; i46++) {
        xdata->data[i46] = rtInf * y->data[i46];
      }

      n = i45 - i44;
      for (i45 = 0; i45 < n; i45++) {
        xdata->data[i45 + y->size[1]] = temp_fit_data[i44 + i45];
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
          i44 = idx + 1;
          for (k = i44; k <= n; k++) {
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
            i44 = y->size[0] * y->size[1];
            y->size[0] = 1;
            n = b_idx - idx;
            y->size[1] = n + 1;
            emxEnsureCapacity_real_T(y, i44);
            for (i44 = 0; i44 <= n; i44++) {
              y->data[i44] = idx + i44;
            }
          }

          if (rtIsNaN(SFC)) {
            i44 = b_y->size[0] * b_y->size[1];
            b_y->size[0] = 1;
            b_y->size[1] = 1;
            emxEnsureCapacity_real_T(b_y, i44);
            b_y->data[0] = rtNaN;
          } else if (idx < SFC) {
            b_y->size[0] = 1;
            b_y->size[1] = 0;
          } else if (rtIsInf(SFC) && (SFC == idx)) {
            i44 = b_y->size[0] * b_y->size[1];
            b_y->size[0] = 1;
            b_y->size[1] = 1;
            emxEnsureCapacity_real_T(b_y, i44);
            b_y->data[0] = rtNaN;
          } else if (floor(SFC) == SFC) {
            i44 = b_y->size[0] * b_y->size[1];
            b_y->size[0] = 1;
            n = (int)floor(u1);
            b_y->size[1] = n + 1;
            emxEnsureCapacity_real_T(b_y, i44);
            for (i44 = 0; i44 <= n; i44++) {
              b_y->data[i44] = SFC + (double)i44;
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
            i44 = b_y->size[0] * b_y->size[1];
            b_y->size[0] = 1;
            b_y->size[1] = n;
            emxEnsureCapacity_real_T(b_y, i44);
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

          i44 = b_tmp->size[0];
          b_tmp->size[0] = y->size[1];
          emxEnsureCapacity_real_T(b_tmp, i44);
          n = y->size[1];
          for (i44 = 0; i44 < n; i44++) {
            b_tmp->data[i44] = y->data[i44];
          }

          i44 = RD->size[0];
          RD->size[0] = b_y->size[1];
          emxEnsureCapacity_real_T(RD, i44);
          n = b_y->size[1];
          for (i44 = 0; i44 < n; i44++) {
            RD->data[i44] = b_y->data[i44];
          }

          Coder_baseline(b_tmp, RD, RD_data, idx, LinearOrNot, TC, scd_fit_data,
                         scd_fit_size, cff);
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
            i44 = 0;
            i45 = 0;
          } else {
            i44 = (int)SFC - 1;
            i45 = (int)TC;
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
              i46 = idx + 1;
              for (k = i46; k <= n; k++) {
                apnd = RD_data[k - 1];
                if (u0 < apnd) {
                  u0 = apnd;
                }
              }
            }
          }

          nm1d2 = i45 - i44;
          for (i45 = 0; i45 < nm1d2; i45++) {
            varargin_1_data[i45] = RD_data[i44 + i45];
          }

          n = nm1d2 - 1;
          if (nm1d2 <= 2) {
            if (nm1d2 == 1) {
              cdiff = RD_data[i44];
            } else {
              cdiff = RD_data[i44 + 1];
              if ((RD_data[i44] > cdiff) || (rtIsNaN(RD_data[i44]) && (!rtIsNaN
                    (cdiff)))) {
              } else {
                cdiff = RD_data[i44];
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
              cdiff = RD_data[i44];
            } else {
              cdiff = varargin_1_data[idx - 1];
              i44 = idx + 1;
              for (k = i44; k <= n + 1; k++) {
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
              i44 = y->size[0] * y->size[1];
              y->size[0] = 1;
              y->size[1] = 1;
              emxEnsureCapacity_real_T(y, i44);
              y->data[0] = rtNaN;
            } else if (*EFC < b_idx) {
              y->size[0] = 1;
              y->size[1] = 0;
            } else if (rtIsInf(*EFC) && (b_idx == *EFC)) {
              i44 = y->size[0] * y->size[1];
              y->size[0] = 1;
              y->size[1] = 1;
              emxEnsureCapacity_real_T(y, i44);
              y->data[0] = rtNaN;
            } else {
              i44 = y->size[0] * y->size[1];
              y->size[0] = 1;
              n = (int)floor(u1);
              y->size[1] = n + 1;
              emxEnsureCapacity_real_T(y, i44);
              for (i44 = 0; i44 <= n; i44++) {
                y->data[i44] = (double)b_idx + (double)i44;
              }
            }

            if (b_idx < SFC) {
              b_y->size[0] = 1;
              b_y->size[1] = 0;
            } else if (floor(SFC) == SFC) {
              i44 = b_y->size[0] * b_y->size[1];
              b_y->size[0] = 1;
              n = (int)floor(ndbl);
              b_y->size[1] = n + 1;
              emxEnsureCapacity_real_T(b_y, i44);
              for (i44 = 0; i44 <= n; i44++) {
                b_y->data[i44] = SFC + (double)i44;
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

              i44 = b_y->size[0] * b_y->size[1];
              b_y->size[0] = 1;
              b_y->size[1] = n;
              emxEnsureCapacity_real_T(b_y, i44);
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

            i44 = b_tmp->size[0];
            b_tmp->size[0] = y->size[1];
            emxEnsureCapacity_real_T(b_tmp, i44);
            n = y->size[1];
            for (i44 = 0; i44 < n; i44++) {
              b_tmp->data[i44] = y->data[i44];
            }

            i44 = RD->size[0];
            RD->size[0] = b_y->size[1];
            emxEnsureCapacity_real_T(RD, i44);
            n = b_y->size[1];
            for (i44 = 0; i44 < n; i44++) {
              RD->data[i44] = b_y->data[i44];
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

  /* ------------- U-sahpeΩ≈»£ ªΩ∆¢±‚ πÊ¡ˆ ------- */
  if ((RD_data[(int)TC - 1] < RD_data[0]) && (cff[0] > 0.0) && (LinearOrNot ==
       0.0) && (FB == 0.0)) {
    u1 = scd_fit_data[(int)*EFC0 - 1];
    if ((u1 - scd_fit_data[(int)TC - 1]) / (RD_data[(int)TC - 1] - u1) > 0.2) {
      nm1d2 = (int)(((float)*EFC0 - 50.0F) * ((float)*EFC0 - 50.0F));
      cff[0] = (u1 - (4.0 * u1 + scd_fit_data[(int)TC - 1]) / 5.0) / ((double)
        nm1d2 - (TC - 50.0) * (TC - 50.0));
      cff[1] = u1 - cff[0] * (double)nm1d2;
      if (*EFC0 > TC) {
        i44 = 1;
        i45 = 0;
      } else {
        i44 = (int)*EFC0;
        i45 = (int)TC;
      }

      if (rtIsNaN(TC)) {
        i46 = y->size[0] * y->size[1];
        y->size[0] = 1;
        y->size[1] = 1;
        emxEnsureCapacity_real_T(y, i46);
        y->data[0] = rtNaN;
        i46 = b_y->size[0] * b_y->size[1];
        b_y->size[0] = 1;
        b_y->size[1] = 1;
        emxEnsureCapacity_real_T(b_y, i46);
        b_y->data[0] = rtNaN;
      } else {
        if (TC < *EFC0) {
          y->size[0] = 1;
          y->size[1] = 0;
        } else if (*EFC0 == *EFC0) {
          i46 = y->size[0] * y->size[1];
          y->size[0] = 1;
          n = (int)floor(TC - *EFC0);
          y->size[1] = n + 1;
          emxEnsureCapacity_real_T(y, i46);
          for (i46 = 0; i46 <= n; i46++) {
            y->data[i46] = *EFC0 + (double)i46;
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

          i46 = y->size[0] * y->size[1];
          y->size[0] = 1;
          y->size[1] = n;
          emxEnsureCapacity_real_T(y, i46);
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
          i46 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = (int)floor(TC - *EFC0) + 1;
          emxEnsureCapacity_real_T(b_y, i46);
          n = (int)floor(TC - *EFC0);
          for (i46 = 0; i46 <= n; i46++) {
            b_y->data[i46] = *EFC0 + (double)i46;
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

          i46 = b_y->size[0] * b_y->size[1];
          b_y->size[0] = 1;
          b_y->size[1] = n;
          emxEnsureCapacity_real_T(b_y, i46);
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

      nm1d2 = (signed char)i45 - (signed char)i44;
      for (i45 = 0; i45 <= nm1d2; i45++) {
        tmp_data[i45] = (signed char)((signed char)((signed char)i44 + (signed
          char)i45) - 1);
      }

      i44 = xdata->size[0];
      xdata->size[0] = y->size[1];
      emxEnsureCapacity_real_T(xdata, i44);
      n = y->size[1];
      for (i44 = 0; i44 < n; i44++) {
        xdata->data[i44] = y->data[i44];
      }

      i44 = b_tmp->size[0];
      b_tmp->size[0] = b_y->size[1];
      emxEnsureCapacity_real_T(b_tmp, i44);
      n = b_y->size[1];
      for (i44 = 0; i44 < n; i44++) {
        b_tmp->data[i44] = b_y->data[i44];
      }

      y_size[0] = xdata->size[0];
      n = xdata->size[0];
      for (i44 = 0; i44 < n; i44++) {
        b_y_data[i44] = b_tmp->data[i44] - 50.0;
      }

      y_data.data = &b_y_data[0];
      y_data.size = &y_size[0];
      y_data.allocatedSize = 100;
      y_data.numDimensions = 1;
      y_data.canFreeData = false;
      power(&y_data, xdata);
      n = nm1d2 + 1;
      for (i44 = 0; i44 < n; i44++) {
        scd_fit_data[tmp_data[i44]] = cff[0] * xdata->data[i44] + cff[1];
      }
    }
  }

  emxFree_real_T(&b_tmp);
  emxFree_real_T(&b_y);
  emxFree_real_T(&y);
  emxFree_real_T(&xdata);

  /*  DataProcess(:,3)=scd_fit;%cff(1)*(x-50).^2+cff(2); */
}

/* End of code generation (Coder_Section_Baseline_v4.c) */
