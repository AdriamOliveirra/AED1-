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

        *(mapa + i) = valor;
    }
}

void mostrar_mapa(const int *mapa, int tamanho) {
    printf("\n--- EXIBINDO O MAPA ---\n");
    for (int i = 0; i < tamanho; i++) {
        int valor = *(mapa + i);
        const int *endereco = mapa + i;
        printf("Plataforma %d -> Endereco: %p | Impulso/Pontos: %d\n", i + 1, (void*)endereco, valor);
    }
}

// --- Funcao da Atividade 05: Exploracao com Cursor (Ponteiro Auxiliar) ---
int explorar_mapa(const int *mapa, int tamanho) {
    printf("\n--- INICIANDO EXPLORACAO DO MAPA ---\n");
    
    /* 
       Comparacao: 
       Acesso por indice usa 'vetor[i]' calculando a posicao a partir da base (base + i * tamanho_tipo).
       Já o incremento de ponteiro ('cursor++') desloca o ponteiro diretamente para o proximo 
       endereco da memoria de forma continua, sem precisar multiplicar pelo indice a cada passo.
    */
    
    const int *cursor = mapa;             // Ponteiro auxiliar no inicio do vetor
    const int *limite = mapa + tamanho;   // Endereco imediatamente posterior ao ultimo elemento
    
    int pontos_coletados = 0;
    int posicao_logica = 1;

    // O laco termina exatamente ao alcancar o endereco limite
    while (cursor < limite) {
        int valor_atual = *cursor;
        pontos_coletados += valor_atual;

        printf("Posicao %d | Endereco: %p | Valor lido: %d | Pontos acumulados: %d\n", 
               posicao_logica, (void*)cursor, valor_atual, pontos_coletados);

        posicao_logica++;
        cursor++; // Incremento do ponteiro auxiliar para ir para a proxima plataforma
    }

    // Resumo do percurso ao terminar
    printf("\n=== RESUMO DO PERCURSO ===\n");
    printf("Total de plataformas percorridas: %d\n", tamanho);
    printf("Total de pontos acumulados no percurso: %d\n", pontos_coletados);

    return pontos_coletados;
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

    // Exploracao por incremento de ponteiro
    int pontos_mapa = explorar_mapa(plataformas, tamanho);
    pontuacao += pontos_mapa;

    printf("\nPontuacao atualizada do jogador: %d\n\n", pontuacao);

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