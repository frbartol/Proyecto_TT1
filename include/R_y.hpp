#ifndef _R_Y_
#define _R_Y_

#include "matrix.hpp"

/**
 * @file R_y.hpp
 * @brief Matriz de rotación en torno al eje Y.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Devuelve la matriz de rotación 3x3 respecto al eje Y para un ángulo dado.
 * @param angle Ángulo de rotación en radianes.
 * @return Matriz de rotación 3x3.
 */

Matrix& R_y(double angle);
    
#endif