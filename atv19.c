#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int nivel;
    int pontos_vida;
    int ataque;
} Personagem;

void exibir_personagem(const Personagem *p) {
    if (p == NULL) return;
    printf("Nome: %-10s | Nivel: %2d | PV: %3d | Ataque: %d\n", 
           p->nome, p->nivel, p->pontos_vida, p->ataque);
}

// ETAPA: COMBINAR (Intercalação de dois vetores ordenados)
// Junta v1 (tamanho n1) e v2 (tamanho n2) no vetor de saída 'resultado'
void intercalar(Personagem v1[], int n1, Personagem v2[], int n2, Personagem resultado[], int *comparacoes) {
    int i = 0; // Índice independente para v1
    int j = 0; // Índice independente para v2
    int k = 0; // Índice para o vetor resultado

    // Intercala comparando pelo nível dos personagens
    while (i < n1 && j < n2) {
        (*comparacoes)++; // Contabiliza a comparação feita
        
        if (v1[i].nivel <= v2[j].nivel) {
            resultado[k] = v1[i];
            i++;
        } else {
            resultado[k] = v2[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de v1, se houver
    while (i < n1) {
        resultado[k] = v1[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de v2, se houver
    while (j < n2) {
        resultado[k] = v2[j];
        j++;
        k++;
    }
}

// ESTRUTURA RECURSIVA (Divisão do problema estilo Merge Sort)
void merge_sort_recursivo(Personagem equipe[], int inicio, int fim, int *comparacoes) {
    // Caso base: subvetor com 0 ou 1 elemento já está resolvido
    if (inicio >= fim) {
        return; 
    }

    // ETAPA: DIVIDIR (Cálculo do ponto médio)
    int meio = inicio + (fim - inicio) / 2;

    // ETAPA: RESOLVER (Chamadas recursivas para as duas metades)
    merge_sort_recursivo(equipe, inicio, meio, comparacoes);
    merge_sort_recursivo(equipe, meio + 1, fim, comparacoes);

    // ETAPA: COMBINAR (Junta as duas metades ordenadas usando um vetor temporário)
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    Personagem *v1 = (Personagem *)malloc(n1 * sizeof(Personagem));
    Personagem *v2 = (Personagem *)malloc(n2 * sizeof(Personagem));

    for (int i = 0; i < n1; i++) v1[i] = equipe[inicio + i];
    for (int j = 0; j < n2; j++) v2[j] = equipe[meio + 1 + j];

    // Intercala v1 e v2 direto na posição correspondente da equipe original
    intercalar(v1, n1, v2, n2, &equipe[inicio], comparacoes);

    free(v1);
    free(v2);
}

int main() {
    int comparacoes = 0;

    // Demonstração 1: Intercalação direta de duas subequipes já ordenadas
    printf("=== DEMONSTRAÇÃO 1: INTERCALAÇÃO DE DUAS ENTRADAS ===\n");
    Personagem subequipeA[] = {
        {"Gimli", 5, 80, 20},
        {"Aragorn", 10, 100, 25}
    };
    Personagem subequipeB[] = {
        {"Frodo", 2, 50, 5},
        {"Legolas", 8, 90, 22},
        {"Gandalf", 15, 120, 35}
    };

    int nA = sizeof(subequipeA) / sizeof(subequipeA[0]);
    int nB = sizeof(subequipeB) / sizeof(subequipeB[0]);
    Personagem equipeIntercalada[nA + nB];

    intercalar(subequipeA, nA, subequipeB, nB, equipeIntercalada, &comparacoes);

    printf("Resultado da intercalação (Ordenado por nível):\n");
    for (int i = 0; i < nA + nB; i++) {
        exibir_personagem(&equipeIntercalada[i]);
    }
    printf("Comparações realizadas na intercalação: %d\n\n", comparacoes);

    // Demonstração 2: Estrutura recursiva de divisão e ordenação
    printf("=== DEMONSTRAÇÃO 2: ESTRUTURA RECURSIVA (DIVIDIR, RESOLVER E COMBINAR) ===\n");
    Personagem equipeGeral[] = {
        {"Aragorn", 10, 100, 25},
        {"Frodo", 2, 50, 5},
        {"Gandalf", 15, 120, 35},
        {"Gimli", 5, 80, 20},
        {"Legolas", 8, 90, 22}
    };
    int nGeral = sizeof(equipeGeral) / sizeof(equipeGeral[0]);

    comparacoes = 0; // Reseta o contador
    merge_sort_recursivo(equipeGeral, 0, nGeral - 1, &comparacoes);

    printf("Equipe totalmente ordenada via Divisão e Conquista:\n");
    for (int i = 0; i < nGeral; i++) {
        exibir_personagem(&equipeGeral[i]);
    }
    printf("Total de comparações no processo recursivo: %d\n", comparacoes);

    return 0;
}