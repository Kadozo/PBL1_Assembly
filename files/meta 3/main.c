#include <stdio.h>
#include <stdlib.h>

 int soma( int a, int b, int c);


 int main() {
	 int x, y, z;
	scanf("%d %d %d", &x, &y, &z);
	printf("resultado = %d\n", soma(x, y, z));
}

 int soma( int a,  int b, int c) {
	 int d;
	__asm__(
		"imul %1, %2"
		:[saida] "=r" (d)
		: "r" (a),"r" (b), "r" (c)
	);
	return d;
}
