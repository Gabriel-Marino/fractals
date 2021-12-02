/**
 * Created when     :   2021.11.19;
 * Last Update      :   2021.12.02;
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
#define Tol 1e-8
#define iterations 1000
#define phi (1+sqrt(5))/2

//  Struct used to create arrays of complex numbers which ones are the roots of the studied equation;
struct cmplx {
    double real;    //  Real part of the given complex number;
    double imag;    //  Imaginary part of the given complex number;
};

//  Output (op) function, print the results into .dat archives;
void op(int *arr) {
    int i, j;
    FILE *file;
    char name[100];

    sprintf(name, "dat/Fractal.dat");
    file = fopen(name, "w");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            fprintf(file, "%d ", arr[i*N+j]);
        };
        fprintf(file, "\n");
    };
    fclose(file);
};
