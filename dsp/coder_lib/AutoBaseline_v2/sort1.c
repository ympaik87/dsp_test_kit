/*
 * sort1.c
 *
 * Code generation for function 'sort1'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "sort1.h"
#include "AutoBaseline_v2_emxutil.h"
#include "sortIdx.h"

/* Function Definitions */
void sort(emxArray_real_T *x, emxArray_int32_T *idx)
{
  int dim;
  int i33;
  emxArray_real_T *vwork;
  int vlen;
  int x_idx_0;
  int vstride;
  int k;
  emxArray_int32_T *iidx;
  dim = 0;
  if (x->size[0] != 1) {
    dim = -1;
  }

  if (dim + 2 <= 1) {
    i33 = x->size[0];
  } else {
    i33 = 1;
  }

  emxInit_real_T(&vwork, 1);
  vlen = i33 - 1;
  x_idx_0 = vwork->size[0];
  vwork->size[0] = i33;
  emxEnsureCapacity_real_T(vwork, x_idx_0);
  x_idx_0 = x->size[0];
  i33 = idx->size[0];
  idx->size[0] = x_idx_0;
  emxEnsureCapacity_int32_T(idx, i33);
  vstride = 1;
  for (k = 0; k <= dim; k++) {
    vstride *= x->size[0];
  }

  emxInit_int32_T(&iidx, 1);
  for (x_idx_0 = 0; x_idx_0 < vstride; x_idx_0++) {
    for (k = 0; k <= vlen; k++) {
      vwork->data[k] = x->data[x_idx_0 + k * vstride];
    }

    sortIdx(vwork, iidx);
    for (k = 0; k <= vlen; k++) {
      i33 = x_idx_0 + k * vstride;
      x->data[i33] = vwork->data[k];
      idx->data[i33] = iidx->data[k];
    }
  }

  emxFree_int32_T(&iidx);
  emxFree_real_T(&vwork);
}

/* End of code generation (sort1.c) */
