#include "matrix.h"

namespace Matrix {

template <typename DType>
Matrix<DType> inv(Matrix<DType> A) {
    // assert shape ...

    int N = A.get_shape()[0];

    Matrix<DType> I = identity<DType>(N);
    Matrix<DType> B = A;

    for (int x = 0; x < N; x++) {
        for (int row = x + 1; row < N; row++) {
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
