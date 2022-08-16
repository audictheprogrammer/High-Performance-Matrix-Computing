#ifndef MATRIX_MUL_H
#define MATRIX_MUL_H

#include "matrix.h"


// Measuring memory and modulo
u_int64_t mul_no_mem(int size, u_int32_t p);
u_int64_t** mul_no_mod(u_int64_t** A, u_int64_t** B, int size);

// Naive implementation
u_int64_t** mul_naive(u_int64_t** A, u_int64_t** B, int size, u_int32_t p);

// Implementations based on Data locality
u_int64_t** mul_trans(u_int64_t** A, u_int64_t** B, int size, u_int32_t p);
u_int64_t** mul_block(u_int64_t** A, u_int64_t** B, int size, u_int32_t p);
u_int64_t** mul_block_trans(u_int64_t** A, u_int64_t** B, int size, u_int32_t p);

// Implementations based on Modulo
u_int64_t** mul_decomp(u_int64_t** A, u_int64_t** B, int size, u_int32_t p);
u_int32_t reduction(u_int64_t a, u_int32_t p);
u_int64_t** mul_barrett(u_int64_t** A, u_int64_t** B, int size, u_int32_t p);
u_int64_t** mul_decomp_barrett(u_int64_t** A, u_int64_t** B, int size, u_int32_t p);


// Grouping implementations
u_int64_t** mul_decomp_barrett_block_trans(u_int64_t** A, u_int64_t** B, int size, u_int32_t p);
u_int64_t** mul_decomp_barrett_trans(u_int64_t** A, u_int64_t** B, int size, u_int32_t p);

#endif
    
    
    
    
    