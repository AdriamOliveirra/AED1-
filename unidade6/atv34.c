#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para os Jogadores
typedef struct {
    int id;
    char nome[50];
    int pontuacao;
} Jogador;

// Estrutura para contagem de métricas
typedef struct {
    int comparacoes;
    int deslocamentos;
} Metricas;

// --- FUNÇÕES DE COMPARAÇÃO ---

// Compara dois jogadores focando na ORDEM ALFABÉTICA do Nome
// Em caso de nomes iguais, usa a Pontuação (decrescente) ou ID como desempate
int compararPorNome(Jogador a, Jogador b) {
    int resNome = strcmp(a.nome, b.nome); // Comparar nomes com strcmp
    
    if (resNome != 0) {
        return resNome; // Se os nomes forem diferentes, retorna a ordem alfabética
    }
    
    // Critério secundário para nomes iguais: Maior pontuação primeiro
    if (a.pontuacao != b.pontuacao) {
        return b.pontuacao - a.pontuacao;
    }
    
    // Terceiro critério de desempate: ID (crescente)
    return a.id - b.id;
}

// --- INSERTION SORT POR NOME ---

// Insere uma estrutura de jogador no prefixo ordenado
void inserirNoPrefixoPorNome(Jogador arr[], int pos, Metricas *m) {
    Jogador chave = arr[pos]; // Usar uma estrutura temporária completa
    int j = pos - 1;

    // Desloca os elementos cujos nomes sejam alfabeticamente maiores que a chave
    while (j >= 0) {
        m->comparacoes++;
        if (compararPorNome(arr[j], chave) > 0) {
            arr[j + 1] = arr[j]; // Mover todos os campos juntos
            m->deslocamentos++;
            j--;
        } else {
            break;
        }
    }
    arr[j + 1] = chave; // Insere a estrutura completa na posição correta
}

// Algoritmo Insertion Sort por Nome
void insertionSortPorNome(Jogador arr[], int n, Metricas *m) {
    m->comparacoes = 0;
    m->deslocamentos = 0;

    for (int i = 1; i < n; i++) {
        inserirNoPrefixoPorNome(arr, i, m);
    }
}

// --- FUNÇÃO DE IMPRESSÃO ---

// Exibe os registros no terminal
void exibirRegistros(const char *titulo, Jogador arr[], int n) {
    printf("\n--- %s ---\n", titulo);
    for (int i = 0; i < n; i++) {
        printf("ID: %-3d | Nome: %-10s | Pontuação: %d\n", arr[i].id, arr[i].nome, arr[i].pontuacao);
    }
}

// --- CENTRAL / MENU PRINCIPAL ---

void menuCentral() {
    // Registros de teste contendo nomes repetidos para testar o desempate
    Jogador catalogoOriginal[] = {
        {101, "Carlos", 150},
        {102, "Ana",    200},
        {103, "Bruno",  180},
        {104, "Ana",    250}, // Nome repetido "Ana", com maior pontuação
        {105, "Carlos", 100}, // Nome repetido "Carlos", com menor pontuação
        {106, "Beatriz", 220}
    };
    int n = sizeof(catalogoOriginal) / sizeof(catalogoOriginal[0]);

    Jogador copiaTrabalho[n];
    Metricas metricas;

    int opcao;
    do {
        printf("\n=====================================\n");
        printf("    CENTRAL DE CATALOGO DE JOGADORES  \n");
        printf("=====================================\n");
        printf("1. Exibir catálogo original\n");
        printf("2. Ordenar por Nome (Insertion Sort)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirRegistros("Catálogo Original (Preservado)", catalogoOriginal, n);
                break;

            case 2:
                // Copia os dados para preservar o original
                memcpy(copiaTrabalho, catalogoOriginal, sizeof(catalogoOriginal));

                printf("\nExibindo antes da ordenacao:");
                exibirRegistros("Antes da Ordenação", copiaTrabalho, n);

                // Executa a ordenação por nome
                insertionSortPorNome(copiaTrabalho, n, &metricas);

                printf("\nExibindo depois da ordenacao:");
                exibirRegistros("Depois da Ordenação (Ordem Alfabética)", copiaTrabalho, n);

                printf("\n--- MÉTRICAS DA ORDENAÇÃO ---\n");
                printf("Comparações: %d\n", metricas.comparacoes);
                printf("Deslocamentos: %d\n", metricas.deslocamentos);
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

int main() {
    menuCentral();
    return 0;
}