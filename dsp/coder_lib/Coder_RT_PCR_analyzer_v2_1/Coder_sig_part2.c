/*
 * Coder_sig_part2.c
 *
 * Code generation for function 'Coder_sig_part2'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_sig_part2.h"
#include "Coder_RT_PCR_analyzer_v2_1_emxutil.h"
#include "power.h"

/* Function Definitions */
void Coder_sig_part2(const double param[4], const double xval_data[], const int
                     xval_size[1], const double fixed_pt[2], double f_data[],
                     int f_size[1])
{
  emxArray_real_T *b_fixed_pt;
  double x;
  int i30;
  int loop_ub;
  emxInit_real_T(&b_fixed_pt, 1);
  x = (fixed_pt[1] - param[0]) * 2.0;
  i30 = b_fixed_pt->size[0];
  b_fixed_pt->size[0] = xval_size[0];
  emxEnsureCapacity_real_T(b_fixed_pt, i30);
  loop_ub = xval_size[0];
  for (i30 = 0; i30 < loop_ub; i30++) {
    b_fixed_pt->data[i30] = (fixed_pt[0] - xval_data[i30]) * param[3];
  }

  b_power(b_fixed_pt->data, b_fixed_pt->size, f_data, f_size);
  loop_ub = f_size[0];
  emxFree_real_T(&b_fixed_pt);
  for (i30 = 0; i30 < loop_ub; i30++) {
    f_data[i30] = param[0] + x / (1.0 + f_data[i30]);
  }

  /*  fprintf('%s\n', '#################### test1 : 10^0=0 ?? ######################'); */
  /*  fprintf('(fixed_pt(1)-xval)*param(4)=%s\n', Double2String((fixed_pt(1)-xval(1))*param(4))); */
  /*  fprintf('10.^((fixed_pt(1)-xval)*param(4))=%s\n', Double2String(10.^((fixed_pt(1)-xval(1))*param(4)))); */
  /*  fprintf('1+10.^((fixed_pt(1)-xval)*param(4))=%s\n', Double2String(1+10.^((fixed_pt(1)-xval(1))*param(4)))); */
  /*  fprintf('1/(1+10.^((fixed_pt(1)-xval)*param(4)))=%s\n', Double2String(1/(1+10.^((fixed_pt(1)-xval(1))*param(4))))); */
  /*  fprintf('2/(1+10.^((fixed_pt(1)-xval)*param(4)))=%s\n', Double2String( 2/(1+10.^((fixed_pt(1)-xval(1))*param(4))) )); */
  /*   */
  /*  fprintf('%s\n', '#################### test2 : 10^0=0 ?? ######################'); */
  /*  ah=((fixed_pt(1)-xval(1))*param(4)); */
  /*  fprintf('ah=%s\n', '(fixed_pt(1)-xval(1))*param(4)'); */
  /*  fprintf('ah=%s\n', Double2String(ah)); */
  /*  fprintf('2/(1+10^ah)=%s\n', Double2String( 2./(1+10^ah) )); */
  /*   */
  /*  fprintf('%s\n', '#################### test3 : 10^0=0 ?? ######################'); */
  /*  a=34; b=34; c=a-b; d=0.2; */
  /*  fprintf('10^0=%s\n', Double2String(10.^((a-b)*d))); */
  /*  fprintf('10^0=%s\n', Double2String(10.^(c*d))); */
  /*  fprintf('%s\n', 'Evaluations for fixed values seem to be calculated before converting to C code'); */
  /*   */
  /*  fprintf('%s\n', '#################### test4 : inf works well ?? ######################'); */
  /*  e=inf; */
  /*  for i=1:2 */
  /*      if e-4>100 */
  /*          fprintf('%s\n', 'Inf works well in the statement including if'); */
  /*          e=5; */
  /*      end */
  /*  end */
  /*   */
  /*  e2=inf; */
  /*  while e2-4>100 */
  /*      fprintf('%s\n', 'Inf works well in the statement including while'); */
  /*      e2=5; */
  /*  end */
  /*   */
  /*  for i=1:2 */
  /*      a=[-inf inf i*100 -i*100]; */
  /*      [~,maxindx]=max(a); */
  /*      [~,minindx]=min(a); */
  /*      if i==2 */
  /*          fprintf('Max index : %s\n', Double2String(maxindx)); */
  /*          fprintf('Min index : %s\n', Double2String(minindx)); */
  /*           */
  /*          if maxindx==2             */
  /*              fprintf('%s\n', 'Inf works well in the statement including max'); */
  /*          end */
  /*          if minindx==1 */
  /*              fprintf('%s\n', 'Inf works well in the statement including min'); */
  /*          end */
  /*      end */
  /*  end */
}

/* End of code generation (Coder_sig_part2.c) */
