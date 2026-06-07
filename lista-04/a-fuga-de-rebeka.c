#include <stdio.h>

void leMatriz(long long linhas, long long colunas, char matriz[linhas][colunas], long long origem[2], long long saida[2]);
long long calcularPassos(long long linhas, long long colunas, char matriz[linhas][colunas], long long lOrigem, long long cOrigem, long long lSaida, long long cSaida, long long passosAtual);

int main(){
    long long linhas, colunas;
    scanf("%lldx%lld", &linhas, &colunas);
    char matriz[linhas][colunas];
    
    long long origem[2] = {0, 0};
    long long saida[2] = {0, 0};
    long long passosFinal = 1000000;
    leMatriz(linhas, colunas, matriz, origem, saida);
    passosFinal = calcularPassos(linhas, colunas, matriz, origem[0], origem[1], saida[0], saida[1], 0);
    if(passosFinal < 1000000){
        printf("Apos correr %lld metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", passosFinal);
    }else{
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }
    return 0;
}

void leMatriz(long long linhas, long long colunas, char matriz[linhas][colunas], long long origem[2], long long saida[2]){
    for(long long l = 0; l < linhas; l++){
        for(long long c = 0; c < colunas; c++){
            scanf(" %c", &matriz[l][c]);
            if(matriz[l][c] == 'o'){
                origem[0] = l;
                origem[1] = c;
            }
            if(matriz[l][c] == 'd'){
                saida[0] = l;
                saida[1] = c;
            }
        }
    }
}

long long calcularPassos(long long linhas, long long colunas, char matriz[linhas][colunas], long long lOrigem, long long cOrigem, long long lSaida, long long cSaida, long long passosAtual){
    //chegou na saida
    if(lOrigem == lSaida && cOrigem == cSaida){
        return passosAtual;
    }

    //marca o caminho atual
    char backup = matriz[lOrigem][cOrigem];
    matriz[lOrigem][cOrigem] = 'X';

    long long menorCaminho = 1000000;

    //vetores de direcao para baixo, cima, direita e esquerda
    int direcoesCB[] = {1, -1, 0, 0};
    int direcoesDE[] = {0, 0, 1, -1};

    for(int d = 0; d < 4; d++){
        long long iNovo = lOrigem + direcoesCB[d];
        long long jNovo = cOrigem + direcoesDE[d];

        //verifica se o proximo passo esta dentro da matriz e é valido
        if(iNovo >= 0 && iNovo < linhas && jNovo >= 0 && jNovo < colunas){
            if(matriz[iNovo][jNovo] == '_' || matriz[iNovo][jNovo] == 'd'){
                long long resultado = calcularPassos(linhas, colunas, matriz, iNovo, jNovo, lSaida, cSaida, passosAtual + 1);
            
                if(resultado < menorCaminho){
                    menorCaminho = resultado;
                }
            }
        }
    }
    
    matriz[lOrigem][cOrigem] = backup; //desmarca o caminho atual
    return menorCaminho;
}