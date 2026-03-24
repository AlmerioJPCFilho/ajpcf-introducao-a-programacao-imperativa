#include <stdio.h>
#include <string.h>

int main(){
    int n_testes;
    scanf("%d", &n_testes);

    char luz_gigante[70000]; //tamanho maximo
    luz_gigante[0] = '\0'; //inicializa a string vazia
    int tam_gigante = 0;
    //loop principal
    for(int i = 0; i < n_testes; i++){
        char estados[61];//tamanho maximo de cada teste
        long long n_flashes;
        scanf("%s %lld", &estados, &n_flashes);
        
        int tam_atual = strlen(estados);

        //flashes
        for(long long j = 0; j < n_flashes; j++){
            for(int k = 0; k < tam_atual; k++){
                char estado_anterior = estados[k];
                if(estados[k] == 'O'){
                    estados[k] = 'X';
                } else {
                    estados[k] = 'O';
                }
                //se o estado nao mudou, para o loop
                if(!(estado_anterior == 'O' && estados[k] == 'X')){
                    break;
                }
            }
        }
        printf("%s\n", estados);

        if(tam_gigante > 0){
            char ultimo_gigante = luz_gigante[tam_gigante - 1];
            char primeiro_novo = estados[0];
            char ornamento;

            if(tam_gigante % 2 == 0){ //par
                if(ultimo_gigante == primeiro_novo){
                    ornamento = '@';
                }else{
                    ornamento = '$';
                }
            }else{ //impar
                if(ultimo_gigante == primeiro_novo){
                    ornamento = '#';
                }else{
                    ornamento = '%';
                }
            }
            luz_gigante[tam_gigante] = ornamento;
            tam_gigante++;
        }
        //adiciona o fio atual
        for(int i = 0; i < tam_atual; i++){
            luz_gigante[tam_gigante] = estados[i];
            tam_gigante++;
        }
        luz_gigante[tam_gigante] = '\0';//finaliza a string
    }

    printf("%s\n", luz_gigante);

    return 0;
}