#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>

#define d               0.0001
#define max_iterations  1000
#define N               3

double mandelbrot (double _Complex c) {

    int i;
    double _Complex z = c, zt;               //  by definition z0=0, so z1 = c;

    for (i = 0; i < max_iterations; i++) {
        zt = z*z + c;                       //  by definition z_n = z_(n-1)^2+c;
        z = zt;
        if (cabs(z) > 2) {                  //! Mathematically if the module of the complex number is bigger than 2 then it not belong to Mandebrot set;
            break;
        }; 
    };

    return (1.0*i)/(1.0*max_iterations);                /*  Return how many iterations needed to check if the number c belong to or not to the Mandelbrot set, so we can map by color
                                                the numbers in the complex plane by how close it to the Mandelbrot set.*/
};


int main (int argc, char **argv) {

    double x, y;

    FILE *file = fopen("mandelbrot.dat", "w");

    for (x = -N; x <= N; x += d) {
        for (y = -N; y <= N; y += d) {
            fprintf(file, "%e", mandelbrot(x+I*y));
        };
        fprintf(file, "\n");
        if ((int)((x+N)/d)%((int)(N/d)/1000) == 0) {
            printf("%0.2f%%\n", ((x+N)/d)/((2*N/d)/100));
        };
    };

    fclose(file);

    return 0;
};