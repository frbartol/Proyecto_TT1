#ifndef _JPL_EPH_DE430_
#define _JPL_EPH_DE430_

#include <tuple>
#include "matrix.hpp"
#include "global.hpp"
#include "Cheb3D.hpp"

using namespace std;

tuple<Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&> JPL_Eph_DE430(double Mjd_TDB);

#endif