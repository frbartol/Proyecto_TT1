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

    return 0;
}


int main()
{
	eop19620101(21413);
	GGM03S(181);
	DE430Coeff(2285, 1020);
    int result = all_tests();

    if (result == 0)
        printf("PASSED\n");

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
