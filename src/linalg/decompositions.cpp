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

#ifndef _LINALG_DECOMPOSITIONS_
#define _LINALG_DECOMPOSITIONS_

#include "../matrix.h"
#include "../linalg/algorithms.h"
#include <vector>
#include <iostream>

namespace Matrix {

template <typename DType>
std::vector<Matrix<DType>> LU(Matrix<DType> A) {
    auto __shape = A.get_shape();
    int N = __shape[0];

    Matrix<DType> L = identity<DType>(N);
    Matrix<DType> U = A;

    std::vector<Matrix<DType>> RESULT;

    for (int pivot = 0; pivot < N - 1; pivot++) {
        if (U(pivot, pivot) == 0)
            return RESULT;

        for (int x = pivot + 1; x < N; x++) {
            double co = U(x, pivot) / U(pivot, pivot);
            replace_rows(U, pivot, x, -co);
            replace_rows(L, pivot, x, -co);
            U(x, pivot) = 0;
        }
    }

    RESULT.push_back(inv(L));
    RESULT.push_back(U);
    return RESULT;
}

//std::vector<Matrix<DType>> QR(Matrix<DType> A) {}

//std::vector<Matrix<DType>> cholesky(Matrix<DType> A) {}

//std::vector<Matrix<DType>> eigen(Matrix<DType> A) {}

//std::vector<Matrix<DType>> SVD(Matrix<DType> A) {}
}

#endif // end of _LINALG_DECOMPOSITIONS
