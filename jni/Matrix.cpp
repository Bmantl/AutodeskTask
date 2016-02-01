/*
 * Matrix.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: boris
 */

#include "Matrix.h"
#include <string.h>

Matrix::Matrix(double* matrix, int rows, int cols) {
	this->cols = cols;
	this->rows = rows;
	this->matrix = matrix;
}

Matrix::Matrix(int rows, int cols) {
	this->cols = cols;
	this->rows = rows;
	this->matrix = new double[rows * cols];
}

Matrix::Matrix(int size) :
		Matrix(size, size) {
}

Matrix::~Matrix() {
	delete[] this->matrix;
}

Matrix* Matrix::multiplyBy(const Matrix &other) {
	return new Matrix(this->multiplyMatricesNaive(other), this->rows, other.cols);
}

double* Matrix::multiplyMatricesNaive(const Matrix &other) {
	int aRows = this->rows;
	int aCols = this->cols;
	int bCols = other.cols;
	double * c = new double[aRows * bCols];
	for (int i = 0; i < aRows; i++) {
		for (int k = 0; k < bCols; k++) {
			for (int j = 0; j < aCols; j++)
				c[i * aRows + k] += this->matrix[i * aRows + j] * other.matrix[j*aCols + k];
		}
	}

	return c;
}

char* Matrix::toString() {
	std::ostringstream s;
	s << ("-----------------------------------\n");
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			s << this->matrix[i * this->rows + j];
			if(j != this->cols -1)
				s << "\t";
		}
		s << "\n";
	}
	s << "-----------------------------------\n";

	char * c= new char[s.str().length()];
	strcpy(c, s.str().c_str());
	std:: cout <<c;
	return c;
}
