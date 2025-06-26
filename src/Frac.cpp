/**
 * @file Frac.cpp
 * @brief Implementación de la función que calcula la parte fraccionaria de un número real.
 * @author Francisco Bartolome Alcalde
 */

#include "..\include\Frac.hpp"
double Frac(double x){
    return x-floor(x);
}