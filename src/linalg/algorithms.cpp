/* 
 * MIT License 
 *  
 * Copyright (c) 2022 CihatAltiparmak 
 *  
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions: 
 * 
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software. 
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE. 
 */

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

    assert((__shape.size() == 2) &&
        "The matrix must be the square matrix!");
    assert((__shape[0] == __shape[1]) &&
        "The matrix must be the square matrix!");

    int N = __shape[0];

    Matrix<DType> invA = identity<DType>(N);
    Matrix<DType> B = A;

    for (int pivot = 0; pivot < N; pivot++) {
        if (B(pivot, pivot) == 0) {
            bool is_pivot_found = false;
            for (int x = pivot + 1; x < N; x++) {
                if (B(x, pivot) != 0) {
                    swap_rows(B, x, pivot);
                    swap_rows(invA, x, pivot);
                    is_pivot_found = true;
                    break;
                }
            }
            if (!is_pivot_found) {
                return zeros<DType>(N, N); 
            }
        
        }
        
        // normalizing the relating row
        if (B(pivot, pivot) != 1) {
            scale_row(invA, pivot, 1 / B(pivot, pivot));
            scale_row(B, pivot, 1 / B(pivot, pivot));
        }

        for (int x = pivot + 1; x < N; x++) {
            replace_rows(invA, pivot, x, -B(x, pivot));
            replace_rows(B, pivot, x, -B(x, pivot));
        }
    }

    for (int x = N - 1; x >= 0; x--)
        for (int y = x - 1; y >= 0; y--)
            replace_rows(invA, x, y, -B(x, y));

    return invA;
}

/*
 * The function that returns the determinant of the matrix
 * 
 * The matrix use row-reduction method to find determinant. 
 * If the matrix is not square matrix, raise assertion error.
 * @param A the matrix
 * 
 * @retval the determinant of the matrix A
 */
template <typename DType>
double det(Matrix<DType> A) {
    auto __shape = A.get_shape();

    assert((__shape.size() == 2) &&
        "The matrix must be the square matrix!");
    assert((__shape[0] == __shape[1]) &&
        "The matrix must be the square matrix!");

    int N = __shape[0];

    Matrix<DType> B = A;
    double determinant = 1;

    for (int pivot = 0; pivot < N; pivot++) { 
        if (B(pivot, pivot) == 0) {
            bool is_pivot_found = false;
            for (int x = pivot + 1; x < N; x++) {
                if (B(x, pivot) != 0) {
                    swap_rows(B, x, pivot);
                    is_pivot_found = true;
                    break;
                }
            }
            if (!is_pivot_found) {
                return 0;
            }
        
        }
        
        if (B(pivot, pivot) != 1) {
            determinant *= B(pivot, pivot); 
            scale_row(B, pivot, 1 / B(pivot, pivot)); 
        }

        for (int x = pivot + 1; x < N; x++) {
            replace_rows(B, pivot, x, -B(x, pivot));
        }
    }

    for (int x = 0; x < N; x++)
        determinant *= B(x, x);

    return determinant;
}

}// end of namespace
