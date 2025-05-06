#include "../include/Cheb3D.hpp"
Matrix Cheb3D(double t, int N, double Ta, double Tb, Matrix& Cx, Matrix& Cy, Matrix& Cz){
    if(t<Ta || Tb<t){
        cout<<"Cheb3D: Time out of range";
    }
    if(Cx.n_column!=N || Cy.n_column!=N || Cz.n_column!=N){
        cout<<"Cheb3D: Incorrect size of Cx/Cy/Cz";
    }
    double tau = (2*t-Ta-Tb)/(Tb-Ta);
    Matrix f1 = zeros(1,3);
    Matrix f2 = zeros(1,3);

    for(int i = N; i>=2; i--){
        Matrix old_f1 = f1;
        f1 = f1*2*tau - f2;
        f1(1,1) = f1(1,1) + Cx(1,i);
        f1(1,2) = f1(1,2) + Cy(1,i);
        f1(1,3) = f1(1,3) + Cz(1,i);
        f2 = old_f1;
    }

    Matrix ChebApp(1,3);
    ChebApp = f1*tau-f2;
    ChebApp(1,1) = ChebApp(1,1)+Cx(1,1);
    ChebApp(1,2) = ChebApp(1,2)+Cy(1,1);
    ChebApp(1,3) = ChebApp(1,3)+Cz(1,1);
    return ChebApp;
}