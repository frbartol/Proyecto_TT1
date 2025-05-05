#include "..\include\matrix.hpp"
#include "..\include\AccelPointMass.hpp"
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
	int c = 3;
	Matrix r(f,c);
	r(1,1)= 7000000; r(1,2)= 0; r(1,3)= 0;

	Matrix s(f,c);
	s(1,1)= 0; s(1,2)= 6371000; s(1,3)= 0;

	cout<<AccelPointMass(r,s,GM);
}