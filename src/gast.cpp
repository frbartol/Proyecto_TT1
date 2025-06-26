/**
 * @file gast.cpp
 * @brief Implementación del cálculo del Tiempo Sidéreo Aparente de Greenwich (GAST).
 * @author Francisco Bartolome Alcalde
 */
#include "..\include\gast.hpp"

double gast(double Mjd_UT1){
    double gstime = fmod( gmst(Mjd_UT1) + EqnEquinox(Mjd_UT1), 2*SAT_Const::pi );
    if(gstime<0) gstime += 2*SAT_Const::pi;
    return gstime;
}