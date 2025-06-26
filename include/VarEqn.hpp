#ifndef _VAREQN_
#define _VAREQN_

#include "matrix.hpp"
#include "IERS.hpp"
#include "global.hpp"
#include "timediff.hpp"
#include "PrecMatrix.hpp"
#include "SAT_Const.hpp"
#include "NutMatrix.hpp"
#include "PoleMatrix.hpp"
#include "GHAMatrix.hpp"
#include "AccelHarmonic.hpp"
#include "G_AccelHarmonic.hpp"

/**
 * @file VarEqn.hpp
 * @brief Declaración de la función para calcular la derivada del sistema variacional para propagación de la matriz de transición.
 * @author Francisco Bartolome Alcalde
 */
/**
 * @brief Calcula la derivada del sistema de ecuaciones variacionales.
 * 
 * @param x Tiempo (en segundos desde una fecha de referencia).
 * @param yPhi Vector que contiene el estado y la matriz de transición aplanada.
 * @return Derivada del vector estado y de la matriz de transición.
 */
Matrix& VarEqn(double x, Matrix& yPhi);

#endif