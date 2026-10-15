#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para os Jogadores
typedef struct {
    int id;
    char nome[50];
    int pontuacao;
} Jogador;

// Estrutura para contagem de comparações e trocas
typedef struct {
    int comparacoes;
    int trocas;
} Metricas;

// --- 1. ORDENAÇÃO DE VETOR NUMÉRICO ---

// Encontra o índice do menor elemento a partir de 'inicio'
int encontrarMinimoInt(int arr[], int inicio, int n, Metricas *m) {
    int idxMin = inicio;
    for (int j = inicio + 1; j < n; j++) {
        m->comparacoes++;
        if (arr[j] < arr[idxMin]) {
            idxMin = j;
        }
    }
    return idxMin;
}

// Selection Sort para inteiros
void selectionSortInt(int arr[], int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;

    for (int i = 0; i < n - 1; i++) {
        int idxMin = encontrarMinimoInt(arr, i, n, m);
        
        if (idxMin != i) {
            int temp = arr[i];
            arr[i] = arr[idxMin];
            arr[idxMin] = temp;
            m->trocas++;
        }
    }
}

// --- 2. ORDENAÇÃO DE JOGADORES COM DESEMPATE ---

// Compara dois jogadores: prioriza a pontuação (crescente)
// Em caso de empate, usa o nome (ou ID) como critério de desempate[cite: 1]
int compararJogadores(Jogador a, Jogador b) {
    if (a.pontuacao != b.pontuacao) {
        return a.pontuacao - b.pontuacao; // Menor pontuação vem primeiro
    }
    // Desempate por nome (ordem alfabética)[cite: 1]
    int resNome = strcmp(a.nome, b.nome);
    if (resNome != 0) {
        return resNome;
    }
    // Desempate por ID caso os nomes também sejam iguais[cite: 1]
    return a.id - b.id;
}

// Encontra o menor jogador a partir da posição 'inicio'[cite: 1]
int encontrarMinimoJogador(Jogador arr[], int inicio, int n, Metricas *m) {
    int idxMin = inicio;
    for (int j = inicio + 1; j < n; j++) {
        m->comparacoes++;
        if (compararJogadores(arr[j], arr[idxMin]) < 0) {
            idxMin = j;
        }
    }
    return idxMin;
}

// Selection Sort para a estrutura de Jogadores[cite: 1]
void selectionSortJogadores(Jogador arr[], int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;

    for (int i = 0; i < n - 1; i++) {
        int idxMin = encontrarMinimoJogador(arr, i, n, m);
        
        if (idxMin != i) {
            // Troca a estrutura inteira[cite: 1]
            Jogador temp = arr[i];
            arr[i] = arr[idxMin];
            arr[idxMin] = temp;
            m->trocas++;
        }
    }
}

// --- FUNÇÕES AUXILIARES DE IMPRESSÃO ---

void imprimirVetorInt(const char *titulo, int arr[], int n) {
    printf("%s: [ ", titulo);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void imprimirJogadores(const char *titulo, Jogador arr[], int n) {
    printf("\n--- %s ---\n", titulo);
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Nome: %-10s | Pontos: %d\n", arr[i].id, arr[i].nome, arr[i].pontuacao);
    }
}

// --- MAIN ---

int main() {
    Metricas metricas;

    // ----------------------------------------------------
    // TESTE 1: Vetor de Inteiros
    // ----------------------------------------------------
    int origInt[] = {64, 25, 12, 22, 11};
    int nInt = sizeof(origInt) / sizeof(origInt[0]);
    
    // Cópia de trabalho para preservar a entrada original[cite: 1]
    int copiaInt[nInt];
    memcpy(copiaInt, origInt, sizeof(origInt));

    selectionSortInt(copiaInt, nInt, &metricas);

    printf("=== TESTE COM VETOR INTEIRO ===\n");
    imprimirVetorInt("Original", origInt, nInt);
    imprimirVetorInt("Ordenado", copiaInt, nInt);
    printf("Métricas -> Comparações: %d | Trocas: %d\n\n", metricas.comparacoes, metricas.trocas);

    // ----------------------------------------------------
    // TESTE 2: Vetor de Estruturas (Jogadores)
    // ----------------------------------------------------
    Jogador origJogadores[] = {
        {101, "Carlos", 150},
        {102, "Ana",    200},
        {103, "Bruno",  150}, // Empate em pontos com Carlos, desempata pelo nome ("Bruno" < "Carlos")[cite: 1]
        {104, "Ana",    150}, // Empate em pontos com Carlos e Bruno, desempata pelo nome ("Ana" < "Bruno")[cite: 1]
        {105, "Diana",  100}
    };
    int nJogadores = sizeof(origJogadores) / sizeof(origJogadores[0]);

    // Cópia de trabalho[cite: 1]
    Jogador copiaJogadores[nJogadores];
    memcpy(copiaJogadores, origJogadores, sizeof(origJogadores));

    selectionSortJogadores(copiaJogadores, nJogadores, &metricas);

    printf("=== TESTE COM ESTRUTURA DE JOGADORES ===");
    imprimirJogadores("Vetor Original (Preservado)", origJogadores, nJogadores);
    imprimirJogadores("Vetor Ordenado", copiaJogadores, nJogadores);
    printf("\nMétricas -> Comparações: %d | Trocas: %d\n", metricas.comparacoes, metricas.trocas);

    return 0;
}