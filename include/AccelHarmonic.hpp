#ifndef _ACCELHARMONIC_
#define _ACCELHARMONIC_

#include "matrix.hpp"
#include "SAT_Const.hpp"
#include "Legendre.hpp"
#include "global.hpp"

/**
 * @file AccelHarmonic.hpp
 * @brief Cálculo de la aceleración gravitatoria debido al campo armónico terrestre.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula la aceleración perturbadora generada por el potencial gravitacional armónico de la Tierra.
 * 
 * @param r Vector de posición en sistema ECEF (3x1).
 * @param E Matriz de rotación ECI a ECEF (3x3).
 * @param n_max Grado máximo del desarrollo armónico.
 * @param m_max Orden máximo del desarrollo armónico.
 * @return Vector aceleración perturbadora (3x1).
 */

Matrix& AccelHarmonic(Matrix& r, Matrix& E, double n_max, double m_max);

#endif