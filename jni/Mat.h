/*
 * Mat.h
 *
 *  Created on: Jan 30, 2016
 *      Author: boris
 */
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#ifndef JNI_MAT_H_
#define JNI_MAT_H_
using namespace std;

class Mat {
public:
	int rows, cols;
	double ** matrix;

	Mat(double** matrix, int rows, int cols);
	Mat(int rows, int cols);
	Mat(int size);
	virtual ~Mat();

	Mat* multiplyBy(const Mat &other);

	static vector<Mat*> * readMatrices(std::string filename){
			std::ifstream *infile = new ifstream(filename.c_str());
			int cols = getMatrixSize(filename);
			vector<Mat*> * matList = new vector<Mat*>();
			matList->push_back(parseMatrix(cols, infile));
			matList->push_back(parseMatrix(cols, infile));
			infile->close();
			delete infile;
			return matList;
		}

	char* toString();

private:
	double** multiplyMatricesNaive(const Mat &other);

	static Mat* parseMatrix(int columns, ifstream *infile){
			string line;
			vector<istringstream> lineArray;
			while (getline(*infile, line) && !line.empty()) {
				lineArray.push_back(istringstream(line));
			}
			int rows = lineArray.size();
			double ** matrix = new double*[rows];
			for (int i = 0; i < rows; i++) {
				matrix[i] = new double[columns];

				for (int j = 0; j < columns; j++) {
					int a;
					lineArray[i] >> a;
					matrix[i][j] = a;
				}
			}
			return new Mat(matrix, rows, columns);
		}

	static int getMatrixSize(std::string filename){
		string line;
		ifstream infile;
		infile.open(filename.c_str());
		getline(infile, line);
		return count(line.begin(), line.end(), '\t') + 1;
	}

};

#endif /* JNI_MAT_H_ */
