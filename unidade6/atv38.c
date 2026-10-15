#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para os Jogadores
typedef struct {
    int id;
    char nome[50];
    int pontuacao;
} Jogador;

// Estrutura de Métricas
typedef struct {
    int comparacoes;
} Metricas;

// --- 1. MERGE SORT PARA VETORES NUMÉRICOS ---

// Função de intercalação para inteiros utilizando memória auxiliar dinâmica
void intercalarInt(int arr[], int inicio, int meio, int fim, Metricas *m) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Alocação dinâmica de memória para vetores auxiliares
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[inicio + i];
    for (int j = 0; j < n2; j++) R[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = inicio;

    // Ordena e combina as duas metades sem perder elementos repetidos
    while (i < n1 && j < n2) {
        m->comparacoes++;
        if (L[i] <= R[j]) { // <= garante estabilidade para elementos repetidos
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // Copia os elementos restantes
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    // Libertar memória auxiliar dinâmica
    free(L);
    free(R);
}

void mergeSortInt(int arr[], int inicio, int fim, Metricas *m) {
    // Caso-base para intervalos com zero ou um elemento
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;

    // Chamadas recursivas para as duas metades
    mergeSortInt(arr, inicio, meio, m);
    mergeSortInt(arr, meio + 1, fim, m);

    // Intercalação dos resultados
    intercalarInt(arr, inicio, meio, fim, m);
}

// --- 2. MERGE SORT PARA ESTRUTURA DE JOGADORES ---

// Critério explícito aplicado às estruturas: Pontuação (decrescente) e Nome (crescente)
int compararJogadores(Jogador a, Jogador b) {
    if (a.pontuacao != b.pontuacao) {
        return b.pontuacao - a.pontuacao; // Maior pontuação primeiro
    }
    return strcmp(a.nome, b.nome); // Desempate por ordem alfabética do nome
}

// Intercalação para Jogadores utilizando memória auxiliar dinâmica
void intercalarJogadores(Jogador arr[], int inicio, int meio, int fim, Metricas *m) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Alocação dinâmica de memória auxiliar
    Jogador *L = (Jogador *)malloc(n1 * sizeof(Jogador));
    Jogador *R = (Jogador *)malloc(n2 * sizeof(Jogador));

    for (int i = 0; i < n1; i++) L[i] = arr[inicio + i];
    for (int j = 0; j < n2; j++) R[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        m->comparacoes++;
        if (compararJogadores(L[i], R[j]) <= 0) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    // Libertar memória auxiliar dinâmica
    free(L);
    free(R);
}

void mergeSortJogadores(Jogador arr[], int inicio, int fim, Metricas *m) {
    // Caso-base
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;

    mergeSortJogadores(arr, inicio, meio, m);
    mergeSortJogadores(arr, meio + 1, fim, m);

    intercalarJogadores(arr, inicio, meio, fim, m);
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
        printf("ID: %-3d | Nome: %-10s | Pontuação: %d\n", arr[i].id, arr[i].nome, arr[i].pontuacao);
    }
}

// --- MAIN / CENTRAL DE TESTES ---

int main() {
    Metricas metricasInt = {0};
    Metricas metricasJogadores = {0};

    // TESTE 1: Vetor Numérico (incluindo elementos repetidos)
    int numerosOriginal[] = {38, 27, 43, 3, 9, 82, 10, 27};
    int nNumeros = sizeof(numerosOriginal) / sizeof(numerosOriginal[0]);

    int numerosCopia[nNumeros];
    memcpy(numerosCopia, numerosOriginal, sizeof(numerosOriginal));

    mergeSortInt(numerosCopia, 0, nNumeros - 1, &metricasInt);

    printf("=================================================\n");
    printf("     MERGE SORT: VETOR NUMÉRICO COM REPETIÇÃO    \n");
    printf("=================================================\n");
    imprimirVetorInt("Entrada Original", numerosOriginal, nNumeros);
    imprimirVetorInt("Saída Ordenada  ", numerosCopia, nNumeros);
    printf("Métricas -> Comparações na Intercalação: %d\n\n", metricasInt.comparacoes);

    // TESTE 2: Estruturas de Jogadores
    Jogador jogadoresOriginal[] = {
        {101, "Carlos", 150},
        {102, "Ana",    200},
        {103, "Bruno",  150}, // Empate em pontos com Carlos (Ana e Bruno desempatam por nome)
        {104, "Ana",    150},
        {105, "Diana",  100},
        {106, "Eduardo",200}  // Empate em pontos com Ana
    };
    int nJogadores = sizeof(jogadoresOriginal) / sizeof(jogadoresOriginal[0]);

    Jogador jogadoresCopia[nJogadores];
    memcpy(jogadoresCopia, jogadoresOriginal, sizeof(jogadoresOriginal));

    mergeSortJogadores(jogadoresCopia, 0, nJogadores - 1, &metricasJogadores);

    printf("=================================================\n");
    printf("   MERGE SORT: REGISTOS DE JOGADORES (CENTRAL)   \n");
    printf("=================================================\n");
    imprimirJogadores("Entrada Original (Preservada)", jogadoresOriginal, nJogadores);
    imprimirJogadores("Saída Ordenada (Pontuação Desc, Nome Asc)", jogadoresCopia, nJogadores);
    printf("\nMétricas -> Comparações na Intercalação: %d\n", metricasJogadores.comparacoes);

    return 0;
}