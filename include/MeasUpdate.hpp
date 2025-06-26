#ifndef _MEASUPDATE_
#define _MEASUPDATE_

#include "matrix.hpp"
#include <tuple>

/**
 * @file MeasUpdate.hpp
 * @brief Actualización de medida para el filtro de Kalman extendido.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Realiza la actualización del estado y de la matriz de covarianza utilizando una nueva medida.
 * 
 * @param x Vector de estado previo a la medida (será actualizado).
 * @param z Valor escalar de la observación.
 * @param g Valor escalar predicho de la observación.
 * @param s Desviación estándar del ruido de medida.
 * @param G Matriz de sensibilidad de la medida respecto al estado.
 * @param P Matriz de covarianza del estado previo.
 * @param n Dimensión del estado.
 * @return Una tupla con el vector de ganancia de Kalman, el estado actualizado y la covarianza actualizada.
 */
tuple<Matrix&, Matrix&, Matrix&> MeasUpdate(Matrix& x, double z, double g, double s, Matrix& G, Matrix& P, int n);

#endif