#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 1. O(1) - Tempo Constante: Acesso direto[cite: 1]
int acesso_direto(const int arr[], int tamanho, int indice, int *contador) {
    *contador = 0;

    (*contador)++; // Validação de limites[cite: 1]
    if (indice < 0 || indice >= tamanho) {
        printf("Erro: Índice %d fora dos limites do vetor.\n", indice);
        return -1;
    }

    (*contador)++; // Acesso direto[cite: 1]
    return arr[indice];
}

// 2. O(n) - Tempo Linear: Buscar o maior valor[cite: 1]
int buscar_maior(const int arr[], int tamanho, int *contador) {
    *contador = 0;

    if (tamanho <= 0) return -1;

    int maior = arr[0];
    (*contador)++;

    for (int i = 0; i < tamanho; i++) {
        (*contador)++;
        if (arr[i] > maior) {
            maior = arr[i];
            (*contador)++;
        }
    }

    return maior;
}

// 3. O(n²) - Tempo Quadrático: Encontrar pares com soma igual a um alvo[cite: 2]
int encontrar_pares_soma(const int arr[], int tamanho, int alvo, int *contador) {
    *contador = 0;
    int pares_encontrados = 0;

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            (*contador)++; // Comparação no núcleo[cite: 2]
            if (arr[i] + arr[j] == alvo) {
                pares_encontrados++;
            }
        }
    }

    return pares_encontrados;
}

// 4. O(log n) - Tempo Logarítmico: Busca Binária Iterativa[cite: 3]
int busca_binaria(const int arr[], int tamanho, int alvo, int *contador) {
    *contador = 0;
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2; //[cite: 3]

        (*contador)++; // Contabiliza a comparação do meio com o alvo
        if (arr[meio] == alvo) {
            return meio; // Posição encontrada[cite: 3]
        }

        (*contador)++; // Contabiliza a decisão do próximo intervalo[cite: 3]
        if (arr[meio] < alvo) {
            inicio = meio + 1; //[cite: 3]
        } else {
            fim = meio - 1; //[cite: 3]
        }
    }

    return -1; // Elemento ausente[cite: 3, 4]
}

// 5. O(n) - Busca Linear com Interface Equivalente à Busca Binária (Atividade 29)
int busca_linear(const int arr[], int tamanho, int alvo, int *contador) {
    *contador = 0;

    for (int i = 0; i < tamanho; i++) {
        (*contador)++; // Contabiliza a comparação de igualdade com o alvo
        if (arr[i] == alvo) {
            return i; // Retorna a primeira posição correspondente
        }
    }

    return -1; // Retorna -1 se o valor estiver ausente
}

// Funções auxiliares de preenchimento
void preencher_vetor_ordenado(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        arr[i] = (i + 1) * 2; // Preenche com inteiros pares ordenados[cite: 3]
    }
}

void preencher_vetor_desordenado(int arr[], int tamanho) {
    // Vetor deliberadamente desordenado com elementos variados
    for (int i = 0; i < tamanho; i++) {
        arr[i] = (i * 37 + 13) % 1000;
    }
}

int main() {
    int tamanhos[] = {100, 500, 1000};
    int num_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("=========================================================================\n");
    printf("   ATIVIDADE 29: BUSCA LINEAR VS BUSCA BINÁRIA E PRÉ-CONDIÇÕES\n");
    printf("=========================================================================\n\n");

    // --- PARTE 1: Comparação lado a lado em Vetor Ordenado (Início, Meio, Fim, Ausente)[cite: 4] ---
    printf("--- 1. COMPARAÇÃO LADO A LADO EM DADOS ORDENADOS ---\n\n");

    for (int t = 0; t < num_testes; t++) {
        int n = tamanhos[t];
        int *vetor_ord = (int *)malloc(n * sizeof(int));
        preencher_vetor_ordenado(vetor_ord, n);

        printf("Tamanho do Vetor (N): %d\n", n);
        printf("-------------------------------------------------------------------------\n");
        printf("%-15s | %-12s | %-15s | %-15s\n", "Cenário Testado", "Valor Alvo", "Busca Linear", "Busca Binária");
        printf("-------------------------------------------------------------------------\n");

        // Casos de teste exigidos: Início, Meio, Fim e Ausente[cite: 4]
        int alvos[] = {vetor_ord[0], vetor_ord[n / 2], vetor_ord[n - 1], -999};
        const char *rotulos[] = {"Início", "Meio", "Fim", "Ausente"};

        for (int k = 0; k < 4; k++) {
            int ops_lin = 0, ops_bin = 0;
            int pos_lin = busca_linear(vetor_ord, n, alvos[k], &ops_lin); //[cite: 4]
            int pos_bin = busca_binaria(vetor_ord, n, alvos[k], &ops_bin); //[cite: 4]

            printf("%-15s | %-12d | %2d ops (pos %3d) | %2d ops (pos %3d)\n",
                   rotulos[k], alvos[k], ops_lin, pos_lin, ops_bin, pos_bin);
        }
        printf("=========================================================================\n\n");

        free(vetor_ord);
    }

    // --- PARTE 2: Demonstração de Falha da Busca Binária em Vetor Desordenado[cite: 4] ---
    printf("--- 2. DEMONSTRAÇÃO: VETOR DESORDENADO E PRÉ-CONDIÇÕES ---\n\n");

    int n_desord = 10;
    int vetor_desord[] = {45, 12, 89, 3, 77, 21, 99, 4, 15, 60}; // Vetor totalmente desalinhado
    int alvo_teste = 12; // Valor que EXISTE na posição 1[cite: 4]
    int ops_lin = 0, ops_bin = 0;

    printf("Vetor Desordenado: [");
    for (int i = 0; i < n_desord; i++) {
        printf("%d%s", vetor_desord[i], (i < n_desord - 1) ? ", " : "");
    }
    printf("]\n");
    printf("Procurando o valor: %d (que ESTÁ presente no vetor)\n\n", alvo_teste);

    int res_lin = busca_linear(vetor_desord, n_desord, alvo_teste, &ops_lin); //[cite: 4]
    int res_bin = busca_binaria(vetor_desord, n_desord, alvo_teste, &ops_bin); //[cite: 4]

    printf("Resultados Obtidos:\n");
    printf("  * Busca Linear:  Posição = %d | Comparações = %d  -> [CORRETO]\n", res_lin, ops_lin);
    printf("  * Busca Binária: Posição = %d | Comparações = %d  -> [%s]\n\n", 
           res_bin, ops_bin, (res_bin == -1) ? "FALHA / INALTERADO" : "FALSO RESULTADO");

    // --- PARTE 3: Explicando as Pré-condições e Custos[cite: 4] ---
    printf("--- EXPLICAÇÃO DAS PRÉ-CONDIÇÕES E CUSTOS OBSERVADOS ---\n");
    printf("1. Pré-condição da Busca Binária:\n");
    printf("   - EXIGE obrigatoriamente que o vetor esteja previamente ORDENADO[cite: 3, 4].\n");
    printf("   - Se aplicada em dados desordenados, ela descarta metades válidas incorretamente,\n");
    printf("     retornando posições erradas ou informando -1 para valores existentes[cite: 4].\n\n");
    printf("2. Pré-condição da Busca Linear:\n");
    printf("   - NÃO possui pré-condição de ordenação. Funciona em qualquer sequência de dados[cite: 4].\n\n");
    printf("3. Comparação de Custos Observados:\n");
    printf("   - No melhor caso (Início), a Busca Linear gasta apenas 1 comparação[cite: 4].\n");
    printf("   - Nos piores casos (Fim / Ausente), a Busca Linear exige N comparações (O(n))[cite: 4].\n");
    printf("   - A Busca Binária mantém um custo logarítmico O(log n) consistente, exigindo no\n");
    printf("     máximo ~log2(N) comparações independentemente da posição do elemento[cite: 3, 4].\n");

    return 0;
}