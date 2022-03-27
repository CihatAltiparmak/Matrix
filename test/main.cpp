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
     

    A(0, 0) = 100;
    A(1, 0) = -100;
    A(2, 0) = 0;


    Matrix::Matrix<double> invA = Matrix::inv(A);

    double ADet   = Matrix::det(A);
    std::cout << "********************" << std::endl;
    double invDet = Matrix::det(invA);

    std::cout << ADet << " : " << invDet << std::endl;

    return 0;

}
