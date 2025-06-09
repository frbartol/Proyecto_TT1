#ifndef _DEINTEG_
#define _DEINTEG_

#include "matrix.hpp"
#include "SAT_Const.hpp"
#include "sign_.hpp"

Matrix& DEInteg(Matrix& func(double, Matrix&), double t, double tout, double relerr, double abserr, int n_eqn, Matrix& y);

#endif