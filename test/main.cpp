#include <iostream>
#include <vector>

#include "../src/matrix.h"
#include "../src/linalg/algorithms.h"
#include "../src/linalg/decompositions.h"

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
     
    print_m(A);
    std::cout << "*********************" << std::endl;


    A(0, 0) = 100;
    A(1, 0) = -100;
    A(2, 0) = 0;

    std::vector<Matrix::Matrix<double>> res = Matrix::LU(A);
    std::cout << res.size() << std::endl;
    print_m(res[0]);
    std::cout << "*********************" << std::endl;
    print_m(res[1]);
    std::cout << "*********************" << std::endl;    

    Matrix::Matrix<double> K = Matrix::dot(res[0], res[1]);
    print_m(K) ;

    /*
    Matrix::Matrix<double> K = Matrix::dot(A, A);

    print_m(A);
    std::cout << "*********************" << std::endl;

    print_m(K); 

    A(0, 0) = 100;
    A(1, 0) = -100;
    A(2, 0) = 0;


    Matrix::Matrix<double> invA = Matrix::inv(A);

    double ADet   = Matrix::det(A);
    std::cout << "********************" << std::endl;
    double invDet = Matrix::det(invA);

    std::cout << ADet << " : " << invDet << std::endl;
    */
    return 0;

}
