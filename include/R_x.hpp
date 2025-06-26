#ifndef _R_X_
#define _R_X_

#include "matrix.hpp"

/**
 * @file R_x.hpp
 * @brief Matriz de rotación en torno al eje X.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Devuelve la matriz de rotación 3x3 respecto al eje X para un ángulo dado.
 * @param angle Ángulo de rotación en radianes.
 * @return Matriz de rotación 3x3.
 */

Matrix& R_x(double angle);
    
#endif