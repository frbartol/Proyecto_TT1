/**
 * @file MeanObliquity.cpp
 * @brief Implementación del cálculo de la oblicuidad media de la eclíptica.
 * @author Francisco Bartolome Alcalde
 */

#include "..\include\MeanObliquity.hpp"
double MeanObliquity(double Mjd_TT){
    double T = (Mjd_TT-SAT_Const::MJD_J2000)/36525.0;
    double MOblq = SAT_Const::Rad *( 84381.448/3600.0-(46.8150+(0.00059-0.001813*T)*T)*T/3600.0 );

    return MOblq;
}