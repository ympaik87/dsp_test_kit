/*
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include files */
#include "rt_nonfinite.h"
#include "Coder_RT_PCR_analyzer_v2_1.h"
#include "main.h"
#include "Coder_RT_PCR_analyzer_v2_1_terminate.h"
#include "Coder_RT_PCR_analyzer_v2_1_initialize.h"

/* Function Declarations */
static void argInit_d100x1_real_T(double result_data[], int result_size[1]);
static double argInit_real_T(void);
static void main_Coder_RT_PCR_analyzer_v2_1(void);

/* Function Definitions */
static void argInit_d100x1_real_T(double result_data[], int result_size[1])
{
  int idx0;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result_size[0] = 2;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 2; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result_data[idx0] = argInit_real_T();
  }
}

static double argInit_real_T(void)
{
  return 0.0;
}

static void main_Coder_RT_PCR_analyzer_v2_1(void)
{
  double x_data[100];
  int x_size[1];
  double RD_data[100];
  int RD_size[1];
  double perturbation_data[100];
  int perturbation_size[1];
  double SFC_tmp;
  double DRFU;
  double Thrd;
  double RPC;
  double RC;
  double dfM;
  double dfC;
  double PMC;
  double FB;
  double AR;
  double isPC;
  double ver_array_data[20];
  int ver_array_size[1];
  double result_well;
  double DataProcessNum;
  double DataProcess_data[800];
  int DataProcess_size[2];
  double LSR_val;
  double RD_diff_data[100];
  int RD_diff_size[1];
  double ivd_cdd_ouput_data[100];
  int ivd_cdd_ouput_size[2];
  double cff[2];
  double scd_fit_data[100];
  int scd_fit_size[1];
  double R_p2;
  double EFC;
  double ABSD_orig_data[100];
  int ABSD_orig_size[1];
  double ABSD_data[100];
  int ABSD_size[1];
  double f_data[100];
  int f_size[1];
  double f_new_data[100];
  int f_new_size[1];
  double sht;
  double sht2;
  double param[4];
  double param_new[4];
  double R2;
  double EndRFU;
  double df;

  /* Initialize function 'Coder_RT_PCR_analyzer_v2_1' input arguments. */
  /* Initialize function input argument 'x'. */
  argInit_d100x1_real_T(x_data, x_size);

  /* Initialize function input argument 'RD'. */
  argInit_d100x1_real_T(RD_data, RD_size);

  /* Initialize function input argument 'perturbation'. */
  argInit_d100x1_real_T(perturbation_data, perturbation_size);
  SFC_tmp = argInit_real_T();
  DRFU = argInit_real_T();
  Thrd = argInit_real_T();
  RPC = argInit_real_T();
  RC = argInit_real_T();
  dfM = argInit_real_T();
  dfC = argInit_real_T();
  PMC = argInit_real_T();
  FB = argInit_real_T();
  AR = argInit_real_T();
  isPC = argInit_real_T();

  /* Initialize function input argument 'ver_array'. */
  argInit_d100x1_real_T(ver_array_data, ver_array_size);

  /* Call the entry-point 'Coder_RT_PCR_analyzer_v2_1'. */
  Coder_RT_PCR_analyzer_v2_1(x_data, x_size, RD_data, RD_size, perturbation_data,
    perturbation_size, SFC_tmp, SFC_tmp, DRFU, Thrd, RPC, RC, dfM, dfC, PMC, FB,
    AR, isPC, ver_array_data, ver_array_size, argInit_real_T(), &result_well,
    &DataProcessNum, DataProcess_data, DataProcess_size, &LSR_val, RD_diff_data,
    RD_diff_size, ivd_cdd_ouput_data, ivd_cdd_ouput_size, cff, scd_fit_data,
    scd_fit_size, &R_p2, &EFC, ABSD_orig_data, ABSD_orig_size, ABSD_data,
    ABSD_size, f_data, f_size, f_new_data, f_new_size, &sht, &sht2, param,
    param_new, &R2, &EndRFU, &df);
}

int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  Coder_RT_PCR_analyzer_v2_1_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_Coder_RT_PCR_analyzer_v2_1();

  /* Terminate the application.
     You do not need to do this more than one time. */
  Coder_RT_PCR_analyzer_v2_1_terminate();
  return 0;
}

/* End of code generation (main.c) */
