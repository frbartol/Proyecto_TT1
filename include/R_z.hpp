#ifndef _R_Z_
#define _R_Z_

#include "matrix.hpp"

/**
 * @file R_z.hpp
 * @brief Matriz de rotación en torno al eje Z.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Devuelve la matriz de rotación 3x3 respecto al eje Z para un ángulo dado.
 * @param angle Ángulo de rotación en radianes.
 * @return Matriz de rotación 3x3.
 */

Matrix& R_z(double angle);
    
#endif