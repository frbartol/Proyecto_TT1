/**
 * @file EqnEquinox.cpp
 * @brief Implementación del cálculo de la ecuación de los equinoccios.
 * @author Francisco Bartolome Alcalde
 */

#include "..\include\EqnEquinox.hpp"

double EqnEquinox(double Mjd_TT){
    // Nutation in longitude and obliquity
    auto [dpsi, deps] = NutAngles(Mjd_TT);

    // Equation of the equinoxes
    return dpsi * cos ( MeanObliquity(Mjd_TT) );
}