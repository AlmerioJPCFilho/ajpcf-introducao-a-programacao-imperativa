#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// ============================== estrutura de dados ==============================
// representa um aluno
typedef struct No{
    long long int mat; // 11 digitos
    int pri; // 1 - 3
    float cr; // 0.00 - 10.00
    int L; // segundo de chegada 1 - 10^9
    int R; // L+1 - 10^9
    int score; // (int)round(cr * 100) / pri

    struct No *proximo;
} No;

typedef struct Fila{
    No *inicio;
    No *fim;
} Fila;

// ============================== funcoes para manipular a fila ==============================
void inicializarFila(Fila *f);
void enqueue(Fila *f, long long int mat, int pri, float cr, int L, int R);
No dequeue(Fila *f);

// ============================== main ==============================
int main(){
    Fila requisicoes; // fila para processamento
    Fila confirmados; // fila para printar os alunos processados
    inicializarFila(&requisicoes);
    inicializarFila(&confirmados);

    char comando[20];
    char disciplina[50];
    int vagas;
    int tempoAtual = 1;

    while(scanf("%s", comando) != EOF){
        if(strcmp(comando, "START") == 0){
            scanf("%s %d", disciplina, &vagas);
        }else if(strcmp(comando, "ADD") == 0){
            long long int mat;
            int pri, L, R;
            float cr;
            scanf("%lld %d %f %d %d", &mat, &pri, &cr, &L, &R);
            // adiciona o aluno ao fim da fila
            enqueue(&requisicoes, mat, pri, cr, L, R);
        }else if(strcmp(comando, "PROC") == 0){
            int qtd;
            scanf("%d", &qtd);
            for(int i = 0; i < qtd; i++){
                // se a fila estiver vazia
                if(requisicoes.inicio == NULL){
                    break;
                }
                // remove o primeiro da fila
                No aluno = dequeue(&requisicoes);
                if(tempoAtual < aluno.L){
                    tempoAtual = aluno.L;
                }
                // se o tempo passar do limite, o aluno e desconectado e nao e processado
                if(tempoAtual > aluno.R){
                    printf("[TIMEOUT] mat=%lld | Desconectado da fila.\n", aluno.mat);
                }else{
                    if(vagas > 0){
                        printf("[ALOCADO] mat=%lld | score=%d | Processado no seg: %d\n", aluno.mat, aluno.score, tempoAtual);
                        vagas--;
                        enqueue(&confirmados, aluno.mat, aluno.pri, aluno.cr, aluno.L, aluno.R);
                    }else{
                        printf("[LOTADO] mat=%lld | score=%d | Processado no seg: %d\n", aluno.mat, aluno.score, tempoAtual);
                    }

                    tempoAtual++;
                }
            }
        }else if(strcmp(comando, "FIM") == 0){
            printf("--- LISTA OFICIAL: %s ---\n", disciplina);
            int posicao = 1;
            while(confirmados.inicio != NULL){
                No aluno = dequeue(&confirmados);
                printf("%d. Matricula: %lld\n", posicao, aluno.mat);
                posicao++;
            }
            break;
        }
    }

    return 0;
}

// ============================== funcoes para manipular a fila ==============================
void inicializarFila(Fila *f){
    f->inicio = NULL;
    f->fim = NULL;
}

void enqueue(Fila *f, long long int mat, int pri, float cr, int L, int R){
    No *novo = (No*)malloc(sizeof(No));
    novo->mat = mat;
    novo->pri = pri;
    novo->cr = cr;
    novo->L = L;
    novo->R = R;
    novo->score = (int)round(cr * 100) / pri;
    novo->proximo = NULL;
    if(f->fim == NULL){ // fila vazia
        f->inicio = novo;
        f->fim = novo;
    }else{ // fila nao vazia
        f->fim->proximo = novo; // atualiza o ultimo para apontar para o novo
        f->fim = novo; // atualiza o ultimo para ser o novo
    }
}

No dequeue(Fila *f){
    No aluno;
    if(f->inicio == NULL){ // fila vazia
        aluno.mat = -1;
        return aluno;
    }

    No *temp = f->inicio;
    aluno = *temp; // copia o primeiro da fila
    f->inicio = temp->proximo; // o segundo vira o primeiro

    if(f->inicio == NULL){ // se a fila ficou vazia depois de remover o primeiro
        f->fim = NULL;
    }

    free(temp);

    return aluno;
}