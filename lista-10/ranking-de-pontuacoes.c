#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int pontuacao;

    struct No *left;
    struct No *right;
}No;

// ============================== funcao inserir ==============================
No* inserir(No *raiz, int valor);

// ============================== funcoes de percurso ==============================
void preOrdem(No *raiz);
void emOrdem(No *raiz);
void posOrdem(No *raiz);

// ============================== funcoes de informacao ==============================
int contarNos(No *raiz);
int contarFolhas(No *raiz);
int altura(No *raiz);
int menorValor(No *raiz);
int maiorValor(No *raiz);

// ============================== limpeza de memoria ==============================
void liberarArvore(No *raiz);

// ============================== main ==============================
int main(){
    int numero;
    No *raiz = NULL;

    // preenchendo a arvore
    do{
        scanf("%d", &numero);
        if(numero != -1){
            raiz = inserir(raiz, numero);
        }
    }while(numero != -1);

    // printando as informacoes
    if(raiz == NULL){
        printf("ARVORE VAZIA\n");
        return 0;
    }
    
    printf("PREORDEM: ");
    preOrdem(raiz);
    printf("\nEMORDEM: ");
    emOrdem(raiz);
    printf("\nPOSORDEM: ");
    posOrdem(raiz);
    printf("\nNOS: %d\n", contarNos(raiz));
    printf("FOLHAS: %d\n", contarFolhas(raiz));
    printf("ALTURA: %d\n", altura(raiz));
    printf("MENOR: %d\n", menorValor(raiz));
    printf("MAIOR: %d\n", maiorValor(raiz));

    liberarArvore(raiz);
    raiz = NULL;
    return 0;
}

No* inserir(No *raiz, int valor){
    // caso raiz (ou no atual) esteja vazia, cria o novo no
    if(raiz == NULL){
        No *novo = (No*)malloc(sizeof(No));
        novo->pontuacao = valor;
        novo->left = NULL;
        novo->right = NULL;
        return novo;
    }
    // caso a raiz ja exista, compara o valor com o valor da raiz
    if(valor < raiz->pontuacao){
        raiz->left = inserir(raiz->left, valor);
    }else if(valor > raiz->pontuacao){
        raiz->right = inserir(raiz->right, valor);
    }
    return raiz;
}

void preOrdem(No *raiz){
    if(raiz != NULL){
        printf("%d ", raiz->pontuacao); // printa o no atual
        preOrdem(raiz->left); // percorre a esquerda
        preOrdem(raiz->right); // percorre a direita
    }
}

void emOrdem(No *raiz){
    if(raiz != NULL){
        emOrdem(raiz->left); // percorre a esquerda
        printf("%d ", raiz->pontuacao); // printa o no atual
        emOrdem(raiz->right); // percorre a direita
    }
}

void posOrdem(No *raiz){
    if(raiz != NULL){
        posOrdem(raiz->left); // percorre a esquerda
        posOrdem(raiz->right); // percorre a direita
        printf("%d ", raiz->pontuacao); // printa o no atual
    }
}

int contarNos(No *raiz){
    if(raiz == NULL){ // caso a arvore esteja vazia ou o no atual seja nulo
        return 0;
    }
    return 1 + contarNos(raiz->left) + contarNos(raiz->right); // conta o no atual + esquerda + direita
}

int contarFolhas(No *raiz){
    if(raiz == NULL){ // caso a arvore esteja vazia ou o no atual seja nulo
        return 0;
    }
    if(raiz->left == NULL && raiz->right == NULL){ // caso o no atual seja uma folha (nao tem filhos)
        return 1;
    }
    return contarFolhas(raiz->left) + contarFolhas(raiz->right); // conta as folhas da esquerda + direita
}

int altura(No *raiz){
    if(raiz == NULL){ // caso a arvore esteja vazia ou o no atual seja nulo
        return -1; // altura de uma árvore vazia é -1
    }
    int alturaEsquerda = altura(raiz->left); // altura da subárvore esquerda
    int alturaDireita = altura(raiz->right); // altura da subárvore direita
    return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita); // maior altura entre esquerda e direita + 1 para o ultimo no
}

int menorValor(No *raiz){
    if(raiz == NULL){ // caso a arvore esteja vazia ou o no atual seja nulo
        return -1;
    }
    No *atual = raiz;
    while(atual->left != NULL){
        atual = atual->left;
    }
    return atual->pontuacao; // encontra o no mais a esquerda (menor valor em uma arvore)
}

int maiorValor(No *raiz){
    if(raiz == NULL){
        return -1;
    }
    No *atual = raiz;
    while(atual->right != NULL){
        atual = atual->right;
    }
    return atual->pontuacao; // encontra o no mais a direita (maior valor em uma arvore)
}

void liberarArvore(No *raiz){
    if(raiz != NULL){
        liberarArvore(raiz->left); // libera todos os nos da esquerda
        liberarArvore(raiz->right); // libera todos os nos da direita
        free(raiz); // libera a raiz ou no atual
    }
}