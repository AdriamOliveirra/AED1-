#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar o jogador
typedef struct {
    char nome[50];
    int idade;
} Jogador;

int main() {
    int quantidade;

    printf("Digite a quantidade de jogadores da equipe: ");
    scanf("%d", &quantidade);

    // 1. Validar a quantidade solicitada
    if (quantidade <= 0) {
        printf("Quantidade invalida! O numero deve ser maior que zero.\n");
        return 1;
    }

    /* 
     * VANTAGEM DE USAR sizeof(*equipe):
     * Usar 'sizeof(*equipe)' em vez de 'sizeof(Jogador)' e mais seguro porque,
     * se o tipo da variavel 'equipe' for alterado no futuro, o calculo do tamanho
     * em bytes se adapta automaticamente, evitando erros de memoria.
     */

    // 2. Alocar com malloc(quantidade * sizeof(*ponteiro))
    Jogador *equipe = (Jogador *) malloc(quantidade * sizeof(*equipe));

    // 3. Verificar o retorno do malloc
    if (equipe == NULL) {
        printf("Erro ao alocar memoria! Operacao encerrada.\n");
        return 1; // Encerra sem acessar o ponteiro
    }

    // 4. Preencher somente posicoes validas
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Jogador %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", equipe[i].nome); // Le string com espacos
        printf("Idade: ");
        scanf("%d", &equipe[i].idade);
    }

    // Exibir somente posicoes validas
    printf("\n=== ELENCO CADASTRADO ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Jogador %d: %s, %d anos\n", i + 1, equipe[i].nome, equipe[i].idade);
    }

    // 5. Liberar o bloco quando nao for mais necessario
    free(equipe);
    equipe = NULL;

    return 0;
}