/**
 * @file TimeUpdate.cpp
 * @brief Implementación de la actualización temporal de la matriz de covarianza (filtro de Kalman).
 * @author Francisco Bartolome Alcalde
 */

#include "..\include\TimeUpdate.hpp"

Matrix& TimeUpdate(Matrix& P, Matrix& Phi, double Qdt){
    return Phi*P*transpose(Phi) + Qdt;
}