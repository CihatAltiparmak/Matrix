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

// just for two dimensional matrices
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

TEST(MATRIX, CREATING) {

    Matrix::Matrix<double> A(3, 3);
    EXPECT_TRUE(is_equal(A, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {3, 3}));

    Matrix::Matrix<double> B(3, 5);
    EXPECT_TRUE(is_equal(B, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}, {3, 5}));

//    Matrix::Matrix<double> C(2, 2, 2);
//    EXPECT_TRUE(is_equal(C, {0, 1, 2, 3, 4, 5, 6, 7}, {2, 2, 2}));

    Matrix::Matrix<double> D(1, 8);
    EXPECT_TRUE(is_equal(D, {0, 1, 2, 3, 4, 5, 6, 7}, {1, 8}));
}

TEST(MATRIX, GET_ELEMENT) {

    Matrix::Matrix<double> A(3, 3);

    EXPECT_EQ(A(0, 0), 0);
    EXPECT_EQ(A(2, 1), 7);
}

TEST(MATRIX, SET_ELEMENT) {

    Matrix::Matrix<double> A(3, 3);
    A(1, 1) = 1000;
    A(2, 0) = -17;

    EXPECT_TRUE(is_equal(A, {0, 1, 2, 3, 1000, 5, -17, 7, 8}, {3, 3}));
}

TEST(MATRIX, ASSIGNING) {

    Matrix::Matrix<double> A(3, 3);
    A(1, 1) = 1000;
    A(2, 0) = -17;

    Matrix::Matrix<double> B = A;

    EXPECT_TRUE(is_equal(B, {0, 1, 2, 3, 1000, 5, -17, 7, 8}, {3, 3}));

}

TEST(MATRIX, COPYING_CONSTRUCTOR) {

    Matrix::Matrix<double> A(3, 3);
    A(1, 1) = 1000;
    A(2, 0) = -17;

    Matrix::Matrix<double> B(A);

    EXPECT_TRUE(is_equal(B, {0, 1, 2, 3, 1000, 5, -17, 7, 8}, {3, 3}));
}

TEST(MATRIX, OPERATOR_PLUS) {
    Matrix::Matrix<double> A(3, 3);

    A += A;
    EXPECT_TRUE(is_equal(A, {0, 2, 4, 6, 8, 10, 12, 14, 16}, {3, 3}));
    
    A += 3;
    EXPECT_TRUE(is_equal(A, {3, 5, 7, 9, 11, 13, 15, 17, 19}, {3, 3}));


    Matrix::Matrix<double> X(3, 3);
    Matrix::Matrix<double> C = X + X;

    EXPECT_TRUE(is_equal(C, {0, 2, 4, 6, 8, 10, 12, 14, 16}, {3, 3}) &&
                is_equal(X, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {3, 3}));


    Matrix::Matrix<double> D = X + 2;

    EXPECT_TRUE(is_equal(D, {2, 3, 4, 5, 6, 7, 8, 9, 10}, {3, 3}) &&
                is_equal(X, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {3, 3})); 
}

TEST(MATRIX, OPERATOR_MINUS) {
    Matrix::Matrix<double> A(3, 3);

    A -= A;
    EXPECT_TRUE(is_equal(A, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {3, 3}));
    
    A -= 3;
    EXPECT_TRUE(is_equal(A, {-3, -3, -3, -3, -3, -3, -3, -3, -3}, {3, 3}));


    Matrix::Matrix<double> X(3, 3);
    Matrix::Matrix<double> C = X - A;

    EXPECT_TRUE(is_equal(C, {3, 4, 5, 6, 7, 8, 9, 10, 11}, {3, 3}) &&
                is_equal(X, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {3, 3}) &&
                is_equal(A, {-3, -3, -3, -3, -3, -3, -3, -3, -3}, {3, 3}));


    Matrix::Matrix<double> D = X - 2;

    EXPECT_TRUE(is_equal(D, {-2, -1, 0, 1, 2, 3, 4, 5, 6}, {3, 3}) &&
                is_equal(X, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {3, 3})); 
}

TEST(MATRIX, OPERATOR_DIVISION) {
    Matrix::Matrix<double> A(3, 3);

    A /= 2;
    EXPECT_TRUE(is_equal(A, {0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4}, {3, 3}));
    
    Matrix::Matrix<double> B = A / 0.5;
    EXPECT_TRUE(is_equal(B, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {3, 3})); 
}

TEST(MATRIX, OPERATOR_MULTIPLY) {
    Matrix::Matrix<double> A(3, 3);

    A *= A;
    EXPECT_TRUE(is_equal(A, {0, 1, 4, 9, 16, 25, 36, 49, 64}, {3, 3}));
    
    A *= 3;
    EXPECT_TRUE(is_equal(A, {0, 3, 12, 27, 48, 75, 108, 147, 192}, {3, 3}));


    Matrix::Matrix<double> X(3, 3);
    Matrix::Matrix<double> C = X * X;

    EXPECT_TRUE(is_equal(C, {0, 1, 4, 9, 16, 25, 36, 49, 64}, {3, 3}) &&
                is_equal(X, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {3, 3}));


    Matrix::Matrix<double> D = X * 2;

    EXPECT_TRUE(is_equal(D, {0, 2, 4, 6, 8, 10, 12, 14, 16}, {3, 3}) &&
                is_equal(X, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {3, 3})); 
}

TEST(MATRIX_FUNCTIONS, DOT) {

    Matrix::Matrix<double> A(3, 3);
    Matrix::Matrix<double> x(3, 1);

    Matrix::Matrix<double> b = Matrix::dot(A, x);

    EXPECT_TRUE(is_equal(b, {5, 14, 23}, {3, 1}));


    Matrix::Matrix<double> C = Matrix::dot(A, A);
    EXPECT_TRUE(is_equal(C, {15, 18, 21, 42, 54, 66, 69, 90, 111}, {3, 3}));

}

TEST(MATRIX_FUNCTIONS, ZEROS) {

    Matrix::Matrix<double> A = Matrix::zeros<double>(2, 6);
    EXPECT_TRUE(is_equal(A, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {2, 6}));

    Matrix::Matrix<double> B = Matrix::zeros<double>(1, 12);
    EXPECT_TRUE(is_equal(B, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 12}));

}

TEST(MATRIX_FUNCTIONS, ONES) {

    Matrix::Matrix<double> A = Matrix::ones<double>(2, 6);
    EXPECT_TRUE(is_equal(A, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {2, 6}));

    Matrix::Matrix<double> B = Matrix::ones<double>(1, 12);
    EXPECT_TRUE(is_equal(B, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 12}));

}

TEST(MATRIX_FUNCTIONS, RESHAPE) {

    Matrix::Matrix<double> A(3, 1, 3, 1);
    Matrix::reshape(A, {9, 1});

    EXPECT_TRUE(is_equal(A, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {9, 1}));
}

TEST(MATRIX_FUNCTIONS, SQUEEZE) {

    Matrix::Matrix<double> A(3, 1, 3, 1);

    Matrix::Matrix<double> B = Matrix::squeeze(A);

    EXPECT_TRUE(is_equal(B, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {3, 3}));
}

TEST(MATRIX_FUNCTIONS, IDENTITY) {

    Matrix::Matrix<double> A = Matrix::identity<double>(3);

    EXPECT_TRUE(is_equal(A, {1, 0, 0, 0, 1, 0, 0, 0, 1}, {3, 3}));
}

TEST(MATRIX_FUNCTIONS, SWAP_ROWS) {

    Matrix::Matrix<double> A(3, 3);
    Matrix::swap_rows(A, 0, 1);

    EXPECT_TRUE(is_equal(A, {3, 4, 5, 0, 1, 2, 6, 7, 8}, {3, 3}));
}

TEST(MATRIX_FUNCTIONS, REPLACE_ROWS) {

    Matrix::Matrix<double> A(3, 3);
    Matrix::replace_rows(A, 0, 1, 2.0);

    EXPECT_TRUE(is_equal(A, {0, 1, 2, 3, 6, 9, 6, 7, 8}, {3, 3}));
}

TEST(MATRIX_FUNCTIONS, SCALE_ROW) {

    Matrix::Matrix<double> A(3, 3);
    Matrix::scale_row(A, 2, 2.0);

    EXPECT_TRUE(is_equal(A, {0, 1, 2, 3, 4, 5, 12, 14, 16}, {3, 3}));
}

TEST(MATRIX_FUNCTIONS, EXP) {

    Matrix::Matrix<double> A(3, 3);
    Matrix::Matrix<double> B = Matrix::exp(A);

    auto exp_test = [] (double x) {
        return std::exp(x);
    };

    EXPECT_TRUE(function_tester(B, A, exp_test));
}

TEST(MATRIX_FUNCTIONS, TANH) {

    Matrix::Matrix<double> A(3, 3);
    Matrix::Matrix<double> B = Matrix::tanh(A);

    auto tanh_test = [] (double x) {
        return (std::exp(x) - std::exp(-x)) / (std::exp(x) + std::exp(-x));
    };

    EXPECT_TRUE(function_tester(B, A, tanh_test));
}

TEST(MATRIX_FUNCTIONS, SIGMOID) {

    Matrix::Matrix<double> A(3, 3);
    Matrix::Matrix<double> B = Matrix::sigmoid(A);

    auto sigmoid_test = [] (double x) {
        return 1 / (1 + std::exp(-1 * x));
    };

    EXPECT_TRUE(function_tester(B, A, sigmoid_test));
}