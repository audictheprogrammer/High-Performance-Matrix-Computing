#include <stdio.h>
#include <stdlib.h>
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
    }

    return atoi(argv[1]);
}

int main(int argc, char** argv){
    const int TEST1 = 0;
    const int TEST2 = 0;
    const int TEST3 = 0;
    const int TEST4 = 0;
    const int TEST5 = 0;
    const int TEST6 = 0;
    const int TEST7 = 1;


    if (TEST1) {
        srand(time(NULL));
        u_int32_t p = 1073741827;
        int size = input(argc, argv);

        u_int64_t** mat = create_matrix_mod(size, p);
        print_matrix(mat, size);
        
        u_int64_t** mat_t = transpose_matrix(mat, size);
        print_matrix(mat_t, size);

        delete_matrix(&mat, size);
        delete_matrix(&mat_t, size);
    }

    if (TEST2) {
        srand(time(NULL));
        u_int32_t p = 1073741827;
        int size = input(argc, argv);

        u_int64_t** mat = create_matrix_mod(size, p);
        write_matrix(mat, size, "mat1.txt");

        int mat_size;
        u_int64_t** mat2 = read_matrix("mat1.txt", &mat_size);
        write_matrix(mat, mat_size, "mat2.txt");

        int nb1 = equals_matrix(mat, mat2, size);
        int nb2 = equals_matrix_file("mat1.txt", "mat2.txt");

        if (nb1)
            printf("mat equals mat2 \n");
        else
            printf("mat not equals mat2 \n");
        if (nb2)
            printf("file1 equals fil2 \n");
        else
            printf("file1 not equals fil2 \n");

        delete_matrix(&mat, size);
        delete_matrix(&mat2, mat_size);
    }
    if (TEST3) {
        srand(time(NULL));
        u_int32_t p = 1073741827;
        int size;

        printf("Reading A... \n");
        u_int64_t** A = read_matrix("mat_A.txt", &size);
        printf("Reading B... \n");
        u_int64_t** B = read_matrix("mat_B.txt", &size);
        printf("Reading C... \n");
        u_int64_t** C = read_matrix("mat_C.txt", &size);
        printf("Computing D naively... \n");
        u_int64_t** D = mul_naive(A, B, size, p);
        write_matrix(D, size, "mat_D.txt");

        if (equals_matrix(C, D, size))
            printf("C equals D! \n");
        else
            printf("C not equals to D! \n");
        
    }

    if (TEST4) {
        srand(time(NULL));
        u_int32_t p = 1073741827;
        int size;

        printf("Reading A... \n");
        u_int64_t** A = read_matrix("mat_A.txt", &size);
        printf("Reading B... \n");
        u_int64_t** B = read_matrix("mat_B.txt", &size);
        printf("Reading C... \n");
        u_int64_t** C = read_matrix("mat_C.txt", &size);

        printf("Computing A*B with transpose method... \n");
        u_int64_t** D = mul_trans(A, B, size, p);
        
        printf("Computing A*B with blocking method... \n");
        u_int64_t** E = mul_trans(A, B, size, p);

        // Check if mul_trans and mul_block are valid.
        if (equals_matrix(C, D, size))
            printf("C equals D! \n");
        else
            printf("C not equals to D! \n");
        
        if (equals_matrix(C, E, size))
            printf("C equals E! \n");
        else
            printf("C not equals to E! \n");
        

    }
    if (TEST5) {
        u_int32_t a = 2147483647;
        u_int64_t b = 2147483647;
        u_int64_t c = a + b;
        u_int64_t d = ((u_int64_t) a) + b;
        u_int32_t e = a + b;

        printf("a = %d \n", a);
        printf("b = %ld \n", b);
        printf("c = %ld \n", c);
        printf("d = %ld \n", d);
        printf("e = %d \n", e);

        // we always have c = d
        // e doesn't work

        u_int64_t n = 9223372036854775807;

        printf("n = %ld \n", n+1); // 2^63
        printf("n2 = %ld \n", n); // 2^63 - 1

        // 2^63 not valid for u_int64_t
        // 2^63-1 valid for u_int64_t

    }

    if (TEST6) {
        u_int64_t lst1[33] = {354617355, 799961463, 639482444, 65587883, 96450888, 1000075130, 659861645, 978692232, 239614840, 916404309, 
        216593519, 5152889, 117776626, 92893461, 173736673, 149372558, 643251926, 16077711, 361021482, 486351602, 452062925, 663825035, 
        391862806, 306884593, 415235050, 523119111, 730893512, 1060437676, 1016327675, 784117384, 95829091, 711335746};

        u_int64_t lst2[33] = {523325216, 706994396, 348613160, 310603731, 353267799, 810346065, 163612198, 239583735, 686655889, 898189884, 
        703541204, 812688889, 778901496, 833811272, 1064363471, 1064788307, 1049254405, 42158020, 721643584, 427179406, 455364967, 269890226, 
        159889744, 447448574, 377405766, 896343894, 495263168, 133990152, 1053110264, 754056279, 1017912613, 1017912613, 103131143};

        u_int32_t p = 1073741827;
        u_int64_t C = 0;
        printf("%ld\n", C);

        for (int i = 0; i < 32; i++){
            printf("C = %ld \n", C);
            u_int64_t temp = C;

            C += lst1[i] * lst2[i];
            printf("%ld * %ld = %ld \n", lst1[i], lst2[i], lst1[i] * lst2[i]);
            printf("%ld mod p = %ld \n", lst1[i] * lst2[i], (lst1[i] * lst2[i]) % p);
            u_int64_t temp2 = (lst1[i] * lst2[i]) % p;
            printf("%ld + %ld = %ld \n", temp, temp2, temp+temp2);
            C %= p;
            printf("C = %ld \n\n", C);
        }

        // u_int64_t A = p-1;
        // C = A * A;
        // printf("A = %ld \n", A);
        // printf("C = %ld \n", C);

        printf("1073741826 * 1073741826 + 1073741826 = %ld \n", (u_int64_t) (p-1) * (p-1) + (p-1));

    }

    if (TEST7) {
        u_int64_t temp = 64;
        printf("temp = %ld \n", temp);
        temp << 1;
        printf("temp << 1 \n");
        printf("temp = %ld \n", temp);
    
    }

    return 0;
}