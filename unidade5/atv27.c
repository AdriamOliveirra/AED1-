#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 1. Função de Tempo Constante O(1): Acesso direto[cite: 1]
int acesso_direto(const int arr[], int tamanho, int indice, int *contador) {
    *contador = 0;

    (*contador)++; // Validação de limites
    if (indice < 0 || indice >= tamanho) {
        printf("Erro: Índice %d fora dos limites do vetor.\n", indice);
        return -1;
    }

    (*contador)++; // Acesso direto ao elemento
    return arr[indice];
}

// 2. Função de Tempo Linear O(n): Buscar o maior valor[cite: 1]
int buscar_maior(const int arr[], int tamanho, int *contador) {
    *contador = 0;

    if (tamanho <= 0) return -1;

    int maior = arr[0];
    (*contador)++; // Acesso inicial

    for (int i = 0; i < tamanho; i++) {
        (*contador)++; // Comparação/incremento no laço
        if (arr[i] > maior) {
            maior = arr[i];
            (*contador)++; // Atribuição do novo maior
        }
    }

    return maior;
}

// 3. Função de Tempo Quadrático O(n²): Encontrar pares que somam um valor-alvo
int encontrar_pares_soma(const int arr[], int tamanho, int alvo, int *contador) {
    *contador = 0;
    int pares_encontrados = 0;

    // Laços aninhados para examinar combinações únicas de pares
    // i vai de 0 até tamanho - 1
    // j começa em i + 1 para evitar:
    //   - Combinar uma posição consigo mesma (i == j)
    //   - Apresentar pares duplicados como (A, B) e (B, A)
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            (*contador)++; // Instrumentação da comparação principal do núcleo
            
            if (arr[i] + arr[j] == alvo) {
                pares_encontrados++;
            }
        }
    }

    return pares_encontrados;
}

// Função auxiliar para preencher o vetor com valores de teste
void preencher_vetor(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        arr[i] = (i + 1) * 2; // Preenche com números pares simples
    }
}

int main() {
    // Testar tamanhos de entrada crescentes[cite: 1, 2]
    int tamanhos[] = {100, 500, 1000};
    int num_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);
    int alvo = 200; // Valor-alvo para a soma dos pares

    printf("=========================================================================\n");
    printf("   COMPARAÇÃO DE COMPLEXIDADE DE TEMPO: O(1) vs O(n) vs O(n²)\n");
    printf("=========================================================================\n\n");

    for (int t = 0; t < num_testes; t++) {
        int n = tamanhos[t];
        int *vetor = (int *)malloc(n * sizeof(int));

        if (vetor == NULL) {
            printf("Erro ao alocar memória.\n");
            return 1;
        }

        preencher_vetor(vetor, n);

        // Contadores independentes para cada algoritmo[cite: 1, 2]
        int ops_constante = 0;
        int ops_linear = 0;
        int ops_quadratica = 0;

        int indice_teste = n / 2;

        // Execução das 3 funções
        acesso_direto(vetor, n, indice_teste, &ops_constante);
        buscar_maior(vetor, n, &ops_linear);
        int total_pares = encontrar_pares_soma(vetor, n, alvo, &ops_quadratica);

        printf("Tamanho da Entrada (N): %d\n", n);
        printf("-------------------------------------------------------------------------\n");
        printf("1. O(1) - Acesso Direto:   %10d operações\n", ops_constante);
        printf("2. O(n) - Busca do Maior:  %10d operações\n", ops_linear);
        printf("3. O(n²) - Busca de Pares: %10d operações (Pares com soma %d: %d)\n", 
               ops_quadratica, alvo, total_pares);
        printf("=========================================================================\n\n");

        free(vetor);
    }

    // Análise e identificação do comportamento O(n²)
    printf("--- ANÁLISE COMPARATIVA DO COMPORTAMENTO ---\n");
    printf("* O(1) [Constante]: O número de operações permanece fixo em 2[cite: 1].\n");
    printf("* O(n) [Linear]: Cresce proporcionalmente a N (ex: N=1000 -> ~1000 op)[cite: 1].\n");
    printf("* O(n²) [Quadrático]: Para testar todos os pares únicos, o número de comparações\n");
    printf("  é N * (N - 1) / 2. Por exemplo:\n");
    printf("  - N = 100  ->    4.950 comparações\n");
    printf("  - N = 500  ->  124.750 comparações (~25x mais que N=100)\n");
    printf("  - N = 1000 ->  499.500 comparações (~100x mais que N=100)\n");
    printf("  Este crescimento quadrático demonstra por que a tarefa escala muito mais rápido.\n");

    return 0;
}