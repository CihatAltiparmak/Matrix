#ifndef _LINALG_DECOMPOSITIONS_H_
#define _LINALG_DECOMPOSITIONS_H_

namespace Matrix {
    template <typename DType>
    std::vector<Matrix<DType>> LU(Matrix<DType>);

    #if 0
    template <typename DType>
    std::vector<Matrix<DType>> QR(Matrix<DType>);

    template <typename DType>
    std::vector<Matrix<DType>> cholesky(Matrix<DType>); 

    // be careful
    template <typename DType>
    std::vector<Matrix<DType>> eigen(Matrix<DType>);

    template <typename DType>
    std::vector<Matrix<DType>> SVD(Matrix<DType>);
    #endif

}

#include "decompositions.cpp"

#endif // end of _LINALG_DECOMPOSITIONS_H_
