#include "../include/AccelPointMass.hpp"

Matrix& AccelPointMass(Matrix &r, Matrix &s, double GM){
    if(r.n_row!=1 || r.n_column!=3 || s.n_row!=1 || s.n_column!=3){
        cout<<"AccelPointMass: r and s must be 3x1 matrix";
        
    }
    Matrix d = r-s;
    Matrix a = (d/pow(d.norm(),3)+s/pow(s.norm(),3))*(-GM);
    return a;
}