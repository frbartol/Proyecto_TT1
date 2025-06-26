#ifndef _MEANOBLIQUITY_
#define _MEANOBLIQUITY_

#include "SAT_Const.hpp"

/**
 * @file MeanObliquity.hpp
 * @brief Cálculo de la oblicuidad media de la eclíptica en función del tiempo.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula la oblicuidad media de la eclíptica en radianes.
 * @param Mjd_TT Fecha en tiempo Terrestre (Modified Julian Date).
 * @return Oblicuidad media en radianes.
 */

double MeanObliquity(double Mjd_TT);

#endif