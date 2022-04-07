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
double Vector<DType>::norm(bool is_squared) {

    auto __shape = this->get_shape();
    double norm_of_vector = 0.0;


    if (__shape[0] != 1) {
        for (int i = 0; i < __shape[0]; i++)
            norm_of_vector += (*this)(i, 0) * (*this)(i, 0);
    } else {
        for (int i = 0; i < __shape[1]; i++)
            norm_of_vector += (*this)(0, i) * (*this)(0, i); 
    }   

    if (is_squared)
        return std::sqrt(norm_of_vector);
    else
        return norm_of_vector;
}

template <typename DType>
std::vector<Vector<DType>> get_column_vectors(Matrix<DType> A) {
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
std::vector<Vector<DType>> get_row_vectors(Matrix<DType> A) {
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

} // end of namespace Matrix

#endif // __VECTOR_CPP__ 