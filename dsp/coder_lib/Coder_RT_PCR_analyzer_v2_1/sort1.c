/*
 * sort1.c
 *
 * Code generation for function 'sort1'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "sort1.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "sortIdx.h"

/* Function Definitions */
void sort(emxArray_real_T *x, emxArray_int32_T *idx)
{
  int dim;
  int i45;
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
    i45 = x->size[0];
  } else {
    i45 = 1;
  }

  emxInit_real_T(&vwork, 1);
  vlen = i45 - 1;
  x_idx_0 = vwork->size[0];
  vwork->size[0] = i45;
  emxEnsureCapacity_real_T(vwork, x_idx_0);
  x_idx_0 = x->size[0];
  i45 = idx->size[0];
  idx->size[0] = x_idx_0;
  emxEnsureCapacity_int32_T(idx, i45);
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
      i45 = x_idx_0 + k * vstride;
      x->data[i45] = vwork->data[k];
      idx->data[i45] = iidx->data[k];
    }
  }

  emxFree_int32_T(&iidx);
  emxFree_real_T(&vwork);
}

/* End of code generation (sort1.c) */
