#include "Benchmark.h"
#include "Mat.h"
#include "Matrix.h"

JNIEXPORT void JNICALL Java_Benchmark_multiplyUsingMat(JNIEnv * env,
		jobject obj, jstring str) {
	string filename(env->GetStringUTFChars(str, NULL));
	vector<Mat*> * vector = Mat::readMatrices(filename);
	Mat *c = (*vector)[0]->multiplyBy(*(*vector)[1]);
	delete (*vector)[1];
	delete (*vector)[0];
	delete vector;
	delete c;
}

JNIEXPORT void JNICALL Java_Benchmark_multiplyUsingMatrix(JNIEnv * env,
		jobject obj, jstring str) {
	string filename(env->GetStringUTFChars(str, NULL));
	vector<Matrix*> * vector = Matrix::readMatrices(filename);
	Matrix *c = (*vector)[0]->multiplyBy(*(*vector)[1]);
	delete (*vector)[1];
	delete (*vector)[0];
	delete vector;
	delete c;
}
