/**
 * @file NutMatrix.cpp
 * @brief Implementación del cálculo de la matriz de nutación.
 * @author Francisco Bartolome Alcalde
 */

#include "..\include\NutMatrix.hpp"

Matrix& NutMatrix(double Mjd_TT){
    // Mean obliquity of the ecliptic
    double eps = MeanObliquity (Mjd_TT);

    // Nutation in longitude and obliquity
    auto [dpsi, deps] = NutAngles (Mjd_TT);

    // Transformation from mean to true equator and equinox
    Matrix& NutMat = R_x(-eps-deps)*R_z(-dpsi)*R_x(+eps);
    return NutMat;
}