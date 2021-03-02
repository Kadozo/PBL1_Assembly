#include <stdio.h>
#include<stdlib.h>

int** matrix_reader( FILE *fp ){
	int x,y;
	fscanf(fp, "%dx%d", &x,&y);
	int **matrix = (int**) malloc(sizeof(int*)*x);
	for(int i = 0; i<y; i++){
		matrix[i] = (int*) malloc(sizeof(int)*y);
	}
	for(int i=0; i<x; i++){
		for( int j=0; j<y; j++ ){
			fscanf(fp, "%d,", &matrix[ i ][ j ]);
		}
	}
	printf("\n\n\n\n");
	return matrix;
}

int main(void){
	FILE *fp;
	fp = fopen("padrão_matrizes.txt","r");
	int **matriz_a = matrix_reader(fp);
	int **matriz_b = matrix_reader(fp);
	printf("%d",matriz_a[9][5]);
	fclose(fp);
}
