#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de métricas para contagem de comparações e trocas
typedef struct {
    int comparacoes;
    int trocas;
} Metricas;

// --- 1. PARTIÇÃO COM MEMÓRIA AUXILIAR ---

// Partição usando um vetor auxiliar para entender o processo
int particionarComMemoriaAuxiliar(int arr[], int inicio, int fim, Metricas *m) {
    int pivo = arr[fim]; // Escolhe o último elemento como pivô
    int tamanho = fim - inicio + 1;
    
    // Alocação de memória auxiliar
    int *temp = (int *)malloc(tamanho * sizeof(int));
    
    int posEsq = 0;
    int posDir = tamanho - 1;

    // Separa valores segundo uma regra clara em relação ao pivô
    for (int i = inicio; i < fim; i++) {
        m->comparacoes++;
        if (arr[i] <= pivo) {
            temp[posEsq++] = arr[i]; // Menores ou iguais ficam à esquerda
        } else {
            temp[posDir--] = arr[i]; // Maiores ficam à direita
        }
    }

    // Coloca o pivô na sua posição final
    int posPivoRelativa = posEsq;
    temp[posPivoRelativa] = pivo;

    // Preserva todos os elementos copiando de volta para o vetor original
    for (int i = 0; i < tamanho; i++) {
        arr[inicio + i] = temp[i];
    }

    free(temp); // Liberta a memória auxiliar

    // Devolve a posição final absoluta do pivô
    return inicio + posPivoRelativa;
}

// --- 2. PARTIÇÃO IN-PLACE (LOMUTO) ---

// Partição in-place diretamente no próprio vetor
int particionarInPlace(int arr[], int inicio, int fim, Metricas *m) {
    int pivo = arr[fim]; // Pivô no último elemento
    int i = inicio - 1;  // Mantém índices válidos para a partição in-place

    for (int j = inicio; j < fim; j++) {
        m->comparacoes++;
        if (arr[j] <= pivo) {
            i++;
            // Troca de elementos
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            m->trocas++;
        }
    }

    // Coloca o pivô na posição correta (i + 1)
    int temp = arr[i + 1];
    arr[i + 1] = arr[fim];
    arr[fim] = temp;
    m->trocas++;

    // Devolver a posição final do pivô
    return i + 1;
}

// --- 3. QUICK SORT RECURSIVO ---

void quickSort(int arr[], int inicio, int fim, Metricas *m) {
    // Aplica Quick Sort somente aos subintervalos necessários
    if (inicio < fim) {
        // Usa a partição in-place
        int posPivo = particionarInPlace(arr, inicio, fim, m);

        // Chamadas recursivas excluindo a posição já fixada do pivô
        quickSort(arr, inicio, posPivo - 1, m);
        quickSort(arr, posPivo + 1, fim, m);
    }
}

// --- FUNÇÕES AUXILIARES DE IMPRESSÃO ---

void imprimirVetor(const char *titulo, int arr[], int n) {
    printf("%s: [ ", titulo);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

// --- MAIN / DEMONSTRAÇÕES ---

int main() {
    Metricas metricas = {0, 0};

    // -----------------------------------------------------------------
    // DEMONSTRAÇÃO 1: Partição com Memória Auxiliar
    // -----------------------------------------------------------------
    int arrAux[] = {25, 64, 12, 22, 11, 30};
    int nAux = sizeof(arrAux) / sizeof(arrAux[0]);

    printf("=== 1. TESTE ISOLADO: PARTIÇÃO COM MEMÓRIA AUXILIAR ===\n");
    imprimirVetor("Vetor Antes ", arrAux, nAux);
    printf("Pivô Escolhido (último elemento): %d\n", arrAux[nAux - 1]);

    int posPivoAux = particionarComMemoriaAuxiliar(arrAux, 0, nAux - 1, &metricas);

    imprimirVetor("Vetor Depois", arrAux, nAux);
    printf("Posição Final do Pivô: Índice %d (Valor: %d)\n", posPivoAux, arrAux[posPivoAux]);
    printf("Métricas -> Comparações: %d\n\n", metricas.comparacoes);

    // -----------------------------------------------------------------
    // DEMONSTRAÇÃO 2: Partição In-Place Isolada
    // -----------------------------------------------------------------
    metricas.comparacoes = 0;
    metricas.trocas = 0;

    int arrInPlace[] = {25, 64, 12, 22, 11, 30};
    int nInPlace = sizeof(arrInPlace) / sizeof(arrInPlace[0]);

    printf("=== 2. TESTE ISOLADO: PARTIÇÃO IN-PLACE ===\n");
    imprimirVetor("Vetor Antes ", arrInPlace, nInPlace);
    printf("Pivô Escolhido (último elemento): %d\n", arrInPlace[nInPlace - 1]);

    int posPivoInPlace = particionarInPlace(arrInPlace, 0, nInPlace - 1, &metricas);

    imprimirVetor("Vetor Depois", arrInPlace, nInPlace);
    printf("Posição Final do Pivô: Índice %d (Valor: %d)\n", posPivoInPlace, arrInPlace[posPivoInPlace]);
    printf("Métricas -> Comparações: %d | Trocas: %d\n\n", metricas.comparacoes, metricas.trocas);

    // -----------------------------------------------------------------
    // DEMONSTRAÇÃO 3: Quick Sort Recursivo com Valores Repetidos
    // -----------------------------------------------------------------
    metricas.comparacoes = 0;
    metricas.trocas = 0;

    int arrRepetidos[] = {25, 12, 25, 30, 12, 11, 25, 5};
    int nRepetidos = sizeof(arrRepetidos) / sizeof(arrRepetidos[0]);

    printf("=== 3. QUICK SORT RECURSIVO (CASO COM VALORES REPETIDOS) ===\n");
    imprimirVetor("Entrada Original", arrRepetidos, nRepetidos);

    quickSort(arrRepetidos, 0, nRepetidos - 1, &metricas);

    imprimirVetor("Saída Ordenada  ", arrRepetidos, nRepetidos);
    printf("Métricas Finais -> Comparações: %d | Trocas: %d\n", metricas.comparacoes, metricas.trocas);

    return 0;
}