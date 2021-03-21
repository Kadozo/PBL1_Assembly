#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **multMatriz(int **A, int **B, int tamA[2], int tamB[2]);
int **multMatrizASM(int **A, int **B, int tamA[2], int tamB[2]);
int** matrixReader( FILE *fp, int * lin, int * col);
int matrixWrite(int ** A, int tam[2]);
void MatrixCalculator( char * arq,int flag);


int main(int argc, char *argv[]) {
	MatrixCalculator("padrão_matrizes.txt",0);
}



/*
	Faz a multiplicação de duas matrizes, A e B.
	
Parâmetros:
** A = primeira matriz da multiplicação;
** B = segunda matriz da multiplicação;
tamA[2] = dimensões da matriz A;
tamB[2] = dimensões da matriz B.

Retorno:
** C = matriz resultado da multiplicação entre A e B.
*/
int **multMatriz(int **A, int **B, int tamA[2], int tamB[2]){
	
	// É verificado se as matrizes tem dimensões com condições de multiplicação
	if(tamA[1] != tamB[0]){
		return NULL;
	}
	else{
		int ** C;
		int i, j, k;
		
		// É instanciado uma matriz com as dimensões resultado da multiplicação
		C =(int **)malloc(tamA[0] *sizeof(int*));
		for( i = 0; i<tamA[0]; i++){
			C[i] = (int *) malloc(tamB[1]*sizeof(int));
		}
		//Matriz é zerada para remover qualquer lixo que esteja nela
		for(i = 0; i<tamA[0]; i++){
			for( j = 0; j<tamB[1]; j++){
				C[i][j] = 0;
			}
		}
		
		//lógica para a multiplicação das matrizes e preenchimento da terceira matriz
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

int **multMatrizASM(int **A, int **B, int tamA[2], int tamB[2]){
	
	// É verificado se as matrizes tem dimensões com condições de multiplicação
	if(tamA[1] != tamB[0]){
		return NULL;
	}
	else{
		int ** C;
		int i, j, k;
		
		// É instanciado uma matriz com as dimensões resultado da multiplicação
		C =(int **)malloc(tamA[0] *sizeof(int*));
		for( i = 0; i<tamA[0]; i++){
			C[i] = (int *) malloc(tamB[1]*sizeof(int));
		}
		//Matriz é zerada para remover qualquer lixo que esteja nela
		for(i = 0; i<tamA[0]; i++){
			for( j = 0; j<tamB[1]; j++){
				C[i][j] = 0;
			}
		}
		
		//lógica para a multiplicação das matrizes e preenchimento da terceira matriz em assembly
	__asm__(
		"push rbp\n" //inicia uma pilha
		"mov rbp,rsp\n" //pega a referencia do topo da pilha
		"mov DWORD PTR[rbp-4],0\n" //i
		"mov DWORD PTR[rbp-8],0\n" //j
		"mov DWORD PTR[rbp-12],0\n" //k
        "LOOP1:\n" //rótulo do loop1
            "cmp [rbp-4], r8d\n"    //compara i com tam
            "jge ENDLOOP1\n" //se i>= tam salta para o final de ENDLOOP1
            "LOOP2:\n" //rótulo do loop2
                "cmp [rbp-8], r8d\n"    //compara j com tam
                "jge ENDLOOP2\n" //se j>= tam salta para o ENDLOOP2
                "LOOP3:\n" //rótulo do loop3 
                    "cmp [rbp-12], r8d\n"    //compara k com tam
                    "jge ENDLOOP3\n" //se k >= tam salta para o ENDLOOP3
					
					"mov ebx,[rbp-12]\n"  //ebx recebe k           
					"mov r10d,[rcx+8*rbx]\n" //r10d é um endereço de B[k][]
					
                    
                    "mov ebx,[rbp-4]\n" //ebx recebe i
                    "mov r9d,[rdx+8*rbx]\n"//r9d é um endereço de A[i][]
                    "mov r11d,[rax+8*rbx]\n"//r11d é um endereço de C[i][]
                    
					"mov ebx,[rbp-8]\n"//ebx recebe j
                    "mov r9d,[r9d+4*ebx]\n"//r9d recebe o valor de A[i][j]
                    "mov r10d,[r10d+4*ebx]\n" //recebe valor B[k][j]
                    
                    "imul r10d,r9d\n" //r10d = r10d*r9d    //r10d = A[i][j]*B[k][j]
                    "add [r11d+4*ebx],r10d\n" // C[i][j] = C[i][j] + r10d
                    
                    
					"inc DWORD PTR[rbp-12]\n"        //incremente k
                    "jmp LOOP3\n" //Salta para o rótulo LOOP3
                "ENDLOOP3:\n" //Rótulo ENDLOOP3
                "inc DWORD PTR[rbp-8]\n"            //incrementa j
                "mov DWORD PTR[rbp-12], 0\n"        //zera k
                "jmp LOOP2\n" //Salta para o rótulo LOOP2
            "ENDLOOP2:\n" //Rótulo ENDLOOP2
            "inc DWORD PTR[rbp-4]\n"                // incrementa i
            "mov DWORD PTR[rbp-8], 0\n"                //zera j
            "jmp LOOP1\n" //Salta para o rótulo LOOP1
        "ENDLOOP1:\n" //Rótulo ENDLOOP1
        "pop rbp\n"
        : [saida] "+r" (C)
        : "r" (A), "r" (B), "r" (tamA[0])
	);
		return C;
	}
}






/*
	Função para leitura de uma matriz em um arquivo .txt com layout pré-
definido. O layout do arquivo foi idealizado pelo grupo José Gabriel,
Mateus e Thiago.

Parâmetros:
*fp = ponteiro do arquivo que será lido, já aberto e definido como leitura;
*lin = quantidade de linhas da matriz que será retornado por referência à 
quem chamou a função;
*col = quantidade de colunas da matriz que será retornado por referência à
quem chamou a função.

retorno:
matrix = matriz lida no arquivo .txt.
*/
int** matrixReader( FILE *fp, int * lin, int * col){
	int i, j;
	
	// obtem a primeira linha do arquivo com as dimensões da matriz.
	fscanf(fp, "%dx%d", lin, col); 
	
	//instancia matriz com as dimensões adquiridas.
	int **matrix = (int**) malloc(sizeof(int*)*(*lin));
	for( i = 0; i<(*col); i++){
		matrix[i] = (int*) malloc(sizeof(int)*(*col));
	}
	
	//lê elemento por elemento e o coloca na matriz.
	for( i=0; i<(*lin); i++){
		for( j=0; j<(*col); j++ ){
			fscanf(fp, "%d,", &matrix[ i ][ j ]);
		}
	}
	//retorna matriz preenchida.
	return matrix;
}

/*
	Faz a escrita de uma matriz em um arquivo .txt com um layout pré-definido.
O layout do arquivo foi idealizado pelo grupo José Gabriel, Mateus e Thiago.

Parâmetros:
** A = matriz que será escrita no arquivo;
tam[2] = dimensões da matriz A.

Retorno:
1 - caso a escrita do arquivo tenha sido efetuada;
0 - caso não tenha sido possível abrir o arquivo.
*/
int matrixWrite(int ** A, int tam[2]){
	int i, j;
	
	//Aponta o ponteiro file para o arquivo desejado.
	FILE * file;
	file = fopen("resultado_matriz.txt", "a");
	//caso nao exista o arquivo, este é criado.
	if(file == NULL){
		file = fopen("resultado_matriz.txt", "w");
		//caso a criação do arquivo falhe, a função retorna 0.
		if(file == NULL){
			return 0;
		}
	}
	
	// escreve as dimensões da matriz no arquivo
	fprintf(file,"%dx%d\n",tam[0],tam[1]);
	
	//e logo depois escreve os elementos, separados por vírgulas
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
	Faz a integração de diversas funções que calculam o produto de duas matrizes que
se encontram em um arquivo (arq).

Parâmetros:
*arq = nome do arquivo que contém as matrizes que serão multiplicadas.

*/
void MatrixCalculator( char * arq,int flag){
	int i, j;
	
	//instancia o ponteiro e o aponta para o arquivo cujo nome foi passado como parâmetro
	FILE *fp;
	fp = fopen(arq,"r");
	//se o arquivo nao existir no diretório da aplicação, é informado ao usuário.
	if(fp == NULL){
		printf("*******ERROR 0001*******\nAquivo nao encontrado\nTente colocar o arquivo no diretorio da aplicacao\n");
		getchar();
	}
	else{
		//as quatro variáveis são para capturar as dimensões das matrizes que serão lidas
		//pela função matrixReader, já que nao tinha possibilidade de fazer isso pelo retorno
		//da função.
		int * linA, *colA, * linB, *colB;
		linA = (int*) malloc(sizeof(int));
		colA = (int*) malloc(sizeof(int));
		linB = (int*) malloc(sizeof(int));
		colB = (int*) malloc(sizeof(int));
		int **matriz_a = matrixReader(fp,linA, colA);
		int **matriz_b = matrixReader(fp, linB, colB);
		fclose(fp);
		
		//transfere, então as dimensoes para dois vetores para utiliza-los na outra função
		int tamA[] = {*linA,*colA};
		int tamB [] = {*linB,*colB};
		
		// é liberado o espaço alocado dinamicamente das dimensões das matrizes.
		free(linA);
		free(linB);
		free(colA);
		free(colB);
		int ** matriz_c;
		// aqui é chamada  a função que realiza a multiplicação das duas matrizes lidas no arquivo.
		if(flag){
			matriz_c = multMatriz(matriz_a,matriz_b, tamA, tamB);
		}
		else{
			matriz_c = multMatrizASM(matriz_a,matriz_b, tamA, tamB);
		}
		
		//caso as matrizes não possam ser multiplicadas
		if(matriz_c == NULL){
			printf("*******ERROR 0002*******\n\n");
			printf("Nao foi possivel realizar a multiplicacao. . .");
			getchar();
		}
		// se as matrizes forem multiplicadas o resultado é mostrado
		else{
			int tamC[] = {tamA[0], tamB[1]};
			printf("Matrizes multiplicadas.\nResultado:\n");
			for(i=0; i<tamC[0]; i++){
				for(j=0; j<tamC[1]; j++){
					printf("%d ", matriz_c[i][j]);
				}
				printf("\n");
			}
			
			// e então, a matrizes resultado é introduzida no já existente ( ou não)
			// arquivo de matrizes resultado.
			int verify = matrixWrite(matriz_c, tamC);
			// aqui é liberado o espaço das matrizes que foram alocadas.
			free(matriz_a);
			free(matriz_b);
			free(matriz_c);
		}
	}
}
