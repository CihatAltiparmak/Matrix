#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <vector>
#include "matrix.h"

namespace Matrix {

template <typename DType>
class Vector: public Matrix<DType> {
    public: 

//        Vector<DType>() = default;
        template <typename... DIMS>
        Vector<DType>(DIMS...);
        Vector<DType>(Matrix<DType>);

        double norm(bool);
};

template <typename DType>
std::vector<Vector<DType>> get_column_vectors(Matrix<DType>);

template <typename DType>
std::vector<Vector<DType>> get_row_vectors(Matrix<DType>);

}

#include "vector.cpp"

#endif
