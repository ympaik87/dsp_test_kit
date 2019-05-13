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
#include "SigFit.h"
#include "main.h"
#include "SigFit_terminate.h"
#include "SigFit_initialize.h"

/* Function Declarations */
static void argInit_1x4_real_T(double result[4]);
static void argInit_45x1_real_T(double result[45]);
static void argInit_60x1_real_T(double result[60]);
static double argInit_real_T(void);
static void main_SigFit(void);

/* Function Definitions */
static void argInit_1x4_real_T(double result[4])
{
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 4; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx1] = argInit_real_T();
  }
}

static void argInit_45x1_real_T(double result[45])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 45; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

static void argInit_60x1_real_T(double result[60])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 60; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

static double argInit_real_T(void)
{
  return 0.0;
}

static void main_SigFit(void)
{
  double x[45];
  double ABSD[45];
  double result;
  double ini_param[4];
  double dv1[60];
  double SC;
  double param_data[16];
  int param_size[2];
  double f[45];

  /* Initialize function 'SigFit' input arguments. */
  /* Initialize function input argument 'x'. */
  argInit_45x1_real_T(x);

  /* Initialize function input argument 'ABSD'. */
  argInit_45x1_real_T(ABSD);
  result = argInit_real_T();

  /* Initialize function input argument 'ini_param'. */
  argInit_1x4_real_T(ini_param);

  /* Initialize function input argument 'perturbation'. */
  /* Call the entry-point 'SigFit'. */
  argInit_60x1_real_T(dv1);
  SC = argInit_real_T();
  SigFit(x, ABSD, &result, ini_param, &SC, argInit_real_T(), argInit_real_T(),
         argInit_real_T(), dv1, param_data, param_size, f);
}

int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  SigFit_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_SigFit();

  /* Terminate the application.
     You do not need to do this more than one time. */
  SigFit_terminate();
  return 0;
}

/* End of code generation (main.c) */
