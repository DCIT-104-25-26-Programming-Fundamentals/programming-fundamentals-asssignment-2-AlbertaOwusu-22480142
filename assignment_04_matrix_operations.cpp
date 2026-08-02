// =============================================================================
// PROGRAMMING FUNDAMENTALS — Assignment 4
// =============================================================================
//
// TASK: Matrix Operations
//
// Write a C++ program that performs three operations on matrices (2D arrays),
// each implemented in its own function.
//
// NOTE: Use a fixed maximum size of 10 for array dimensions.
//       Declare arrays as int matrix[10][10].
//
// -----------------------------------------------------------------------------
// PART A — Transpose a Matrix
// -----------------------------------------------------------------------------
// - Read an M x N matrix from the user.
// - Compute and display its transpose (rows become columns, columns become rows).
//
// Example (2 x 3 input):
//
//   Original Matrix:      Transposed Matrix:
//   1  2  3               1  4
//   4  5  6               2  5
//                         3  6
//
// -----------------------------------------------------------------------------
// PART B — Add Two Matrices
// -----------------------------------------------------------------------------
// - Read two matrices of exactly the same size (M x N).
// - Compute their element-wise sum and display the result.
//
// -----------------------------------------------------------------------------
// PART C — Multiply Two Matrices
// -----------------------------------------------------------------------------
// - Read matrix A of size M x N and matrix B of size N x P.
//   (Number of COLUMNS in A must equal number of ROWS in B.)
// - Compute and display the matrix product A x B (result is M x P).
//
// -----------------------------------------------------------------------------
// EXPECTED INPUT FORMAT
// -----------------------------------------------------------------------------
// The user enters each row's values one at a time:
//
//   Enter number of rows: 2
//   Enter number of columns: 3
//   Enter element [0][0]: 1
//   Enter element [0][1]: 2
//   ...
//
// -----------------------------------------------------------------------------
// REQUIREMENTS
// -----------------------------------------------------------------------------
// - Use nested loops for all operations (no external libraries).
// - Each operation must be in its own function (see scaffold below).
// - Display each matrix in a neat, aligned grid using setw().
// - Tip: Complete Part A first, then Parts B and C.
//

// =============================================================================
// YOUR CODE BELOW — remove the // symbols from the scaffold and fill it in
// =============================================================================

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

double** allocateMatrix(int rows, int cols) {
    double** mat = new double*[rows];
    for (int i = 0; i < rows; i++) {
        mat[i] = new double[cols];
    }
    return mat;
}

void freeMatrix(double** mat, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] mat[i];
    }
    delete[] mat;
}

double** readMatrix(int rows, int cols, const string& name) {
    double** mat = allocateMatrix(rows, cols);
    cout << "\nEnter elements for matrix " << name
         << " (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Enter element [" << i << "][" << j << "]: ";
            cin >> mat[i][j];
        }
    }
    return mat;
}

void printMatrix(double** mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(8) << mat[i][j];
        }
        cout << "\n";
    }
}

double** transposeMatrix(double** mat, int rows, int cols) {
    double** result = allocateMatrix(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = mat[i][j];
        }
    }
    return result;
}

double** addMatrices(double** a, double** b, int rows, int cols) {
    double** result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    return result;
}


double** multiplyMatrices(double** a, double** b, int m, int n, int p) {
    double** result = allocateMatrix(m, p);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

int main() {
    int choice;

    do {
        cout << "\n=====================================\n";
        cout << " MATRIX OPERATIONS MENU\n";
        cout << "=====================================\n";
        cout << "1. Transpose a Matrix\n";
        cout << "2. Add Two Matrices\n";
        cout << "3. Multiply Two Matrices\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
        
            int rows, cols;
            cout << "\nEnter number of rows: ";
            cin >> rows;
            cout << "Enter number of columns: ";
            cin >> cols;

            double** mat = readMatrix(rows, cols, "A");
            double** result = transposeMatrix(mat, rows, cols);

            cout << "\nOriginal Matrix:\n";
            printMatrix(mat, rows, cols);
            cout << "\nTransposed Matrix:\n";
            printMatrix(result, cols, rows);

            freeMatrix(mat, rows);
            freeMatrix(result, cols);

        } else if (choice == 2) {
        
            int rows, cols;
            cout << "\nEnter number of rows: ";
            cin >> rows;
            cout << "Enter number of columns: ";
            cin >> cols;

            double** a = readMatrix(rows, cols, "A");
            double** b = readMatrix(rows, cols, "B");
            double** result = addMatrices(a, b, rows, cols);

            cout << "\nSum Matrix (A + B):\n";
            printMatrix(result, rows, cols);

            freeMatrix(a, rows);
            freeMatrix(b, rows);
            freeMatrix(result, rows);

        } else if (choice == 3) {
        
            int m, n, n2, p;
            cout << "\nEnter number of rows for matrix A (M): ";
            cin >> m;
            cout << "Enter number of columns for matrix A (N): ";
            cin >> n;
            double** a = readMatrix(m, n, "A");

            cout << "\nEnter number of rows for matrix B (must equal N = "
                 << n << "): ";
            cin >> n2;
            cout << "Enter number of columns for matrix B (P): ";
            cin >> p;

            if (n2 != n) {
                cout << "\nError: Number of columns in A ("
                     << n << ") must equal number of rows in B ("
                     << n2 << "). Cannot multiply.\n";
                freeMatrix(a, m);
                continue;
            }

            double** b = readMatrix(n2, p, "B");
            double** result = multiplyMatrices(a, b, m, n, p);

            cout << "\nProduct Matrix (A x B):\n";
            printMatrix(result, m, p);

            freeMatrix(a, m);
            freeMatrix(b, n2);
            freeMatrix(result, m);

        } else if (choice == 4) {
            cout << "\nExiting program. Goodbye!\n";
        } else {
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
