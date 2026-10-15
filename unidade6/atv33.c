#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para os Jogadores
typedef struct {
    int id;
    char nome[50];
    int pontuacao;
} Jogador;

// Estrutura para contagem de comparações e deslocamentos
typedef struct {
    int comparacoes;
    int deslocamentos;
} Metricas;

// --- 1. INSERTION SORT PARA VETOR NUMÉRICO ---

// Função auxiliar que insere um elemento no prefixo ordenado
void inserirNoPrefixoInt(int arr[], int pos, Metricas *m) {
    int chave = arr[pos]; // Guardar temporariamente o valor inserido
    int j = pos - 1;

    // Respeitar o limite inferior (j >= 0) durante a busca da posição
    while (j >= 0) {
        m->comparacoes++;
        if (arr[j] > chave) {
            arr[j + 1] = arr[j]; // Deslocar elementos maiores sem sobrescrevê-los
            m->deslocamentos++;
            j--;
        } else {
            break; // Encontrou a posição correta
        }
    }
    arr[j + 1] = chave; // Encaixa o valor na posição correta
}

// Insertion Sort para inteiros
void insertionSortInt(int arr[], int n, Metricas *m) {
    m->comparacoes = 0;
    m->deslocamentos = 0;

    for (int i = 1; i < n; i++) {
        inserirNoPrefixoInt(arr, i, m);
    }
}

// --- 2. INSERTION SORT PARA ESTRUTURA DE JOGADORES ---

// Função de comparação entre dois jogadores
int compararJogadores(Jogador a, Jogador b) {
    if (a.pontuacao != b.pontuacao) {
        return a.pontuacao - b.pontuacao; // Menor pontuação vem primeiro
    }
    int resNome = strcmp(a.nome, b.nome); // Desempate por nome
    if (resNome != 0) {
        return resNome;
    }
    return a.id - b.id; // Desempate por ID
}

// Insere uma estrutura de jogador no prefixo ordenado
void inserirNoPrefixoJogador(Jogador arr[], int pos, Metricas *m) {
    Jogador chave = arr[pos]; // Guardar temporariamente a estrutura
    int j = pos - 1;

    while (j >= 0) {
        m->comparacoes++;
        if (compararJogadores(arr[j], chave) > 0) {
            arr[j + 1] = arr[j]; // Desloca a estrutura inteira
            m->deslocamentos++;
            j--;
        } else {
            break;
        }
    }
    arr[j + 1] = chave;
}

// Insertion Sort para Jogadores
void insertionSortJogadores(Jogador arr[], int n, Metricas *m) {
    m->comparacoes = 0;
    m->deslocamentos = 0;

    for (int i = 1; i < n; i++) {
        inserirNoPrefixoJogador(arr, i, m);
    }
}

// --- FUNÇÕES AUXILIARES DE IMPRESSÃO E VALIDAÇÃO ---

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

int validarResultadoInt(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) return 0;
    }
    return 1;
}

int validarResultadoJogadores(Jogador arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (compararJogadores(arr[i], arr[i + 1]) > 0) return 0;
    }
    return 1;
}

// --- MAIN ---

int main() {
    Metricas metricas;

    // TESTE 1: Vetor de Inteiros
    int origInt[] = {64, 25, 12, 22, 11};
    int nInt = sizeof(origInt) / sizeof(origInt[0]);
    
    int copiaInt[nInt];
    memcpy(copiaInt, origInt, sizeof(origInt));

    insertionSortInt(copiaInt, nInt, &metricas);

    printf("=== INSERTION SORT: VETOR INTEIRO ===\n");
    imprimirVetorInt("Original", origInt, nInt);
    imprimirVetorInt("Ordenado", copiaInt, nInt);
    printf("Métricas -> Comparações: %d | Deslocamentos: %d\n", metricas.comparacoes, metricas.deslocamentos);
    printf("Validação do Resultado Final: %s\n\n", validarResultadoInt(copiaInt, nInt) ? "SUCESSO (Ordenado)" : "FALHA");

    // TESTE 2: Estrutura de Jogadores
    Jogador origJogadores[] = {
        {101, "Carlos", 150},
        {102, "Ana",    200},
        {103, "Bruno",  150},
        {104, "Ana",    150},
        {105, "Diana",  100}
    };
    int nJogadores = sizeof(origJogadores) / sizeof(origJogadores[0]);

    Jogador copiaJogadores[nJogadores];
    memcpy(copiaJogadores, origJogadores, sizeof(origJogadores));

    insertionSortJogadores(copiaJogadores, nJogadores, &metricas);

    printf("=== INSERTION SORT: ESTRUTURA DE JOGADORES ===");
    imprimirJogadores("Vetor Original (Preservado)", origJogadores, nJogadores);
    imprimirJogadores("Vetor Ordenado", copiaJogadores, nJogadores);
    printf("\nMétricas -> Comparações: %d | Deslocamentos: %d\n", metricas.comparacoes, metricas.deslocamentos);
    printf("Validação do Resultado Final: %s\n", validarResultadoJogadores(copiaJogadores, nJogadores) ? "SUCESSO (Ordenado)" : "FALHA");

    return 0;
}