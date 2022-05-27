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

#ifndef _LINALG_UTILS_CPP_
#define _LINALG_UTILS_CPP_


#include <vector>

#include "../matrix.h"
#include "../vector.h"

namespace Matrix {

template <typename DType>
std::vector<Vector<DType>> gram_schmidt(std::vector<Vector<DType>> v) {
    // assert the v vectors are column vector

    int N = v.size();

    std::vector<Vector<DType>> orthagonalized_vectors;
    std::vector<double> uu_dot;

    for (int i = 0; i < N; i++) {
        Vector<DType> u = v[i];
        
        for (int j = 0; j < i; j++) {
            double co = vector_dot(orthagonalized_vectors[j], v[i]) / uu_dot[j];
            Vector<DType> x = orthagonalized_vectors[j] * co;
            u -= x;
        }
        uu_dot.push_back(vector_dot(u, u));
        orthagonalized_vectors.push_back(u); 
    }

    for (int i = 0; i < N; i++)
        orthagonalized_vectors[i] /= std::sqrt(uu_dot[i]);

    return orthagonalized_vectors;
}

} // end of namespace

#endif // end of _LINALG_UTILS_CPP_