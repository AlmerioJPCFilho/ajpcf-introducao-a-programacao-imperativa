#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================== structs ==============================
typedef struct{
    int codigo;
    char nome[100];
    int qtd;
    float preco;
}Produto;

typedef struct{
    int codigo;
    char tipo; // E = entrada, S = saida
    int qtd;
}Movimento;

typedef struct{
    int codigo;
    char tipo; // E = entrada, S = saida
    int qtd;
    char nome[100]; // ESTOQUE_INSUFICIENTE, PRODUTO_INEXISTENTE
}Inconsistencia;

int main(){
    int capacidadeMov = 2; // capacidade do vetor de movimentos
    int qtdMov = 0; // quantidade de movimentos salvos

    Movimento *pMovimentos = malloc(capacidadeMov * sizeof(Movimento));
    if(pMovimentos == NULL){
        printf("Erro ao alocar memoria para os movimentos.\n");
        exit(1);
    }

    // ler arquivo de movimentos
    FILE *mov = fopen("movimentos.txt", "r");
    if(mov == NULL){
        printf("Erro ao abrir arquivo.\n");
        free(pMovimentos);
        exit(1);
    }
    while(fscanf(mov, "%d %c %d", &pMovimentos[qtdMov].codigo, &pMovimentos[qtdMov].tipo, &pMovimentos[qtdMov].qtd) != EOF){
        qtdMov++;
        if(qtdMov == capacidadeMov){
            capacidadeMov *= 2;
            Movimento *temp = realloc(pMovimentos, capacidadeMov * sizeof(Movimento));
            if(temp == NULL){
                printf("Erro ao realocar memoria para os movimentos.\n");
                free(pMovimentos);
                fclose(mov);
                exit(1);
            }
            pMovimentos = temp;
        }
    }

    int capacidadeProd = 2; // capacidade do vetor de produtos
    int qtdProd = 0; // quantidade de produtos salvos

    Produto *pProdutos = malloc(capacidadeProd * sizeof(Produto));
    if(pProdutos == NULL){
        printf("Erro ao alocar memoria para os produtos.\n");
        free(pMovimentos);
        fclose(mov);
        exit(1);
    }

    // ler arquivo de produtos
    FILE *prod = fopen("produtos.txt", "r");
    if(prod == NULL){
        printf("Erro ao abrir arquivo.\n");
        free(pMovimentos);
        fclose(mov);
        free(pProdutos);
        fclose(prod);
        exit(1);
    }
    while(fscanf(prod, "%d %s %d %f", &pProdutos[qtdProd].codigo, pProdutos[qtdProd].nome, &pProdutos[qtdProd].qtd, &pProdutos[qtdProd].preco) != EOF){
        qtdProd++;
        if(qtdProd == capacidadeProd){
            capacidadeProd *= 2;
            Produto *temp = realloc(pProdutos, capacidadeProd * sizeof(Produto));
            if(temp == NULL){
                printf("Erro ao realocar memoria para os produtos.\n");
                free(pMovimentos);
                fclose(mov);
                free(pProdutos);
                fclose(prod);
                exit(1);
            }
            pProdutos = temp;
        }
    }
    
    // criar arquivo de estoque
    FILE *estoque = fopen("estoque_atualizado.txt", "w");
    if(estoque == NULL){
        printf("Erro ao criar arquivo de estoque.\n");
        free(pMovimentos);
        fclose(mov);
        fclose(prod);
        exit(1);
    }
    // criar arquivo de relatorio
    FILE *relatorio = fopen("relatorio.txt", "w");
    if(relatorio == NULL){
        printf("Erro ao criar arquivo de relatorio.\n");
        free(pMovimentos);
        fclose(mov);
        fclose(prod);
        fclose(estoque);
        exit(1);
    }

    // variaveis para o relatorio
    int movAplicados = 0;
    int saidasRecusadas = 0;
    int movSemCadastro = 0;
    Inconsistencia inconsistencias[qtdMov]; // salvar inconsistencias
    int qtdInc = 0;

    // encontrar o produto com codigo do movimento atual e atualizar o estoque
    for(int i = 0; i < qtdMov; i++){
        int encontrou = 0;
        for(int j = 0; j < qtdProd; j++){
            if(pMovimentos[i].codigo == pProdutos[j].codigo){ // movimento com cadastro
                encontrou = 1;
                if(pMovimentos[i].tipo == 'E'){ // entrada sempre e aceita
                    pProdutos[j].qtd += pMovimentos[i].qtd;
                    movAplicados++;
                }else if(pMovimentos[i].tipo == 'S'){
                    if(pProdutos[j].qtd >= pMovimentos[i].qtd){ // saida aceita se tiver estoque suficiente
                        pProdutos[j].qtd -= pMovimentos[i].qtd;
                        movAplicados++;
                    }else{ // saida recusada por falta de estoque
                        // recusar movimento
                        inconsistencias[qtdInc].codigo = pMovimentos[i].codigo;
                        inconsistencias[qtdInc].tipo = 'S';
                        inconsistencias[qtdInc].qtd = pMovimentos[i].qtd;
                        strcpy(inconsistencias[qtdInc].nome, "ESTOQUE_INSUFICIENTE");
                        qtdInc++;
                        saidasRecusadas++;
                    }
                }
                break; // se ja encontrou, para de procurar os produtos do movimento atual
            }
        }
        if(!encontrou){ // movimento sem cadastro
                inconsistencias[qtdInc].codigo = pMovimentos[i].codigo;
                inconsistencias[qtdInc].tipo = pMovimentos[i].tipo;
                inconsistencias[qtdInc].qtd = pMovimentos[i].qtd;
                strcpy(inconsistencias[qtdInc].nome, "PRODUTO_INEXISTENTE");
                qtdInc++;
                movSemCadastro++;
        }
    }

    // escrevendo o estoque atualizado
    for(int i = 0; i < qtdProd; i++){
        fprintf(estoque, "%d %s %d %.2f\n", pProdutos[i].codigo, pProdutos[i].nome, pProdutos[i].qtd, pProdutos[i].preco);
    }
    // escrevendo o relatorio
    fprintf(relatorio, "PRODUTOS PROCESSADOS: %d\n", qtdProd);
    fprintf(relatorio, "MOVIMENTOS APLICADOS: %d\n", movAplicados);
    fprintf(relatorio, "SAIDAS RECUSADAS: %d\n", saidasRecusadas);
    fprintf(relatorio, "MOVIMENTOS SEM CADASTRO: %d\n", movSemCadastro);
    fprintf(relatorio, "ESTOQUE BAIXO:\n");
    for(int i = 0; i < qtdProd; i++){
        if(pProdutos[i].qtd <= 5){
            fprintf(relatorio, "%d %s %d\n", pProdutos[i].codigo, pProdutos[i].nome, pProdutos[i].qtd);
        }
    }
    fprintf(relatorio, "INCONSISTENCIAS:\n");
    for(int i = 0; i < qtdInc; i++){
        fprintf(relatorio, "%d %c %d %s\n", inconsistencias[i].codigo, inconsistencias[i].tipo, inconsistencias[i].qtd, inconsistencias[i].nome);
    }

    // liberando memoria e fechando arquivos
    free(pMovimentos);
    free(pProdutos);
    fclose(mov);
    fclose(prod);
    fclose(estoque);
    fclose(relatorio);
    return 0;
}