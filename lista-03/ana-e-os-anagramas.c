#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char string[101] = {0};
    fgets(string, 101, stdin);
    string[strcspn(string, "\n")] = 0; //remove o \n do final da string
    int n_pares = 0;

    //conta quantas palavras tem
    int n_palavras = 0;
    int is_palavra = 0; //ve se esta dentro de uma palavra ou nao
    for(int i = 0; string[i] != '\0'; i++){
        if(isalpha(string[i])){
            if(!is_palavra){
                n_palavras++;
                is_palavra = 1;
            }else{
                is_palavra = 0;
            }
        }
    }

    int j = 0;//variavel para auxiliar no loop principal
    int k;
    //loop principal
    for(int i = 0; i < n_palavras; i++){
        char palavra[101] = {0};//palavra atual para testar os pares
        while(string[j] != '\0' && !isalpha(string[j])){//enquanto o caractere atual for letra, modifica a palavra atual
            j++;
        }
        while(isalpha(string[j])){
            palavra[strlen(palavra)] = string[j];
            j++;
        }

        //possivel anagrama
        k = j; //não permite que salve palavras anteriores
        //for que testa todas as palavras menos as atuais e anteriores
        for(int teste = 0; teste < n_palavras - i; teste++){
            char palavra_teste[101] = {0};//palavra atual de teste

            while(string[k] != '\0' && !isalpha(string[k])){//enquanto o caractere atual for letra, modifica a palavra teste
                k++;
            }
            
            while(isalpha(string[k])){
                palavra_teste[strlen(palavra_teste)] = string[k];
                k++;
            }

            char temp_palavra[101] = {0};//salva as letras da palavra atual
            for(int a = 0; a < strlen(palavra); a++){
                temp_palavra[a] = palavra[a];//salva as letras da palavra atual
            }

            char temp_teste[101] = {0};
            for(int b = 0; b < strlen(palavra_teste); b++){
                temp_teste[b] = palavra_teste[b];//salva as letras da palavra teste atual
            }

            //testa se as letras sao iguais
            int tam_palavra = strlen(temp_palavra);
            int tam_teste = strlen(temp_teste);
            int iguais = 0; //letras iguais
            if(tam_palavra == tam_teste && tam_palavra > 0){
                for(int a = 0; a < tam_palavra; a++){
                    for(int b = 0; b < tam_teste; b++){
                        if(temp_teste[b] != 0 && tolower(temp_palavra[a]) == tolower(temp_teste[b])){
                            temp_teste[b] = 0;
                            iguais++;
                            break;
                        }
                    }
                }
            }
            if(iguais == tam_palavra && tam_palavra > 0){
                n_pares += 1;
                if(n_pares == 1){
                    printf("Pares de anagramas encontrados:\n");
                }
                printf("%s e %s\n", palavra, palavra_teste);
            }
        }
    }
    if(n_pares > 0){
            printf("\nTotal de pares: %d", n_pares);
    }else{
        printf("Nao existem anagramas na frase.");
    }
    return 0;
}