/**
 * @file R_z.cpp
 * @brief Implementación de la matriz de rotación respecto al eje Z.
 * @author Francisco Bartolome Alcalde
 */

#include "..\include\R_z.hpp"

Matrix& R_z(double angle){
	double C,S;
	C = cos(angle);
	S = sin(angle);
	Matrix& rotmat = zeros(3,3);

	rotmat(1,1) =      C;  rotmat(1,2) =   S;  rotmat(1,3) = 0.0;
    rotmat(2,1) = -1.0*S;  rotmat(2,2) =   C;  rotmat(2,3) = 0.0;
    rotmat(3,1) =    0.0;  rotmat(3,2) = 0.0;  rotmat(3,3) = 1.0;
	return rotmat;
}