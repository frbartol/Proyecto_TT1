#ifndef _DEINTEG_
#define _DEINTEG_

#include "matrix.hpp"
#include "SAT_Const.hpp"
#include "sign_.hpp"

/**
 * @file DEInteg.hpp
 * @brief Definición del integrador numérico multistep de Shampine & Gordon para sistemas de ecuaciones diferenciales ordinarias.
 * @author Francisco Bartolome Alcalde
 */
/**
 * @brief Integrador multistep con paso y orden variable basado en el método de Shampine & Gordon.
 * 
 * @param func Función que define el sistema de ecuaciones diferenciales (debe devolver la derivada de y).
 * @param t Tiempo inicial.
 * @param tout Tiempo final deseado de integración.
 * @param relerr Error relativo permitido.
 * @param abserr Error absoluto permitido.
 * @param n_eqn Número de ecuaciones del sistema.
 * @param y Vector de estado inicial (y se actualiza con el estado final).
 * @return Vector de estado final tras la integración.
 */
Matrix& DEInteg(Matrix& func(double, Matrix&), double t, double tout, double relerr, double abserr, int n_eqn, Matrix& y);

#endif