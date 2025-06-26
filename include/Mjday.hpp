#ifndef _MJDAY_
#define _MJDAY_

#include <cmath>

/**
 * @file Mjday.hpp
 * @brief Cálculo del Modified Julian Date (MJD) a partir de fecha y hora calendario.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @brief Calcula el Modified Julian Date (MJD) a partir de una fecha y hora dadas.
 * @param yr Año.
 * @param mon Mes (1–12).
 * @param day Día del mes.
 * @param hr Hora (por defecto 0).
 * @param min Minutos (por defecto 0).
 * @param sec Segundos (por defecto 0.0).
 * @return Fecha en MJD.
 */

double Mjday(int yr, int mon, int day, int hr=0, int min=0, double sec=0);

#endif