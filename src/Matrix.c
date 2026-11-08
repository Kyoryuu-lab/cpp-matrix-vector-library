#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>

SVector VectorCreate(unsigned long int NumElement) {
    SVector v;
    v.VectorSize = NumElement;
    v.Data = (double*)calloc(NumElement, sizeof(double));
    if (!v.Data && NumElement > 0) {
        fprintf(stderr, "Fehler: Speicherallokation fuer Vektor fehlgeschlagen.\n");
        exit(EXIT_FAILURE);
    }
    return v;
}

SVector VectorCreateFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Fehler: Datei %s konnte nicht geoeffnet werden.\n", filename);
        exit(EXIT_FAILURE);
    }

    unsigned long int numElements = 0;
    if (fscanf(file, "%lu", &numElements) != 1) {
        fprintf(stderr, "Fehler: Ungueltiges Dateiformat (Elementanzahl fehlt).\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    SVector v = VectorCreate(numElements);
    for (unsigned long int i = 0; i < numElements; ++i) {
        if (fscanf(file, "%lf", &v.Data[i]) != 1) {
            fprintf(stderr, "Fehler: Datenelement %lu konnte nicht gelesen werden.\n", i);
            fclose(file);
            VectorDelete(&v);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
    return v;
}

void VectorOutputToFile(SVector v, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Fehler beim Schreiben der Datei %s.\n", filename);
        return;
    }

    fprintf(file, "%lu\n", v.VectorSize);
    for (unsigned long int i = 0; i < v.VectorSize; ++i) {
        fprintf(file, "%lf ", v.Data[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}

SVector VectorFormula(double(*func)(double), unsigned long int size) {
    SVector v = VectorCreate(size);
    for (unsigned long int i = 0; i < size; ++i) {
        v.Data[i] = func((double)i);
    }
    return v;
}

void VectorDisplay(SVector v1) {
    printf("\nVektor[Groesse: %lu] = [", v1.VectorSize);
    for (unsigned long int i = 0; i < v1.VectorSize; i++) {
        printf(" %g", v1.Data[i]);
    }
    printf(" ]\n");
}

SVector VectorAdd(SVector v1, SVector v2) {
    if (v1.VectorSize != v2.VectorSize) {
        fprintf(stderr, "Fehler: Dimensionen fuer Vektoraddition inkompatibel.\n");
        exit(EXIT_FAILURE);
    }
    SVector res = VectorCreate(v1.VectorSize);
    for (unsigned long int i = 0; i < v1.VectorSize; ++i) {
        res.Data[i] = v1.Data[i] + v2.Data[i];
    }
    return res;
}

SVector VectorDiff(SVector v1, SVector v2) {
    if (v1.VectorSize != v2.VectorSize) {
        fprintf(stderr, "Fehler: Dimensionen fuer Vektorsubtraktion inkompatibel.\n");
        exit(EXIT_FAILURE);
    }
    SVector res = VectorCreate(v1.VectorSize);
    for (unsigned long int i = 0; i < v1.VectorSize; ++i) {
        res.Data[i] = v1.Data[i] - v2.Data[i];
    }
    return res;
}

double VectorScalar(SVector v1, SVector v2) {
    if (v1.VectorSize != v2.VectorSize) {
        fprintf(stderr, "Fehler: Dimensionen fuer Skalarprodukt inkompatibel.\n");
        exit(EXIT_FAILURE);
    }
    double res = 0.0;
    for (unsigned long int i = 0; i < v1.VectorSize; ++i) {
        res += v1.Data[i] * v2.Data[i];
    }
    return res;
}

SVector VectorMultConst(SVector v1, double c) {
    SVector res = VectorCreate(v1.VectorSize);
    for (unsigned long int i = 0; i < v1.VectorSize; ++i) {
        res.Data[i] = v1.Data[i] * c;
    }
    return res;
}

SVector VectorCopy(SVector v1) {
    SVector res = VectorCreate(v1.VectorSize);
    for (unsigned long int i = 0; i < v1.VectorSize; ++i) {
        res.Data[i] = v1.Data[i];
    }
    return res;
}

void VectorDelete(SVector* v1) {
    if (v1 && v1->Data) {
        free(v1->Data);
        v1->Data = NULL;
        v1->VectorSize = 0;
    }
}

SMatrix MatrixCreate(unsigned long int row, unsigned long int col) {
    SMatrix m;
    m.Row = row;
    m.Col = col;
    m.Data = (double**)malloc(row * sizeof(double*));
    for (unsigned long int i = 0; i < row; ++i) {
        m.Data[i] = (double*)calloc(col, sizeof(double));
    }
    return m;
}

void MatrixDisplay(SMatrix m1) {
    printf("\nMatrix [%lu x %lu]:\n", m1.Row, m1.Col);
    for (unsigned long int i = 0; i < m1.Row; ++i) {
        printf("  |");
        for (unsigned long int j = 0; j < m1.Col; ++j) {
            printf(" %6.2f", m1.Data[i][j]);
        }
        printf(" |\n");
    }
}

void MatrixMakeE(SMatrix* m1) {
    if (m1->Row != m1->Col) {
        fprintf(stderr, "Fehler: Matrix muss quadratisch sein fuer Einheitsmatrix.\n");
        exit(EXIT_FAILURE);
    }
    for (unsigned long int i = 0; i < m1->Row; ++i) {
        for (unsigned long int j = 0; j < m1->Col; ++j) {
            m1->Data[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

SMatrix MatrixMMMult(SMatrix m1, SMatrix m2) {
    if (m1.Col != m2.Row) {
        fprintf(stderr, "Fehler: Dimensionen inkompatibel fuer Matrixmultiplikation.\n");
        exit(EXIT_FAILURE);
    }
    SMatrix res = MatrixCreate(m1.Row, m2.Col);
    for (unsigned long int i = 0; i < m1.Row; ++i) {
        for (unsigned long int j = 0; j < m2.Col; ++j) {
            for (unsigned long int k = 0; k < m1.Col; ++k) {
                res.Data[i][j] += m1.Data[i][k] * m2.Data[k][j];
            }
        }
    }
    return res;
}

SMatrix MatrixMMAdd(SMatrix m1, SMatrix m2) {
    if (m1.Row != m2.Row || m1.Col != m2.Col) {
        fprintf(stderr, "Fehler: Dimensionen muessen uebereinstimmen fuer Matrixaddition.\n");
        exit(EXIT_FAILURE);
    }
    SMatrix res = MatrixCreate(m1.Row, m1.Col);
    for (unsigned long int i = 0; i < m1.Row; ++i) {
        for (unsigned long int j = 0; j < m1.Col; ++j) {
            res.Data[i][j] = m1.Data[i][j] + m2.Data[i][j];
        }
    }
    return res;
}

SMatrix MatrixMVMult(SMatrix m1, SVector v1) {
    if (m1.Col != v1.VectorSize) {
        fprintf(stderr, "Fehler: Matrix- und Vektordimensionen inkompatibel.\n");
        exit(EXIT_FAILURE);
    }
    SMatrix res = MatrixCreate(m1.Row, 1);
    for (unsigned long int i = 0; i < m1.Row; ++i) {
        for (unsigned long int j = 0; j < m1.Col; ++j) {
            res.Data[i][0] += m1.Data[i][j] * v1.Data[j];
        }
    }
    return res;
}

SMatrix MatrixCopy(SMatrix m1) {
    SMatrix res = MatrixCreate(m1.Row, m1.Col);
    for (unsigned long int i = 0; i < m1.Row; ++i) {
        for (unsigned long int j = 0; j < m1.Col; ++j) {
            res.Data[i][j] = m1.Data[i][j];
        }
    }
    return res;
}

void MatrixDelete(SMatrix* m1) {
    if (m1 && m1->Data) {
        for (unsigned long int i = 0; i < m1->Row; ++i) {
            free(m1->Data[i]);
        }
        free(m1->Data);
        m1->Data = NULL;
        m1->Row = 0;
        m1->Col = 0;
    }
}
