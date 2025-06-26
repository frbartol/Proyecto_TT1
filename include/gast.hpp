#ifndef _GAST_
#define _GAST_

#include "gmst.hpp"
#include "SAT_Const.hpp"
#include "EqnEquinox.hpp"
/**
 * @file gast.hpp
 * @brief Cálculo del Tiempo Sidéreo Aparente de Greenwich (GAST).
 * @author Francisco Bartolome Alcalde
 */
/**
 * @brief Calcula el Tiempo Sidéreo Aparente de Greenwich (GAST) en radianes.
 * 
 * @param Mjd_UT1 Tiempo Juliano Modificado en UT1.
 * @return Valor del GAST en radianes (0 a 2π).
 */
double gast(double Mjd_UT1);

#endif