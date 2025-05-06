#include "..\include\EccAnom.hpp"
double EccAnom(double M, double e){

    const double eps = numeric_limits<double>::epsilon();
    const int maxit = 15;
    double f;
    double E;
    int i = 1;
    
    M = fmod(M,2.0*M_PI);
    
    if(e<0.8) E = M;
    else E = M_PI;

    
    f = E -e*sin(E)-M;
    E = E - f/(1.0 - e*cos(E));
    while(abs(f)>1e2*eps){
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