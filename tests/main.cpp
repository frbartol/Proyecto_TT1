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
#include <tuple>
#include <iostream>

using namespace std;

int main() {
	eop19620101(21413);
	GGM03S(181);
	DE430Coeff(2285, 1020);
	
	Matrix& r = zeros(3,1);
	r(1) = 7078.1363e3;
	r(2) = 0;
	r(3) = 0;

	Matrix& E = eye(3);

	double n_max_test = 10;
	double m_max_test = 10;
	cout<<AccelHarmonic(r,E,n_max_test, m_max_test);
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