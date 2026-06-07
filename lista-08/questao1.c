#include <stdio.h>

// struct com os valores separados
typedef struct{
    unsigned char erro     : 1; // 0 = normal, 1 = falha
    unsigned char modo     : 3; // 0...7
    unsigned char leitura  : 4; // 0...15
} Separado;

// union para acessar de diferentes formas
typedef union{
    unsigned char byteBruto; // valor do input

    Separado valores; // vai receber os valores automaticamente quando setar "byteBruto"
} Status;

int main(){
    Status sensor;
    int input;

    scanf("%d", &input);
    sensor.byteBruto = (unsigned char)input;
    // acessa as variaveis (mesmo que elas nao tenham sido alteradas diretamente, elas recebem os valores corretos pois compartilham memoria com "byteBruto")
    printf("Byte bruto: %d | Erro: %d | Modo: %d | Leitura: %d\n", sensor.byteBruto, sensor.valores.erro, sensor.valores.modo, sensor.valores.leitura);

    return 0;
}