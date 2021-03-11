#include <stdio.h>
#include <stdlib.h>

 int mult( int a, int b);


 int main() {
	 int x, y;
	scanf("%d %d %d", &x, &y);
	printf("resultado = %d\n", soma(x, y));
}

 int soma( int a,  int b) {
	 int c;
	__asm__(
		"imul %1, %2"
		:[saida] "=r" (c)
		: "r" (a),"r" (b)
	);
	return c;
}
