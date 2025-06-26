#ifndef _ACCEL_
#define _ACCEL_

#include "matrix.hpp"
#include "IERS.hpp"
#include "global.hpp"
#include "timediff.hpp"
#include "PrecMatrix.hpp"
#include "SAT_Const.hpp"
#include "NutMatrix.hpp"
#include "PoleMatrix.hpp"
#include "GHAMatrix.hpp"
#include "Mjday_TDB.hpp"
#include "JPL_Eph_DE430.hpp"
#include "AccelHarmonic.hpp"
#include "AccelPointMass.hpp"
/**
 * @file Accel.hpp
 * @brief Prototipo de la función que calcula la aceleración total que actúa sobre un satélite.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula la aceleración total sobre un satélite, teniendo en cuenta efectos gravitacionales y perturbaciones.
 * 
 * @param x Tiempo en MJD_TT (Modified Julian Date, Tiempo Terrestre).
 * @param Y Vector de estado del satélite (posición y velocidad).
 * @return Aceleración total en el sistema de referencia inercial.
 */
Matrix& Accel(double x, Matrix& Y);

#endif