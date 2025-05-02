#include "..\include\matrix.hpp"
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
	int f = 1, c = 3;

	Matrix A(1,3);
	A(1,1)= 1; A(1,1)= 2; A(1,1)= 2; 

	Matrix B(1,3);
	B(1,1)= 4; B(1,1)= -5; B(1,1)= 6; 

	cout<<A.dot(B);
}