#include "..\include\SAT_Const.hpp"
#include "..\include\matrix.hpp"
#include "..\include\AccelPointMass.hpp"
#include "..\include\Cheb3d.hpp"
#include "..\include\EccAnom.hpp"
#include "..\include\Frac.hpp"
#include "..\include\MeanObliquity.hpp"
#include "..\include\Mjday.hpp"
#include "..\include\Mjday_TDB.hpp"
#include "..\include\Position.hpp"
#include "..\include\R_x.hpp"
#include "..\include\R_y.hpp"
#include "..\include\R_z.hpp"
#include "..\include\timediff.hpp"
#include "..\include\AzElPa.hpp"
#include "..\include\IERS.hpp"
#include "..\include\Legendre.hpp"
#include "..\include\NutAngles.hpp"
#include "..\include\TimeUpdate.hpp"
#include "..\include\global.hpp"
#include "..\include\AccelHarmonic.hpp"
#include "..\include\EqnEquinox.hpp"
#include "..\include\JPL_Eph_DE430.hpp"
#include "..\include\LTC.hpp"
#include "..\include\NutMatrix.hpp"
#include "..\include\PoleMatrix.hpp"
#include "..\include\PrecMatrix.hpp"
#include "..\include\gmst.hpp"
#include "..\include\gast.hpp"
#include "..\include\MeasUpdate.hpp"
#include "..\include\G_AccelHarmonic.hpp"
#include "..\include\GHAMatrix.hpp"
#include "..\include\Accel.hpp"
#include "..\include\VarEqn.hpp"
#include "..\include\DEInteg.hpp"

#include <tuple>
#include <iostream>
#include <string.h>

using namespace std;
/**
 * @file EKF_GEOS3.cpp
 * @brief Estimación de la órbita de un satélite usando el filtro de Kalman extendido (EKF) y medidas reales del satélite GEOS-3.
 * 
 * El programa carga observaciones topocéntricas (acimut, elevación, distancia) desde el fichero `GEOS3.txt` y estima la trayectoria del satélite
 * integrando su movimiento con un modelo dinámico completo que incluye:
 * - Campo gravitatorio armónico terrestre (modelo GGM03S)
 * - Perturbaciones de cuerpos mayores (Luna, Sol, planetas)
 * - Parámetros de orientación terrestre (EOP) e instantes en distintos sistemas de tiempo (UTC, UT1, TT, TDB)
 * 
 * Se inicializa el estado con una aproximación, se propaga usando `DEInteg`, y se aplica el EKF con las funciones:
 * - `Accel`: dinámica orbital
 * - `VarEqn`: derivadas de transición
 * - `MeasUpdate`: actualizaciones del estado por medidas
 * - `TimeUpdate`: predicción de la covarianza
 * - `AzElPa`: conversión de coordenadas topocéntricas y derivadas parciales
 * 
 * Finalmente se compara el estado estimado con el estado real para evaluar la precisión de la estimación.
 * 
 * Entradas:
 * - Fichero `../data/GEOS3.txt` con 46 observaciones (formato fijo)
 * 
 * Salida:
 * - Errores de posición y velocidad estimados respecto a valores conocidos
 * 
 * @author Francisco Bartolome Alcalde
 */

int main() {
	eop19620101(21413);
	GGM03S(181);
	DE430Coeff(2285, 1020);
    initializeAuxParam();

    int nobs = 46, Ye, M, D, h, m, n_eqn;
    double se, az, el, Dist, sigma_range, sigma_az, sigma_el, lat, lon, alt,
    Mjd1, Mjd2, Mjd3, Mjd0, Mjd_UTC, t, t_old, Mjd_TT, Mjd_UT1, theta, Azim,
    Elev;
    Matrix& obs = zeros(nobs,4);
    char tline[55], aux[11]; 

    // read observations
    FILE *fid = fopen("../data/GEOS3.txt","r");

    if(fid==NULL){
		printf("Fail open GEOS3.txt file\n");
		exit(EXIT_FAILURE);
	}

    for (int i=1; i<=nobs; i++){
        fgets(tline, sizeof(tline) + 2, fid);

        strncpy(aux, tline + 0, 4);
        aux[4] = '\0';
        Ye = atoi(aux);

        strncpy(aux, tline + 5, 2);
        aux[2] = '\0';
        M = atoi(aux);

        strncpy(aux, tline + 8, 2);
        aux[2] = '\0';
        D = atoi(aux);

        strncpy(aux, tline + 12, 2);
        aux[2] = '\0';
        h = atoi(aux);

        strncpy(aux, tline + 15, 2);
        aux[2] = '\0';
        m = atoi(aux);

        strncpy(aux, tline + 18, 6);
        aux[6] = '\0';
        se = atof(aux);

        strncpy(aux, tline + 25, 8);
        aux[8] = '\0';
        az = atof(aux);

        strncpy(aux, tline + 35, 7);
        aux[7] = '\0';
        el = atof(aux);

        strncpy(aux, tline + 44, 10);
        aux[10] = '\0';
        Dist = atof(aux);
        obs(i,1) = Mjday(Ye,M,D,h,m,se);
        obs(i,2) = SAT_Const::Rad*az;
        obs(i,3) = SAT_Const::Rad*el;
        obs(i,4) = 1e3*Dist;
    }

    fclose(fid);
    
    sigma_range = 92.5;          // [m]
    sigma_az = 0.0224*SAT_Const::Rad; // [rad]
    sigma_el = 0.0139*SAT_Const::Rad; // [rad]

    // Kaena Point station
    lat = SAT_Const::Rad*21.5748;     // [rad]
    lon = SAT_Const::Rad*(-158.2706); // [rad]
    alt = 300.20;                // [m]

    Matrix& Rs = transpose(Position(lon, lat, alt));
    
    Mjd1 = obs(1,1);
    Mjd2 = obs(9,1);
    Mjd3 = obs(18,1);

    Matrix &r2 = zeros(1,3), &v2 = zeros(1,3);
    r2(1)=6221397.62857869; r2(2)=2867713.77965738; r2(3)=3006155.98509949;
	v2(1)=4645.04725161806; v2(2)=-2752.21591588204; v2(3)=-7507.99940987031;
    //auto [r2,v2] = anglesg(obs(1,2),obs(9,2),obs(18,2),obs(1,3),obs(9,3),obs(18,3),Mjd1,Mjd2,Mjd3,Rs,Rs,Rs);

    Matrix& Y0_apr = r2.union_vector(v2);
    
    Mjd0 = Mjday(1995,1,29,02,38,0);

    Mjd_UTC = obs(9,1);

    AuxParam.Mjd_UTC = Mjd_UTC;
    AuxParam.n      = 20;
    AuxParam.m      = 20;
    AuxParam.sun     = 1;
    AuxParam.moon    = 1;
    AuxParam.planets = 1;
    
    n_eqn  = 6;

    Matrix& Y = DEInteg(Accel,0,-(obs(9,1)-Mjd0)*86400.0,1e-13,1e-6,6,Y0_apr);
    
    Matrix& P = zeros(6);
    
    for (int i=1; i<=3; i++){
        P(i,i)=1e8;
    }
    for (int i=4; i<=6; i++){
        P(i,i)=1e3;
    }
    
    Matrix& LT = LTC(lon,lat);

    Matrix& yPhi = zeros(1,42);
    Matrix& Phi  = zeros(6);

    // Measurement loop
    t = 0.0;

    Matrix& Y_old = zeros(1);
    Matrix& U = zeros(1);
    Matrix& r = zeros(1);
    Matrix& s = zeros(1);
    Matrix& dAdY = zeros(1);
    Matrix& dDdY = zeros(1);
    Matrix& K = zeros(1);
    Matrix& dEdY = zeros(1);
    Matrix& dDds = zeros(1);
    Matrix& dAds = zeros(1);
    Matrix& dEds = zeros(1);
    
    for (int i=1; i<=nobs; i++){
        // Previous step
        t_old = t;
        Y_old = Y;
        
        // Time increment and propagation
        Mjd_UTC = obs(i,1);                       // Modified Julian Date
        t       = (Mjd_UTC-Mjd0)*86400.0;         // Time since epoch [s]
        
        auto [x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = IERS(eopdata,Mjd_UTC,'l');
        auto [UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = timediff(UT1_UTC,TAI_UTC);
        Mjd_TT = Mjd_UTC + TT_UTC/86400;
        Mjd_UT1 = Mjd_TT + (UT1_UTC-TT_UTC)/86400.0;
        AuxParam.Mjd_UTC = Mjd_UTC;
        AuxParam.Mjd_TT = Mjd_TT;
        
        for (int ii=1; ii<=6; ii++){
            yPhi(ii) = Y_old(ii);
            for (int j=1; j<=6; j++){  
                if (ii==j){
                    yPhi(6*j+ii) = 1.0; 
                }
                else{
                    yPhi(6*j+ii) = 0.0;
                }
            }
        }
        
        yPhi = DEInteg (VarEqn,0,t-t_old,1e-13,1e-6,42,yPhi);
        
        // Extract state transition matrices
        for (int j=1; j<=6; j++){
            Phi.asign_column(j, transpose(yPhi.extract_vector(6*j+1,6*j+6)));
        }
        
        Y = DEInteg (Accel,0,t-t_old,1e-13,1e-6,6,Y_old);
        
        // Topocentric coordinates
        theta = gmst(Mjd_UT1);                    // Earth rotation
        U = R_z(theta);
        r = Y.extract_vector(1,3);
        
        s = LT*(U*transpose(r)-Rs);                          // Topocentric position [m]
        
        // Time update
        P = TimeUpdate(P, Phi);
            
        // Azimuth and partials
        std::tie(Azim, Elev, dAds, dEds) = AzElPa(transpose(s));     // Azimuth, Elevation
        
        dAdY = (dAds*LT*U).union_vector(zeros(1,3));
        
        // Measurement update
        cout<<"Y\n"<<Y<<endl;
        cout<<"obs(i,2)\n"<<obs(i,2)<<endl;
        cout<<"Azim\n"<<Azim<<endl;
        cout<<"sigma_az\n"<<sigma_az<<endl;
        cout<<"dAdY\n"<<dAdY<<endl;
        cout<<"P\n"<<P<<endl;
        std::tie(K, Y, P) = MeasUpdate ( Y, obs(i,2), Azim, sigma_az, dAdY, P, 6 );
        cout<<"K\n"<<K<<endl;
        cout<<"Y\n"<<Y<<endl;
        cout<<"P\n"<<P<<endl;
        // Elevation and partials
        r = Y.extract_vector(1,3);
        s = LT*(U*transpose(r)-Rs);                          // Topocentric position [m]
        
        auto [Azim, Elev, dAds, dEds] = AzElPa(transpose(s));     // Azimuth, Elevation
        
        dEdY = (dEds*LT*U).union_vector(zeros(1,3));
        
        // Measurement update
        

        std::tie(K, Y, P) = MeasUpdate ( Y, obs(i,3), Elev, sigma_el, dEdY, P, 6 );
        
        // Range and partials
        r = Y.extract_vector(1,3);
        s = LT*(U*transpose(r)-Rs);                          // Topocentric position [m]
        Dist = s.norm(); dDds = transpose(s/Dist);         // Range
        dDdY = (dDds*LT*U).union_vector(zeros(1,3));
        
        // Measurement update
        std::tie(K, Y, P) = MeasUpdate ( Y, obs(i,4), Dist, sigma_range, dDdY, P, 6 );
    }
    auto [x_pole,y_pole,UT1_UTC,LOD,dpsi,deps,dx_pole,dy_pole,TAI_UTC] = IERS(eopdata,obs(46,1),'l');
    auto [UT1_TAI,UTC_GPS,UT1_GPS,TT_UTC,GPS_UTC] = timediff(UT1_UTC,TAI_UTC);
    
    Mjd_TT = Mjd_UTC + TT_UTC/86400.0;
    AuxParam.Mjd_UTC = Mjd_UTC;
    AuxParam.Mjd_TT = Mjd_TT;
    
    Matrix& Y0 = DEInteg (Accel,0,-(obs(46,1)-obs(1,1))*86400.0,1e-13,1e-6,6,Y);

    Matrix& Y_True = zeros(6,1);
    Y_True(1) = 5753.173e3;
    Y_True(2) = 2673.361e3;
    Y_True(2) = 3440.304e3;
    Y_True(2) = 4.324207e3;
    Y_True(2) = -1.924299e3;
    Y_True(2) = -5.728216e3;
    
    printf("\nError of Position Estimation\n");
    printf("dX%10.1f [m]\n",Y0(1)-Y_True(1));
    printf("dY%10.1f [m]\n",Y0(2)-Y_True(2));
    printf("dZ%10.1f [m]\n",Y0(3)-Y_True(3));
    printf("\nError of Velocity Estimation\n");
    printf("dVx%8.1f [m/s]\n",Y0(4)-Y_True(4));
    printf("dVy%8.1f [m/s]\n",Y0(5)-Y_True(5));
    printf("dVz%8.1f [m/s]\n",Y0(6)-Y_True(6));
}