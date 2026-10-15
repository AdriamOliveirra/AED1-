#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// =========================================================================
// ATIVIDADES ANTERIORES: O(1), O(n), O(n²), O(log n)
// =========================================================================

// 1. O(1) - Tempo Constante: Acesso direto
int acesso_direto(const int arr[], int tamanho, int indice, int *contador) {
    *contador = 0;
    (*contador)++; // Validação de limites
    if (indice < 0 || indice >= tamanho) {
        printf("Erro: Índice %d fora dos limites do vetor.\n", indice);
        return -1;
    }
    (*contador)++; // Acesso direto
    return arr[indice];
}

// 2. O(n) - Tempo Linear: Buscar o maior valor
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

// 3. O(n²) - Tempo Quadrático: Encontrar pares com soma igual a um alvo
int encontrar_pares_soma(const int arr[], int tamanho, int alvo, int *contador) {
    *contador = 0;
    int pares_encontrados = 0;

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            (*contador)++; // Comparação no núcleo
            if (arr[i] + arr[j] == alvo) {
                pares_encontrados++;
            }
        }
    }
    return pares_encontrados;
}

// 4. O(log n) - Tempo Logarítmico: Busca Binária Iterativa
int busca_binaria(const int arr[], int tamanho, int alvo, int *contador) {
    *contador = 0;
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        (*contador)++; // Comparação do meio
        if (arr[meio] == alvo) {
            return meio;
        }

        (*contador)++; // Decisão do intervalo
        if (arr[meio] < alvo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

// 5. O(n) - Busca Linear Iterativa
int busca_linear(const int arr[], int tamanho, int alvo, int *contador) {
    *contador = 0;
    for (int i = 0; i < tamanho; i++) {
        (*contador)++;
        if (arr[i] == alvo) {
            return i;
        }
    }
    return -1;
}

// =========================================================================
// RECURSÃO (CASO-BASE, PROGRESSO E RASTREAMENTO)
// =========================================================================

// --- A. Problema Numérico Simples: Fatorial ---

long long fatorial_iterativo(int n, int *contador) {
    *contador = 0;
    long long resultado = 1;
    for (int i = 1; i <= n; i++) {
        (*contador)++;
        resultado *= i;
    }
    return resultado;
}

long long fatorial_recursivo(int n, int *chamadas) {
    (*chamadas)++;

    // Caso-Base alcançável
    if (n <= 1) {
        return 1;
    }

    // Progresso: reduz a entrada
    return n * fatorial_recursivo(n - 1, chamadas);
}

// --- B. Percurso em Vetor: Soma dos Elementos ---

long long soma_vetor_iterativa(const int arr[], int tamanho, int *contador) {
    *contador = 0;
    long long soma = 0;
    for (int i = 0; i < tamanho; i++) {
        (*contador)++;
        soma += arr[i];
    }
    return soma;
}

// Soma Recursiva Segura via Divisão e Conquista
long long soma_vetor_recursiva(const int arr[], int inicio, int fim, int *chamadas) {
    (*chamadas)++;

    // Caso-base 1: Posição inválida ou fora dos limites do vetor
    if (inicio > fim) {
        return 0;
    }

    // Caso-base 2: Um único elemento
    if (inicio == fim) {
        return arr[inicio];
    }

    // Progresso: divide o vetor ao meio
    int meio = inicio + (fim - inicio) / 2;
    return soma_vetor_recursiva(arr, inicio, meio, chamadas) + 
           soma_vetor_recursiva(arr, meio + 1, fim, chamadas);
}

// Auxiliar de preenchimento
void preencher_vetor_ordenado(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        arr[i] = (i + 1) * 2;
    }
}

int main() {
    printf("=========================================================================\n");
    printf("   ATIVIDADE: RECURSÃO (CASO-BASE, PROGRESSO E RETORNO DE CHAMADAS)\n");
    printf("=========================================================================\n\n");

    // TESTE 1: Fatorial
    int num_fatorial = 10;
    int ops_fat_iter = 0;
    int chamadas_fat_rec = 0;

    long long res_fat_iter = fatorial_iterativo(num_fatorial, &ops_fat_iter);
    long long res_fat_rec = fatorial_recursivo(num_fatorial, &chamadas_fat_rec);

    printf("--- 1. NUMÉRICA SIMPLES: FATORIAL DE %d ---\n", num_fatorial);
    printf("  * [Iterativo] Resultado: %lld | Iterações: %d\n", res_fat_iter, ops_fat_iter);
    printf("  * [Recursivo] Resultado: %lld | Chamadas na Pilha: %d\n", res_fat_rec, chamadas_fat_rec);
    printf("  * Validação: Ambas as abordagens retornaram %s resultado.\n\n", 
           (res_fat_iter == res_fat_rec) ? "o MESMO" : "resultados DIFERENTES");

    // TESTE 2: Soma de Vetor em tamanhos crescentes
    int tamanhos[] = {100, 500, 1000};
    int num_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("--- 2. PERCURSO EM VETOR: SOMA DOS ELEMENTOS ---\n\n");

    for (int t = 0; t < num_testes; t++) {
        int n = tamanhos[t];
        int *vetor = (int *)malloc(n * sizeof(int));
        
        if (vetor == NULL) {
            printf("Erro ao alocar memória.\n");
            return 1;
        }

        preencher_vetor_ordenado(vetor, n);

        int ops_soma_iter = 0;
        int chamadas_soma_rec = 0;

        long long res_soma_iter = soma_vetor_iterativa(vetor, n, &ops_soma_iter);
        long long res_soma_rec = soma_vetor_recursiva(vetor, 0, n - 1, &chamadas_soma_rec);

        printf("Tamanho da Entrada (N): %d\n", n);
        printf("-------------------------------------------------------------------------\n");
        printf("  * Versão Iterativa: Resultado = %lld | Operações = %d\n", res_soma_iter, ops_soma_iter);
        printf("  * Versão Recursiva: Resultado = %lld | Chamadas  = %d\n", res_soma_rec, chamadas_soma_rec);
        printf("-------------------------------------------------------------------------\n\n");

        free(vetor);
    }

    printf("--- ANÁLISE COMPARATIVA: ITERAÇÃO VS RECURSÃO ---\n");
    printf("1. Caso-Base e Progresso:\n");
    printf("   - No Fatorial: Caso-base (n <= 1) e progresso via (n - 1).\n");
    printf("   - Na Soma: Caso-base (inicio == fim) e progresso via divisão em subintervalos.\n");
    printf("2. Desempenho e Memória:\n");
    printf("   - A abordagem de divisão e conquista reduz drasticamente o número de níveis empilhados,\n");
    printf("     evitando estouros de pilha (Stack Overflow) no VS Code e sistemas com limites restritos.\n");

    return 0;
}