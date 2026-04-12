#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void fundirCaracteres(char *str);

int main(){
    int n_strings;
    scanf("%d", &n_strings);

    char *strings[n_strings]; //ponteiro para cada string individual
    int tamanhos[n_strings]; //tamanho de cada string individual
    int tamanho_total = 0;

    for(int i = 0; i < n_strings; i++){
        char temp[1001];
        scanf("%s", temp);

        tamanhos[i] = strlen(temp); //salva o tamanho da string atual
        tamanho_total += tamanhos[i]; //soma o tamanho da string atual ao tamanho total

        strings[i] = (char *)malloc((tamanhos[i] + 1) * sizeof(char)); //aloca memória para a string atual
        if(strings[i] == NULL){
            printf("Erro ao alocar memória para a string %d\n", i);
            exit(1); //sai do programa em caso de erro de alocação
        }
        strcpy(strings[i], temp); //copia a string temporária para a string alocada
    }

    char *stringConcatenada = (char *)malloc((tamanho_total + 1) * sizeof(char)); //aloca memória para a string concatenada
    if(stringConcatenada == NULL){
        printf("Erro ao alocar memória para a string concatenada\n");
        exit(1);
    }

    int k = 0; //indice para a string concatenada
    int offset = 0; //offset para cada letra a ser concatenada
    int continuar = 1; //se ainda tiver letras para concatenar
    while(continuar){
        continuar = 0; 
        for(int i = 0; i < n_strings; i++){
            if(offset < tamanhos[i]){ //se a string atual for menor que o offset
                stringConcatenada[k++] = strings[i][offset]; //concatena a letra atual da string atual e avanca o indice k
                continuar = 1; //ainda tem letras para concatenar
            }
        }
        offset++; //avança o offset para a próxima letra
    }
    stringConcatenada[k] = '\0';

    printf("%s\n", stringConcatenada); //printa a string original
    fundirCaracteres(stringConcatenada);
    printf("%s\n", stringConcatenada); //printa a string fundida

    //liberando a memoria usada
    for(int i = 0; i < n_strings; i++){
        free(strings[i]); //libera a memória de cada string individual
    }
    free(stringConcatenada); //libera a memória da string concatenada
    return 0;
}

void fundirCaracteres(char *str){
    int fundiu = 1;

    while(fundiu){
        fundiu = 0;
        int i = 0;
        while(str[i] != '\0' && str[i+1] != '\0'){
            if(str[i] == str[i+1]){
                if(str[i] == 'z'){//se for 'z', volta para 'a'
                    str[i] = 'a';
                }else{//se nao for 'z', avanca para o proximo caractere
                    str[i] = str[i] + 1;
                }
                for(int j = i + 1; str[j] != '\0'; j++){
                    str[j] = str[j+1]; //puxa os caracteres para a esquerda, apagando o que foi fundido
                }
                fundiu = 1;
                i++;//avanca para o proximo caractere
            }else{
                i++; //avanca para o proximo caractere caso nao sejam iguais
            }
        }
    }
}