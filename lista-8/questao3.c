#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================== struct para os dados de cada linha ==============================
typedef struct{
    float sepal_length;
    float sepal_width;
    float petal_length;
    float petal_width;
    char species[50];
} Dados;

typedef struct{
    char species[50];
    int qtdEspecie;
} FreqEspecie;

// ============================== main ==============================
int main(){
    int qtdArquivos = 0;
    scanf("%d", &qtdArquivos);

    for(int i = 0; i < qtdArquivos; i++){
        char nomeArquivo[50];

        // gera o nome do arquivo
        sprintf(nomeArquivo, "iris%d.csv", i+1);

        FILE *file = fopen(nomeArquivo, "r");
        if(file == NULL){
            printf("Erro ao abrir o arquivo. Abrindo o proximo... %s\n", nomeArquivo);
            continue;
        }

        int capacidade = 2;
        int qtdLinhas = 0;

        Dados *pDados = malloc(capacidade * sizeof(Dados));

        char cabecalho[100];
        char linha[100];
        
        // le o cabecalho
        if(fgets(cabecalho, sizeof(cabecalho), file) == NULL){
            fclose(file);
            free(pDados);
            continue;
        }

        // le cada linha
        while(fgets(linha, sizeof(linha), file) != NULL){
            // se chegar na capacidade, dobra o tamanho do array
            if(qtdLinhas == capacidade){
                capacidade *= 2;
                Dados *temp = realloc(pDados, capacidade * sizeof(Dados));
                if(temp == NULL){
                    printf("Erro ao realocar memoria\n");
                    free(pDados);
                    fclose(file);
                    exit(1);
                }
                pDados = temp;
            }

            sscanf(linha, "%f,%f,%f,%f,%[^\n\r]", &pDados[qtdLinhas].sepal_length, 
                                                    &pDados[qtdLinhas].sepal_width, 
                                                    &pDados[qtdLinhas].petal_length, 
                                                    &pDados[qtdLinhas].petal_width, 
                                                    pDados[qtdLinhas].species);

            qtdLinhas++;
        }
        // fecha o arquivo atual
        fclose(file);

        if(qtdLinhas == 0){
            free(pDados);
            continue;
        }

        // calcular media e moda

        float somaSL = 0, somaSW = 0, somaPL = 0, somaPW = 0;
        FreqEspecie freqEspecies[100];
        int qtdEspecies = 0;

        for(int j = 0; j < qtdLinhas; j++){
            // somas para as medias
            somaSL += pDados[j].sepal_length;
            somaSW += pDados[j].sepal_width;
            somaPL += pDados[j].petal_length;
            somaPW += pDados[j].petal_width;

            // contagem de frequencias para a moda
            int encontrada = 0;
            for(int k = 0; k < qtdEspecies; k++){ // se a especie ja foi encontrada, aumenta a contagem
                if(strcmp(freqEspecies[k].species, pDados[j].species) == 0){
                    freqEspecies[k].qtdEspecie++;
                    encontrada = 1;
                    break;
                }
            }
            if(!encontrada){ // se nao foi encontrada, salva a nova especie
                strcpy(freqEspecies[qtdEspecies].species, pDados[j].species);
                freqEspecies[qtdEspecies].qtdEspecie = 1;
                qtdEspecies++;
            }
        }

        // calculo das medias
        float mediaSL = somaSL / qtdLinhas;
        float mediaSW = somaSW / qtdLinhas;
        float mediaPL = somaPL / qtdLinhas;
        float mediaPW = somaPW / qtdLinhas;

        // encontrando a moda
        int qtdMax = -1; // se continuar em -1 nao tem moda
        char moda[50] = "";

        for(int k = 0; k < qtdEspecies; k++){
            if(freqEspecies[k].qtdEspecie > qtdMax){
                qtdMax = freqEspecies[k].qtdEspecie;
                strcpy(moda, freqEspecies[k].species);
            }else if(freqEspecies[k].qtdEspecie == qtdMax){ // desempate ordem alfabetica
                if(strcmp(freqEspecies[k].species, moda) < 0){ // se a especie atual vier antes, ela vira a moda
                    strcpy(moda, freqEspecies[k].species);
                }
            }
        }

        // relatorio
        printf("============================================================\n");
        printf("Arquivo: <%s>\n", nomeArquivo);
        printf("============================================================\n");
        printf("%s", cabecalho);
        for(int j = 0; j < qtdLinhas; j++){
            printf("%.1f,%.1f,%.1f,%.1f,%s\n", pDados[j].sepal_length, 
                                                pDados[j].sepal_width, 
                                                pDados[j].petal_length, 
                                                pDados[j].petal_width, 
                                                pDados[j].species);
        }
        printf("------------------------------------------------------------\n");
        printf("Medias:\n");
        printf("Sepal Length: %.2f\n", mediaSL);
        printf("Sepal Width: %.2f\n", mediaSW);
        printf("Petal Length: %.2f\n", mediaPL);
        printf("Petal Width: %.2f\n", mediaPW);
        printf("------------------------------------------------------------\n");
        printf("Moda: %s\n", moda);

        // salvar o relatorio nos arquivos
        file = fopen(nomeArquivo, "a");
        if(file != NULL){
            fprintf(file, "\n------------------------------\n");
            fprintf(file, "Medias:\n");
            fprintf(file, "Sepal Length: %.2f\n", mediaSL);
            fprintf(file, "Sepal Width: %.2f\n", mediaSW);
            fprintf(file, "Petal Length: %.2f\n", mediaPL);
            fprintf(file, "Petal Width: %.2f\n", mediaPW);
            fprintf(file, "------------------------------\n");
            fprintf(file, "Moda: %s\n", moda);
            fclose(file);
        }else{
            printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        }

        // libera os ponteiros
        free(pDados);
    }
    printf("============================================================\n");
    return 0;
}