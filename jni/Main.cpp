/*
 * Main.cpp
 *
 *  Created on: Jan 29, 2016
 *      Author: bmant
 */
#include <iostream>
#include "Main.h"
#include "Matrix.h"

/*
	 * Method: objectArrayToMatrix
	 * converts a jObjectArray to a 1D array (representing a matrix)
	 *
	 * params:
	 * env - java environment object
	 * a - object array representing a 2d double matrix
	 * rows - ref to fill with row count
	 * cols - ref to fill with row count
	 *
	 * returns:
	 * a 1D array representing the matrix
	 */
double* objectArrayToMatrix(JNIEnv * env, jobjectArray a, int &rows, int &cols);

/*
	 * Method: objectArrayToMatrix
	 * converts a Matrix object to a 2D jobject array
	 *
	 * params:
	 * env - java environment object
	 * m - the Matrix to convert
	 *
	 * returns:
	 * 2D jobject array
	 */
jobjectArray MatrixToObjectArray(JNIEnv * env, const Matrix &m);

JNIEXPORT jobject JNICALL Java_Main_readMatrices(JNIEnv * env, jobject object,
		jstring str) {

	string filename(env->GetStringUTFChars(str, NULL));
	jclass intArray1DClass = env->FindClass("[D");
	jclass intArray2DClass = env->FindClass("[[D");
	jclass cList = env->FindClass("java/util/LinkedList");
	jmethodID ctr = env->GetMethodID(cList, "<init>", "()V");
	jobject jList = env->NewObject(cList, ctr);
	jmethodID mAdd = env->GetMethodID(cList, "add", "(Ljava/lang/Object;)Z");

	vector<Matrix*> * matrices = Matrix::readMatrices(filename);
	jobjectArray a = MatrixToObjectArray(env, *(*matrices)[0]);
	jobjectArray b = MatrixToObjectArray(env, *(*matrices)[1]);
	env->CallBooleanMethod(jList, mAdd, a);
	env->CallBooleanMethod(jList, mAdd, b);

	delete (*matrices)[1];
	delete (*matrices)[0];
	delete matrices;


	return jList;
}

JNIEXPORT jobjectArray JNICALL Java_Main_multiply__Ljava_lang_String_2
  (JNIEnv *env , jobject obj , jstring str)
{

	string filename(env->GetStringUTFChars(str, NULL));
	vector<Matrix*> * matrices = Matrix::readMatrices(filename);
	Matrix *c = (*matrices)[0]->multiplyBy(*(*matrices)[1]);

	//clean
	delete (*matrices)[1];
	delete (*matrices)[0];
	delete matrices;
	jobjectArray res = MatrixToObjectArray(env, *c);
	delete c;
	return res;
}

JNIEXPORT void JNICALL Java_Main_multiply__Ljava_lang_String_2Ljava_lang_String_2
  (JNIEnv * env, jobject obj , jstring str, jstring str1){
	string filename(env->GetStringUTFChars(str, NULL));
	vector<Matrix*> * matrices = Matrix::readMatrices(filename);
	Matrix *res = (*matrices)[0]->multiplyBy(*(*matrices)[1]);

	string outputFile(env->GetStringUTFChars(str1, NULL));
	std::ofstream outFile(outputFile.c_str());
	std::cout << outputFile.c_str();
	std::streambuf* cout_sbuf = std::cout.rdbuf();
	std::cout.rdbuf(outFile.rdbuf());
	char * outString = res->toString();
	outFile << outString;
	outFile.close();
	std::cout.rdbuf(cout_sbuf);

	//clean
	delete (*matrices)[1];
	delete (*matrices)[0];
	delete matrices;
	delete res;
	delete[] outString;
}


JNIEXPORT jobjectArray JNICALL Java_Main_multiply___3_3D_3_3D(JNIEnv * env, jobject obj,
		jobjectArray a, jobjectArray b) {

	int aRows, aCols, bRows, bCols;
	double *aArray = objectArrayToMatrix(env, a, aRows, aCols);
	double *bArray = objectArrayToMatrix(env, b, bRows, bCols);

	Matrix A(aArray, aRows, aCols);
	Matrix B(bArray, bRows, bCols);

	Matrix *c = A.multiplyBy(B);
	jobjectArray res = MatrixToObjectArray(env, *c);
	delete c;
	return res;

	return res;
}

double* objectArrayToMatrix(JNIEnv * env, jobjectArray a, int &rows, int &cols)
{
	rows = env->GetArrayLength(a);
	jdoubleArray array1D = (jdoubleArray) env->GetObjectArrayElement(a, 0);
	cols = env->GetArrayLength(array1D);
	double * c = new double[rows * cols];

	for (int y = 0; y < rows; y++)
	{
		array1D = (jdoubleArray) env->GetObjectArrayElement(a, y);
		cols = env->GetArrayLength(array1D);
		jdouble *body = env->GetDoubleArrayElements(array1D, 0);
		for (int z = 0; z < cols; z++)
		{
			c[y * rows + z] = body[z];
		}
		env->ReleaseDoubleArrayElements(array1D, body, 0);
	}
	return c;
}


jobjectArray MatrixToObjectArray(JNIEnv * env, const Matrix &m) {
	jclass intArray1DClass = env->FindClass("[D");

	jobjectArray array2D = env->NewObjectArray(m.rows, intArray1DClass, NULL);

	for (int y = 0; y < m.rows; y++) {
		jdoubleArray array1D = env->NewDoubleArray(m.cols);
		jdouble *body = env->GetDoubleArrayElements(array1D, 0);

		for (int z = 0; z < m.cols; z++) {
			body[z] = m.matrix[ y*m.rows + z];
		}
		env->ReleaseDoubleArrayElements(array1D, body, 0);
		env->SetObjectArrayElement(array2D, y, array1D);
	}

	return array2D;
}

