#include <vector>
#include <algorithm>

using Matrix = std::vector<std::vector<double>>;

Matrix blocked_multiply(const Matrix& A, const Matrix& B, int block_size = 64) {
    int n = A.size();
    Matrix C(n, std::vector<double>(n, 0.0));
    
    for (int ii = 0; ii < n; ii += block_size) {
        for (int kk = 0; kk < n; kk += block_size) {
            for (int jj = 0; jj < n; jj += block_size) {
                
                for (int i = ii; i < std::min(ii + block_size, n); i++) {
                    for (int k = kk; k < std::min(kk + block_size, n); k++) {
                        double aik = A[i][k];
                        for (int j = jj; j < std::min(jj + block_size, n); j++) {
                            C[i][j] += aik * B[k][j];
                        }
                    }
                }
            }
        }
    }
    return C;
}