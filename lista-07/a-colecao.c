#include <stdio.h>
#include <string.h>

// estrutura de cada jogo
struct jogo {
    char titulo[100];
    char genero[50];
    char estudio[50];
    char console[50];
    int nota;
    int anoLancamento;
};

// typedef para facilitar a declaracao de variaveis do tipo jogo
typedef struct jogo Jogo;


void lerJogos(Jogo jogo[], int qtdJogos);
// executa a funcao escolhida usando ponteiros para funcao
void executarFuncao(Jogo jogo[], int qtdJogos, char *funcao);

// funcoes de parametro
void printAno(Jogo jogo[], int qtdJogos);
void printLetra(Jogo jogo[], int qtdJogos);
void printStudio(Jogo jogo[], int qtdJogos);
void printConsole(Jogo jogo[], int qtdJogos);
void printColecao(Jogo jogo[], int qtdJogos);


int main(){
    int qtdJogos;
    scanf("%d", &qtdJogos);
    // cria um vetor do tipo Jogo com a quantidade de jogos informada
    Jogo jogo[qtdJogos];

    lerJogos(jogo, qtdJogos);

    // enquanto for digitada uma funcao valida, o loop continua
    char funcao[20];
    while(scanf(" %s", funcao) == 1){
        executarFuncao(jogo, qtdJogos, funcao);
    }
    
    //print final
    printf("Enjoei de jogar, agora vou ver TV.\n");
    return 0;
}


void lerJogos(Jogo jogo[], int qtdJogos){
    for(int i = 0; i < qtdJogos; i++){
        scanf(" %s", jogo[i].titulo);
        scanf(" %s", jogo[i].genero);
        scanf(" %s", jogo[i].estudio);
        scanf(" %s", jogo[i].console);
        scanf("%d", &jogo[i].nota);
        if(jogo[i].nota > 7){
            printf("AWESOME! Mais um GOTY pra minha coleção!\n");
        }else if(jogo[i].nota < 4){
            printf("Era melhor jogar mais um jogo de Mahjong.\n");
        }
        scanf("%d", &jogo[i].anoLancamento);
    }
}

// recebe a opcao escolhida e executa a funcao usando o ponteiro para a funcao correspondente
void executarFuncao(Jogo jogo[], int qtdJogos, char *opcao){
    void (*funcao)(Jogo[], int) = NULL;

    if(strcmp(opcao, "printAno") == 0){
        funcao = printAno;
    }else if(strcmp(opcao, "printLetra") == 0){
        funcao = printLetra;
    }else if(strcmp(opcao, "printStudio") == 0){
        funcao = printStudio;
    }else if(strcmp(opcao, "printConsole") == 0){
        funcao = printConsole;
    }else if(strcmp(opcao, "printColecao") == 0){
        funcao = printColecao;
    }

    if(funcao != NULL){
        funcao(jogo, qtdJogos);
    }
}

void printAno(Jogo jogo[], int qtdJogos){
    int ano;
    int qtd = 0;
    scanf(" %d", &ano);
    for(int i = 0; i < qtdJogos; i++){
        if(jogo[i].anoLancamento == ano){
            qtd++;
            printf("%s\n", jogo[i].titulo);
        }
    }

    if(qtd > 0){
        printf("Tenho %d jogos || %d.\n", qtd, ano);
    }else{
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

void printLetra(Jogo jogo[], int qtdJogos){
    char letra;
    int qtd = 0;
    scanf(" %c", &letra);
    for(int i = 0; i < qtdJogos; i++){
        if(jogo[i].titulo[0] == letra){
            qtd++;
            printf("%s\n", jogo[i].titulo);
        }
    }

    if(qtd > 0){
        printf("Tenho %d jogos || %c.\n", qtd, letra);
    }else{
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

void printStudio(Jogo jogo[], int qtdJogos){
    char estudio[50];
    int qtd = 0;
    scanf(" %s", estudio);
    for(int i = 0; i < qtdJogos; i++){
        if(strcmp(jogo[i].estudio, estudio) == 0){
            qtd++;
            printf("%s\n", jogo[i].titulo);
        }
    }

    if(qtd > 0){
        printf("Tenho %d jogos || %s.\n", qtd, estudio);
    }else{
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

void printConsole(Jogo jogo[], int qtdJogos){
    char console[50];
    int qtd = 0;
    scanf(" %s", console);
    for(int i = 0; i < qtdJogos; i++){
        if(strcmp(jogo[i].console, console) == 0){
            qtd++;
            printf("%s\n", jogo[i].titulo);
        }
    }
    if(qtd > 0){
        printf("Tenho %d jogos || %s.\n", qtd, console);
    }else{
        printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
    }
}

void printColecao(Jogo jogo[], int qtdJogos){
    for(int i = 0; i < qtdJogos; i++){
        printf("%s", jogo[i].titulo);
        printf(" %d\n", jogo[i].nota);
    }
}