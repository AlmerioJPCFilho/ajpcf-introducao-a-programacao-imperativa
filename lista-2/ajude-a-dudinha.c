#include <stdio.h>

int main(){
    long N, K, P;
    scanf("%ld %ld %ld", &N, &K, &P);
    long primeiro = -1;
    long Q = 0;
    for(long numero = N; numero < K; numero++){//percorre os números de N a K
        int fatores = 0;
        long temp = numero;//copia o número para não modificar o original

        if(numero >= 2){
            for(int j = 2; j * j <= temp; j++){//fatoração

                int contador = 0;

                while(temp % j == 0){//conta quantas vezes o número é divisível pelo fator primo
                    contador++;
                    temp /= j;
                }

                if(contador >= 2 && j % 2 != 0){//se o fator se repete sendo ímpar,o número é inválido
                    fatores = -1;
                    break;
                }
                if(contador == 1 && j % 2 != 0){//se o fator é ímpar e só aparece uma vez, conta como fator ímpar
                    fatores++;
                }
            }
        }
        if(fatores != -1 && temp > 1 && temp % 2 != 0){//verifica se sobrou um fator primo maior que 1 e ímpar com o numero sendo válido
            fatores++;
        }

        if(primeiro == -1 && fatores == P){//se ainda não achou o primeiro e os fatores dele são iguais a P
            primeiro = numero;
        }else if(fatores == P){//se os fatores são iguais a P após o primeiro
            Q++;
        }
    }

    if(primeiro == -1){//se não encontrou nenhum número válido, o primeiro não será alterado, permanecendo -1
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    }else{
        printf("%ld %ld\n", primeiro, Q);
    }
    return 0;
}