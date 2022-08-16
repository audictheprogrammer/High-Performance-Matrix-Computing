#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Basic operations
u_int64_t** create_matrix(int size);
u_int64_t** create_matrix_mod(int size, u_int32_t mod);
void delete_matrix(u_int64_t*** mat, int size);
u_int64_t** transpose_matrix(u_int64_t** mat, int size);
void print_matrix(u_int64_t** mat, int size);
void write_matrix(u_int64_t** mat, int size, char* filename);
u_int64_t** read_matrix(char* filename, int* size);
int equals_matrix(u_int64_t** A, u_int64_t** B, int size);
int equals_matrix_file(char* filename1, char* filename2);


#endif