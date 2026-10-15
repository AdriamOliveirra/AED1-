#include <stdio.h>
#include <stdlib.h>

// Estrutura para contabilizar métricas da intercalação
typedef struct {
    int comparacoes;
} Metricas;

// --- ETAPA: COMBINAR (INTERCALAÇÃO) ---

// Função que recebe dois vetores ordenados (A e B) e produz um terceiro vetor ordenado (C)
void intercalarVetores(int A[], int nA, int B[], int nB, int C[], Metricas *m) {
    int i = 0; // Manter índices independentes para a primeira entrada
    int j = 0; // Manter índices independentes para a segunda entrada
    int k = 0; // Índice do vetor resultante C

    // Comparar e combinar elementos dos dois vetores
    while (i < nA && j < nB) {
        m->comparacoes++; // Contar comparações da intercalação
        if (A[i] <= B[j]) {
            C[k++] = A[i++];
        } else {
            C[k++] = B[j++];
        }
    }

    // Copiar os elementos restantes quando uma entrada terminar
    while (i < nA) {
        C[k++] = A[i++];
    }

    while (j < nB) {
        C[k++] = B[j++];
    }
}

// --- ESTRUTURA RECURSIVA (DIVIDIR E RESOLVER) ---

// Função recursiva que divide o intervalo em duas metades
void estruturaRecursiva(int arr[], int inicio, int fim) {
    // Caso base: subvetor com 1 ou 0 elementos já está "resolvido"
    if (inicio >= fim) {
        return;
    }

    // ETAPA 1: DIVIDIR
    // Calcular corretamente o ponto médio
    int meio = inicio + (fim - inicio) / 2;

    printf("Dividindo intervalo [%d..%d] em: [%d..%d] e [%d..%d]\n", 
           inicio, fim, inicio, meio, meio + 1, fim);

    // ETAPA 2: RESOLVER (Chamadas recursivas para as duas metades)
    estruturaRecursiva(arr, inicio, meio);
    estruturaRecursiva(arr, meio + 1, fim);

    // ETAPA 3: COMBINAR
    // Nota: A combinação completa e ordenação sobre o próprio vetor será finalizada na próxima atividade.
}

// --- FUNÇÃO AUXILIAR DE IMPRESSÃO ---

void imprimirVetor(const char *titulo, int arr[], int n) {
    printf("%s: [ ", titulo);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

// --- MAIN ---

int main() {
    Metricas metricas = {0};

    // 1. Teste da Intercalação de dois vetores ordenados
    int A[] = {12, 25, 64};
    int nA = sizeof(A) / sizeof(A[0]);

    int B[] = {11, 22, 50, 70};
    int nB = sizeof(B) / sizeof(B[0]);

    int nC = nA + nB;
    int C[nC];

    printf("=== DEMONSTRAÇÃO DA INTERCALAÇÃO (COMBINAR) ===\n");
    imprimirVetor("Vetor A (Ordenado)", A, nA);
    imprimirVetor("Vetor B (Ordenado)", B, nB);

    // Produzir saída com todos os valores
    intercalarVetores(A, nA, B, nB, C, &metricas);

    imprimirVetor("Vetor C (Intercalado)", C, nC);
    printf("Métricas -> Comparações na Intercalação: %d\n\n", metricas.comparacoes);

    // 2. Teste da Estrutura Recursiva (Divisão em metades)
    int vetorExemplo[] = {38, 27, 43, 3, 9, 82, 10};
    int nExemplo = sizeof(vetorExemplo) / sizeof(vetorExemplo[0]);

    printf("=== DEMONSTRAÇÃO DA ESTRUTURA RECURSIVA (DIVIDIR E RESOLVER) ===\n");
    imprimirVetor("Vetor de Entrada", vetorExemplo, nExemplo);
    printf("\nPassos de divisão:\n");

    estruturaRecursiva(vetorExemplo, 0, nExemplo - 1);

    return 0;
}