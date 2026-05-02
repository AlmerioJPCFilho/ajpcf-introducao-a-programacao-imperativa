#include <stdio.h>

void leMatriz(long long linhas, long long colunas, char matriz[linhas][colunas]);
void modificaMatriz(long long linhas, long long colunas, char matriz[linhas][colunas]);
void printaMatriz(long long linhas, long long colunas, char matriz[linhas][colunas]);

int main(){
    long long linhas, colunas;
    scanf("%lld %lld", &linhas, &colunas);
    char matriz[linhas][colunas];

    leMatriz(linhas, colunas, matriz);
    modificaMatriz(linhas, colunas, matriz);
    printaMatriz(linhas, colunas, matriz);
    return 0;
}

void leMatriz(long long linhas, long long colunas, char matriz[linhas][colunas]){
    char linha[colunas + 1];
    for(long long i = 0; i < linhas; i++){
        scanf("%s", linha);
        for(long long j = 0; j < colunas; j++){
            matriz[i][j] = linha[j];
        }
    }
}

void modificaMatriz(long long linhas, long long colunas, char matriz[linhas][colunas]){
    for(long long i = 0; i < linhas; i++){
        for(long long j = 0; j < colunas; j++){
            if(matriz[i][j] == 'P'){
                if((j - 1) >= 0 && (i - 1) >= 0 && matriz[i - 1][j - 1] != '+' && matriz[i - 1][j - 1] != 'P'){
                    matriz[i - 1][j - 1] = 'x';//cima esquerda
                }
                if((j + 1) < colunas && (i - 1) >= 0 && matriz[i - 1][j + 1] != '+' && matriz[i - 1][j + 1] != 'P'){
                    matriz[i - 1][j + 1] = 'x';//cima direita
                }
                if((j - 1) >= 0 && (i + 1) < linhas && matriz[i + 1][j - 1] != '+' && matriz[i + 1][j - 1] != 'P'){
                    matriz[i + 1][j - 1] = 'x';//baixo esquerda
                }
                if((j + 1) < colunas && (i + 1) < linhas && matriz[i + 1][j + 1] != '+' && matriz[i + 1][j + 1] != 'P'){
                    matriz[i + 1][j + 1] = 'x';//baixo direita
                }
                if((i - 1) >= 0 && matriz[i - 1][j] != 'P'){ matriz[i - 1][j] = '+';}//cima
                if((i + 1) < linhas && matriz[i + 1][j] != 'P'){ matriz[i + 1][j] = '+';}//baixo
                if((j - 1) >= 0 && matriz[i][j - 1] != 'P'){ matriz[i][j - 1] = '+';}//esquerda
                if((j + 1) < colunas && matriz[i][j + 1] != 'P'){ matriz[i][j + 1] = '+';}//direita 
            }
        }
    }
}

void printaMatriz(long long linhas, long long colunas, char matriz[linhas][colunas]){
    for(long long i = 0; i < linhas; i++){
        for(long long j = 0; j < colunas; j++){
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}
