#ifndef _GMST_
#define _GMST_

#include "Frac.hpp"
#include "SAT_Const.hpp"

/**
 * @file gmst.hpp
 * @brief Cálculo del Tiempo Sidéreo Medio de Greenwich (GMST) a partir del MJD en UT1.
 * @author Francisco Bartolome Alcalde
 */
/**
 * @brief Calcula el Tiempo Sidéreo Medio de Greenwich (GMST) en radianes.
 * 
 * @param Mjd_UT1 Tiempo Universal 1 en formato Modified Julian Date.
 * @return GMST en radianes.
 */

double gmst(double Mjd_UT1);

#endif