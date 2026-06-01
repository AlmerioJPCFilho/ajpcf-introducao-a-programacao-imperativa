#include <stdio.h>

int main(){
    char pilha[1000];
    int topo = -1;
    char c;

    while(scanf(" %c", &c) != EOF){
        int processando = 1;

        while(processando){
            if(topo >= 0){
                char cTopo = pilha[topo];

                if((c == 'g' && cTopo == 'b') || (c == 'b' && cTopo == 'g')){
                    c = 'c'; // vira ciano
                    topo--;
                    continue; // para checar o novo caractere
                }
                else if((c == 'r' && cTopo == 'b') || (c == 'b' && cTopo == 'r')){
                    c = 'm'; // vira magenta
                    topo--;
                    continue; // para checar o novo caractere
                }
                else if((c == 'r' && cTopo == 'g') || (c == 'g' && cTopo == 'r')){
                    c = 'y'; // vira amarelo
                    topo--;
                    continue; // para checar o novo caractere
                }
            }
            topo++; // empilha o caractere atual se nao combinou com nenhum do topo
            pilha[topo] = c;
            processando = 0; // para o loop

            if(topo >= 2){
                if(pilha[topo] == pilha[topo-1] && pilha[topo-1] == pilha[topo-2]){
                    topo -= 3;
                }
            }
        }

        if(topo == -1){
            printf("Pilha vazia!\n\n");
        }else{
            for(int i = topo; i >= 0; i--){
                printf("%c\n", pilha[i]);
            }
            printf("\n");
        }
    }

    printf("Thank You So Much For Playing My Game!\n");
    return 0;
}