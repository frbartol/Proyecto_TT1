#include "..\include\timediff.hpp"

tuple<double, double, double, double, double> timediff(double UT1_UTC, double TAI_UTC){
    double TT_TAI, GPS_TAI, TT_GPS, TAI_GPS, UT1_TAI, UTC_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC;

    TT_TAI  = +32.184;          
    GPS_TAI = -19.0;            
    TT_GPS  =  TT_TAI-GPS_TAI;  
    TAI_GPS = -GPS_TAI;
    UT1_TAI = UT1_UTC-TAI_UTC;  
    UTC_TAI = -TAI_UTC;             
    UTC_GPS = UTC_TAI-GPS_TAI;  
    UT1_GPS = UT1_TAI-GPS_TAI;  
    TT_UTC  = TT_TAI-UTC_TAI;   
    GPS_UTC = GPS_TAI-UTC_TAI; 

    return tie(UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC);
}