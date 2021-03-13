#include <stdio.h>
#include <stdlib.h>


int main() {

	int a[2][2] = {{2,2},{2,2}};
	int b[2][2] = {{2,2},{2,2}};
	int c = 0;
	int tam = 2;
	int i = 0, j = 0, k = 0, constante = 0;
	printf("%d\n", c);
	
	__asm__(
		"l1:\n"							// label do inicil do loop 1
		"	cmp %3, %4\n"				// compara i com tam
		"	jge l1end\n"				// verifica se i (%4) é maior ou igual a tam (%3) e pula para o label l1end (loop 1 end) caso verdade
		"l2:\n"							//label do inicio do loop 2
		"	cmp %3, %5\n"				//compara  j com tam
		"	jge l2end\n"				// verifica se j (%5) é maior ou igual a tam (%3) e pula para o label l2end (loop 2 end) caso verdade
		"l3:\n"							//label do inicio do loop 3
		"	cmp %3, %6\n"				// compara k com tam
		"	jge l3end\n"				// verifica se k (%6) é maior ou igual a tam (%3) e pula para o label l3end (loop 3 end) caso verdade
		"	inc %[saida]\n"				// incrementa 1 à saída (c)
		"	inc %6\n"					// incrementa 1 à k
		"	jmp l3\n"					// volta para o início do loop 3
		"l3end:\n"						// label do fim do loop 3
		"	inc %5\n"					// incrementa 1 à j
		"	mov %7, %6\n" 				// zera a variavel k
		"	jmp l2\n"					// salta para o inicio do loop 2
		"l2end:\n"						// label do fim do loop 2
		"	inc %4\n"					//incrementa 1 à i
		"	mov %7, %5\n" 				// zera à variavel j
		"	jmp l1\n"					// salta para o inicio do loop 1
		"l1end:"						// label do final do loop 1
		: [saida] "+r" (c)
		: "r" (a), "r" (b), "r" (tam), "r" (i), "r" (j), "r" (k), "r" (constante)
	);
	printf("%d\n", c);
	return 0;
}
