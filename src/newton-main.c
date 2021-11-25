/**
 * Created when     :   2021.10.21;
 * Last Update      :   2021.11.25;
 * Author           :   G. Marino <gcmarino404@gmail.com>;
 * Notes            :
 * Compilation      :   gcc -O3 src/newton-main.c -static -lgsl -lgslcblas -lm -o fractal.out
 * Execution        :   time ./fractal.out
 */

#include "../newton.h"

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

double _Complex find_root(double _Complex r0, double _Complex f(double _Complex x), double _Complex df(double _Complex x)) {

    double _Complex r, rt = r0;

    for (int i = 0; i < root_iterations; i++) {
        r = rt - f(rt)/df(rt);
        r = rt;
    };

    return r;
};

//  roots = [1, -1, 0, i, -i];
double _Complex fun1 (double _Complex x) {return x*(x*x+1)*(x*x-1); };
double _Complex dfun1(double _Complex x) {return 5*x*x*x*x-1; };
struct cmplx roots1[5] = {{1.0, 0.0}, {-1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {0.0, -1.0}};

//  I chose this specific function because it have golden ratio and plus or minus i as root; roots = [phi, 1-phi, 0, i, -i];
double _Complex fun2 (double _Complex x) {return x*(x*x+1)*(x*x-x-1); };
double _Complex dfun2(double _Complex x) {return x*(x*x*(5*x-4)-2)-1; };
struct cmplx roots2[5] = {{phi, 0.0}, {1-phi, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {0.0, -1.0}};

void fractal(double _Complex func(double _Complex x), double _Complex dfunc(double _Complex x), struct cmplx *root_arr) {

    struct cmplx *plane_2_root = calloc(N*N, sizeof(struct cmplx));
    int x, y, i, *color = calloc(N*N, sizeof(int));
    double _Complex r, z;

    for (x = 0; x < N; x++) {
        for (y = 0; y < N; y++) {
            r = find_root(x+y*I, func, dfunc);
            plane_2_root[x*N+y].real = creal(r);
            plane_2_root[x*N+y].imag = cimag(r);
        };
    };

    for (x = 0; x < N; x++) {
        for (y = 0; y < N; y++) {
            for (i = 0; i < sizeof(roots1); i++) {
                if ((plane_2_root[x*N+y].real-root_arr[x*N+y].real) < Tol && (plane_2_root[x*N+y].imag-root_arr[x*N+y].imag) < Tol) {
                    color[i] = i+1;
                };
            };
        };
    };

    op(color);

    free(color);
};

int main(int argc, char **argv) {

    fractal(fun1, dfun1, roots1);

    return 0;
};
