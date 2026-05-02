#include <stdio.h>

int main(){
    char C;
    scanf("%c", &C);

    int linhas = C - 'A' + 1;

    for(int i = 1; i <= linhas; i++){
        for(int j = 0; j < linhas - i; j++){//imprime os pontos da direita (linhas - i) vezes
            printf(".");
        }
        for(int j = 0; j < i; j++){//imprime as letras em ordem crescente, até a maior letra
            printf("%c", 'A' + j);
        }
        for(int j = i - 2; j >= 0; j--){//imprime as letras em ordem decrescente, da maior letra até a letra A novamente
            printf("%c", 'A' + j);
        }
        for(int j = 0; j < linhas - i; j++){//imprime os pontos da esquerda (linhas - i) vezes
            printf(".");
        }
        printf("\n");//passa para a próxima linha
    }
    return 0;
}