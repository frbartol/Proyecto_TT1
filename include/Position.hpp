#ifndef _POSITION_
#define _POSITION_

#include "matrix.hpp"
#include "SAT_Const.hpp"

/**
 * @file Position.hpp
 * @brief Conversión de coordenadas geodésicas a coordenadas cartesianas ECEF.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula el vector de posición ECEF a partir de longitud, latitud y altura.
 * 
 * @param lon Longitud geodésica (en radianes).
 * @param lat Latitud geodésica (en radianes).
 * @param h Altura sobre el elipsoide (en km).
 * @return Vector posición en coordenadas ECEF (3x1).
 */

Matrix& Position(double lon, double lat, double h);

#endif