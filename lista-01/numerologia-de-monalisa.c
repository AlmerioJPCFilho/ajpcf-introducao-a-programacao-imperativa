#include <stdio.h>

int main()
{
    int diaNasc, mesNasc, anoNasc, diaAtual, mesAtual, anoAtual;
    scanf("%d/%d/%d %d/%d/%d", &diaNasc, &mesNasc, &anoNasc, &diaAtual, &mesAtual, &anoAtual);
    
    //amor
    int restoAmor = ((diaNasc + mesNasc + anoNasc + diaAtual + mesAtual + anoAtual) * 7) % 101; //inteiro pois o resto nao tera parte decimal
    
    printf("Amor: %d%% ", restoAmor);
    
    //if else para printar as mensagens
    if(restoAmor < 20){
        printf("Pessimo dia para se apaixonar.\n");
    }else if(restoAmor >= 20 && restoAmor <= 40){
        printf("Melhor manter o coracao <3 longe de perigo.\n");
    }else if(restoAmor >= 41 && restoAmor <= 69){
        printf("Se o papo e as ideias baterem, esta liberado pensar em algo.\n");
    }else if(restoAmor >= 70 && restoAmor <= 80){
        printf("Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.\n");
    }else if(restoAmor > 80){
        printf("Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.\n");
    }
    
    //sorte
    int restoSorte = (((diaNasc + diaAtual + mesNasc + mesAtual) * 9) + (anoAtual - anoNasc)) % 101;
    
    printf("Sorte: %d%% ", restoSorte);
    
    if(restoSorte < 30){
        printf("Nem jogue moedas pra cima hoje.");
    }else if(restoSorte >= 30 && restoSorte <= 50){
        printf("Melhor nao arriscar.");
    }else if(restoSorte >= 51 && restoSorte <= 79){
        printf("Por sua conta em risco.");
    }else if(restoSorte >= 80 && restoSorte <= 90){
        printf("Hoje vale a pena arriscar.");
    }else if(restoSorte > 90){
        printf("Nao tenha medo de virar cartas hoje.");
    }
    printf(" Sem tigrinho nem jogos de azar, por favor!\n");
    
    //trabalho
    int restoTrabalho = ((anoNasc + anoAtual) - ((diaNasc + diaAtual + mesNasc + mesAtual) * 8)) % 101;
    
    printf("Trabalho: %d%% ", restoTrabalho);
    
    if(restoTrabalho < 40){
        printf("Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.\n");
    }else if(restoTrabalho >= 40 && restoTrabalho <= 50){
        printf("Segura a emocao, nao xinga ninguem, nao esquece de beber agua.\n");
    }else if(restoTrabalho >= 51 && restoTrabalho <= 69){
        printf("Um dia proveitoso com certeza, leve sua simpatia consigo.\n");
    }else if(restoTrabalho >= 70 && restoTrabalho <= 84){
        printf("Boas vibracoes hoje, chances podem estar ao seu redor.\n");
    }else if(restoTrabalho > 85){
        printf("Use do maximo de networking possível hoje, dia bom para negocios.\n");
    }
    
    //cor
    
    int restoCor = (diaNasc * diaNasc + diaAtual * diaAtual + mesNasc * mesNasc + mesAtual * mesAtual + anoNasc * anoNasc + anoAtual * anoAtual) % 11;
    
    printf("Cor: ");
    //switch pois cada cor tem apenas um numero correspondente
    switch(restoCor){
        case 0:
            printf("Cinza.");
            break;
        case 1:
            printf("Vermelho.");
            break;
        case 2:
            printf("Laranja.");
            break;
        case 3:
            printf("Amarelo.");
            break;
        case 4: 
            printf("Verde.");
            break;
        case 5:
            printf("Azul.");
            break;
        case 6:
            printf("Roxo.");
            break;
        case 7:
            printf("Marrom.");
            break;
        case 8:
            printf("Rosa.");
            break;
        case 9:
            printf("Preto.");
            break;
        case 10:
            printf("Branco.");
            break;
        default:
            break;
    }
    
    return 0;
}