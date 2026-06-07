#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// manipulacao de matriz
int **alocarMatriz(int linhas, int colunas);
int **copiarMatriz(int **matriz, int linhas, int colunas);
void lerElementos(int **matriz, int linhas, int colunas);
void printarMatriz(int **matriz, int linhas, int colunas);
void liberarMatriz(int **matriz, int linhas);

// ataques
void EXPLOSAO_ARCANA(int **matriz, int linhas, int colunas, int iAtk, int jAtk);
void NUVEM_VENENOSA(int **matriz, int linhas, int colunas, int iAtk, int jAtk);

// aplicacao de ataques
void aplicarAtaque(int **matriz, int linhas, int colunas, int iAtk, int jAtk, char *ataque);
void dano(int **matriz, int linhas, int colunas, int j, int i, int danoIndividual);
int verificarVizinhosVivos(int **matriz, int linhas, int colunas, int iAtk, int jAtk);


int main(){
    int linhas, colunas;
    scanf("%d %d", &linhas, &colunas);
    int **mapaOriginal = alocarMatriz(linhas, colunas);

    lerElementos(mapaOriginal, linhas, colunas);
    // coordenadas do ataque, coluna e linha
    int jAtk, iAtk;
    scanf("%d %d", &jAtk, &iAtk);
    // tipo do ataque
    char ataque[20];
    scanf("%s", ataque);

    printf("Estado inicial do mapa:\n");
    printarMatriz(mapaOriginal, linhas, colunas);
    printf("\n");

    int **mapaCopia = copiarMatriz(mapaOriginal, linhas, colunas);

    aplicarAtaque(mapaCopia, linhas, colunas, jAtk, iAtk, ataque);

    liberarMatriz(mapaOriginal, linhas);
    liberarMatriz(mapaCopia, linhas);
    return 0;
}

// funcoes de manipulacao de matriz
int **alocarMatriz(int linhas, int colunas){
    int **matriz = (int **)malloc(linhas * sizeof(*matriz));
    if(matriz == NULL){
        printf("Erro ao alocar a matriz\n");
        exit(1);
    }
    for(int i = 0; i < linhas; i++){
        matriz[i] = (int *)malloc(colunas * sizeof(**matriz));
        if(matriz[i] == NULL){
            printf("Erro ao alocar linha %d\n", i);
            for(int j = 0; j < i; j++){
                free(matriz[j]);
            }
            free(matriz);
            exit(1);
        }
    }
    return matriz;
}

int **copiarMatriz(int **matriz, int linhas, int colunas){
    int **copia = alocarMatriz(linhas, colunas);
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            copia[i][j] = matriz[i][j];
        }
    }
    return copia;
}

void lerElementos(int **matriz, int linhas, int colunas){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            scanf(" %d", &matriz[i][j]);
        }
    }
}

void printarMatriz(int **matriz, int linhas, int colunas){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void liberarMatriz(int **matriz, int linhas){
    for(int i = 0; i < linhas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

// ataques
void EXPLOSAO_ARCANA(int **matriz, int linhas, int colunas, int iAtk, int jAtk){
    //camada 1(dano alto)
    int camada1[5][2] = {{jAtk, iAtk}, {jAtk-1, iAtk}, {jAtk+1, iAtk}, {jAtk, iAtk-1}, {jAtk, iAtk+1}}; // vetores de coordenadas da camada 1
    for(int i = 0; i < 5; i++){
        dano(matriz, linhas, colunas, camada1[i][0], camada1[i][1], 50);
    }
    //camada 2(dano reduzido)
    int camada2[16][2] = { // vetores de coordenadas da camada 2
        {jAtk-1, iAtk-1}, {jAtk+1, iAtk-1}, {jAtk-1, iAtk+1}, {jAtk+1, iAtk+1}, // diagonais
        {jAtk-2, iAtk}, {jAtk+2, iAtk}, {jAtk, iAtk-2}, {jAtk, iAtk+2}, // centros externos
        {jAtk-2, iAtk-1}, {jAtk-2, iAtk+1}, {jAtk+2, iAtk-1}, {jAtk+2, iAtk+1}, // cantos externos direita e esquerda
        {jAtk-1, iAtk-2}, {jAtk+1, iAtk-2}, {jAtk-1, iAtk+2}, {jAtk+1, iAtk+2} // cantos externos cima e baixo
    };
    for(int i = 0; i < 16; i++){
        dano(matriz, linhas, colunas, camada2[i][0], camada2[i][1], 25);
    }

    printf("Estado do mapa após usar a Explosão Arcana:\n");
    printarMatriz(matriz, linhas, colunas);
}

void NUVEM_VENENOSA(int **matriz, int linhas, int colunas, int iAtk, int jAtk){
    printf("Estado do mapa, por turno, após usar a Nuvem Venenosa:\n");
    //celulas afetadas
    int celulasAfetadas[21][2] = { // vetores de coordenadas das celulas afetadas
        {jAtk, iAtk}, {jAtk-1, iAtk}, {jAtk+1, iAtk}, {jAtk, iAtk-1}, {jAtk, iAtk+1}, // camada 1
        {jAtk-1, iAtk-1}, {jAtk+1, iAtk-1}, {jAtk-1, iAtk+1}, {jAtk+1, iAtk+1}, // diagonais
        {jAtk-2, iAtk}, {jAtk+2, iAtk}, {jAtk, iAtk-2}, {jAtk, iAtk+2}, // centros externos
        {jAtk-2, iAtk-1}, {jAtk-2, iAtk+1}, {jAtk+2, iAtk-1}, {jAtk+2, iAtk+1}, // cantos externos direita e esquerda
        {jAtk-1, iAtk-2}, {jAtk+1, iAtk-2}, {jAtk-1, iAtk+2}, {jAtk+1, iAtk+2} // cantos externos cima e baixo
    };

    for(int turno = 0; turno < 3; turno++){ 
        // contar vivos
        int vivos = 0;
        for(int k = 0; k < 21; k++){
            int j = celulasAfetadas[k][0];
            int i = celulasAfetadas[k][1];
            if(j >= 0 && j < colunas && i >= 0 && i < linhas && matriz[i][j] > 0){
                vivos++;
            }
        }
        if(vivos == 0){
            break;
        }

        // calcular dano em cada celula
        int danosIndividuais[21];
        for(int i = 0; i < 21; i++){
            int vizinhosVivos = verificarVizinhosVivos(matriz, linhas, colunas, celulasAfetadas[i][0], celulasAfetadas[i][1]);
            danosIndividuais[i] = 5 + (8 * vizinhosVivos);
        }
        // aplicar dano
        for(int i = 0; i < 21; i++){
            dano(matriz, linhas, colunas, celulasAfetadas[i][0], celulasAfetadas[i][1], danosIndividuais[i]);
        }

        printarMatriz(matriz, linhas, colunas);
        printf("\n");
    }
}

// aplicacao de ataques
void dano(int **matriz, int linhas, int colunas, int j, int i, int danoIndividual){
    if(j >= 0 && j < colunas && i >= 0 && i < linhas){
        matriz[i][j] = matriz[i][j] - danoIndividual;
        if(matriz[i][j] < 0){
            matriz[i][j] = 0;
        }
    }
}

int verificarVizinhosVivos(int **matriz, int linhas, int colunas, int j, int i){
    int vivos = 0;
    int vizinhos[8][2] = { // vetores de coordenadas dos vizinhos
        {j-1, i-1}, {j, i-1}, {j+1, i-1}, // cima
        {j-1, i}, {j+1, i}, // esquerda e direita
        {j-1, i+1}, {j, i+1}, {j+1, i+1} // baixo
    };
    for(int k = 0; k < 8; k++){
        int jVizinho = vizinhos[k][0];
        int iVizinho = vizinhos[k][1];
        if(jVizinho >= 0 && jVizinho < colunas && iVizinho >= 0 && iVizinho < linhas && matriz[iVizinho][jVizinho] > 0){
            vivos++;
        }
    }
    return vivos;
}

// funcao para aplicar o ataque escolhido usando ponteiro para funcao
void aplicarAtaque(int **matriz, int linhas, int colunas, int iAtk, int jAtk, char *ataque){
    void (*funcaoAtaque)(int **, int, int, int, int) = NULL;

    if(strcmp(ataque, "EXPLOSAO_ARCANA") == 0){
        funcaoAtaque = EXPLOSAO_ARCANA;
    }else if(strcmp(ataque, "NUVEM_VENENOSA") == 0){
        funcaoAtaque = NUVEM_VENENOSA;
    }

    if(funcaoAtaque != NULL){
        funcaoAtaque(matriz, linhas, colunas, iAtk, jAtk);
    }
}