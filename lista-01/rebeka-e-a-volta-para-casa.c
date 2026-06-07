#include <stdio.h>

int main(){
    int total, x, y, z;
    int rebeka = 3;
    int investiu = 0;
    int conseguiu = 0; //divisao deu certo ou nao
    int sobrou = 0; //quanto sobrou apos a divisao
    scanf("%d", &total);
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &z);
    //primeira tentativa
    if(total*x%100 == 0 && total*y%100 == 0 && total*z%100 == 0){//checa se o valor para cada é inteiro
        int a = total*x/100;
        int b = total*y/100;
        int c = total*z/100;
        sobrou = total - a - b - c;
        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
        conseguiu = 1;
        rebeka += sobrou;
    }
    //segunda tentativa (investido 1 real)
    if(!conseguiu){
        total += 1;
        rebeka -= 1;
        investiu += 1;
        if(total*x%100 == 0 && total*y%100 == 0 && total*z%100 == 0){
            int a = total*x/100;
            int b = total*y/100;
            int c = total*z/100;
            sobrou = total - a - b - c;
            if(sobrou > investiu){//checa se sobrou pelo menos uma moeda
                printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
                conseguiu = 1;
                rebeka += sobrou;
            }
        }
    }
    //terceira tentativa (investido 2 reais)
    if(!conseguiu){
        total += 1;
        rebeka -= 1;
        investiu += 1;
        if(total*x%100 == 0 && total*y%100 == 0 && total*z%100 == 0){
            int a = total*x/100;
            int b = total*y/100;
            int c = total*z/100;
            sobrou = total - a - b - c;
            if(sobrou > investiu){
                printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
                conseguiu = 1;
                rebeka += sobrou;
            }
        }
    }
    //quarta tentativa (investido 3 reais)
    if(!conseguiu){
        total += 1;
        rebeka -= 1;
        investiu += 1;
        if(total*x%100 == 0 && total*y%100 == 0 && total*z%100 == 0){
            int a = total*x/100;
            int b = total*y/100;
            int c = total*z/100;
            sobrou = total - a - b - c;
            if(sobrou > investiu){
                printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
                conseguiu = 1;
                rebeka += sobrou;
            }
        }
    }

    if(investiu == 2 && conseguiu){//caso tenha dado certo com 2 reais
        char l1, l2, l3;
        scanf(" %c", &l1);
        scanf(" %c", &l2);
        scanf(" %c", &l3);
        int soma = l1 + l2 + l3 - 288;//288 é o correspondente a 3 * 96(valor de 'a' na tabela ascii -1)
        printf("%d\n", soma);
    }else if(investiu == 3 && conseguiu){//caso tenha dado certo com 3 reais
        int i1, i2, i3;
        scanf("%d", &i1);
        scanf("%d", &i2);
        scanf("%d", &i3);
        int p1 = 0 , p2 = 0 , p3 = 0;
        if(i1%3 == 0){
            p1 = i1/3;
        }
        if(i2%3 == 0){
            p2 = i2/3;
        }
        if(i3%3 == 0){
            p3 = i3/3;
        }
        printf("%d\n", p1 + p2 + p3);
    }        

    if(!conseguiu){//não conseguiu dividir
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }else{//conseguiu dividir
        if(rebeka >= 7){//conseguiu o valor da passagem
            printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
        }else{//não conseguiu o valor da passagem
            printf("E parece que Rebeka vai ter que voltar andando...\n");
        }
    }
    return 0;
}