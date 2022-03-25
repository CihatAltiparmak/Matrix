#include <iostream>
#include <vector>
#include "matrix.h"
#include "linalg/algorithms.h"

void print_m(Matrix::Matrix<double> A) {
    
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++)
            std::cout << A(x, y) << " ";
        std::cout << std::endl;
    }
}


int main()
{

    Matrix::Matrix<double> A(3, 3);
    Matrix::Matrix<double> C = Matrix::zeros<double>(3, 3);
    
    std::cout << "[";
    for (int i = 0; i < 3; i++) {
        std::cout << "[";
        for (int j = 0; j < 3; j++) {
            std::cout << C(i, j);
            if (j < 2)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << "]" << std::endl;

#if 0
    Matrix::Matrix<double> A(3, 3);
    Matrix::Matrix<double> B(4, 3);

    A(0, 0) = 100;
    A(1, 0) = -100;
    A(2, 0) = 0;

    
    print_m(A);
    
    std::cout << "------------------------" << std::endl;


    //Matrix::Matrix<double> I = Matrix::identity<double>(3);

    Matrix::Matrix<double> invA = Matrix::inv(A);
    print_m(invA);

    double ADet   = Matrix::det(A);
    double invDet = Matrix::det(invA);

    std::cout << ADet << " : " << invDet << std::endl;
#endif

    return 0;

}
