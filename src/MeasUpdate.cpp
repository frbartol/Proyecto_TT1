/**
 * @file MeasUpdate.cpp
 * @brief Implementación de la actualización de medida para el filtro de Kalman extendido.
 * @author Francisco Bartolome Alcalde
 */

#include "..\include\MeasUpdate.hpp"
tuple<Matrix&, Matrix&, Matrix&> MeasUpdate(Matrix& x, double z, double g, double s, Matrix& G, Matrix& P, int n){
    int m = 1;
    double Inv_W = s*s;

    // Kalman gain
    Matrix& K = transpose(P*transpose(G)*transpose(inv(G*P*transpose(G)+Inv_W)));

    // State update
    x = x + K*(z-g);

    // Covariance update
    P = (eye(n)-transpose(K)*G)*P;
    return tie(K,x,P);
}
