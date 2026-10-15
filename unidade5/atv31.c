#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// =========================================================================
// AUXILIARES
// =========================================================================

void preencher_vetor_ordenado(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        arr[i] = (i + 1) * 2;
    }
}

void preencher_vetor_desordenado(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        arr[i] = (i * 37 + 13) % 1000;
    }
}

// =========================================================================
// EXPERIMENTO 1: O(1) e O(n) (Atividade 26)
// =========================================================================

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

void executar_exp1() {
    printf("\n--- EXPERIMENTO 1: Tempo Constante O(1) vs Tempo Linear O(n) ---\n\n");
    int tamanhos[] = {100, 1000, 10000};
    
    for (int t = 0; t < 3; t++) {
        int n = tamanhos[t];
        int *vetor = (int *)malloc(n * sizeof(int));
        preencher_vetor_ordenado(vetor, n);

        int ops_constante = 0, ops_linear = 0;
        int val_direto = acesso_direto(vetor, n, n / 2, &ops_constante);
        int val_maior = buscar_maior(vetor, n, &ops_linear);

        printf("N = %-5d | O(1) Acesso Direto: %d ops (val: %d) | O(n) Maior: %d ops (val: %d)\n",
               n, ops_constante, val_direto, ops_linear, val_maior);

        free(vetor);
    }
}

// =========================================================================
// EXPERIMENTO 2: O(n²) - Combinações de Pares (Atividade 27)
// =========================================================================

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

void executar_exp2() {
    printf("\n--- EXPERIMENTO 2: Tempo Quadrático O(n²) - Pares com Soma ---\n\n");
    int tamanhos[] = {100, 500, 1000};
    int alvo = 200;

    for (int t = 0; t < 3; t++) {
        int n = tamanhos[t];
        int *vetor = (int *)malloc(n * sizeof(int));
        preencher_vetor_ordenado(vetor, n);

        int ops_quadratica = 0;
        int pares = encontrar_pares_soma(vetor, n, alvo, &ops_quadratica);

        printf("N = %-5d | O(n²) Comparações de Pares: %d ops (Pares encontrados: %d)\n",
               n, ops_quadratica, pares);

        free(vetor);
    }
}

// =========================================================================
// EXPERIMENTO 3: O(log n) - Busca Binária Iterativa (Atividade 28)
// =========================================================================

int busca_binaria_iterativa(const int arr[], int tamanho, int alvo, int *contador) {
    *contador = 0;
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        (*contador)++;
        if (arr[meio] == alvo) return meio;

        (*contador)++;
        if (arr[meio] < alvo) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

void executar_exp3() {
    printf("\n--- EXPERIMENTO 3: Tempo Logarítmico O(log n) - Busca Binária ---\n\n");
    int tamanhos[] = {100, 500, 1000};

    for (int t = 0; t < 3; t++) {
        int n = tamanhos[t];
        int *vetor = (int *)malloc(n * sizeof(int));
        preencher_vetor_ordenado(vetor, n);

        int ops_pres = 0, ops_aus = 0;
        int pos_pres = busca_binaria_iterativa(vetor, n, vetor[n - 5], &ops_pres);
        int pos_aus = busca_binaria_iterativa(vetor, n, -999, &ops_aus);

        printf("N = %-5d | Busca (Presente): %d ops (pos %d) | Busca (Ausente): %d ops (pos %d)\n",
               n, ops_pres, pos_pres, ops_aus, pos_aus);

        free(vetor);
    }
}

// =========================================================================
// EXPERIMENTO 4: Busca Linear vs Binária e Pré-Condições (Atividade 29)
// =========================================================================

int busca_linear_iterativa(const int arr[], int tamanho, int alvo, int *contador) {
    *contador = 0;
    for (int i = 0; i < tamanho; i++) {
        (*contador)++;
        if (arr[i] == alvo) return i;
    }
    return -1;
}

void executar_exp4() {
    printf("\n--- EXPERIMENTO 4: Busca Linear vs Busca Binária ---\n\n");
    int n = 1000;
    int *vetor = (int *)malloc(n * sizeof(int));
    preencher_vetor_ordenado(vetor, n);

    int alvos[] = {vetor[0], vetor[n / 2], vetor[n - 1], -999};
    const char *rotulos[] = {"Início", "Meio", "Fim", "Ausente"};

    printf("Testes em Vetor Ordenado (N = 1000):\n");
    for (int k = 0; k < 4; k++) {
        int ops_lin = 0, ops_bin = 0;
        busca_linear_iterativa(vetor, n, alvos[k], &ops_lin);
        busca_binaria_iterativa(vetor, n, alvos[k], &ops_bin);
        printf("  * Cenário [%-7s]: Linear = %4d ops | Binária = %2d ops\n", rotulos[k], ops_lin, ops_bin);
    }

    printf("\nDemonstração de Falha em Vetor Desordenado:\n");
    int vetor_desord[] = {45, 12, 89, 3, 77, 21, 99, 4, 15, 60};
    int alvo_teste = 12;
    int ops_lin = 0, ops_bin = 0;

    int res_lin = busca_linear_iterativa(vetor_desord, 10, alvo_teste, &ops_lin);
    int res_bin = busca_binaria_iterativa(vetor_desord, 10, alvo_teste, &ops_bin);

    printf("  * Busca Linear:  Posição = %d (%d ops) -> [CORRETO]\n", res_lin, ops_lin);
    printf("  * Busca Binária: Posição = %d (%d ops) -> [FALHOU por falta de ordenação]\n", res_bin, ops_bin);

    free(vetor);
}

// =========================================================================
// EXPERIMENTO 5: Caso-Base e Progresso em Recursão (Atividade 30)
// =========================================================================

long long fatorial_recursivo(int n, int *chamadas) {
    (*chamadas)++;
    if (n <= 1) return 1; // Caso-base
    return n * fatorial_recursivo(n - 1, chamadas); // Progresso
}

long long soma_vetor_recursiva(const int arr[], int inicio, int fim, int *chamadas) {
    (*chamadas)++;
    if (inicio > fim) return 0;
    if (inicio == fim) return arr[inicio]; // Caso-base

    int meio = inicio + (fim - inicio) / 2;
    return soma_vetor_recursiva(arr, inicio, meio, chamadas) + 
           soma_vetor_recursiva(arr, meio + 1, fim, chamadas);
}

void executar_exp5() {
    printf("\n--- EXPERIMENTO 5: Caso-Base e Progresso na Recursão ---\n\n");
    int chamadas_fat = 0;
    long long res_fat = fatorial_recursivo(8, &chamadas_fat);
    printf("Fatorial de 8: Resultado = %lld | Chamadas na Pilha = %d\n", res_fat, chamadas_fat);

    int n = 1000;
    int *vetor = (int *)malloc(n * sizeof(int));
    preencher_vetor_ordenado(vetor, n);

    int chamadas_soma = 0;
    long long res_soma = soma_vetor_recursiva(vetor, 0, n - 1, &chamadas_soma);
    printf("Soma de Vetor (N=1000): Resultado = %lld | Chamadas na Pilha = %d\n", res_soma, chamadas_soma);

    free(vetor);
}

// =========================================================================
// EXPERIMENTO 6: Recursão Ramificada vs Busca Binária Recursiva (Atividade 31)
// =========================================================================

// 1. Fibonacci Ingênuo (Exemplo Ramificado) - Gera 2 chamadas por nível
long long fibonacci_ramificado(int n, int *chamadas) {
    (*chamadas)++;

    // Caso-base: F(0) = 0, F(1) = 1
    if (n <= 0) return 0;
    if (n == 1) return 1;

    // Ramificação em duas subchamadas
    return fibonacci_ramificado(n - 1, chamadas) + fibonacci_ramificado(n - 2, chamadas);
}

// 2. Busca Binária Recursiva - Descarta metade a cada chamada
int busca_binaria_recursiva(const int arr[], int inicio, int fim, int alvo, int *chamadas) {
    (*chamadas)++;

    // Caso-base 1: Intervalo vazio (não encontrado)
    if (inicio > fim) {
        return -1;
    }

    int meio = inicio + (fim - inicio) / 2;

    // Caso-base 2: Encontrou o elemento
    if (arr[meio] == alvo) {
        return meio;
    }

    // Progresso escolhendo apenas UMA metade
    if (arr[meio] < alvo) {
        return busca_binaria_recursiva(arr, meio + 1, fim, alvo, chamadas);
    } else {
        return busca_binaria_recursiva(arr, inicio, meio - 1, alvo, chamadas);
    }
}

void executar_exp6() {
    printf("\n--- EXPERIMENTO 6: Recursão Ramificada O(2^n) vs Busca Binária Recursiva O(log n) ---\n\n");

    // Teste 1: Fibonacci Ingênuo com Entrada Limitada
    printf("1. FIBONACCI RAMIFICADO (Entrada limitada para evitar explosão de chamadas):\n");
    int termos_fib[] = {5, 10, 15, 20, 25};
    for (int i = 0; i < 5; i++) {
        int n = termos_fib[i];
        int chamadas = 0;
        long long res = fibonacci_ramificado(n, &chamadas);
        printf("  * Fib(%2d) = %-8lld | Chamadas Recursivas: %-7d (Crescimento Exponencial)\n", n, res, chamadas);
    }

    // Teste 2: Busca Binária Recursiva
    printf("\n2. BUSCA BINÁRIA RECURSIVA (Processa apenas uma metade por vez):\n");
    int tamanhos[] = {100, 1000, 1000000};
    for (int t = 0; t < 3; t++) {
        int n = tamanhos[t];
        int *vetor = (int *)malloc(n * sizeof(int));
        preencher_vetor_ordenado(vetor, n);

        int chamadas_pres = 0, chamadas_aus = 0;
        int alvo_pres = vetor[n - 10];
        int alvo_aus = -999;

        int pos_pres = busca_binaria_recursiva(vetor, 0, n - 1, alvo_pres, &chamadas_pres);
        int pos_aus = busca_binaria_recursiva(vetor, 0, n - 1, alvo_aus, &chamadas_aus);

        printf("  * N = %-7d | Alvo Presente: %2d chamadas (pos %d) | Alvo Ausente: %2d chamadas\n",
               n, chamadas_pres, pos_pres, chamadas_aus);

        free(vetor);
    }

    printf("\n--- EXPLICAÇÃO DOS CASOS-BASE E CUSTOS ---\n");
    printf("* Fibonacci Ramificado O(2^n):\n");
    printf("  Cada chamada gera DUAS novas chamadas. Os casos-base (n=0 e n=1) apenas param a árvore.\n");
    printf("  A árvore cresce exponencialmente, tornando inviável para N grandes.\n");
    printf("* Busca Binária Recursiva O(log n):\n");
    printf("  Cada chamada reduz o problema à metade e escolhe APENAS UM caminho.\n");
    printf("  Mesmo para N = 1.000.000, são necessárias no máximo ~20 chamadas na pilha.\n");
}

// =========================================================================
// MENU INTEGRADO
// =========================================================================

int main() {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n=========================================================================\n");
        printf("            LABORATÓRIO DE COMPLEXIDADE E ALGORITMOS EM C\n");
        printf("=========================================================================\n");
        printf("  1. Exp 1: Tempo Constante O(1) e Linear O(n)\n");
        printf("  2. Exp 2: Tempo Quadrático O(n²) - Análise de Pares\n");
        printf("  3. Exp 3: Tempo Logarítmico O(log n) - Busca Binária Iterativa\n");
        printf("  4. Exp 4: Busca Linear vs Binária e Pré-Condições de Ordenação\n");
        printf("  5. Exp 5: Recursão - Caso-Base, Progresso e Rastreamento\n");
        printf("  6. Exp 6: Recursão Ramificada O(2^n) vs Busca Binária Recursiva O(log n)\n");
        printf("  7. Executar TODOS os Experimentos\n");
        printf("  0. Sair\n");
        printf("=========================================================================\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida.\n");
            break;
        }

        switch (opcao) {
            case 1: executar_exp1(); break;
            case 2: executar_exp2(); break;
            case 3: executar_exp3(); break;
            case 4: executar_exp4(); break;
            case 5: executar_exp5(); break;
            case 6: executar_exp6(); break;
            case 7:
                executar_exp1();
                executar_exp2();
                executar_exp3();
                executar_exp4();
                executar_exp5();
                executar_exp6();
                break;
            case 0:
                printf("\nPrograma finalizado.\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    }

    return 0;
}