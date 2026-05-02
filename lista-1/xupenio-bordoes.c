#include <stdio.h>

int main(){
    long long N, A, B;
    scanf("%lld", &N);
    scanf("%lld %lld", &A, &B);

    long long somaTotal = N * (N + 1) / 2; //soma dos numeros de 1 a N
    //multiplos de A
    long long multA = N / A; //quantidade de multiplos de A
    long long somaMultA = A * multA * (multA + 1) / 2; //soma dos multiplos de A

    //multiplos de B
    long long multB = N / B; //quantidade de multiplos de B
    long long somaMultB = B * multB * (multB + 1) / 2; //soma dos multiplos de B

    //multiplos de A e B
    long long AB = A * B; //produto de A e B
    long long multAB = N / AB; //quantidade de multiplos de A e B
    long long somaMultAB = AB * multAB * (multAB + 1) / 2; //soma dos multiplos de A e B

    long long resultado = somaTotal - somaMultA - somaMultB + somaMultAB;
    
    printf("%lld\n", resultado);

    if(resultado%2 == 0){
        printf("Lá ele!!!");
    }else if(resultado%2 != 0){
        printf("Opa xupenio AULAS...");
    }

    return 0;
}