#include <iostream>
#include <vector>
#include <atrix/matrix.h>

//using namespace Matrix;
using namespace std;

void print_matrix(Matrix::Matrix<double> A) {
    
    auto shape = A.get_shape();

    for (int x = 0; x < shape[0]; x++) {
        for (int y = 0; y < shape[1]; y++)
            std::cout << A(x, y) << " ";
        std::cout << std::endl;
    }
}

int main() {
    Matrix::Matrix<double> A(3, 3);

    cout << "Test 1" << endl;
    print_matrix(A); 

    A(0, 2) = 100;

    Matrix::Matrix<double> C = A;
    print_matrix(C);
    cout << "-------------" << endl;

    C(2, 2) = A(0, 2);

    C += 1000;

    print_matrix(C);
    
}
