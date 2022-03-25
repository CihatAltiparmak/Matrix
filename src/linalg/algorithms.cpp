#include "matrix.h"

namespace Matrix {

/*
 * The function that returns the inverse of the given matrix.
 * 
 * The function returns the inverse of the given matrix if there exists.
 * If the matrix is singular matrix(it has no its inverse) returns the matrix with zeros.
 *
 * The algorithm runs folowing. But the main important trick is the transformation [A | I] -> [I | invA] 
 * I presents identity matrix
 *
 * Firstly, we create a identity matrix that is available for A. we deep-copy the matrix A to the matrix B.
 * Then, we start first row and first column (the up-left side of the matrix, shortly the point (0, 0) according to computer :))
 * We select this value. After that, we do row-reductions that zero the all values in column of where we are. 
 * We apply this row reductions for I matrix. Then the current row and current column are increased by 1. (to forward diagonally)
 * In the end, the B matrix turn into upper-triangular matrix.
 * Now, we start the last row and last column. We apply row reductions to zero the all elements above column where we are. 
 * This row-reductions applies for I matrix.
 *
 * Finally, A turn into I, I turns into invA.
 * 
 * @param A the matrix
 * 
 * @retval the inverse of the matrix A
 */
template <typename DType>
Matrix<DType> inv(Matrix<DType> A) {
    auto __shape = A.get_shape();

    assert((__shape.size() != 2) &&
        "The matrix must be the square matrix!");
    assert((__shape[0] == __shape[1]) &&
        "The matrix must be the square matrix!");

    int N = __shape[0];

    Matrix<DType> I = identity<DType>(N);
    Matrix<DType> B = A;

    for (int x = 0; x < N; x++) {
        for (int row = x + 1; row < N; row++) {
            if (B(x, x) == 0.0) {
                int bci, bri;
                for (bri = x; bci < N; bci++)
                    if (B(bri, x) != 0.0)
                        break;

                for (int bci = 0; bci < N; bci++) 
                    swap(B[bri][bci], B[x][x]);
            }
            // FIXME Gümledik
            double e = B(row,x) / B(x, x);
            B(row, x) = 0.0;

            for (int col = x + 1; col < N; col++)
                B(row, col) -= e * B(x, col);

            for (int col = 0; col < N; col++)
                I(row, col) -= e * I(x, col);
        }
    }

    for (int x = N - 1; x >= 0; x--) {
        double bxx = B(x, x);
        
        for (int row = x - 1; row >= 0; row--) {
            double e = B(row, x) / bxx;

            for (int col = 0; col < N; col++)
                I(row, col) -= e * I(x, col); 
        }

        for (int col = 0; col < N; col++)
            I(x, col) /= bxx;
    }

    return I;
}

template <typename DType>
double det(Matrix<DType> A) {

    int N = A.get_shape()[0];

    double determinant = 1;
    Matrix<DType> B = A;

    for (int x = 0; x < N; x++) {
        double bxx = B(x, x);

        for (int row = x + 1; row < N; row++) {
            double e = B(row,x) / bxx;

            for (int col = x + 1; col < N; col++)
                B(row, col) -= e * B(x, col);
        }
    }

    for (int x = N - 1; x >= 0; x--)
        determinant *= B(x, x); 

    return determinant;
}

}// end of namespace
