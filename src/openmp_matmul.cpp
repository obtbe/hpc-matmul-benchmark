#include <vector>
#include <omp.h>

using Matrix = std::vector<std::vector<double>>;

Matrix openmp_multiply(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, std::vector<double>(n, 0.0));
    
    // Parallelize only the outer loop (better for large matrices)
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            double aik = A[i][k];
            // Inner loop - each thread works on its own row
            for (int j = 0; j < n; j++) {
                C[i][j] += aik * B[k][j];
            }
        }
    }
    return C;
}