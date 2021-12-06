/**
 * Created when     :   2021.12.06;
 * Last Update      :   2021.12.06;
 * Author           :   G. Marino <gcmarino404@gmail.com>;
 * Notes            :
 * Compilation      :   gcc -O3 src/newtonV1.c -static -lgsl -lgslcblas -lm -o fractal.out
 * Execution        :   time ./fractal.out
 */

#include "../fractals.h"

//  roots = [1, -1, 0, i, -i];
double _Complex f (double _Complex z) {return z*(z*z+1)*(z*z-1); };
double _Complex df(double _Complex z) {return 5*z*z*z*z-1; };
struct cmplx roots[5] = {{1.0, 0.0}, {-1.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {0.0, -1.0}};


double _Complex find_root(double _Complex r0) {

    double _Complex r, rt = r0;

    for (int i = 0; i < iterations; i++) {
        r = rt - f(rt)/df(rt);
        rt = r;
    };

    return r;
};

void Newton(struct cmplx *root_arr) {

    struct cmplx *plane_2_root = calloc(N*N, sizeof(struct cmplx));
    int x, y, i, *color = calloc(N*N, sizeof(int));
    double _Complex r, z;

    for (x = -N/2; x <= N/2; x++) {
        for (y = -N/2; y <= N/2; y++) {
            r = find_root(x+y*I);
            plane_2_root[(x+N/2)*N+(y+N/2)].real = creal(r);
            plane_2_root[(x+N/2)*N+(y+N/2)].imag = cimag(r);
        };
    };

    for (x = 0; x < N; x++) {
        for (y = 0; y < N; y++) {
            for (i = 0; i < sizeof(root_arr); i++) {
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

    Newton(roots);

    return 0;
};
