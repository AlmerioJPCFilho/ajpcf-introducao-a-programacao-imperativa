#include <stdio.h>

int main(){

    int n_clientes, X, Y, hora, minuto, latas; //numero de clientes, compraram 1 lata, compraram mais de 1 lata, hora, minuto, latas compradas
    scanf("%d", &n_clientes);
    scanf("%d", &X);
    scanf("%d", &Y);
    int clientes[n_clientes + 1]; //inicializa o vetor de tamanho dado + 1 para facilitar a contagem dos clientes
    //zera todos os indices do vetor de tamanho variavel
    for(int i = 0; i < n_clientes + 1; i++){
        clientes[i] = 0;
    }
    //marcando os clientes que compraram 1 lata
    if(X > 0){
        for(int i = X; i < n_clientes + 1; i += X){
            clientes[i] = 1;
        }
    }

    //Y clientes compraram mais de 1 lata
    for(int i = 0; i < Y; i++){
        scanf(" %d:%d %d", &hora, &minuto, &latas);
        int cliente = ((hora - 7 ) * 60 + minuto) / 3;//verifica o indice do cliente que comprou Y latas
        clientes[cliente] = latas;
    }

    //contagem das latas ate 50
    int latas_totais = 0;
    for(int i = 1; i < n_clientes + 1; i++){
        latas_totais += clientes[i]; //soma as latas de cada cliente ao total
        //se chegar a 50 latas, descobre o cliente vencedor e para o loop
        if(latas_totais >= 50){
            int min_vencedor = i * 3; //calcula quantos minutos apos as 7 horas o cliente venceu
            int hora_vencedor = 7 + (int)(min_vencedor / 60); //calcula a hora da 50a lata //int para forcar o valor inteiro
            int minuto_vencedor = min_vencedor % 60; //calcula os minutos da 50a lata

            if(clientes[i] == 1){
                printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou 1 lata.", i, hora_vencedor, minuto_vencedor);
            }else{
                printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.", i, hora_vencedor, minuto_vencedor, clientes[i]);
            }
            break;
        }
    }

    int faltam_latas = 50 - latas_totais;
    if(latas_totais < 50){
        if(faltam_latas == 1){
            printf("Ainda nao foram vendidas latas suficientes. Falta %d lata.", faltam_latas);
        }else{
            printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.", faltam_latas);
        }
    }
    return 0;
}