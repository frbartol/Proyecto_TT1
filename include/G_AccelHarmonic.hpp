#ifndef _G_ACCELHARMONIC_
#define _G_ACCELHARMONIC_

#include "matrix.hpp"
/**
 * @file G_AccelHarmonic.hpp
 * @brief Cálculo del gradiente de la aceleración debido al campo gravitacional armónico terrestre.
 * @author Francisco Bartolome Alcalde
 */
/**
 * @brief Calcula el gradiente de la aceleración debida al campo armónico gravitacional.
 * 
 * @param r Vector de posición en coordenadas cartesianas.
 * @param U Matriz de rotación del sistema inercial al sistema cuerpo.
 * @param n_max Grado máximo del desarrollo armónico.
 * @param m_max Orden máximo del desarrollo armónico.
 * @return Matriz con el gradiente de la aceleración en coordenadas inerciales.
 */
Matrix& G_AccelHarmonic( Matrix& r, Matrix& U, int n_max, int m_max );

#endif