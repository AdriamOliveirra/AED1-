#include <stdio.h>
int main(){

    int vida = 100;
int tesouro = 0;
int *pVida = &vida;
int *pTesouro = &tesouro;
printf("estado inicial: \n");
printf("Vida:%d\n", vida); 
printf("Tesouro; %d\n", tesouro);
*pVida = *pVida - 20;
printf("Depois do dano:\n");
printf("Vida: %d\n", vida);
printf("Tesouro; %d\n", tesouro);
printf("Restaurando vida:\n");
*pVida = *pVida + 20;
printf("Vida: %d\n\n", vida);
printf("Tesouro; %d\n", tesouro);
printf("Ativando tesouro: \n");
*pTesouro = 1;
printf("Tesouro; %d\n", tesouro);
return 0;
}
