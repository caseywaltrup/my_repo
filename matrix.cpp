#include <iostream>
using namespace std;

class Matrix {
private:
    int rows, cols;
    int** data;

public:
    //matrix constructor
    Matrix(int r, int c) : rows(r), cols(c) {
        //initialize n rows
        data = new int*[rows];
        //for each row
        for (int i = 0; i < rows; i++) {
            //make m columns
            data[i] = new int[cols]();
        }
    }

    //data setter
    void set(int i, int j, int val) {
        data[i][j] = val;
    }

    //data getter
    int get(int i, int j) const {
        return data[i][j];
    }

    //scalar multiplication function 
    Matrix operator*(int scalar) const {
        //initialize result matrix
        Matrix result(rows, cols);
        //multiply all m*n cells by the scalar
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] * scalar;
        return result;
    }

    //matrix transpose
    Matrix transpose() const {
        //initialize result matrix
        Matrix result(cols, rows);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                //row i becomes column i
                result.data[j][i] = data[i][j];
        return result;
    }

    //multiply 2 matrices
    Matrix operator*(const Matrix& other) const {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j)
                for (int k = 0; k < cols; ++k)
                    //compute dot product
                    result.data[i][j] += data[i][k] * other.data[k][j];
        return result;
    }

    //add 2 matrices
    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                //simply add the corresponding cells
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    //prints the matrix
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j)
                cout << data[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
};

int main() {
    //matrix A
    //6 4
    //8 3
    Matrix A(2, 2);
    A.set(0, 0, 6); A.set(0, 1, 4);
    A.set(1, 0, 8); A.set(1, 1, 3);
    A.print();

    //matrix B
    //1 2 3
    //4 5 6
    Matrix B(2, 3);
    B.set(0, 0, 1); B.set(0, 1, 2); B.set(0, 2, 3);
    B.set(1, 0, 4); B.set(1, 1, 5); B.set(1, 2, 6);
    B.print();

    //matrix C
    //2 4 6
    //1 3 5
    Matrix C(2, 3);
    C.set(0, 0, 2); C.set(0, 1, 4); C.set(0, 2, 6);
    C.set(1, 0, 1); C.set(1, 1, 3); C.set(1, 2, 5);
    C.print();

    //D = A + (3 * B) * C^T
    //  90  70
    // 200 150
    Matrix threeB = B * 3;
    Matrix CT = C.transpose();
    Matrix result = A + (threeB * CT);

    cout << "D = A + (3 * B) * C^T:\n";
    result.print();

    return 0;
}