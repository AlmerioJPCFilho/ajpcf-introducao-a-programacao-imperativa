#include <stdio.h>

int main(){
    int X, N, f1, f2, f3;
    int chance = 1000000; //começa alta pois quanto menor o valor, maior a chance
    int canal = 0; //começa em 0 pois o canal certo sempre será maior que 0
    int min = 1000000; //começa alto pois quanto menor o valor, mais rápido ele via ser chamado
    int termo = 0; //termo mais próximo de X, para verificar o VIP

    scanf("%d %d", &X, &N);

    for(int i = 1; i <= N; i++){
        scanf("%d %d", &f1, &f2);
        f3 = f1 + f2;
        if(X > f2){
            int min_atual = 3; //começa em 3 pois se for for maior que f2 ele vai ser chamado no mínimo no minuto 3
            while(f3 < X){
                f1 = f2;
                f2 = f3;
                f3 = f1 + f2;
                min_atual++; //aumenta 1 minuto a cada iteração
            }
            
            int chance_atual = 1000000; //chance no canal atual
            int termo_atual = 0;

            if(X - f2 > f3 - X){
                chance_atual = f3 - X; //chance caso o termo mais próximo seja f3
                termo_atual = f3;
            }else{
                chance_atual = X - f2; //chance caso o termo mais próximo seja f2 ou os dois termos empatem
                min_atual--; //desconta um minuto pois é adicionado um minuto sempre que f3 é calculado, mas se o mais próximo for f2, ele é chamado 1 minuto antes
                termo_atual = f2;
            }

            if(chance_atual <= chance){//caso a chance no canal atual seja melhor ou igual
                chance = chance_atual;
                canal = i;
                min = min_atual;
                termo = termo_atual;
            }
        }else{
            int min_atual = 2; //começa em 2 e se for f1 desconta 1 minuto
            int chance_atual = 1000000;
            int termo_atual = 0;
            if(X < f1){ //se X for menor que f1, o termo mais próximo é f1
                chance_atual = f1 - X;
                termo_atual = f1;
                min_atual--; //desconta um minuto pois se o mais próximo for f1, ele é chamado 1 minuto antes
            }else if(X - f1 > f2 - X){
                chance_atual = f2 - X; //chance caso o termo mais próximo seja f2
                termo_atual = f2;
            }else{
                chance_atual = X - f1; //chance caso o termo mais próximo seja f1 ou os dois termos empatem
                termo_atual = f1;
                min_atual--; //desconta um minuto pois se o mais próximo for f1, ele é chamado 1 minuto antes
            }

            if(chance_atual <= chance){ //caso a chance no canal atual seja melhor ou igual
                chance = chance_atual;
                canal = i;
                min = min_atual;
                termo = termo_atual;
            }
        }
    }

    //para verificar o VIP
    int vip = 0;
    int n = termo;
    while(n > 0){
        vip += n % 10; //soma os dígitos do termo mais próximo
        n /= 10;
    }

    if(vip >= 10){
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", canal, min);
    }else{
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP não vai rolar :(\n", canal, min);
    }

    return 0;
}