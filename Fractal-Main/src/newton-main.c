/**
 * Created when     :   2021.10.21;
 * Last Update      :   2021.11.19;
 * Author           :   G. Marino <gcmarino404@gmail.com>;
 * Notes            :
 * Compilation      :   gcc -O3 newton-main.c -static -lgsl -lgslcblas -lm -o fractal.out
 * Execution        :   time ./fractal.out
 */

#include "newton.h"

//  roots = [-1, 0, 1, -i, i];
double complex fun1(double complex x) {return x*(x*x+1)*(x*x-1); };
//  I chose this specific function because it have golden ratio and plus or minus i as root; roots = [1-phi, 0, phi, -i, i];
double complex fun2(double complex x) {return x*(x*x+1)*(x*x-x-1); };

double complex dfun1(double complex x) {return 5*x*x*x*x-1; };
double complex dfun2(double complex x) {return x*(x*x*(5*x-4)-2)-1; };

// The function Roots give the roots of the fuction given above.
double complex root1(double complex r0) {
    double complex r, temp_r = r0;

    for (int i = 1; i <= 100; i++) {
        r = temp_r - fun1(temp_r)/dfun1(temp_r);
        temp_r = r;
    };

    return r;
};

double complex root2(double complex r0) {
    double complex r, temp_r = r0;

    for (int i = 1; i <= 100; i++) {
        r = temp_r - fun2(temp_r)/dfun2(temp_r);
        temp_r = r;
    };

    return r;
};

int main(int argc, char **argv) {

    double complex *r = calloc(N*N, sizeof(double complex)), z;

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            r[x*N+y] = root1(1.0*x+1.0*y*I);
        };
    };



    return 0;
};
