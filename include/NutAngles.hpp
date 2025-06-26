#ifndef _NUTANGLES_
#define _NUTANGLES_

#include "SAT_Const.hpp"
#include <tuple>
#include <cmath>

using namespace std;

/**
 * @file NutAngles.hpp
 * @brief Cálculo de los ángulos de nutación: Δψ y Δε.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula los ángulos de nutación en longitud (Δψ) y oblicuidad (Δε).
 * 
 * @param Mjd_TT Fecha en tiempo terrestre (Modified Julian Date).
 * @return Tupla con:
 * - Δψ: Nutación en longitud (rad).
 * - Δε: Nutación en oblicuidad (rad).
 */

tuple<double, double> NutAngles(double Mjd_TT);

#endif