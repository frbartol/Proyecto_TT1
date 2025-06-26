#ifndef _TIMEUPDATE_
#define _TIMEUPDATE_

#include "matrix.hpp"

/**
 * @file TimeUpdate.hpp
 * @brief Actualización temporal de la matriz de covarianza en un filtro de Kalman.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Realiza la actualización temporal (predictiva) de la matriz de covarianza.
 * 
 * @param P Matriz de covarianza anterior.
 * @param Phi Matriz de transición del sistema.
 * @param Qdt Valor escalar que representa el ruido del proceso (opcional, por defecto 0).
 * @return Matriz de covarianza predicha.
 */

Matrix& TimeUpdate(Matrix& P, Matrix& Phi, double Qdt = 0.0);

#endif