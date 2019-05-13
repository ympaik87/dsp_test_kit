/*
 * Coder_AsymmSigFit.c
 *
 * Code generation for function 'Coder_AsymmSigFit'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_AsymmSigFit.h"
#include "Coder_invsig.h"
#include "Coder_SigFit_par.h"
#include "Coder_find_cycle.h"
#include "Coder_multi_amp.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "mean.h"
#include "var.h"
#include "dsig.h"
#include "Coder_SigFit_par3.h"
#include "Coder_SigFit_par2.h"
#include "sum.h"
#include "abs.h"
#include "diff.h"
#include "Coder_local_smoothing.h"
#include "Coder_SingleThresholdCt.h"
#include "Coder_AsymmSigFit_old.h"
#include "Coder_RT_PCR_analyzer_v2_1_rtwutil.h"

/* Function Definitions */
void Coder_AsymmSigFit(const double x_data[], const int x_size[1], const double
  ABSD_data[], const int ABSD_size[1], double f_data[], int f_size[1], double
  *result_well, double *DataProcessNum, double param[4], double SFC, double MFC,
  double EFC0, double TC, double SRFU, double Thrd, double Max_DRFU_Thrd, double
  *sht, const double perturbation_data[], double f_new_data[], int f_new_size[1],
  double param_new[4], double *sht2)
{
  double param3;
  emxArray_real_T *check_itv;
  emxArray_real_T *varargin_1;
  int i96;
  double ndbl;
  double apnd;
  double cdiff;
  int nm1d2;
  double u1;
  double RFU_EC_array[2];
  double u0;
  int ABSD_size_tmp;
  int b_ABSD_size[1];
  int n;
  double b_ABSD_data[100];
  double b_SRFU[4];
  int num_RFU_EC;
  boolean_T exitg1;
  double check_val;
  double Ct_diff_tmp;
  double EC;
  double RFU_EC;
  double DBorASMM;
  int i_ASMM;
  int i_DB;
  double param_new_DB[4];
  int f_new_DB_size[1];
  double f_new_DB_data[100];
  double RFU_EC_save;
  double EC_save;
  double f_new2_data[100];
  double check_itv2[5];
  double f[5];
  int i97;
  double b_check_itv2[5];
  int i98;
  double param_left[4];
  double param_right[4];
  int i99;
  int i100;
  int i101;
  double f_temp[5];
  int i_RFU_EC;
  double b_EC[2];
  double f_left_data[100];
  int f_left_size[1];
  double f_right_data[100];
  int f_right_size[1];
  int c_ABSD_size[1];
  double c_ABSD_data[97];
  int d_ABSD_size[1];
  double d_ABSD_data[97];
  int e_ABSD_size[1];
  int f_ABSD_size[1];
  int g_ABSD_size[1];
  double e_ABSD_data[99];
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

  /*  fprintf('param3_before_if= %s\n', Double2String(param3)) */
  emxInit_real_T(&check_itv, 2);
  emxInit_real_T(&varargin_1, 1);
  if ((param3 > SFC) && (param3 < TC - 2.0) && (EFC0 < TC - 2.0)) {
    /*      fprintf('param3_after_if= %s\n', Double2String(param3)) */
    /*      fprintf('ABSD=[ %s, ', Double2String(ABSD(1))) */
    /*      for i=2:44 */
    /*          fprintf('%s, ', Double2String(ABSD(i))) */
    /*      end */
    /*      fprintf('%s]\n ', Double2String(ABSD(45))) */
    /*      fprintf('f=[ %s, ', Double2String(f(1))) */
    /*      for i=2:44 */
    /*          fprintf('%s, ', Double2String(f(i))) */
    /*      end */
    /*      fprintf('%s]\n ', Double2String(f(45))) */
    if (EFC0 + 2.0 < EFC0 - 2.0) {
      check_itv->size[0] = 1;
      check_itv->size[1] = 0;
    } else if ((rtIsInf(EFC0 - 2.0) || rtIsInf(EFC0 + 2.0)) && (EFC0 - 2.0 ==
                EFC0 + 2.0)) {
      i96 = check_itv->size[0] * check_itv->size[1];
      check_itv->size[0] = 1;
      check_itv->size[1] = 1;
      emxEnsureCapacity_real_T(check_itv, i96);
      check_itv->data[0] = rtNaN;
    } else if (floor(EFC0 - 2.0) == EFC0 - 2.0) {
      i96 = check_itv->size[0] * check_itv->size[1];
      check_itv->size[0] = 1;
      nm1d2 = (int)floor((EFC0 + 2.0) - (EFC0 - 2.0));
      check_itv->size[1] = nm1d2 + 1;
      emxEnsureCapacity_real_T(check_itv, i96);
      for (i96 = 0; i96 <= nm1d2; i96++) {
        check_itv->data[i96] = (EFC0 - 2.0) + (double)i96;
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

      i96 = check_itv->size[0] * check_itv->size[1];
      check_itv->size[0] = 1;
      check_itv->size[1] = n;
      emxEnsureCapacity_real_T(check_itv, i96);
      if (n > 0) {
        check_itv->data[0] = EFC0 - 2.0;
        if (n > 1) {
          check_itv->data[n - 1] = apnd;
          nm1d2 = (n - 1) / 2;
          for (num_RFU_EC = 0; num_RFU_EC <= nm1d2 - 2; num_RFU_EC++) {
            check_itv->data[1 + num_RFU_EC] = (EFC0 - 2.0) + (1.0 + (double)
              num_RFU_EC);
            check_itv->data[(n - num_RFU_EC) - 2] = apnd - (1.0 + (double)
              num_RFU_EC);
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
    i96 = varargin_1->size[0];
    varargin_1->size[0] = check_itv->size[1];
    emxEnsureCapacity_real_T(varargin_1, i96);
    nm1d2 = check_itv->size[1];
    for (i96 = 0; i96 < nm1d2; i96++) {
      varargin_1->data[i96] = ((f_data[(int)check_itv->data[i96] - 1] -
        ABSD_data[(int)check_itv->data[i96] - 1]) - ndbl) + SRFU;
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
        num_RFU_EC = 2;
        exitg1 = false;
        while ((!exitg1) && (num_RFU_EC <= varargin_1->size[0])) {
          if (!rtIsNaN(varargin_1->data[num_RFU_EC - 1])) {
            nm1d2 = num_RFU_EC;
            exitg1 = true;
          } else {
            num_RFU_EC++;
          }
        }
      }

      if (nm1d2 == 0) {
        ndbl = varargin_1->data[0];
      } else {
        ndbl = varargin_1->data[nm1d2 - 1];
        i96 = nm1d2 + 1;
        for (num_RFU_EC = i96; num_RFU_EC <= n; num_RFU_EC++) {
          if (ndbl < varargin_1->data[num_RFU_EC - 1]) {
            ndbl = varargin_1->data[num_RFU_EC - 1];
          }
        }
      }
    }

    check_val = ndbl / Thrd;

    /*       */
    /*      fprintf('check_itv=[%s, %s]\n', Double2String(check_itv(1)),Double2String(check_itv(end))) */
    /*      fprintf('check_val=%s\n ', Double2String(check_val))     */
    /*       */
    /*  Coder_invsig(param,Thrd+sht) */
    /*  Coder_SingleThresholdCt(ABSD,MFC,TC,Thrd+sht) */
    ndbl = Thrd + *sht;
    Ct_diff_tmp = Coder_invsig(param, ndbl);
    ndbl = fabs(Ct_diff_tmp - Coder_SingleThresholdCt(ABSD_data, MFC, TC, ndbl));

    /* PC일때만 (check_val>0.2) || (Ct_diff>0.4 && Ct_diff<5) 하고 싶은데 지금 바꾸기 어려움 */
    /*      if (check_val>0.2) || (Ct_diff>0.4 && Ct_diff<5) */
    if ((check_val > 0.3) || ((ndbl > 0.8) && (ndbl < 5.0))) {
      EC = param3;

      /*          RFU_EC=1000000000;%inf;  */
      RFU_EC = rtInf;
      DBorASMM = 3.0;
      i_ASMM = 0;
      i_DB = 1;
      param_new_DB[0] = 0.0;
      param_new_DB[1] = 0.0;
      param_new_DB[2] = 0.0;
      param_new_DB[3] = 0.0;
      f_new_DB_size[0] = x_size[0];
      if (0 <= x_size[0] - 1) {
        memset(&f_new_DB_data[0], 0, (unsigned int)(x_size[0] * (int)sizeof
                (double)));
      }

      RFU_EC_save = 0.0;
      EC_save = 0.0;
      if (0 <= x_size[0] - 1) {
        memset(&f_new2_data[0], 0, (unsigned int)(x_size[0] * (int)sizeof(double)));
      }

      /*          if isequal(i_rgt,'GIP') && ismember(well,PC_well) && i_ch==4 && i_Tm==1 */
      /*              ABSD=signal_corrector(x,ABSD,EFC0,TC); */
      /*          end */
      /*           */
      /*          fprintf('RFU_EC=%s\n ', Double2String(RFU_EC)) */
      /*          fprintf('SRFU=%s\n ', Double2String(SRFU)) */
      while ((RFU_EC - SRFU > Thrd) && (EC > SFC) && (DBorASMM > 1.5) && (i_ASMM
              <= 5)) {
        i_ASMM++;

        /*              fprintf('i_ASMM= %s\n ', Double2String(i_ASMM)) */
        for (i96 = 0; i96 < 5; i96++) {
          check_itv2[i96] = ABSD_data[(int)(EC + (-2.0 + (double)i96)) - 1];
        }

        b_Coder_local_smoothing(check_itv2, f);
        for (nm1d2 = 0; nm1d2 < 5; nm1d2++) {
          b_check_itv2[nm1d2] = check_itv2[nm1d2] - f[nm1d2];
        }

        d_diff(b_check_itv2, b_SRFU);
        param_left[0] = b_SRFU[0];
        param_left[1] = b_SRFU[1];
        param_left[2] = b_SRFU[2];
        param_left[3] = b_SRFU[3];
        d_abs(param_left, b_SRFU);
        param_right[0] = b_SRFU[0];
        param_right[1] = b_SRFU[1];
        param_right[2] = b_SRFU[2];
        param_right[3] = b_SRFU[3];
        nm1d2 = (int)TC;
        n = nm1d2 - 1;
        ndbl = b_sum(param_right) / (f_data[n] - f_data[0]);
        if (ndbl < 0.2) {
          RFU_EC_array[0] = ABSD_data[(int)EC - 1];
          RFU_EC_array[1] = f_data[(int)EC - 1];
          num_RFU_EC = 2;
        } else if (ndbl < 0.4) {
          RFU_EC_array[0] = f_data[(int)EC - 1];
          RFU_EC_array[1] = ABSD_data[(int)EC - 1];
          num_RFU_EC = 2;
        } else {
          RFU_EC_array[0] = f_data[(int)EC - 1];
          RFU_EC_array[1] = 0.0;
          num_RFU_EC = 1;
        }

        i_RFU_EC = 0;
        exitg1 = false;
        while ((!exitg1) && (i_RFU_EC <= num_RFU_EC - 1)) {
          RFU_EC = RFU_EC_array[i_RFU_EC];

          /*                  fprintf('RFU_EC= %s\n', Double2String(RFU_EC)) */
          if (RFU_EC_array[i_RFU_EC] - SRFU > Thrd) {
            /*                      fprintf('ABSD=[ %s, ', Double2String(ABSD(1))) */
            /*                      for i=2:44 */
            /*                          fprintf('%s, ', Double2String(ABSD(i))) */
            /*                      end */
            /*                      fprintf('%s]\n ', Double2String(ABSD(45))) */
            /*                      fprintf('f=[ %s, ', Double2String(f(1))) */
            /*                      for i=2:44 */
            /*                          fprintf('%s, ', Double2String(f(i))) */
            /*                      end */
            /*                      fprintf('%s]\n ', Double2String(f(45))) */
            ndbl = *result_well;
            b_SRFU[0] = SRFU;
            b_SRFU[1] = ABSD_data[n];
            b_SRFU[2] = param3;
            b_SRFU[3] = 0.2;
            b_EC[0] = EC;
            b_EC[1] = RFU_EC_array[i_RFU_EC];
            Coder_SigFit_par2(x_data, x_size, ABSD_data, &ndbl, EC, b_SRFU, b_EC,
                              SFC, perturbation_data, param_left, f_left_data,
                              f_left_size, &apnd);

            /*                      fprintf('result1 %s\n', Double2String(result1)) */
            /*                      fprintf('param_left[ %s, ', Double2String(param_left(1))) */
            /*                      for i=2:3 */
            /*                          fprintf('%s, ', Double2String(param_left(i))) */
            /*                      end */
            /*                      fprintf('%s]\n ', Double2String(param_left(4))) */
            /*                       */
            /*                       */
            /*                      fprintf('ABSD=[ %s, ', Double2String(ABSD(1))) */
            /*                      for i=2:44 */
            /*                          fprintf('%s, ', Double2String(ABSD(i))) */
            /*                      end */
            /*                      fprintf('%s]\n ', Double2String(ABSD(45))) */
            /*                      fprintf('f=[ %s, ', Double2String(f(1))) */
            /*                      for i=2:44 */
            /*                          fprintf('%s, ', Double2String(f(i))) */
            /*                      end */
            /*                      fprintf('%s]\n ', Double2String(f(45))) */
            /*                      fprintf('TC=%s\n ', Double2String(TC)) */
            /*                      fprintf('EC=%s\n ', Double2String(EC)) */
            if (ndbl == 0.0) {
              ndbl = *result_well;
              b_SRFU[0] = SRFU;
              b_SRFU[1] = ABSD_data[(int)TC - 1];
              b_SRFU[2] = param3;
              b_SRFU[3] = 0.2;
              b_EC[0] = EC;
              b_EC[1] = RFU_EC_array[i_RFU_EC];
              Coder_SigFit_par3(x_data, x_size, ABSD_data, &ndbl, &EC, b_SRFU,
                                b_EC, TC, perturbation_data, param_right,
                                f_right_data, f_right_size);

              /*                          fprintf('result2 %s\n', Double2String(result2)) */
              /*                          fprintf('param_right[ %s, ', Double2String(param_right(1))) */
              /*                          for i=2:3 */
              /*                              fprintf('%s, ', Double2String(param_right(i))) */
              /*                          end */
              /*                          fprintf('%s]\n ', Double2String(param_right(4))) */
              if (ndbl == 0.0) {
                ndbl = dsig(param_left, EC);
                apnd = dsig(param_right, EC);
                u0 = apnd / ndbl;
                u1 = ndbl / apnd;
                if ((u0 > u1) || rtIsNaN(u1)) {
                  ndbl = u0;
                } else {
                  ndbl = u1;
                }

                /*                              fprintf('DBorASMM_temp= %s\n', Double2String(DBorASMM_temp)) */
                if (ndbl < DBorASMM) {
                  param_new[0] = param_left[0];
                  param_new[1] = param_left[1];
                  param_new[2] = param_left[2];
                  param_new[3] = param_left[3];
                  f_new_size[0] = f_left_size[0];
                  if (0 <= f_left_size[0] - 1) {
                    memcpy(&f_new_data[0], &f_left_data[0], (unsigned int)
                           (f_left_size[0] * (int)sizeof(double)));
                  }

                  if (0 <= f_right_size[0] - 1) {
                    memcpy(&f_new2_data[0], &f_right_data[0], (unsigned int)
                           (f_right_size[0] * (int)sizeof(double)));
                  }

                  RFU_EC_save = RFU_EC_array[i_RFU_EC];
                  EC_save = EC;
                  DBorASMM = ndbl;
                }

                if ((i_DB == 1) && (1 + i_RFU_EC == 1) && (check_val > 0.3)) {
                  if (SFC > EC) {
                    i96 = 0;
                    i97 = 0;
                    i99 = 0;
                    i100 = 0;
                    i101 = 0;
                  } else {
                    i96 = (int)SFC - 1;
                    i97 = (int)EC;
                    i99 = (int)SFC - 1;
                    i100 = (int)SFC - 1;
                    i101 = (int)EC;
                  }

                  ABSD_size_tmp = i97 - i96;
                  c_ABSD_size[0] = ABSD_size_tmp;
                  for (i97 = 0; i97 < ABSD_size_tmp; i97++) {
                    c_ABSD_data[i97] = ABSD_data[i96 + i97] - f_left_data[i99 +
                      i97];
                  }

                  ABSD_size_tmp = i101 - i100;
                  d_ABSD_size[0] = ABSD_size_tmp;
                  for (i96 = 0; i96 < ABSD_size_tmp; i96++) {
                    d_ABSD_data[i96] = ABSD_data[i100 + i96];
                  }

                  if (EC > TC) {
                    i96 = 0;
                    i97 = 0;
                    i99 = 0;
                    i100 = 0;
                    i101 = 0;
                  } else {
                    i96 = (int)EC - 1;
                    i97 = nm1d2;
                    i99 = (int)EC - 1;
                    i100 = (int)EC - 1;
                    i101 = nm1d2;
                  }

                  ABSD_size_tmp = i97 - i96;
                  e_ABSD_size[0] = ABSD_size_tmp;
                  for (i97 = 0; i97 < ABSD_size_tmp; i97++) {
                    b_ABSD_data[i97] = ABSD_data[i96 + i97] - f_right_data[i99 +
                      i97];
                  }

                  ABSD_size_tmp = i101 - i100;
                  f_ABSD_size[0] = ABSD_size_tmp;
                  for (i96 = 0; i96 < ABSD_size_tmp; i96++) {
                    f_left_data[i96] = ABSD_data[i100 + i96];
                  }

                  apnd = (1.0 - var(c_ABSD_data, c_ABSD_size) / var(d_ABSD_data,
                           d_ABSD_size)) - (1.0 - var(b_ABSD_data, e_ABSD_size) /
                    var(f_left_data, f_ABSD_size));
                  if ((apnd > 0.04) || ((DBorASMM > 2.0) && (i_ASMM > 3))) {
                    Coder_multi_amp(f_data, ABSD_data, ABSD_size, TC, &u1, &ndbl,
                                    b_EC);

                    /* EC_Double */
                    if (u1 < TC) {
                      ABSD_size_tmp = (int)u1;
                      g_ABSD_size[0] = ABSD_size_tmp;
                      if (0 <= ABSD_size_tmp - 1) {
                        memcpy(&e_ABSD_data[0], &ABSD_data[0], (unsigned int)
                               (ABSD_size_tmp * (int)sizeof(double)));
                      }

                      cdiff = *result_well;
                      b_SRFU[0] = SRFU;
                      b_SRFU[1] = ABSD_data[(int)u1 - 1];
                      b_SRFU[2] = Coder_find_cycle(e_ABSD_data, g_ABSD_size, MFC,
                        u1);
                      b_SRFU[3] = 0.2;
                      Coder_SigFit_par(x_data, x_size, ABSD_data, &cdiff, u1,
                                       b_SRFU, SFC, MFC - 2.0, perturbation_data,
                                       param_new_DB, f_new_DB_data,
                                       f_new_DB_size, &ndbl);
                      if ((cdiff == 0.0) && (f_new_DB_data[n] - f_new_DB_data[0]
                           > Max_DRFU_Thrd) && (Coder_invsig(param_new_DB, Thrd
                            + f_new_DB_data[0]) - Ct_diff_tmp > 0.5)) {
                        i_DB = 2;
                        if (apnd > 0.04) {
                          i_ASMM = 7;
                        }
                      } else {
                        i_DB = 4;
                      }
                    }
                  }
                }
              }
            }

            if ((i_ASMM == 6) && (DBorASMM < 2.0)) {
              i_DB = 4;
            }
          }

          /* RFU_EC>Thrd */
          if (DBorASMM <= 1.5) {
            exitg1 = true;
          } else {
            if (1 + i_RFU_EC == num_RFU_EC) {
              EC--;
            }

            i_RFU_EC++;
          }
        }

        /*  i_RFU_EC */
      }

      /* while */
      if ((i_ASMM > 5) && (i_DB == 2)) {
        param_new[0] = param_new_DB[0];
        param_new[1] = param_new_DB[1];
        param_new[2] = param_new_DB[2];
        param_new[3] = param_new_DB[3];
        f_new_size[0] = f_new_DB_size[0];
        if (0 <= f_new_DB_size[0] - 1) {
          memcpy(&f_new_data[0], &f_new_DB_data[0], (unsigned int)
                 (f_new_DB_size[0] * (int)sizeof(double)));
        }

        *result_well = -2.0;
        *DataProcessNum = -2.0;
        *sht2 = f_new_DB_data[0];

        /*              DataProcess(:,8)=f_new; */
      }

      if ((*result_well == 0.0) && (RFU_EC_save - SRFU > Thrd) && (EC_save > SFC))
      {
        i96 = (int)EC_save;
        i97 = i96 - 1;
        f_data[i97] = (f_new_data[(int)(EC_save - 1.0) - 1] + f_new2_data[(int)
                       (EC_save + 1.0) - 1]) / 2.0;
        if (1.0 > EC_save - 1.0) {
          i98 = 0;
        } else {
          i98 = (int)EC_save - 1;
        }

        nm1d2 = i98 - 1;
        if (0 <= nm1d2) {
          memcpy(&f_data[0], &f_new_data[0], (unsigned int)((nm1d2 + 1) * (int)
                  sizeof(double)));
        }

        if (EC_save + 1.0 > TC) {
          i99 = 1;
          i100 = 0;
          i101 = 1;
        } else {
          i99 = i96 + 1;
          i100 = (int)TC;
          i101 = (int)EC_save + 1;
        }

        nm1d2 = i100 - i99;
        for (i100 = 0; i100 <= nm1d2; i100++) {
          f_data[(i101 + i100) - 1] = f_new2_data[(i99 + i100) - 1];
        }

        *sht = f_data[0];
        if ((DBorASMM > 1.5) && (EC_save > 4.0) && (EC_save + 3.0 < TC) &&
            (f_data[i96 - 3] - f_data[0] > Thrd)) {
          f_temp[0] = e_mean(*(double (*)[5])&f_data[-5 + i96]);
          f_temp[1] = e_mean(*(double (*)[5])&f_data[-4 + i96]);
          for (i99 = 0; i99 < 5; i99++) {
            ndbl = EC_save + (-2.0 + (double)i99);
            f[i99] = f_data[(int)ndbl - 1];
            check_itv2[i99] = ndbl;
          }

          f_temp[2] = e_mean(f);
          f_temp[3] = e_mean(*(double (*)[5])&f_data[-2 + i96]);
          f_temp[4] = e_mean(*(double (*)[5])&f_data[i97]);
          for (i96 = 0; i96 < 5; i96++) {
            f_data[(int)check_itv2[i96] - 1] = f_temp[i96];
          }
        }

        /*              EndRFU=f(end)-f(1); */
        param[0] = param_new[0];
        param[1] = param_new[1];
        param[2] = param_new[2];
        param[3] = param_new[3];
        *DataProcessNum = -3.0;

        /*              DataProcess(:,8)=f; */
      }
    }

    /* if check_val>0.3 */
  }

  emxFree_real_T(&varargin_1);
  emxFree_real_T(&check_itv);

  /*  fprintf('%s\n', '########################################') */
  /*  fprintf('f_new(1)= %s\n', Double2String(f_new(1))) */
  /*  fprintf('ABSD=[ %s, ', Double2String(ABSD(1))) */
  /*  for i=2:44 */
  /*      fprintf('%s, ', Double2String(ABSD(i))) */
  /*  end */
  /*  fprintf('%s]\n ', Double2String(ABSD(45))) */
  /*  fprintf('f=[ %s, ', Double2String(f(1))) */
  /*  for i=2:44 */
  /*      fprintf('%s, ', Double2String(f(i))) */
  /*  end */
  /*  fprintf('%s]\n ', Double2String(f(45))) */
  /*  fprintf('%s\n ', Double2String(TC)) */
  if ((*DataProcessNum == 0.0) && ((SRFU - f_data[0]) / (f_data[f_size[0] - 1] -
        f_data[0]) > 0.02)) {
    Coder_multi_amp(f_data, ABSD_data, ABSD_size, TC, &u1, &ndbl, RFU_EC_array);

    /* EC_Double */
    /*      fprintf('EC_D= %s\n', Double2String(EC_D)) */
    ABSD_size_tmp = (int)u1;
    b_ABSD_size[0] = ABSD_size_tmp;
    if (0 <= ABSD_size_tmp - 1) {
      memcpy(&b_ABSD_data[0], &ABSD_data[0], (unsigned int)(ABSD_size_tmp * (int)
              sizeof(double)));
    }

    cdiff = *result_well;
    b_SRFU[0] = SRFU;
    b_SRFU[1] = ABSD_data[(int)u1 - 1];
    b_SRFU[2] = Coder_find_cycle(b_ABSD_data, b_ABSD_size, MFC, u1);
    b_SRFU[3] = 0.2;
    Coder_SigFit_par(x_data, x_size, ABSD_data, &cdiff, u1, b_SRFU, SFC, MFC -
                     2.0, perturbation_data, param_new, f_new_data, f_new_size,
                     &ndbl);
    if ((cdiff == 0.0) && (f_new_data[(int)TC - 1] - f_new_data[0] >
                           Max_DRFU_Thrd) && (Coder_invsig(param_new, Thrd +
          f_new_data[0]) - Coder_invsig(param, Thrd + *sht) > 0.5)) {
      i96 = (int)MFC - 1;
      if ((f_new_data[i96] - f_data[i96]) / (f_new_data[0] - f_data[0]) < 0.9) {
        *result_well = -2.0;
        *DataProcessNum = -2.0;
        *sht2 = f_new_data[0];

        /*              DataProcess(:,8)=f_new; */
      }
    }
  }
}

/* End of code generation (Coder_AsymmSigFit.c) */
