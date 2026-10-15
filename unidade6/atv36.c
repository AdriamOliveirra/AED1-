#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do Jogador com novo campo (vida)
typedef struct {
    int id;
    char nome[50];
    int pontuacao;
    int vida; // Novo critério ainda não utilizado
} Jogador;

// Métricas de execução
typedef struct {
    int comparacoes;
    int trocas;
    int passagens;
} Metricas;

// Enumeração para controlar a direção da ordenação
typedef enum {
    CRESCENTE = 1,
    DECRESCENTE = 2
} Ordem;

// --- FUNÇÃO DE COMPARAÇÃO DE JOGADORES ---

// Função genérica de comparação por Vida (HP) com suporte a ordem crescente/decrescente
int compararJogadoresPorVida(Jogador a, Jogador b, Ordem ordem) {
    if (a.vida != b.vida) {
        if (ordem == CRESCENTE) {
            return a.vida - b.vida; // Retorna > 0 se 'a' for maior
        } else {
            return b.vida - a.vida; // Retorna > 0 se 'b' for maior
        }
    }
    // Critério secundário de desempate por ID (crescente)
    return a.id - b.id;
}

// --- BUBBLE SORT PARA ESTRUTURAS ---

void bubbleSortJogadores(Jogador arr[], int n, Ordem ordem, Metricas *m) {
    m->comparacoes = 0;
    m->trocas = 0;
    m->passagens = 0;

    int houveTroca;

    for (int i = 0; i < n - 1; i++) {
        houveTroca = 0;
        m->passagens++;

        // Reduz a faixa útil a cada passagem
        for (int j = 0; j < n - 1 - i; j++) {
            m->comparacoes++;

            // Separa a regra de comparação da lógica de ordenação
            if (compararJogadoresPorVida(arr[j], arr[j + 1], ordem) > 0) {
                // Troca todos os membros do registro
                Jogador temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                houveTroca = 1;
                m->trocas++;
            }
        }

        // Aplica a parada antecipada
        if (!houveTroca) {
            break;
        }
    }
}

// --- VALIDAÇÃO DA ORDEM FINAL ---

int validarOrdemFinal(Jogador arr[], int n, Ordem ordem) {
    for (int i = 0; i < n - 1; i++) {
        if (compararJogadoresPorVida(arr[i], arr[i + 1], ordem) > 0) {
            return 0; // Falha na ordenação
        }
    }
    return 1; // Sucesso na ordenação
}

// --- FUNÇÕES DE IMPRESSÃO ---

void exibirJogadores(const char *titulo, Jogador arr[], int n) {
    printf("\n--- %s ---\n", titulo);
    for (int i = 0; i < n; i++) {
        printf("ID: %-3d | Nome: %-10s | Pontos: %-3d | Vida (HP): %d\n", 
               arr[i].id, arr[i].nome, arr[i].pontuacao, arr[i].vida);
    }
}

// --- CENTRAL / MENU PRINCIPAL ---

void menuCentral() {
    Jogador catalogoOriginal[] = {
        {101, "Carlos", 150, 80},
        {102, "Ana",    200, 100},
        {103, "Bruno",  180, 45},
        {104, "Diana",  250, 95},
        {105, "Eduardo",100, 45} // Empate em vida com Bruno (desempata por ID)
    };
    int n = sizeof(catalogoOriginal) / sizeof(catalogoOriginal[0]);

    Jogador copia[n];
    Metricas m;
    int opcao;

    do {
        printf("\n=============================================\n");
        printf("   CENTRAL DE ORDENACAO (BUBBLE SORT POR VIDA) \n");
        printf("=============================================\n");
        printf("1. Exibir registos originais\n");
        printf("2. Ordenar por VIDA [Crescente]\n");
        printf("3. Ordenar por VIDA [Decrescente]\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 2 || opcao == 3) {
            Ordem ordemSelecionada = (opcao == 2) ? CRESCENTE : DECRESCENTE;
            
            // Preserva a versão original
            memcpy(copia, catalogoOriginal, sizeof(catalogoOriginal));

            printf("\n>>> INDICAÇÃO: Ordenando pelo campo [VIDA] na direção [%s] <<<\n", 
                   (ordemSelecionada == CRESCENTE) ? "CRESCENTE" : "DECRESCENTE");

            exibirJogadores("Registos Antes da Ordenacao", copia, n);

            // Executa o Bubble Sort
            bubbleSortJogadores(copia, n, ordemSelecionada, &m);

            exibirJogadores("Registos Depois da Ordenacao", copia, n);

            // Apresenta as métricas obtidas
            printf("\n--- METRICAS DA EXECUCAO ---\n");
            printf("Passagens: %d\n", m.passagens);
            printf("Comparações: %d\n", m.comparacoes);
            printf("Trocas: %d\n", m.trocas);

            // Valida a ordem final
            if (validarOrdemFinal(copia, n, ordemSelecionada)) {
                printf("Validação do Resultado: SUCESSO (Vetor ordenado corretamente)\n");
            } else {
                printf("Validação do Resultado: FALHA (Vetor fora de ordem)\n");
            }
        } else if (opcao == 1) {
            exibirJogadores("Catálogo Original (Preservado)", catalogoOriginal, n);
        } else if (opcao != 0) {
            printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);
}

int main() {
    menuCentral();
    return 0;
}