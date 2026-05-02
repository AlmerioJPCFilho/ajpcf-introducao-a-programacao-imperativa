#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================== estruturas dos mecha ==============================
typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1;     // Atk: Dano Base   | Def: Blindagem Fixa | Utl: Recup. Base
    int atrib2;     // Atk: Custo Ener. | Def: Bônus de Slot   | Utl: Multiplicador
    
    // Função Modular: deve ser atribuída conforme o tipo do sistema.
    // m: ponteiro para o mecha dono do sistema.
    // slot: o índice da posição de entrada deste sistema no array sistemas[]
    // input: o dano base enviado pelo Wintermute para o combate.
    // output: onde deve ser gravado o resultado final da operação.
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;                // Identificador único (0 até N-1)
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;       // Contexto de dano enviado pelo Comando
    SubSistema sistemas[]; // O Flexible Array Member (FAM)
};

// ============================== subrotinas ==============================

void defesa(Mecha *m, int slot, int input, int *output);
void utilidade(Mecha *m, int slot, int input, int *output);
void ataque(Mecha *m, int slot, int input, int *output);

// ============================== funcao qsort ==============================

int compararMecha(const void *a, const void *b);

// ============================== main ==============================

int main(){
    int qtdMecha;
    scanf("%d", &qtdMecha);

    // aloca um array de ponteiros para os mechas
    Mecha **esquadrao = (Mecha **)malloc(qtdMecha * sizeof(Mecha *));
    if(esquadrao == NULL){
        printf("Erro ao alocar memória para o esquadrão de mechas\n");
        exit(1);
    }
    // configurar os mecha
    for(int i = 0; i < qtdMecha; i++){
        int id, energia_inicial, qtdSistemas;
        char modelo[50];

        scanf("%d %s %d %d", &id, modelo, &energia_inicial, &qtdSistemas);

        Mecha *novoMecha = (Mecha *)malloc(sizeof(Mecha) + (qtdSistemas * sizeof(SubSistema)));
        if(novoMecha == NULL){
            printf("Erro ao alocar memória para o mecha %d\n", id);
            for(int j = 0; j < i; j++){
                free(esquadrao[j]);
            }
            free(esquadrao);
            exit(1);
        }

        novoMecha->id = id;
        strcpy(novoMecha->modelo, modelo);
        novoMecha->energia_atual = energia_inicial;
        novoMecha->num_sistemas = qtdSistemas;

        // ler os sistemas
        for(int j = 0; j < qtdSistemas; j++){
            char tipo;
            scanf(" %c %s %d %d", &tipo, novoMecha->sistemas[j].nome, &novoMecha->sistemas[j].atrib1, &novoMecha->sistemas[j].atrib2);

            if(tipo == 'D'){
                novoMecha->sistemas[j].subrotina = defesa;
            }else if(tipo == 'U'){
                novoMecha->sistemas[j].subrotina = utilidade;
            }else if(tipo == 'A'){
                novoMecha->sistemas[j].subrotina = ataque;
            }
        }

        scanf("%d", &novoMecha->valor_wintermute);

        esquadrao[i] = novoMecha;
    }

    // ordenas os mecha por id
    qsort(esquadrao, qtdMecha, sizeof(Mecha *), compararMecha);

    // combate
    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for(int i = 0; i < qtdMecha; i++){
        Mecha *m = esquadrao[i];
        int input = m->valor_wintermute;

        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", m->id, m->modelo, m->energia_atual);

        // ver se tem defesa
        for(int j = 0; j < m->num_sistemas; j++){
            if(m->sistemas[j].subrotina == defesa){
                int danoSofrido;
                m->sistemas[j].subrotina(m, j, input, &danoSofrido);
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->sistemas[j].nome, danoSofrido);
            }
        }


        // ver se tem utilidade
        for(int j = 0; j < m->num_sistemas; j++){
            if(m->sistemas[j].subrotina == utilidade){
                int recuperado;
                m->sistemas[j].subrotina(m, j, input, &recuperado);
                printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->sistemas[j].nome, m->energia_atual);
            }
        }

        // ver se tem ataque
        for(int j = 0; j < m->num_sistemas; j++){
            if(m->sistemas[j].subrotina == ataque){
                int danoCausado;
                m->sistemas[j].subrotina(m, j, input, &danoCausado);
                
                if(danoCausado > 0){
                    printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", m->sistemas[j].nome, danoCausado, m->energia_atual);
                }else{
                    printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[j].nome);
                }
            }
        }

        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        printf("-----------------------------------------\n");
    }

    printf("Esquadrao pronto para o combate.\n");

    // liberar memoria
    for(int i = 0; i < qtdMecha; i++){
        free(esquadrao[i]);
    }
    free(esquadrao);

    return 0;
}

// ============================== subrotinas ==============================

void defesa(Mecha *m, int slot, int input, int *output){
    // DanoFinal = input - atrib1 - (slot * atrib2)
    *output = input - m->sistemas[slot].atrib1 - (slot * m->sistemas[slot].atrib2);
    if(*output < 0){
        *output = 0;
    }
}

void utilidade(Mecha *m, int slot, int input, int *output){
    // Recuperado = atrib1 + (slot * atrib2)
    int recuperado = m->sistemas[slot].atrib1 + (slot * m->sistemas[slot].atrib2);
    m->energia_atual += recuperado;
}

void ataque(Mecha *m, int slot, int input, int *output){
    int custo = m->sistemas[slot].atrib2;
    if(m->energia_atual >= custo){
        // Dano = atrib1 + energia_atual + slot - input
        *output = m->sistemas[slot].atrib1 + m->energia_atual + slot - input;
        m->energia_atual -= custo;
    }else{
        *output = 0;
    }
}

// ============================== funcao qsort ==============================

int compararMecha(const void *a, const void *b){
    Mecha *mechaA = *(Mecha **)a;
    Mecha *mechaB = *(Mecha **)b;

    // comparar ids
    return mechaA->id - mechaB->id;
}