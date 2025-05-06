#include "..\include\matrix.hpp"
#include "..\include\AccelPointMass.hpp"
#include "..\include\Cheb3d.hpp"
#include <iostream>

using namespace std;

int main() {
	//eop19620101(4);
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
	double GM = 3.986004418e14;
	int f = 1;
	int c = 5;
	Matrix Cx(f,c);
	Cx(1,1) = 1; Cx(1,2) = 0.5; Cx(1,3) = 0.2; Cx(1,4) = 0.1; Cx(1,5) = 0.05; 
	
	Matrix Cy(f,c);
	Cy(1,1) = 0.8; Cy(1,2) = 0.3; Cy(1,3) = 0.15; Cy(1,4) = 0.07; Cy(1,5) = 0.03;

	Matrix Cz(f,c);
	Cz(1,1) = 0.6; Cz(1,2) = 0.4; Cz(1,3) = 0.1; Cz(1,4) = 0.05; Cz(1,5) = 0.02;

	Matrix ChebApp = Cheb3D(0.5,5,0,1,Cx,Cy,Cz);

	cout<<ChebApp;
}