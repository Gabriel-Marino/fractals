/**
 * Created when     :   2021.10.21;
 * Last Update      :   2021.11.19;
 * Author           :   G. Marino <gcmarino404@gmail.com>;
 * Notes            :
 * Compilation      :   gcc -O3 src/newton-main.c -static -lgsl -lgslcblas -lm -o fractal.out
 * Execution        :   time ./fractal.out
 */

#include "../newton.h"

//  Output (op) function, print the results into .dat archives;
void op(int *phi) {
    int i, j;
    FILE *file;
    char name[100];

    sprintf(name, "dat/Fractal.dat");
    file = fopen(name, "w");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            fprintf(file, "%d ", phi[i*N+j]);
        };
        fprintf(file, "\n");
    };
    fclose(file);
};

//  roots = [1, -1, 0, i, -i];
double _Complex *roots[] = (1.0+0.0*I, -1.0+0.0*I, 0.0+0.0*I, 0.0+1.0*I, 0.0-1.0*I);
double _Complex fun1 (double _Complex x) {return x*(x*x+1)*(x*x-1); };
double _Complex dfun1(double _Complex x) {return 5*x*x*x*x-1; };

// The function Roots give the roots of the fuction given above.
double _Complex root_fun(double _Complex r0) {
    double _Complex r, temp_r = r0;

    for (int i = 1; i <= 100; i++) {
        r = temp_r - fun1(temp_r)/dfun1(temp_r);
        temp_r = r;
    };

    return r;
};

//  I chose this specific function because it have golden ratio and plus or minus i as root; roots = [phi, 1-phi, 0, i, -i];
//  double _Complex *roots[] = ((1.0+sqrt(5))/2.0+0.0*I, (1.0-sqrt(5))/2.0+0.0*I, 0.0+0.0*I, 0.0+1.0*I, 0.0-1.0*I);
double _Complex fun2 (double _Complex x) {return x*(x*x+1)*(x*x-x-1); };
double _Complex dfun2(double _Complex x) {return x*(x*x*(5*x-4)-2)-1; };

int main(int argc, char **argv) {

    double _Complex r, z;
    int *color = calloc(N*N, sizeof(int));

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            r = root_fun(1.0*x+1.0*y*I);                    //  Evaluate each point as an initial guess;
            for (int i = 0; i < sizeof(roots); i++) {
                z = r - roots[i];                           //  Evaluate how close the point after N iterations of each root of the function;
                if (creal(z) < Tol && cimag(z) < Tol) {
                    color[x*N+y] = i+1;                     //  Link the point to a given number which going to relate to a color;
                };
            };
        };
    };

    op(color);

    free(color);

    return 0;
};
