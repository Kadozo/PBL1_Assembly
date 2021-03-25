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
#include <time.h>

int **multMatriz(int **A, int **B, int tamA[2], int tamB[2]);
int **multMatrizASM(int **A, int **B, int tamA[2], int tamB[2]);
int** matrixReader( FILE *fp, int * lin, int * col);
int matrixWrite(int ** A, int tam[2]);
void MatrixCalculator( char * arq,int flag);


int main() {
	int x;
	printf("Escolha como deseja multiplicar.\n[1] - Multiplicacao em C\t[0] - Multiplicacao em Assembly\n");
	scanf("%d", &x);
	MatrixCalculator("MatrizesFonte.txt",x);
}
/*
	Faz a multiplicacao de duas matrizes, A e B.
	
Parametros:
** A = primeira matriz da multiplicacao;
** B = segunda matriz da multiplicacao;
tamA[2] = dimensoes da matriz A;
tamB[2] = dimensoes da matriz B.

Retorno:
** C = matriz resultado da multiplicacao entre A e B.
*/
int **multMatriz(int **A, int **B, int tamA[2], int tamB[2]){
	
	// E verificado se as matrizes tem dimensoes com condicoes de multiplicacao
	if(tamA[1] != tamB[0]){
		return NULL;
	}
	else{
		int ** C;
		int i, j, k;
		
		// E instanciado uma matriz com as dimensoes resultado da multiplicacao
		C =(int **)malloc(tamA[0] *sizeof(int*));
		for( i = 0; i<tamA[0]; i++){
			C[i] = (int *) malloc(tamB[1]*sizeof(int));
		}
		//Matriz e zerada para remover qualquer lixo que esteja nela
		for(i = 0; i<tamA[0]; i++){
			for( j = 0; j<tamB[1]; j++){
				C[i][j] = 0;
			}
		}
		//captura o tempo do clock do processador no inicio da multiplicacao
		clock_t begin = clock();
		//logica para a multiplicacao das matrizes e preenchimento da terceira matriz
		for(i = 0; i<tamA[0]; i++){
			for(j = 0; j<tamB[1]; j++){
				for(k = 0; k<tamA[1]; k++){
					C[i][j] = C[i][j] + (A[i][k]*B[k][j]);
				}
			}
		}
		//captura o tempo do clock do processador no fim da multiplicacao
		clock_t end = clock();
		//divide o tempo do processador usado durante a multiplicacao pelo clock por segundo do processador
		double tempo = (double) (end - begin)/CLOCKS_PER_SEC;
		//grava o dado adquirido em um arquivo
		FILE * fp = fopen("tempo.txt", "a");
		fprintf(fp, "tempo em C: %.9lf\n", tempo);
		fclose(fp);
		return C;
	}
}
/*
	Faz a multiplicacao de duas matrizes, A e B.
	
Parametros:
** A = primeira matriz da multiplicacao;
** B = segunda matriz da multiplicaÃ§Ã£o;
tamA[2] = dimensoes da matriz A;
tamB[2] = dimensoes da matriz B.

Retorno:
** C = matriz resultado da multiplicacao entre A e B.
*/
int **multMatrizASM(int **A, int **B, int tamA[2], int tamB[2]){
	
	// E verificado se as matrizes tem dimensoes com condicoes de multiplicacao
	if(tamA[1] != tamB[0]){
		return NULL;
	}
	else{
		int ** C;
		int i, j, k;
		
		// E instanciado uma matriz com as dimensoes resultado da multiplicacao
		C =(int **)malloc(tamA[0] *sizeof(int*));
		for( i = 0; i<tamA[0]; i++){
			C[i] = (int *) malloc(tamB[1]*sizeof(int));
		}
		//Matriz e zerada para remover qualquer lixo que esteja nela
		for(i = 0; i<tamA[0]; i++){
			for( j = 0; j<tamB[1]; j++){
				C[i][j] = 0;
			}
		}
		//captura o tempo do clock do processador no inicio da multiplicacao
		clock_t begin = clock();
		//logica para a multiplicacao das matrizes e preenchimento da terceira matriz em assembly
		__asm__(
		"push rbp\n" //inicia uma pilha
		"mov rbp,rsp\n" //pega a referencia do topo da pilha
		"mov DWORD PTR[rbp-4],0\n" //i
		"mov DWORD PTR[rbp-8],0\n" //j
		"mov DWORD PTR[rbp-12],0\n" //k
       	"LOOP1:\n" //rotulo do loop1
        	"cmp [rbp-4], esi\n"    //compara i com tam
        	"jge ENDLOOP1\n" //se i>= tam salta para o final de ENDLOOP1
        	"LOOP2:\n" //rotulo do loop2
            	"cmp [rbp-8], esi\n"    //compara j com tam
        		"jge ENDLOOP2\n" //se j>= tam salta para o ENDLOOP2
        		"LOOP3:\n" //rotulo do loop3 
                 	"cmp [rbp-12], esi\n"    //compara k com tam
         			"jge ENDLOOP3\n" //se k >= tam salta para o ENDLOOP3
				
					"mov ebx,[rbp-4]\n" //ebx recebe i
            		"mov r9d,[rdx+8*rbx]\n"//r9d e um endereco de A[i][]
           			"mov r11d,[rax+8*rbx]\n"//r11d e um endereco de C[i][]
               			 
            		"mov ebx,[rbp-12]\n"  //ebx recebe k           
					"mov r10d,[rcx+8*rbx]\n" //r10d e um endereco de B[k][]
					"mov r9d,[r9d+4*ebx]\n"//r9d recebe o valor de A[i][k]
                   			
					"mov ebx,[rbp-8]\n"//ebx recebe j
               		"mov r10d,[r10d+4*ebx]\n" //recebe valor B[k][j]
                
					"imul r10d,r9d\n" //r10d = r10d*r9d    //r10d = A[i][k]*B[k][j]
					"add [r11d+4*ebx],r10d\n" // C[i][j] = C[i][j] + r10d
                    
					"inc DWORD PTR[rbp-12]\n"        //incremente k
					"jmp LOOP3\n" //Salta para o rotulo LOOP3
		 		"ENDLOOP3:\n" //Rotulo ENDLOOP3
            	"inc DWORD PTR[rbp-8]\n"            //incrementa j
            	"mov DWORD PTR[rbp-12], 0\n"        //zera k
        		"jmp LOOP2\n" //Salta para o rotulo LOOP2
    		"ENDLOOP2:\n" //Rotulo ENDLOOP2
        	"inc DWORD PTR[rbp-4]\n"                // incrementa i
    		"mov DWORD PTR[rbp-8], 0\n"                //zera j
    		"jmp LOOP1\n" //Salta para o rotulo LOOP1
		"ENDLOOP1:\n" //Rotulo ENDLOOP1
        "pop rbp\n"
        : [saida] "+r" (C) //C é armazenado em rax
        : "r" (A), "r" (B), "r" (tamA[0]) // o A é armazenado em rdx, o B em rcx e o tamA[0] em esi
		);
		//captura o tempo do clock do processador no fim da multiplicacao
		clock_t end = clock();
		//divide o tempo do processador usado durante a multiplicacao pelo clock por segundo do processador
		double tempo = (double) (end - begin)/CLOCKS_PER_SEC;
		//grava o dado adquirido em um arquivo
		FILE * fp = fopen("tempo.txt", "a");
		fprintf(fp, "tempo em ASM: %.9lf\n", tempo);
		fclose(fp);
		return C;
	}
}






/*
	Funcao para leitura de uma matriz em um arquivo .txt com layout pre-
definido. O layout do arquivo foi idealizado pelo grupo JosÃ© Gabriel,
Mateus Fernandes e Thiago Cardozo.

Parametros:
*fp = ponteiro do arquivo que sera lido, ja aberto e definido como leitura;
*lin = quantidade de linhas da matriz que sera retornado por referencia a  
quem chamou a funcao;
*col = quantidade de colunas da matriz que sera retornado por referencia a 
quem chamou a funcao.

retorno:
matrix = matriz lida no arquivo .txt.
*/
int** matrixReader( FILE *fp, int * lin, int * col){
	int i, j;
	
	// obtem a primeira linha do arquivo com as dimensoes da matriz.
	fscanf(fp, "%dx%d", lin, col); 
	
	//instancia matriz com as dimensoes adquiridas.
	int **matrix = (int**) malloc(sizeof(int*)*(*lin));
	for( i = 0; i<(*col); i++){
		matrix[i] = (int*) malloc(sizeof(int)*(*col));
	}
	
	//le elemento por elemento e o coloca na matriz.
	for( i=0; i<(*lin); i++){
		for( j=0; j<(*col); j++ ){
			fscanf(fp, "%d,", &matrix[ i ][ j ]);
		}
	}
	//retorna matriz preenchida.
	return matrix;
}

/*
	Faz a escrita de uma matriz em um arquivo .txt com um layout pre-definido.
O layout do arquivo foi idealizado pelo grupo Jose Gabriel, Mateus Fernandes e Thiago Cardozo.

Parametros:
** A = matriz que sere escrita no arquivo;
tam[2] = dimensÃµes da matriz A.

Retorno:
1 - caso a escrita do arquivo tenha sido efetuada;
0 - caso nao tenha sido possivel abrir o arquivo.
*/
int matrixWrite(int ** A, int tam[2]){
	int i, j;
	
	//Aponta o ponteiro file para o arquivo desejado.
	FILE * file;
	file = fopen("resultado_matriz.txt", "a");
	//caso nao exista o arquivo, este e criado.
	if(file == NULL){
		file = fopen("resultado_matriz.txt", "w");
		//caso a criacao do arquivo falhe, a funcao retorna 0.
		if(file == NULL){
			return 0;
		}
	}
	
	// escreve as dimensoes da matriz no arquivo
	fprintf(file,"%dx%d\n",tam[0],tam[1]);
	
	//e logo depois escreve os elementos, separados por virgulas
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
	Faz a integracao de diversas funcoes que calculam o produto de duas matrizes que
se encontram em um arquivo (arq).

Parametros:
*arq = nome do arquivo que contem as matrizes que serao multiplicadas.

*/
void MatrixCalculator( char * arq,int flag){
	int i, j;
	
	//instancia o ponteiro e o aponta para o arquivo cujo nome foi passado como parametro
	FILE *fp;
	fp = fopen(arq,"r");
	//se o arquivo nao existir no diretorio da aplicacao, e informado ao usuario.
	if(fp == NULL){
		printf("*******ERROR 0001*******\nAquivo nao encontrado\nTente colocar o arquivo no diretorio da aplicacao\n");
		getchar();
	}
	else{
		//as quatro variaveis sao para capturar as dimensoes das matrizes que serao lidas
		//pela funcao matrixReader, ja que nao tinha possibilidade de fazer isso pelo retorno
		//da funcao.
		int * linA, *colA, * linB, *colB;
		linA = (int*) malloc(sizeof(int));
		colA = (int*) malloc(sizeof(int));
		linB = (int*) malloc(sizeof(int));
		colB = (int*) malloc(sizeof(int));
		int **matriz_a = matrixReader(fp,linA, colA);
		int **matriz_b = matrixReader(fp, linB, colB);
		fclose(fp);
		
		//transfere, entao as dimensoes para dois vetores para utiliza-los na outra funcao
		int tamA[] = {*linA,*colA};
		int tamB [] = {*linB,*colB};
		
		// E liberado o espaco alocado dinamicamente das dimensoes das matrizes.
		free(linA);
		free(linB);
		free(colA);
		free(colB);
		int ** matriz_c;
		// aqui e chamada  a funcaoo que realiza a multiplicacao das duas matrizes lidas no arquivo.
		if(flag){
			matriz_c = multMatriz(matriz_a,matriz_b, tamA, tamB);
		}
		else{
			matriz_c = multMatrizASM(matriz_a,matriz_b, tamA, tamB);
		}
		
		//caso as matrizes nao possam ser multiplicadas
		if(matriz_c == NULL){
			printf("*******ERROR 0002*******\n\n");
			printf("Nao foi possivel realizar a multiplicacao. . .");
			getchar();
		}
		// se as matrizes forem multiplicadas
		else{
			int tamC[] = {tamA[0], tamB[1]};
			// e entao, a matrizes resultado e introduzida no ja existente ( ou nao)
			// arquivo de matrizes resultado.
			matrixWrite(matriz_c, tamC);
			
			// aqui e liberado o espaco das matrizes que foram alocadas.
			free(matriz_a);
			free(matriz_b);
			free(matriz_c);
		}
	}
}
