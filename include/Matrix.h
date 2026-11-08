#ifndef MATRIX_H
#define MATRIX_H

#include "SMatrix.h"

#ifdef __cplusplus
extern "C" {
#endif

// Vektor-Operationen
SVector VectorCreate(unsigned long int NumElement);
SVector VectorCreateFromFile(const char* filename);
void VectorOutputToFile(SVector v, const char* filename);
SVector VectorFormula(double(*func)(double), unsigned long int size);
void VectorDisplay(SVector v1);
SVector VectorAdd(SVector v1, SVector v2);
SVector VectorDiff(SVector v1, SVector v2);
double VectorScalar(SVector v1, SVector v2);
SVector VectorMultConst(SVector v1, double c);
SVector VectorCopy(SVector v1);
void VectorDelete(SVector* v1);

// Matrix-Operationen
SMatrix MatrixCreate(unsigned long int row, unsigned long int col);
void MatrixDisplay(SMatrix m1);
void MatrixMakeE(SMatrix* m1);
SMatrix MatrixMMMult(SMatrix m1, SMatrix m2);
SMatrix MatrixMMAdd(SMatrix m1, SMatrix m2);
SMatrix MatrixMVMult(SMatrix m1, SVector v1);
SMatrix MatrixCopy(SMatrix m1);
void MatrixDelete(SMatrix* m1);

#ifdef __cplusplus
}
#endif

#endif // MATRIX_H
