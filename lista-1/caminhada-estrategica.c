#include <stdio.h>

int main(){
    int x, y, quad_evitado, quad;
    int passos_x, passos_y;

    scanf("%d %d %d", &x, &y, &quad_evitado);

    if(x > 0 && y > 0){
        quad = 1;
        passos_x = x + 1; // + 1 pois sempre se quer chegar ao ponto (1, 1) do quadrante diagonalmente oposto
        passos_y = y + 1;
    }else if(x < 0 && y > 0){
        quad = 2;
        passos_x = -x + 1;
        passos_y = y + 1;
    }else if(x < 0 && y < 0){
        quad = 3;
        passos_x = -x + 1;
        passos_y = -y + 1;
    }else if(x > 0 && y < 0){
        quad = 4;
        passos_x = x + 1;
        passos_y = -y + 1;
    }
    //if e else para determinar a ordem de passos para evitar o quadrante indicado em cada combinação possível
    if(quad == 1 && quad_evitado == 2){ 
        printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
    }else if(quad == 1 && quad_evitado == 4){
        printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
    }else if(quad == 2 && quad_evitado == 1){
        printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
    }else if(quad == 2 && quad_evitado == 3){
        printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
    }else if(quad == 3 && quad_evitado == 2){
        printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
    }else if(quad == 3 && quad_evitado == 4){
        printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
    }else if(quad == 4 && quad_evitado == 1){
        printf("%d passos em x e %d passos em y\n", passos_x, passos_y);
    }else if(quad == 4 && quad_evitado == 3){
        printf("%d passos em y e %d passos em x\n", passos_y, passos_x);
    }else{
        printf("caminhada invalida\n");
    }
    //também poderia ser usado um switch case
    return 0;
}