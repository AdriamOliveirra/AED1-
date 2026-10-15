#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Função para tempo constante O(1): acesso direto a uma posição
int acesso_direto(const int arr[], int tamanho, int indice, int *contador) {
    *contador = 0;

    // 1. Validar o índice do acesso direto
    (*contador)++; // Contabiliza a validação/comparação de limites
    if (indice < 0 || indice >= tamanho) {
        printf("Erro: Índice %d fora dos limites do vetor.\n", indice);
        return -1;
    }

    // 2. Contar a operação constante de forma coerente
    (*contador)++; // Contabiliza a operação de acesso direto ao elemento
    return arr[indice];
}

// Função para tempo linear O(n): percorre todo o vetor para encontrar o maior valor
int buscar_maior(const int arr[], int tamanho, int *contador) {
    *contador = 0;

    if (tamanho <= 0) return -1;

    int maior = arr[0];
    (*contador)++; // Acesso inicial para definir o maior elemento

    // Percorrer todos os elementos na busca do maior
    for (int i = 0; i < tamanho; i++) {
        (*contador)++; // Contabiliza a verificação/incremento do laço (acesso ao vetor e comparação de condição)
        
        if (arr[i] > maior) {
            maior = arr[i];
            (*contador)++; // Contabiliza a atribuição do novo maior valor
        }
    }

    return maior;
}

// Função auxiliar para preencher o vetor com dados de teste
void preencher_vetor(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        arr[i] = rand() % 10000;
    }
}

int main() {
    // Testar ao menos três tamanhos de entrada diferentes
    int tamanhos[] = {100, 1000, 10000};
    int num_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("===============================================================\n");
    printf("   ANÁLISE DE COMPLEXIDADE DE TEMPO: O(1) VS O(n)\n");
    printf("===============================================================\n\n");

    for (int t = 0; t < num_testes; t++) {
        int n = tamanhos[t];
        int *vetor = (int *)malloc(n * sizeof(int));
        
        if (vetor == NULL) {
            printf("Erro ao alocar memória.\n");
            return 1;
        }

        preencher_vetor(vetor, n);

        // Usar contadores independentes
        int ops_constante = 0;
        int ops_linear = 0;

        int indice_teste = n / 2; // Posição válida no meio do vetor
        
        // Execução do acesso direto O(1)
        int valor_direto = acesso_direto(vetor, n, indice_teste, &ops_constante);
        
        // Execução da busca linear O(n)[cite: 1]
        int maior_valor = buscar_maior(vetor, n, &ops_linear);

        printf("Tamanho do Vetor (N): %d\n", n);
        printf("---------------------------------------------------------------\n");
        printf("1. Acesso Direto [O(1)]:\n");
        printf("   - Valor obtido no índice %d: %d\n", indice_teste, valor_direto);
        printf("   - Operações contabilizadas: %d\n\n", ops_constante);

        printf("2. Busca do Maior Elemento [O(n)]:\n");
        printf("   - Maior valor encontrado: %d\n", maior_valor);
        printf("   - Operações contabilizadas: %d\n\n", ops_linear);
        printf("===============================================================\n\n");

        free(vetor);
    }

    // Relacionar os resultados a O(1) e O(n)[cite: 1]
    printf("--- RELAÇÃO DOS RESULTADOS COM O(1) E O(n) ---\n");
    printf("* O(1) - Tempo Constante: O número de operações do acesso direto permanece fixo (2 operações),\n");
    printf("  independentemente do tamanho do vetor (N = 100, 1000 ou 10000)[cite: 1].\n");
    printf("* O(n) - Tempo Linear: O número de operações cresce de forma proporcional ao tamanho do vetor (N),\n");
    printf("  pois é necessário iterar por cada elemento para garantir que o maior valor foi encontrado[cite: 1].\n");

    return 0;
}