#ifndef _SAT_CONST_
#define _SAT_CONST_

/**
 * @file SAT_Const.hpp
 * @brief Constantes astronómicas y físicas usadas en dinámica orbital y propagación satelital.
 * @author Francisco Bartolome Alcalde
 */

/**
 * @class SAT_Const
 * @brief Contiene constantes matemáticas, astronómicas y físicas necesarias para cálculos orbitales.
 */

class SAT_Const{
public:

    // Mathematical constants
    static const double pi;
    static const double pi2;       
    static const double Rad;
    static const double Deg;       
    static const double Arcs;
    // General
    static const double MJD_J2000;
    static const double T_B1950;
    static const double c_light;
    static const double AU;

    // Physical parameters of the Earth, Sun and Moon

    // Equatorial radius and flattening
    static const double R_Earth;
    static const double f_Earth;
    static const double R_Sun;
    static const double R_Moon;

    // Earth rotation (derivative of GMST at J2000; differs from inertial period by precession)
    static const double omega_Earth;

    // Gravitational coefficients
    static const double GM_Earth;
    static const double GM_Sun;
    static const double GM_Moon;
    static const double GM_Mercury;
    static const double GM_Venus;
    static const double GM_Mars;
    static const double GM_Jupiter;
    static const double GM_Saturn;
    static const double GM_Uranus;
    static const double GM_Neptune;
    static const double GM_Pluto;

    // Solar radiation pressure at 1 AU 
    static const double P_Sol;
    static const double eps;
};


#endif