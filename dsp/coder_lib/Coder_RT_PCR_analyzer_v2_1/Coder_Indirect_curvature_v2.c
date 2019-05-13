/*
 * Coder_Indirect_curvature_v2.c
 *
 * Code generation for function 'Coder_Indirect_curvature_v2'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_Indirect_curvature_v2.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "sum.h"

/* Function Definitions */
void Coder_Indirect_curvature_v2(const double RD_data[], double TC, double
  cuv_data[], int cuv_size[2])
{
  int cuv_size_tmp;
  int i24;
  emxArray_real_T *y;
  int i;
  int i25;
  double a;
  int a_size[1];
  emxArray_real_T a_data;
  double b_a_data[100];
  cuv_size[0] = 1;
  cuv_size_tmp = (int)TC;
  cuv_size[1] = cuv_size_tmp;
  if (0 <= cuv_size_tmp - 1) {
    memset(&cuv_data[0], 0, (unsigned int)(cuv_size_tmp * (int)sizeof(double)));
  }

  i24 = (int)((TC - 3.0) + -3.0);
  emxInit_real_T(&y, 2);
  for (i = 0; i < i24; i++) {
    /*      i */
    i25 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 7;
    emxEnsureCapacity_real_T(y, i25);
    for (i25 = 0; i25 < 7; i25++) {
      y->data[i25] = (i + 1U) + i25;
    }

    a = (RD_data[((i + i) - i) + 6] - RD_data[i]) / (((4.0 + (double)i) + 3.0) -
      ((4.0 + (double)i) - 3.0));

    /*      L-sub_RD */
    a_size[0] = y->size[1];
    cuv_size_tmp = y->size[1];
    for (i25 = 0; i25 < cuv_size_tmp; i25++) {
      b_a_data[i25] = (a * (y->data[i25] - ((4.0 + (double)i) - 3.0)) +
                       RD_data[i]) - RD_data[i + i25];
    }

    a_data.data = &b_a_data[0];
    a_data.size = &a_size[0];
    a_data.allocatedSize = 100;
    a_data.numDimensions = 1;
    a_data.canFreeData = false;
    cuv_data[i + 3] = sum(&a_data);
  }

  emxFree_real_T(&y);
}

/* End of code generation (Coder_Indirect_curvature_v2.c) */
