#ifndef _POLEMATRIX_
#define _POLEMATRIX_

#include "matrix.hpp"
#include "R_x.hpp"
#include "R_y.hpp"

/**
 * @file PoleMatrix.hpp
 * @brief Corrección de coordenadas debido al movimiento del polo terrestre.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Devuelve la matriz de rotación que compensa el desplazamiento del polo terrestre.
 * 
 * @param xp Coordenada X del polo (en radianes).
 * @param yp Coordenada Y del polo (en radianes).
 * @return Matriz de rotación resultante.
 */

Matrix& PoleMatrix(double xp, double yp);

#endif