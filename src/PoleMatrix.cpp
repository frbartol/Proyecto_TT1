/**
 * @file PoleMatrix.cpp
 * @brief Implementación de la matriz de corrección por el desplazamiento del polo terrestre.
 * @author Francisco Bartolome Alcalde
 */

#include "..\include\PoleMatrix.hpp"

Matrix& PoleMatrix(double xp, double yp){
    Matrix& PoleMat = R_y(-xp) * R_x(-yp);

    return PoleMat;
}