#ifndef _IERS_
#define _IERS_

#include <tuple>
#include "matrix.hpp"
#include "SAT_Const.hpp"

/**
 * @file IERS.hpp
 * @brief Interpolación de parámetros del IERS a una fecha dada.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Interpola los parámetros EOP (Earth Orientation Parameters) para una fecha dada.
 * 
 * @param eop Matriz de parámetros EOP (cada fila representa una fecha).
 * @param Mjd_UTC Fecha UTC en formato Modified Julian Date.
 * @param interp Modo de interpolación: 'l' para lineal, cualquier otro carácter para sin interpolación.
 * @return Tupla con:
 * - x_p: coordenada del polo en segundos de arco.
 * - y_p: coordenada del polo en segundos de arco.
 * - UT1-UTC en segundos.
 * - LOD: duración del día.
 * - dpsi: corrección de la precesión nutación en longitud.
 * - deps: corrección de la precesión nutación en oblicuidad.
 * - dx: corrección del modelo IAU2000 en x.
 * - dy: corrección del modelo IAU2000 en y.
 * - TAI-UTC en segundos.
 */

tuple<double, double, double, double, double, double, double, double, double> IERS(Matrix& eop, double Mjd_UTC, char interp);

#endif