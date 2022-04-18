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

#include <gtest/gtest.h>
#include <vector>

#include <atrix/matrix.h>
#include <atrix/vector.h>

template <typename T>
bool is_equal(Matrix::Vector<T> A, std::vector<T> expected_data, std::vector<int> expected_shape) {
    if (A.get_shape() != expected_shape)
        return false;

    std::vector<T> calculated_data;

    for (int i = 0; i < expected_shape[0]; i++) {
        for (int j = 0; j < expected_shape[1]; j++)
            calculated_data.push_back(A(i, j));
    }

    return calculated_data == expected_data;
}

template <typename T>
bool is_equal(Matrix::Matrix<T> A, std::vector<T> expected_data, std::vector<int> expected_shape) {
    if (A.get_shape() != expected_shape)
        return false;

    std::vector<T> calculated_data;

    for (int i = 0; i < expected_shape[0]; i++) {
        for (int j = 0; j < expected_shape[1]; j++)
            calculated_data.push_back(A(i, j));
    }

    return calculated_data == expected_data;
}

template <typename T>
bool function_tester(Matrix::Matrix<T> newA, Matrix::Matrix<T> oldA, std::function<double(double)> given_func) {

    std::vector<int> newA_shape = newA.get_shape();
    std::vector<int> oldA_shape = oldA.get_shape();

    if (newA_shape != oldA_shape)
        return false;

    for (int i = 0; i < newA_shape[0]; i++) {
        for (int j = 0; j < newA_shape[1]; j++) {
            if (newA(i, j) != given_func(oldA(i, j)))
                return false;
        }
    }

    return true;

}

TEST(VECTOR, CREATING) {

    Matrix::Vector<double> A(3, 1);


    EXPECT_TRUE(is_equal(A, {0, 1, 2}, {3, 1}));

    Matrix::Vector<double> B(1, 3);
    EXPECT_TRUE(is_equal(B, {0, 1, 2}, {1, 3}));



}

TEST(VECTOR, CREATING_FROM_MATRIX) {

    Matrix::Matrix<double> C(3, 1);
    Matrix::Vector<double> A(C);

    EXPECT_TRUE(is_equal(A, {0, 1, 2}, {3, 1}));

    Matrix::Vector<double> B = C;
    EXPECT_TRUE(is_equal(B, {0, 1, 2}, {3, 1}));


    Matrix::Matrix<double> D(1, 3);
    Matrix::Vector<double> E(D);

    EXPECT_TRUE(is_equal(E, {0, 1, 2}, {1, 3}));

    Matrix::Vector<double> F = D;
    EXPECT_TRUE(is_equal(F, {0, 1, 2}, {1, 3}));

}

TEST(VECTOR, ARRAY_SUBSCRIPT_GET_VALUE) {

    Matrix::Vector<double> A(5, 1);

    EXPECT_TRUE(A(4, 0) == 4);
}

TEST(VECTOR, VECTOR_ARRAY_SUBSCRIPT_SET_VALUE) {

    Matrix::Vector<double> A(5, 1);
    A(4, 0) = 100;

    EXPECT_TRUE(is_equal(A, {0, 1, 2, 3, 100}, {5, 1}));

    Matrix::Vector<double> B(1, 5);
    B(0, 4) = 100;

    EXPECT_TRUE(is_equal(B, {0, 1, 2, 3, 100}, {1, 5}));
}

TEST(VECTOR, VECTOR_DOT) {

    Matrix::Vector<double> A(3, 1);
    Matrix::Vector<double> B(3, 1);
    double x1 = Matrix::vector_dot(A, B);

    EXPECT_TRUE(x1 == 5);

    Matrix::Vector<double> C(1, 3);
    Matrix::Vector<double> D(1, 3);
    double x2 = Matrix::vector_dot(C, D);
    EXPECT_TRUE(x2 == 5);
}

TEST(VECTOR, TO_COLUMN_VECTOR) {
    Matrix::Matrix<double> A(3, 3);

    auto column_vectors = Matrix::to_column_vectors(A);

    EXPECT_TRUE(is_equal(column_vectors[0], {0, 3, 6}, {3, 1}) && 
                is_equal(column_vectors[1], {1, 4, 7}, {3, 1}) &&
                is_equal(column_vectors[2], {2, 5, 8}, {3, 1}));   

}

TEST(VECTOR, TO_ROW_VECTOR) {
    Matrix::Matrix<double> A(3, 3);

    auto row_vectors = Matrix::to_row_vectors(A);

    EXPECT_TRUE(is_equal(row_vectors[0], {0, 1, 2}, {1, 3}) && 
                is_equal(row_vectors[1], {3, 4, 5}, {1, 3}) &&
                is_equal(row_vectors[2], {6, 7, 8}, {1, 3}));   

}

TEST(VECTOR, FROM_COLUMN_VECTOR) {
    Matrix::Vector<double> A(3, 1);
    std::vector<Matrix::Vector<double>> column_vectors = {A, A, A, A};
    Matrix::Matrix<double> RESULT = Matrix::from_column_vectors(column_vectors);

    EXPECT_TRUE(is_equal(RESULT, {0, 0, 0, 0, 
                                  1, 1, 1, 1,
                                  2, 2, 2, 2}, {3, 4}));
}

TEST(VECTOR, FROM_ROW_VECTOR) {
    Matrix::Vector<double> A(1, 3);
    std::vector<Matrix::Vector<double>> row_vectors = {A, A, A, A};
    Matrix::Matrix<double> RESULT = Matrix::from_row_vectors(row_vectors);

    EXPECT_TRUE(is_equal(RESULT, {0, 1, 2,
                                  0, 1, 2,
                                  0, 1, 2,
                                  0, 1, 2}, {4, 3}));
}