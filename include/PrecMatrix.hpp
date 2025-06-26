#ifndef _PRECMATRIX_
#define _PRECMATRIX_

#include "matrix.hpp"
#include "SAT_Const.hpp"
#include "R_y.hpp"
#include "R_z.hpp"

/**
 * @file PrecMatrix.hpp
 * @brief Cálculo de la matriz de precesión entre dos fechas dadas en tiempo juliano modificado.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Devuelve la matriz de transformación debida a la precesión entre dos fechas.
 * 
 * @param Mjd_1 Fecha inicial en MJD (Modified Julian Date).
 * @param Mjd_2 Fecha final en MJD (Modified Julian Date).
 * @return Matriz de precesión 3x3.
 */

Matrix& PrecMatrix(double Mjd_1, double Mjd_2);

#endif