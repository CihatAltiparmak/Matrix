# My Matrix Library

![love](http://ForTheBadge.com/images/badges/built-with-love.svg)

This matrix library is the library that create matrix easily and perform various matrix operations for cpp. 

# Table of contents

# Installation
This Project is still under construction.
But it is set **installation with cmake**.

To install the Matrix library, just run
```
$ git clone https://github.com/CihatAltiparmak/Matrix.git
$ cd Matrix
$ mkdir build && cd build
$ cmake ..
$ sudo make install
```

These commands will setup  Matrix library to `/usr/local/include` and `/usr/local/lib`

To see files that are installed, run
```
$ cat install_manifest.txt
```
To uninstall this library
```
$ xarg rm < install_manifest.txt
```

To use this library in your project, you can compile like this

main.cpp
```cpp
#include <iostream>
#include <vector>

#include <atrix/matrix.h>
#include <atrix/linalg/algorithms.h>
#include <atrix/linalg/decompositions.h>

void print_m(Matrix::Matrix<double> A) {
    
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++)
            std::cout << A(x, y) << " ";
        std::cout << std::endl;
    }
}

void print_m1(Matrix::Matrix<double> A) {
    
    for (int x = 0; x < 3; x++)
        std::cout << A(x) << " ";
    std::cout << std::endl;
}

int main()
{

    Matrix::Matrix<double> A(3, 3);
    Matrix::Matrix<double> C = Matrix::zeros<double>(3, 3);
     
    print_m(A);
    std::cout << "*********************" << std::endl;

    std::vector<Matrix::Matrix<double>> X = Matrix::get_column_vectors(A);

    for (auto v : X) {
        print_m1(v);
        std::cout << "###########" << std::endl;
    }

    A(0, 0) = 100;
    A(1, 0) = -100;
    A(2, 0) = 0;

    return 0;

}
```

Compile command

```shell
g++ main.cpp -o main -std=c++17 -g
```

# Documentation
The matrix library documentation is only inside source code of this repo now. But the wiki of this repo is going to be edited for documentation.


# Benchmarks
It is going to be added soon.

# Getting Help
You can open issue here or you can mail to me.

# Contribute 
It is going to be added soon

# Code Contributors
![GitHub Contributors Image](https://contrib.rocks/image?repo=CihatAltiparmak/Matrix)

# License
This repo is under MIT LICENSE

# TODO
* Add benchmark for all functions and methods in this repo.
* Add decomposition functions, functions that convert a matrix to row-echelon and reduced row echelon form.
* Add assertions for some functions.
* Add augment function for operations like [A | I] here
* Refactor the function inv there if you can augment function.
* You can add the functions for eigen values.
* Edit the wiki of this project.
* Edit the README.md of this project.
* Add test option for this repo (insufficient)
* Add python bindings (That's not importart. It's not priority for us now)

# Third Party Libraries
* It is not used third party library in this repo.
