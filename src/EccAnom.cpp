/**
 * @file EccAnom.cpp
 * @brief Implementación del cálculo de la anomalía excéntrica mediante el método de Newton-Raphson.
 * @author Francisco Bartolome Alcalde
 */

#include "..\include\EccAnom.hpp"
double EccAnom(double M, double e){

    const double eps = numeric_limits<double>::epsilon();
    const int maxit = 15;
    double f;
    double E;
    int i = 1;
    
    M = fmod(M,2.0*SAT_Const::pi);
    if(M<0) M += 2.0*SAT_Const::pi;
    
    if(e<0.8) E = M;
    else E = SAT_Const::pi;

    
    f = E -e*sin(E)-M;
    E = E - f/(1.0 - e*cos(E));
    while(fabs(f)>1e2*eps){
        f = E -e*sin(E) - M;
        E = E - f/(1.0-e*cos(E));
        i++;
        if(i==maxit){
            cout<<"EccAnom: convergence problems";
            exit(EXIT_FAILURE);
        }
    }
    return E;
}