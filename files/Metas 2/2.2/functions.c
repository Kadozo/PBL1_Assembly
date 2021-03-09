#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Faz a multiplica��o de duas matrizes, A e B.
	
Par�metros:
** A = primeira matriz da multiplica��o;
** B = segunda matriz da multiplica��o;
tamA[2] = dimens�es da matriz A;
tamB[2] = dimens�es da matriz B.

Retorno:
** C = matriz resultado da multiplica��o entre A e B.
*/
int **multMatriz(int **A, int **B, int tamA[2], int tamB[2]){
	
	// � verificado se as matrizes tem dimens�es com condi��es de multiplica��o
	if(tamA[1] != tamB[0]){
		return NULL;
	}
	else{
		int ** C;
		int i, j, k;
		
		// � instanciado uma matriz com as dimens�es resultado da multiplica��o
		C =(int **)malloc(tamA[0] *sizeof(int*));
		for( i = 0; i<tamA[0]; i++){
			C[i] = (int *) malloc(tamB[1]*sizeof(int));
		}
		//Matriz � zerada para remover qualquer lixo que esteja nela
		for(i = 0; i<tamA[0]; i++){
			for( j = 0; j<tamB[1]; j++){
				C[i][j] = 0;
			}
		}
		
		//l�gica para a multiplica��o das matrizes e preenchimento da terceira matriz
		for(i = 0; i<tamA[0]; i++){
			for(j = 0; j<tamB[1]; j++){
				for(k = 0; k<tamA[1]; k++){
					C[i][j] = C[i][j] + (A[i][k]*B[k][j]);
				}
			}
		}
		return C;
	}
}

/*
	Fun��o para leitura de uma matriz em um arquivo .txt com layout pr�-
definido. O layout do arquivo foi idealizado pelo grupo Jos� Gabriel,
Mateus e Thiago.

Par�metros:
*fp = ponteiro do arquivo que ser� lido, j� aberto e definido como leitura;
*lin = quantidade de linhas da matriz que ser� retornado por refer�ncia � 
quem chamou a fun��o;
*col = quantidade de colunas da matriz que ser� retornado por refer�ncia �
quem chamou a fun��o.

retorno:
matrix = matriz lida no arquivo .txt.
*/
int** matrixReader( FILE *fp, int * lin, int * col){
	int i, j;
	
	// obtem a primeira linha do arquivo com as dimens�es da matriz.
	fscanf(fp, "%dx%d", lin, col); 
	
	//instancia matriz com as dimens�es adquiridas.
	int **matrix = (int**) malloc(sizeof(int*)*(*lin));
	for( i = 0; i<(*col); i++){
		matrix[i] = (int*) malloc(sizeof(int)*(*col));
	}
	
	//l� elemento por elemento e o coloca na matriz.
	for( i=0; i<(*lin); i++){
		for( j=0; j<(*col); j++ ){
			fscanf(fp, "%d,", &matrix[ i ][ j ]);
		}
	}
	//retorna matriz preenchida.
	return matrix;
}

/*
	Faz a escrita de uma matriz em um arquivo .txt com um layout pr�-definido.
O layout do arquivo foi idealizado pelo grupo Jos� Gabriel, Mateus e Thiago.

Par�metros:
** A = matriz que ser� escrita no arquivo;
tam[2] = dimens�es da matriz A.

Retorno:
1 - caso a escrita do arquivo tenha sido efetuada;
0 - caso n�o tenha sido poss�vel abrir o arquivo.
*/
int matrixWrite(int ** A, int tam[2]){
	int i, j;
	
	//Aponta o ponteiro file para o arquivo desejado.
	FILE * file;
	file = fopen("resultado_matriz.txt", "a");
	//caso nao exista o arquivo, este � criado.
	if(file == NULL){
		file = fopen("resultado_matriz.txt", "w");
		//caso a cria��o do arquivo falhe, a fun��o retorna 0.
		if(file == NULL){
			return 0;
		}
	}
	
	// escreve as dimens�es da matriz no arquivo
	fprintf(file,"%dx%d\n",tam[0],tam[1]);
	
	//e logo depois escreve os elementos, separados por v�rgulas
	for(i = 0; i<tam[0]; i++){
		for(j = 0; j<tam[1];j++){
			fprintf(file,"%d,", A[i][j]);
		}
	}
	fprintf(file,"\n");
	fclose(file);
	
	return 1;
}


/*
	Faz a integra��o de diversas fun��es que calculam o produto de duas matrizes que
se encontram em um arquivo (arq).

Par�metros:
*arq = nome do arquivo que cont�m as matrizes que ser�o multiplicadas.

*/
void MatrixCalculator( char * arq){
	int i, j;
	
	//instancia o ponteiro e o aponta para o arquivo cujo nome foi passado como par�metro
	FILE *fp;
	fp = fopen(arq,"r");
	//se o arquivo nao existir no diret�rio da aplica��o, � informado ao usu�rio.
	if(fp == NULL){
		printf("*******ERROR 0001*******\nAquivo nao encontrado\nTente colocar o arquivo no diretorio da aplicacao\n");
		getchar();
	}
	else{
		//as quatro vari�veis s�o para capturar as dimens�es das matrizes que ser�o lidas
		//pela fun��o matrixReader, j� que nao tinha possibilidade de fazer isso pelo retorno
		//da fun��o.
		int * linA, *colA, * linB, *colB;
		linA = (int*) malloc(sizeof(int));
		colA = (int*) malloc(sizeof(int));
		linB = (int*) malloc(sizeof(int));
		colB = (int*) malloc(sizeof(int));
		int **matriz_a = matrixReader(fp,linA, colA);
		int **matriz_b = matrixReader(fp, linB, colB);
		fclose(fp);
		
		//transfere, ent�o as dimensoes para dois vetores para utiliza-los na outra fun��o
		int tamA[] = {*linA,*colA};
		int tamB [] = {*linB,*colB};
		
		// � liberado o espa�o alocado dinamicamente das dimens�es das matrizes.
		free(linA);
		free(linB);
		free(colA);
		free(colB);
		
		// aqui � chamada  a fun��o que realiza a multiplica��o das duas matrizes lidas no arquivo.
		int ** matriz_c = multMatriz(matriz_a,matriz_b, tamA, tamB);
		
		//caso as matrizes n�o possam ser multiplicadas
		if(matriz_c == NULL){
			printf("*******ERROR 0002*******\n\n");
			printf("Nao foi possivel realizar a multiplicacao. . .");
			getchar();
		}
		// se as matrizes forem multiplicadas o resultado � mostrado
		else{
			int tamC[] = {tamA[0], tamB[1]};
			printf("Matrizes multiplicadas.\nResultado:\n");
			for(i=0; i<tamC[0]; i++){
				for(j=0; j<tamC[1]; j++){
					printf("%d ", matriz_c[i][j]);
				}
				printf("\n");
			}
			printf("\nPressione enter para salvar a matriz resultado...");
			getchar();
			
			// e ent�o, a matrizes resultado � introduzida no j� existente ( ou n�o)
			// arquivo de matrizes resultado.
			int verify = matrixWrite(matriz_c, tamC);
			
			// � feito uma verifica��o se o arquivo foi mesmo escrito e avisado ao usu�rio.
			if(verify  == 0){
				printf("Erro ao abrir o arquivo!\n");
				printf("*******ERROR 0003*******\n");
				getchar();
			}
			else{
				printf("\nMatriz salva com sucesso!\n\n");
				printf("Procure por matriz_resultado.txt no diret�rio da aplicacao. . . .");
				getchar();
			}
			// aqui � liberado o espa�o das matrizes que foram alocadas.
			free(matriz_a);
			free(matriz_b);
			free(matriz_c);
		}
	}
}
