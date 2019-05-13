/*
 * vmedian.c
 *
 * Code generation for function 'vmedian'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "vmedian.h"
#include "quickselect.h"

/* Function Definitions */
double vmedian(double v_data[], int v_size[1], int n)
{
  double m;
  int k;
  int exitg1;
  int midm1;
  int ilast;
  double unusedU3_data[100];
  int unusedU5;
  boolean_T b0;
  boolean_T b1;
  double b;
  boolean_T b2;
  boolean_T b3;
  boolean_T b4;
  boolean_T b5;
  boolean_T b6;
  boolean_T b7;
  boolean_T b8;
  boolean_T b9;
  k = 0;
  do {
    exitg1 = 0;
    if (k <= n - 1) {
      if (rtIsNaN(v_data[k])) {
        m = rtNaN;
        exitg1 = 1;
      } else {
        k++;
      }
    } else {
      if (n <= 4) {
        if (n == 0) {
          m = rtNaN;
        } else if (n == 1) {
          m = v_data[0];
        } else if (n == 2) {
          if (rtIsInf(v_data[0]) || rtIsInf(v_data[1])) {
            m = (v_data[0] + v_data[1]) / 2.0;
          } else {
            m = v_data[0] + (v_data[1] - v_data[0]) / 2.0;
          }
        } else if (n == 3) {
          if (rtIsNaN(v_data[1])) {
            b1 = !rtIsNaN(v_data[0]);
          } else {
            b1 = ((!rtIsNaN(v_data[0])) && (v_data[0] < v_data[1]));
          }

          if (b1) {
            if (rtIsNaN(v_data[2])) {
              b5 = !rtIsNaN(v_data[1]);
            } else {
              b5 = ((!rtIsNaN(v_data[1])) && (v_data[1] < v_data[2]));
            }

            if (b5) {
              unusedU5 = 1;
            } else {
              if (rtIsNaN(v_data[2])) {
                b9 = !rtIsNaN(v_data[0]);
              } else {
                b9 = ((!rtIsNaN(v_data[0])) && (v_data[0] < v_data[2]));
              }

              if (b9) {
                unusedU5 = 2;
              } else {
                unusedU5 = 0;
              }
            }
          } else {
            if (rtIsNaN(v_data[2])) {
              b4 = !rtIsNaN(v_data[0]);
            } else {
              b4 = ((!rtIsNaN(v_data[0])) && (v_data[0] < v_data[2]));
            }

            if (b4) {
              unusedU5 = 0;
            } else {
              if (rtIsNaN(v_data[2])) {
                b8 = !rtIsNaN(v_data[1]);
              } else {
                b8 = ((!rtIsNaN(v_data[1])) && (v_data[1] < v_data[2]));
              }

              if (b8) {
                unusedU5 = 2;
              } else {
                unusedU5 = 1;
              }
            }
          }

          m = v_data[unusedU5];
        } else {
          if (rtIsNaN(v_data[1])) {
            b0 = !rtIsNaN(v_data[0]);
          } else {
            b0 = ((!rtIsNaN(v_data[0])) && (v_data[0] < v_data[1]));
          }

          if (b0) {
            if (rtIsNaN(v_data[2])) {
              b3 = !rtIsNaN(v_data[1]);
            } else {
              b3 = ((!rtIsNaN(v_data[1])) && (v_data[1] < v_data[2]));
            }

            if (b3) {
              k = 0;
              unusedU5 = 1;
              ilast = 2;
            } else {
              if (rtIsNaN(v_data[2])) {
                b7 = !rtIsNaN(v_data[0]);
              } else {
                b7 = ((!rtIsNaN(v_data[0])) && (v_data[0] < v_data[2]));
              }

              if (b7) {
                k = 0;
                unusedU5 = 2;
                ilast = 1;
              } else {
                k = 2;
                unusedU5 = 0;
                ilast = 1;
              }
            }
          } else {
            if (rtIsNaN(v_data[2])) {
              b2 = !rtIsNaN(v_data[0]);
            } else {
              b2 = ((!rtIsNaN(v_data[0])) && (v_data[0] < v_data[2]));
            }

            if (b2) {
              k = 1;
              unusedU5 = 0;
              ilast = 2;
            } else {
              if (rtIsNaN(v_data[2])) {
                b6 = !rtIsNaN(v_data[1]);
              } else {
                b6 = ((!rtIsNaN(v_data[1])) && (v_data[1] < v_data[2]));
              }

              if (b6) {
                k = 1;
                unusedU5 = 2;
                ilast = 0;
              } else {
                k = 2;
                unusedU5 = 1;
                ilast = 0;
              }
            }
          }

          if (v_data[k] < v_data[3]) {
            if (v_data[3] < v_data[ilast]) {
              if (rtIsInf(v_data[unusedU5]) || rtIsInf(v_data[3])) {
                m = (v_data[unusedU5] + v_data[3]) / 2.0;
              } else {
                m = v_data[unusedU5] + (v_data[3] - v_data[unusedU5]) / 2.0;
              }
            } else if (rtIsInf(v_data[unusedU5]) || rtIsInf(v_data[ilast])) {
              m = (v_data[unusedU5] + v_data[ilast]) / 2.0;
            } else {
              m = v_data[unusedU5] + (v_data[ilast] - v_data[unusedU5]) / 2.0;
            }
          } else if (rtIsInf(v_data[k]) || rtIsInf(v_data[unusedU5])) {
            m = (v_data[k] + v_data[unusedU5]) / 2.0;
          } else {
            m = v_data[k] + (v_data[unusedU5] - v_data[k]) / 2.0;
          }
        }
      } else {
        midm1 = n >> 1;
        if ((n & 1) == 0) {
          quickselect(v_data, midm1 + 1, n, &m, &k, &ilast);
          if (midm1 < k) {
            k = v_size[0];
            if (0 <= k - 1) {
              memcpy(&unusedU3_data[0], &v_data[0], (unsigned int)(k * (int)
                      sizeof(double)));
            }

            quickselect(unusedU3_data, midm1, ilast - 1, &b, &k, &unusedU5);
            if (rtIsInf(m) || rtIsInf(b)) {
              m = (m + b) / 2.0;
            } else {
              m += (b - m) / 2.0;
            }
          }
        } else {
          k = v_size[0];
          if (0 <= k - 1) {
            memcpy(&unusedU3_data[0], &v_data[0], (unsigned int)(k * (int)sizeof
                    (double)));
          }

          quickselect(unusedU3_data, midm1 + 1, n, &m, &k, &unusedU5);
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return m;
}

/* End of code generation (vmedian.c) */
