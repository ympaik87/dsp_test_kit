/*
 * Coder_analytical_inverse.c
 *
 * Code generation for function 'Coder_analytical_inverse'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "Coder_analytical_inverse.h"

/* Function Definitions */
void Coder_analytical_inverse(const double a[16], double inv_a[16])
{
  double det_tmp;
  double b_det_tmp;
  double c_det_tmp;
  double d_det_tmp;
  double e_det_tmp;
  double f_det_tmp;
  double g_det_tmp;
  double h_det_tmp;
  double i_det_tmp;
  double j_det_tmp;
  double k_det_tmp;
  double l_det_tmp;
  double m_det_tmp;
  double n_det_tmp;
  double o_det_tmp;
  double p_det_tmp;
  double q_det_tmp;
  double r_det_tmp;
  double s_det_tmp;
  double t_det_tmp;
  double u_det_tmp;
  double v_det_tmp;
  double w_det_tmp;
  double x_det_tmp;
  double y_det_tmp;
  double ab_det_tmp;
  double bb_det_tmp;
  double cb_det_tmp;
  double db_det_tmp;
  double eb_det_tmp;
  double fb_det_tmp;
  double gb_det_tmp;
  double hb_det_tmp;
  double ib_det_tmp;
  double jb_det_tmp;
  double kb_det_tmp;
  double det;
  double inv_a_tmp;
  double b_inv_a_tmp;
  double c_inv_a_tmp;
  double d_inv_a_tmp;
  double e_inv_a_tmp;
  double f_inv_a_tmp;
  double g_inv_a_tmp;
  double h_inv_a_tmp;
  double i_inv_a_tmp;
  double j_inv_a_tmp;
  double k_inv_a_tmp;
  double l_inv_a_tmp;
  int i22;

  /* http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html */
  memset(&inv_a[0], 0, sizeof(double) << 4);
  det_tmp = a[0] * a[5];
  b_det_tmp = a[0] * a[9];
  c_det_tmp = a[0] * a[13];
  d_det_tmp = a[4] * a[1];
  e_det_tmp = a[4] * a[9];
  f_det_tmp = a[4] * a[13];
  g_det_tmp = a[8] * a[1];
  h_det_tmp = a[8] * a[5];
  i_det_tmp = a[8] * a[13];
  j_det_tmp = a[12] * a[1];
  k_det_tmp = a[12] * a[5];
  l_det_tmp = a[12] * a[9];
  m_det_tmp = f_det_tmp * a[10];
  n_det_tmp = h_det_tmp * a[14];
  o_det_tmp = l_det_tmp * a[6];
  p_det_tmp = e_det_tmp * a[14];
  q_det_tmp = i_det_tmp * a[6];
  r_det_tmp = k_det_tmp * a[10];
  s_det_tmp = b_det_tmp * a[14];
  t_det_tmp = i_det_tmp * a[2];
  u_det_tmp = j_det_tmp * a[10];
  v_det_tmp = c_det_tmp * a[10];
  w_det_tmp = g_det_tmp * a[14];
  x_det_tmp = l_det_tmp * a[2];
  y_det_tmp = c_det_tmp * a[6];
  ab_det_tmp = d_det_tmp * a[14];
  bb_det_tmp = k_det_tmp * a[2];
  cb_det_tmp = det_tmp * a[14];
  db_det_tmp = f_det_tmp * a[2];
  eb_det_tmp = j_det_tmp * a[6];
  fb_det_tmp = det_tmp * a[10];
  gb_det_tmp = e_det_tmp * a[2];
  hb_det_tmp = g_det_tmp * a[6];
  ib_det_tmp = b_det_tmp * a[6];
  jb_det_tmp = d_det_tmp * a[10];
  kb_det_tmp = h_det_tmp * a[2];
  det = ((((((((((((((((((((((fb_det_tmp * a[15] + s_det_tmp * a[7]) + y_det_tmp
    * a[11]) + ab_det_tmp * a[11]) + gb_det_tmp * a[15]) + m_det_tmp * a[3]) +
    hb_det_tmp * a[15]) + n_det_tmp * a[3]) + t_det_tmp * a[7]) + u_det_tmp * a
                      [7]) + bb_det_tmp * a[11]) + o_det_tmp * a[3]) -
                   cb_det_tmp * a[11]) - ib_det_tmp * a[15]) - v_det_tmp * a[7])
                - jb_det_tmp * a[15]) - p_det_tmp * a[3]) - db_det_tmp * a[11])
             - w_det_tmp * a[7]) - kb_det_tmp * a[15]) - q_det_tmp * a[3]) -
          eb_det_tmp * a[11]) - r_det_tmp * a[3]) - x_det_tmp * a[7];
  if (det != 0.0) {
    inv_a_tmp = a[13] * a[10];
    b_inv_a_tmp = a[9] * a[14];
    c_inv_a_tmp = a[5] * a[14];
    d_inv_a_tmp = a[13] * a[6];
    e_inv_a_tmp = a[9] * a[6];
    f_inv_a_tmp = a[5] * a[10];
    inv_a[0] = ((((f_inv_a_tmp * a[15] + b_inv_a_tmp * a[7]) + d_inv_a_tmp * a
                  [11]) - c_inv_a_tmp * a[11]) - e_inv_a_tmp * a[15]) -
      inv_a_tmp * a[7];
    g_inv_a_tmp = a[8] * a[14];
    h_inv_a_tmp = a[12] * a[10];
    i_inv_a_tmp = a[12] * a[6];
    j_inv_a_tmp = a[4] * a[14];
    k_inv_a_tmp = a[4] * a[10];
    l_inv_a_tmp = a[8] * a[6];
    inv_a[4] = ((((j_inv_a_tmp * a[11] + l_inv_a_tmp * a[15]) + h_inv_a_tmp * a
                  [7]) - k_inv_a_tmp * a[15]) - g_inv_a_tmp * a[7]) -
      i_inv_a_tmp * a[11];
    inv_a[8] = ((((e_det_tmp * a[15] + i_det_tmp * a[7]) + k_det_tmp * a[11]) -
                 f_det_tmp * a[11]) - h_det_tmp * a[15]) - l_det_tmp * a[7];
    inv_a[12] = ((((m_det_tmp + n_det_tmp) + o_det_tmp) - p_det_tmp) - q_det_tmp)
      - r_det_tmp;
    m_det_tmp = a[13] * a[2];
    n_det_tmp = a[1] * a[14];
    o_det_tmp = a[1] * a[10];
    p_det_tmp = a[9] * a[2];
    inv_a[1] = ((((n_det_tmp * a[11] + p_det_tmp * a[15]) + inv_a_tmp * a[3]) -
                 o_det_tmp * a[15]) - b_inv_a_tmp * a[3]) - m_det_tmp * a[11];
    inv_a_tmp = a[0] * a[14];
    b_inv_a_tmp = a[12] * a[2];
    q_det_tmp = a[8] * a[2];
    r_det_tmp = a[0] * a[10];
    inv_a[5] = ((((r_det_tmp * a[15] + g_inv_a_tmp * a[3]) + b_inv_a_tmp * a[11])
                 - inv_a_tmp * a[11]) - q_det_tmp * a[15]) - h_inv_a_tmp * a[3];
    inv_a[9] = ((((c_det_tmp * a[11] + g_det_tmp * a[15]) + l_det_tmp * a[3]) -
                 b_det_tmp * a[15]) - i_det_tmp * a[3]) - j_det_tmp * a[11];
    inv_a[13] = ((((s_det_tmp + t_det_tmp) + u_det_tmp) - v_det_tmp) - w_det_tmp)
      - x_det_tmp;
    g_inv_a_tmp = a[5] * a[2];
    h_inv_a_tmp = a[1] * a[6];
    inv_a[2] = ((((h_inv_a_tmp * a[15] + c_inv_a_tmp * a[3]) + m_det_tmp * a[7])
                 - n_det_tmp * a[7]) - g_inv_a_tmp * a[15]) - d_inv_a_tmp * a[3];
    c_inv_a_tmp = a[0] * a[6];
    d_inv_a_tmp = a[4] * a[2];
    inv_a[6] = ((((inv_a_tmp * a[7] + d_inv_a_tmp * a[15]) + i_inv_a_tmp * a[3])
                 - c_inv_a_tmp * a[15]) - j_inv_a_tmp * a[3]) - b_inv_a_tmp * a
      [7];
    inv_a[10] = ((((det_tmp * a[15] + f_det_tmp * a[3]) + j_det_tmp * a[7]) -
                  c_det_tmp * a[7]) - d_det_tmp * a[15]) - k_det_tmp * a[3];
    inv_a[14] = ((((y_det_tmp + ab_det_tmp) + bb_det_tmp) - cb_det_tmp) -
                 db_det_tmp) - eb_det_tmp;
    inv_a[3] = ((((o_det_tmp * a[7] + g_inv_a_tmp * a[11]) + e_inv_a_tmp * a[3])
                 - h_inv_a_tmp * a[11]) - f_inv_a_tmp * a[3]) - p_det_tmp * a[7];
    inv_a[7] = ((((c_inv_a_tmp * a[11] + k_inv_a_tmp * a[3]) + q_det_tmp * a[7])
                 - r_det_tmp * a[7]) - d_inv_a_tmp * a[11]) - l_inv_a_tmp * a[3];
    inv_a[11] = ((((b_det_tmp * a[7] + d_det_tmp * a[11]) + h_det_tmp * a[3]) -
                  det_tmp * a[11]) - e_det_tmp * a[3]) - g_det_tmp * a[7];
    inv_a[15] = ((((fb_det_tmp + gb_det_tmp) + hb_det_tmp) - ib_det_tmp) -
                 jb_det_tmp) - kb_det_tmp;
    for (i22 = 0; i22 < 16; i22++) {
      inv_a[i22] /= det;
    }
  }
}

void b_Coder_analytical_inverse(const double a[4], double inv_a[4])
{
  double det;

  /* http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html */
  inv_a[0] = 0.0;
  inv_a[1] = 0.0;
  inv_a[2] = 0.0;
  inv_a[3] = 0.0;
  det = a[0] * a[3] - a[2] * a[1];
  if (det != 0.0) {
    inv_a[0] = a[3] / det;
    inv_a[1] = -a[1] / det;
    inv_a[2] = -a[2] / det;
    inv_a[3] = a[0] / det;
  }
}

void c_Coder_analytical_inverse(const double a[9], double inv_a[9])
{
  double det_tmp;
  double b_det_tmp;
  double c_det_tmp;
  double det;
  int i35;

  /* http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html */
  memset(&inv_a[0], 0, 9U * sizeof(double));
  det_tmp = a[1] * a[5];
  b_det_tmp = a[0] * a[5];
  c_det_tmp = a[0] * a[4];
  det = ((((c_det_tmp * a[8] + det_tmp * a[6]) + a[2] * a[3] * a[7]) - b_det_tmp
          * a[7]) - a[2] * a[4] * a[6]) - a[1] * a[3] * a[8];
  if (det != 0.0) {
    inv_a[0] = a[4] * a[8] - a[7] * a[5];
    inv_a[3] = a[6] * a[5] - a[3] * a[8];
    inv_a[6] = a[3] * a[7] - a[6] * a[4];
    inv_a[1] = a[7] * a[2] - a[1] * a[8];
    inv_a[4] = a[0] * a[8] - a[6] * a[2];
    inv_a[7] = a[6] * a[1] - a[0] * a[7];
    inv_a[2] = det_tmp - a[4] * a[2];
    inv_a[5] = a[3] * a[2] - b_det_tmp;
    inv_a[8] = c_det_tmp - a[3] * a[1];
    for (i35 = 0; i35 < 9; i35++) {
      inv_a[i35] /= det;
    }
  }
}

/* End of code generation (Coder_analytical_inverse.c) */
