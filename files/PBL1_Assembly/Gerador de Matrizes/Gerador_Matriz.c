/*
 *
 * Componente Curricular: TEC-499 MI- Sistemas Digitais, Turma TP01
 * Autor: José Gabriel Gomes dos Santos Oliveira, Mateus Fernandes Santos e Thiago Cardozo de Jesus
 * Data: 19/03/2021
 *
 * Declaro que este código foi elaborado por mim de forma individual e
 * não contém nenhum trecho de código de outro colega ou de outro autor, 
 * tais como provindos de livros e apostilas, e páginas ou documentos 
 * eletrônicos da Internet. Qualquer trecho de código de outra autoria que
 * uma citação para o  não a minha está destacado com  autor e a fonte do
 * código, e estou ciente que estes trechos não serão considerados para fins
 * de avaliação. Alguns trechos do código podem coincidir com de outros
 * colegas pois estes foram discutidos em sessões tutorias.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void){
	#define LIM 100
	FILE *fp;
	int tam = 0;
	int i;
	
	printf("\t**GERADOR DE MATRIZ**\n\n");
	printf("Quantidade de elementos por linha na matriz quadrada: ");
	scanf("%d",&tam);
	
	fp = fopen("MatrizesFonte.txt","w");
	//coloca o tamanho da primeira matriz no arquivo
	fprintf(fp,"%dx%d\n",tam,tam);
	//gera a primeira matriz
	for(i =0;i<tam*tam;i++){
		fprintf(fp,"%d,",rand() % LIM);
	}
	fprintf(fp,"\n");
	//coloca o tamanho da segunda matriz no arquivo
	fprintf(fp,"%dx%d\n",tam,tam);
	//gera a segunda matriz
	for(i=0;i<tam*tam;i++){
		fprintf(fp,"%d,",rand() % LIM);
	}
	
	fclose(fp);
	
	return 0;
}
