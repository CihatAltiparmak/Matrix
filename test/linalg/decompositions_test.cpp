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

TEST(DECOMPOSITIONS, LU) {

}

TEST(DECOMPOSITIONS, QR) {

}