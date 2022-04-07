#include <iostream>
#include <vector>

#include <atrix/matrix.h>
#include <atrix/vector.h>

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

    Matrix::Vector<double> v(4, 1);
    print_matrix(v);

    cout << "--------------------" << endl;

    Matrix::Matrix<double> A(4, 1);
    Matrix::Vector<double> u(A);
    print_matrix(u); 

    cout << "The norm of u: " << u.norm(false) << endl; 
    cout << "--------------------" << endl;

    Matrix::Vector<double> B = v + u;
    Matrix::Matrix<double> C = v + u + u;
    print_matrix(B);
    cout << "##################" << endl;
    print_matrix(C);    
    cout << "--------------------" << endl;

    double a_1 = 15;
    Matrix::Vector<double> z = v * a_1;
    print_matrix(z);

    cout << "---------------- TEST --------------------" << endl;

    Matrix::Matrix<double> D(5, 6);
    vector<Matrix::Vector<double>> row_vecs = Matrix::get_row_vectors(D);

    for (int i = 0; i < 5; i++) {
        print_matrix(row_vecs[i]);
        cout << "################" << endl;
    }

}
