#include "..\include\JPL_Eph_DE430.hpp"

/**
 * @file JPL_Eph_DE430.cpp
 * @brief Implementación de la función JPL_Eph_DE430 para calcular posiciones de cuerpos celestes desde la efeméride DE430.
 * 
 * Utiliza coeficientes de polinomios de Chebyshev almacenados en la matriz global `PC` para interpolar posiciones
 * de los planetas, la Luna y el Sol, así como datos de nutación y libración.
 * 
 * Ajusta los vectores de posición al sistema centrado en la Tierra y escala a metros.
 * 
 * @return Tupla con las posiciones (columnas 3x1 en metros) relativas a la Tierra de:
 * - Mercurio
 * - Venus
 * - Tierra (baricentro Tierra-Luna)
 * - Marte
 * - Júpiter
 * - Saturno
 * - Urano
 * - Neptuno
 * - Plutón
 * - Luna (relativa a la Tierra)
 * - Sol
 * 
 * @author Francisco Bartolome Alcalde
 */

tuple<Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&, Matrix&> JPL_Eph_DE430(double Mjd_TDB){

    double JD = Mjd_TDB + 2400000.5;
    int i = -1;
    for (int k = 1; k <= PC.n_row; k++) {
        if (PC(k, 1) <= JD && JD <= PC(k, 2)) {
            i = k;
            break;
        }
    }
    if(i==-1){
        cout<<"JPL_Eph_DE430: JD out of range";
        exit(EXIT_FAILURE);
    }

    Matrix& PCtemp = PC.extract_row(i);

    double t1 = PCtemp(1)-2400000.5; // MJD at start of interval

    double dt = Mjd_TDB - t1;

    Matrix& temp = zeros(4);
    temp(1) = 231.0;
    temp(2) = 244.0;
    temp(3) = 257.0;
    temp(4) = 270.0;
    Matrix& Cx_Earth = PCtemp.extract_vector(temp(1),temp(2)-1.0);
    Matrix& Cy_Earth = PCtemp.extract_vector(temp(2),temp(3)-1.0);
    Matrix& Cz_Earth = PCtemp.extract_vector(temp(3),temp(4)-1.0);
    temp = temp+39;
    Matrix& Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix& Cz = PCtemp.extract_vector(temp(3),temp(4)-1);
    Cx_Earth = Cx_Earth.union_vector(Cx);
    Cy_Earth = Cy_Earth.union_vector(Cy);
    Cz_Earth = Cz_Earth.union_vector(Cz);
    int j;
    double Mjd0;
    if (0<=dt && dt<=16){
        j=0;
        Mjd0 = t1;
    }
    else if(16<dt && dt<=32){
        j=1;
        Mjd0 = t1+16*j;
    }
    Matrix& r_Earth = transpose(Cheb3D(Mjd_TDB, 13, Mjd0, Mjd0+16, Cx_Earth.extract_vector(13*j+1,13*j+13),
                        Cy_Earth.extract_vector(13*j+1,13*j+13), Cz_Earth.extract_vector(13*j+1,13*j+13)))*1e3;

    temp(1) = 441.0;
    temp(2) = 454.0;
    temp(3) = 467.0;
    temp(4) = 480.0;
    Matrix& Cx_Moon = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy_Moon = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix& Cz_Moon = PCtemp.extract_vector(temp(3),temp(4)-1);
    for (int i=1; i<=7; i++){
        temp = temp+39;
        Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
        Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
        Cz = PCtemp.extract_vector(temp(3),temp(4)-1);   
        Cx_Moon = Cx_Moon.union_vector(Cx);
        Cy_Moon = Cy_Moon.union_vector(Cy);
        Cz_Moon = Cz_Moon.union_vector(Cz);    
    }
    if (0<=dt && dt<=4){
        j=0;
        Mjd0 = t1;
    }
    else if(4<dt && dt<=8){
        j=1;
        Mjd0 = t1+4*j;
    }
    else if(8<dt && dt<=12){
        j=2;
        Mjd0 = t1+4*j;
    }
    else if(12<dt && dt<=16){
        j=3;
        Mjd0 = t1+4*j;
    }
    else if(16<dt && dt<=20){
        j=4;
        Mjd0 = t1+4*j;
    }
    else if(20<dt && dt<=24){
        j=5;
        Mjd0 = t1+4*j;
    }
    else if(24<dt && dt<=28){
        j=6;
        Mjd0 = t1+4*j;
    }
    else if(28<dt && dt<=32){
        j=7;
        Mjd0 = t1+4*j;
    }
    Matrix& r_Moon = transpose(Cheb3D(Mjd_TDB, 13, Mjd0, Mjd0+4, Cx_Moon.extract_vector(13*j+1,13*j+13),
                        Cy_Moon.extract_vector(13*j+1,13*j+13), Cz_Moon.extract_vector(13*j+1,13*j+13)))*1e3;

    temp(1) = 753.0;
    temp(2) = 764.0;
    temp(3) = 775.0;
    temp(4) = 786.0;

    Matrix& Cx_Sun = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy_Sun = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix& Cz_Sun = PCtemp.extract_vector(temp(3),temp(4)-1);
    temp = temp+33;
    Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
    Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
    Cz = PCtemp.extract_vector(temp(3),temp(4)-1);   
    Cx_Sun = Cx_Sun.union_vector(Cx);
    Cy_Sun = Cy_Sun.union_vector(Cy);
    Cz_Sun = Cz_Sun.union_vector(Cz);
    if (0<=dt && dt<=16){
        j=0;
        Mjd0 = t1;
    }
    else if(16<dt && dt<=32){
        j=1;
        Mjd0 = t1+16*j;
    }
    Matrix& r_Sun = transpose(Cheb3D(Mjd_TDB, 11, Mjd0, Mjd0+16, Cx_Sun.extract_vector(11*j+1,11*j+11),
                    Cy_Sun.extract_vector(11*j+1,11*j+11), Cz_Sun.extract_vector(11*j+1,11*j+11)))*1e3;

    temp(1) = 3.0;
    temp(2) = 17.0;
    temp(3) = 31.0;
    temp(4) = 45.0;
    Matrix& Cx_Mercury = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy_Mercury = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix& Cz_Mercury = PCtemp.extract_vector(temp(3),temp(4)-1);
    for (int i=1; i<=3; i++){
        temp = temp+42;
        Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
        Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
        Cz = PCtemp.extract_vector(temp(3),temp(4)-1);
        Cx_Mercury = Cx_Mercury.union_vector(Cx);
        Cy_Mercury = Cy_Mercury.union_vector(Cy);
        Cz_Mercury = Cz_Mercury.union_vector(Cz);    
    }
    if (0<=dt && dt<=8){
        j=0;
        Mjd0 = t1;
    }
    else if(8<dt && dt<=16){
        j=1;
        Mjd0 = t1+8*j;
    }
    else if (16<dt && dt<=24){
        j=2;
        Mjd0 = t1+8*j;
    }
    else if(24<dt && dt<=32){
        j=3;
        Mjd0 = t1+8*j;
    }
    Matrix& r_Mercury = transpose(Cheb3D(Mjd_TDB, 14, Mjd0, Mjd0+8, Cx_Mercury.extract_vector(14*j+1,14*j+14),
                        Cy_Mercury.extract_vector(14*j+1,14*j+14), Cz_Mercury.extract_vector(14*j+1,14*j+14)))*1e3;

    temp(1) = 171.0;
    temp(2) = 181.0;
    temp(3) = 191.0;
    temp(4) = 201.0;
    Matrix& Cx_Venus = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy_Venus = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix& Cz_Venus = PCtemp.extract_vector(temp(3),temp(4)-1);
    temp = temp+30;
    Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
    Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
    Cz = PCtemp.extract_vector(temp(3),temp(4)-1);
    Cx_Venus = Cx_Venus.union_vector(Cx);
    Cy_Venus = Cy_Venus.union_vector(Cy);
    Cz_Venus = Cz_Venus.union_vector(Cz);
    if (0<=dt && dt<=16){
        j=0;
        Mjd0 = t1;
    }
    else if(16<dt && dt<=32){
        j=1;
        Mjd0 = t1+16*j;
    }
    Matrix& r_Venus = transpose(Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+16, Cx_Venus.extract_vector(10*j+1,10*j+10),
                        Cy_Venus.extract_vector(10*j+1,10*j+10), Cz_Venus.extract_vector(10*j+1,10*j+10)))*1e3;

    temp(1) = 309;
    temp(2) = 320.0;
    temp(3) = 331.0;
    temp(4) = 342.0;
    Matrix& Cx_Mars = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy_Mars = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix& Cz_Mars = PCtemp.extract_vector(temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Mars = transpose(Cheb3D(Mjd_TDB, 11, Mjd0, Mjd0+32, Cx_Mars.extract_vector(11*j+1,11*j+11),
                        Cy_Mars.extract_vector(11*j+1,11*j+11), Cz_Mars.extract_vector(11*j+1,11*j+11)))*1e3;

    temp(1) = 342.0;
    temp(2) = 350.0;
    temp(3) = 358.0;
    temp(4) = 366.0;
    Matrix& Cx_Jupiter = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy_Jupiter = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix& Cz_Jupiter = PCtemp.extract_vector(temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Jupiter = transpose(Cheb3D(Mjd_TDB, 8, Mjd0, Mjd0+32, Cx_Jupiter.extract_vector(8*j+1,8*j+8),
                        Cy_Jupiter.extract_vector(8*j+1,8*j+8), Cz_Jupiter.extract_vector(8*j+1,8*j+8)))*1e3;

    temp(1) = 366.0;
    temp(2) = 373.0;
    temp(3) = 380.0;
    temp(4) = 387.0;
    Matrix& Cx_Saturn = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy_Saturn = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix& Cz_Saturn = PCtemp.extract_vector(temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Saturn = transpose(Cheb3D(Mjd_TDB, 7, Mjd0, Mjd0+32, Cx_Saturn.extract_vector(7*j+1,7*j+7),
                        Cy_Saturn.extract_vector(7*j+1,7*j+7), Cz_Saturn.extract_vector(7*j+1,7*j+7)))*1e3;

    temp(1) = 387.0;
    temp(2) = 393.0;
    temp(3) = 399.0;
    temp(4) = 405.0;
    Matrix& Cx_Uranus = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy_Uranus = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix& Cz_Uranus = PCtemp.extract_vector(temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Uranus = transpose(Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0+32, Cx_Uranus.extract_vector(6*j+1,6*j+6),
                        Cy_Uranus.extract_vector(6*j+1,6*j+6), Cz_Uranus.extract_vector(6*j+1,6*j+6)))*1e3;

    temp(1) = 405.0;
    temp(2) = 411.0;
    temp(3) = 417.0;
    temp(4) = 423.0;
    Matrix& Cx_Neptune = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy_Neptune = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix& Cz_Neptune = PCtemp.extract_vector(temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Neptune = transpose(Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0+32, Cx_Neptune.extract_vector(6*j+1,6*j+6),
                        Cy_Neptune.extract_vector(6*j+1,6*j+6), Cz_Neptune.extract_vector(6*j+1,6*j+6)))*1e3;

    temp(1) = 423.0;
    temp(2) = 429.0;
    temp(3) = 435.0;
    temp(4) = 441.0;
    Matrix& Cx_Pluto = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy_Pluto = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix& Cz_Pluto = PCtemp.extract_vector(temp(3),temp(4)-1);
    j=0;
    Mjd0 = t1;
    Matrix& r_Pluto = transpose(Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0+32, Cx_Pluto.extract_vector(6*j+1,6*j+6),
                        Cy_Pluto.extract_vector(6*j+1,6*j+6), Cz_Pluto.extract_vector(6*j+1,6*j+6)))*1e3;
    temp = zeros(3);
    temp(1) = 819.0;
    temp(2) = 829.0;
    temp(3) = 839.0;
    Matrix& Cx_Nutations = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy_Nutations = PCtemp.extract_vector(temp(2),temp(3)-1);
    for (int i=1; i<=3; i++){
        temp = temp+20;
        Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
        Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
        Cx_Nutations = Cx_Nutations.union_vector(Cx);
        Cy_Nutations = Cy_Nutations.union_vector(Cy);
    }
    if (0<=dt && dt<=8){
        j=0;
        Mjd0 = t1;
    }
    else if(8<dt && dt<=16){
        j=1;
        Mjd0 = t1+8*j;
    }
    else if (16<dt && dt<=24){
        j=2;
        Mjd0 = t1+8*j;
    }
    else if(24<dt && dt<=32){
        j=3;
        Mjd0 = t1+8*j;
    }
    Matrix& Nutations = transpose(Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+8, Cx_Nutations.extract_vector(10*j+1,10*j+10),
                    Cy_Nutations.extract_vector(10*j+1,10*j+10),zeros(1,10)));
    temp = zeros(4);
    temp(1) = 899.0;
    temp(2) = 909.0;
    temp(3) = 919.0;
    temp(4) = 929.0;
    Matrix& Cx_Librations = PCtemp.extract_vector(temp(1),temp(2)-1);
    Matrix& Cy_Librations = PCtemp.extract_vector(temp(2),temp(3)-1);
    Matrix& Cz_Librations = PCtemp.extract_vector(temp(3),temp(4)-1);
    for (int i=1; i<=3; i++){
        temp = temp+30;
        Cx = PCtemp.extract_vector(temp(1),temp(2)-1);
        Cy = PCtemp.extract_vector(temp(2),temp(3)-1);
        Cz = PCtemp.extract_vector(temp(3),temp(4)-1);
        Cx_Librations = Cx_Librations.union_vector(Cx);
        Cy_Librations = Cy_Librations.union_vector(Cy);
        Cz_Librations = Cz_Librations.union_vector(Cz);    
    }
    if (0<=dt && dt<=8){
        j=0;
        Mjd0 = t1;
    }
    else if(8<dt && dt<=16){
        j=1;
        Mjd0 = t1+8*j;
    }
    else if (16<dt && dt<=24){
        j=2;
        Mjd0 = t1+8*j;
    }
    else if(24<dt && dt<=32){
        j=3;
        Mjd0 = t1+8*j;
    }
    Matrix& Librations = transpose(Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+8, Cx_Librations.extract_vector(10*j+1,10*j+10),
                        Cy_Librations.extract_vector(10*j+1,10*j+10), Cz_Librations.extract_vector(10*j+1,10*j+10)));
    double EMRAT = 81.30056907419062; // DE430
    double EMRAT1 = 1/(1+EMRAT);
    r_Earth = r_Earth-(r_Moon*EMRAT1);
    r_Mercury = r_Mercury-r_Earth;
    r_Venus = r_Venus-r_Earth;
    r_Mars = r_Mars-r_Earth;
    r_Jupiter = r_Jupiter-r_Earth;
    r_Saturn = r_Saturn-r_Earth;
    r_Uranus = r_Uranus-r_Earth;
    r_Neptune = r_Neptune-r_Earth;
    r_Pluto = r_Pluto-r_Earth;
    r_Sun = r_Sun-r_Earth;

    return tie(transpose(r_Mercury), transpose(r_Venus), transpose(r_Earth), transpose(r_Mars), transpose(r_Jupiter), transpose(r_Saturn), transpose(r_Uranus), transpose(r_Neptune), transpose(r_Pluto), transpose(r_Moon), transpose(r_Sun));
}