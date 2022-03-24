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
Matrix<DType>::Matrix(Matrix<DType>const& matrix_copy) {
    *this = matrix_copy;
}

template <typename DType>
Matrix<DType>::~Matrix() {
    if (MATRIX != nullptr)
        delete[] MATRIX;
}

template <typename DType>
Matrix<DType>& Matrix<DType>::operator=(Matrix<DType>const& matrix_copy) {
    SHAPE       = matrix_copy.SHAPE;
    MATRIX_SIZE = matrix_copy.MATRIX_SIZE;

    MATRIX = new DType[MATRIX_SIZE];
    
    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] = matrix_copy.MATRIX[i];

    return *this;
}

/*
 * The operator overloading to be able to assign and return by using indexes
 *
 * This operator overloading can used to change the chosed-by-indexes element
 * of matrix. For example: 
 * 
 * Matrix::Matrix<double> A(3, 3, 3);
 * A(1, 2, 0) = -1.0;
 *
 *
 * In this example, we create the matrix with the dimensions (3, 3, 3), 
 * then we change the element of A_1_2_3 in the A matrix.
 *
 * Similarly, we can return the element A_1_2_3 of the A matrix.
 *
 * double x = A(1, 2, 0);
 *
 * @param index the necessary integer indexes. If the number of indexes
 * is larger than the size of matrix, it's raised assertion error. In addition
 * if the indexes cause the out of bounds, it's raised assertion error.
 * 
 * @retval the element of the matrix in index
 */
template <typename DType>
template <typename... Index>
DType& Matrix<DType>::operator()(Index... index) {
 
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

/*
 * The operator overloading to divide elements of the matrix by certain value
 *
 * This operator overloading can used to divide element
 * of matrix by the certain value. For example: 
 * 
 * Matrix::Matrix<double> A(3, 3, 3);
 *
 * // [[1.0, 2.0, 3.0],
 * //  [4.0, 5.0, 6.0],
 * //  [7.0, 8.0, 9.0]]
 *
 * A /= 2;
 *
 * // [[0.5, 1.0, 1.5],
 * //  [2.0, 2.5, 3.0],
 * //  [3.5, 4.0, 4.5]]
 *
 *
 * @param val the divisor of the elements of the matrix
 * 
 * @retval the same matrix whose elemets divided by parameter val
 */
template <typename DType>
Matrix<DType>& Matrix<DType>::operator/=(DType& val) {

    assert((val != 0) && 
        "The divisor cannot be zero!");

    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] /= val;

    return *this;
}

/*
 * The operator overloading to produce the new matrix by dividing 
 * elements of the matrix by certain value without changing 
 * the dividing matrix.
 *
 * For example: 
 * 
 * Matrix::Matrix<double> A(3, 3);
 *
 * // [[1.0, 2.0, 3.0],
 * //  [4.0, 5.0, 6.0],
 * //  [7.0, 8.0, 9.0]]
 *
 * B = A / 2;
 *
 * The content of B (the content of A doesn't change.)
 * // [[0.5, 1.0, 1.5],
 * //  [2.0, 2.5, 3.0],
 * //  [3.5, 4.0, 4.5]]
 *
 *
 * @param val the divisor of the elements of the matrix
 * 
 * @retval the new matrix whose elemets is created by dividing 
 * the elements of the matrix
 */
template <typename DType>
Matrix<DType> Matrix<DType>::operator/(DType& val) {
    
    assert((val != 0) && 
        "The divisor cannot be zero!");

    Matrix<DType> RESULT(*this);
    RESULT /= val;

    return RESULT;
}

/*
 * The operator overloading to increase elements of the matrix by certain value
 *
 * This operator overloading can used to increase element
 * of matrix by the certain value. For example: 
 * 
 * Matrix::Matrix<double> A(3, 3);
 *
 * // [[0.0, 1.0, 2.0],
 * //  [3.0, 4.0, 5.0],
 * //  [6.0, 7.0, 8.0]]
 *
 * A += 0.5;
 *
 * // [[0.5, 1.5, 2.5],
 * //  [3.5, 4.5, 5.5],
 * //  [6.5, 7.5, 8.5]]
 *
 *
 * @param val the increasor of the elements of the matrix
 * 
 * @retval the same matrix whose elemets are increased by parameter val
 */
template <typename DType>
Matrix<DType>& Matrix<DType>::operator+=(DType& val) {
    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] += val;

    return *this;
}

/*
 * The operator overloading to increase the new matrix by dividing 
 * elements of the matrix by certain value without changing 
 * the increasing matrix.
 *
 * For example: 
 * 
 * Matrix::Matrix<double> A(3, 3);
 *
 * // [[0.0, 1.0, 2.0],
 * //  [3.0, 4.0, 5.0],
 * //  [6.0, 7.0, 8.0]]
 *
 * B = A + 0.5;
 *
 * The content of B (the content of A doesn't change.) 
 * // [[0.5, 1.5, 2.5],
 * //  [3.5, 4.5, 5.5],
 * //  [6.5, 7.5, 8.5]]
 *
 * @param val the increasor of the elements of the matrix
 * 
 * @retval the new matrix whose elemets is created by increasing 
 * the elements of the matrix
 */
template <typename DType>
Matrix<DType> Matrix<DType>::operator+(DType& val) {
    Matrix<DType> RESULT(*this);
    RESULT += val;
    
    return RESULT;
}

/*
 * The operator overloading to increase elements of the matrices elementwisely
 *
 * This operator overloading can used to add the matrix to another matrix elementwisely
 * 
 * Matrix::Matrix<double> A(3, 3);
 * Matrix::Matrix<double> B(3, 3);
 * 
 *     The matrix A       The matrix B
 *   -----------------   ----------------
 * // [[0.0, 1.0, 2.0],  [[0.0, 1.0, 2.0]
 * //  [3.0, 4.0, 5.0],   [3.0, 4.0, 5.0] 
 * //  [6.0, 7.0, 8.0]]   [6.0, 7.0, 8.0]]
 *
 * A += B;
 * 
 *     The matrix A
 *   -----------------
 * // [[0.0, 2.0, 4.0],
 * //  [6.0, 8.0, 10.0],
 * //  [12.0, 14.0, 16.0]]
 *
 *
 * @param A the other matrix which will add elementwisely
 * 
 * @retval the same matrix whose elemets are added to another matrix elementwisely.
 */
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

/*
 * The operator overloading to increase elements of the matrices elementwisely
 *
 * This operator overloading can used to add the matrix to another matrix elementwisely
 * 
 * Matrix::Matrix<double> A(3, 3);
 * Matrix::Matrix<double> B(3, 3);
 * Matrix::Matrix<double> C(3, 3); 
 *
 *     The matrix A       The matrix B
 *   -----------------   ----------------
 * // [[0.0, 1.0, 2.0],  [[0.0, 1.0, 2.0]
 * //  [3.0, 4.0, 5.0],   [3.0, 4.0, 5.0] 
 * //  [6.0, 7.0, 8.0]]   [6.0, 7.0, 8.0]]
 *
 * C = A + B;
 * 
 *     The matrix C (A and B don't change)
 *   -----------------
 * // [[0.0, 2.0, 4.0],
 * //  [6.0, 8.0, 10.0],
 * //  [12.0, 14.0, 16.0]]
 *
 *
 * @param A the other matrix which will add elementwisely
 * 
 * @retval the new matrix whose elemets are added to another matrix elementwisely.
 */
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

/*
 * The operator overloading to decrease elements of the matrix by certain value
 *
 * This operator overloading can used to decrease element
 * of matrix by the certain value. For example: 
 * 
 * Matrix::Matrix<double> A(3, 3);
 *
 * // [[0.0, 1.0, 2.0],
 * //  [3.0, 4.0, 5.0],
 * //  [6.0, 7.0, 8.0]]
 *
 * A -= 0.5;
 *
 * // [[-0.5, 0.5, 1.5],
 * //  [2.5, 3.5, 4.5],
 * //  [5.5, 6.5, 7.5]]
 *
 *
 * @param val the decreasor of the elements of the matrix
 * 
 * @retval the same matrix whose elemets are decreased by parameter val
 */
template <typename DType>
Matrix<DType>& Matrix<DType>::operator-=(DType& val) { 

    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] -= val;

    return *this;
}

/*
 * The operator overloading to decrease the new matrix by decreasing 
 * elements of the matrix by certain value without changing 
 * the processing matrix.
 *
 * For example: 
 * 
 * Matrix::Matrix<double> A(3, 3);
 *
 * // [[0.0, 1.0, 2.0],
 * //  [3.0, 4.0, 5.0],
 * //  [6.0, 7.0, 8.0]]
 *
 * B = A - 0.5;
 *
 * The content of B (the content of A doesn't change.) 
 * // [[-0.5, 0.5, 1.5],
 * //  [2.5, 3.5, 4.5],
 * //  [5.5, 6.5, 7.5]]
 *
 * @param val the decreasor of the elements of the matrix
 * 
 * @retval the new matrix whose elemets is created by decreasing 
 * the elements of the matrix
 */
template <typename DType>
Matrix<DType> Matrix<DType>::operator-(DType& val) {
    
    Matrix<DType> RESULT(*this);
    RESULT -= val;
    
    return RESULT;
}

/*
 * The operator overloading to subtract elements of the matrices elementwisely
 *
 * This operator overloading can used to substract the matrix to another matrix elementwisely
 * 
 * Matrix::Matrix<double> A(3, 3);
 * Matrix::Matrix<double> B(3, 3);
 * 
 *     The matrix A       The matrix B
 *   -----------------   ----------------
 * // [[0.0, 1.0, 2.0],  [[0.0, 1.0, 2.0]
 * //  [3.0, 4.0, 5.0],   [3.0, 4.0, 5.0] 
 * //  [6.0, 7.0, 8.0]]   [6.0, 7.0, 8.0]]
 *
 * A -= B;
 * 
 *     The matrix A
 *   -----------------
 * // [[0.0, 0.0, 0.0],
 * //  [0.0, 0.0, 0.0],
 * //  [0.0, 0.0, 0.0]]
 *
 *
 * @param A the other matrix which will add elementwisely
 * 
 * @retval the same matrix whose elemets are substracted to another matrix elementwisely.
 */
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

/*
 * The operator overloading to substract elements of the matrices elementwisely
 *
 * This operator overloading can used to substract the matrix to another matrix elementwisely
 * 
 * Matrix::Matrix<double> A(3, 3);
 * Matrix::Matrix<double> B(3, 3);
 * Matrix::Matrix<double> C(3, 3); 
 *
 *     The matrix A       The matrix B
 *   -----------------   ----------------
 * // [[0.0, 1.0, 2.0],  [[0.0, 1.0, 2.0]
 * //  [3.0, 4.0, 5.0],   [3.0, 4.0, 5.0] 
 * //  [6.0, 7.0, 8.0]]   [6.0, 7.0, 8.0]]
 *
 * C = A + B;
 * 
 *     The matrix C (A and B don't change)
 *   -----------------
 * // [[0.0, 2.0, 4.0],
 * //  [6.0, 8.0, 10.0],
 * //  [12.0, 14.0, 16.0]]
 *
 *
 * @param A the other matrix which will substract elementwisely
 * 
 * @retval the new matrix whose elemets are substracted to another matrix elementwisely.
 */
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

/*
 * The operator overloading to multiply elements of the matrix by certain value
 *
 * This operator overloading can used to multiply element
 * of matrix by the certain value. For example: 
 * 
 * Matrix::Matrix<double> A(3, 3);
 *
 * // [[0.0, 1.0, 2.0],
 * //  [3.0, 4.0, 5.0],
 * //  [6.0, 7.0, 8.0]]
 *
 * A *= 0.5;
 *
 * // [[0.0, 0.5, 1.0],
 * //  [1.5, 2.0, 2.5],
 * //  [3.0, 3.5, 4.0]]
 *
 *
 * @param val the multiplicator of the elements of the matrix
 * 
 * @retval the same matrix whose elemets are multiplicator by parameter val
 */
template <typename DType>
Matrix<DType>& Matrix<DType>::operator*=(DType& val) {

    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] *= val;

    return *this;
}

/*
 * The operator overloading to multiply the new matrix by multiplying 
 * elements of the matrix by certain value without changing 
 * the processing matrix.
 *
 * For example: 
 * 
 * Matrix::Matrix<double> A(3, 3);
 *
 * // [[0.0, 1.0, 2.0],
 * //  [3.0, 4.0, 5.0],
 * //  [6.0, 7.0, 8.0]]
 *
 * B = A * 0.5;
 *
 * The content of B (the content of A doesn't change.) 
 * // [[0.0, 0.5, 1.0],
 * //  [1.5, 2.0, 2.5],
 * //  [3.0, 3.5, 4.0]]
 *
 * @param val the multiplicator of the elements of the matrix
 * 
 * @retval the new matrix whose elemets is created by multiplicating 
 * the elements of the matrix
 */
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
Matrix<DType> zeros(DIMS... dims) {
    Matrix<DType> RESULT(dims...);
    
    for (int i = 0; i < RESULT.MATRIX_SIZE; i++)
        RESULT.MATRIX[i] = 0;

    return RESULT;
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

template <typename DType>
Matrix<DType> squeeze(Matrix<DType>& A) {
    Matrix<DType> B(A);
    B.SHAPE = {A.MATRIX_SIZE};
    
    return B;
}

template <typename DType>
Matrix<DType> identity(int N) {
    Matrix<DType> I = zeros<DType>(N, N);

    for (int i = 0; i < N; i++) 
        I(i, i) = 1.0;

    return I;
}

} // end of namespace
