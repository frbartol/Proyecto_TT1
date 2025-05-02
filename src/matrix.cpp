#include "..\include\matrix.hpp"

//hay que añadir un constructor vacio
Matrix::Matrix(const int n_row, const int n_column) {
    if (n_row <= 0 || n_column <= 0) {
		cout << "Matrix create: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	this->n_row = n_row;
	this->n_column = n_column;
	this->data = (double **) malloc(n_row*sizeof(double *));
	
    if (this->data == NULL) {
		cout << "Matrix create: error in data\n";
        exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < n_row; i++) {
		this->data[i] = (double *) malloc(n_column*sizeof(double));
	}
}

Matrix::Matrix(const int n) {
    if (n <= 0) {
		cout << "Matrix create: error in n\n";
        exit(EXIT_FAILURE);
	}
	
	this->n_row = n;
	this->n_column = n;
	this->data = (double **) malloc(n*sizeof(double *));
	
    if (this->data == NULL) {
		cout << "Matrix create: error in data\n";
        exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < n_row; i++) {
		this->data[i] = (double *) malloc(n*sizeof(double));
	}
}

double& Matrix::operator () (const int row, const int column) {
	if (row <= 0 || row > this->n_row || column <= 0 || column > this->n_column) {
		cout << "Matrix get: error in row/column\n";
        exit(EXIT_FAILURE);
	}
	
	return this->data[row - 1][column - 1];
}

Matrix& Matrix::operator + (Matrix &m) {
	if (this->n_row != m.n_row || this->n_column != m.n_column) {
		cout << "Matrix sum: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) + m(i,j);
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator - (Matrix &m) {
	if (this->n_row != m.n_row || this->n_column != m.n_column) {
		cout << "Matrix sub: error in n_row/n_column\n";
        exit(EXIT_FAILURE); 
	}
	
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	
    for(int i = 1; i <= this->n_row; i++) {
        for(int j = 1; j <= this->n_column; j++) {
			(*m_aux)(i,j) = (*this)(i,j) - m(i,j);
		}
	}
	
	return *m_aux;
}

Matrix& Matrix::operator * (Matrix &m) {
	if (this->n_column != m.n_row) {
		cout << "Matrix mul: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	double sum;
	
	Matrix *m_aux = new Matrix(this->n_row, m.n_column);
	for (int i = 1; i <= this->n_row; i++){
		for (int j = 1; j <= m.n_column; j++){
			sum=0;
			for (int k=1; k<= this->n_column; k++){
				sum += (*this)(i,k)*m(k,j);
			}
			(*m_aux)(i,j) = sum;
		}
	}		
	
	return *m_aux;
}

Matrix& Matrix::operator / (Matrix &m) {
	if (this->n_column != m.n_row) {
		cout << "Matrix div: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}
	
	Matrix &m_inv = inv(m);
	Matrix *m_aux = new Matrix(this->n_row, m.n_column);

	double sum;

	for (int i = 1; i <= this->n_row; i++){
		for (int j = 1; j <= m_inv.n_column; j++){
			sum=0;
			for (int k=1; k<= this->n_column; k++){
				sum += (*this)(i,k)*m_inv(k,j);
			}
			(*m_aux)(i,j) = sum;
		}
	}		
	
	return *m_aux;
}


Matrix& Matrix::operator = (Matrix &m) {
	this->n_row = m.n_row;
	this->n_column = m.n_column;
	this->data = (double **) malloc(n_row*sizeof(double *));
	for(int i = 0; i < n_row; i++) {
		this->data[i] = (double *) malloc(n_column*sizeof(double));
		for (int j = 0; j < this->n_column; j++) {
            this->data[i][j] = m.data[i][j];
        }
	}
	return *this;
}



Matrix& Matrix::operator + (double s){
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	for(int i = 1; i <= this->n_row; i++){
		for(int j = 1; j <= this->n_column; j++){
			(*m_aux)(i,j) = (*this)(i,j) + s;
		}
	}
	return *m_aux;
}

Matrix& Matrix::operator - (double s){
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	for(int i = 1; i <= this->n_row; i++){
		for(int j = 1; j <= this->n_column; j++){
			(*m_aux)(i,j) = (*this)(i,j) - s;
		}
	}
	return *m_aux;
}

Matrix& Matrix::operator * (double s){
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	for(int i = 1; i <= this->n_row; i++){
		for(int j = 1; j <= this->n_column; j++){
			(*m_aux)(i,j) = (*this)(i,j)*s;
		}
	}
	return *m_aux;
}

Matrix& Matrix::operator / (double s){
	if (s==0) {
		cout << "Divisor can't be 0";
        exit(EXIT_FAILURE);
	}
	Matrix *m_aux = new Matrix(this->n_row, this->n_column);
	for(int i = 1; i <= this->n_row; i++){
		for(int j = 1; j <= this->n_column; j++){
			(*m_aux)(i,j) = (*this)(i,j)/s;
		}
	}
	return *m_aux;
}

ostream& operator << (ostream &o, Matrix &m) {
	for (int i = 1; i <= m.n_row; i++) {
        for (int j = 1; j <= m.n_column; j++)
			printf("%5.20lf ", m(i,j));
        o << "\n";
    }
	
    return o;
}

Matrix& zeros(const int n_row, const int n_column) {
	Matrix *m_aux = new Matrix(n_row, n_column);
	
	for(int i = 1; i <= n_row; i++) {
		for(int j = 1; j <= n_column; j++) {
			(*m_aux)(i,j) = 0;
		}
	}
	
	return (*m_aux);
}

Matrix& eye(const int n){
	Matrix *m_aux = new Matrix(n);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(i==j) (*m_aux)(i,j)=1;
			else (*m_aux)(i,j)=0;
		}
	}
	return (*m_aux);
}

Matrix& zeros(const int n) {
	Matrix *m_aux = new Matrix(n);
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			(*m_aux)(i,j) = 0;
		}
	}
	
	return (*m_aux);
}

Matrix& transpose(Matrix &m){
	Matrix *m_aux = new Matrix(m.n_column, m.n_row);
	for(int i = 1; i <= (*m_aux).n_row; i++){
		for(int j = 1; j <= (*m_aux).n_column; j++){
			(*m_aux)(i,j) = m(j,i);
		}
	}
	return *m_aux;
}

Matrix& inv(Matrix &m){
	if (m.n_row != m.n_column) {
		cout << "Matrix inv: error in n_row/n_column\n";
        exit(EXIT_FAILURE);
	}

	int n = m.n_row;
	Matrix *m_aux = new Matrix(n);  // Copia de m
	Matrix &I = eye(n);             // Matriz identidad

	// Copiar contenido de m a m_aux
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			(*m_aux)(i, j) = m(i, j);
		}
	}

	// Gauss-Jordan para obtener la inversa
	for (int i = 1; i <= n; i++) {
		double pivot = (*m_aux)(i, i);

		// Si el pivote es 0, buscar fila para intercambiar
		if (pivot == 0) {
			int swap_row = -1;
			for (int k = i + 1; k <= n; k++) {
				if ((*m_aux)(k, i) != 0) {
					swap_row = k;
					break;
				}
			}
			if (swap_row == -1) {
				cout << "Matrix inv: matriz no invertible (pivot = 0)\n";
				exit(EXIT_FAILURE);
			}

			// Intercambiar filas en ambas matrices
			for (int j = 1; j <= n; j++) {
				swap((*m_aux)(i, j), (*m_aux)(swap_row, j));
				swap(I(i, j), I(swap_row, j));
			}
			pivot = (*m_aux)(i, i);
		}

		// Normalizar fila i
		for (int j = 1; j <= n; j++) {
			(*m_aux)(i, j) /= pivot;
			I(i, j) /= pivot;
		}

		// Hacer ceros en otras filas de la columna
		for (int k = 1; k <= n; k++) {
			if (k == i) continue;
			double factor = (*m_aux)(k, i);
			for (int j = 1; j <= n; j++) {
				(*m_aux)(k, j) -= factor * (*m_aux)(i, j);
				I(k, j) -= factor * I(i, j);
			}
		}
	}

	return I;
}
