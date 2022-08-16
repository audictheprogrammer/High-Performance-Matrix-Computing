#include "matrix.h"
#include "matrix_mul.h"

int input(int argc, char** argv){
    if (argc != 2){
        printf("Please input size\n");
        char buffer[16];
        int size;
        if (fgets(buffer, 16, stdin) != NULL){
            if (sscanf(buffer, "%d", &size) == 1){
                return size;
            }
        }
        return input(0, NULL);
    }

    return atoi(argv[1]);
}

void debug_mul_naive(u_int32_t p){
    /* Compares mul_naive with flint's matrix mul */
    int size;

    // SIZE 16
    // u_int64_t** A = read_matrix("debug/mat_A_16.txt", &size);
    // u_int64_t** B = read_matrix("debug/mat_B_16.txt", &size);
    // u_int64_t** C = read_matrix("debug/mat_C_16.txt", &size);

    // u_int64_t** D = mul_naive(A, B, size, p);
    // write_matrix(D, size, "debug/mat_D_16.txt");

    // equals_matrix_file("debug/mat_C_16.txt", "debug/mat_D_16.txt");

    // // SIZE 32
    // u_int64_t** A = read_matrix("debug/mat_A_32.txt", &size);
    // u_int64_t** B = read_matrix("debug/mat_B_32.txt", &size);
    // u_int64_t** C = read_matrix("debug/mat_C_32.txt", &size);

    // u_int64_t** D = mul_naive(A, B, size, p);
    // write_matrix(D, size, "debug/mat_D_32.txt");

    // if (equals_matrix(C, D, size))
    //     printf("C equals D! \n");
    // else
    //     printf("C not equals to D! \n");
    
    // SIZE 64
    u_int64_t** A = read_matrix("debug/mat_A_64.txt", &size);
    u_int64_t** B = read_matrix("debug/mat_B_64.txt", &size);
    u_int64_t** C = read_matrix("debug/mat_C_64.txt", &size);
    u_int64_t** D = mul_naive(A, B, size, p);

    write_matrix(D, size, "debug/mat_D_64.txt");

    if (equals_matrix(C, D, size))
        printf("Naive passed !\n");
    else
        printf("Bug \n");

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);
    delete_matrix(&D, size);

    return;
}

void debug_mul_trans(int size, u_int32_t p){
    /* Compares mul_naive with mul_trans */
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);
    u_int64_t** C = mul_naive(A, B, size, p);
    u_int64_t** D = mul_trans(A, B, size, p);

    write_matrix(A, size, "debug/debug_A.txt");
    write_matrix(B, size, "debug/debug_B.txt");
    write_matrix(C, size, "debug/debug_C.txt");
    write_matrix(D, size, "debug/debug_D.txt");

    if (equals_matrix_file("debug/debug_C.txt", "debug/debug_D.txt"))
        printf("Trans passed !\n");
    else
        printf("Bug \n");

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);
    delete_matrix(&D, size);

    return;
}

void debug_mul_block(int size, u_int32_t p){
    /* Compares mul_trans with mul_block */
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);
    u_int64_t** C = mul_trans(A, B, size, p);
    u_int64_t** D = mul_block(A, B, size, p);

    write_matrix(A, size, "debug/debug_A.txt");
    write_matrix(B, size, "debug/debug_B.txt");
    write_matrix(C, size, "debug/debug_C.txt");
    write_matrix(D, size, "debug/debug_D.txt");

    if (equals_matrix_file("debug/debug_C.txt", "debug/debug_D.txt"))
        printf("Trans passed !\n");
    else
        printf("Bug \n");

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);
    delete_matrix(&D, size);

    return;
}

void debug_mul_block_trans(int size, u_int32_t p){
    /* Compares mul_trans with mul_block_trans */
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);
    u_int64_t** C = mul_trans(A, B, size, p);
    u_int64_t** D = mul_block_trans(A, B, size, p);

    write_matrix(A, size, "debug/debug_A.txt");
    write_matrix(B, size, "debug/debug_B.txt");
    write_matrix(C, size, "debug/debug_C.txt");
    write_matrix(D, size, "debug/debug_D.txt");

    if (equals_matrix_file("debug/debug_C.txt", "debug/debug_D.txt"))
        printf("Block Trans passed !\n");
    else
        printf("Bug \n");

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);
    delete_matrix(&D, size);

    return;
}

void debug_mul_decomp(int size, u_int32_t p){
    /* Compares mul_trans with mul_decomp */
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);
    u_int64_t** C = mul_trans(A, B, size, p);
    u_int64_t** D = mul_decomp(A, B, size, p);

    write_matrix(A, size, "debug/debug_A.txt");
    write_matrix(B, size, "debug/debug_B.txt");
    write_matrix(C, size, "debug/debug_C.txt");
    write_matrix(D, size, "debug/debug_D.txt");

    if (equals_matrix_file("debug/debug_C.txt", "debug/debug_D.txt"))
        printf("Decomp passed !\n");
    else
        printf("Bug \n");

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);
    delete_matrix(&D, size);

    return;
}

void debug_mul_barrett(int size, u_int32_t p){
    /* Compares mul_trans with mul_barrett */
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);
    u_int64_t** C = mul_trans(A, B, size, p);
    u_int64_t** D = mul_barrett(A, B, size, p);

    write_matrix(A, size, "debug/debug_A.txt");
    write_matrix(B, size, "debug/debug_B.txt");
    write_matrix(C, size, "debug/debug_C.txt");
    write_matrix(D, size, "debug/debug_D.txt");

    if (equals_matrix_file("debug/debug_C.txt", "debug/debug_D.txt"))
        printf("Barrett passed !\n");
    else
        printf("Bug \n");

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);
    delete_matrix(&D, size);

    return;
}

void debug_mul_decomp_barrett(int size, u_int32_t p){
    /* Compares mul_trans with mul_decomp_barrett */
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);
    u_int64_t** C = mul_trans(A, B, size, p);
    u_int64_t** D = mul_decomp_barrett(A, B, size, p);

    write_matrix(A, size, "debug/debug_A.txt");
    write_matrix(B, size, "debug/debug_B.txt");
    write_matrix(C, size, "debug/debug_C.txt");
    write_matrix(D, size, "debug/debug_D.txt");

    if (equals_matrix_file("debug/debug_C.txt", "debug/debug_D.txt"))
        printf("Decomp Barrett passed !\n");
    else
        printf("Bug \n");

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);
    delete_matrix(&D, size);

    return;
}

void debug_mul_decomp_barrett_block_trans(int size, u_int32_t p){
    /* Compares mul_trans with mul_decomp_barrett_block_trans */
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);
    u_int64_t** C = mul_trans(A, B, size, p);
    u_int64_t** D = mul_decomp_barrett_block_trans(A, B, size, p);

    write_matrix(A, size, "debug/debug_A.txt");
    write_matrix(B, size, "debug/debug_B.txt");
    write_matrix(C, size, "debug/debug_C.txt");
    write_matrix(D, size, "debug/debug_D.txt");

    if (equals_matrix_file("debug/debug_C.txt", "debug/debug_D.txt"))
        printf("Decomp Barrett Block Trans passed !\n");
    else
        printf("Bug \n");

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);
    delete_matrix(&D, size);

    return;
}

void debug_mul_decomp_barrett_trans(int size, u_int32_t p){
    /* Compares mul_trans with mul_decomp_barrett_trans */
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);
    u_int64_t** C = mul_trans(A, B, size, p);
    u_int64_t** D = mul_decomp_barrett_trans(A, B, size, p);

    write_matrix(A, size, "debug/debug_A.txt");
    write_matrix(B, size, "debug/debug_B.txt");
    write_matrix(C, size, "debug/debug_C.txt");
    write_matrix(D, size, "debug/debug_D.txt");

    if (equals_matrix_file("debug/debug_C.txt", "debug/debug_D.txt"))
        printf("Decomp Barrett Trans passed !\n");
    else
        printf("Bug \n");

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);
    delete_matrix(&D, size);

    return;
}

int main(int argc, char** argv){
    srand(time(NULL));
    u_int32_t p = 1073741827;
    int size = input(argc, argv);

    printf("Debugging Naive...\n");
    debug_mul_naive(p);

    printf("Debugging Trans...\n");
    debug_mul_trans(size, p);
    printf("Debugging Block...\n");
    debug_mul_block(size, p);
    printf("Debugging Block Trans...\n");
    debug_mul_block_trans(size, p);

    printf("Debugging Decomp... \n");
    debug_mul_decomp(size, p);
    printf("Debugging Barrett... \n");
    debug_mul_barrett(size, p);
    printf("Debugging Decomp Barrett... \n");
    debug_mul_decomp_barrett(size, p);

    printf("Debugging Decomp Barrett Block Trans... \n");
    debug_mul_decomp_barrett_block_trans(size, p);
    printf("Debugging Decomp Barrett Trans... \n");
    debug_mul_decomp_barrett_trans(size, p);

    return 0;
}