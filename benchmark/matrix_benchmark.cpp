#include <benchmark/benchmark.h>
#include <atrix/matrix.h>

static void CustomArgumentsOfMatrixCreate(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});

}

template <typename... T>
void MatrixCreate(T... dims) {

    Matrix::Matrix<double> A(dims...);
}

static void BM_MatrixCreate(benchmark::State& state) {

    for (auto _ : state) {
        MatrixCreate(state.range(0), state.range(1), state.range(2));
    }
}

BENCHMARK(BM_MatrixCreate)
->Apply(CustomArgumentsOfMatrixCreate);
//------------------------------------

static void CustomArgumentsOfMatrixCopyConstructor(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixCopyConstructor(Matrix::Matrix<double> A) {
    Matrix::Matrix<double> B(A);
}

static void BM_MatrixCopyConstructor(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));

    for (auto _ : state)
        MatrixCopyConstructor(A);
}

BENCHMARK(BM_MatrixCopyConstructor)
->Apply(CustomArgumentsOfMatrixCopyConstructor);

//------------------------------------

static void CustomArgumentsOfMatrixOperatorAssign(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixOperatorAssign(Matrix::Matrix<double> A, Matrix::Matrix<double> B) {
    B = A;
}

static void BM_MatrixOperatorAssign(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));
    Matrix::Matrix<double> B(1, 1, 1);
    for (auto _ : state)
        MatrixOperatorAssign(A, B);
}

BENCHMARK(BM_MatrixOperatorAssign)
->Apply(CustomArgumentsOfMatrixOperatorAssign);

//------------------------------------

static void CustomArgumentsOfMatrixOperatorDivisionByElement(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k, k});
}

template <typename T>
void MatrixOperatorDivisionByElement(Matrix::Matrix<double> A, T element) {
    A /= element;
}

static void BM_MatrixOperatorDivisionByElement(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));

    for (auto _ : state)
        MatrixOperatorDivisionByElement(A, state.range(3));
}

BENCHMARK(BM_MatrixOperatorDivisionByElement)
->Apply(CustomArgumentsOfMatrixOperatorDivisionByElement);

//------------------------------------

static void CustomArgumentsOfMatrixOperatorPlusByElement(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k, k});
}

template <typename T>
void MatrixOperatorPlusByElement(Matrix::Matrix<double> A, T element) {
    A += element;
}

static void BM_MatrixOperatorPlusByElement(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));

    for (auto _ : state)
        MatrixOperatorPlusByElement(A, state.range(3));
}

BENCHMARK(BM_MatrixOperatorPlusByElement)
->Apply(CustomArgumentsOfMatrixOperatorPlusByElement);

//------------------------------------

static void CustomArgumentsOfMatrixOperatorPlusByMatrix(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixOperatorPlusByMatrix(Matrix::Matrix<double> A, Matrix::Matrix<double> B) {
    A += B;
}

static void BM_MatrixOperatorPlusByMatrix(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));
    Matrix::Matrix<double> B(state.range(0), state.range(1), state.range(2));
    for (auto _ : state)
        MatrixOperatorPlusByMatrix(A, B);
}

BENCHMARK(BM_MatrixOperatorPlusByMatrix)
->Apply(CustomArgumentsOfMatrixOperatorPlusByMatrix);

//------------------------------------

static void CustomArgumentsOfMatrixOperatorMinusByElement(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k, k});
}

template <typename T>
void MatrixOperatorMinusByElement(Matrix::Matrix<double> A, T element) {
    A -= element;
}

static void BM_MatrixOperatorMinusByElement(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));

    for (auto _ : state)
        MatrixOperatorMinusByElement(A, state.range(3));
}

BENCHMARK(BM_MatrixOperatorMinusByElement)
->Apply(CustomArgumentsOfMatrixOperatorMinusByElement);

//------------------------------------

static void CustomArgumentsOfMatrixOperatorMinusByMatrix(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixOperatorMinusByMatrix(Matrix::Matrix<double> A, Matrix::Matrix<double> B) {
    A -= B;
}

static void BM_MatrixOperatorMinusByMatrix(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));
    Matrix::Matrix<double> B(state.range(0), state.range(1), state.range(2));
    for (auto _ : state)
        MatrixOperatorMinusByMatrix(A, B);
}

BENCHMARK(BM_MatrixOperatorMinusByMatrix)
->Apply(CustomArgumentsOfMatrixOperatorMinusByMatrix);

//------------------------------------

static void CustomArgumentsOfMatrixOperatorMultiplyByElement(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k, k});
}

template <typename T>
void MatrixOperatorMultiplyByElement(Matrix::Matrix<double> A, T element) {
    A *= element;
}

static void BM_MatrixOperatorMultiplyByElement(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));

    for (auto _ : state)
        MatrixOperatorMultiplyByElement(A, state.range(3));
}

BENCHMARK(BM_MatrixOperatorMultiplyByElement)
->Apply(CustomArgumentsOfMatrixOperatorMultiplyByElement);

//------------------------------------

static void CustomArgumentsOfMatrixOperatorMultiplyByMatrix(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixOperatorMultiplyByMatrix(Matrix::Matrix<double> A, Matrix::Matrix<double> B) {
    A -= B;
}

static void BM_MatrixOperatorMultiplyByMatrix(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));
    Matrix::Matrix<double> B(state.range(0), state.range(1), state.range(2));
    for (auto _ : state)
        MatrixOperatorMultiplyByMatrix(A, B);
}

BENCHMARK(BM_MatrixOperatorMultiplyByMatrix)
->Apply(CustomArgumentsOfMatrixOperatorMultiplyByMatrix);

//------------------------------------

static void CustomArgumentsOfMatrixDot(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 300; i <<= 2)
        for (int j = 1; j < 300; j <<= 2)
            b->Args({i, j});
}

void MatrixDot(Matrix::Matrix<double> A, Matrix::Matrix<double> B) {
    Matrix::dot(A, B);
}

static void BM_MatrixDot(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1));
    Matrix::Matrix<double> B(state.range(1), state.range(0));
    for (auto _ : state)
        MatrixDot(A, B);
}

BENCHMARK(BM_MatrixDot)
->Apply(CustomArgumentsOfMatrixDot);

//------------------------------------

static void CustomArgumentsOfMatrixSigmoid(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixSigmoid(Matrix::Matrix<double> A) {
    Matrix::sigmoid(A);
}

static void BM_MatrixSigmoid(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));

    for (auto _ : state)
        MatrixSigmoid(A);
}

BENCHMARK(BM_MatrixSigmoid)
->Apply(CustomArgumentsOfMatrixSigmoid);

//------------------------------------

static void CustomArgumentsOfMatrixExp(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixExp(Matrix::Matrix<double> A) {
    Matrix::exp(A);
}

static void BM_MatrixExp(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));

    for (auto _ : state)
        MatrixExp(A);
}

BENCHMARK(BM_MatrixExp)
->Apply(CustomArgumentsOfMatrixExp);

//------------------------------------

static void CustomArgumentsOfMatrixTanh(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixTanh(Matrix::Matrix<double> A) {
    Matrix::tanh(A);
}

static void BM_MatrixTanh(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));

    for (auto _ : state)
        MatrixTanh(A);
}

BENCHMARK(BM_MatrixTanh)
->Apply(CustomArgumentsOfMatrixTanh);

//------------------------------------

static void CustomArgumentsOfMatrixZeros(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixZeros(Matrix::Matrix<double> A) {
    Matrix::zeros<double>(A);
}

static void BM_MatrixZeros(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));

    for (auto _ : state)
        MatrixZeros(A);
}

BENCHMARK(BM_MatrixZeros)
->Apply(CustomArgumentsOfMatrixZeros);

//------------------------------------

static void CustomArgumentsOfMatrixOnes(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixOnes(Matrix::Matrix<double> A) {
    Matrix::ones<double>(A);
}

static void BM_MatrixOnes(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));

    for (auto _ : state)
        MatrixOnes(A);
}

BENCHMARK(BM_MatrixOnes)
->Apply(CustomArgumentsOfMatrixOnes);

//------------------------------------

static void CustomArgumentsOfMatrixRandom(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixRandom(Matrix::Matrix<double> A) {
    Matrix::random<double>(A);
}

static void BM_MatrixRandom(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));

    for (auto _ : state)
        MatrixRandom(A);
}

BENCHMARK(BM_MatrixRandom)
->Apply(CustomArgumentsOfMatrixRandom);

//------------------------------------

static void CustomArgumentsOfMatrixReshape(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixReshape(Matrix::Matrix<double> A, std::vector<int> dims) {
    Matrix::reshape(A, dims);
}

static void BM_MatrixReshape(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1), state.range(2));
    std::vector<int> shape = {static_cast<int>(state.range(2)), static_cast<int>(state.range(1)), static_cast<int>(state.range(0))};

    for (auto _ : state)
        MatrixReshape(A, shape);
}

BENCHMARK(BM_MatrixReshape)
->Apply(CustomArgumentsOfMatrixReshape);

//------------------------------------

static void CustomArgumentsOfMatrixSqueeze(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 10; i <<= 2)
        for (int j = 1; j < 10; j <<= 2)
            for (int k = 1; k < 1000; k <<= 3)
                b->Args({i, j, k});
}

void MatrixSqueeze(Matrix::Matrix<double> A) {
    Matrix::squeeze(A);
}

static void BM_MatrixSqueeze(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(1, 1, 1, 1, state.range(0), 1, 1, 1, 1, 1, 1, state.range(1), 1, 1, 1, 1, state.range(2), 1, 1);

    for (auto _ : state)
        MatrixSqueeze(A);
}

BENCHMARK(BM_MatrixSqueeze)
->Apply(CustomArgumentsOfMatrixSqueeze);

//------------------------------------

static void CustomArgumentsOfMatrixIdentity(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 1000; i <<= 2)
        b->Args({i});
}

void MatrixIdentity(int n) {
    Matrix::identity<double>(n);
}

static void BM_MatrixIdentity(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    for (auto _ : state)
        MatrixIdentity(state.range(0));
}

BENCHMARK(BM_MatrixIdentity)
->Apply(CustomArgumentsOfMatrixIdentity);

//------------------------------------

static void CustomArgumentsOfMatrixSwapRows(benchmark::internal::Benchmark* b) {
    for (int i = 2; i < 300; i <<= 2)
        for (int j = 2; j < 300; j <<= 2)
            for (int k = 1; k < i; k <<= 4)
                for (int l = 1; l < i; l <<= 4)
                    b->Args({i, j, k, l});
}

void MatrixSwapRows(Matrix::Matrix<double> A, int a, int b) {
    Matrix::swap_rows(A, a, b);
}

static void BM_MatrixSwapRows(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1));
    int a = state.range(2);
    int b = state.range(3);
    
    for (auto _ : state)
        MatrixSwapRows(A, a, b);
}

BENCHMARK(BM_MatrixSwapRows)
->Apply(CustomArgumentsOfMatrixSwapRows);

//------------------------------------

static void CustomArgumentsOfMatrixReplaceRows(benchmark::internal::Benchmark* b) {
    for (int i = 2; i < 300; i <<= 2)
        for (int j = 2; j < 300; j <<= 2)
            for (int k = 1; k < i; k <<= 4)
                for (int l = 1; l < i; l <<= 4) {
                    //if (k != l)
                    b->Args({i, j, k, l, 15});
                    //std::cout << "(dbg) : " << i << "|" << j << "|" << k << "|"  << l << std::endl;
                }
}

void MatrixReplaceRows(Matrix::Matrix<double> A, int a, int b, int scalar) {
    Matrix::replace_rows(A, a, b, scalar);
}

static void BM_MatrixReplaceRows(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1));
    int a = state.range(2);
    int b = state.range(3);
    int scalar = state.range(4);
    for (auto _ : state)
        MatrixReplaceRows(A, a, b, scalar);
}

BENCHMARK(BM_MatrixReplaceRows)
->Apply(CustomArgumentsOfMatrixReplaceRows);

//------------------------------------

static void CustomArgumentsOfMatrixScaleRow(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 300; i <<= 2)
        for (int j = 2; j < 300; j <<= 2)
            for (int k = 1; k < i; k <<= 4)
                b->Args({i, j, k, 15});
}

void MatrixScaleRow(Matrix::Matrix<double> A, int a, double b) {
    Matrix::scale_row(A, a, b);
}

static void BM_MatrixScaleRow(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1));
    int a = state.range(2);
    double b = state.range(3);
    
    for (auto _ : state)
        MatrixScaleRow(A, a, b);
}

BENCHMARK(BM_MatrixScaleRow)
->Apply(CustomArgumentsOfMatrixScaleRow);

//------------------------------------

static void CustomArgumentsOfMatrixTranspoze(benchmark::internal::Benchmark* b) {
    for (int i = 1; i < 300; i <<= 2)
        for (int j = 1; j < 300; j <<= 2)
            b->Args({i, j});
}

void MatrixTranspoze(Matrix::Matrix<double> A) {
    Matrix::transpoze(A);
}

static void BM_MatrixTranspoze(benchmark::State& state) {
    // FIXME: Is it correct benchmarking? I am not sure.
    Matrix::Matrix<double> A(state.range(0), state.range(1));
    for (auto _ : state)
        MatrixTranspoze(A);
}

BENCHMARK(BM_MatrixTranspoze)
->Apply(CustomArgumentsOfMatrixTranspoze);


BENCHMARK_MAIN();