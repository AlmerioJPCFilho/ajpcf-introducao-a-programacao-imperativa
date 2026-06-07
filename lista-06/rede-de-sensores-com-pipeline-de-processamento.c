#include <stdio.h>
#include <stdlib.h>

// funcoes de matriz
int **alocarMatriz(int linhas, int colunas);
void lerMatriz(int **matriz, int linhas, int colunas);
void printarMatriz(int **matriz, int linhas, int colunas);
void sensorCritico(int **matriz, int linhas, int colunas);
void liberarMatriz(int **matriz, int linhas);

// funcoes de filtro
int calibracao(int valor);
int saturacao(int valor);
int amplificador(int valor);

// funcoes de aplicacao
void modificar(int **matriz, int linhas, int colunas, int (**pipeline)(int), int qtdFiltros);

int main(){
    int linhas, colunas;
    scanf("%d %d", &linhas, &colunas);
    int **matriz = alocarMatriz(linhas, colunas);
    lerMatriz(matriz, linhas, colunas);

    // array de ponteiros para a pipeline
    int (*todosFiltros[4])(int) = {NULL, calibracao, saturacao, amplificador}; // NULL para as opcoes comecarem em 1

    int entrada;
    do{
        scanf("%d", &entrada);
        int qtdFiltros;
        switch(entrada){
            case 1: {
                qtdFiltros = 1;
                // aloca um array de ponteiros para as funcoes, cada uma com tamanho de um ponteiro para funcao que recebe int e retorna int
                int (**pipeline)(int) = (int (**)(int))malloc(qtdFiltros * sizeof(int (*)(int)));
                if(pipeline == NULL){
                    printf("Erro ao alocar pipeline\n");
                    exit(1);
                }
                pipeline[0] = calibracao;
                modificar(matriz, linhas, colunas, pipeline, qtdFiltros);
                free(pipeline);
                break;
            }
            case 2: {
                qtdFiltros = 1;
                // aloca um array de ponteiros para as funcoes, cada uma com tamanho de um ponteiro para funcao que recebe int e retorna int
                int (**pipeline)(int) = (int (**)(int))malloc(qtdFiltros * sizeof(int (*)(int)));
                if(pipeline == NULL){
                    printf("Erro ao alocar pipeline\n");
                    exit(1);
                }
                pipeline[0] = saturacao;
                modificar(matriz, linhas, colunas, pipeline, qtdFiltros);
                free(pipeline);
                break;
            }
            case 3: {
                qtdFiltros = 1;
                // aloca um array de ponteiros para as funcoes, cada uma com tamanho de um ponteiro para funcao que recebe int e retorna int
                int (**pipeline)(int) = (int (**)(int))malloc(qtdFiltros * sizeof(int (*)(int)));
                if(pipeline == NULL){
                    printf("Erro ao alocar pipeline\n");
                    exit(1);
                }
                pipeline[0] = amplificador;
                modificar(matriz, linhas, colunas, pipeline, qtdFiltros);
                free(pipeline);
                break;
            }
            case 4: {
                scanf("%d", &qtdFiltros);
                // aloca um array de ponteiros para as funcoes, cada uma com tamanho de um ponteiro para funcao que recebe int e retorna int
                int (**pipeline)(int) = (int (**)(int))malloc(qtdFiltros * sizeof(int (*)(int)));
                if(pipeline == NULL){
                    printf("Erro ao alocar pipeline\n");
                    exit(1);
                }
                for(int i = 0; i < qtdFiltros; i++){
                    int filtro;
                    scanf("%d", &filtro);
                    pipeline[i] = todosFiltros[filtro];
                }
                modificar(matriz, linhas, colunas, pipeline, qtdFiltros);
                free(pipeline);
                break;
            }
        }
    }while(entrada != 0);

    
    printarMatriz(matriz, linhas, colunas);
    sensorCritico(matriz, linhas, colunas);
    liberarMatriz(matriz, linhas);
    return 0;
}

// funcoes de matriz
int **alocarMatriz(int linhas, int colunas){
    int **matriz = (int **)malloc(linhas * sizeof(*matriz));
    if(matriz == NULL){
        printf("Erro ao alocar a matriz\n");
        exit(1);
    }
    for(int i = 0; i < linhas; i++){
        matriz[i] = (int *)malloc(colunas * sizeof(**matriz));
        if(matriz[i] == NULL){
            printf("Erro ao alocar linha %d\n", i);
            for(int j = 0; j < i; j++){
                free(matriz[j]);
            }
            free(matriz);
            exit(1);
        }
    }
    return matriz;
}

void lerMatriz(int **matriz, int linhas, int colunas){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            scanf("%d", &matriz[i][j]);
        }
    }
}

void printarMatriz(int **matriz, int linhas, int colunas){
    printf("Matriz processada:\n");
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void sensorCritico(int **matriz, int linhas, int colunas){
    int maior = -1, iMaior = -1, jMaior = -1;
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            if(matriz[i][j] > maior){
                maior = matriz[i][j];
                iMaior = i;
                jMaior = j;
            }
        }
    }
    printf("Sensor critico: %d\n", maior);
    printf("Posicao: (%d,%d)\n", iMaior, jMaior);
}

void liberarMatriz(int **matriz, int linhas){
    for(int i = 0; i < linhas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

// funcoes de filtro
int calibracao(int valor){
    return valor + 5;
}

int saturacao(int valor){
    if(valor > 80){
        return 80;
    }
    return valor;
}

int amplificador(int valor){
    return valor * 2;
}

// funcoes de aplicacao
void modificar(int **matriz, int linhas, int colunas, int (**pipeline)(int), int qtdFiltros){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            for(int k = 0; k < qtdFiltros; k++){
                matriz[i][j] = pipeline[k](matriz[i][j]); //para cada elemento da matriz, aplica cada filtro da pipeline em sequencia
            }
        }
    }
}