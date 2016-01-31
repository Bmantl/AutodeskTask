/*
 * Mat.cpp
 *
 *  Created on: Jan 30, 2016
 *      Author: boris
 */

#include "Mat.h"
#include <string.h>

Mat::Mat(double** matrix, int rows, int cols) {
	this->cols = cols;
	this->rows = rows;
	this->matrix = matrix;
}

Mat::Mat(int rows, int cols) {
	this->cols = cols;
	this->rows = rows;
	this->matrix = new double*[rows];
	for (int i = 0; i < rows; i++) {
		this->matrix[i] = new double[cols];
	}
}

Mat::Mat(int size) :
		Mat(size, size) {

}

Mat::~Mat() {
	for (int i = 0; i < rows; i++) {
			delete[] this->matrix[i];
		}

	delete[] this->matrix;
}

Mat* Mat::multiplyBy(const Mat &other) {
	return new Mat(this->multiplyMatricesNaive(other), this->rows, other.cols);
}

double** Mat::multiplyMatricesNaive(const Mat &other) {
	int aRows = this->rows;
	int aCols = this->cols;
	int bCols = other.cols;
	double ** c = new double*[aRows];
	for (int i = 0; i < aRows; i++) {
		c[i] = new double[bCols];
		for (int k = 0; k < bCols; k++) {
			for (int j = 0; j < aCols; j++)
				c[i][k] += this->matrix[i][j] * other.matrix[j][k];

		}
	}
	return c;
}

char* Mat::toString() {
	std::ostringstream s;
	s << ("-----------------------------------\n");
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			s << this->matrix[i][j];
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
