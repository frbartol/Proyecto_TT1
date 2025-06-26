#ifndef _NUTMATRIX_
#define _NUTMATRIX_

#include "matrix.hpp"
#include "MeanObliquity.hpp"
#include "NutAngles.hpp"
#include "R_x.hpp"
#include "R_z.hpp"

/**
 * @file NutMatrix.hpp
 * @brief Cálculo de la matriz de nutación a partir del tiempo terrestre (Mjd_TT).
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula la matriz de nutación utilizando los ángulos de nutación y la oblicuidad media.
 * 
 * @param Mjd_TT Tiempo terrestre en Modified Julian Date.
 * @return Matriz de nutación (3x3) que transforma de coordenadas medias a verdaderas.
 */

Matrix& NutMatrix(double Mjd_TT);

#endif