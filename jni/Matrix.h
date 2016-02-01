/*
 * Matrix.h
 *
 *  Created on: Jan 31, 2016
 *      Author: boris
 */

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#ifndef JNI_MATRIX_H_
#define JNI_MATRIX_H_
using namespace std;

class Matrix {
public:
	int rows, cols;
	double * matrix;

	Matrix(double* matrix, int rows, int cols);
	Matrix(int rows, int cols);
	Matrix(int size);
	virtual ~Matrix();

	/*
	 * Method: multiplyBy
	 * Multiplies the invoking matrix with other
	 * Should pick between multi algos according to matrix size - not implemented..
	 *
	 * params:
	 * other - other matrix
	 *
	 * returns:
	 * the product of this * other
	 */
	Matrix* multiplyBy(const Matrix &other);

	/*
	 * Method: readMatrices
	 * Reads matrices from a file
	 *
	 * params:
	 * filename - file containing the matrices
	 *
	 * returns:
	 * a vector with the matrices
	 */
	static vector<Matrix*> * readMatrices(std::string filename) {
		std::ifstream *infile = new ifstream(filename.c_str());
		int cols = getMatrixSize(filename);
		vector<Matrix*> * matList = new vector<Matrix*>();
		matList->push_back(parseMatrix(cols, infile));
		matList->push_back(parseMatrix(cols, infile));
		infile->close();
		delete infile;
		return matList;
	}

	char* toString();

private:
	/*
	 * Method: multiplyMatricesNaive
	 * Multiplies using the naive n^3 algo
	 *
	 * params:
	 * other - other matrix
	 *
	 * returns:
	 * the product of this * other
	 */
	double* multiplyMatricesNaive(const Matrix &other);

	static Matrix* parseMatrix(int columns, ifstream *infile) {
		//read the matrix lines from the file
		string line;
		vector<istringstream> lineArray;
		while (getline(*infile, line) && !line.empty()) {
			lineArray.push_back(istringstream(line));
		}
		int rows = lineArray.size();

		//fill the matrix
		double * matrix = new double[rows * columns];
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				int a;
				lineArray[i] >> a;
				matrix[i * rows + j] = a;
			}
		}
		return new Matrix(matrix, rows, columns);
	}

	static int getMatrixSize(std::string filename) {
		string line;
		ifstream infile;
		infile.open(filename.c_str());
		getline(infile, line);
		return count(line.begin(), line.end(), '\t') + 1;
	}

};

#endif /* JNI_MATRIX_H_ */
