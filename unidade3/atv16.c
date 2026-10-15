#include <stdio.h>
#include <string.h>

#define TAM_NOME 50

// Estrutura do Personagem
typedef struct {
    char nome[TAM_NOME];
    int nivel;
    int pontos_vida;
} Personagem;

// Função construtora
Personagem criar_personagem(const char *nome, int nivel, int pontos_vida) {
    Personagem p;
    strncpy(p.nome, nome, TAM_NOME - 1);
    p.nome[TAM_NOME - 1] = '\0'; // Garante o término seguro da string
    p.nivel = nivel;
    p.pontos_vida = pontos_vida;
    return p;
}

// Operação segura para atualizar o nome
void atualizar_nome(Personagem *p) {
    char novo_nome[TAM_NOME];

    printf("Digite o novo nome do personagem: ");
    // Leitura segura descartando o '\n' do buffer
    if (fgets(novo_nome, sizeof(novo_nome), stdin) != NULL) {
        novo_nome[strcspn(novo_nome, "\n")] = '\0'; // Remove a quebra de linha
        
        // Copia com limite de tamanho seguro
        strncpy(p->nome, novo_nome, TAM_NOME - 1);
        p->nome[TAM_NOME - 1] = '\0';
    }
}

// Função para exibir o registro completo
void exibir_personagem(const Personagem *p) {
    printf("\n--- Dados do Personagem ---\n");
    printf("Nome: %s\n", p->nome);
    printf("Nível: %d\n", p->nivel);
    printf("PV: %d\n", p->pontos_vida);
    printf("---------------------------\n");
}

int main() {
    // 1. Inicialização designada na declaração
    Personagem p1 = { .nome = "Guerreiro", .nivel = 1, .pontos_vida = 100 };
    printf("Personagem 1 (Inicialização Designada):");
    exibir_personagem(&p1);

    // 2. Inicialização via Função Construtora
    Personagem p2 = criar_personagem("Mago", 5, 60);
    printf("\nPersonagem 2 (Criado via Função Construtora):");
    exibir_personagem(&p2);

    // 3. Atualização segura do nome
    printf("\nAlterando nome do Personagem 2:\n");
    atualizar_nome(&p2);

    // 4. Exibição do registro completo após alteração
    exibir_personagem(&p2);

    return 0;
}