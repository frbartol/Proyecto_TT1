#ifndef _AZELPA_
#define _AZELPA_

#include <tuple>
#include "matrix.hpp"

/**
 * @file AzElPa.hpp
 * @brief Cálculo del acimut, elevación y vectores parciales a partir del vector topocéntrico.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula el acimut, elevación y los vectores parciales del acimut y la elevación.
 * 
 * @param s Vector topocéntrico (3x1).
 * @return Tupla con:
 * - Acimut (rad)
 * - Elevación (rad)
 * - Vector parcial respecto al acimut (3x1)
 * - Vector parcial respecto a la elevación (3x1)
 */

tuple<double, double, Matrix&, Matrix&> AzElPa(Matrix& s);

#endif