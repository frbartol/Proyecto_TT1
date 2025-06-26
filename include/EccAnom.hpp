#ifndef _ECANOM_
#define _ECANOM_

#include "SAT_Const.hpp"
#include "math.h"
#include <cmath>
#include <limits>
#include <iostream>
/**
 * @file EccAnom.hpp
 * @brief Cálculo de la anomalía excéntrica a partir de la media y la excentricidad.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula la anomalía excéntrica a partir de la anomalía media y la excentricidad.
 * 
 * @param M Anomalía media (en radianes).
 * @param e Excentricidad orbital (0 <= e < 1).
 * @return Anomalía excéntrica (en radianes).
 */
using namespace std;
double EccAnom(double M, double e);

#endif