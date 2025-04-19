#include <iostream>
#include <vector>
using namespace std;

class Matrix {
private:
    int rows, cols;
    vector<vector<int>> data;

public:
    Matrix(int r = 0, int c = 0) : rows(r), cols(c), data(r, vector<int>(c)) {}

    //input data for each spot in matrix
    void input() {
        cout << "Enter elements (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                cout << "Element [" << i << "][" << j << "]: ";
                cin >> data[i][j];
            }
    }

    //print matrix
    void print() const {
        for (const auto& row : data) {
            for (int val : row)
                cout << val << " ";
            cout << endl;
        }
    }

    //add matricies
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Matrix dimensions do not match\n";
            return Matrix();
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }
    
    //matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            cout << "Matrix dimensions do not match\n";
            return Matrix();
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j)
                for (int k = 0; k < cols; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
        return result;
    }

    //scalar multiplication
    Matrix operator*(int scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] * scalar;
        return result;
    }

    //matrix transpose
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                //row i becomes column i
                result.data[j][i] = data[i][j];
        return result;
    }
};

int main() {
    int rowsA, colsA, rowsB, colsB, rowsC, colsC;

    cout << "Enter rows and cols for Matrix A: ";
    cin >> rowsA >> colsA;
    Matrix A(rowsA, colsA);
    A.input();

    cout << "Enter rows and cols for Matrix B: ";
    cin >> rowsB >> colsB;
    Matrix B(rowsB, colsB);
    B.input();

    cout << "Enter rows and cols for Matrix C: ";
    cin >> rowsC >> colsC;
    Matrix C(rowsC, colsC);
    C.input();

    cout << "\nMatrix A:\n";
    A.print();

    cout << "\nMatrix B:\n";
    B.print();

    cout << "\nMatrix C:\n";
    C.print();

    Matrix threeB = B * 3;
    Matrix CT = C.transpose();
    Matrix result = A + (threeB * CT);

    cout << "D = A + (3 * B) * C^T:\n";
    result.print();

    return 0;
}