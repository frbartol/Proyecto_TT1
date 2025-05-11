#include "..\include\TimeUpdate.hpp"

Matrix& TimeUpdate(Matrix& P, Matrix& Phi, double Qdt){
    return Phi*P*transpose(Phi) + Qdt;
}