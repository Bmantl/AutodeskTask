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

	Matrix* multiplyBy(const Matrix &other);

	static vector<Matrix*> * readMatrices(std::string filename){
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
	double* multiplyMatricesNaive(const Matrix &other);

	static Matrix* parseMatrix(int columns, ifstream *infile){
			string line;
			vector<istringstream> lineArray;
			while (getline(*infile, line) && !line.empty()) {
				lineArray.push_back(istringstream(line));
			}

			int rows = lineArray.size();
			double * matrix = new double[rows * columns];
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int a;
					lineArray[i] >> a;
					matrix[i*rows + j] = a;
				}
			}
			return new Matrix(matrix, rows, columns);
		}

	static int getMatrixSize(std::string filename){
		string line;
		ifstream infile;
		infile.open(filename.c_str());
		getline(infile, line);
		return count(line.begin(), line.end(), '\t') + 1;
	}

};

#endif /* JNI_MATRIX_H_ */
