#ifndef _TIMEDIFF_
#define _TIMEDIFF_

#include <tuple>
using namespace std;


/**
 * @file timediff.hpp
 * @brief Cálculo de diferencias de tiempo entre escalas temporales estándar.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula las diferencias entre escalas de tiempo UT1, TAI, TT, UTC y GPS.
 * 
 * @param UT1_UTC Diferencia UT1 - UTC [s].
 * @param TAI_UTC Diferencia TAI - UTC [s].
 * @return Tupla con:
 * - UT1 - UTC
 * - TAI - UTC
 * - UTC - TAI
 * - GPS - UTC
 * - TT - UTC
 */

tuple<double, double, double, double, double> timediff(double UT1_UTC, double TAI_UTC);
    
#endif