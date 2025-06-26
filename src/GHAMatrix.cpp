/**
 * @file GHAMatrix.cpp
 * @brief Implementación de la función que calcula la matriz de ángulo horario de Greenwich (GHA).
 * @author Francisco Bartolome Alcalde
 */
#include "..\include\GHAMatrix.hpp"

Matrix& GHAMatrix(double Mjd_UT1){
    Matrix& GHAmat = R_z( gast(Mjd_UT1) );
    return GHAmat;
}