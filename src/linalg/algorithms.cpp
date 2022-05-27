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

#ifndef _LINALG_ALGORITHMS_CPP_
#define _LINALG_ALGORITHMS_CPP_

#include "../matrix.h"
#include "../vector.h"
#include "../linalg/decompositions.h"
#include "../errors.h"

namespace Matrix {

/*
 * The function that returns the inverse of the given matrix.
 * 
 * The function returns the inverse of the given matrix if there exists.
 * If the matrix is singular matrix(it has no its inverse) it is raised a error. 
 *
 * The algorithm runs following. But the main important trick is the LUP decomposition.
 *
 * If there exists inverse of A matrix, the matrix A is able to be factorized by LUP decomposition. 
 * Otherwise, While LUP decomposition, it is raised that the matrix A cannot be decomposed by LUP decomposition.
 * For more information, please look at https://github.com/CihatAltiparmak/Matrix/blob/main/src/linalg/decompositions.cpp#L38-L93  
 * 
 * Firstly, the matrix A is factorized by LUP decomposition. After that, we find their inverses of L, U
 * and P matrices. 
 * 
 * Finally, we make matrix multiplication like this. 
 * 
 * inv(A) = inv(P^-1 LU) 
 *        = inv(U) inv(L) inv(P^-1) 
 *        = inv(U) inv(L) P
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

    try {
        auto lup = LUP(A);

        int N = __shape[0];

        Matrix<DType> invL = identity<DType>(N);
        Matrix<DType> invU = identity<DType>(N);

        // to find the inverse of L in LUP decomposition
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {

                for (int k = 0; k <= i; k++) {
                    invL(j, k) -= invL(i, k) * lup[0](j, i);
                }
            }
        }

        // to find the inverse of U in LUP decomposition
        // firstly, scale the rows of U matrix by its diagonal
        for (int i = 0; i < N; i++) { 
            double divisior = lup[1](i, i);
            invU(i, i) /= divisior;
            for (int j = i; j < N; j++) {
                lup[1](i, j) /= divisior;
            }
        }

        for (int i = N - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                for (int k = N - 1; k >= i; k--) {
                    invU(j, k) -= invU(i, k) * lup[1](j, i);
                }
            }
        }

        // P is permutation matrix, therefore, P^-1 = P^T
        // If PA = LU => A = P^T LU, so, A^-1 = U^-1 L^-1 P
        Matrix<DType> invA = dot(dot(invU, invL), transpoze(lup[2]));

        return invA;
    } catch (DecompositionError& e) {
        throw InverseOfMatrixNotFoundError();
    } 
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

    try {
        auto U = LUP(A)[1];
        int N = __shape[0];
        double determinant = 1;

        for (int i = 0; i < N; i++)
            determinant *= U(i, i);

        return determinant;
    } catch (DecompositionError& e) {
        return 0;
    }
}

}// end of namespace

#endif // end of _LINALG_ALGORITHMS_CPP_

