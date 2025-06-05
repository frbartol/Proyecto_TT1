#include "..\include\SAT_Const.hpp"
#include "..\include\matrix.hpp"
#include "..\include\AccelPointMass.hpp"
#include "..\include\Cheb3D.hpp"
#include "..\include\EccAnom.hpp"
#include "..\include\Frac.hpp"
#include "..\include\MeanObliquity.hpp"
#include "..\include\Mjday.hpp"
#include "..\include\Mjday_TDB.hpp"
#include "..\include\Position.hpp"
#include "..\include\R_x.hpp"
#include "..\include\R_y.hpp"
#include "..\include\R_z.hpp"
#include "..\include\sign_.hpp"
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

#include <cstdio>
#include <cmath>

int tests_run = 0;

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

int m_equals(Matrix A, Matrix B, double p) {
	if (A.n_row != B.n_row || A.n_column != B.n_column)
		return 0;
	else
		for(int i = 1; i <= A.n_row; i++)
			for(int j = 1; j <= A.n_column; j++)
				if(fabs(A(i,j)-B(i,j)) > p) {
					printf("%2.20lf %2.20lf\n",A(i,j),B(i,j));
					return 0;
				}
	
	return 1;
}

int m_sum_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f, c);
	B(1,1) = 2; B(1,2) =  0; B(1,3) = 0; B(1,4) = 0;
	B(2,1) = 7; B(2,2) = -2; B(2,3) = 1; B(2,4) = 0;
	B(3,1) = 0; B(3,2) = -3; B(3,3) = 0; B(3,4) = 2;
	
	Matrix C(f, c);
	C(1,1) = 2; C(1,2) =  2; C(1,3) = 8; C(1,4) = 0;
	C(2,1) = 8; C(2,2) = -3; C(2,3) = 1; C(2,4) = 0;
	C(3,1) = 0; C(3,2) = -2; C(3,3) = 0; C(3,4) = 7;
	
	Matrix R = A + B;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_sub_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(f, c);
	B(1,1) = 2; B(1,2) = 0; B(1,3) = 0; B(1,4) = 0;
	B(2,1) = 7; B(2,2) = -2; B(2,3) = 1; B(2,4) = 0;
	B(3,1) = 0; B(3,2) = -3; B(3,3) = 0; B(3,4) = 2;
	
	Matrix C(f, c);
	C(1,1) = -2; C(1,2) = 2; C(1,3) = 8; C(1,4) = 0;
	C(2,1) = -6; C(2,2) = 1; C(2,3) = -1; C(2,4) = 0;
	C(3,1) = 0; C(3,2) = 4; C(3,3) = 0; C(3,4) = 3;
	
	Matrix R = A - B;
    
    _assert(m_equals(C, R, 1e-10));
    
    return 0;
}

int m_zeros_01() {
    int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) = 0; A(1,3) = 0; A(1,4) = 0;
	A(2,1) = 0; A(2,2) = 0; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 0; A(3,3) = 0; A(3,4) = 0;
	
	Matrix B = zeros(3, 4);
    
    _assert(m_equals(A, B, 1e-10));
    
    return 0;
}

int m_zerosSquare_01() {
    int f = 3;
	
	Matrix A(f);
	A(1,1) = 0; A(1,2) = 0; A(1,3) = 0;
	A(2,1) = 0; A(2,2) = 0; A(2,3) = 0;
	A(3,1) = 0; A(3,2) = 0; A(3,3) = 0;
	
	Matrix B = zeros(3);
    
    _assert(m_equals(A, B, 1e-10));
    
    return 0;
}

int m_mul_01(){
	int fa = 3, ca = 4;
	int fb = 4, cb = 2;
	int fc = 3, cc = 2;
	
	Matrix A(fa,ca);
	A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(fb,cb);
	
	B(1,1) = 1; B(1,2) = 0;
	B(2,1) = 0; B(2,2) = 1;
	B(3,1) = -1; B(3,2) = 0;
	B(4,1) = 0; B(4,2) = 1;
	
	Matrix C(fc,cc);
	
	C(1,1) = -8; C(1,2) = 2;
	C(2,1) = 1; C(2,2) = -1;
	C(3,1) = 0; C(3,2) = 6;
	
	Matrix R = A*B;
	
	_assert(m_equals(C, R, 1e-10));
	
	return 0;
}

int m_div_01(){
	int n = 2;
	Matrix A(n);
	A(1,1) = 10; A(1,2) = 6;
	A(2,1) = 4; A(2,2) = 2;

	Matrix B(n);
	B(1,1) = 2; B(1,2) = 0;
	B(2,1) = 1; B(2,2) = 1;

	Matrix C(n);
	C(1,1) = 2; C(1,2) = 6;
	C(2,1) = 1; C(2,2) = 2;

	Matrix R = A/B;
	_assert(m_equals(C,R,1e-10));

	return 0;
}

int m_asign_01(){
	int fa = 3, ca = 4;
	int fb = 4, cb = 2;

	Matrix A(fa,ca);
	A(1,1) = 0; A(1,2) = 2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) = 1; A(3,3) = 0; A(3,4) = 5;
	
	Matrix B(fb,cb);
	
	B(1,1) = 1; B(1,2) = 0;
	B(2,1) = 0; B(2,2) = 1;
	B(3,1) = -1; B(3,2) = 0;
	B(4,1) = 0; B(4,2) = 1;

	B=A;

	_assert(m_equals(A,B,1e-10));

	return 0;
}

int m_sumScalar_01(){
	int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;

	Matrix B(f,c);
	B(1,1) = 2; B(1,2) =  4; B(1,3) = 10; B(1,4) = 2;
	B(2,1) = 3; B(2,2) =  1; B(2,3) = 2; B(2,4) = 2;
	B(3,1) = 2; B(3,2) =  3; B(3,3) = 2; B(3,4) = 7;

	Matrix R=A+2;
	_assert(m_equals(B,R,1e-10));

	return 0;
}

int m_subScalar_01(){
	int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;

	Matrix B(f,c);
	B(1,1) = -2; B(1,2) =  0; B(1,3) = 6; B(1,4) = -2;
	B(2,1) = -1; B(2,2) =  -3; B(2,3) = -2; B(2,4) = -2;
	B(3,1) = -2; B(3,2) =  -1; B(3,3) = -2; B(3,4) = 3;

	Matrix R=A-2;
	_assert(m_equals(B,R,1e-10));

	return 0;
}

int m_mulScalar_01(){
	int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;

	Matrix B(f,c);
	B(1,1) = 0; B(1,2) =  4; B(1,3) = 16; B(1,4) = 0;
	B(2,1) = 2; B(2,2) =  -2; B(2,3) = 0; B(2,4) = 0;
	B(3,1) = 0; B(3,2) =  2; B(3,3) = 0; B(3,4) = 10;

	Matrix R=A*2;
	_assert(m_equals(B,R,1e-10));

	return 0;
}

int m_divScalar_01(){
	int f = 3;
    int c = 4;
	
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;

	Matrix B(f,c);
	B(1,1) = 0; B(1,2) =  1; B(1,3) = 4; B(1,4) = 0;
	B(2,1) = 0.5; B(2,2) = -0.5; B(2,3) = 0; B(2,4) = 0;
	B(3,1) = 0; B(3,2) =  0.5; B(3,3) = 0; B(3,4) = 2.5;

	Matrix R=A/2;
	_assert(m_equals(B,R,1e-10));

	return 0;
}

int m_transpose_01(){
	int f = 3;
    int c = 4;
	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;

	Matrix B(c, f);
	B(1,1) = 0;  B(1,2) = 1;  B(1,3) = 0;
	B(2,1) = 2;  B(2,2) = -1; B(2,3) = 1;
	B(3,1) = 8;  B(3,2) = 0;  B(3,3) = 0;
	B(4,1) = 0;  B(4,2) = 0;  B(4,3) = 5;

	Matrix R=transpose(A);
	_assert(m_equals(R,B,1e-10));

	return 0;
}

int m_inv_01(){
	int n=3;
	Matrix A(n);
	A(1,1) = 2; A(1,2) =  1; A(1,3) = 1; 
	A(2,1) = 1; A(2,2) = 3; A(2,3) = 2; 
	A(3,1) = 1; A(3,2) =  0; A(3,3) = 0;

	Matrix B(n);
	B(1,1) = 0; B(1,2) =  0; B(1,3) = 1; 
	B(2,1) = -2; B(2,2) = 1; B(2,3) = 3; 
	B(3,1) = 3; B(3,2) =  -1; B(3,3) = -5;

	Matrix R = inv(A);
	_assert(m_equals(R,B,1e-10));

	return 0;
}

int m_norm_01(){
	int n= 2;
	Matrix A(n);
	A(1,1) = 3; A(1,2) = 4; 
	A(2,1) = 0; A(2,2) = 5;

	double r= sqrt(3*3 + 4*4 + 0*0 + 5*5);

	_assert(fabs(A.norm()-r)<1e-10);

	return 0;
}

int m_dot_01(){
	int f = 1, c = 3;

	Matrix A(1,3);
	A(1,1)= 1; A(1,2)= 2; A(1,3)= 2; 

	Matrix B(1,3);
	B(1,1)= 4; B(1,2)= -5; B(1,3)= 6; 

	_assert(fabs(6-A.dot(B))<1e-10);

	return 0;
}

int m_cross_01(){
	int f = 1;
	int c = 3;

	Matrix A(f,c);
	A(1,1) = 1; A(1,2) = 2; A(1,3) = 3; 

	Matrix B(f,c);
	B(1,1) = 4; B(1,2) = 5; B(1,3) = 6;

	Matrix R(f,c);
	R(1,1) = -3; R(1,2) = 6; R(1,3) = -3;

	_assert(m_equals(A.cross(B),R,1e-10));

	return 0;
}

int m_extract_vector_01(){
	int f = 3;
	int c = 4;

	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;

	Matrix B(1,6);
	B(1,1) = 2; B(1,2) = 8; B(1,3) = 0; B(1,4) = 1; B(1,5) = -1; B(1,6) = 0;
	
	Matrix R = A.extract_vector(2,7);

	_assert(m_equals(B,R,1e-10));

	return 0;
}

int m_union_vector_01(){
	Matrix A(1,3);
	A(1,1) = 1; A(1,2) = 2; A(1,3) = 3; 

	Matrix B(1,4);
	B(1,1) = 4; B(1,2) = 5; B(1,3) = 6; B(1,4) = 7;

	Matrix C(1,7);
	C(1,1) = 4; C(1,2) = 5; C(1,3) = 6; C(1,4) = 7; C(1,5) = 1; C(1,6) = 2; C(1,7) = 3;

	Matrix R = B.union_vector(A);

	_assert(m_equals(C,R,1e-10));
	return 0;
}

int m_extract_row_01(){
	int f = 3;
	int c = 4;

	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;

	Matrix B(1, c);
	B(1,1) = 1; B(1,2) = -1; B(1,3) = 0; B(1,4) = 0;

	Matrix R = A.extract_row(2);

	_assert(m_equals(B,R,1e-10));
	return 0;
}

int m_extract_column_01(){
	int f = 3;
	int c = 4;

	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;

	Matrix B(f,1);
	B(1,1) = 2;
	B(2,1) = -1;
	B(3,1) = 1;

	Matrix R = A.extract_column(2);

	_assert(m_equals(B,R,1e-10));
	return 0;
}

int m_asign_row_01(){
	int f = 3;
	int c = 4;

	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;

	Matrix B(1,c);
	B(1,1) = 8; B(1,2) = 8; B(1,3) = 8; B(1,4) = 8;

	Matrix C(f,c);
	C(1,1) = 0; C(1,2) =  2; C(1,3) = 8; C(1,4) = 0;
	C(2,1) = 8; C(2,2) = 8; C(2,3) = 8; C(2,4) = 8;
	C(3,1) = 0; C(3,2) =  1; C(3,3) = 0; C(3,4) = 5;

	A.asign_row(2,B);

	_assert(m_equals(A,C,1e-10));
	return 0;
}

int m_asign_column_01(){
	int f = 3;
	int c = 4;

	Matrix A(f, c);
	A(1,1) = 0; A(1,2) =  2; A(1,3) = 8; A(1,4) = 0;
	A(2,1) = 1; A(2,2) = -1; A(2,3) = 0; A(2,4) = 0;
	A(3,1) = 0; A(3,2) =  1; A(3,3) = 0; A(3,4) = 5;

	Matrix B(f,1);
	B(1,1) = 9;
	B(2,1) = 9;
	B(3,1) = 9;

	Matrix C(f, c);
	C(1,1) = 0; C(1,2) =  9; C(1,3) = 8; C(1,4) = 0;
	C(2,1) = 1; C(2,2) = 9; C(2,3) = 0; C(2,4) = 0;
	C(3,1) = 0; C(3,2) =  9; C(3,3) = 0; C(3,4) = 5;

	A.asign_column(2,B);

	_assert(m_equals(A,C,1e-10));
	return 0;
}

int i1_accel_point_mass_01(){
	double GM = 3.986004418e14;
	int f = 1;
	int c = 3;
	Matrix r(f,c);
	r(1,1)= 7000000; r(1,2)= 0; r(1,3)= 0;

	Matrix s(f,c);
	s(1,1)= 0; s(1,2)= 6371000; s(1,3)= 0;

	Matrix a = AccelPointMass(r,s,GM);

	Matrix C(f,c);
	C(1,1)= -3.2904032183; C(1,2)= -6.8255135008; C(1,3)= 0;

	_assert(m_equals(a,C,1e-10));
	return 0;
}

int i1_cheb3d_01(){
	int f = 1;
	int c = 5;
	Matrix Cx(f,c);
	Cx(1,1) = 1; Cx(1,2) = 0.5; Cx(1,3) = 0.2; Cx(1,4) = 0.1; Cx(1,5) = 0.05; 
	
	Matrix Cy(f,c);
	Cy(1,1) = 0.8; Cy(1,2) = 0.3; Cy(1,3) = 0.15; Cy(1,4) = 0.07; Cy(1,5) = 0.03;

	Matrix Cz(f,c);
	Cz(1,1) = 0.6; Cz(1,2) = 0.4; Cz(1,3) = 0.1; Cz(1,4) = 0.05; Cz(1,5) = 0.02;

	Matrix ChebApp = Cheb3D(0.5,5,0,1,Cx,Cy,Cz);

	Matrix R(1,3);
	R(1,1) = 0.8500000000; R(1,2) = 0.6800000000; R(1,3) = 0.5200000000;

	_assert(m_equals(ChebApp,R,1e-10));
	return 0;
}

int i1_eccanon_01(){
	double M = 0.5;
	double e = 0.1;

	_assert(fabs(0.5524799869-EccAnom(M,e))<1e-10);
	return 0;
}

int i1_frac_01(){
	double x = -3.700000;
	double r = 0.3;

	_assert(fabs(r-Frac(x))<1e-10);
	return 0;
}

int i1_meanobliquity_01(){
	double Mjd_TT = 51544.5;
	double r = 0.4090928042;

	_assert(fabs(r-MeanObliquity(Mjd_TT))<1e-10);
	return 0;
}

int i1_mjday_01(){
	int yr = 2000;
	int mon = 1;
	int day = 1;
	int hr = 12;
	int min = 30;
	double sec = 45.5;

	double r = 51544.5213599536;

	_assert(fabs(r-Mjday(yr,mon,day,hr,min,sec))<1e-10);

	return 0;
}

int i1_mjday_tdb_01(){ // probar en matlab
	double Mjd_TT = 51544.5;
	
	double r = 51544.5000000247;

	_assert(fabs(r-Mjday_TDB(Mjd_TT))<1e-6);
	return 0;
}

int i1_position_01(){ //probar en matlab
	double lon = 0.0;
	double lat = 0.0;
	double h = 0.0;

	Matrix r(1,3);
	r(1,1) = 6378136.2999999998;
	r(1,2) = 0;
	r(1,3) = 0;

	_assert(m_equals(r,Position(lon,lat,h),1e-10));
	return 0;
}

int i1_rx_01(){
	double angle = SAT_Const::pi/4;
	Matrix& rotmat = R_x(angle);
	Matrix r(3,3);
	r(1,1) = 1.0000000000; r(1,2) = 0.0000000000; r(1,3) = 0.0000000000; 
	r(2,1) = 0.0000000000; r(2,2) = 0.7071067812; r(2,3) = 0.7071067812; 
	r(3,1) = 0.0000000000; r(3,2) = -0.7071067812; r(3,3) = 0.7071067812; 

	_assert(m_equals(r,rotmat,1e-10));
	return 0;
}

int i1_ry_01(){
	double angle = SAT_Const::pi/4;
	Matrix& rotmat = R_y(angle);
	Matrix r(3,3);
	r(1,1) = 0.7071067812; r(1,2) = 0.0000000000; r(1,3) = -0.7071067812; 
	r(2,1) = 0.0000000000; r(2,2) = 1.0000000000; r(2,3) = 0.0000000000; 
	r(3,1) = 0.7071067812; r(3,2) = 0.0000000000; r(3,3) = 0.7071067812; 

	_assert(m_equals(r,rotmat,1e-10));
	return 0;
}

int i1_rz_01(){
	double angle = SAT_Const::pi/4;
	Matrix& rotmat = R_z(angle);
	Matrix r(3,3);
	r(1,1) = 0.7071067812; r(1,2) = 0.7071067812; r(1,3) = 0.0000000000; 
	r(2,1) = -0.7071067812; r(2,2) = 0.7071067812; r(2,3) = 0.0000000000; 
	r(3,1) = 0.0000000000; r(3,2) = 0.0000000000; r(3,3) = 1.0000000000; 

	_assert(m_equals(r,rotmat,1e-10));
	return 0;
}

int i1_sign_01(){
	_assert(fabs(-2-sign_(2,-3))<1e-10);
	return 0;
}

int i1_timediff_01(){
	auto result = timediff(-0.5,36);
	_assert(fabs(-36.5000000000-get<0>(result))<1e-10);
	_assert(fabs(-17.0000000000-get<1>(result))<1e-10);
	_assert(fabs(-17.5000000000-get<2>(result))<1e-10);
	_assert(fabs(68.1840000000-get<3>(result))<1e-10);
	_assert(fabs(17.0000000000-get<4>(result))<1e-10);
	return 0;
}

int i1_AzElPa_01(){
	Matrix s(1,3);
	s(1,1) = 1.0;
	s(1,2) = 1.0;
	s(1,3) = 1.0;

	auto result = AzElPa(s);

	Matrix dAds(1,3);
	dAds(1,1) = 0.5;
	dAds(1,2) = -0.5;
	dAds(1,3) = 0.0;

	Matrix dEds(1,3);
	dEds(1,1) = -0.2357022604;
	dEds(1,2) = -0.2357022604;
	dEds(1,3) = 0.4714045208;

	_assert(fabs(0.7853981634-get<0>(result))<1e-10);
	_assert(fabs(0.6154797087-get<1>(result))<1e-10);
	_assert(m_equals(dAds, get<2>(result), 1e-10));
	_assert(m_equals(dEds, get<3>(result), 1e-10));

	return 0;
}

int i1_iers_01(){
	Matrix& eop = zeros(13,2);
	eop(4,1) = 51544; eop(4,2) = 51545;
	eop(5,1) = 0.1; eop(5,2) = 0.2;
	eop(6,1) = 0.3; eop(6,2) = 0.4;
	eop(7,1) = -0.5; eop(7,2) = -0.6;
	eop(8,1) = 0.001; eop(8,2) = 0.002;
	eop(9,1) = -0.05; eop(9,2) = -0.06;
	eop(10,1) = 0.02; eop(10,2) = 0.03;
	eop(11,1) = 0.01; eop(11,2) = 0.02;
	eop(12,1) = 0.03; eop(12,2) = 0.04;
	eop(13,1) = 36.0; eop(13,2) = 36.0;

	double Mjd_UTC = 51544.5;
	auto result = IERS(eop, Mjd_UTC, 'n');

	_assert(fabs(0.0000004848-get<0>(result))<1e-10);
	_assert(fabs(0.0000014544-get<1>(result))<1e-10);
	_assert(fabs(-0.5-get<2>(result))<1e-10);
	_assert(fabs(0.001-get<3>(result))<1e-10);
	_assert(fabs(-0.0000002424-get<4>(result))<1e-10);
	_assert(fabs(0.0000000970-get<5>(result))<1e-10);
	_assert(fabs(0.0000000485-get<6>(result))<1e-10);
	_assert(fabs(0.0000001454-get<7>(result))<1e-10);
	_assert(fabs(36.0-get<8>(result))<1e-10);
	return 0;
}

int i1_iers_02(){
	Matrix& eop = zeros(13,2);
	eop(4,1) = 51544; eop(4,2) = 51545;
	eop(5,1) = 0.1; eop(5,2) = 0.2;
	eop(6,1) = 0.3; eop(6,2) = 0.4;
	eop(7,1) = -0.5; eop(7,2) = -0.6;
	eop(8,1) = 0.001; eop(8,2) = 0.002;
	eop(9,1) = -0.05; eop(9,2) = -0.06;
	eop(10,1) = 0.02; eop(10,2) = 0.03;
	eop(11,1) = 0.01; eop(11,2) = 0.02;
	eop(12,1) = 0.03; eop(12,2) = 0.04;
	eop(13,1) = 36.0; eop(13,2) = 36.0;

	double Mjd_UTC = 51544.5;
	auto result = IERS(eop, Mjd_UTC, 'l');

	_assert(fabs(0.0000007272-get<0>(result))<1e-10);
	_assert(fabs(0.0000016968-get<1>(result))<1e-10);
	_assert(fabs(-0.55-get<2>(result))<1e-10);
	_assert(fabs(0.0015-get<3>(result))<1e-10);
	_assert(fabs(-0.0000002666-get<4>(result))<1e-10);
	_assert(fabs(0.0000001212-get<5>(result))<1e-10);
	_assert(fabs(0.0000000727-get<6>(result))<1e-10);
	_assert(fabs(0.0000001697-get<7>(result))<1e-10);
	_assert(fabs(36.0-get<8>(result))<1e-10);
	return 0;
}

int i1_legendre_01(){
	int n = 1;
	int m = 2;
	double fi = SAT_Const::pi/4;

	auto result = Legendre(n,m,fi);
	Matrix pnm(2,3);
	pnm(1,1) = 1.0; pnm(1,2) = 0.0; pnm(1,3) = 0.0;
	pnm(2,1) = 1.2247448714; pnm(2,2) = 1.2247448714; pnm(2,3) = 0.0;

	Matrix dpnm(2,3);
	dpnm(1,1) = 0.0; dpnm(1,2) = 0.0; dpnm(1,3) = 0.0;
	dpnm(2,1) = 1.2247448714; dpnm(2,2) = -1.2247448714; dpnm(2,3) = 0.0;

	_assert(m_equals(pnm, get<0>(result),1e-10));
	_assert(m_equals(dpnm, get<1>(result),1e-10));
	return 0;
}

int i1_nutangles_01(){
	double Mjd_TT = 58849.0;

	auto result = NutAngles(Mjd_TT);
	double dpsi = -0.0000799279;
	double deps = -0.0000082772;

	_assert(fabs(dpsi-get<0>(result))<1e-10);
	_assert(fabs(deps-get<1>(result))<1e-10);
	return 0;
}

int i1_timeupdate_01(){
	Matrix& P = zeros(2);
	P(1,1) = 1.5; P(1,2) = 0.2;
	P(2,1) = 0.2; P(2,2) = 1.0;

	Matrix& Phi = zeros(2);
	Phi(1,1) = 1.0; Phi(1,2) = 0.1;
	Phi(2,1) = 0.0; Phi(2,2) = 1.0;

	double Qdt = 0.1;

	Matrix& newP = zeros(2);
	newP(1,1) = 1.65; newP(1,2) = 0.4;
	newP(2,1) = 0.4; newP(2,2) = 1.1;

	_assert(m_equals(newP,TimeUpdate(P,Phi,Qdt),1e-10));
	return 0;
	
}

int i2_accelharmonic_01(){
	Matrix& r = zeros(1,3);
	r(1,1) = 7078.1363e3;
	r(1,2) = 0;
	r(1,3) = 0;

	Matrix& E = eye(3);

	double n_max_test = 10;
	double m_max_test = 10;

	Matrix& result = zeros(1,3);
	result(1,1) = -7.96666584966782;
	result(1,2) = -1.5109436138171e-05;
	result(1,3) = 2.9539528788116e-05;

	_assert(m_equals(result,AccelHarmonic(r,E,n_max_test, m_max_test),1e-10));
	return 0;
}

int i2_eqnequinox_01(){
	_assert(fabs(-4.31830493518006e-05 - EqnEquinox(58000.12345678)));
	return 0;
}

int i2_jplephde430_01(){
	auto [r_Mercury,r_Venus,r_Earth,r_Mars,r_Jupiter,r_Saturn,r_Uranus, r_Neptune,r_Pluto,r_Moon,r_Sun] = JPL_Eph_DE430(59948.0);

	Matrix& exp_Mercury = zeros(1,3);
	exp_Mercury(1) = 37474811331.4849777222;
	exp_Mercury(2) = -90853200205.3267974854;
	exp_Mercury(3) = -35738960751.6226959229;
	_assert(m_equals(exp_Mercury, r_Mercury, 1e-10));

	Matrix& exp_Venus = zeros(1,3);
	exp_Venus(1) = 122526574967.4041137695;
	exp_Venus(2) = -185957969420.2913208008;
	exp_Venus(3) = -87162380032.1979675293;
	_assert(m_equals(exp_Venus, r_Venus, 1e-10));

	Matrix& exp_Earth = zeros(1,3);
	exp_Earth(1) = -34512445228.7528152466;
	exp_Earth(2) = 131487140006.5218505859;
	exp_Earth(3) = 57032802033.2604370117;
	_assert(m_equals(exp_Earth, r_Earth, 1e-10));

	Matrix& exp_Mars = zeros(1,3);
	exp_Mars(1) = 36225476108.1189041138;
	exp_Mars(2) = 81717257992.2647094727;
	exp_Mars(3) = 40711189737.0723114014;
	_assert(m_equals(exp_Mars, r_Mars, 1e-10));

	Matrix& exp_Jupiter = zeros(1,3);
	exp_Jupiter(1) = 756182955791.8770751953;
	exp_Jupiter(2) = 21855341833.6717834473;
	exp_Jupiter(3) = -8871389658.5872344971;
	_assert(m_equals(exp_Jupiter, r_Jupiter, 1e-10));

	Matrix& exp_Saturn = zeros(1,3);
	exp_Saturn(1) = 1253250658157.5458984375;
	exp_Saturn(2) = -871551371453.2583007812;
	exp_Saturn(3) = -415209753505.8096313477;
	_assert(m_equals(exp_Saturn, r_Saturn, 1e-10));

	Matrix& exp_Uranus = zeros(1,3);
	exp_Uranus(1) = 2031934646845.7473144531;
	exp_Uranus(2) = 1856816576287.4799804688;
	exp_Uranus(3) = 785539496767.8784179688;
	_assert(m_equals(exp_Uranus, r_Uranus, 1e-10));

	Matrix& exp_Neptune = zeros(1,3);
	exp_Neptune(1) = 4485448149454.5195312500;
	exp_Neptune(2) = -496882946711.2616577148;
	exp_Neptune(3) = -317403838347.0413818359;
	_assert(m_equals(exp_Neptune, r_Neptune, 1e-10));

	Matrix& exp_Pluto = zeros(1,3);
	exp_Pluto(1) = 2454452075393.5581054688;
	exp_Pluto(2) = -4253417375436.2500000000;
	exp_Pluto(3) = -2072482064861.6914062500;
	_assert(m_equals(exp_Pluto, r_Pluto, 1e-10));

	Matrix& exp_Moon = zeros(1,3);
	exp_Moon(1) = 133734596.5636594296;
	exp_Moon(2) = 339095411.8405320048;
	exp_Moon(3) = 165815677.7021569312;
	_assert(m_equals(exp_Moon, r_Moon, 1e-10));

	Matrix& exp_Sun = zeros(1,3);
	exp_Sun(1) = 33158353911.4335060120;
	exp_Sun(2) = -131490279354.1122131348;
	exp_Sun(3) = -56999884478.6396255493;
	_assert(m_equals(exp_Sun, r_Sun, 1e-10));

	return 0;
}

int i2_ltc_01(){
	Matrix& r = zeros(3);
	r(1) = 0.800354635326713; r(2) = -0.599526861542536; r(3) = 0.0;
	r(4) = 0.596030256591891; r(5) = 0.795686747764587; r(6) = 0.107844947303148;
	r(7) = -0.0646559427898768; r(8) = -0.08631420347064; r(9) = 0.994167725960354;

	_assert(m_equals(r,LTC(123.45, -23.67),1e-10));
	return 0;
}

int i2_nutmatrix_01(){
	Matrix& r = zeros(3);
	r(1) = 0.999999996769734; r(2) = -7.37348554646969e-05; r(3) = -3.19953577384509e-05;
	r(4) = 7.37347961892059e-05; r(5) = 0.999999997279872; r(6) = -1.85380348782793e-06;
	r(7) = 3.19954943413517e-05; r(8) = 1.85144431064099e-06; r(9) = 0.99999999948643;

	_assert(m_equals(r,NutMatrix(1234.56789),1e-10));
	return 0;
}

int i2_polematrix_01(){
	Matrix& r = zeros(3);
	r(1) = 0.999993875006253; r(2) = -7.34997959152141e-06; r(3) = 0.00349998513668964;
	r(4) = 0; r(5) = 0.99999779500081; r(6) = 0.00209999845650034;
	r(7) = -0.00349999285417104; r(8) = -0.00209998559402292; r(9) = 0.999991670020569;

	_assert(m_equals(r,PoleMatrix(0.0035, -0.0021),1e-1));
	return 0;
}

int i2_precmatrix_01(){
	Matrix& r = zeros(3);
	r(1) = 0.999999776973167; r(2) = -0.000612558151695768; r(3) = -0.000266131783951279;
	r(4) = 0.000612558151695665; r(5) = 0.999999812386234; r(6) = -8.15109896675957e-08;
	r(7) = 0.000266131783951514; r(8) = -8.15102221962074e-08; r(9) = 0.999999964586933;

	_assert(m_equals(r, PrecMatrix(58000.12345, 59000.54321), 1e-10));
	return 0;
}

int i2_gmst_01(){
	_assert(fabs(3.13108955996666-gmst(58000.54321))<1e-10);
	return 0;
}

int i3_gast_01(){
	_assert(fabs(3.13104627466474-gast(58000.54321))<1e-10);
	return 0;
}

int i3_measupdate_01(){

    const int n = 1;
    Matrix x(n, 1);
    x(1,1) = 2.0;
    
    Matrix P = eye(n);
    P(1,1) = 1.0;
    
    double z = 3.0;
    double g = 2.5;
    double s = 0.5;
    
    Matrix G(1, n);
    G(1,1) = 1.0;
    
    auto [K, x_updated, P_updated] = MeasUpdate(x, z, g, s, G, P, n);

    double expected_K = 0.8;       
    double expected_x = 2.4;        
    double expected_P = 0.2;      
    
    const double tolerance = 1e-6;

    
    _assert(fabs(K(1,1) - expected_K) < tolerance);
    _assert(fabs(x_updated(1,1) - expected_x) < tolerance); 
    _assert(fabs(P_updated(1,1) - expected_P) < tolerance);

    return 0;
}

int i3_gaccelharmonic_01(){
	Matrix& r = zeros(1,3);
    r(1) = 7000e3; r(2) = 0; r(3) = 0;

    Matrix& U = eye(3);

    int n_max = 4;
    int m_max = 4;

	Matrix& result = zeros(3);
	result(1) = 0.233048175246609; result(2) = -0.000001880628986; result(3) = -0.000005189093599;
	result(4) = -0.000001880403020;   result(5) = -0.116369304011321; result(6) = -0.000000590145164;
	result(7) = -0.000005189005889;   result(8) = -0.000000590145165; result(9) = -0.116678871423607;

	result = result*1e-5;

	_assert(m_equals(result,G_AccelHarmonic(r,U,n_max,m_max),1e-10));
	return 0;
}

int i3_ghamatrix_01(){
	Matrix& r = zeros(3);
	r(1) = -0.999944387461251; r(2) =  0.010546183420693; r(3) = 0.0;
	r(4) = -0.010546183420693; r(5) = -0.999944387461251; r(6) = 0.0;
	r(7) =  0.0;                r(8) =  0.0;                r(9) = 1.0;

	_assert(m_equals(r,GHAMatrix(58000.54321),1e-10));
	return 0;
}

int i3_accel_01(){
	double x = 3600;
    Matrix& Y = zeros(1,6);
    Y(1) = 7000e3;
    Y(2) = 0;
    Y(3) = 0;
    Y(4) = 0;
    Y(5) = 7.5e3;
    Y(6) = 0;

	Matrix& result = zeros(1,6);
	result(1) = 0.0;             result(2) = 7.500000000000000; result(3) = 0.0;
	result(4) = -0.008145746493786; result(5) = -0.000000071640030; result(6) = -0.000000049183314;

	result = result*1e3;

	_assert(m_equals(result,Accel(x,Y),1e-10));
	return 0;
}

int i3_vareqn_01(){
	double x = 3600;
    Matrix& yPhi = zeros(1,42);
    yPhi(1) = 7000000; yPhi(2) = 0;       yPhi(3) = 0;       yPhi(4) = 0;     yPhi(5) = 7500;   yPhi(6) = 0;
    yPhi(7) = 1;       yPhi(8) = 0;       yPhi(9) = 0;       yPhi(10) = 0;    yPhi(11) = 0;     yPhi(12) = 0;
    yPhi(13) = 0;      yPhi(14) = 1;      yPhi(15) = 0;      yPhi(16) = 0;    yPhi(17) = 0;     yPhi(18) = 0;
    yPhi(19) = 0;      yPhi(20) = 0;      yPhi(21) = 1;      yPhi(22) = 0;    yPhi(23) = 0;     yPhi(24) = 0;
    yPhi(25) = 0;      yPhi(26) = 0;      yPhi(27) = 0;      yPhi(28) = 1;    yPhi(29) = 0;     yPhi(30) = 0;
    yPhi(31) = 0;      yPhi(32) = 0;      yPhi(33) = 0;      yPhi(34) = 0;    yPhi(35) = 1;     yPhi(36) = 0;
    yPhi(37) = 0;      yPhi(38) = 0;      yPhi(39) = 0;      yPhi(40) = 0;    yPhi(41) = 0;     yPhi(42) = 1;

	Matrix& result = zeros(1, 42);
	result(1)  = 0;
	result(2)  = 7500;
	result(3)  = 0;
	result(4)  = -8.14573205035272;
	result(5)  = -2.73247066264748e-05;
	result(6)  = -1.83319533570083e-05;
	result(7)  = 0;
	result(8)  = 0;
	result(9)  = 0;
	result(10) = 2.33048819886505e-06;
	result(11) = -2.23201457316691e-11;
	result(12) = 2.14778542173555e-12;
	result(13) = 0;
	result(14) = 0;
	result(15) = 0;
	result(16) = -2.23252527575823e-11;
	result(17) = -1.16365971392085e-06;
	result(18) = 2.16918540421607e-11;
	result(19) = 0;
	result(20) = 0;
	result(21) = 0;
	result(22) = 2.1440627051561e-12;
	result(23) = 2.16913154105214e-11;
	result(24) = -1.1668284973388e-06;
	result(25) = 1;
	result(26) = 0;
	result(27) = 0;
	result(28) = 0;
	result(29) = 0;
	result(30) = 0;
	result(31) = 0;
	result(32) = 1;
	result(33) = 0;
	result(34) = 0;
	result(35) = 0;
	result(36) = 0;
	result(37) = 0;
	result(38) = 0;
	result(39) = 1;
	result(40) = 0;
	result(41) = 0;
	result(42) = 0;
    
	_assert(m_equals(result,VarEqn(x,yPhi),1e-10));

	return 0;
}

int all_tests()
{
    _verify(m_sum_01);
    _verify(m_sub_01);
    _verify(m_zeros_01);
	_verify(m_zerosSquare_01);
	_verify(m_mul_01);
	_verify(m_div_01);
	_verify(m_asign_01);
	_verify(m_sumScalar_01);
	_verify(m_subScalar_01);
	_verify(m_mulScalar_01);
	_verify(m_divScalar_01);
	_verify(m_transpose_01);
	_verify(m_inv_01);
	_verify(m_norm_01);
	_verify(m_dot_01);
	_verify(m_cross_01);
	_verify(m_extract_vector_01);
	_verify(m_union_vector_01);
	_verify(m_extract_row_01);
	_verify(m_extract_column_01);
	_verify(m_asign_row_01);
	_verify(m_asign_column_01);
	_verify(i1_accel_point_mass_01);
	_verify(i1_cheb3d_01);
	_verify(i1_eccanon_01);
	_verify(i1_frac_01);
	_verify(i1_meanobliquity_01);
	_verify(i1_mjday_01);
	_verify(i1_mjday_tdb_01);
	_verify(i1_position_01);
	_verify(i1_rx_01);
	_verify(i1_ry_01);
	_verify(i1_rz_01);
	_verify(i1_sign_01);
	_verify(i1_timediff_01);
	_verify(i1_AzElPa_01);
	_verify(i1_iers_01);
	_verify(i1_iers_02);
	_verify(i1_legendre_01);
	_verify(i1_nutangles_01);
	_verify(i1_timeupdate_01);
	_verify(i2_accelharmonic_01);
	_verify(i2_eqnequinox_01);
	_verify(i2_jplephde430_01);
	_verify(i2_ltc_01);
	_verify(i2_nutmatrix_01);
	_verify(i2_polematrix_01);
	_verify(i2_precmatrix_01);
	_verify(i2_gmst_01);
	_verify(i3_gast_01);
	_verify(i3_measupdate_01);
	_verify(i3_gaccelharmonic_01);
	_verify(i3_ghamatrix_01);
	_verify(i3_accel_01);
	_verify(i3_vareqn_01);

    return 0;
}


int main()
{
	eop19620101(21413);
	GGM03S(181);
	DE430Coeff(2285, 1020);
	initializeAuxParam();
    int result = all_tests();

    if (result == 0)
        printf("PASSED\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
