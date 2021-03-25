all: matrix_mul

matrix_mul: main.o
	gcc main.o -o matrix_mul.exe -masm=intel

main.o: main.c
	gcc main.c -o main.o -masm=intel -c

clean:
	rm main.o
