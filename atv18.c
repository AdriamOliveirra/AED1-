#include <stdio.h>
#include <string.h>

#define MAX_VIDA 100

// Struct expandida para incluir posição (x, y) e pontuação
typedef struct {
    char nome[50];
    int nivel;
    int pontos_vida;
    int ataque;
    int x;
    int y;
    int pontuacao;
} Personagem;

// 1. Função de consulta: exibe os dados do personagem
void exibir_personagem(const Personagem *p) {
    if (p == NULL) return;
    printf("Nome: %-10s | Nivel: %2d | PV: %3d/%d | Pos: (%d, %d) | Pontos: %d\n", 
           p->nome, p->nivel, p->pontos_vida, MAX_VIDA, p->x, p->y, p->pontuacao);
}

// 2. Modifica a vida: valida ponteiro nulo e limites (0 a MAX_VIDA)
void alterar_vida(Personagem *p, int quantidade) {
    if (p == NULL) {
        printf("[Erro] Ponteiro nulo fornecido!\n");
        return;
    }

    p->pontos_vida += quantidade;

    // Regra de negócio: não permite vida negativa nem superior ao máximo
    if (p->pontos_vida > MAX_VIDA) {
        p->pontos_vida = MAX_VIDA;
    } else if (p->pontos_vida < 0) {
        p->pontos_vida = 0;
    }
}

// 3. Modifica a posição: altera as coordenadas x e y
void mover_personagem(Personagem *p, int delta_x, int delta_y) {
    if (p == NULL) {
        printf("[Erro] Ponteiro nulo fornecido!\n");
        return;
    }

    // Uso do operador seta (->)
    p->x += delta_x;
    p->y += delta_y;
}

// 4. Modifica a pontuação: demonstração da sintaxe equivalente (*p).membro
void adicionar_pontuacao(Personagem *p, int pontos) {
    if (p == NULL) {
        printf("[Erro] Ponteiro nulo fornecido!\n");
        return;
    }

    if (pontos < 0) {
        printf("[Aviso] Tentativa de adicionar pontuação negativa ignorada.\n");
        return;
    }

    // Demonstração da equivalência: (*p).pontuacao é exatamente igual a p->pontuacao
    (*p).pontuacao += pontos; 
}

int main() {
    // Inicialização do personagem com x=0, y=0 e pontuacao=0
    Personagem heroi = {"Aragorn", 10, 100, 25, 0, 0, 0};

    printf("--- Estado Inicial ---\n");
    exibir_personagem(&heroi);

    // 1. Modificando a posição (avançar no mapa)
    printf("\n--- Mover Personagem (+5 em X, +3 em Y) ---\n");
    mover_personagem(&heroi, 5, 3);
    exibir_personagem(&heroi);

    // 2. Modificando os pontos (ganhar pontos)
    printf("\n--- Ganhar Pontuação (+250 pts) ---\n");
    adicionar_pontuacao(&heroi, 250);
    exibir_personagem(&heroi);

    // 3. Modificando a vida (receber dano)
    printf("\n--- Receber Dano (-40 PV) ---\n");
    alterar_vida(&heroi, -40);
    exibir_personagem(&heroi);

    // 4. Testando limite inferior (dano excessivo)
    printf("\n--- Receber Dano Letal (-100 PV) ---\n");
    alterar_vida(&heroi, -100); // Deve travar em 0
    exibir_personagem(&heroi);

    // 5. Testando limite superior (cura excessiva)
    printf("\n--- Curar Personagem (+150 PV) ---\n");
    alterar_vida(&heroi, 150); // Deve travar no MAX_VIDA (100)
    exibir_personagem(&heroi);

    // 6. Testando validação de ponteiro nulo
    printf("\n--- Teste com Ponteiro Nulo ---\n");
    Personagem *ponteiro_invalido = NULL;
    alterar_vida(ponteiro_invalido, 10);

    return 0;
}