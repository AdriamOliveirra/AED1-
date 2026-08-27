#include <stdio.h>

// Função para aplicar dano na vida
void aplicar_dano(int *vida, int dano) {
    if (vida == NULL) return; // Validação do ponteiro
    
    printf("  [Funcao aplicar_dano] Endereco recebido: %p\n", (void *)vida);
    *vida -= dano;
}

// Função para restaurar a vida (cura padrão de +15)
void restaurar_vida(int *vida) {
    if (vida == NULL) return; // Validação do ponteiro
    
    printf("  [Funcao restaurar_vida] Endereco recebido: %p\n", (void *)vida);
    *vida += 15;
}

// Função para dobrar a pontuação do jogador
void aplicar_pontuacao_dupla(int *pontuacao) {
    if (pontuacao == NULL) return; // Validação do ponteiro
    
    printf("  [Funcao aplicar_pontuacao_dupla] Endereco recebido: %p\n", (void *)pontuacao);
    *pontuacao *= 2;
}

int main() {
    int vida = 100;
    int tesouro = 0; // 0 = inativo, 1 = ativo
    int pontuacao = 250;

    printf("=== ESTADO INICIAL ===\n");
    printf("Vida: %d | Endereco: %p\n", vida, (void *)&vida);
    printf("Tesouro: %d | Endereco: %p\n", tesouro, (void *)&tesouro);
    printf("Pontuacao: %d | Endereco: %p\n\n", pontuacao, (void *)&pontuacao);

    // 1. Aplicar Dano
    printf("--- Executando aplicar_dano(30) ---\n");
    aplicar_dano(&vida, 30);
    printf("Apos dano  -> Vida: %d\n\n", vida);

    // 2. Restaurar Vida
    printf("--- Executando restaurar_vida ---\n");
    restaurar_vida(&vida);
    printf("Apos cura -> Vida: %d\n\n", vida);

    // 3. Aplicar Pontuação Dupla
    printf("--- Executando aplicar_pontuacao_dupla ---\n");
    aplicar_pontuacao_dupla(&pontuacao);
    printf("Apos bonus -> Pontuacao: %d\n\n", pontuacao);

    printf("=== ESTADO FINAL ===\n");
    printf("Vida Final: %d\n", vida);
    printf("Pontuacao Final: %d\n", pontuacao);

    return 0;
}