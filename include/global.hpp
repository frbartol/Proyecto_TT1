/**
 * @file global.hpp
 * @brief Declaraciones globales para el sistema de estimación orbital.
 *
 * Este archivo contiene definiciones y declaraciones de variables y funciones globales,
 * como los parámetros auxiliares, coeficientes gravitacionales y datos EOP.
 * Estas estructuras son compartidas por todo el sistema para garantizar coherencia
 * en los cálculos astronómicos y de dinámica orbital.
 *
 * @author Francisco Bartolome Alcalde
 */

#ifndef _GLOBAL_
#define _GLOBAL_

#include "..\include\matrix.hpp"
#include <cmath>

/**
 * @struct Param
 * @brief Estructura que contiene parámetros auxiliares para los modelos físicos y astronómicos.
 *
 * Esta estructura centraliza los datos necesarios para realizar cálculos relacionados
 * con la dinámica orbital, incluyendo fechas en MJD y activación de perturbaciones.
 */
typedef struct {
    double Mjd_UTC;   ///< Tiempo Universal Coordinado (UTC) en Modified Julian Date
    double Mjd_TT;    ///< Tiempo Terrestre (TT) en Modified Julian Date
    int n;            ///< Grado máximo de armónicos gravitacionales
    int m;            ///< Orden máximo de armónicos gravitacionales
    int sun;          ///< 1 si se considera perturbación solar, 0 en caso contrario
    int moon;         ///< 1 si se considera perturbación lunar, 0 en caso contrario
    int planets;      ///< 1 si se consideran perturbaciones planetarias, 0 en caso contrario
} Param;

// Variables globales externas

/** @brief Datos de parámetros de orientación de la Tierra (Earth Orientation Parameters). */
extern Matrix eopdata;

/** @brief Coeficientes Cnm de armónicos esféricos del campo gravitatorio terrestre. */
extern Matrix Cnm;

/** @brief Coeficientes Snm de armónicos esféricos del campo gravitatorio terrestre. */
extern Matrix Snm;

/** @brief Coeficientes de series de interpolación para efemérides. */
extern Matrix PC;

/** @brief Parámetros auxiliares para cálculos globales. */
extern Param AuxParam;

// Funciones globales

/**
 * @brief Carga los datos de orientación de la Tierra desde el año 1962.
 * @param c Número de filas a cargar del archivo.
 */
void eop19620101(int c);

/**
 * @brief Carga los coeficientes armónicos del modelo gravitacional GGM03S.
 * @param n Grado máximo del modelo a cargar.
 */
void GGM03S(int n);

/**
 * @brief Carga los coeficientes del modelo de efemérides JPL DE430.
 * @param f Número de filas.
 * @param c Número de columnas.
 */
void DE430Coeff(int f, int c);

/**
 * @brief Inicializa la estructura `AuxParam` con parámetros por defecto o simulados.
 */
void initializeAuxParam();

#endif
