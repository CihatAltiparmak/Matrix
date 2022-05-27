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



#ifndef _MATRIX_CPP_
#define _MATRIX_CPP_

#include "matrix.h"

#include <vector>    // for std::vector
#include <math.h>    // for exp
#include <ctime>     // for std::time
#include <cstdlib>   // for srand, rand
#include <iostream>  // for std::cin, std::cout
#include <assert.h>  // for assert 
#include <algorithm> // for swap

namespace Matrix {

template <typename DType>
template <typename... DIMS>
Matrix<DType>::Matrix(DIMS... dims)
{
    SHAPE = {dims...};

    assert(SHAPE.size() > 0 && 
        "The matrix must have at least one dimension.");
    
    MATRIX_SIZE = 1;

    for (auto dim : SHAPE) {
        assert(dim > 0 && 
            "The dimensions of matrix cannot nonpozitive");
        MATRIX_SIZE *= dim;
    }

    MATRIX = new DType[MATRIX_SIZE];

    for (int i = 0; i < MATRIX_SIZE; i++)
        MATRIX[i] = i;
}

/*
 * The copy constructor
 *
 * this constructor that gets another Matrix object deep-copies this object
 * 
 * Matrix::Matrix<double> A(3, 3);
 * Matrix::Matrix<double> B(A);
 *
 * @param index the necessary integer indexes. If the number of indexes
 * is larger than the size of matrix, it's raised assertion error. In addition
 * if the indexes cause the out of bounds, it's raised assertion error.
 * 
 * @retval the element of the matrix in index
 */
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
 *    [[1.0, 2.0, 3.0],
 *     [4.0, 5.0, 6.0],
 *     [7.0, 8.0, 9.0]]
 *
 * A /= 2;
 *
 *    [[0.5, 1.0, 1.5],
 *     [2.0, 2.5, 3.0],
 *     [3.5, 4.0, 4.5]]
 *
 * @param val the divisor of the elements of the matrix
 * 
 * @retval the same matrix whose elemets divided by parameter val
 */
template <typename DType>
Matrix<DType>& Matrix<DType>::operator/=(DType val) {

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
Matrix<DType> Matrix<DType>::operator/(DType val) {
    
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
 *    [[0.0, 1.0, 2.0],
 *     [3.0, 4.0, 5.0],
 *     [6.0, 7.0, 8.0]]
 *
 * A += 0.5;
 *
 *    [[0.5, 1.5, 2.5],
 *     [3.5, 4.5, 5.5],
 *     [6.5, 7.5, 8.5]]
 *
 *
 * @param val the increasor of the elements of the matrix
 * 
 * @retval the same matrix whose elemets are increased by parameter val
 */
template <typename DType>
Matrix<DType>& Matrix<DType>::operator+=(DType val) {
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
 *    [[0.0, 1.0, 2.0],
 *     [3.0, 4.0, 5.0],
 *     [6.0, 7.0, 8.0]]
 *
 * B = A + 0.5;
 *
 * The content of B (the content of A doesn't change.) 
 *    [[0.5, 1.5, 2.5],
 *     [3.5, 4.5, 5.5],
 *     [6.5, 7.5, 8.5]]
 *
 * @param val the increasor of the elements of the matrix
 * 
 * @retval the new matrix whose elemets is created by increasing 
 * the elements of the matrix
 */
template <typename DType>
Matrix<DType> Matrix<DType>::operator+(DType val) {
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
 *    [[0.0, 1.0, 2.0],  [[0.0, 1.0, 2.0]
 *     [3.0, 4.0, 5.0],   [3.0, 4.0, 5.0] 
 *     [6.0, 7.0, 8.0]]   [6.0, 7.0, 8.0]]
 *
 * A += B;
 * 
 *     The matrix A
 *   -----------------
 *    [[0.0, 2.0, 4.0],
 *     [6.0, 8.0, 10.0],
 *     [12.0, 14.0, 16.0]]
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
 *    [[0.0, 1.0, 2.0],  [[0.0, 1.0, 2.0]
 *     [3.0, 4.0, 5.0],   [3.0, 4.0, 5.0] 
 *     [6.0, 7.0, 8.0]]   [6.0, 7.0, 8.0]]
 *
 * C = A + B;
 * 
 *     The matrix C (A and B don't change)
 *   -----------------
 *    [[0.0, 2.0, 4.0],
 *     [6.0, 8.0, 10.0],
 *     [12.0, 14.0, 16.0]]
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
 *    [[0.0, 1.0, 2.0],
 *     [3.0, 4.0, 5.0],
 *     [6.0, 7.0, 8.0]]
 *
 * A -= 0.5;
 *
 *    [[-0.5, 0.5, 1.5],
 *     [2.5, 3.5, 4.5],
 *     [5.5, 6.5, 7.5]]
 *
 *
 * @param val the decreasor of the elements of the matrix
 * 
 * @retval the same matrix whose elemets are decreased by parameter val
 */
template <typename DType>
Matrix<DType>& Matrix<DType>::operator-=(DType val) { 

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
 *    [[0.0, 1.0, 2.0],
 *     [3.0, 4.0, 5.0],
 *     [6.0, 7.0, 8.0]]
 *
 * B = A - 0.5;
 *
 * The content of B (the content of A doesn't change.) 
 *    [[-0.5, 0.5, 1.5],
 *     [2.5, 3.5, 4.5],
 *     [5.5, 6.5, 7.5]]
 *
 * @param val the decreasor of the elements of the matrix
 * 
 * @retval the new matrix whose elemets is created by decreasing 
 * the elements of the matrix
 */
template <typename DType>
Matrix<DType> Matrix<DType>::operator-(DType val) {
    
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
 *    [[0.0, 1.0, 2.0],  [[0.0, 1.0, 2.0]
 *     [3.0, 4.0, 5.0],   [3.0, 4.0, 5.0] 
 *     [6.0, 7.0, 8.0]]   [6.0, 7.0, 8.0]]
 *
 * A -= B;
 * 
 *     The matrix A
 *   -----------------
 *    [[0.0, 0.0, 0.0],
 *     [0.0, 0.0, 0.0],
 *     [0.0, 0.0, 0.0]]
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
 *    [[0.0, 1.0, 2.0],  [[0.0, 1.0, 2.0]
 *     [3.0, 4.0, 5.0],   [3.0, 4.0, 5.0] 
 *     [6.0, 7.0, 8.0]]   [6.0, 7.0, 8.0]]
 *
 * C = A + B;
 * 
 *     The matrix C (A and B don't change)
 *   -----------------
 *    [[0.0, 2.0, 4.0],
 *     [6.0, 8.0, 10.0],
 *     [12.0, 14.0, 16.0]]
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
 *    [[0.0, 1.0, 2.0],
 *     [3.0, 4.0, 5.0],
 *     [6.0, 7.0, 8.0]]
 *
 * A *= 0.5;
 *
 *    [[0.0, 0.5, 1.0],
 *     [1.5, 2.0, 2.5],
 *     [3.0, 3.5, 4.0]]
 *
 *
 * @param val the multiplicator of the elements of the matrix
 * 
 * @retval the same matrix whose elemets are multiplicator by parameter val
 */
template <typename DType>
Matrix<DType>& Matrix<DType>::operator*=(DType val) {

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
 *    [[0.0, 1.0, 2.0],
 *     [3.0, 4.0, 5.0],
 *     [6.0, 7.0, 8.0]]
 *
 * B = A * 0.5;
 *
 * The content of B (the content of A doesn't change.) 
 *    [[0.0, 0.5, 1.0],
 *     [1.5, 2.0, 2.5],
 *     [3.0, 3.5, 4.0]]
 *
 * @param val the multiplicator of the elements of the matrix
 * 
 * @retval the new matrix whose elemets is created by multiplicating 
 * the elements of the matrix
 */
template <typename DType>
Matrix<DType> Matrix<DType>::operator*(DType val) {

    Matrix<DType> RESULT(*this);
    RESULT *= val;
    
    return RESULT;
}

/*
 * The operator overloading to multiply elements of the matrices elementwisely
 *
 * This operator overloading can used to substract the matrix to another matrix elementwisely
 * 
 * Matrix::Matrix<double> A(3, 3);
 * Matrix::Matrix<double> B(3, 3);
 * Matrix::Matrix<double> C(3, 3); 
 *
 *     The matrix A       The matrix B
 *   -----------------   ----------------
 *    [[0.0, 1.0, 2.0],  [[0.0, 1.0, 2.0]
 *     [3.0, 4.0, 5.0],   [3.0, 4.0, 5.0] 
 *     [6.0, 7.0, 8.0]]   [6.0, 7.0, 8.0]]
 *
 * C = A * B;
 * 
 *     The matrix C (A and B don't change)
 *   -----------------
 *    [[0.0, 1.0, 4.0],
 *     [9.0, 16.0, 25.0],
 *     [36.0, 49.0, 64.0]]
 *
 *
 * @param A the other matrix which will multiply elementwisely
 * 
 * @retval the new matrix whose elemets are multiplied to another matrix elementwisely.
 */
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

/*
 * The operator overloading to multiply elements of the matrices elementwisely
 *
 * This operator overloading can used to multiply the matrix to another matrix elementwisely
 * 
 * Matrix::Matrix<double> A(3, 3);
 * Matrix::Matrix<double> B(3, 3);
 * Matrix::Matrix<double> C(3, 3); 
 *
 *     The matrix A       The matrix B
 *   -----------------   ----------------
 *    [[0.0, 1.0, 2.0],  [[0.0, 1.0, 2.0]
 *     [3.0, 4.0, 5.0],   [3.0, 4.0, 5.0] 
 *     [6.0, 7.0, 8.0]]   [6.0, 7.0, 8.0]]
 *
 * C = A * B;
 * 
 *     The matrix C (A and B don't change)
 *   -----------------
 *    [[0.0, 1.0, 4.0],
 *     [9.0, 16.0, 25.0],
 *     [36.0, 49.0, 64.0]]
 *
 *
 * @param A the other matrix which will multiply elementwisely
 * 
 * @retval the new matrix whose elemets are multiplied to another matrix elementwisely.
 */
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

/*
 * The method that return the SHAPE of the matrix
 *
 * It returns the dimensions of the matrix as std::vector<int> format
 * 
 * Matrix<double> A(1, 2, 3);
 * std::vector<int> shape = A.get_shape();
 *
 * @param no parameter
 * 
 * @retval the shape of the matrix
 */
template <typename DType>
std::vector<int> Matrix<DType>::get_shape(){
    return SHAPE;
}

template <typename DType>
int Matrix<DType>::get_matrix_size() {
    return MATRIX_SIZE;
}

template <typename DType>
void Matrix<DType>::print_shape() {
    std::cout << "(";
    for (auto v : SHAPE)
        std::cout << v << ", ";
    std::cout << ")" << std::endl;
}



/*
 * The function that do matrix multiplication
 *
 * This function gets two same type matrix and 
 * returns the matrix multiplication of these two matrix
 * If the shape of these matrix is not available for matrix 
 * multiplication, it's raised assertion error
 *
 * This operator overloading can used to substract the matrix to another matrix elementwisely
 * 
 * Matrix::Matrix<double> A(3, 2);
 * Matrix::Matrix<double> B(2, 3);
 * Matrix::Matrix<double> C(3, 3); 
 *
 *     The matrix A       The matrix B
 *   -----------------   ----------------
 *    [[0, 1],            [[0, 1, 2]
 *     [2, 3],             [3, 4, 5]]
 *     [4, 5]]
 *
 * C = Matrix::dot(A, B);
 * 
 *     The matrix C
 *   -----------------
 *    [[3, 4, 5],
 *     [9, 14, 19],
 *     [15, 24, 33]]
 *
 *
 * @param A the first matrix for matrix multiplication
 * @param B the second matrix for matrix multiplication
 * @retval the AB matrix (AB presents matrix multiplication).
 */
template <typename DType>
Matrix<DType> dot(Matrix<DType> A, Matrix<DType> B) {

    auto a_shape = A.get_shape();
    auto b_shape = B.get_shape();

    assert(a_shape[1] == b_shape[0] &&
        "The matrix multiplication is impossible");

    Matrix<DType> AB = zeros<DType>(a_shape[0], b_shape[1]);

    for (int x = 0; x < a_shape[0]; x++) {
        for (int y = 0; y < b_shape[1]; y++)
            for (int i = 0; i < a_shape[1]; i++)
                AB(x, y) += A(x, i) * B(i, y);
    }

    return AB;
}

/*
 * The function that returns new matrix which gets by applying 
 * sigmoid function to the elemets of the old matrix. 
 * FIXME: If the type of matrix is not double, it is raised assertion errors. it should be improved.
 *
 * SIGMOID_FUNCTION_FORMULA: sigmoid(x) = 1 / (1 + e^-x) 
 * 
 * Matrix::Matrix<double> A(3, 3);
 *
 *     The matrix A 
 *   -----------------
 *     [[1.0, 2.0, 3.0],
 *      [4.0, 5.0, 6.0],
 *      [7.0, 8.0, 9.0]]
 *
 * C = Matrix::sigmoid(A);
 * 
 *     The matrix C (A don't change)
 *   -----------------
 *     [[0.5, 0.731059, 0.880797],
 *      [0.952574, 0.982014, 0.993307],
 *      [0.997527, 0.999089, 0.999665]] 
 *
 * @param A the matrix whose elements are applied sigmoid function
 * @retval the result matrix
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
 * The function that returns new matrix which gets by applying 
 * exp function to the elemets of the old matrix. 
 * FIXME: If the type of matrix is not double, it is raised assertion errors. it should be improved.
 *
 * EXP_FUNCTION_FORMULA: EXP(x) = e^x 
 * 
 * Matrix::Matrix<double> A(3, 3);
 *
 *     The matrix A 
 *   -----------------
 *     [[1.0, 2.0, 3.0],
 *      [4.0, 5.0, 6.0],
 *      [7.0, 8.0, 9.0]]
 *
 * C = Matrix::exp(A);
 * 
 *     The matrix C (A don't change)
 *   -----------------
 *     [[1, 2.71828, 7.38906]
 *      [20.0855, 54.5982, 148.413]
 *      [403.429, 1096.63, 2980.96]] 
 *
 * @param A the matrix whose elements are applied exp function
 * @retval the result matrix
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
 * The function that returns new matrix which gets by applying 
 * exp function to the elemets of the old matrix. 
 * FIXME: If the type of matrix is not double, it is raised assertion errors. it should be improved.
 *
 * TANH_FUNCTION_FORMULA: tanh(x) = (e^x - e^-x) / (e^x + e^-x)
 * 
 * Matrix::Matrix<double> A(3, 3);
 *
 *     The matrix A 
 *   -----------------
 *     [[1.0, 2.0, 3.0],
 *      [4.0, 5.0, 6.0],
 *      [7.0, 8.0, 9.0]]
 *
 * C = Matrix::tanh(A);
 * 
 *     The matrix C (A don't change)
 *   -----------------
 *     [[0, 0.761594, 0.964028]
 *      [0.995055, 0.999329, 0.999909]
 *      [0.999988, 0.999998, 1]]
 *
 * @param A the matrix whose elements are applied tanh function
 * @retval the result matrix
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
 * The function that creates the matrix with zeros
 * 
 * Matrix::Matrix<double> A(3, 3);
 *
 * C = Matrix::zeros<double>(3, 3);
 *
 * @param dims the dimensions for the matrix with zeros
 * @retval the result matrix
 */
template <typename DType, typename... DIMS>
Matrix<DType> zeros(DIMS... dims) {
    Matrix<DType> RESULT(dims...);
    
    for (int i = 0; i < RESULT.MATRIX_SIZE; i++)
        RESULT.MATRIX[i] = 0;

    return RESULT;
}

/*
 * The function that creates the matrix with ones
 * 
 * Matrix<double> C = Matrix::ones<double>(3, 3);
 *
 * @param dims the dimensions for the matrix with ones
 * @retval the result matrix
 */
template <typename DType, typename... DIMS>
Matrix<DType> ones(DIMS... dims) {
    Matrix<DType> RESULT(dims...);
    
    for (int i = 0; i < RESULT.MATRIX_SIZE; i++)
        RESULT.MATRIX[i] = 1;

    return RESULT;
}

/*
 * The function that creates the matrix with random values
 * TODO: add the distribution option and improve the func with mersenne twist generator
 * Matrix::Matrix<double> C = Matrix::random(3, 3);
 *
 * @param dims the dimensions for the matrix with random variables
 * @retval the result matrix
 */
template <typename DType, typename... DIMS>
Matrix<DType> random(DIMS... dims) {
    Matrix<DType> RESULT(dims...);
   
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // be careful 
    for (int i = 0; i < RESULT.MATRIX_SIZE; i++)
        RESULT.MATRIX[i] = std::rand();

    return RESULT;
}

/*
 * The function that change the shape of matrix
 *
 * Matrix::Matrix<double> A(2, 4);
 *
 * Matrix::reshape(A, 2, 2, 2);
 * 
 *   the result A matrix
 * -------------------------
 *
 * @param dims the new dimensions for the matrix
 * @retval None
 */
template <typename DType>
void reshape(Matrix<DType>& A, std::vector<int> dims) {
    int __size = 1;

    for (int i = 0; i < dims.size(); i++) {
        assert(dims[i] > 0 &&
            "The dimensions are not nonpositive !");
        __size *= dims[i];
    }

    assert((__size == A.MATRIX_SIZE) && 
        "The size for the new reshaped dimensions must be same as the matrix size!");

    A.SHAPE = dims;
}

/* 
 * The function that squeeze the matrix.
 *
 * For example:
 * 
 *   the matrix A
 * _________________
 *  [[[[1], [2], [3]]],
 *   [[[4], [5], [6]]],
 *   [[[7], [8], [9]]]]
 *
 *   the new matrix after squeezing the matrix
 * ______________________________________________
 *   [[1, 2, 3],
 *    [4, 5, 6],
 *    [7, 8, 9]] 
 *
 * @param  A the matrix for squeezing
 * @return the squeezed function
 */
template <typename DType>
Matrix<DType> squeeze(Matrix<DType> A) {
    Matrix<DType> B(A);

    std::vector<int> new_dims;
    for (auto dim : B.get_shape())
        if (dim != 1)
            new_dims.push_back(dim);

    if (new_dims.size() == 0)
        new_dims.push_back(1);

    reshape(B, new_dims); 
    return B;
}

/*
 * The function that creates the identity matrix with given dimensions
 * 
 * Matrix::Matrix<double> C = Matrix::identity(3);
 *
 * @param dims the one of dimensions for the identity matrix
 * @retval the result matrix
 */
template <typename DType>
Matrix<DType> identity(int N) {
    Matrix<DType> I = zeros<DType>(N, N);

    for (int i = 0; i < N; i++) 
        I(i, i) = 1.0;

    return I;
}

template <typename DType>
void swap_rows(Matrix<DType>& A, int first_row, int second_row) {
    auto __shape = A.get_shape();
    int N = __shape[0];
    int M = __shape[1];

    assert(((first_row < N) && (second_row < N)) &&
        "Invalid row index!");

    assert(((first_row >= 0) && (second_row >= 0)) &&
        "Invalid row index!");

    for (int i = 0; i < M; i++)
        std::swap(A(first_row, i), A(second_row, i));
}

template <typename DType>
void replace_rows(Matrix<DType>& A, int first_row, int second_row, double scalar) {
    auto __shape = A.get_shape();
    int N = __shape[0];
    int M = __shape[1];

    assert(((first_row < N) && (second_row < N)) &&
        "Invalid row index!");

    assert(((first_row >= 0) && (second_row >= 0)) &&
        "Invalid row index!");

    for (int i = 0; i < M; i++)
        A(second_row, i) += A(first_row, i) * scalar;
}

template <typename DType>
void scale_row(Matrix<DType>& A, int row, double scalar) {
    
    auto __shape = A.get_shape();
    int N = __shape[0];
    int M = __shape[1];

    assert((row < N && row >= 0) &&
        "Invalid row index!");

    for (int i = 0; i < M; i++)
        A(row, i) *= scalar;
}

template <typename DType>
Matrix<DType> transpoze(Matrix<DType> A) {

    int N = A.get_shape()[0];
    int M = A.get_shape()[1];

    Matrix<DType> RESULT(M, N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            RESULT(j, i) = A(i, j);

    return RESULT;
}

/*
template<typename DType>
Matrix<DType> augment(Matrix<DType> A, Matrix<DType> B) {
}
*/

} // end of namespace

#endif // end of _MATRIX_CPP_