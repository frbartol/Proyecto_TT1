#include "..\include\SAT_Const.hpp"
// Mathematical constants
const double SAT_Const::pi        = 3.14159265358979324;
const double SAT_Const::pi2       = 2*pi;                // 2pi
const double SAT_Const::Rad       = pi/180;              // Radians per degree
const double SAT_Const::Deg       = 180/pi;              // Degrees per radian
const double SAT_Const::Arcs      = 3600*180/pi;         // Arcseconds per radian

// General
const double SAT_Const::MJD_J2000 = 51544.5;             // Modified Julian Date of J2000
const double SAT_Const::T_B1950   = -0.500002108;        // Epoch B1950
const double SAT_Const::c_light   = 299792458.000000000; // Speed of light  [m/s]; DE430
const double SAT_Const::AU        = 149597870700.000000; // Astronomical unit [m]; DE430

// Physical parameters of the Earth, Sun and Moon

// Equatorial radius and flattening
const double SAT_Const::R_Earth   = 6378.1363e3;      // Earth's radius [m]; DE430
const double SAT_Const::f_Earth   = 1/298.257223563;  // Flattening; WGS-84
const double SAT_Const::R_Sun     = 696000e3;         // Sun's radius [m]; DE430
const double SAT_Const::R_Moon    = 1738e3;           // Moon's radius [m]; DE430

// Earth rotation (derivative of GMST at J2000; differs from inertial period by precession)
const double SAT_Const::omega_Earth = 15.04106717866910/3600*SAT_Const::Rad;   // [rad/s]; WGS-84

// Gravitational coefficients
const double SAT_Const::GM_Earth    = 398600.435436e9;                  // [m^3/s^2]; DE430
const double SAT_Const::GM_Sun      = 132712440041.939400e9;            // [m^3/s^2]; DE430
const double SAT_Const::GM_Moon     = SAT_Const::GM_Earth/81.30056907419062; // [m^3/s^2]; DE430
const double SAT_Const::GM_Mercury  = 22031.780000e9;                   // [m^3/s^2]; DE430
const double SAT_Const::GM_Venus    = 324858.592000e9;                  // [m^3/s^2]; DE430
const double SAT_Const::GM_Mars     = 42828.375214e9;                   // [m^3/s^2]; DE430
const double SAT_Const::GM_Jupiter  = 126712764.800000e9;               // [m^3/s^2]; DE430
const double SAT_Const::GM_Saturn   = 37940585.200000e9;                // [m^3/s^2]; DE430
const double SAT_Const::GM_Uranus   = 5794548.600000e9;                 // [m^3/s^2]; DE430
const double SAT_Const::GM_Neptune  = 6836527.100580e9;                 // [m^3/s^2]; DE430
const double SAT_Const::GM_Pluto    = 977.0000000000009e9;              // [m^3/s^2]; DE430

// Solar radiation pressure at 1 AU 
const double SAT_Const::P_Sol       = 1367/SAT_Const::c_light; // [N/m^2] (~1367 W/m^2) IERS 96
const double SAT_Const::eps = 2.22044604925031e-16;
