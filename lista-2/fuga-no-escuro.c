#include <stdio.h>

int main(){
    int qtd;
    int coluna = 0;
    scanf("%d", &qtd);
    char anterior = 'Z';
    for(int i = 0; i < qtd; i++){//roda a quantidade de vezes fornecida
        int passos;
        char direcao;
        scanf("%d %c", &passos, &direcao);

        if(direcao == 'D'){
            for(int j = 0; j < coluna - 1; j++){
                printf(" ");//espaços até coluna - 1 pois na coluna fica um ponto
            }

            if(anterior == 'B'){//caso o movimento anterior seja para baixo, deve printar mais um ponto
                printf(".");
            }
            for(int j = 0; j < passos; j++){
                printf(".");//printa os pontos de acordo com os passos fornecidos
            }

            coluna += passos;
            anterior = 'D';//salva a direção anterior
        }else if(direcao == 'E'){

            if(passos > coluna){
                printf("Informacao invalida");
                return 0;//finaliza a função main caso não tenha espaço para a esquerda
            }

            coluna -= passos;
            for(int j = 0; j < coluna - 1; j++){
                printf(" ");//printa os pontos até a coluna que finaliza o movimento, pois o print é da esquerda para a direita
            }
            
            for(int j = 0; j < passos; j++){
                printf(".");
            }

            if(anterior == 'B'){//caso o movimento anterior seja para baixo, deve printar mais um ponto
                printf(".");
            }

            anterior = 'E';
        }else if(direcao == 'B'){
            for(int j = 0; j < passos - 1; j++){
                printf("\n");//pula a linha
                for(int k = 0; k < coluna - 1; k++){
                    printf(" ");//printa os espaços até a coluna
                }
                printf(".");//printa o unico ponto da linha atual
            }
            printf("\n");//pula a linha para o proximo print para a direita ou esquerda
            if(i == qtd - 1){
                for(int j = 0; j < coluna - 1; j++){
                    printf(" ");
                }
                printf(".");//caso seja a última iteração, deve printar o último ponto
            }    
            anterior = 'B';//salva a direção anterior
        }
    }
    return 0;
}