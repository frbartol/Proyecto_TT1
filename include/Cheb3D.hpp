#ifndef _CHEB3D_
#define _CHEB3D_

#include "matrix.hpp"

/**
 * @file Cheb3D.hpp
 * @brief Evaluación de interpolación de Chebyshev en 3D.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Evalúa la posición 3D usando una interpolación de Chebyshev.
 * 
 * @param t Tiempo de evaluación.
 * @param N Número de coeficientes.
 * @param Ta Límite inferior del intervalo de tiempo.
 * @param Tb Límite superior del intervalo de tiempo.
 * @param Cx Coeficientes de Chebyshev para la componente X.
 * @param Cy Coeficientes de Chebyshev para la componente Y.
 * @param Cz Coeficientes de Chebyshev para la componente Z.
 * @return Vector posición 3D (1x3).
 */
Matrix& Cheb3D(double t, int N, double Ta, double Tb, Matrix& Cx, Matrix& Cy, Matrix& Cz);

#endif // Cheb3D.hpp
