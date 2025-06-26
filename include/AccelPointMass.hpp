#ifndef _ACCELPOINTMASS_
#define _ACCELPOINTMASS_

#include "matrix.hpp"
#include <iostream>

/**
 * @file AccelPointMass.hpp
 * @brief Cálculo de aceleración debido a una masa puntual.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Devuelve la aceleración perturbadora causada por una masa puntual.
 * @param r Vector posición del satélite (3x1).
 * @param s Vector posición de la masa perturbadora (3x1).
 * @param GM Producto de la constante gravitacional y la masa de la perturbadora.
 * @return Vector aceleración perturbadora (3x1).
 */
Matrix& AccelPointMass(Matrix &r, Matrix &s, double GM);

#endif // AccelPointMass_HPP
