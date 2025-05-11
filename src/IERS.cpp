#include "..\include\IERS.hpp"

tuple<double, double, double, double, double, double, double, double, double> IERS(Matrix& eop, double Mjd_UTC, char interp = 'n'){
    double mjd, mfme, fixf, x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC;
    int i;
    Matrix& preeop = zeros(13,1);
    Matrix& nexteop = zeros(13,1);

    if (interp =='l'){
        mjd = (floor(Mjd_UTC));
        i = 0;
        for (int col = 1; col <= eop.n_column; col++) {
            if (mjd == eop(4, col)) {
                i = col;
                break;
            }
        }
        if (i == 0 || i + 1 > eop.n_column) {
            cout << "IERS: MJD not found in eop data.\n";
            exit(EXIT_FAILURE);  // Salir si no se encuentra el MJD
        }
        preeop = eop.extract_column(i);
        nexteop = eop.extract_column(i+1);
        mfme = 1440*(Mjd_UTC-floor(Mjd_UTC));
        fixf = mfme/1440;
        x_pole  = preeop(5)+(nexteop(5)-preeop(5))*fixf;
        y_pole  = preeop(6)+(nexteop(6)-preeop(6))*fixf;
        UT1_UTC = preeop(7)+(nexteop(7)-preeop(7))*fixf;
        LOD     = preeop(8)+(nexteop(8)-preeop(8))*fixf;
        dpsi    = preeop(9)+(nexteop(9)-preeop(9))*fixf;
        deps    = preeop(10)+(nexteop(10)-preeop(10))*fixf;
        dx_pole = preeop(11)+(nexteop(11)-preeop(11))*fixf;
        dy_pole = preeop(12)+(nexteop(12)-preeop(12))*fixf;
        TAI_UTC = preeop(13);
        
        x_pole  = x_pole/SAT_Const::Arcs;  
        y_pole  = y_pole/SAT_Const::Arcs;  
        dpsi    = dpsi/SAT_Const::Arcs;
        deps    = deps/SAT_Const::Arcs;
        dx_pole = dx_pole/SAT_Const::Arcs; 
        dy_pole = dy_pole/SAT_Const::Arcs;
    }
    else if (interp =='n'){ 
        mjd = (floor(Mjd_UTC));
        i = 0;
        for (int col = 1; col <= eop.n_column; col++) {
            if (mjd == eop(4, col)) {
                i = col;
                break;
            }
        }
        if (i == 0 || i + 1 > eop.n_column) {
            cout << "IERS: MJD not found in eop data.\n";
            exit(EXIT_FAILURE);  // Salir si no se encuentra el MJD
        }
        eop = eop.extract_column(i);
        x_pole  = eop(5)/SAT_Const::Arcs;  
        y_pole  = eop(6)/SAT_Const::Arcs;  
        UT1_UTC = eop(7);             
        LOD     = eop(8);             
        dpsi    = eop(9)/SAT_Const::Arcs;
        deps    = eop(10)/SAT_Const::Arcs;
        dx_pole = eop(11)/SAT_Const::Arcs; 
        dy_pole = eop(12)/SAT_Const::Arcs; 
        TAI_UTC = eop(13);            
    }

    return tie(x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC);
}