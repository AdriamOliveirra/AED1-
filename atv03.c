#include <stdio.h>

void aplicar_dano(int *vida, int dano) {
    if (vida != NULL) {
        *vida -= dano;
    }
}

void restaurar_vida(int *vida) {
    if (vida != NULL) {
        *vida += 15;
    }
}

void aplicar_pontuacao_dupla(int *pontuacao) {
    if (pontuacao != NULL) {
        *pontuacao *= 2;
    }
}

int main() {
    int vida = 100;
    int pontuacao = 250;

    // Vetor com 5 plataformas (pontos/impulso de altura)
    int plataformas[5] = {10, 25, 5, 50, 15};
    int soma_pontos = 0;
    int altura_total = 0;

    printf("--- EXPLORANDO AS PLATAFORMAS ---\n");
    for (int i = 0; i < 5; i++) {
        /* 
           Aritmetica de ponteiros: quando somamos + i em (plataformas + i), o C avanca 
           i * sizeof(int) bytes na memoria. O deslocamento respeita o tipo do ponteiro (int = 4 bytes), 
           entao ele pula de 4 em 4 bytes para ir para o proximo elemento do vetor.
        */
        int valor = *(plataformas + i);
        int *endereco = plataformas + i;

        soma_pontos += valor;
        altura_total += valor; // acumulando a altura total do percurso

        printf("Indice %d -> Endereco: %p | Conteudo: %d\n", i, (void*)endereco, valor);
    }

    pontuacao += soma_pontos;

    printf("\nTotal de pontos coletados: %d\n", soma_pontos);
    printf("Altura total do percurso: %d\n", altura_total);
    printf("Pontuacao atual: %d\n\n", pontuacao);

    printf("--- ACOES DO JOGADOR ---\n");
    aplicar_dano(&vida, 30);
    printf("Vida apos dano: %d\n", vida);

    restaurar_vida(&vida);
    printf("Vida apos cura: %d\n", vida);

    aplicar_pontuacao_dupla(&pontuacao);
    printf("Pontuacao final: %d\n", pontuacao);

    return 0;
}