#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void){
	#define LIM 100
	FILE *fp;
	int tam = 0;
	char stam[40];
	printf("\t**GERADOR DE MATRIZ**\n\n");
	printf("Quantidade de elementos por linha na matriz quadrada: ");
	scanf("%s",&stam);
	char name[20] = "MatrizesFonte.txt";
	tam = atoi(stam);
	strncat(stam, name, 20);
	fp = fopen(stam,"w");
	fprintf(fp,"%dx%d\n",tam,tam);
	for(int i=0;i<tam*tam;i++){
		fprintf(fp,"%d,",rand() % LIM);
	}
	fprintf(fp,"\n");
	fprintf(fp,"%dx%d\n",tam,tam);
	for(int i=0;i<tam*tam;i++){
		fprintf(fp,"%d,",rand() % LIM);
	}
	fclose(fp);
	
	return 0;
}
