/**
 * @file Accel.cpp
 * @brief Implementación de la función que calcula la aceleración total actuando sobre un satélite.
 * @author Francisco Bartolome Alcalde
 */

#include "..\include\Accel.hpp"

Matrix& Accel(double x, Matrix& Y){
    auto [x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = IERS(eopdata,AuxParam.Mjd_UTC + x/86400.0,'l');
    auto [UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = timediff(UT1_UTC,TAI_UTC);
    double Mjd_UT1 = AuxParam.Mjd_UTC + x/86400.0 + UT1_UTC/86400.0;
    double Mjd_TT = AuxParam.Mjd_UTC + x/86400.0 + TT_UTC/86400.0;

    Matrix& P = PrecMatrix(SAT_Const::MJD_J2000,Mjd_TT);
    Matrix& N = NutMatrix(Mjd_TT);
    Matrix& T = N * P;
    Matrix& E = PoleMatrix(x_pole,y_pole) * GHAMatrix(Mjd_UT1) * T;

    double MJD_TDB = Mjday_TDB(Mjd_TT);
    auto [r_Mercury,r_Venus,r_Earth,r_Mars,r_Jupiter,r_Saturn,r_Uranus, r_Neptune,r_Pluto,r_Moon,r_Sun] = JPL_Eph_DE430(MJD_TDB);

    // Acceleration due to harmonic gravity field
    Matrix& a = AccelHarmonic(Y.extract_vector(1,3), E, AuxParam.n, AuxParam.m);

    // Luni-solar perturbations
    if (AuxParam.sun){
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Sun,SAT_Const::GM_Sun);
    }

    if (AuxParam.moon){
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Moon,SAT_Const::GM_Moon);
    }

    // Planetary perturbations
    if (AuxParam.planets){
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Mercury,SAT_Const::GM_Mercury);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Venus,SAT_Const::GM_Venus);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Mars,SAT_Const::GM_Mars);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Jupiter,SAT_Const::GM_Jupiter);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Saturn,SAT_Const::GM_Saturn);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Uranus,SAT_Const::GM_Uranus);    
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Neptune,SAT_Const::GM_Neptune);
        a = a + AccelPointMass(Y.extract_vector(1,3),r_Pluto,SAT_Const::GM_Pluto);
    }

    Matrix& dY = Y.extract_vector(4,6).union_vector(a);

    return dY;
}