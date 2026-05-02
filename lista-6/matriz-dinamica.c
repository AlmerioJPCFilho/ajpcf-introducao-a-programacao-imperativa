#include <stdio.h>
#include <stdlib.h>

int **alocarMatriz(int linhas, int colunas);
void lerElementos(int **matriz, int linhas, int colunas);
void printarMatriz(int **matriz, int linhas, int colunas);
void liberarMatriz(int **matriz, int linhas);
int aplicarOperacao(int **matriz, int linhas, int colunas, int (*operacao)(int));
int dobro(int valor);
int quadrado(int valor);
int absoluto(int valor);

int main(){
    int linhas, colunas;
    scanf("%d %d", &linhas, &colunas);
    // um ponteiro para ponteiro para alocar a matriz dinamicamente
    int **matriz = alocarMatriz(linhas, colunas);
    lerElementos(matriz, linhas, colunas);
    // escolher operacao
    int opcao;
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            aplicarOperacao(matriz, linhas, colunas, dobro);
            break;
        case 2:
            aplicarOperacao(matriz, linhas, colunas, quadrado);
            break;
        case 3:
            aplicarOperacao(matriz, linhas, colunas, absoluto);
            break;
    }
    
    printarMatriz(matriz, linhas, colunas);
    liberarMatriz(matriz, linhas);
    return 0;
}

int **alocarMatriz(int linhas, int colunas){
    // aloca um vetor de ponteiros para as linhas, cada uma com tamanho de um ponteiro para inteiro
    int **matriz = (int **)malloc(linhas * sizeof(*matriz));
    if(matriz == NULL){
        printf("Erro ao alocar memoria para a matriz.\n");
        exit(1);
    }
    for(int i = 0; i < linhas; i++){
        // aloca um vetor de inteiro para as colunas, cada uma com tamanho de um inteiro
        matriz[i] = (int *)malloc(colunas * sizeof(**matriz));
        if(matriz[i] == NULL){
            printf("Erro ao alocar memoria para a linha %d da matriz.\n", i);
            // libera as linhas alocadas até o momento
            for(int j = 0; j < i; j++){
                free(matriz[j]);
            }
            free(matriz); // libera a matriz
            exit(1);
        }
    }
    return matriz;
}

void lerElementos(int **matriz, int linhas, int colunas){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            scanf(" %d", &matriz[i][j]);
        }
    }
}

void printarMatriz(int **matriz, int linhas, int colunas){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void liberarMatriz(int **matriz, int linhas){
    // libera cada linha da matriz
    for(int i = 0; i < linhas; i++){
        free(matriz[i]);
    }
    free(matriz);// libera a matriz, ou seja, o vetor de ponteiros para as linhas
}

//recebe a matriz, o tamanho dela e o ponteiro para a funçao desejada
int aplicarOperacao(int **matriz, int linhas, int colunas, int (*operacao)(int)){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            matriz[i][j] = operacao(matriz[i][j]); //aplica a operacao desejada em cada elemento da matriz
        }
    }
}

int dobro(int valor){
    return valor * 2;
}

int quadrado(int valor){
    return valor * valor;
}

int absoluto(int valor){
    return abs(valor);
}