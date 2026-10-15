#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para contabilizar comparações, trocas e passagens
typedef struct {
    int comparacoes;
    int trocas;
    int passagens;
} Metricas;

// --- BUBBLE SORT COM PARADA ANTECIPADA ---

void bubbleSortComParada(int arr[], int n, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    m->passagens = 0;

    int houveTroca;

    for (int i = 0; i < n - 1; i++) {
        houveTroca = 0;
        m->passagens++; // Registra o início de mais uma passagem

        // A faixa útil é reduzida a cada passagem: (n - 1 - i)
        for (int j = 0; j < n - 1 - i; j++) {
            m->comparacoes++; // Comparar elementos vizinhos

            if (arr[j] > arr[j + 1]) {
                // Troca dos elementos vizinhos
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                houveTroca = 1;
                m->trocas++;
            }
        }

        // Interromper quando nenhuma troca ocorrer na passagem
        if (!houveTroca) {
            break;
        }
    }
}

// --- FUNÇÃO AUXILIAR DE IMPRESSÃO ---

void imprimirVetor(const char *nome, int arr[], int n) {
    printf("%s: [ ", nome);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void executarEExibirTeste(const char *tipoEntrada, int arrOriginal[], int n) {
    int copia[n];
    Metricas m;

    // Preservar a versão anterior / entrada original
    memcpy(copia, arrOriginal, sizeof(int) * n);

    printf("\n-----------------------------------------\n");
    printf("TESTE: %s\n", tipoEntrada);
    printf("-----------------------------------------\n");
    imprimirVetor("Antes ", copia, n);

    bubbleSortComParada(copia, n, &m);

    imprimirVetor("Depois", copia, n);
    printf("Métricas -> Passagens: %d | Comparações: %d | Trocas: %d\n", 
           m.passagens, m.comparacoes, m.trocas);
}

// --- MAIN / CENTRAL ---

int main() {
    int n = 7;

    // 1. Vetor já ordenado (Caso Ideal)
    int ordenado[] = {10, 20, 30, 40, 50, 60, 70};

    // 2. Vetor em ordem inversa (Pior Caso)
    int ordemInversa[] = {70, 60, 50, 40, 30, 20, 10};

    // 3. Vetor aleatório
    int aleatorio[] = {35, 12, 70, 20, 50, 10, 40};

    printf("=========================================\n");
    printf("  BUBBLE SORT COM PARADA ANTECIPADA    \n");
    printf("=========================================\n");

    // Testar os três formatos de entrada e exibir métricas separadamente
    executarEExibirTeste("1. Vetor Já Ordenado", ordenado, n);
    executarEExibirTeste("2. Vetor em Ordem Inversa", ordemInversa, n);
    executarEExibirTeste("3. Vetor Aleatório", aleatorio, n);

    return 0;
}