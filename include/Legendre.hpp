#ifndef _LEGENDRE_
#define _LEGENDRE_

#include <tuple>
#include "matrix.hpp"

/**
 * @file Legendre.hpp
 * @brief Cálculo de polinomios de Legendre normalizados y sus derivadas.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula los polinomios de Legendre normalizados y sus derivadas.
 * 
 * @param n Grado máximo.
 * @param m Orden máximo.
 * @param fi Ángulo en radianes (fi = latitud geocéntrica).
 * @return Tupla con:
 * - Matriz de valores de los polinomios (P̅ₙᵐ)
 * - Matriz de derivadas respecto a fi (dP̅ₙᵐ/dfi)
 */

tuple<Matrix&, Matrix&> Legendre(int n, int m, double fi);

#endif