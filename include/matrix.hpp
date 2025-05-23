#ifndef _MATRIX_
#define _MATRIX_

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

class Matrix {
public:
    int n_row, n_column;
	double **data;

    // Parameterized constructor
    Matrix(const int n_row, const int n_column);
	Matrix(const int n);
	Matrix();
	
	// Member operators
	double& operator () (const int row, const int column);
	double& operator () (const int n);
	Matrix& operator + (Matrix &m);
	Matrix& operator - (Matrix &m);
	Matrix& operator * (Matrix &m);
	Matrix& operator / (Matrix &m);
	Matrix& operator = (Matrix &m);
	
	Matrix& operator + (double s);
	Matrix& operator - (double s);
	Matrix& operator * (double s);
	Matrix& operator / (double s);

	double norm();
	double dot(Matrix &m);
	Matrix& cross(Matrix &m);
	Matrix& extract_vector(int a, int b);
	Matrix& union_vector(Matrix &m);
	Matrix& extract_row(const int n);
	Matrix& extract_column(const int n);
	void asign_row(int n, Matrix &m);
	void asign_column(int n, Matrix &m);
	
	// Non-member operators
	friend ostream& operator << (ostream &o, Matrix &m);
};

// Operator overloading
ostream& operator << (ostream &o, Matrix &m);

// Methods
Matrix& zeros(const int n_row, const int n_column);
Matrix& zeros(const int n);
Matrix& eye(const int n);
Matrix& transpose(Matrix &m);
Matrix& inv(Matrix &m);


#endif