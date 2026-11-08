#ifndef SMATRIX_H
#define SMATRIX_H

typedef struct {
    double* Data;
    unsigned long int VectorSize;
} SVector;

typedef struct {
    double** Data;
    unsigned long int Row;
    unsigned long int Col;
} SMatrix;

#endif // SMATRIX_H
