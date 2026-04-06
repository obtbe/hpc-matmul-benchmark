#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cmath>

using Matrix = std::vector<std::vector<double>>;

// Forward declarations
Matrix naive_multiply(const Matrix& A, const Matrix& B);
Matrix blocked_multiply(const Matrix& A, const Matrix& B, int block_size = 64);
Matrix openmp_multiply(const Matrix& A, const Matrix& B);

// Wrapper for blocked_multiply with default block size
Matrix blocked_multiply_wrapper(const Matrix& A, const Matrix& B) {
    return blocked_multiply(A, B, 64);
}

Matrix random_matrix(int n) {
    Matrix M(n, std::vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = (double)rand() / RAND_MAX;
        }
    }
    return M;
}

double benchmark(const Matrix& A, const Matrix& B, Matrix (*func)(const Matrix&, const Matrix&)) {
    auto start = std::chrono::high_resolution_clock::now();
    Matrix C = func(A, B);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int main() {
    // Test sizes
    std::vector<int> sizes = {128, 256, 384, 512, 640, 768, 896, 1024};
    
    // Create results directory if it doesn't exist
    if (system("mkdir -p results") == -1) {
        std::cerr << "Warning: Could not create results directory" << std::endl;
    }
    
    std::ofstream results("results/raw_data.csv");
    results << "size,naive_time,blocked_time,openmp_time\n";
    
    std::cout << std::setw(8) << "Size" 
              << std::setw(14) << "Naive (s)" 
              << std::setw(14) << "Blocked (s)" 
              << std::setw(14) << "OpenMP (s)" 
              << std::setw(12) << "Speedup" << std::endl;
    std::cout << std::string(62, '-') << std::endl;
    
    for (int n : sizes) {
        std::cout << "Benchmarking size " << n << "..." << std::flush;
        
        Matrix A = random_matrix(n);
        Matrix B = random_matrix(n);
        
        double naive_time = benchmark(A, B, naive_multiply);
        double blocked_time = benchmark(A, B, blocked_multiply_wrapper);
        double openmp_time = benchmark(A, B, openmp_multiply);
        
        double speedup = naive_time / openmp_time;
        
        results << n << "," << naive_time << "," << blocked_time << "," << openmp_time << "\n";
        
        std::cout << "\r" << std::setw(8) << n 
                  << std::setw(14) << std::fixed << std::setprecision(4) << naive_time
                  << std::setw(14) << blocked_time
                  << std::setw(14) << openmp_time
                  << std::setw(12) << std::setprecision(2) << speedup << "x" << std::endl;
    }
    
    results.close();
    std::cout << "\nResults saved to results/raw_data.csv" << std::endl;
    return 0;
}