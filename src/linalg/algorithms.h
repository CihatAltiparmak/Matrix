#ifndef _LINALG_ALGORITHMS_H_
#define _LINALG_ALGORITHMS_H_

#include "../matrix.h"

namespace Matrix {

template <typename DType>
Matrix<DType> inv(Matrix<DType> A);

template <typename DType>
double det(Matrix<DType> A);

//template <typename DType>
//Matrix<DType> gram_schmidt(Matrix<DType>);

} // end of namespace 

#include "algorithms.cpp"
#endif
