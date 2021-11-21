/**
 * Created when     :   2021.11.19;
 * Last Update      :   2021.11.21;
 * Author           :   G. Marino <gcmarino404@gmail.com>;
 * Notes            :   Header to the program Newton-main and correlated files.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <complex.h>
#include <gsl/gsl_rng.h>

//  Size of the visualization grid of area N*N;
#define N 1000
//  How close the guessed root given the point used as guest must be to the real root of the equation, Tol is for Tolerance;
#define Tol 0.0001