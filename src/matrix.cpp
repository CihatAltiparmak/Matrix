//#ifndef _MATRIX_H_
//#define _MATRIX_H_

//#include "matrix.h"
//#include <math.h>
//#include <vector>

#include <math.h>
#include <ctime>
#include <cstdlib>
#include <memory>
#include <iostream>
#include <functional>
#include <assert.h>

namespace Matrix {

template <typename DType>
template <typename... DIMS>
Matrix<DType>::Matrix(DIMS... dims)
{
    SHAPE = {dims...};

    assert(SHAPE.size() > 0 && 
        "The matrix must have at least one dimension.");
    
    MATRIX_SIZE = 1;

    for (auto dim : SHAPE) 
        MATRIX_SIZE *= dim;

    MATRIX = new DType[MATRIX_SIZE];

    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] = i;
}

template <typename DType>
Matrix<DType>::Matrix(Matrix<DType>& matrix_copy) {
    SHAPE       = matrix_copy.SHAPE;
    MATRIX_SIZE = matrix_copy.MATRIX_SIZE;

    MATRIX = new DType[MATRIX_SIZE];
    
    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] = matrix_copy.MATRIX[i];
}

template <typename DType>
template <typename... Index>
DType Matrix<DType>::operator()(Index... index) {
 
    assert(sizeof...(index) == SHAPE.size() && 
        "The number of index parameters must be same as the matrix' shape!");

    std::vector<int> __index = {index...};
  
    int dp = 1;  // dynamic programming tricks
    int real_index = 0; 

    for (int i = SHAPE.size() - 1; i >= 0; i--) { 
        real_index += dp * __index[i];
        dp *= SHAPE[i];
    }
    
    assert(real_index < MATRIX_SIZE &&
        "Out of bounds!");

    return MATRIX[real_index];
}

template <typename DType>
Matrix<DType>& Matrix<DType>::operator/=(DType& val) {

    assert((val != 0) && 
        "The divisor cannot be zero!");

    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] /= val;

    return *this;
}

template <typename DType>
Matrix<DType> Matrix<DType>::operator/(DType& val) {
    
    assert((val != 0) && 
        "The divisor cannot be zero!");

    Matrix<DType> RESULT(*this);
    RESULT /= val;

    return RESULT;
}

template <typename DType>
Matrix<DType>& Matrix<DType>::operator+=(DType& val) {
    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] += val;

    return *this;
}

template <typename DType>
Matrix<DType> Matrix<DType>::operator+(DType& val) {
    Matrix<DType> RESULT(*this);
    RESULT += val;
    
    return RESULT;
}

template <typename DType>
Matrix<DType>& Matrix<DType>::operator+=(Matrix<DType>& A) {
    
    assert((SHAPE.size() == A.SHAPE.size()) &&
        "The dimensions of the matrices must be same.");

    for (int i = 0; i < SHAPE.size(); i++)
        assert((SHAPE[i] == A.SHAPE[i]) &&
            "The dimensions of the matrices must be same.");

    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] += A.MATRIX[i];

    return *this;
}

template <typename DType>
Matrix<DType> Matrix<DType>::operator+(Matrix<DType>& A) {
    
    assert((SHAPE.size() == A.SHAPE.size()) &&
        "The dimensions of the matrices must be same.");

    for (int i = 0; i < SHAPE.size(); i++)
        assert((SHAPE[i] == A.SHAPE[i]) &&
            "The dimensions of the matrices must be same.");

    Matrix<DType> RESULT(*this);
    RESULT += A;
    
    return RESULT;
}

template <typename DType>
Matrix<DType>& Matrix<DType>::operator-=(DType& val) { 

    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] -= val;

    return *this;
}

template <typename DType>
Matrix<DType> Matrix<DType>::operator-(DType& val) {
    
    Matrix<DType> RESULT(*this);
    RESULT -= val;
    
    return RESULT;
}

template <typename DType>
Matrix<DType>& Matrix<DType>::operator-=(Matrix<DType>& A) {

    assert((SHAPE.size() == A.SHAPE.size()) &&
        "The dimensions of the matrices must be same.");

    for (int i = 0; i < SHAPE.size(); i++)
        assert((SHAPE[i] == A.SHAPE[i]) &&
            "The dimensions of the matrices must be same.");


    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] -= A.MATRIX[i];

    return *this;
}

template <typename DType>
Matrix<DType> Matrix<DType>::operator-(Matrix<DType>& A) {

    assert((SHAPE.size() == A.SHAPE.size()) &&
        "The dimensions of the matrices must be same.");

    for (int i = 0; i < SHAPE.size(); i++)
        assert((SHAPE[i] == A.SHAPE[i]) &&
            "The dimensions of the matrices must be same.");

    Matrix<DType> RESULT(*this);
    RESULT -= A;
    
    return RESULT;
}

template <typename DType>
Matrix<DType>& Matrix<DType>::operator*=(DType& val) {

    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] *= val;

    return *this;
}

template <typename DType>
Matrix<DType> Matrix<DType>::operator*(DType& val) {

    Matrix<DType> RESULT(*this);
    RESULT *= val;
    
    return RESULT;
}

template <typename DType>
Matrix<DType>& Matrix<DType>::operator*=(Matrix<DType>& A) {

    assert((SHAPE.size() == A.SHAPE.size()) &&
        "The dimensions of the matrices must be same.");

    for (int i = 0; i < SHAPE.size(); i++)
        assert((SHAPE[i] == A.SHAPE[i]) &&
            "The dimensions of the matrices must be same.");

    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] *= A.MATRIX[i];

    return *this;
}

template <typename DType>
Matrix<DType> Matrix<DType>::operator*(Matrix<DType>& A) {

    assert((SHAPE.size() == A.SHAPE.size()) &&
        "The dimensions of the matrices must be same.");

    for (int i = 0; i < SHAPE.size(); i++)
        assert((SHAPE[i] == A.SHAPE[i]) &&
            "The dimensions of the matrices must be same.");

    Matrix<DType> RESULT(*this);
    RESULT *= A;
    
    return RESULT;
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

    auto a_shape = A.get_size();
    auto b_shape = B.get_size();

    assert(a_shape[1] == b_shape[0] &&
        "The matrix multiplication is impossible");

    Matrix<DType> AB(a_shape[0], b_shape[1]);

    for (int x = 0; x < a_shape[0]; x++) {
        for (int y = 0; y < b_shape[1]; y++)
            for (int i = 0; i < a_shape[1]; i++)
                AB[x][y] = A[x][i] * B[i][y];
    }

    return AB;
}

/* 
 * @brief : apply sigmoid func to the matrix elements
 * @param  A
 * @return res
 */
template <typename DType>
Matrix<DType> sigmoid(Matrix<DType>& A) {

    assert((std::is_same<DType, double>::value) && 
        "DType must be double!");
    
    Matrix<DType> RESULT(A); 
    
    for (int i = 0; i < A.MATRIX_SIZE; i++) {
        double x = RESULT.MATRIX[i];
        double result = 1 / (1 + std::exp(-1 * x));
        RESULT.MATRIX[i] = result;
    }
    
    return RESULT;
}


/* 
 * @brief : apply exponent func to the matrix elements
 * @param  A
 * @return res
 */
template <typename DType>
Matrix<DType> exp(Matrix<DType>& A) {

    assert((std::is_same<DType, double>::value) && 
        "DType must be double!");

    Matrix<DType> RESULT(A);
 
    for (int i = 0; i < A.MATRIX_SIZE; i++) {
        double x = RESULT.MATRIX[i];
        RESULT.MATRIX[i] = std::exp(x);
    } 
    return RESULT; 
}

/* 
 * @brief : apply tanh func to the matrix elements
 * @param  A
 * @return res
 */
template <typename DType>
Matrix<DType> tanh(Matrix<DType>& A) {

    assert((std::is_same<DType, double>::value) && 
        "DType must be double!");

    Matrix<DType> RESULT(A);
    
    for (int i = 0; i < A.MATRIX_SIZE; i++) {
        double x = RESULT.MATRIX[i];
        RESULT.MATRIX[i] = 
            (std::exp(x) - std::exp(-x)) / (std::exp(x) + std::exp(-x));
    
    }
    return RESULT;
}

/* 
 * @brief : assign zero value to the matrix elements
 * @param  A
 * @return res
 */
template <typename DType, typename... DIMS>
Matrix<DType> zero(DIMS... dims) {
    Matrix<DType> RESULT(dims...);
    
    for (int i = 0; i < RESULT.MATRIX_SIZE; i++)
        RESULT.MATRIX[i] = 0;
}

/* 
 * @brief : assign one value to the matrix elements
 * @param  A
 * @return res
 */
template <typename DType, typename... DIMS>
Matrix<DType> ones(DIMS... dims) {
    Matrix<DType> RESULT(dims...);
    
    for (int i = 0; i < RESULT.MATRIX_SIZE; i++)
        RESULT.MATRIX[i] = 1;
}

/* 
 * @brief : assign random value to the matrix elements
 * @param  A
 * @return res
 */
template <typename DType, typename... DIMS>
Matrix<DType> random(DIMS... dims) {
    Matrix<DType> RESULT(dims...);
   
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // be careful 
    for (int i = 0; i < RESULT.MATRIX_SIZE; i++)
        RESULT.MATRIX[i] = std::rand();
}

/* 
 * @brief : reshape the matrix elements
 * @param  A
 * @return res
 */
template <typename DType, typename... DIMS>
Matrix<DType> reshape(Matrix<DType>& A, DIMS... dims) {
    A.SHAPE = {dims...};
}

/* 
 * @brief : get scalar value from matrices like [[1]], [[[1]]]
 * @param  A
 * @return res
 */

//template <typename DType>
//Matrix<DType> squeeze(Matrix<DType> A) {
    // not implemented
//}

/* 
 * @brief : find to the inverse of the matrix
 * @param  A
 * @return res
 */
//template <typename DType>
//Matrix<DType> inv(Matrix<DType> A) {
    // not implemented
//}

/* 
 * @brief : find the determinant of the matrix
 * @param  A
 * @return res
 */
//template <typename DType>
//int det(Matrix<DType> A) {
    // not implemented
//}
} // end of namespace
