#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <vector>

namespace Matrix {

template <typename DType>
class Matrix {

template <typename T> 
friend Matrix<T> sigmoid(const Matrix<T>&);

template <typename T> 
friend Matrix<T> exp(const Matrix<T>&);

template <typename T> 
friend Matrix<T> tanh(const Matrix<T>&);

template <typename T, typename... DIMS>
friend Matrix<T> zeros(const DIMS ...);

template <typename T, typename... DIMS>
friend Matrix<T> ones(const DIMS ...);

template <typename T, typename... DIMS>
friend Matrix<T> random(const DIMS ...);

template <typename T>
friend void reshape(Matrix<T>&, const std::vector<int>);

template <typename T>
friend Matrix<T> squeeze(const Matrix<T>);

template <typename T>
friend Matrix<T> identity(const int);

public:

    Matrix<DType>(const Matrix<DType>&);

    template <typename... DIMS>
    Matrix<DType>(const DIMS&...);

    template <typename... Index>
    auto& operator()(const Index&...);

    template <typename... Index>
    auto operator()(const Index&...) const;

    Matrix<DType>& operator=(const Matrix<DType>&);

    Matrix<DType>& operator/=(const DType);
    Matrix<DType>  operator/(const DType);

    Matrix<DType>& operator+=(const DType);
    Matrix<DType>  operator+(const DType);
    Matrix<DType>& operator+=(const Matrix<DType>&);
    Matrix<DType>  operator+(const Matrix<DType>&);

    Matrix<DType>& operator-=(const DType);
    Matrix<DType>  operator-(const DType);
    Matrix<DType>& operator-=(const Matrix<DType>&);
    Matrix<DType>  operator-(const Matrix<DType>&);

    Matrix<DType>& operator*=(const DType);
    Matrix<DType>  operator*(const DType);
    Matrix<DType>& operator*=(const Matrix<DType>&);
    Matrix<DType>  operator*(const Matrix<DType>&);

    ~Matrix();

    std::vector<int> get_shape() const;
    void print_shape() const;
    int get_matrix_size() const;
private:
    std::vector<int> SHAPE; 
    int MATRIX_SIZE;
    DType* MATRIX;
};

template <typename DType> 
Matrix<DType> dot(const Matrix<DType>&, const Matrix<DType>&);

template <typename DType> 
Matrix<DType> sigmoid(const Matrix<DType>&);

template <typename DType> 
Matrix<DType> exp(const Matrix<DType>&);

template <typename DType> 
Matrix<DType> tanh(const Matrix<DType>&);

template <typename DType, typename... DIMS>
Matrix<DType> zeros(const DIMS...);

template <typename DType, typename... DIMS>
Matrix<DType> ones(const DIMS...);

template <typename DType, typename... DIMS>
Matrix<DType> random(const DIMS...);

template <typename DType>
void reshape(Matrix<DType>&, const std::vector<int>);

template <typename DType> 
Matrix<DType> squeeze(const Matrix<DType>);

template <typename DType>
Matrix<DType> identity(const int);

template <typename DType>
void swap_rows(Matrix<DType>&, const int, const int);

template <typename DType>
void replace_rows(Matrix<DType>&, const int, const int, const double);

template <typename DType>
void scale_row(Matrix<DType>&, const int, const int);

template <typename DType>
Matrix<DType> transpoze(const Matrix<DType>);

} // end of Matrix namespace

#include "matrix.cpp" // FIXME How can we do this without adding matrix.cpp?

#endif
