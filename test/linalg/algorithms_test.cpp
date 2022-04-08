#include <iostream>
#include <vector>

#include <atrix/matrix.h>
#include <atrix/vector.h>
#include <atrix/linalg/algorithms.h>
#include <atrix/linalg/decompositions.h>

//using namespace Matrix;
using namespace std;

void print_matrix(Matrix::Vector<double> A) {
    cout << "VECTOR FUNC" << endl;    
    auto shape = A.get_shape();

    for (int x = 0; x < shape[0]; x++) {
        for (int y = 0; y < shape[1]; y++)
            std::cout << A(x, y) << " ";
        std::cout << std::endl;
    }
}

void print_matrix(Matrix::Matrix<double> A) {
 
    cout << "MATRIX FUNC" << endl;
    auto shape = A.get_shape();

    for (int x = 0; x < shape[0]; x++) {
        for (int y = 0; y < shape[1]; y++)
            std::cout << A(x, y) << " ";
        std::cout << std::endl;
    }
}

int main() {
    
    Matrix::Matrix<double> A(3, 3);

    A(0, 0) = 100;
    A(1, 0) = 47;
    A(2, 0) = -7;

    std::vector<Matrix::Vector<double>> a_vec = Matrix::to_column_vectors(A);
    std::vector<Matrix::Vector<double>> o_vec = Matrix::gram_schmidt(a_vec);

    /*
    for (auto o : o_vec) {
        print_matrix(o);
        std::cout << "-----------------" << std::endl;
    }
    */
    std::vector<Matrix::Matrix<double>> QR_D = Matrix::QR(A);
    
    std::cout << "Q" << std::endl;
    print_matrix(QR_D[0]);
    std::cout << "---------------" << std::endl;
    print_matrix(QR_D[1]);

}
