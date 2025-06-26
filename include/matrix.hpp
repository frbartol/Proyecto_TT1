#ifndef _MATRIX_
#define _MATRIX_

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

/**
 * @class Matrix
 * @brief Clase que representa una matriz y permite operaciones básicas de álgebra lineal.
 * @author Francisco Bartolome Alcalde
 */
class Matrix {
public:
    int n_row;     ///< Número de filas.
    int n_column;  ///< Número de columnas.
    double **data; ///< Datos de la matriz (memoria dinámica).

    /**
     * @brief Constructor parametrizado.
     * @param n_row Número de filas.
     * @param n_column Número de columnas.
     */
    Matrix(const int n_row, const int n_column);

    /**
     * @brief Constructor cuadrado.
     * @param n Dimensión de la matriz cuadrada (n x n).
     */
    Matrix(const int n);

    /**
     * @brief Constructor por defecto.
     */
    Matrix();

    /**
     * @brief Accede o modifica un elemento específico.
     * @param row Fila del elemento.
     * @param column Columna del elemento.
     * @return Referencia al valor.
     */
    double& operator()(const int row, const int column);

    /**
     * @brief Accede o modifica un elemento usando índice lineal (para vectores).
     * @param n Índice lineal.
     * @return Referencia al valor.
     */
    double& operator()(const int n);

    /**
     * @brief Suma de matrices.
     * @param m Matriz a sumar.
     * @return Resultado de la suma.
     */
    Matrix& operator+(Matrix &m);

    /**
     * @brief Resta de matrices.
     * @param m Matriz a restar.
     * @return Resultado de la resta.
     */
    Matrix& operator-(Matrix &m);

    /**
     * @brief Producto matricial.
     * @param m Matriz a multiplicar.
     * @return Resultado del producto.
     */
    Matrix& operator*(Matrix &m);

    /**
     * @brief División elemento a elemento entre matrices.
     * @param m Matriz a dividir.
     * @return Resultado de la división.
     */
    Matrix& operator/(Matrix &m);

    /**
     * @brief Asignación entre matrices.
     * @param m Matriz origen.
     * @return Referencia a esta matriz.
     */
    Matrix& operator=(Matrix &m);

    /**
     * @brief Suma escalar.
     * @param s Escalar a sumar.
     * @return Resultado de la suma.
     */
    Matrix& operator+(double s);

    /**
     * @brief Resta escalar.
     * @param s Escalar a restar.
     * @return Resultado de la resta.
     */
    Matrix& operator-(double s);

    /**
     * @brief Multiplicación escalar.
     * @param s Escalar a multiplicar.
     * @return Resultado de la multiplicación.
     */
    Matrix& operator*(double s);

    /**
     * @brief División escalar.
     * @param s Escalar a dividir.
     * @return Resultado de la división.
     */
    Matrix& operator/(double s);

    /**
     * @brief Calcula la norma euclídea de la matriz (como vector).
     * @return Norma.
     */
    double norm();

    /**
     * @brief Calcula el producto escalar con otro vector.
     * @param m Vector con el que se realiza el producto.
     * @return Resultado escalar.
     */
    double dot(Matrix &m);

    /**
     * @brief Calcula el producto vectorial con otro vector (3D).
     * @param m Vector con el que se realiza el producto.
     * @return Referencia a esta matriz con el resultado.
     */
    Matrix& cross(Matrix &m);

    /**
     * @brief Extrae un subvector desde el índice a hasta el índice b (inclusive).
     * @param a Índice inicial.
     * @param b Índice final.
     * @return Subvector.
     */
    Matrix& extract_vector(int a, int b);

    /**
     * @brief Une este vector con otro vector.
     * @param m Vector a concatenar.
     * @return Vector resultante.
     */
    Matrix& union_vector(Matrix &m);

    /**
     * @brief Extrae la fila n.
     * @param n Índice de fila.
     * @return Fila extraída como vector fila.
     */
    Matrix& extract_row(const int n);

    /**
     * @brief Extrae la columna n.
     * @param n Índice de columna.
     * @return Columna extraída como vector columna.
     */
    Matrix& extract_column(const int n);

    /**
     * @brief Asigna una fila.
     * @param n Índice de fila a modificar.
     * @param m Vector fila a asignar.
     */
    void asign_row(int n, Matrix &m);

    /**
     * @brief Asigna una columna.
     * @param n Índice de columna a modificar.
     * @param m Vector columna a asignar.
     */
    void asign_column(int n, Matrix &m);

    /**
     * @brief Sobrecarga del operador de salida para imprimir la matriz.
     * @param o Flujo de salida.
     * @param m Matriz a imprimir.
     * @return Referencia al flujo de salida.
     */
    friend ostream& operator<<(ostream &o, Matrix &m);
};

/**
 * @brief Operador de salida para imprimir una matriz.
 * @param o Flujo de salida.
 * @param m Matriz a imprimir.
 * @return Flujo resultante.
 */
ostream& operator<<(ostream &o, Matrix &m);

/**
 * @brief Crea una matriz de ceros.
 * @param n_row Número de filas.
 * @param n_column Número de columnas.
 * @return Matriz de ceros.
 */
Matrix& zeros(const int n_row, const int n_column);

/**
 * @brief Crea una matriz cuadrada de ceros.
 * @param n Dimensión.
 * @return Matriz de ceros.
 */
Matrix& zeros(const int n);

/**
 * @brief Crea una matriz identidad.
 * @param n Dimensión.
 * @return Matriz identidad.
 */
Matrix& eye(const int n);

/**
 * @brief Transpone una matriz.
 * @param m Matriz a transponer.
 * @return Matriz transpuesta.
 */
Matrix& transpose(Matrix &m);

/**
 * @brief Calcula la inversa de una matriz.
 * @param m Matriz a invertir.
 * @return Matriz inversa.
 */
Matrix& inv(Matrix &m);

#endif
