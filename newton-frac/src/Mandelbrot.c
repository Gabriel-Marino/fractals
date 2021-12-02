#include "../fractals.h"

//  Some code to study later.

//  Check if the number c belong to the Mandelbrot set and how close it's to the set.
double _Complex Mandelbrot(double _Complex c) {
    double _Complex z = c,                      //  by definition z0=0, so z1 = c;
                    zt;                         //  temporary number z;
    for (int i = 0; i < iterations; i++) {
        zt = z*z + c;                           //  by definition z_n = z_(n-1)^2+c;
        z = zt;
        if (cabs(z) > 2) {
            break;                              //! Mathematically if the module of the complex number is bigger than 2 then it not belong to Mandebrot set;
        };
    };
    return i;                                   /*  Return how many iterations needed to check if the number c belong to or not to the Mandelbrot set, so we can map by color
                                                    the numbers in the complex plane by how close it to the Mandelbrot set.*/
};