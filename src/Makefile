# Targets
all: main_test main_flint main main_debug

# Headers
matrix.o: matrix.c
	gcc -c matrix.c
matrix_mul.o: matrix_mul.c
	gcc -c matrix_mul.c
	
# Mains
main_test: main_test.c matrix.o matrix_mul.o
	gcc -o main_test main_test.c matrix.o matrix_mul.o
main_flint: main_flint.c
	gcc -o main_flint main_flint.c -lflint -lgmp
main: main.c matrix.o matrix_mul.o
	gcc -o main main.c matrix.o matrix_mul.o
main_debug: main_debug.c matrix.o matrix_mul.o
	gcc -o main_debug main_debug.c matrix.o matrix_mul.o

clean:
	rm *.o
	rm -rf main_test main_flint main