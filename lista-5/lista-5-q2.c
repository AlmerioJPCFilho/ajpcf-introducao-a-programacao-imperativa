#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void relatorio(float *pNotas, int nAlunos);
float calcularMedia(float *pNotas, int nAlunos);//retorna a media
int encontrarMaior(float *pNotas, int nAlunos);//retorna o indice da maior nota
int encontrarMenor(float *pNotas, int nAlunos);//retorna o indice da menor nota
int acimaDaMedia(float *pNotas, int nAlunos, float media);//retorna a quantidade de alunos acima da media
float encontrarMediana(float *pNotas, int nAlunos);//retorna a mediana
float encontrarModa(float *pNotas, int nAlunos);//retorna a moda

int main(){
    int nAlunos;
    scanf("%d", &nAlunos);
    //alocar memoria para as notas
    float *pNotas;
    pNotas = (float *)malloc(nAlunos * sizeof(float));
    if(pNotas == NULL){
        printf("Erro ao alocar memória para as notas\n");
        exit(1);
    }
    for(int i = 0; i < nAlunos; i++){
        scanf(" %f", &pNotas[i]);
    }

    printf("Relatorio inicial\n");
    relatorio(pNotas, nAlunos);

    int nNovasNotas;
    scanf("%d", &nNovasNotas);
    //realocar memoria para as novas notas
    float *temp = (float *)realloc(pNotas, (nAlunos + nNovasNotas) * sizeof(float));
    if(temp == NULL){
        printf("Erro ao realocar memória para as novas notas\n");
        free(pNotas);
        exit(1);
    }
    pNotas = temp;
    for(int i = nAlunos; i < nAlunos + nNovasNotas; i++){
        scanf(" %f", &pNotas[i]);
    }

    printf("\nRelatorio atualizado\n");
    relatorio(pNotas, nAlunos + nNovasNotas);

    free(pNotas);
    return 0;
}


void relatorio(float *pNotas, int nAlunos){
    float media = calcularMedia(pNotas, nAlunos);
    printf("Media: %.2f\n", media);

    int indiceMaior = encontrarMaior(pNotas, nAlunos);
    printf("Maior nota: %.2f (aluno %d)\n", pNotas[indiceMaior], indiceMaior + 1);

    int indiceMenor = encontrarMenor(pNotas, nAlunos);
    printf("Menor nota: %.2f (aluno %d)\n", pNotas[indiceMenor], indiceMenor + 1);
    
    printf("Acima da media: %d\n", acimaDaMedia(pNotas, nAlunos, media));

    printf("Mediana: %.2f\n", encontrarMediana(pNotas, nAlunos));

    float moda = encontrarModa(pNotas, nAlunos);
    if(moda == -1){
        printf("Moda: Nao ha moda unica\n");
    }else{
        printf("Moda: %.2f\n", moda);
    }
}

float calcularMedia(float *pNotas, int nAlunos){
    float soma = 0;
    for(int i = 0; i < nAlunos; i++){
        soma += pNotas[i];
    }
    return soma / nAlunos;
}

int encontrarMaior(float *pNotas, int nAlunos){
    int indiceMaior = 0;
    for(int i = 1; i < nAlunos; i++){
        if(pNotas[i] > pNotas[indiceMaior]){
            indiceMaior = i;
        }
    }
    return indiceMaior;
}

int encontrarMenor(float *pNotas, int nAlunos){
    int indiceMenor = 0;
    for(int i = 1; i < nAlunos; i++){
        if(pNotas[i] < pNotas[indiceMenor]){
            indiceMenor = i;
        }
    }
    return indiceMenor;
}

int acimaDaMedia(float *pNotas, int nAlunos, float media){
    int nAcima = 0;
    for (int i = 0; i < nAlunos; i++){
        if(pNotas[i] > media){
            nAcima++;
        }
    }
    return nAcima;
}

float encontrarMediana(float *pNotas, int nAlunos){
    //criar copia das notas
    float *pNotasCopia = (float *)malloc(nAlunos * sizeof(float));
    if(pNotasCopia == NULL){
        printf("Erro ao alocar memória para a copia das notas\n");
        free(pNotas);
        exit(1);
    }
    for(int i = 0; i < nAlunos; i++){
        pNotasCopia[i] = pNotas[i];
    }
    //ordenar a copia das notas
    for(int i = 0; i < nAlunos - 1; i++){
        int indiceMenor = i;
        for(int j = i + 1; j < nAlunos; j++){
            if(pNotasCopia[j] < pNotasCopia[indiceMenor]){
                indiceMenor = j;
            }
        }

        float temp = pNotasCopia[indiceMenor];
        pNotasCopia[indiceMenor] = pNotasCopia[i];
        pNotasCopia[i] = temp;
    }
    //calcular a mediana
    float mediana;
    if(nAlunos % 2 == 0){
        mediana = (pNotasCopia[nAlunos / 2 - 1] + pNotasCopia[nAlunos / 2]) / 2;
    }else{
        mediana = pNotasCopia[(nAlunos / 2)];
    }
    free(pNotasCopia);
    return mediana;
}

float encontrarModa(float *pNotas, int nAlunos){
    float moda = pNotas[0];
    int maxAtual = 1;
    for(int i = 0; i < nAlunos; i++){
        int qtdAtual = 1;
        for(int j = i + 1; j < nAlunos; j++){
            if(pNotas[i] == pNotas[j]){
                qtdAtual++;
            }
        }
        if(qtdAtual > maxAtual){
            maxAtual = qtdAtual;
            moda = pNotas[i];
        }else if(qtdAtual == maxAtual && pNotas[i] != moda){
            moda = -1; //nao tem moda unica
        }
    }
    return moda;
}