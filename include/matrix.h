#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <vector>

namespace Matrix {

template <typename DType>
class Matrix {

public:

    Matrix(DType, int);

    template <typename... OTHER_DIMS>
    Matrix(DType, int, OTHER_DIMS...);

    auto operator[](int);

//    ~Matrix();

    std::vector<int> get_shape();
    void print_shape();

private:
    std::vector<int> SHAPE; 
    void* MATRIX;

    template <typename... OTHER_DIMS>
    Matrix<DType>* __allocate_matrix(int, int, OTHER_DIMS...);
};

template <typename DType> 
Matrix<DType> dot(Matrix<DType>, Matrix<DType>);

template <typename DType> 
Matrix<DType> sigmoid(Matrix<DType>);

template <typename DType> 
Matrix<DType> exp(Matrix<DType>);

template <typename DType> 
Matrix<DType> tanh(Matrix<DType>);

template <typename DType> 
Matrix<DType> zero(Matrix<DType>);

template <typename DType> 
Matrix<DType> ones(Matrix<DType>);

template <typename DType> 
Matrix<DType> random(Matrix<DType>);

template <typename DType> 
Matrix<DType> reshape(Matrix<DType>);

template <typename DType> 
Matrix<DType> squeeze(Matrix<DType>);

template <typename DType> 
Matrix<DType> inv(Matrix<DType>);

template <typename DType> 
double det(Matrix<DType>);

} // end of Matrix namespace

#include "../src/matrix.cpp"

#endif
