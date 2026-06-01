#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================== structs ==============================
typedef struct Tarefa{
    int id;
    int prioridade; // 1 - 5

    struct Tarefa *proxima;
} Tarefa;

typedef struct{
    Tarefa *primeira;
    Tarefa *ultima;
} Fila;

// ============================== funcoes para manipular a fila ==============================
void inicializarFila(Fila *f);
void inserir(Fila *f, int id, int prioridade);
void remover(Fila *f);
void listar(Fila *f);

// ============================== main ==============================
int main(){
    Fila fila;
    inicializarFila(&fila);

    char comando;
    int id, prioridade;

    while(scanf(" %c", &comando) != EOF){
        if(comando == 'I'){
            scanf("%d %d", &id, &prioridade);
            inserir(&fila, id, prioridade);
        }else if(comando == 'R'){
            remover(&fila);
        }else if(comando == 'L'){
            listar(&fila);
        }else if(comando == 'F'){
            break;
        }
    }

    return 0;
}

void inicializarFila(Fila *f){
    f->primeira = NULL;
    f->ultima = NULL;
}

void inserir(Fila *f, int id, int prioridade){
    Tarefa *nova = (Tarefa*)malloc(sizeof(Tarefa));
    nova->id = id;
    nova->prioridade = prioridade;
    nova->proxima = NULL;

    if(f->ultima == NULL){ // fila vazia
        f->primeira = nova;
        f->ultima = nova;
    }else{ // fila nao vazia
        f->ultima->proxima = nova; // atualiza a ultima para apontar para a nova
        f->ultima = nova; // atualiza a ultima para ser a nova
    }
}


void remover(Fila *f){
    if(f->primeira == NULL){ // fila vazia
        printf("Fila vazia\n");
        return;
    }else{
        Tarefa *temp = f->primeira;
        f->primeira = temp->proxima; // a segunda vira a primeira
        if(f->primeira == NULL){ // se a fila ficou vazia depois de remover a primeira
            f->ultima = NULL;
        }
        printf("Removida: id=%d prioridade=%d\n", temp->id, temp->prioridade);
        free(temp);
    }
}

// lista todas as tarefas
void listar(Fila *f){
    Tarefa *atual = f->primeira;
    if(f->primeira == NULL){
        printf("Fila vazia\n");
        return;
    }

    while(atual != NULL){
        printf("id=%d prioridade=%d\n", atual->id, atual->prioridade);
        atual = atual->proxima;
    }
}