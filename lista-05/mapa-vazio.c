#include <stdio.h>
#include <stdlib.h>

int main(){
    int numero = 0;
    int qtdImpares = 0;
    int *impares = NULL;
    int qtdPares = 0;
    int *pares = NULL;

    while(scanf(" %d", &numero) == 1){
        if(numero % 2 != 0){
            qtdImpares++;
            int *temp = (int *)realloc(impares, qtdImpares * sizeof(int)); //ponteiro temporario para evitar perda de memoria caso falhe
            if(temp == NULL){
                printf("Erro ao realocar memória para impares.\n");
                free(impares);
                free(pares);
                exit(1);
            }
            impares = temp;
            impares[qtdImpares - 1] = numero;
        }else{
            qtdPares++;
            int *temp = (int *)realloc(pares, qtdPares * sizeof(int)); //ponteiro temporario para evitar perda de memoria caso falhe
            if(temp == NULL){
                printf("Erro ao realocar memória para pares.\n");
                free(impares);
                free(pares);
                exit(1);
            }
            pares = temp;
            pares[qtdPares - 1] = numero;
        }
    }

    printf("Mais um bom dia de trabalho!\n");
    for(int i = 0; i < qtdImpares; i++){
        printf("%d\n", impares[i]);
    }
    for(int i = 0; i < qtdPares; i++){
        printf("%d\n", pares[i]);
    }
    printf("Vou visitar esses lugares de novo... algum dia.\n");

    free(impares);
    free(pares);
    return 0;
}