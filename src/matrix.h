#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <vector>

namespace Matrix {

template <typename DType>
class Matrix {

template <typename T> 
friend Matrix<T> sigmoid(Matrix<T>&);

template <typename T> 
friend Matrix<T> exp(Matrix<T>&);

template <typename T> 
friend Matrix<T> tanh(Matrix<T>&);

template <typename T, typename... DIMS>
friend Matrix<T> zeros(DIMS ...);

template <typename T, typename... DIMS>
friend Matrix<T> ones(DIMS ...);

template <typename T, typename... DIMS>
friend Matrix<T> random(DIMS ...);

template <typename T>
friend void reshape(Matrix<T>&, std::vector<int>);

template <typename T>
friend Matrix<T> squeeze(Matrix<T>);

template <typename T>
friend Matrix<T> identity(int);

public:

    Matrix<DType>(Matrix<DType>const&);

    template <typename... DIMS>
    Matrix<DType>(DIMS...);

    template <typename... Index>
    DType& operator()(Index...);

    Matrix<DType>& operator=(Matrix<DType>const&);

    Matrix<DType>& operator/=(DType);
    Matrix<DType>  operator/(DType);

    Matrix<DType>& operator+=(DType);
    Matrix<DType>  operator+(DType);
    Matrix<DType>& operator+=(Matrix<DType>&);
    Matrix<DType>  operator+(Matrix<DType>&);

    Matrix<DType>& operator-=(DType);
    Matrix<DType>  operator-(DType);
    Matrix<DType>& operator-=(Matrix<DType>&);
    Matrix<DType>  operator-(Matrix<DType>&);

    Matrix<DType>& operator*=(DType);
    Matrix<DType>  operator*(DType);
    Matrix<DType>& operator*=(Matrix<DType>&);
    Matrix<DType>  operator*(Matrix<DType>&);

    ~Matrix();

    std::vector<int> get_shape();
    void print_shape();
    int get_matrix_size();
private:
    std::vector<int> SHAPE; 
    int MATRIX_SIZE;
    DType* MATRIX;
};

template <typename DType> 
Matrix<DType> dot(Matrix<DType>, Matrix<DType>);

template <typename DType> 
Matrix<DType> sigmoid(Matrix<DType>&);

template <typename DType> 
Matrix<DType> exp(Matrix<DType>&);

template <typename DType> 
Matrix<DType> tanh(Matrix<DType>&);

template <typename DType, typename... DIMS>
Matrix<DType> zeros(DIMS...);

template <typename DType, typename... DIMS>
Matrix<DType> ones(DIMS...);

template <typename DType, typename... DIMS>
Matrix<DType> random(DIMS...);

template <typename DType>
void reshape(Matrix<DType>&, std::vector<int>);

template <typename DType> 
Matrix<DType> squeeze(Matrix<DType>);

template <typename DType>
Matrix<DType> identity(int);

template <typename DType>
void swap_rows(Matrix<DType>&, int, int);

template <typename DType>
void replace_rows(Matrix<DType>&, int, int, double);

template <typename DType>
void scale_row(Matrix<DType>&, int, int);

template <typename DType>
Matrix<DType> transpoze(Matrix<DType>);

} // end of Matrix namespace

#include "matrix.cpp" // FIXME How can we do this without adding matrix.cpp?

#endif
