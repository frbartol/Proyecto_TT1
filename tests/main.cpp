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
	int n=3;
	Matrix A(n);
	A(1,1) = 2; A(1,2) =  1; A(1,3) = 1; 
	A(2,1) = 1; A(2,2) = 3; A(2,3) = 2; 
	A(3,1) = 1; A(3,2) =  0; A(3,3) = 0;
	for(int i=1; i<=9; i++){
		cout<<A(i)<<" ";
		if(i%3==0){
			cout<<"\n";
		}
	}
}