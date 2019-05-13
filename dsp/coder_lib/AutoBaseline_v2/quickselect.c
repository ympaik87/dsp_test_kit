/*
 * quickselect.c
 *
 * Code generation for function 'quickselect'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "quickselect.h"

/* Function Declarations */
static int thirdOfFive(const double v_data[], int ia, int ib);

/* Function Definitions */
static int thirdOfFive(const double v_data[], int ia, int ib)
{
  int im;
  double v4;
  double v5_tmp;
  int b_j1;
  int j2;
  int j3;
  int j4;
  int j5;
  double v5;
  if ((ia == ib) || (ia + 1 == ib)) {
    im = ia;
  } else if ((ia + 2 == ib) || (ia + 3 == ib)) {
    if (v_data[ia - 1] < v_data[ia]) {
      if (v_data[ia] < v_data[ia + 1]) {
        im = ia + 1;
      } else if (v_data[ia - 1] < v_data[ia + 1]) {
        im = ia + 2;
      } else {
        im = ia;
      }
    } else if (v_data[ia - 1] < v_data[ia + 1]) {
      im = ia;
    } else if (v_data[ia] < v_data[ia + 1]) {
      im = ia + 2;
    } else {
      im = ia + 1;
    }
  } else {
    v4 = v_data[ia - 1];
    if (v4 < v_data[ia]) {
      if (v_data[ia] < v_data[ia + 1]) {
        b_j1 = ia;
        j2 = ia;
        j3 = ia + 2;
      } else if (v4 < v_data[ia + 1]) {
        b_j1 = ia;
        j2 = ia + 1;
        j3 = ia + 1;
      } else {
        b_j1 = ia + 2;
        j2 = ia - 1;
        j3 = ia + 1;
      }
    } else {
      v5_tmp = v_data[ia + 1];
      if (v4 < v5_tmp) {
        b_j1 = ia + 1;
        j2 = ia - 1;
        j3 = ia + 2;
      } else if (v_data[ia] < v5_tmp) {
        b_j1 = ia + 1;
        j2 = ia + 1;
        j3 = ia;
      } else {
        b_j1 = ia + 2;
        j2 = ia;
        j3 = ia;
      }
    }

    j4 = ia;
    j5 = ia + 1;
    v4 = v_data[ia + 2];
    v5_tmp = v_data[ia + 3];
    v5 = v5_tmp;
    if (v5_tmp < v4) {
      j4 = ia + 1;
      j5 = ia;
      v5 = v4;
      v4 = v5_tmp;
    }

    if (v5 < v_data[b_j1 - 1]) {
      im = b_j1;
    } else if (v5 < v_data[j2]) {
      im = j5 + 3;
    } else if (v4 < v_data[j2]) {
      im = j2 + 1;
    } else if (v4 < v_data[j3 - 1]) {
      im = j4 + 3;
    } else {
      im = j3;
    }
  }

  return im;
}

void quickselect(double v_data[], int n, int vlen, double *vn, int *nfirst, int *
                 nlast)
{
  int ipiv;
  int ia;
  int ib;
  int ilast;
  int oldnv;
  boolean_T checkspeed;
  boolean_T isslow;
  boolean_T exitg1;
  double vref;
  int k;
  double vk_tmp;
  boolean_T guard1 = false;
  int c;
  int ngroupsof5;
  if (n > vlen) {
    *vn = rtNaN;
    *nfirst = 0;
    *nlast = 0;
  } else {
    ipiv = n - 1;
    ia = 0;
    ib = vlen - 1;
    *nfirst = 1;
    ilast = vlen - 1;
    oldnv = vlen;
    checkspeed = false;
    isslow = false;
    exitg1 = false;
    while ((!exitg1) && (ia + 1 < ib + 1)) {
      vref = v_data[ipiv];
      v_data[ipiv] = v_data[ib];
      v_data[ib] = vref;
      ilast = ia;
      ipiv = -1;
      for (k = ia + 1; k <= ib; k++) {
        vk_tmp = v_data[k - 1];
        if (vk_tmp == vref) {
          v_data[k - 1] = v_data[ilast];
          v_data[ilast] = vk_tmp;
          ipiv++;
          ilast++;
        } else {
          if (vk_tmp < vref) {
            v_data[k - 1] = v_data[ilast];
            v_data[ilast] = vk_tmp;
            ilast++;
          }
        }
      }

      v_data[ib] = v_data[ilast];
      v_data[ilast] = vref;
      guard1 = false;
      if (n <= ilast + 1) {
        *nfirst = ilast - ipiv;
        if (n >= *nfirst) {
          exitg1 = true;
        } else {
          ib = ilast - 1;
          guard1 = true;
        }
      } else {
        ia = ilast + 1;
        guard1 = true;
      }

      if (guard1) {
        c = (ib - ia) + 1;
        if (checkspeed) {
          isslow = (c > oldnv / 2);
          oldnv = c;
        }

        checkspeed = !checkspeed;
        if (isslow) {
          while (c > 1) {
            ngroupsof5 = c / 5;
            *nlast = c - ngroupsof5 * 5;
            c = ngroupsof5;
            for (k = 0; k < ngroupsof5; k++) {
              ipiv = (ia + k * 5) + 1;
              ipiv = thirdOfFive(v_data, ipiv, ipiv + 4) - 1;
              ilast = ia + k;
              vref = v_data[ilast];
              v_data[ilast] = v_data[ipiv];
              v_data[ipiv] = vref;
            }

            if (*nlast > 0) {
              ipiv = (ia + ngroupsof5 * 5) + 1;
              ipiv = thirdOfFive(v_data, ipiv, (ipiv + *nlast) - 1) - 1;
              ilast = ia + ngroupsof5;
              vref = v_data[ilast];
              v_data[ilast] = v_data[ipiv];
              v_data[ipiv] = vref;
              c = ngroupsof5 + 1;
            }
          }
        } else {
          if (c >= 3) {
            ipiv = ia + (c - 1) / 2;
            if (v_data[ia] < v_data[ipiv]) {
              if (v_data[ipiv] < v_data[ib]) {
              } else if (v_data[ia] < v_data[ib]) {
                ipiv = ib;
              } else {
                ipiv = ia;
              }
            } else if (v_data[ia] < v_data[ib]) {
              ipiv = ia;
            } else {
              if (v_data[ipiv] < v_data[ib]) {
                ipiv = ib;
              }
            }

            if (ipiv + 1 > ia + 1) {
              vref = v_data[ia];
              v_data[ia] = v_data[ipiv];
              v_data[ipiv] = vref;
            }
          }
        }

        ipiv = ia;
        *nfirst = ia + 1;
        ilast = ib;
      }
    }

    *vn = v_data[ilast];
    *nlast = ilast + 1;
  }
}

/* End of code generation (quickselect.c) */
