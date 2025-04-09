#include "..\include\R_x.hpp"

Matrix R_x(double angel){
	double C = cos(angle);
	double S = sin(angle);
	Matrix rotmant = zeros(3,3);
	rotmat (1,1