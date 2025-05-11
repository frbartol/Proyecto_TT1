#ifndef _IERS_
#define _IERS_

#include <tuple>
#include "matrix.hpp"
#include "SAT_Const.hpp"

tuple<double, double, double, double, double, double, double, double, double> IERS(Matrix& eop, double Mjd_UTC, char interp);

#endif