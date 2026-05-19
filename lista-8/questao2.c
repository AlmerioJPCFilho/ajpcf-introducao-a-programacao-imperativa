#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// ============================== criando a struct e union ==============================
typedef struct{
    uint32_t id             : 10; // 0 ... 1023
    uint32_t status         : 3; // 0... 7
    uint32_t bateriaBaixa   : 1; // 0 = normal, 1 = critico
    int32_t temperatura     : 12; // complemento de 2
    uint32_t controle       : 6; // erro
} Separado;

typedef union{
    uint32_t dadoBruto; // 32 bits sem sinal

    Separado separado; // struct com os dados separados    
} Pacote;

// ============================== main ==============================
int main(){
    int tamanho = 1;
    int qtdPacotes = 0;

    Pacote *pPacotes = malloc(tamanho * sizeof(Pacote));
    if(pPacotes == NULL){
        printf("Erro ao alocar memoria\n");
        exit(1);
    }

    // ============================== leitura dos dados ==============================
    uint32_t inputHex; // input em hexadecimal
    while(scanf("%x", &inputHex) == 1){ // while para poder parar quando o input for 0
        if(inputHex == 0){ // condicao de parada
            break;
        }

        if(qtdPacotes == tamanho){
            tamanho *= 2;
            // realoca a memoria
            Pacote *temp = realloc(pPacotes, tamanho * sizeof(Pacote));
            if(temp == NULL){
                printf("Erro ao realocar memoria\n");
                free(pPacotes);
                exit(1);
            }
            pPacotes = temp;
        }
        // salva o valor bruto
        pPacotes[qtdPacotes].dadoBruto = inputHex;
        qtdPacotes++;
    }

    // ============================== processamento dos dados ==============================
    for(int i = 0; i < qtdPacotes; i++){
        printf("Pacote [%d] - Dado Bruto: 0x%08X\n", (i + 1), pPacotes[i].dadoBruto);
        printf("ID do Sensor : %u\n", pPacotes[i].separado.id);
        printf("Status : %u\n", pPacotes[i].separado.status);
        printf("Bateria Baixa: %s\n", pPacotes[i].separado.bateriaBaixa ? "SIM (ALERTA)" : "Nao");
        printf("Temperatura : %d graus\n", pPacotes[i].separado.temperatura);
        printf("-------------------------------------------------\n");
    }

    //============================== liberacao de memoria ==============================
    free(pPacotes);
    
    return 0;
}