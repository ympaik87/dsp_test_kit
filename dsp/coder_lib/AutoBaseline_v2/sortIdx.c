/*
 * sortIdx.c
 *
 * Code generation for function 'sortIdx'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "sortIdx.h"
#include "AutoBaseline_v2_emxutil.h"

/* Function Declarations */
static void merge(emxArray_int32_T *idx, emxArray_real_T *x, int offset, int np,
                  int nq, emxArray_int32_T *iwork, emxArray_real_T *xwork);
static void merge_block(emxArray_int32_T *idx, emxArray_real_T *x, int offset,
  int n, int preSortLevel, emxArray_int32_T *iwork, emxArray_real_T *xwork);

/* Function Definitions */
static void merge(emxArray_int32_T *idx, emxArray_real_T *x, int offset, int np,
                  int nq, emxArray_int32_T *iwork, emxArray_real_T *xwork)
{
  int n_tmp;
  int iout;
  int p;
  int i35;
  int q;
  int exitg1;
  if (nq != 0) {
    n_tmp = np + nq;
    for (iout = 0; iout < n_tmp; iout++) {
      i35 = offset + iout;
      iwork->data[iout] = idx->data[i35];
      xwork->data[iout] = x->data[i35];
    }

    p = 0;
    q = np;
    iout = offset - 1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork->data[p] <= xwork->data[q]) {
        idx->data[iout] = iwork->data[p];
        x->data[iout] = xwork->data[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx->data[iout] = iwork->data[q];
        x->data[iout] = xwork->data[q];
        if (q + 1 < n_tmp) {
          q++;
        } else {
          q = iout - p;
          for (iout = p + 1; iout <= np; iout++) {
            i35 = q + iout;
            idx->data[i35] = iwork->data[iout - 1];
            x->data[i35] = xwork->data[iout - 1];
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

static void merge_block(emxArray_int32_T *idx, emxArray_real_T *x, int offset,
  int n, int preSortLevel, emxArray_int32_T *iwork, emxArray_real_T *xwork)
{
  int nPairs;
  int bLen;
  int tailOffset;
  int nTail;
  nPairs = n >> preSortLevel;
  bLen = 1 << preSortLevel;
  while (nPairs > 1) {
    if ((nPairs & 1) != 0) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        merge(idx, x, offset + tailOffset, bLen, nTail - bLen, iwork, xwork);
      }
    }

    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (nTail = 0; nTail < nPairs; nTail++) {
      merge(idx, x, offset + nTail * tailOffset, bLen, bLen, iwork, xwork);
    }

    bLen = tailOffset;
  }

  if (n > bLen) {
    merge(idx, x, offset, bLen, n - bLen, iwork, xwork);
  }
}

void sortIdx(emxArray_real_T *x, emxArray_int32_T *idx)
{
  int i1;
  int i34;
  int n;
  int b_n;
  double x4[4];
  int idx4[4];
  emxArray_int32_T *iwork;
  emxArray_real_T *xwork;
  int nNaNs;
  int ib;
  int k;
  signed char perm[4];
  int quartetOffset;
  int i3;
  int nNonNaN;
  int i4;
  int nBlocks;
  double d4;
  double d5;
  int bLen2;
  int nPairs;
  int b_iwork[256];
  double b_xwork[256];
  int exitg1;
  i1 = x->size[0];
  i34 = idx->size[0];
  idx->size[0] = i1;
  emxEnsureCapacity_int32_T(idx, i34);
  for (i34 = 0; i34 < i1; i34++) {
    idx->data[i34] = 0;
  }

  if (x->size[0] != 0) {
    n = x->size[0];
    b_n = x->size[0];
    x4[0] = 0.0;
    idx4[0] = 0;
    x4[1] = 0.0;
    idx4[1] = 0;
    x4[2] = 0.0;
    idx4[2] = 0;
    x4[3] = 0.0;
    idx4[3] = 0;
    emxInit_int32_T(&iwork, 1);
    i34 = iwork->size[0];
    iwork->size[0] = i1;
    emxEnsureCapacity_int32_T(iwork, i34);
    for (i34 = 0; i34 < i1; i34++) {
      iwork->data[i34] = 0;
    }

    emxInit_real_T(&xwork, 1);
    i1 = x->size[0];
    i34 = xwork->size[0];
    xwork->size[0] = i1;
    emxEnsureCapacity_real_T(xwork, i34);
    for (i34 = 0; i34 < i1; i34++) {
      xwork->data[i34] = 0.0;
    }

    nNaNs = 0;
    ib = -1;
    for (k = 0; k < b_n; k++) {
      if (rtIsNaN(x->data[k])) {
        i34 = (b_n - nNaNs) - 1;
        idx->data[i34] = k + 1;
        xwork->data[i34] = x->data[k];
        nNaNs++;
      } else {
        ib++;
        idx4[ib] = k + 1;
        x4[ib] = x->data[k];
        if (ib + 1 == 4) {
          quartetOffset = k - nNaNs;
          if (x4[0] <= x4[1]) {
            i1 = 1;
            ib = 2;
          } else {
            i1 = 2;
            ib = 1;
          }

          if (x4[2] <= x4[3]) {
            i3 = 3;
            i4 = 4;
          } else {
            i3 = 4;
            i4 = 3;
          }

          d4 = x4[i1 - 1];
          d5 = x4[i3 - 1];
          if (d4 <= d5) {
            if (x4[ib - 1] <= d5) {
              perm[0] = (signed char)i1;
              perm[1] = (signed char)ib;
              perm[2] = (signed char)i3;
              perm[3] = (signed char)i4;
            } else if (x4[ib - 1] <= x4[i4 - 1]) {
              perm[0] = (signed char)i1;
              perm[1] = (signed char)i3;
              perm[2] = (signed char)ib;
              perm[3] = (signed char)i4;
            } else {
              perm[0] = (signed char)i1;
              perm[1] = (signed char)i3;
              perm[2] = (signed char)i4;
              perm[3] = (signed char)ib;
            }
          } else {
            d5 = x4[i4 - 1];
            if (d4 <= d5) {
              if (x4[ib - 1] <= d5) {
                perm[0] = (signed char)i3;
                perm[1] = (signed char)i1;
                perm[2] = (signed char)ib;
                perm[3] = (signed char)i4;
              } else {
                perm[0] = (signed char)i3;
                perm[1] = (signed char)i1;
                perm[2] = (signed char)i4;
                perm[3] = (signed char)ib;
              }
            } else {
              perm[0] = (signed char)i3;
              perm[1] = (signed char)i4;
              perm[2] = (signed char)i1;
              perm[3] = (signed char)ib;
            }
          }

          i34 = perm[0] - 1;
          idx->data[quartetOffset - 3] = idx4[i34];
          i4 = perm[1] - 1;
          idx->data[quartetOffset - 2] = idx4[i4];
          i1 = perm[2] - 1;
          idx->data[quartetOffset - 1] = idx4[i1];
          ib = perm[3] - 1;
          idx->data[quartetOffset] = idx4[ib];
          x->data[quartetOffset - 3] = x4[i34];
          x->data[quartetOffset - 2] = x4[i4];
          x->data[quartetOffset - 1] = x4[i1];
          x->data[quartetOffset] = x4[ib];
          ib = -1;
        }
      }
    }

    i34 = (b_n - nNaNs) - 1;
    if (ib + 1 > 0) {
      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (ib + 1 == 1) {
        perm[0] = 1;
      } else if (ib + 1 == 2) {
        if (x4[0] <= x4[1]) {
          perm[0] = 1;
          perm[1] = 2;
        } else {
          perm[0] = 2;
          perm[1] = 1;
        }
      } else if (x4[0] <= x4[1]) {
        if (x4[1] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 2;
          perm[2] = 3;
        } else if (x4[0] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 3;
          perm[2] = 2;
        } else {
          perm[0] = 3;
          perm[1] = 1;
          perm[2] = 2;
        }
      } else if (x4[0] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 1;
        perm[2] = 3;
      } else if (x4[1] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 3;
        perm[2] = 1;
      } else {
        perm[0] = 3;
        perm[1] = 2;
        perm[2] = 1;
      }

      for (k = 0; k <= ib; k++) {
        i4 = perm[k] - 1;
        i1 = (i34 - ib) + k;
        idx->data[i1] = idx4[i4];
        x->data[i1] = x4[i4];
      }
    }

    ib = (nNaNs >> 1) + 1;
    for (k = 0; k <= ib - 2; k++) {
      i1 = (i34 + k) + 1;
      i3 = idx->data[i1];
      i4 = (b_n - k) - 1;
      idx->data[i1] = idx->data[i4];
      idx->data[i4] = i3;
      x->data[i1] = xwork->data[i4];
      x->data[i4] = xwork->data[i1];
    }

    if ((nNaNs & 1) != 0) {
      i34 += ib;
      x->data[i34] = xwork->data[i34];
    }

    nNonNaN = n - nNaNs;
    i1 = 2;
    if (nNonNaN > 1) {
      if (n >= 256) {
        nBlocks = nNonNaN >> 8;
        if (nBlocks > 0) {
          for (quartetOffset = 0; quartetOffset < nBlocks; quartetOffset++) {
            nNaNs = (quartetOffset << 8) - 1;
            for (b_n = 0; b_n < 6; b_n++) {
              n = 1 << (b_n + 2);
              bLen2 = n << 1;
              nPairs = 256 >> (b_n + 3);
              for (k = 0; k < nPairs; k++) {
                i3 = (nNaNs + k * bLen2) + 1;
                for (i1 = 0; i1 < bLen2; i1++) {
                  ib = i3 + i1;
                  b_iwork[i1] = idx->data[ib];
                  b_xwork[i1] = x->data[ib];
                }

                i4 = 0;
                i1 = n;
                ib = i3 - 1;
                do {
                  exitg1 = 0;
                  ib++;
                  if (b_xwork[i4] <= b_xwork[i1]) {
                    idx->data[ib] = b_iwork[i4];
                    x->data[ib] = b_xwork[i4];
                    if (i4 + 1 < n) {
                      i4++;
                    } else {
                      exitg1 = 1;
                    }
                  } else {
                    idx->data[ib] = b_iwork[i1];
                    x->data[ib] = b_xwork[i1];
                    if (i1 + 1 < bLen2) {
                      i1++;
                    } else {
                      ib -= i4;
                      for (i1 = i4 + 1; i1 <= n; i1++) {
                        i34 = ib + i1;
                        idx->data[i34] = b_iwork[i1 - 1];
                        x->data[i34] = b_xwork[i1 - 1];
                      }

                      exitg1 = 1;
                    }
                  }
                } while (exitg1 == 0);
              }
            }
          }

          i1 = nBlocks << 8;
          ib = nNonNaN - i1;
          if (ib > 0) {
            merge_block(idx, x, i1, ib, 2, iwork, xwork);
          }

          i1 = 8;
        }
      }

      merge_block(idx, x, 0, nNonNaN, i1, iwork, xwork);
    }

    emxFree_real_T(&xwork);
    emxFree_int32_T(&iwork);
  }
}

/* End of code generation (sortIdx.c) */
