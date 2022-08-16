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

void benchmark_mul_no_mem(char* filename, int size, u_int32_t p){
    FILE* f = fopen(filename, "w");

    clock_t initial = clock();
    u_int64_t c = mul_no_mem(size, p);
    clock_t final = clock();

    double time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    printf("Arith Mem: size = %d time = %f \n", size, time);
    fprintf(f, "%d %f ", size, time);

    fclose(f);
    return;
}

void benchmark_mul_no_mod(char* filename, int size, u_int32_t p){

    FILE* f = fopen(filename, "w");
    
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);

    clock_t initial = clock();
    u_int64_t** C = mul_no_mod(A, B, size);
    clock_t final = clock();

    double time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    printf("Arith Mod: size = %d time = %f \n", size, time);
    fprintf(f, "%d %f ", size, time);

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);

    fclose(f);
    return;
}

void benchmark_mul_naive(char* filename, int size, u_int32_t p){

    FILE* f = fopen(filename, "w");
    
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);

    clock_t initial = clock();
    u_int64_t** C = mul_naive(A, B, size, p);
    clock_t final = clock();

    double time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    printf("Naive: size = %d time = %f \n", size, time);
    fprintf(f, "%d %f ", size, time);

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);

    fclose(f);
    return;
}

void benchmark_mul_trans(char* filename, int size, u_int32_t p){

    FILE* f = fopen(filename, "w");
    
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);

    clock_t initial = clock();
    u_int64_t** C = mul_trans(A, B, size, p);
    clock_t final = clock();

    double time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    printf("Trans: size = %d time = %f \n", size, time);
    fprintf(f, "%d %f ", size, time);

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);

    fclose(f);
    return;
}

void benchmark_mul_block(char* filename, int size, u_int32_t p){

    FILE* f = fopen(filename, "w");
    
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);

    clock_t initial = clock();
    u_int64_t** C = mul_block(A, B, size, p);
    clock_t final = clock();

    double time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    printf("Block: size = %d time = %f \n", size, time);
    fprintf(f, "%d %f ", size, time);

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);

    fclose(f);
    return;
}

void benchmark_mul_block_trans(char* filename, int size, u_int32_t p){

    FILE* f = fopen(filename, "w");
    
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);

    clock_t initial = clock();
    u_int64_t** C = mul_block_trans(A, B, size, p);
    clock_t final = clock();

    double time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    printf("Block Trans: size = %d time = %f \n", size, time);
    fprintf(f, "%d %f ", size, time);

    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);

    fclose(f);
    return;
}

void benchmark_mul_decomp(char* filename, int size, u_int32_t p){

    FILE* f = fopen(filename, "w");
    
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);

    clock_t initial = clock();
    u_int64_t** C = mul_decomp(A, B, size, p);
    clock_t final = clock();

    double time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    printf("Decomp: size = %d time = %f \n", size, time);
    fprintf(f, "%d %f ", size, time);
    
    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);

    fclose(f);
    return;
}

void benchmark_mul_barrett(char* filename, int size, u_int32_t p){

    FILE* f = fopen(filename, "w");
    
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);

    clock_t initial = clock();
    u_int64_t** C = mul_barrett(A, B, size, p);
    clock_t final = clock();

    double time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    printf("Barrett: size = %d time = %f \n", size, time);
    fprintf(f, "%d %f ", size, time);
    
    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);

    fclose(f);
    return;
}

void benchmark_mul_decomp_barrett(char* filename, int size, u_int32_t p){

    FILE* f = fopen(filename, "w");
    
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);

    clock_t initial = clock();
    u_int64_t** C = mul_decomp_barrett(A, B, size, p);
    clock_t final = clock();

    double time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    printf("Decomp Barrett: size = %d time = %f \n", size, time);
    fprintf(f, "%d %f ", size, time);
    
    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);

    fclose(f);
    return;
}

void benchmark_mul_decomp_barrett_block_trans(char* filename, int size, u_int32_t p){

    FILE* f = fopen(filename, "w");
    
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);

    clock_t initial = clock();
    u_int64_t** C = mul_decomp_barrett_block_trans(A, B, size, p);
    clock_t final = clock();

    double time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    printf("Decomp Barrett Block Trans: size = %d time = %f \n", size, time);
    fprintf(f, "%d %f ", size, time);
    
    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);

    fclose(f);
    return;
}

void benchmark_mul_decomp_barrett_trans(char* filename, int size, u_int32_t p){

    FILE* f = fopen(filename, "w");
    
    u_int64_t** A = create_matrix_mod(size, p);
    u_int64_t** B = create_matrix_mod(size, p);

    clock_t initial = clock();
    u_int64_t** C = mul_decomp_barrett_trans(A, B, size, p);
    clock_t final = clock();

    double time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    printf("Decomp Barrett Trans: size = %d time = %f \n", size, time);
    fprintf(f, "%d %f ", size, time);
    
    delete_matrix(&A, size);
    delete_matrix(&B, size);
    delete_matrix(&C, size);

    fclose(f);
    return;
}
int main(int argc, char** argv){
    srand(time(NULL));
    u_int32_t p = 1073741827;
    int size = input(argc, argv);

    // FILENAME
    // Measuring memory and modulo
    char filename_arith_mem[256] = "\0";
    sprintf(filename_arith_mem, "benchmark/Arith_Mem_%d.txt", size);
    char filename_arith_mod[256] = "\0";
    sprintf(filename_arith_mod, "benchmark/Arith_Mom_%d.txt", size);

    // Naive implementation
    char filename_naive[256] = "\0";
    sprintf(filename_naive, "benchmark/Naive_%d.txt", size);

    // Implementations based on Data locality
    char filename_trans[256] = "\0";
    sprintf(filename_trans, "benchmark/Trans_%d.txt", size);
    char filename_block[256] = "\0";
    sprintf(filename_block, "benchmark/Block_%d.txt", size);
    char filename_block_trans[256] = "\0";
    sprintf(filename_block_trans, "benchmark/Block_Trans_%d.txt", size);

    // Implementations based on Modulo
    char filename_decomp[256] = "\0";
    sprintf(filename_decomp, "benchmark/Decomp_%d.txt", size);
    char filename_barrett[256] = "\0";
    sprintf(filename_barrett, "benchmark/Barrett_%d.txt", size);
    char filename_decomp_barrett[256] = "\0";
    sprintf(filename_decomp_barrett, "benchmark/DecompBarrett_%d.txt", size);
    
    // Grouping implementations
    char filename_decomp_barrett_block_trans[256] = "\0";
    sprintf(filename_decomp_barrett_block_trans, "benchmark/Decomp_Barrett_BLock_Trans_%d.txt", size);
    char filename_decomp_barrett_trans[256] = "\0";
    sprintf(filename_decomp_barrett_trans, "benchmark/Decomp_Barrett_Trans_%d.txt", size);

    // BENCHMARKING
    benchmark_mul_no_mem(filename_arith_mem, size, p);
    benchmark_mul_no_mod(filename_arith_mod, size, p);

    printf("\n");

    benchmark_mul_naive(filename_naive, size, p);
    benchmark_mul_trans(filename_trans, size, p);
    benchmark_mul_block(filename_block, size, p);
    benchmark_mul_block_trans(filename_block_trans, size, p);

    printf("\n");

    benchmark_mul_decomp(filename_decomp, size, p);
    benchmark_mul_barrett(filename_barrett, size, p);
    benchmark_mul_decomp_barrett(filename_decomp_barrett, size, p);

    printf("\n");

    benchmark_mul_decomp_barrett_block_trans(filename_decomp_barrett_block_trans, size, p);
    benchmark_mul_decomp_barrett_trans(filename_decomp_barrett_trans, size, p);

    // Local test logs
    /* 05/08/2022 20:07 LOCAL
    Arith Mem: size = 1024 time = 12.734375 
    Arith Mod: size = 1024 time = 16.296875 

    Naive: size = 1024 time = 25.546875 
    Trans: size = 1024 time = 14.609375 
    Block: size = 1024 time = 13.125000 
    Block Trans: size = 1024 time = 12.750000
    */

    /* 16/08/2022 21:12 LOCAL
    Arith Mem: size = 1024 time = 12.562500 
    Arith Mod: size = 1024 time = 15.687500 

    Naive: size = 1024 time = 22.796875 
    Trans: size = 1024 time = 12.593750 
    Block: size = 1024 time = 13.312500 
    Block Trans: size = 1024 time = 12.687500 

    Decomp: size = 1024 time = 10.281250 
    Barrett: size = 1024 time = 16.625000 
    Decomp Barrett: size = 1024 time = 10.281250 

    Decomp Barrett Block Trans: size = 1024 time = 4.812500 
    Decomp Barrett Trans: size = 1024 time = 4.390625

    // I don't know why Block Trans and Trans has same perf.
    // Same for Decomp Barrett and Decomp.

    */

    return 0;
}