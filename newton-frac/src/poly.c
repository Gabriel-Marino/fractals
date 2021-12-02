#include "../fractals.h"

//  Some code to study later, originally made by Grant Sanderson in Python.

double _Complex coef_poly(char **coefs) {
    double _Complex z;
    int k;
    for (k = 1; k < sizeof(coefs); k++) {
        z += pow(z, k)*atof(coefs[k-1]);
    };
    return z;
};

double _Complex coef_dpoly(char **coefs) {
    double _Complex z;
    int k;
    for (k = 1; k < sizeof(coefs); k++) {
        z += pow(z, k-1)*atof(coefs[k-1]);
    };
    return z;
};