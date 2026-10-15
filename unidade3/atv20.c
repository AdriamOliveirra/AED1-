#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VIDA 100
#define MAX_MEMBROS 20

// 1. Enumerador para Classe de Personagem
typedef enum {
    GUERREIRO = 1,
    MAGO,
    ARQUEIRO,
    LADINO
} Classe;

// 2. Estrutura aninhada: Posicao (coordenadas x, y)
typedef struct {
    int x;
    int y;
} Posicao;

// 3. Estrutura Personagem com Posicao aninhada e Classe (enum)
typedef struct {
    char nome[50];
    Classe classe;
    int nivel;
    int pontos_vida;
    int ataque;
    Posicao pos;
    int pontuacao;
} Personagem;

// 4. Estrutura Equipe para gerenciar o catálogo de personagens
typedef struct {
    char nome_equipe[50];
    Personagem membros[MAX_MEMBROS];
    int quantidade;
} Equipe;

// Função auxiliar: converte o valor do Enum para texto legível
const char* classe_para_texto(Classe c) {
    switch (c) {
        case GUERREIRO: return "Guerreiro";
        case MAGO:      return "Mago";
        case ARQUEIRO:   return "Arqueiro";
        case LADINO:    return "Ladino";
        default:        return "Desconhecida";
    }
}

// 1. Exibir Personagem (Trata estrutura aninhada e enum)
void exibir_personagem(const Personagem *p) {
    if (p == NULL) return;
    printf("Nome: %-10s | Classe: %-9s | Nivel: %2d | PV: %3d/%d | Pos: (%d, %d) | Pontos: %d\n",
           p->nome, classe_para_texto(p->classe), p->nivel, 
           p->pontos_vida, MAX_VIDA, p->pos.x, p->pos.y, p->pontuacao);
}

// 2. Cadastrar novo personagem na Equipe
void cadastrar_personagem(Equipe *eq) {
    if (eq == NULL) return;
    if (eq->quantidade >= MAX_MEMBROS) {
        printf("\n[Erro] Equipe cheia! Limite de %d membros atingido.\n", MAX_MEMBROS);
        return;
    }

    Personagem *p = &eq->membros[eq->quantidade];

    printf("\n--- Cadastrar Novo Personagem ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", p->nome);

    int opc_classe;
    printf("Escolha a Classe (1-Guerreiro, 2-Mago, 3-Arqueiro, 4-Ladino): ");
    scanf("%d", &opc_classe);
    if (opc_classe < 1 || opc_classe > 4) opc_classe = 1; // Default
    p->classe = (Classe)opc_classe;

    printf("Nivel: ");
    scanf("%d", &p->nivel);

    printf("Pontos de Vida Inicial (max %d): ", MAX_VIDA);
    scanf("%d", &p->pontos_vida);
    if (p->pontos_vida > MAX_VIDA) p->pontos_vida = MAX_VIDA;
    if (p->pontos_vida < 0) p->pontos_vida = 0;

    printf("Ataque: ");
    scanf("%d", &p->ataque);

    printf("Posicao Inicial (X Y): ");
    scanf("%d %d", &p->pos.x, &p->pos.y);

    p->pontuacao = 0;
    eq->quantidade++;

    printf(">> Personagem '%s' cadastrado com sucesso!\n", p->nome);
}

// 3. Listar todos os personagens do catálogo
void listar_equipe(const Equipe *eq) {
    if (eq == NULL) return;
    printf("\n================ [ Equipe: %s (%d/%d) ] ================\n", 
           eq->nome_equipe, eq->quantidade, MAX_MEMBROS);
    
    if (eq->quantidade == 0) {
        printf("Nenhum personagem cadastrado na equipe.\n");
        return;
    }

    for (int i = 0; i < eq->quantidade; i++) {
        printf("[%d] ", i + 1);
        exibir_personagem(&eq->membros[i]);
    }
}

// 4. Buscar personagem pelo nome (retorna ponteiro)
Personagem* buscar_personagem(Equipe *eq, const char *nome) {
    if (eq == NULL || nome == NULL) return NULL;
    for (int i = 0; i < eq->quantidade; i++) {
        if (strcasecmp(eq->membros[i].nome, nome) == 0) {
            return &eq->membros[i];
        }
    }
    return NULL;
}

// 5. Alterar dados (Vida/Posicao/Pontos) de um personagem existente
void alterar_personagem(Equipe *eq) {
    if (eq == NULL || eq->quantidade == 0) {
        printf("\nNenhum personagem disponivel para alteracao.\n");
        return;
    }

    char nome_busca[50];
    printf("\nDigite o nome do personagem que deseja alterar: ");
    scanf(" %[^\n]", nome_busca);

    Personagem *p = buscar_personagem(eq, nome_busca);
    if (p == NULL) {
        printf("[Erro] Personagem '%s' nao encontrado.\n", nome_busca);
        return;
    }

    int opcao;
    printf("\nAlterando '%s':\n", p->nome);
    printf("1. Alterar Vida\n");
    printf("2. Mover Posicao (X, Y)\n");
    printf("3. Adicionar Pontuacao\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            int delta;
            printf("Digite a variacao de vida (+ para cura, - para dano): ");
            scanf("%d", &delta);
            p->pontos_vida += delta;
            if (p->pontos_vida > MAX_VIDA) p->pontos_vida = MAX_VIDA;
            if (p->pontos_vida < 0) p->pontos_vida = 0;
            printf(">> Vida atualizada para %d!\n", p->pontos_vida);
            break;
        }
        case 2: {
            int dx, dy;
            printf("Deslocamento (delta X e delta Y): ");
            scanf("%d %d", &dx, &dy);
            p->pos.x += dx;
            p->pos.y += dy;
            printf(">> Nova posicao: (%d, %d)\n", p->pos.x, p->pos.y);
            break;
        }
        case 3: {
            int pts;
            printf("Pontos a adicionar: ");
            scanf("%d", &pts);
            if (pts > 0) p->pontuacao += pts;
            printf(">> Pontuacao atualizada para %d!\n", p->pontuacao);
            break;
        }
        default:
            printf("Opcao invalida.\n");
    }
}

int main() {
    Equipe minha_equipe;
    strcpy(minha_equipe.nome_equipe, "Sociedade do Anel");
    minha_equipe.quantidade = 0;

    // Preenchendo dados iniciais de exemplo
    minha_equipe.membros[0] = (Personagem){"Aragorn", GUERREIRO, 10, 100, 25, {0, 0}, 150};
    minha_equipe.membros[1] = (Personagem){"Gandalf", MAGO, 15, 90, 35, {1, 2}, 300};
    minha_equipe.quantidade = 2;

    int opcao = 0;
    do {
        printf("\n================ [ MENU DE GERENCIAMENTO ] ================\n");
        printf("1. Listar Equipe\n");
        printf("2. Cadastrar Personagem\n");
        printf("3. Buscar Personagem por Nome\n");
        printf("4. Alterar Atributos de Personagem\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listar_equipe(&minha_equipe);
                break;
            case 2:
                cadastrar_personagem(&minha_equipe);
                break;
            case 3: {
                char busca[50];
                printf("\nNome para busca: ");
                scanf(" %[^\n]", busca);
                Personagem *encontrado = buscar_personagem(&minha_equipe, busca);
                if (encontrado != NULL) {
                    printf("\n[Personagem Encontrado]:\n");
                    exibir_personagem(encontrado);
                } else {
                    printf("\n[Aviso] Personagem '%s' nao encontrado.\n", busca);
                }
                break;
            }
            case 4:
                alterar_personagem(&minha_equipe);
                break;
            case 0:
                printf("\nEncerrando sistema de catalogo...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}