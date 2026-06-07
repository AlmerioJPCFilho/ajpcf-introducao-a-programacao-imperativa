#include <stdio.h>

int main(){
    int num_testes;
    scanf("%d", &num_testes);
    //loop principal para todos os testes
    for(int i = 1; i <= num_testes; i++){
        int tamanho;
        scanf("%d", &tamanho);
        int vetor[tamanho];//declara o vetor de tamanho fornecido
        //leitura dos elementos do vetor
        for(int j = 0; j < tamanho; j++){
            scanf("%d", &vetor[j]);
        }

        int tam_atual = 0; //tamanho da sequencia atual
        int tam_maior = 0; //tamanho da maior sequencia encontrada
        int inicio_atual = 0; //indice de inicio da sequencia atual
        int inicio_maior = 0; //indice de inicio da maior sequencia encontrada
        //loop para encontrar a maior sequência decrescente
        for(int j = 0; j < tamanho; j++){
            inicio_atual = j;
            tam_atual = 1;
            //enquanto o elemento checado nao for o último e o próximo for menor que o atual
            while(j + 1 < tamanho && vetor[j] > vetor[j + 1]){
                tam_atual++;
                j++;//avança para o próximo elemento da sequência e pula iterações do for externo
            }

            if(tam_atual > tam_maior){
                tam_maior = tam_atual;
                inicio_maior = inicio_atual;
            }
        }

        if(tam_maior == 1){
            tam_maior = 0; //se a maior sequência for de tamanho 1, não existe sequência válida
        }
        printf("%d\n", tam_maior);
        //printa a maior sequência encontrada
        if(tam_maior > 0){
            for(int j = inicio_maior; j < inicio_maior + tam_maior; j++){
                printf("%d ", vetor[j]);
            }
        printf("\n");
        }
    }
return 0;
}