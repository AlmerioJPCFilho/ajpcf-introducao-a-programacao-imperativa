#include <stdio.h>

void movimentacao(int matriz[4][4]);
void maisVisitada(int matriz[4][4]);

int main(){
    int matriz[4][4] = {0};
    movimentacao(matriz);
    maisVisitada(matriz);
    return 0;
}

void movimentacao(int matriz[4][4]){
    int posicao[2] = {0, 3};//posicao inicial

    char movimentos[21] = {0};
    for(int i = 0; i < 20; i++){
        scanf(" %c", &movimentos[i]);
    }

    for(int i = 0; i < 20; i++){
        if(movimentos[i] == 'c' && posicao[0] > 0){
            posicao[0]--;
            matriz[posicao[0]][posicao[1]]++;
        }else if(movimentos[i] == 'b' && posicao[0] < 3){
            posicao[0]++;
            matriz[posicao[0]][posicao[1]]++;
        }else if(movimentos[i] == 'e' && posicao[1] > 0){
            posicao[1]--;
            matriz[posicao[0]][posicao[1]]++;
        }else if(movimentos[i] == 'd' && posicao[1] < 3){
            posicao[1]++;
            matriz[posicao[0]][posicao[1]]++;
        }
    }
}

void maisVisitada(int matriz[4][4]){
    int max = 0;
    int coordMax[2] = {0, 0};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(matriz[i][j] > max){
                max = matriz[i][j];
                coordMax[0] = j;
                coordMax[1] = i;
            }
        }
    }
    printf("Coordenada X:%d, Y:%d\n", coordMax[0], coordMax[1]);
}