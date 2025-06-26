#ifndef _LTC_
#define _LTC_

#include "matrix.hpp"
#include "R_x.hpp"
#include "R_y.hpp"
#include "R_z.hpp"
/**
 * @file LTC.hpp
 * @brief Construye una matriz de transformación de coordenadas locales topocéntricas a coordenadas geocéntricas.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula la matriz de transformación Local Topocentric Coordinate (LTC).
 * 
 * Esta matriz transforma vectores desde el sistema de coordenadas topocéntrico local
 * (Este, Norte, Cenit) al sistema de coordenadas geocéntrico (ECI).
 * 
 * @param lon Longitud geográfica en radianes.
 * @param lat Latitud geográfica en radianes.
 * @return Matriz de transformación 3x3.
 */

Matrix& LTC(double lon, double lat);
#endif