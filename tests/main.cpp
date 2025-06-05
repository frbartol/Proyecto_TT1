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

#include <tuple>
#include <iostream>

using namespace std;

int main() {
	eop19620101(21413);
	GGM03S(181);
	DE430Coeff(2285, 1020);
    initializeAuxParam();

	double x = 3600;
    Matrix& yPhi = zeros(1,42);
    yPhi(1) = 7000000; yPhi(2) = 0;       yPhi(3) = 0;       yPhi(4) = 0;     yPhi(5) = 7500;   yPhi(6) = 0;
    yPhi(7) = 1;       yPhi(8) = 0;       yPhi(9) = 0;       yPhi(10) = 0;    yPhi(11) = 0;     yPhi(12) = 0;
    yPhi(13) = 0;      yPhi(14) = 1;      yPhi(15) = 0;      yPhi(16) = 0;    yPhi(17) = 0;     yPhi(18) = 0;
    yPhi(19) = 0;      yPhi(20) = 0;      yPhi(21) = 1;      yPhi(22) = 0;    yPhi(23) = 0;     yPhi(24) = 0;
    yPhi(25) = 0;      yPhi(26) = 0;      yPhi(27) = 0;      yPhi(28) = 1;    yPhi(29) = 0;     yPhi(30) = 0;
    yPhi(31) = 0;      yPhi(32) = 0;      yPhi(33) = 0;      yPhi(34) = 0;    yPhi(35) = 1;     yPhi(36) = 0;
    yPhi(37) = 0;      yPhi(38) = 0;      yPhi(39) = 0;      yPhi(40) = 0;    yPhi(41) = 0;     yPhi(42) = 1;

    cout<<transpose(yPhi);
    //cout<<transpose(VarEqn(x,yPhi));
	//cout<<eopdata;
	/*
    Matrix M1(3, 2);
	M1(1,1) = 5;
	
    Matrix M2(3, 2);
	M2(1,1) = -3;
	
    Matrix M3 = M1 - M2;

    cout << "M1\n" << M1 << "\n";
    cout << "M2\n" << M2 << "\n";
    cout << "M3\n" << M3 << "\n";
	
	cout << M1(1,1) << "\n";
	*/
}