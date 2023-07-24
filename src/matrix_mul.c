#include "matrix_mul.h"

// Measuring memory and modulo
u_int64_t mul_no_mem(int size, u_int32_t p){
    /* Simulate the computation of mul_naive without 2D array strucuture */
    u_int64_t a = rand() % p;
    u_int64_t b = rand() % p;
    u_int64_t c = rand() % p;

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            for (int k = 0; k < size; k++){
                c = (c + a * b) % p;
            }
        }
    }

    return c;
}

u_int64_t** mul_no_mod(u_int64_t** A, u_int64_t** B, int size){
    /* Simulate the computation of mul_naive without mod */
    u_int64_t** C = create_matrix(size);

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            for (int k = 0; k < size; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Naive implementation
u_int64_t** mul_naive(u_int64_t** A, u_int64_t** B, int size, u_int32_t p){
    /* Does the matrix multiplication using naive method */
    u_int64_t** C = create_matrix(size);

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            for (int k = 0; k < size; k++){
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % p;

                // p = 2^30 + 3, 2^30 < p < 2^31
                // A, B, C < p
                // Proof that C + A*B < 2^63

                // C + A*B < p^2 + p = p(p+1)
                // p(p+1) = (2^30 + 3) (2^30 + 4)
                // p(p+1) = (2^30 + 3) (2^30 + 2^2)
                // p(p+1) = 2^60 + 2^32 + 3*2^30 + 3*2^2
                // p(p+1) < 2^60 + 2^60 + 2^60 + 2^60
                // p(p+1) < 2^62 < 2^63
                // So there is no overflow, each (C_ij) fits in u_int64_t.
            }

        }
    }

    return C;
}

// Implementations based on Data locality
u_int64_t** mul_trans(u_int64_t** A, u_int64_t** B, int size, u_int32_t p){
    /* Does the matrix multiplication using transpose method */
    u_int64_t** C = create_matrix(size);
    u_int64_t** T = transpose_matrix(B, size);

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            for (int k = 0; k < size; k++){
                C[i][j] = (C[i][j] + A[i][k] * T[j][k]) % p;
            }
        }
    }

    return C;
}

u_int64_t** mul_block(u_int64_t** A, u_int64_t** B, int size, u_int32_t p){
    /* Does the matrix multiplication using blocking method */
    u_int64_t** C = create_matrix(size);
    int b = 104;

    for (int i = 0; i < size; i += b){
        for (int j = 0; j < size; j += b){
            for (int k = 0; k < size; k += b){

                for (int ii = i; ii < i + b && ii < size; ii++){
                    for (int jj = j; jj < j + b && jj < size; jj++){
                        for (int kk = k; kk < k + b && kk < size; kk++){
                            C[ii][jj] = (C[ii][jj] + A[ii][kk] * B[kk][jj]) % p;
                        }
                    }
                }

            }
        }
    }


    // int q = size / b;

    // for (int i = 0; i <= q; i++){
    //     for (int j = 0; j <= q; j++){
    //         for (int k = 0; k <= q; k++){

    //             for (int ii = 0; ii < b && (i*b + ii) < size; ii++){
    //                 for (int jj = 0; jj < b && (j*b + jj) < size; jj++){
    //                     for (int kk = 0; kk < b && (k*b + kk) < size; kk++){
    //                         C[i*b + ii][j*b + jj] = (C[i*b + ii][j*b + jj] + A[i*b + ii][k*b + kk] * B[k*b + kk][j*b + jj]) % p;
    //                     }
    //                 }
    //             }

    //         }
    //     }
    // }
    // Does the same thing but is slower

    return C;
}


u_int64_t** mul_block_trans(u_int64_t** A, u_int64_t** B, int size, u_int32_t p){
    /* Does the matrix multiplication using multiple implementation: Block and Trans */
    u_int64_t** C = create_matrix(size);
    u_int64_t** T = transpose_matrix(B, size);
    int b = 104;

    for (int i = 0; i < size; i += b){
        for (int j = 0; j < size; j += b){
            for (int k = 0; k < size; k += b){

                for (int ii = i; ii < i + b && ii < size; ii++){
                    for (int jj = j; jj < j + b && jj < size; jj++){
                        for (int kk = k; kk < k + b && kk < size; kk++){
                            C[ii][jj] = (C[ii][jj] + A[ii][kk] * T[jj][kk]) % p;
                        }
                    }
                }

            }
        }
    }

    return C;
}

// Implementations based on Modulo
u_int64_t** mul_decomp(u_int64_t** A, u_int64_t** B, int size, u_int32_t p){
    /* Does the matrix multiplication using decomp method */
    u_int64_t** C = create_matrix(size);

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            u_int64_t h = 0;
            u_int64_t l = 0;
            for (int k = 0; k < size; k++){
                u_int64_t temp = A[i][k] * B[k][j];
                h += temp >> 32;
                l += temp - ((temp >> 32) << 32);

                // A * B < p^2 < 2^62
                // h_k = h_k-1 + A*B < k * 2^30: if k = 1024 = 2^10
                // h = Sum h_k < n * 2^30

                // We need h < 2^30 because of (h * 2^32 + l)

                // l_k = temp - (h_k * 2^32) < 2^32
                // l = Sum l_k < n * 2^32
            }
            u_int64_t n = 1;
            C[i][j] = ((h % p) * (n << 32) + l) % p;
        }
    }

    return C;
}


u_int32_t reduction(u_int64_t a, u_int32_t p){
    /* Makes the modulo operation using Barrett's reduction method.
    Based on this research paper: https://arxiv.org/ftp/arxiv/papers/1407/1407.3383.pdf
    Returns a % p
    */
    u_int32_t s = 30;
    u_int32_t t = 32;

    u_int64_t b = a >> s;
    u_int64_t c = (b * 4294967284) >> t; // 4294967284 = (2^62 / p)

    u_int32_t res = a - c * p;
    (res >= p) ? res -= p : res;
    (res >= p) ? res -= p : res;
    return res;
}


u_int64_t** mul_barrett(u_int64_t** A, u_int64_t** B, int size, u_int32_t p){
    /* Does the matrix multiplication using Barrett's reduction method */
    u_int64_t** C = create_matrix(size);

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            for (int k = 0; k < size; k++){
                C[i][j] = reduction(C[i][j] + A[i][k] * B[k][j], p);
            }
        }
    }

    return C;
}

u_int64_t** mul_decomp_barrett(u_int64_t** A, u_int64_t** B, int size, u_int32_t p){
    /* Does the matrix multiplication using multiple implementation: Decomp and Barrett */
    u_int64_t** C = create_matrix(size);

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            u_int64_t h = 0;
            u_int64_t l = 0;
            for (int k = 0; k < size; k++){
                u_int64_t temp = A[i][k] * B[k][j];
                h += temp >> 32;
                l += temp - ((temp >> 32) << 32);
            }
            u_int64_t n = 1;
            u_int64_t h_reduced = reduction(h, p);
            u_int64_t l_reduced = reduction(l, p);
            C[i][j] = reduction(h_reduced * (n << 32) + l_reduced, p);
        }
    }

    return C;
}

// Grouping implementations
u_int64_t** mul_decomp_barrett_block_trans(u_int64_t** A, u_int64_t** B, int size, u_int32_t p){
    /* Does the matrix multiplication using multiple implementation: Decomp Barrett Block and Trans */
    u_int64_t** C = create_matrix(size);
    u_int64_t** T = transpose_matrix(B, size);

    int b = 104;

    for (int i = 0; i < size; i += b){
        for (int j = 0; j < size; j += b){
            for (int k = 0; k < size; k += b){

                for (int ii = i; ii < i + b && ii < size; ii++){
                    for (int jj = j; jj < j + b && jj < size; jj++){
                        u_int64_t h = 0;
                        u_int64_t l = 0;
                        for (int kk = k; kk < k + b && kk < size; kk++){
                            u_int64_t temp = A[ii][kk] * T[jj][kk];
                            h += temp >> 32;
                            l += temp - ((temp >> 32) << 32);
                        }
                        u_int64_t n = 1;
                        u_int64_t h_reduced = reduction(h, p);
                        u_int64_t l_reduced = reduction(l, p);
                        C[ii][jj] = reduction((C[ii][jj] + h_reduced * (n << 32) + l_reduced), p);
                    }
                }

            }
        }
    }

    return C;
}

u_int64_t** mul_decomp_barrett_trans(u_int64_t** A, u_int64_t** B, int size, u_int32_t p){
    /* Does the matrix multiplication using multiple implementation: Decomp Barrett and Trans */
    u_int64_t** C = create_matrix(size);
    u_int64_t** T = transpose_matrix(B, size);

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            u_int64_t h = 0;
            u_int64_t l = 0;
            for (int k = 0; k < size; k++){
                u_int64_t temp = A[i][k] * T[j][k];
                h += temp >> 32;
                l += temp - ((temp >> 32) << 32);
            }
            u_int64_t n = 1;
            u_int64_t h_reduced = reduction(h, p);
            u_int64_t l_reduced = reduction(l, p);
            C[i][j] = reduction(h_reduced * (n << 32) + l_reduced, p);
        }
    }

    return C;
}
