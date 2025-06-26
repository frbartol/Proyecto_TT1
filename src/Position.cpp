/**
 * @file Position.cpp
 * @brief Implementación de la conversión de coordenadas geodésicas a ECEF.
 * @author Francisco Bartolome Alcalde
 */
#include "..\include\Position.hpp"

Matrix& Position(double lon, double lat, double h){
    double R_equ, f, e2, CosLat, SinLat, N;
    Matrix& r = zeros(1,3);

    R_equ = SAT_Const::R_Earth;
    f     = SAT_Const::f_Earth;

    e2     = f*(2.0-f);  
    CosLat = cos(lat);
    SinLat = sin(lat);

    N = R_equ / sqrt(1.0-e2*SinLat*SinLat);

    r(1) =  (N+h)*CosLat*cos(lon);
    r(2) =  (N+h)*CosLat*sin(lon);
    r(3) =  ((1.0-e2)*N+h)*SinLat;

    return r;
}