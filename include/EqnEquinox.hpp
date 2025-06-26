#ifndef _EQNEQUINOX_
#define _EQNEQUINOX_

#include "NutAngles.hpp"
#include "MeanObliquity.hpp"

/**
 * @file EqnEquinox.hpp
 * @brief Cálculo de la ecuación de los equinoccios.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula la ecuación de los equinoccios en radianes.
 * 
 * @param Mjd_TT Fecha en tiempo terrestre (Modified Julian Date).
 * @return Ecuación de los equinoccios en radianes.
 */

double EqnEquinox(double Mjd_TT);

#endif