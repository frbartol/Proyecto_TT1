/**
 * @file LTC.cpp
 * @brief Implementación de la matriz de transformación Local Topocentric Coordinate (LTC).
 * @author Francisco Bartolome Alcalde
 */
#include "..\include\LTC.hpp"
Matrix& LTC(double lon, double lat){
    Matrix& M = R_y(-1.0*lat)*R_z(lon);

    double Aux = 0.0;

    for (int j=1; j<=3; j++){
        Aux=M(1,j);
        M(1,j)=M(2,j);
        M(2,j)=M(3,j);
        M(3,j)= Aux;
    }

    return M;
}