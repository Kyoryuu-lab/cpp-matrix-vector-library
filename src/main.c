#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

double square_func(double x) {
    return x * x;
}

int main(void) {
    printf("=====================================================\n");
    printf("  DYNAMIC MATRIX & VECTOR MATH SUITE (C/C++)\n");
    printf("=====================================================\n");

    // 1. Vektor aus Datei laden oder dynamisch erstellen
    const char* in_file = "input_vector.txt";
    SVector v1;
    FILE* test_f = fopen(in_file, "r");
    if (test_f) {
        fclose(test_f);
        v1 = VectorCreateFromFile(in_file);
    } else {
        printf("[!] '%s' nicht gefunden. Erzeuge synthetischen Vektor...\n", in_file);
        v1 = VectorCreate(5);
        for (int i = 0; i < 5; i++) v1.Data[i] = (i + 1) * 2.0;
    }

    printf("\n[*] Geladener Vektor v1:");
    VectorDisplay(v1);

    // 2. Vektor in Ausgabedatei schreiben
    VectorOutputToFile(v1, "output_vector.txt");
    printf("[+] Vektor v1 erfolgreich in 'output_vector.txt' serialisiert.\n");

    // 3. Vektorgenerierung via Funktionszeiger (Quadrate f(x) = x^2)
    SVector v2 = VectorFormula(square_func, 6);
    printf("\n[*] Synthetischer Funktionsvektor v2 (f(x) = x^2):");
    VectorDisplay(v2);

    // 4. Matrix-Operationen
    SMatrix m1 = MatrixCreate(3, 3);
    MatrixMakeE(&m1);
    printf("\n[*] 3x3 Einheitsmatrix E:");
    MatrixDisplay(m1);

    SMatrix m2 = MatrixCreate(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m2.Data[i][j] = (i + 1) * (j + 2);
        }
    }
    printf("\n[*] 3x3 Testmatrix M2:");
    MatrixDisplay(m2);

    SMatrix m_prod = MatrixMMMult(m1, m2);
    printf("\n[*] Matrixmultiplikation E * M2 (sollte identisch zu M2 sein):");
    MatrixDisplay(m_prod);

    // 5. Speicherfreigabe
    VectorDelete(&v1);
    VectorDelete(&v2);
    MatrixDelete(&m1);
    MatrixDelete(&m2);
    MatrixDelete(&m_prod);

    printf("\n[+] Alle dynamischen Allokationen fehlerfrei freigegeben.\n");
    return 0;
}
