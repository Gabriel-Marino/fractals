/**
 * Created when     :   2021.10.21;
 * Last Update      :   2021.12.02;
 * Author           :   G. Marino <gcmarino404@gmail.com>;
 * Notes            :
 * Compilation      :   gcc -O3 src/newton-main.c -static -lgsl -lgslcblas -lm -o fractal.out
 * Execution        :   time ./fractal.out
 */

#include "../fractals.h"

//  roots = [1, -1, 0, i, -i];
double _Complex fun1 (double _Complex z) {return z*(z*z+1)*(z*z-1); };
double _Complex dfun1(double _Complex z) {return 5*z*z*z*z-1; };
struct cmplx roots1[5] = {{1.0, 0.0}, {-1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {0.0, -1.0}};

//  I chose this specific function because it have golden ratio and plus or minus i as root; roots = [phi, 1-phi, 0, i, -i];
double _Complex fun2 (double _Complex z) {return z*(z*z+1)*(z*z-z-1); };
double _Complex dfun2(double _Complex z) {return z*(z*z*(5*z-4)-2)-1; };
struct cmplx roots2[5] = {{phi, 0.0}, {1-phi, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {0.0, -1.0}};

double _Complex find_root(double _Complex r0, double _Complex f(double _Complex z), double _Complex df(double _Complex z)) {

    double _Complex r, rt = r0;

    for (int i = 0; i < iterations; i++) {
        r = rt - f(rt)/df(rt);
        r = rt;
    };

    return r;
};

void fractal(double _Complex func(double _Complex z), double _Complex dfunc(double _Complex z), struct cmplx *root_arr) {

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
