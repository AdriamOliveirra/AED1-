#include <stdio.h>

#define MAX_PLATAFORMAS 10

// --- Funcoes Anteriores ---
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

// --- Funcoes da Atividade 04 ---
void ler_mapa(int *mapa, int tamanho) {
    printf("--- CONFIGURACAO DO MAPA ---\n");
    for (int i = 0; i < tamanho; i++) {
        int valor;
        do {
            printf("Informe o valor da plataforma %d (>= 0): ", i + 1);
            scanf("%d", &valor);
            
            if (valor < 0) {
                printf("Valor invalido! Tente um valor maior ou igual a zero.\n");
            }
        } while (valor < 0);

        // Aritmetica de ponteiros para salvar o valor lido
        *(mapa + i) = valor;
    }
}

void mostrar_mapa(const int *mapa, int tamanho) {
    printf("\n--- EXIBINDO O MAPA ---\n");
    for (int i = 0; i < tamanho; i++) {
        // Aritmetica de ponteiros para ler o elemento sem modificar o vetor
        int valor = *(mapa + i);
        const int *endereco = mapa + i;
        
        printf("Plataforma %d -> Endereco: %p | Impulso/Pontos: %d\n", i + 1, (void*)endereco, valor);
    }
}

int main() {
    int vida = 100;
    int pontuacao = 250;
    int plataformas[MAX_PLATAFORMAS];
    int tamanho = 0;

    // Leitura e validacao do tamanho do mapa
    do {
        printf("Digite a quantidade de plataformas (entre 1 e %d): ", MAX_PLATAFORMAS);
        scanf("%d", &tamanho);
        
        if (tamanho < 1 || tamanho > MAX_PLATAFORMAS) {
            printf("Tamanho invalido! Digite um numero dentro do limite.\n");
        }
    } while (tamanho < 1 || tamanho > MAX_PLATAFORMAS);

    // Entrada dos dados via funcao
    ler_mapa(plataformas, tamanho);

    // Saida dos dados via funcao
    mostrar_mapa(plataformas, tamanho);

    // Exploracao completa (acumulando pontos/altura do percurso)
    int soma_pontos = 0;
    for (int i = 0; i < tamanho; i++) {
        soma_pontos += *(plataformas + i);
    }

    pontuacao += soma_pontos;

    printf("\nTotal coletado nas plataformas: %d\n", soma_pontos);
    printf("Pontuacao atualizada: %d\n\n", pontuacao);

    // Teste das acoes do jogador
    printf("--- ACOES DO JOGADOR ---\n");
    aplicar_dano(&vida, 30);
    printf("Vida apos dano: %d\n", vida);

    restaurar_vida(&vida);
    printf("Vida apos cura: %d\n", vida);

    aplicar_pontuacao_dupla(&pontuacao);
    printf("Pontuacao final: %d\n", pontuacao);

    return 0;
}