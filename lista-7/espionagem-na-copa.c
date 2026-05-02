#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct cidadela{
    char nome[100];
    int populacao;
    int perigo;
    char funcao[100];
};
typedef struct cidadela Cidadela;

int compararCidadelas(const void *a, const void *b);

int main(){
    int nCidadelas = 0;

    // aloca memoria para as cidadelas
    Cidadela *pCidadelas = (Cidadela *)malloc((nCidadelas + 1) * sizeof(Cidadela));
    if(pCidadelas == NULL){
        printf("Erro ao alocar memória para as cidadelas\n");
        exit(1);
    }

    char mensagem[201];
    int chave = -1;

    while(fgets(mensagem, sizeof(mensagem), stdin) != NULL){
        nCidadelas++;

        // zera a struct atual
        pCidadelas[nCidadelas - 1].nome[0] = '\0';
        pCidadelas[nCidadelas - 1].populacao = 0;
        pCidadelas[nCidadelas - 1].perigo = 0;
        pCidadelas[nCidadelas - 1].funcao[0] = '\0';

        char nome[100] = "";
        char numero[20] = "";
        int perigo = 0;
        char funcao[100] = "";
        int especial = 0; // indica de a mensagem e especial

        int idxNome = 0;
        int idxNumero = 0;
        int idxFuncao = 0;
        
        for(int i = 0; mensagem[i] != '\0'; i++){
            if(isupper(mensagem[i])){
                nome[idxNome++] = mensagem[i];
                nome[idxNome] = '\0';
            }
            if(isdigit(mensagem[i])){
                numero[idxNumero++] = mensagem[i];
                numero[idxNumero] = '\0';
            }
            if(mensagem[i] == '*'){
                perigo++;
            }
            if(mensagem[i] == ' ' && mensagem[i + 1] == ' '){
                funcao[idxFuncao++] = mensagem[i + 2];
                funcao[idxFuncao] = '\0';
            }
            if(mensagem[i] == '!'){
                especial = 1;
            }
        }
        // formata o nome e a funcao
        nome[0] = toupper(nome[0]);
        for(int i = 1; nome[i] != '\0'; i++){
            nome[i] = tolower(nome[i]);
        }

        funcao[0] = toupper(funcao[0]);
        for(int i = 1; funcao[i] != '\0'; i++){
            funcao[i] = tolower(funcao[i]);
        }

        // copia os dados para a struct
        if(especial){ // caso seja uma mensagem especial, salva apenas a chave
            chave = atoi(numero);
            nCidadelas--; // nao conta essa mensagem como uma cidadela
        }else{
            strcpy(pCidadelas[nCidadelas - 1].nome, nome);
            pCidadelas[nCidadelas - 1].populacao = atoi(numero);
            pCidadelas[nCidadelas - 1].perigo = perigo;
            strcpy(pCidadelas[nCidadelas - 1].funcao, funcao);
        }

        // realoca memoria para a proxima cidadela
        Cidadela *temp = (Cidadela *)realloc(pCidadelas, (nCidadelas + 1) * sizeof(Cidadela));
        if(temp == NULL){
            printf("Erro ao realocar memória para as cidadelas\n");
            free(pCidadelas);
            exit(1);
        }
        pCidadelas = temp;
    }
    
    Cidadela ordemCidadelas[nCidadelas];
    Cidadela cidadelaAtual;
    //ordenar por habitantes > perigo > alfabetico
    qsort(pCidadelas, nCidadelas, sizeof(Cidadela), compararCidadelas);

    // encontrar gingrey
    if(chave == -1){
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
    }else{
        printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade ",
            pCidadelas[chave - 1].nome, pCidadelas[chave - 1].populacao, pCidadelas[chave - 1].funcao);
        for(int i = 0; i < pCidadelas[chave - 1].perigo; i++){
            printf("*");
        }
        printf(". ");
            if(pCidadelas[chave - 1].populacao > 1000 && pCidadelas[chave - 1].perigo > 3){
                printf("Talvez seja melhor desistir...\n");
            }else if(pCidadelas[chave - 1].populacao > 1000){
                printf("Um lugar denso, vai ser difícil achar ela.\n");
            }else if(pCidadelas[chave - 1].perigo > 3){
                printf("Vai ser complicado entrar lá.\n");
            }
    }
    return 0;
}

int compararCidadelas(const void *a, const void *b){
    Cidadela *cidA = (Cidadela *)a; // converte os ponteiros genéricos para ponteiros do tipo Cidadela
    Cidadela *cidB = (Cidadela *)b;

    // populacao
    if(cidA->populacao != cidB->populacao){
        return cidB->populacao - cidA->populacao; // retorna negativo se A for maior e positivo de B for maior
    }

    // perigo (caso haja empate na populacao)
    if(cidA->perigo != cidB->perigo){
        return cidB->perigo - cidA->perigo; // retorna negativo se A for maior e positivo se B for maior
    }

    // ordem alfabetica (caso haja empate na populacao e no perigo)
    return strcmp(cidA->nome, cidB->nome); // retorna negativo se A for menor(vem antes), positivo se B for menor(vem antes) e 0 se forem iguais
}