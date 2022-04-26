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

#ifndef _LINALG_DECOMPOSITIONS_CPP_
#define _LINALG_DECOMPOSITIONS_CPP_

#include "../matrix.h"
#include "../vector.h"
#include "../linalg/algorithms.h"

#include <vector>
#include <iostream>

namespace Matrix {

template <typename DType>
std::vector<Matrix<DType>> LU(Matrix<DType> A) {
    auto __shape = A.get_shape();
    int N = __shape[0];

    Matrix<DType> L = identity<DType>(N);
    Matrix<DType> U = zeros<DType>(N, N);

    std::vector<Matrix<DType>> RESULT;

    for(int i = 0; i < N; i++)
        U(0, i) = A(0, i);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i > j) {
                L(i, j) = A(i, j);
                for (int k = 0; k < std::min(i, j); k++)
                    L(i, j) -= L(i, k) * U(k, j);

                if (U(j, j) == 0) // to control whether there exists LU decomposition of A matrix (but i am not sure it's correct way) 
                    return RESULT;
                L(i, j) /= U(j, j);
            } else {
                U(i, j) = A(i, j);
                for (int k = 0; k < std::min(i, j); k++) 
                    U(i, j) -= L(i, k) * U(k, j);
            }
        }
    }

    RESULT.push_back(L);
    RESULT.push_back(U);
    return RESULT;
}

template <typename DType>
std::vector<Matrix<DType>> QR(Matrix<DType> A) {
    auto __shape = A.get_shape();

    std::vector<Vector<DType>> a_vectors = to_column_vectors(A);
    std::vector<Vector<DType>> q_vectors = gram_schmidt(a_vectors);

    Matrix<DType> Q = from_column_vectors(q_vectors);
    Matrix<DType> R = zeros<DType>(__shape[1], __shape[1]); 

    for (int i = 0; i < __shape[1]; i++) {
        for (int j = i; j < __shape[1]; j++) {
            R(i, j) = vector_dot(q_vectors[i], a_vectors[j]);
        }
    }

    return {Q, R};
}

template <typename DType>
std::vector<Matrix<DType>> cholesky(Matrix<DType> A) {

    // assert A is two dimensional matrix
    // assert A is square and symetric matrix

    auto __shape = A.get_shape();
    int N = __shape[0];
    int M = __shape[1];

    Matrix<DType> L(A);
    Matrix<DType> LT(A);

    for (int j = 0; j < N; j++) {
        for (int k = 0; k < j; k++)
            L(j, j) -= L(j, k) * L(j, k);

        L(j, j) = std::sqrt(L(j, j));

        for (int i = N - 1; i > j; i--) {
            for (int k = 0; k < j; k++)
                L(i, j) -= L(i, k) * L(j, k);
            L(i, j) /= L(j, j);
            L(j, i) = 0;
        }
        
    }

    LT = transpoze(L);

    return {L, LT};
}

//std::vector<Matrix<DType>> eigen(Matrix<DType> A) {}

//std::vector<Matrix<DType>> SVD(Matrix<DType> A) {}
}

#endif // end of _LINALG_DECOMPOSITIONS_CPP_
