#include "..\include\AzElPa.hpp"
#include "..\include\SAT_Const.hpp"
tuple<double, double, Matrix&, Matrix&> AzElPa(Matrix& s){
    double rho, Az, El;
    Matrix& dAds = zeros(1,3);
    Matrix& dEds = zeros(1,3);

    rho = sqrt(s(1)*s(1)+s(2)*s(2));

    Az = atan2(s(1),s(2));

    if (Az<0.0) Az = Az+SAT_Const::pi2;

    El = atan ( s(3) / rho );

    dAds(1,1) = s(2)/(rho*rho);
    dAds(1,2) = -s(1)/(rho*rho);
    dAds(1,3) = 0.0;

    dEds(1,1) = -s(1)*s(3)/rho;
    dEds(1,2) = -s(2)*s(3)/rho;
    dEds(1,3) = rho;
    dEds = dEds/s.dot(s);

    return tie(Az, El, dAds, dEds);
}