#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    int** data;
} Matrix;

//initialize a matrix with given dimensions
Matrix createMatrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        mat.data[i] = (int*)calloc(cols, sizeof(int));
    }
    return mat;
}

//free the matrix memory
void freeMatrix(Matrix* mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
}

//matrix setter
void set(Matrix* mat, int i, int j, int val) {
    mat->data[i][j] = val;
}

//matrix getter
int get(Matrix* mat, int i, int j) {
    return mat->data[i][j];
}

//matrix scalar multiplication
Matrix multiplyScalar(Matrix* mat, int scalar) {
    Matrix result = createMatrix(mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
        for (int j = 0; j < mat->cols; j++)
            result.data[i][j] = mat->data[i][j] * scalar;
    return result;
}

//transpose matrix
Matrix transpose(Matrix* mat) {
    Matrix result = createMatrix(mat->cols, mat->rows);
    for (int i = 0; i < mat->rows; i++)
        for (int j = 0; j < mat->cols; j++)
            //row i becomes column i
            result.data[j][i] = mat->data[i][j];
    return result;
}


//matrix multiplication
Matrix multiply(Matrix* a, Matrix* b) {
    Matrix result = createMatrix(a->rows, b->cols);
    for (int i = 0; i < a->rows; i++)
        for (int j = 0; j < b->cols; j++)
            for (int k = 0; k < a->cols; k++)
                //compute dot product
                result.data[i][j] += a->data[i][k] * b->data[k][j];
    return result;
}

//matrix addition
Matrix add(Matrix* a, Matrix* b) {
    Matrix result = createMatrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++)
        for (int j = 0; j < a->cols; j++)
            result.data[i][j] = a->data[i][j] + b->data[i][j];
    return result;
}

//print matrix
void print(Matrix* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%d ", mat->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    //matrix A
    //6 4
    //8 3
    Matrix A = createMatrix(2, 2);
    set(&A, 0, 0, 6); set(&A, 0, 1, 4);
    set(&A, 1, 0, 8); set(&A, 1, 1, 3);
    print(&A);

    //matrix B
    //1 2 3
    //4 5 6
    Matrix B = createMatrix(2, 3);
    set(&B, 0, 0, 1); set(&B, 0, 1, 2); set(&B, 0, 2, 3);
    set(&B, 1, 0, 4); set(&B, 1, 1, 5); set(&B, 1, 2, 6);
    print(&B);

    //matrix C
    //2 4 6
    //1 3 5
    Matrix C = createMatrix(2, 3);
    set(&C, 0, 0, 2); set(&C, 0, 1, 4); set(&C, 0, 2, 6);
    set(&C, 1, 0, 1); set(&C, 1, 1, 3); set(&C, 1, 2, 5);
    print(&C);

    //D = A + (3 * B) * C^T
    //  90  70
    // 200 150
    Matrix threeB = multiplyScalar(&B, 3);
    Matrix CT = transpose(&C);
    Matrix prod = multiply(&threeB, &CT);
    Matrix D = add(&A, &prod);

    printf("D = A + (3 * B) * C^T:\n");
    print(&D);

    // Free memory
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&threeB);
    freeMatrix(&CT);
    freeMatrix(&prod);
    freeMatrix(&D);

    return 0;
}