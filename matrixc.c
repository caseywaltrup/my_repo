#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    int** data;
} Matrix;

//allocate memory for a matrix
Matrix createMatrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) {
        mat.data[i] = (int*)malloc(cols * sizeof(int));
    }
    return mat;
}

//free matrix memory
void freeMatrix(Matrix* mat) {
    for (int i = 0; i < mat->rows; ++i)
        free(mat->data[i]);
    free(mat->data);
}

//input data for each spot in matrix
void inputMatrix(Matrix* mat) {
    printf("Enter elements (%dx%d):\n", mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; ++i) {
        for (int j = 0; j < mat->cols; ++j) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &mat->data[i][j]);
        }
    }
}

//print matrix
void printMatrix(const Matrix* mat) {
    for (int i = 0; i < mat->rows; ++i) {
        for (int j = 0; j < mat->cols; ++j) {
            printf("%d ", mat->data[i][j]);
        }
        printf("\n");
    }
}

//add matricies
Matrix addMatrix(const Matrix* A, const Matrix* B) {
    if (A->rows != B->rows || A->cols != B->cols) {
        printf("Addition Error: Dimension mismatch.\n");
        return createMatrix(0, 0);
    }

    Matrix result = createMatrix(A->rows, A->cols);
    for (int i = 0; i < A->rows; ++i)
        for (int j = 0; j < A->cols; ++j)
            result.data[i][j] = A->data[i][j] + B->data[i][j];

    return result;
}

//matrix multiplcation
Matrix multiplyMatrix(const Matrix* A, const Matrix* B) {
    if (A->cols != B->rows) {
        printf("Multiplication Error: Dimension mismatch.\n");
        return createMatrix(0, 0);
    }

    Matrix result = createMatrix(A->rows, B->cols);
    for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < B->cols; ++j) {
            result.data[i][j] = 0;  // ✅ initialize to 0
            for (int k = 0; k < A->cols; ++k)
                result.data[i][j] += A->data[i][k] * B->data[k][j];
        }
    }

    return result;
}

//scalar multiplication
Matrix scalarMultiplyMatrix(const Matrix* A, int scalar) {
    Matrix result = createMatrix(A->rows, A->cols);
    for (int i = 0; i < A->rows; ++i)
        for (int j = 0; j < A->cols; ++j)
            result.data[i][j] = A->data[i][j] * scalar;

    return result;
}

//matrix transpose
Matrix transposeMatrix(const Matrix* A) {
    Matrix result = createMatrix(A->cols, A->rows);
    for (int i = 0; i < A->rows; ++i)
        for (int j = 0; j < A->cols; ++j)
            result.data[j][i] = A->data[i][j];

    return result;
}

int main() {
    int rowsA, colsA, rowsB, colsB, rowsC, colsC;

    printf("Enter rows and cols for Matrix A: ");
    scanf("%d %d", &rowsA, &colsA);
    Matrix A = createMatrix(rowsA, colsA);
    inputMatrix(&A);

    printf("Enter rows and cols for Matrix B: ");
    scanf("%d %d", &rowsB, &colsB);
    Matrix B = createMatrix(rowsB, colsB);
    inputMatrix(&B);

    printf("Enter rows and cols for Matrix C: ");
    scanf("%d %d", &rowsC, &colsC);
    Matrix C = createMatrix(rowsC, colsC);
    inputMatrix(&C);

    printf("\nMatrix A:\n");
    printMatrix(&A);

    printf("\nMatrix B:\n");
    printMatrix(&B);

    printf("\nMatrix C:\n");
    printMatrix(&C);

    Matrix threeB = scalarMultiplyMatrix(&B, 3);
    Matrix CT = transposeMatrix(&C);
    Matrix mult = multiplyMatrix(&threeB, &CT);
    Matrix D = addMatrix(&A, &mult);

    printf("\nD = A + (3 * B) * C^T:\n");
    printMatrix(&D);

    //free all matrices
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&threeB);
    freeMatrix(&CT);
    freeMatrix(&mult);
    freeMatrix(&D);

    return 0;
}