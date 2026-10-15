#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 1. O(1) - Tempo Constante: Acesso direto[cite: 1]
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
            (*contador)++; // Comparação no núcleo
            if (arr[i] + arr[j] == alvo) {
                pares_encontrados++;
            }
        }
    }

    return pares_encontrados;
}

// 4. O(log n) - Tempo Logarítmico: Busca Binária Iterativa[cite: 3]
int busca_binaria(const int arr[], int tamanho, int alvo, int *contador, bool detalhar_passos) {
    *contador = 0;
    int inicio = 0;
    int fim = tamanho - 1;

    if (detalhar_passos) {
        printf("   [Busca Binaria - Rastreamento para Alvo: %d]\n", alvo);
    }

    // Executa enquanto o intervalo não estiver vazio (inicio <= fim)[cite: 3]
    while (inicio <= fim) {
        // Cálculo seguro do meio para evitar transbordo de inteiros e índices inválidos[cite: 3]
        int meio = inicio + (fim - inicio) / 2;

        if (detalhar_passos) {
            printf("   -> Inicio: %d | Meio: %d (Valor: %d) | Fim: %d\n", 
                   inicio, meio, arr[meio], fim);
        }

        (*contador)++; // Contabiliza a comparação principal[cite: 3]
        if (arr[meio] == alvo) {
            return meio; // Elemento encontrado
        }

        (*contador)++; // Contabiliza a decisão de redução do intervalo[cite: 3]
        if (arr[meio] < alvo) {
            inicio = meio + 1; // Reduz o intervalo para a metade direita[cite: 3]
        } else {
            fim = meio - 1;    // Reduz o intervalo para a metade esquerda[cite: 3]
        }
    }

    return -1; // Intervalo ficou vazio -> Elemento não encontrado[cite: 3]
}

// Função auxiliar para garantir que o vetor esteja ordenado (Requisito)[cite: 3]
void preencher_vetor_ordenado(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        arr[i] = (i + 1) * 2; // Preenche com números pares em ordem crescente (2, 4, 6, 8...)[cite: 3]
    }
}

int main() {
    int tamanhos[] = {100, 500, 1000};
    int num_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("=========================================================================\n");
    printf("  COMPARAÇÃO DE COMPLEXIDADE: O(1) vs O(log n) vs O(n) vs O(n²)\n");
    printf("=========================================================================\n\n");

    for (int t = 0; t < num_testes; t++) {
        int n = tamanhos[t];
        int *vetor = (int *)malloc(n * sizeof(int));

        if (vetor == NULL) {
            printf("Erro ao alocar memória.\n");
            return 1;
        }

        // Garante o vetor ordenado exigido pela Busca Binária[cite: 3]
        preencher_vetor_ordenado(vetor, n);

        int ops_constante = 0;
        int ops_linear = 0;
        int ops_quadratica = 0;
        int ops_binaria_presente = 0;
        int ops_binaria_ausente = 0;

        int indice_teste = n / 2;
        int alvo_presente = vetor[n - 5]; // Valor garantidamente presente no vetor[cite: 3]
        int alvo_ausente = 999999;        // Valor garantidamente ausente no vetor[cite: 3]

        // Execução dos algoritmos
        acesso_direto(vetor, n, indice_teste, &ops_constante);
        buscar_maior(vetor, n, &ops_linear);
        encontrar_pares_soma(vetor, n, 200, &ops_quadratica);

        // Demonstração detalhada dos passos apenas no primeiro teste (N = 100)[cite: 3]
        bool detalhar = (t == 0);

        printf("Tamanho da Entrada (N): %d\n", n);
        printf("-------------------------------------------------------------------------\n");
        
        // Teste de Busca Binária (Valor Presente)[cite: 3]
        int pos_pres = busca_binaria(vetor, n, alvo_presente, &ops_binaria_presente, detalhar);
        if (detalhar) printf("\n");

        // Teste de Busca Binária (Valor Ausente)[cite: 3]
        int pos_aus = busca_binaria(vetor, n, alvo_ausente, &ops_binaria_ausente, detalhar);
        if (detalhar) printf("\n");

        printf("1. O(1)      - Acesso Direto:       %10d operações\n", ops_constante);
        printf("2. O(log n)  - Busca Binária (Pres): %10d operações (Posição: %d)\n", ops_binaria_presente, pos_pres);
        printf("3. O(log n)  - Busca Binária (Aus):  %10d operações (Posição: %d)\n", ops_binaria_ausente, pos_aus);
        printf("4. O(n)      - Busca do Maior:      %10d operações\n", ops_linear);
        printf("5. O(n²)     - Combinação de Pares: %10d operações\n", ops_quadratica);
        printf("=========================================================================\n\n");

        free(vetor);
    }

    // Análise da redução e relação com O(log n)[cite: 3]
    printf("--- RELAÇÃO DA REDUÇÃO À COMPLEXIDADE O(log n) ---\n");
    printf("* Ao descartar metade do espaço restante a cada passo, o número máximo de etapas\n");
    printf("  necessárias para encontrar um valor ou esgotar o intervalo é dado por log2(N)[cite: 3].\n");
    printf("* Comparação de crescimento com o aumento de N[cite: 3]:\n");
    printf("  - N = 100  -> Busca Binária realiza ~10-12 comparações | O(n) realiza ~100 | O(n²) realiza 4.950[cite: 3]\n");
    printf("  - N = 500  -> Busca Binária realiza ~16 comparações    | O(n) realiza ~500 | O(n²) realiza 124.750[cite: 3]\n");
    printf("  - N = 1000 -> Busca Binária realiza ~18 comparações    | O(n) realiza ~1000| O(n²) realiza 499.500[cite: 3]\n");
    printf("* Mesmo multiplicando o tamanho da entrada por 10 (100 para 1000), a busca binária\n");
    printf("  adiciona apenas poucas comparações extras, demonstrando a eficiência de O(log n)[cite: 3].\n");

    return 0;
}