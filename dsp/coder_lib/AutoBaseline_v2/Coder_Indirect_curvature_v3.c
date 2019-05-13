/*
 * Coder_Indirect_curvature_v3.c
 *
 * Code generation for function 'Coder_Indirect_curvature_v3'
 *
 */

/* Include files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "AutoBaseline_v2.h"
#include "Coder_Indirect_curvature_v3.h"
#include "AutoBaseline_v2_emxutil.h"
#include "sum.h"

/* Function Definitions */
void Coder_Indirect_curvature_v3(const double RD_data[], double TC, double
  cuv_data[], int cuv_size[2])
{
  int cuv_size_tmp;
  int i17;
  emxArray_real_T *y;
  emxArray_real_T *b_y;
  emxArray_real_T *c_y;
  int i;
  double a;
  double b;
  double c;
  int i18;
  double x;
  int a_size[1];
  emxArray_real_T a_data;
  double b_a_data[53];
  cuv_size[0] = 1;
  cuv_size_tmp = (int)TC;
  cuv_size[1] = cuv_size_tmp;
  if (0 <= cuv_size_tmp - 1) {
    memset(&cuv_data[0], 0, (unsigned int)(cuv_size_tmp * (int)sizeof(double)));
  }

  i17 = (int)((TC - 4.0) + -4.0);
  emxInit_real_T(&y, 2);
  emxInit_real_T(&b_y, 2);
  emxInit_real_T(&c_y, 1);
  for (i = 0; i < i17; i++) {
    /*       i */
    /*  ax+by+c=0 */
    a = RD_data[((i + i) - i) + 8] - RD_data[i];
    b = ((5.0 + (double)i) - 4.0) - ((5.0 + (double)i) + 4.0);
    c = -b * RD_data[i] - ((5.0 + (double)i) - 4.0) * a;

    /*  distance between point and line. */
    i18 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 9;
    emxEnsureCapacity_real_T(y, i18);
    for (i18 = 0; i18 < 9; i18++) {
      y->data[i18] = (i + 1U) + i18;
    }

    i18 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = 9;
    emxEnsureCapacity_real_T(b_y, i18);
    for (i18 = 0; i18 < 9; i18++) {
      b_y->data[i18] = (i + 1U) + i18;
    }

    x = sqrt(a * a + b * b);
    i18 = c_y->size[0];
    c_y->size[0] = y->size[1];
    emxEnsureCapacity_real_T(c_y, i18);
    cuv_size_tmp = y->size[1];
    for (i18 = 0; i18 < cuv_size_tmp; i18++) {
      c_y->data[i18] = y->data[i18];
    }

    a_size[0] = c_y->size[0];
    cuv_size_tmp = c_y->size[0];
    for (i18 = 0; i18 < cuv_size_tmp; i18++) {
      b_a_data[i18] = ((a * b_y->data[i18] + b * RD_data[i + i18]) + c) / x;
    }

    a_data.data = &b_a_data[0];
    a_data.size = &a_size[0];
    a_data.allocatedSize = 53;
    a_data.numDimensions = 1;
    a_data.canFreeData = false;
    cuv_data[i + 4] = sum(&a_data);
  }

  emxFree_real_T(&c_y);
  emxFree_real_T(&b_y);
  emxFree_real_T(&y);
}

/* End of code generation (Coder_Indirect_curvature_v3.c) */
