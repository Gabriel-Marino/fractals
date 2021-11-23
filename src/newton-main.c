/**
 * Created when     :   2021.10.21;
 * Last Update      :   2021.11.23;
 * Author           :   G. Marino <gcmarino404@gmail.com>;
 * Notes            :
 * Compilation      :   gcc -O3 src/newton-main.c -static -lgsl -lgslcblas -lm -o fractal.out
 * Execution        :   time ./fractal.out <coefficient of x> <coefficient of x square> <coefficient of x cubic> ... <coefficient of x in nth power>
 */

#include "../newton.h"

//  Struct used to create arrays of complex numbers which ones are the roots of the studied equation;
struct cmplx {
    double real;    //  Real part of the given complex number;
    double imag;    //  Imaginary part of the given complex number;
};

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
// double _Complex *roots[] = (1.0+0.0*I, -1.0+0.0*I, 0.0+0.0*I, 0.0+1.0*I, 0.0-1.0*I);
// struct cmplx *roots[5] = {{1.0, 0.0}, {-1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {0.0, -1.0}};
// double _Complex fun1 (double _Complex x) {return x*(x*x+1)*(x*x-1); };
// double _Complex dfun1(double _Complex x) {return 5*x*x*x*x-1; };

//  I chose this specific function because it have golden ratio and plus or minus i as root; roots = [phi, 1-phi, 0, i, -i];
//  double _Complex *roots[] = ((1.0+sqrt(5))/2.0+0.0*I, (1.0-sqrt(5))/2.0+0.0*I, 0.0+0.0*I, 0.0+1.0*I, 0.0-1.0*I);
// double _Complex fun2 (double _Complex x) {return x*(x*x+1)*(x*x-x-1); };
// double _Complex dfun2(double _Complex x) {return x*(x*x*(5*x-4)-2)-1; };

//  Inspired by Grant Sanderson, Grant uses same generalization in one of he's code.
double _Complex fun(double _Complex x, double *coefs) {
    double _Complex y;
    for (int i = 1; i <= sizeof(coefs); i++) {
        y += coefs[i]*cpow(x, i);
    };
    return y;
};

//  Inspired by Grant Sanderson, Grant uses same generalization in one of he's code.
double _Complex dfun(double _Complex x, double *coefs) {
    double _Complex y;
    for (int i = 1; i <= sizeof(coefs); i++) {
        y += i*coefs[i]*cpow(x, i-1);
    };
    return y;
};

//  Inspired by Grant Sanderson, Grant uses same generalization in one of he's code.
double _Complex roots(double _Complex r0, double *coefs) {
    double _Complex r, rt = r0;
    for (int i = 0; i < 1000; i++) {
        r = rt - fun(rt, coefs)/dfun(rt, coefs);
        rt = r;
    };
    return r;
};

int main(int argc, char **argv) {

    double _Complex r, z;
    int *color = calloc(N*N, sizeof(int));
    double *coefs = calloc(argc, sizeof(double));

    for (int i = 1; i < argc; i++) {
        coefs[i-1] = atof(argv[i]);
    };

    // for (int x = 0; x < N; x++) {
    //     for (int y = 0; y < N; y++) {
    //         r = root_fun(1.0*x+1.0*y*I);                    //  Evaluate each point as an initial guess;
    //         for (int i = 0; i < sizeof(roots); i++) {
    //             z = r - roots[i];                           //  Evaluate how close the point after N iterations of each root of the function;
    //             if (creal(z) < Tol && cimag(z) < Tol) {
    //                 color[x*N+y] = i+1;                     //  Link the point to a given number which going to relate to a color;
    //             };
    //         };
    //     };
    // };

    // for (int x = 0; x < N; x++) {
    //     for (int y = 0; y < N; y++) {
    //         r = root_fun(1.0*x+1.0*y*I);                                                            //  Evaluate each point as an initial guess;
    //         for (int i = 0; i < sizeof(roots); i++) {
    //             if (((creal(r) - roots[i].real) < Tol) && ((cimag(r) - roots[i].imag) < Tol)) {     //  Evaluate how close the point after N iterations of each root of the function;
    //                 color[x*N+y] = i+1;                                                             //  Link the point to a given number which going to relate to a color;
    //             };
    //         };
    //     };
    // };

    op(color);

    free(color);

    return 0;
};
