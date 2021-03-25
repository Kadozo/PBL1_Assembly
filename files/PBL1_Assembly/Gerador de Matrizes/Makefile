all: gerador

gerador: Gerador_Matriz.o
	gcc Gerador_Matriz.o -o gerador.exe

Gerador_Matriz.o: Gerador_Matriz.c
	gcc Gerador_Matriz.c -o Gerador_Matriz.o -c

clean:
	rm Gerador_Matriz.o
