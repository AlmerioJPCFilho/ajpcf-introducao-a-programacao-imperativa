#include <stdio.h>
#include <stdlib.h>

// ============================== estrutura dos nos ==============================
typedef struct No{
    char cor;
    struct No *prox;
}No;

// ============================== funções para manipulação da pilha ==============================
void empilhar(No **topo, char c);
void desempilhar(No **topo);

int main(){
    No *topo = NULL; // declara o primeiro  elemento da pilha
    char c;

    while(scanf(" %c", &c) != EOF){
        int processando = 1;

        while(processando){
            if(topo != NULL){
                char cTopo = topo->cor;

                if((c == 'g' && cTopo == 'b') || (c == 'b' && cTopo == 'g')){
                    c = 'c'; // vira ciano
                    desempilhar(&topo);
                    continue; // para checar o novo caractere
                }
                else if((c == 'r' && cTopo == 'b') || (c == 'b' && cTopo == 'r')){
                    c = 'm'; // vira magenta
                    desempilhar(&topo);
                    continue; // para checar o novo caractere
                }
                else if((c == 'r' && cTopo == 'g') || (c == 'g' && cTopo == 'r')){
                    c = 'y'; // vira amarelo
                    desempilhar(&topo);
                    continue; // para checar o novo caractere
                }
            }
            empilhar(&topo, c); // empilha o caractere atual se nao combinou com nenhum do topo
            processando = 0; // para o loop

            if(topo != NULL && topo->prox != NULL && topo->prox->prox != NULL){ // verifica se tem 3 elementos para comparar
                if((topo->cor == topo->prox->cor) && (topo->cor == topo->prox->prox->cor)){ // se os tres forem iguais
                    // desempilha os tres do topo
                    desempilhar(&topo);
                    desempilhar(&topo);
                    desempilhar(&topo);
                }
            }
        }

        if(topo == NULL){
            printf("Pilha vazia!\n\n");
        }else{
            No *atual = topo;

            while(atual != NULL){
                printf("%c\n", atual->cor);
                atual = atual->prox;
            }
            printf("\n");
        }
    }

    while(topo != NULL){ // limpa a pilha antes de finalizar
        desempilhar(&topo);
    }

    printf("Thank You So Much For Playing My Game!\n");
    return 0;
}

// ============================== funcoes para manipulação da pilha ==============================
void empilhar(No **topo, char c){
    No *novoNo = (No*)malloc(sizeof(No));
    if(novoNo == NULL){
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novoNo->cor = c;
    novoNo->prox = *topo;
    *topo = novoNo;
}

void desempilhar(No **topo){
    if(*topo == NULL){
        return;
    }
    No *temp = *topo;
    *topo = temp->prox;
    free(temp);
}