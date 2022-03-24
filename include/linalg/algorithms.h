#ifndef _LINALG_ALGORITHMS_H_
#define _LINALG_ALGORITHMS_H_

#include "../matrix.h"

namespace Matrix {

template <typename DType>
Matrix<DType> inv(Matrix<DType> A);

template <typename DType>
double det(Matrix<DType> A);

} // end of namespace 

#include "../../src/linalg/algorithms.cpp"


#endif
