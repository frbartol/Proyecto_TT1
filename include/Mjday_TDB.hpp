#ifndef _MJDAY_TDB_
#define _MJDAY_TDB_

#include <cmath>
/**
 * @file Mjday_TDB.hpp
 * @brief Declaración de la función que convierte tiempo TT a TDB (Barycentric Dynamical Time).
 *
 * Esta cabecera declara la función `Mjday_TDB`, que transforma el Tiempo Terrestre (TT)
 * al Tiempo Dinámico Baricéntrico (TDB), teniendo en cuenta los efectos de la órbita terrestre.
 *
 * @author Francisco Bartolome Alcalde
 */
/**
 * @brief Convierte MJD en Tiempo Terrestre (TT) a Tiempo Dinámico Baricéntrico (TDB).
 * 
 * @param Mjd_TT Tiempo Terrestre (TT) en Modified Julian Date.
 * @return Tiempo Dinámico Baricéntrico (TDB) en Modified Julian Date.
 */
double Mjday_TDB(double Mjd_TT);

#endif