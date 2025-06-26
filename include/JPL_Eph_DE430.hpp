#ifndef _JPL_EPH_DE430_
#define _JPL_EPH_DE430_

#include <tuple>
#include "matrix.hpp"
#include "global.hpp"
#include "Cheb3D.hpp"

using namespace std;

/**
 * @file JPL_Eph_DE430.hpp
 * @brief Cálculo de posiciones planetarias usando la efeméride JPL DE430.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Devuelve las posiciones de los principales cuerpos del sistema solar desde JPL DE430.
 * 
 * @param Mjd_TDB Fecha en Tiempo Dinámico Baricéntrico (TDB) en formato MJD.
 * @return Tupla con las posiciones (3x1) en km de:
 * - Mercurio
 * - Venus
 * - Tierra
 * - Luna
 * - Marte
 * - Júpiter
 * - Saturno
 * - Urano
 * - Neptuno
 * - Plutón
 * - Sol
 */

tuple<Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&> JPL_Eph_DE430(double Mjd_TDB);

#endif