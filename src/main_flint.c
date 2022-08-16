#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

#include "flint/flint.h"
#include "flint/nmod_mat.h"
// http://www.flintlib.org/flint-2.5.pdf


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

void init_mat(nmod_mat_t* A, nmod_mat_t* B, nmod_mat_t* C, int size,mp_limb_t p){
    FLINT_TEST_INIT(state);
    nmod_mat_init(*A, size, size, p);
    nmod_mat_init(*B, size, size, p);
    nmod_mat_init(*C, size, size, p);
    nmod_mat_randfull(*A, state);
    nmod_mat_randfull(*B, state);
    FLINT_TEST_CLEANUP(state);
}

void benchmark_flint(char* filename, int size, mp_limb_t p){
    
    FILE* f = fopen(filename, "w");

    nmod_mat_t A, B, C;
    init_mat(&A, &B, &C, size, p);

    clock_t initial = clock();
    nmod_mat_mul(C, A, B);
    clock_t final = clock();

    double time = ((double) (final - initial)) / CLOCKS_PER_SEC;
    printf("FLINT: size = %d time = %f \n", size, (double)time);
    fprintf(f, "%d %f ", size, time);

    // printf("Printing A: \n");
    // nmod_mat_print_pretty(A);
    // printf("\nPrinting B: \n");
    // nmod_mat_print_pretty(B);
    // printf("\nPrinting C: \n");
    // nmod_mat_print_pretty(C);
    // Combine with "tee" command on linux
    // Example: ./main_flint 1024 | tee -a output.txt

    nmod_mat_clear(A);
    nmod_mat_clear(B);
    nmod_mat_clear(C);
    
    fclose(f);
    return;
}

int main(int argc, char** argv){
    srand(time(NULL));
    mp_limb_t p = 1073741827;
    int size = input(argc, argv);

    char filename[256] = "\0";
    sprintf(filename, "benchmark/Flint_%d.txt", size);

    benchmark_flint(filename, size, p);

    return 0;
}