#include <iostream>
#include <vector>
#include "matrix.h"

void print_m(Matrix::Matrix<double> A) {
    
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 3; y++)
            std::cout << A(x, y) << " ";
        std::cout << std::endl;
    }
}


int main()
{
    Matrix::Matrix<double> A(4, 3);
    Matrix::Matrix<double> B(4, 3);

    Matrix::Matrix<double> C = A + B;

    print_m(A);
    print_m(B);
    print_m(C);

    std::cout << "------------------" << std::endl;

    A += B;
    A = Matrix::sigmoid(A);

    print_m(A);
    //B.print_shape();

    //int X = B[0][0][1];

    //cout << X[]
    /*
    std::cout << "SHAPE is : ";   
    for (auto v : sp)
        std::cout << v << "|";
    std::cout << std::endl; 
    */
    return 0;

}
