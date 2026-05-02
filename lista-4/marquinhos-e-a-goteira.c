#include <stdio.h>

void leMatriz(long long linhas, long long colunas, char matriz[linhas][colunas]);
void trajetoGota(long long linhas, long long colunas, char matriz[linhas][colunas]);
void printaMatriz(long long linhas, long long colunas, char matriz[linhas][colunas]);

int main(){
    long long linhas, colunas;
    scanf("%lld %lld", &linhas, &colunas);
    char matriz[linhas][colunas];

    leMatriz(linhas, colunas, matriz);
    trajetoGota(linhas, colunas, matriz);
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

void trajetoGota(long long linhas, long long colunas, char matriz[linhas][colunas]){
    int movimentou = 1;//verifica se a gota se movimentou na iteracao passada
    while(movimentou){
        movimentou = 0;
        for(long long i = linhas - 2; i >= 0; i--){
            for(long long j = 0; j < colunas; j++){
                if(matriz[i][j] == 'o'){
                    if(matriz[i + 1][j] == '.'){//tenta descer
                        matriz[i + 1][j] = 'o';
                        movimentou = 1;
                    }else if(matriz[i + 1][j] == '#'){//tenta se mover para os lados
                        //esquerda
                        if(j > 0 && matriz[i][j - 1] == '.'){
                            matriz[i][j - 1] = 'o';
                            movimentou = 1;
                        }
                        //direita
                        if(j + 1 < colunas && matriz[i][j + 1] == '.'){
                            matriz[i][j + 1] = 'o';
                            movimentou = 1;
                        }
                    }
                }
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