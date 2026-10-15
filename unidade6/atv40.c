#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para os Jogadores
typedef struct {
    int id;
    char nome[50];
    int pontuacao;
} Jogador;

// Estrutura para contagem de métricas operacionais
typedef struct {
    int comparacoes;
    int trocas;
    int deslocamentos;
} Metricas;

// --- FUNÇÃO DE COMPARAÇÃO DE JOGADORES ---

// Critério: Pontuação (decrescente) e Desempate por Nome/ID (crescente)
int compararJogadores(Jogador a, Jogador b) {
    if (a.pontuacao != b.pontuacao) {
        return b.pontuacao - a.pontuacao; // Maior pontuação primeiro
    }
    int resNome = strcmp(a.nome, b.nome);
    if (resNome != 0) {
        return resNome; // Desempate por nome alfabético
    }
    return a.id - b.id; // Desempate por ID
}

// --- 1. QUICK SORT RANDOMIZADO PARA ESTRUTURA DE JOGADORES ---

// Partição In-Place para Jogadores
int particionarJogadores(Jogador arr[], int inicio, int fim, Metricas *m) {
    Jogador pivo = arr[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        m->comparacoes++;
        if (compararJogadores(arr[j], pivo) <= 0) {
            i++;
            // Troca de estruturas inteiras
            Jogador temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            m->trocas++;
        }
    }

    Jogador temp = arr[i + 1];
    arr[i + 1] = arr[fim];
    arr[fim] = temp;
    m->trocas++;

    return i + 1;
}

// Escolhe um pivô aleatório dentro do subintervalo atual [inicio..fim]
int particionarRandomizado(Jogador arr[], int inicio, int fim, Metricas *m) {
    // Gerar um índice aleatório estritamente dentro do subintervalo
    int idxAleatorio = inicio + rand() % (fim - inicio + 1);

    // Coloca o pivô sorteado na posição esperada pela partição (fim)
    Jogador temp = arr[idxAleatorio];
    arr[idxAleatorio] = arr[fim];
    arr[fim] = temp;
    m->trocas++;

    return particionarJogadores(arr, inicio, fim, m);
}

void quickSortRandomizado(Jogador arr[], int inicio, int fim, Metricas *m) {
    if (inicio < fim) {
        int posPivo = particionarRandomizado(arr, inicio, fim, m);
        quickSortRandomizado(arr, inicio, posPivo - 1, m);
        quickSortRandomizado(arr, posPivo + 1, fim, m);
    }
}

// --- 2. ALGORITMOS AUXILIARES PARA COMPARAÇÃO ---

// Insertion Sort para Jogadores (Gera deslocamentos)
void insertionSortJogadores(Jogador arr[], int n, Metricas *m) {
    m->comparacoes = 0;
    m->deslocamentos = 0;
    m->trocas = 0;

    for (int i = 1; i < n; i++) {
        Jogador chave = arr[i];
        int j = i - 1;

        while (j >= 0) {
            m->comparacoes++;
            if (compararJogadores(arr[j], chave) > 0) {
                arr[j + 1] = arr[j];
                m->deslocamentos++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
    }
}

// Bubble Sort para Jogadores
void bubbleSortJogadores(Jogador arr[], int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    m->deslocamentos = 0;

    int houveTroca;
    for (int i = 0; i < n - 1; i++) {
        houveTroca = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            m->comparacoes++;
            if (compararJogadores(arr[j], arr[j + 1]) > 0) {
                Jogador temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                m->trocas++;
                houveTroca = 1;
            }
        }
        if (!houveTroca) break;
    }
}

// --- FUNÇÃO DE IMPRESSÃO ---

void exibirJogadores(const char *titulo, Jogador arr[], int n) {
    printf("\n--- %s ---\n", titulo);
    for (int i = 0; i < n; i++) {
        printf("ID: %-3d | Nome: %-10s | Pontuação: %d\n", arr[i].id, arr[i].nome, arr[i].pontuacao);
    }
}

// --- CENTRAL E RELATÓRIO FINAL ---

void executarCentral() {
    // Inicializar o gerador pseudoaleatório uma única vez
    srand((unsigned int)time(NULL));

    // Base de dados original preservada
    Jogador original[] = {
        {101, "Carlos", 150},
        {102, "Ana",    200},
        {103, "Bruno",  150},
        {104, "Ana",    150},
        {105, "Diana",  100},
        {106, "Eduardo",200},
        {107, "Beatriz",180}
    };
    int n = sizeof(original) / sizeof(original[0]);

    Jogador copia[n];
    Metricas mQuick = {0}, mInsertion = {0}, mBubble = {0};

    printf("=====================================================\n");
    printf("   CENTRAL DE ORDENAÇÃO DE JOGADORES (RELATÓRIO)    \n");
    printf("=====================================================\n");

    exibirJogadores("Entrada Original (Preservada)", original, n);

    // 1. Executar Quick Sort Randomizado
    memcpy(copia, original, sizeof(original));
    quickSortRandomizado(copia, 0, n - 1, &mQuick);
    exibirJogadores("Resultado Ordenado (Quick Sort Randomizado)", copia, n);

    // 2. Executar Insertion Sort sobre a mesma entrada original
    memcpy(copia, original, sizeof(original));
    insertionSortJogadores(copia, n, &mInsertion);

    // 3. Executar Bubble Sort sobre a mesma entrada original
    memcpy(copia, original, sizeof(original));
    bubbleSortJogadores(copia, n, &mBubble);

    // Produzir relatório final de comparações, trocas e deslocamentos
    printf("\n=====================================================\n");
    printf("            RELATÓRIO COMPARATIVO DE MÉTRICAS         \n");
    printf("=====================================================\n");
    printf("%-22s | %-12s | %-8s | %-13s\n", "Algoritmo", "Comparações", "Trocas", "Deslocamentos");
    printf("-----------------------------------------------------\n");
    printf("%-22s | %-12d | %-8d | %-13d\n", "Quick Sort (Random)", mQuick.comparacoes, mQuick.trocas, mQuick.deslocamentos);
    printf("%-22s | %-12d | %-8d | %-13d\n", "Insertion Sort", mInsertion.comparacoes, mInsertion.trocas, mInsertion.deslocamentos);
    printf("%-22s | %-12d | %-8d | %-13d\n", "Bubble Sort", mBubble.comparacoes, mBubble.trocas, mBubble.deslocamentos);
    printf("=====================================================\n");
}

int main() {
    executarCentral();
    return 0;
}