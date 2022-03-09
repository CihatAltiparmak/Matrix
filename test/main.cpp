#include <iostream>
#include <vector>
#include "matrix.h"

int main()
{
    Matrix::Matrix<int> A(3, 4, 3, 2, 2);

//    int B = A[0];

//    std::cout << B << endl;

    A.print_shape();

    Matrix::Matrix<int> B = A[1];    
    B.print_shape();


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
