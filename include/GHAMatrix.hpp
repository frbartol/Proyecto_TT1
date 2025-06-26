#ifndef _GHAMATRIX_
#define _GHAMATRIX_

#include "matrix.hpp"
#include "R_z.hpp"
#include "gast.hpp"

/**
 * @file GHAMatrix.hpp
 * @brief Cabecera de la función que calcula la matriz de ángulo horario de Greenwich (GHA) en función del tiempo UT1.
 * @author Francisco Bartolome Alcalde
 */
/**
 * @brief Calcula la matriz de rotación que representa el ángulo horario de Greenwich (GHA).
 * 
 * Esta matriz transforma coordenadas desde el sistema de referencia inercial al sistema de referencia terrestre (TRF),
 * aplicando una rotación alrededor del eje Z por el ángulo GAST (Greenwich Apparent Sidereal Time).
 * 
 * @param Mjd_UT1 Fecha juliana modificada en tiempo UT1.
 * @return Matriz de rotación correspondiente al ángulo horario de Greenwich.
 */
Matrix& GHAMatrix(double Mjd_UT1);

#endif