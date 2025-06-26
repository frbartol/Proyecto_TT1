#ifndef _SIGN__
#define _SIGN__

#include <cmath>

/**
 * @file sign_.hpp
 * @brief Devuelve el valor absoluto de `a` con el signo de `b`.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Devuelve |a| con el signo de b.
 * 
 * Equivalente a la función `SIGN(a, b)` de Fortran.
 * 
 * @param a Valor base.
 * @param b Referencia de signo.
 * @return |a| si b ≥ 0, -|a| si b < 0.
 */

double sign_(double a, double b);

#endif