#include <stdio.h>
#include <stdlib.h>



int main(){
	int c = 0, a = 1000, i = 0;
	int aux1 = 1, aux2 = 2;
	
	/*
	__asm__(
		"l1:\n"
		"cmp %1, %2\n"
		"jge l1end\n"
		"mov %3, %0\n"
		"jmp l1end2\n"
		"l1end:\n"
		"mov %4, %0\n"
		"l1end2:\n"
		: [saida] "+r" (c)
		: "r" (a), "r" (i), "r" (aux1), "r" (aux2)
	); 
	*/
	
	
	// /*
	__asm__(
		"l1:\n"
		"cmp %1, %2\n"
		"jge l1end\n"
		"inc %[saida]\n"
		"inc %2\n"
		"jmp l1\n"
		"l1end:\n"
		: [saida] "+r" (c)
		: "r" (a), "r" (i), "r" (aux1), "r" (aux2)
	);
	
	//*/
	printf("%d", c);
}
