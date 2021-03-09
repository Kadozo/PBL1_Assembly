all: mltp_matriz

mltp_matriz: main.o functions.o
	gcc -o mltp_matriz main.o functions.o

main.o: main.c
	gcc -o main.o main.c -c

functions.o: functions.c
	gcc -o functions.o functions.c -c	

clean:
	rm main.o functions.o
