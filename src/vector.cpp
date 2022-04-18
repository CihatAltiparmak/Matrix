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

#ifndef _VECTOR_CPP_
#define _VECTOR_CPP_

#include <vector>

#include "vector.h"

namespace Matrix {

template <typename DType>
template <typename... DIMS>
Vector<DType>::Vector(DIMS... dims) 
: Matrix<DType>(dims...)
{
    // assert the shape of matrix A is in format (N, 1) or (1, N)
    auto __shape = this->get_shape();

    assert(sizeof...(dims) == 2 && 
        "The vector must have 2 dimensions."); 

    assert((__shape[0] == 1 || __shape[1] == 1 ) && 
        "At least one dimesion of vector must be 1"); 
}

template <typename DType>
Vector<DType>::Vector(Matrix<DType> A) 
: Matrix<DType>(A)
{
    // assert the shape of matrix A is in format (N, 1) or (1, N)
    auto __shape = this->get_shape();

    assert(__shape.size() == 2 && 
        "The vector must have 2 dimensions.");
     

    assert((__shape[0] == 1 || __shape[1] == 1 ) && 
        "At least one dimesion of vector must be 1");
}

template <typename DType>
double vector_dot(Vector<DType> u, Vector<DType> v) {

    auto u_shape = u.get_shape();
    auto v_shape = v.get_shape();

    // assert u_shape = v_shape
    
    double result = 0;
    if (u_shape[0] != 1) {
        for (int i = 0; i < u_shape[0]; i++)
            result += u(i, 0) * v(i, 0);
    } else {
        for (int i = 0; i < u_shape[1]; i++)
            result += u(0, i) * v(0, i);
    }

    return result;
}

template <typename DType>
std::vector<Vector<DType>> to_column_vectors(Matrix<DType> A) {
    // assert 0 <= K < N

    auto __shape = A.get_shape();
    int N = __shape[0];
    int M = __shape[1];
    
    std::vector<Vector<DType>> column_vectors; // trajicomics

    for (int j = 0; j < M; j++) {
        Vector<DType> vec(N, 1);
        for (int i = 0; i < N; i++)
            vec(i, 0) = A(i, j);
        column_vectors.push_back(vec);
    }

    return column_vectors;
}

template <typename DType>
std::vector<Vector<DType>> to_row_vectors(Matrix<DType> A) {
    // assert 0 <= K < N

    auto __shape = A.get_shape();
    int N = __shape[0];
    int M = __shape[1];
    
    std::vector<Vector<DType>> row_vectors; // trajicomics

    for (int i = 0; i < N; i++) {
        Vector<DType> vec(1, M);
        for (int j = 0; j < M; j++)
            vec(0, j) = A(i, j);
        row_vectors.push_back(vec);
    }

    return row_vectors;
}

template <typename DType>
Matrix<DType> from_column_vectors(std::vector<Vector<DType>> column_vectors) {
    // assert vector shapes are same format and column_vectors is not empty
    int N = column_vectors[0].get_matrix_size();
    int M = column_vectors.size();

    Matrix<DType> RESULT_MATRIX(N, M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            RESULT_MATRIX(i, j) = column_vectors[j](i, 0);

    return RESULT_MATRIX;
}

template <typename DType>
Matrix<DType> from_row_vectors(std::vector<Vector<DType>> row_vectors) {
    // assert vector shapes are same format and row_vectors is not empty
    int N = row_vectors.size();
    int M = row_vectors[0].get_matrix_size();

    Matrix<DType> RESULT_MATRIX(N, M);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            RESULT_MATRIX(i, j) = row_vectors[i](0, j);

    return RESULT_MATRIX;
}

} // end of namespace Matrix

#endif // __VECTOR_CPP__ 
