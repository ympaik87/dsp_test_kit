/*
 * Coder_AsymmSigFit_old.c
 *
 * Code generation for function 'Coder_AsymmSigFit_old'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer.h"
#include "Coder_AsymmSigFit_old.h"
#include "Coder_invsig.h"
#include "Coder_SigFit_par.h"
#include "Coder_find_cycle.h"
#include "Coder_multi_amp.h"
#include "Coder_RT_PCR_analyzer_emxutil.h"
#include "dsig.h"
#include "Coder_SigFit_par3.h"
#include "Coder_SigFit_par2.h"
#include "Coder_RT_PCR_analyzer_rtwutil.h"

/* Function Definitions */
void Coder_AsymmSigFit_old(const double x_data[], const int x_size[1], const
  double ABSD_data[], const int ABSD_size[1], double f_data[], int f_size[1],
  double *result_well, double *DataProcessNum, double param[4], double SFC,
  double MFC, double EFC0, double TC, double SRFU, double Thrd, double
  Max_DRFU_Thrd, double *sht, const double perturbation_data[], double
  f_new_data[], int f_new_size[1], double param_new[4], double *sht2)
{
  double param3;
  emxArray_real_T *check_itv;
  emxArray_real_T *varargin_1;
  int i72;
  double ndbl;
  double apnd;
  double b_param3[2];
  double cdiff;
  int n;
  double u0;
  int b_ABSD_size[1];
  double u1;
  double f_new2_data[100];
  double b_SRFU[4];
  int nm1d2;
  int k;
  boolean_T exitg1;
  int SRFU_tmp_tmp_tmp;
  double param_new2[4];
  int f_new2_size[1];
  double b_u0;
  int c_ABSD_size[1];
  double b_ABSD_data[99];
  int i73;
  f_new_size[0] = x_size[0];
  if (0 <= x_size[0] - 1) {
    memset(&f_new_data[0], 0, (unsigned int)(x_size[0] * (int)sizeof(double)));
  }

  param_new[0] = 0.0;
  param_new[1] = 0.0;
  param_new[2] = 0.0;
  param_new[3] = 0.0;
  *sht2 = 0.0;
  param3 = rt_roundd_snf(param[2]);
  emxInit_real_T(&check_itv, 2);
  emxInit_real_T(&varargin_1, 1);
  if ((param3 > SFC) && (param3 < TC - 2.0) && (EFC0 < TC - 2.0)) {
    if (EFC0 + 2.0 < EFC0 - 2.0) {
      check_itv->size[0] = 1;
      check_itv->size[1] = 0;
    } else if ((rtIsInf(EFC0 - 2.0) || rtIsInf(EFC0 + 2.0)) && (EFC0 - 2.0 ==
                EFC0 + 2.0)) {
      i72 = check_itv->size[0] * check_itv->size[1];
      check_itv->size[0] = 1;
      check_itv->size[1] = 1;
      emxEnsureCapacity_real_T(check_itv, i72);
      check_itv->data[0] = rtNaN;
    } else if (floor(EFC0 - 2.0) == EFC0 - 2.0) {
      i72 = check_itv->size[0] * check_itv->size[1];
      check_itv->size[0] = 1;
      n = (int)floor((EFC0 + 2.0) - (EFC0 - 2.0));
      check_itv->size[1] = n + 1;
      emxEnsureCapacity_real_T(check_itv, i72);
      for (i72 = 0; i72 <= n; i72++) {
        check_itv->data[i72] = (EFC0 - 2.0) + (double)i72;
      }
    } else {
      ndbl = floor(((EFC0 + 2.0) - (EFC0 - 2.0)) + 0.5);
      apnd = (EFC0 - 2.0) + ndbl;
      cdiff = apnd - (EFC0 + 2.0);
      u0 = fabs(EFC0 - 2.0);
      u1 = fabs(EFC0 + 2.0);
      if (u0 > u1) {
        u1 = u0;
      }

      if (fabs(cdiff) < 4.4408920985006262E-16 * u1) {
        ndbl++;
        apnd = EFC0 + 2.0;
      } else if (cdiff > 0.0) {
        apnd = (EFC0 - 2.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = (int)ndbl;
      } else {
        n = 0;
      }

      i72 = check_itv->size[0] * check_itv->size[1];
      check_itv->size[0] = 1;
      check_itv->size[1] = n;
      emxEnsureCapacity_real_T(check_itv, i72);
      if (n > 0) {
        check_itv->data[0] = EFC0 - 2.0;
        if (n > 1) {
          check_itv->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (k = 0; k <= nm1d2 - 2; k++) {
            check_itv->data[1 + k] = (EFC0 - 2.0) + (1.0 + (double)k);
            check_itv->data[(n - k) - 2] = apnd - (1.0 + (double)k);
          }

          if (nm1d2 << 1 == n - 1) {
            check_itv->data[nm1d2] = ((EFC0 - 2.0) + apnd) / 2.0;
          } else {
            check_itv->data[nm1d2] = (EFC0 - 2.0) + (double)nm1d2;
            check_itv->data[nm1d2 + 1] = apnd - (double)nm1d2;
          }
        }
      }
    }

    ndbl = f_data[0];
    i72 = varargin_1->size[0];
    varargin_1->size[0] = check_itv->size[1];
    emxEnsureCapacity_real_T(varargin_1, i72);
    n = check_itv->size[1];
    for (i72 = 0; i72 < n; i72++) {
      varargin_1->data[i72] = ((f_data[(int)check_itv->data[i72] - 1] -
        ABSD_data[(int)check_itv->data[i72] - 1]) - ndbl) + SRFU;
    }

    n = varargin_1->size[0];
    if (varargin_1->size[0] <= 2) {
      if (varargin_1->size[0] == 1) {
        ndbl = varargin_1->data[0];
      } else if ((varargin_1->data[0] < varargin_1->data[1]) || (rtIsNaN
                  (varargin_1->data[0]) && (!rtIsNaN(varargin_1->data[1])))) {
        ndbl = varargin_1->data[1];
      } else {
        ndbl = varargin_1->data[0];
      }
    } else {
      if (!rtIsNaN(varargin_1->data[0])) {
        nm1d2 = 1;
      } else {
        nm1d2 = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= varargin_1->size[0])) {
          if (!rtIsNaN(varargin_1->data[k - 1])) {
            nm1d2 = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (nm1d2 == 0) {
        ndbl = varargin_1->data[0];
      } else {
        ndbl = varargin_1->data[nm1d2 - 1];
        i72 = nm1d2 + 1;
        for (k = i72; k <= n; k++) {
          if (ndbl < varargin_1->data[k - 1]) {
            ndbl = varargin_1->data[k - 1];
          }
        }
      }
    }

    if (ndbl / Thrd > 0.3) {
      if (fabs(f_data[(int)param3 - 1] - ABSD_data[(int)param3 - 1]) / (f_data
           [(int)TC - 1] - f_data[0]) < 0.05) {
        apnd = ABSD_data[(int)param3 - 1];
      } else {
        apnd = f_data[(int)param3 - 1];
      }

      if (apnd > Thrd) {
        cdiff = *result_well;
        b_SRFU[0] = SRFU;
        SRFU_tmp_tmp_tmp = (int)TC;
        nm1d2 = SRFU_tmp_tmp_tmp - 1;
        b_SRFU[1] = ABSD_data[nm1d2];
        b_SRFU[2] = param3;
        b_SRFU[3] = 0.2;
        b_param3[0] = param3;
        b_param3[1] = apnd;
        Coder_SigFit_par2(x_data, x_size, ABSD_data, &cdiff, param3, b_SRFU,
                          b_param3, SFC, perturbation_data, param_new,
                          f_new_data, f_new_size, &ndbl);
        if (cdiff == 0.0) {
          ndbl = *result_well;
          b_SRFU[0] = SRFU;
          b_SRFU[1] = ABSD_data[nm1d2];
          b_SRFU[2] = param3;
          b_SRFU[3] = 0.2;
          b_param3[0] = param3;
          b_param3[1] = apnd;
          Coder_SigFit_par3(x_data, x_size, ABSD_data, &ndbl, &param3, b_SRFU,
                            b_param3, TC, perturbation_data, param_new2,
                            f_new2_data, f_new2_size);
          if (ndbl == 0.0) {
            ndbl = dsig(param_new, param3);
            apnd = dsig(param_new2, param3);
            u0 = apnd / ndbl;
            u1 = ndbl / apnd;
            if ((u0 > u1) || rtIsNaN(u1)) {
              b_u0 = u0;
            } else {
              b_u0 = u1;
            }

            if (b_u0 > 1.5) {
              Coder_multi_amp(f_data, ABSD_data, ABSD_size, TC, &apnd, &ndbl,
                              b_param3);

              /* EC_Double */
              if (apnd < TC) {
                n = (int)apnd;
                c_ABSD_size[0] = n;
                if (0 <= n - 1) {
                  memcpy(&b_ABSD_data[0], &ABSD_data[0], (unsigned int)(n * (int)
                          sizeof(double)));
                }

                cdiff = *result_well;
                b_SRFU[0] = SRFU;
                b_SRFU[1] = ABSD_data[(int)apnd - 1];
                b_SRFU[2] = Coder_find_cycle(b_ABSD_data, c_ABSD_size, MFC, apnd);
                b_SRFU[3] = 0.2;
                Coder_SigFit_par(x_data, x_size, ABSD_data, &cdiff, apnd, b_SRFU,
                                 SFC, MFC - 2.0, perturbation_data, param_new,
                                 f_new_data, f_new_size, &ndbl);
                if ((cdiff == 0.0) && (f_new_data[nm1d2] - f_new_data[0] >
                                       Max_DRFU_Thrd)) {
                  ndbl = Thrd + *sht;
                  apnd = Thrd + f_new_data[0];
                  if (fabs((param[2] - log10((param[1] - ndbl) / (ndbl - param[0]))
                            / param[3]) - (param_new[2] - log10((param_new[1] -
                          apnd) / (apnd - param_new[0])) / param_new[3])) > 0.5)
                  {
                    *result_well = -2.0;
                    *DataProcessNum = -2.0;
                    *sht2 = f_new_data[0];
                  }
                }
              }
            }

            if (*result_well == 0.0) {
              /* && (DBorASMM<=2) */
              /* f(EC)=(f(EC)-dsig(param_new,EC)+f(EC)+dsig(param,EC))/2; */
              i72 = (int)param3;
              f_data[i72 - 1] = (f_new_data[i72 - 2] + f_new2_data[i72]) / 2.0;
              if (1.0 > param3 - 1.0) {
                i73 = 0;
              } else {
                i73 = (int)param3 - 1;
              }

              n = i73 - 1;
              if (0 <= n) {
                memcpy(&f_data[0], &f_new_data[0], (unsigned int)((n + 1) * (int)
                        sizeof(double)));
              }

              if (param3 + 1.0 > TC) {
                i72 = 1;
                SRFU_tmp_tmp_tmp = 0;
                k = 1;
              } else {
                i72++;
                k = (int)param3 + 1;
              }

              n = SRFU_tmp_tmp_tmp - i72;
              for (nm1d2 = 0; nm1d2 <= n; nm1d2++) {
                f_data[(k + nm1d2) - 1] = f_new2_data[(i72 + nm1d2) - 1];
              }

              *sht = f_data[0];
              param[0] = param_new[0];
              param[1] = param_new[1];
              param[2] = param_new[2];
              param[3] = param_new[3];
              *DataProcessNum = -3.0;
            }
          }
        }
      }
    }
  }

  emxFree_real_T(&varargin_1);
  emxFree_real_T(&check_itv);
  if ((*DataProcessNum == 0.0) && ((SRFU - f_data[0]) / (f_data[f_size[0] - 1] -
        f_data[0]) > 0.02)) {
    Coder_multi_amp(f_data, ABSD_data, ABSD_size, TC, &apnd, &ndbl, b_param3);

    /* EC_Double */
    n = (int)apnd;
    b_ABSD_size[0] = n;
    if (0 <= n - 1) {
      memcpy(&f_new2_data[0], &ABSD_data[0], (unsigned int)(n * (int)sizeof
              (double)));
    }

    cdiff = *result_well;
    b_SRFU[0] = SRFU;
    b_SRFU[1] = ABSD_data[(int)apnd - 1];
    b_SRFU[2] = Coder_find_cycle(f_new2_data, b_ABSD_size, MFC, apnd);
    b_SRFU[3] = 0.2;
    Coder_SigFit_par(x_data, x_size, ABSD_data, &cdiff, apnd, b_SRFU, SFC, MFC -
                     2.0, perturbation_data, param_new, f_new_data, f_new_size,
                     &ndbl);
    if ((cdiff == 0.0) && (f_new_data[(int)TC - 1] - f_new_data[0] >
                           Max_DRFU_Thrd)) {
      ndbl = Thrd + *sht;
      if (fabs((param[2] - log10((param[1] - ndbl) / (ndbl - param[0])) / param
                [3]) - Coder_invsig(param_new, Thrd + f_new_data[0])) > 0.5) {
        *result_well = -2.0;
        *DataProcessNum = -2.0;
        *sht2 = f_new_data[0];
      }
    }
  }
}

/* End of code generation (Coder_AsymmSigFit_old.c) */
