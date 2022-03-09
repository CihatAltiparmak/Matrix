//#ifndef _MATRIX_H_
//#define _MATRIX_H_

//#include "matrix.h"
//#include <math.h>
//#include <vector>
#include <memory>

#include <iostream>

namespace Matrix {

template <typename DType>
Matrix<DType>::Matrix(DType val, int dim) 
{

    SHAPE = {dim};
    MATRIX = new DType[dim];

    for (int i = 0; i < dim; i++)
        ((DType*)MATRIX)[i] = val;

}

template <typename DType>
template <typename... OTHER_DIMS>
Matrix<DType>::Matrix(DType val, int dim, OTHER_DIMS... other_dims)
{
    SHAPE = {dim, other_dims...};
    MATRIX = this->__allocate_matrix(dim, val, other_dims...);
}


template <typename DType>
auto Matrix<DType>::operator[](int i) {
    if (SHAPE.size() > 1) {
        return *((Matrix<DType>*)MATRIX + i);
    } else { 
        int val = ((DType*)MATRIX)[i];
        return Matrix<DType>(val, 1);
    }
}

template <typename DType>
template <typename... OTHER_DIMS>
Matrix<DType>* Matrix<DType>::__allocate_matrix(int n, int val, OTHER_DIMS... other_dims) {
    
    typename std::allocator<Matrix<DType>> alloc;
    typename std::allocator<Matrix<DType>>::pointer matrix_pointer;
 
    matrix_pointer = alloc.allocate(n);
    
    for (int i = 0; i < n; i++)
        alloc.construct(matrix_pointer + i, val, other_dims...); 
        
    return matrix_pointer;
}

template <typename DType>
std::vector<int> Matrix<DType>::get_shape(){
    return SHAPE;
}

template <typename DType>
void Matrix<DType>::print_shape() {
    std::cout << "(";
    for (auto v : SHAPE)
        std::cout << v << ", ";
    std::cout << ")" << std::endl;
}


/* 
 * @brief : gives matrix product of AB
 * @param  A
 * @param  B
 * @return res
 */
template <typename DType>
Matrix<DType> dot(Matrix<DType> A, Matrix<DType> B) {
    // not implemented
}

/* 
 * @brief : apply sigmoid func to the matrix elements
 * @param  A
 * @return res
 */
template <typename DType>
Matrix<DType> sigmoid(Matrix<DType> A) {
    // not implemented
}

/* 
 * @brief : apply exponent func to the matrix elements
 * @param  A
 * @return res
 */
template <typename DType>
Matrix<DType> exp(Matrix<DType> A) {
    // not implemented
}

/* 
 * @brief : apply tanh func to the matrix elements
 * @param  A
 * @return res
 */
template <typename DType>
Matrix<DType> tanh(Matrix<DType> A) {
    // not implemented
}

/* 
 * @brief : assign zero value to the matrix elements
 * @param  A
 * @return res
 */
template <typename DType>
Matrix<DType> zero(Matrix<DType> A) {
    // not implemented
}

/* 
 * @brief : assign one value to the matrix elements
 * @param  A
 * @return res
 */
template <typename DType>
Matrix<DType> ones(Matrix<DType> A) {
    // not implemented
}

/* 
 * @brief : assign random value to the matrix elements
 * @param  A
 * @return res
 */
template <typename DType>
Matrix<DType> random(Matrix<DType> A) {
    // not implemented
}

/* 
 * @brief : reshape the matrix elements
 * @param  A
 * @return res
 */
template <typename DType>
Matrix<DType> reshape(Matrix<DType> A) {
    // not implemented
}

/* 
 * @brief : get scalar value from matrices like [[1]], [[[1]]]
 * @param  A
 * @return res
 */
template <typename DType>
Matrix<DType> squeeze(Matrix<DType> A) {
    // not implemented
}

/* 
 * @brief : find to the inverse of the matrix
 * @param  A
 * @return res
 */
template <typename DType>
Matrix<DType> inv(Matrix<DType> A) {
    // not implemented
}

/* 
 * @brief : find the determinant of the matrix
 * @param  A
 * @return res
 */
template <typename DType>
int det(Matrix<DType> A) {
    // not implemented
}

}
