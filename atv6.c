#include <stdio.h>

#define MAX_PLATAFORMAS 5

// --- Funcoes de Vida e Pontuacao ---
void aplicar_dano(int *vida, int dano) {
    if (vida != NULL) {
        *vida -= dano;
    }
}

void restaurar_vida(int *vida) {
    if (vida != NULL) {
        *vida += 15;
    }
}

void aplicar_pontuacao_dupla(int *pontuacao) {
    if (pontuacao != NULL) {
        *pontuacao *= 2;
    }
}

// --- Funcoes do Mapa ---
void ler_mapa(int *mapa, int tamanho) {
    printf("\n--- CONFIGURACAO DO MAPA ---\n");
    for (int i = 0; i < tamanho; i++) {
        int valor;
        do {
            printf("Plataforma %d (1 a 100): ", i + 1);
            scanf("%d", &valor);
            if (valor < 1 || valor > 100) {
                printf("Valor invalido! Tente entre 1 e 100.\n");
            }
        } while (valor < 1 || valor > 100);

        *(mapa + i) = valor;
    }
}

void mostrar_mapa(const int *mapa, int tamanho) {
    printf("\n=== MAPA DA FASE ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Plataforma %d -> End: %p | Valor: %d\n", 
               i + 1, (void *)(mapa + i), *(mapa + i));
    }
}

void explorar_mapa(const int *mapa, int tamanho, int *pontuacao) {
    if (!mapa || !pontuacao || tamanho <= 0) return;

    const int *ptr = mapa;
    const int *fim = mapa + tamanho;
    int passos = 0;
    int pontos_coletados = 0;

    printf("\n=== INICIANDO EXPLORACAO ===\n");
    while (ptr < fim) {
        int valor = *ptr;
        pontos_coletados += valor;
        printf("Passo %d | End: %p | Valor: %d\n", passos + 1, (void *)ptr, valor);
        passos++;
        ptr++;
    }

    *pontuacao += pontos_coletados;
    printf("\n=== RESUMO DA EXPLORACAO ===\n");
    printf("Plataformas visitadas: %d\n", passos);
    printf("Pontos coletados: %d\n", pontos_coletados);
    printf("Pontuacao atualizada: %d\n", *pontuacao);
}

// --- Funcoes do Inventario (Atividade 06) ---

// 1. Exibir usando notacao de vetor: inventario[i]
void exibir_inventario_vetor(int *inventario[], int tamanho) {
    printf("\n--- INVENTARIO (Acesso por Colchetes) ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Item %d -> Aponta para: %p | Valor: %d\n", 
               i + 1, (void *)inventario[i], *inventario[i]);
    }
}

// 2. Modificar usando aritmetica de ponteiros: *(inventario + i)
void alterar_item_aritmetica(int **inventario, int tamanho) {
    int pos, novo_valor;
    printf("\nDigite o numero do item para alterar (1 a %d): ", tamanho);
    scanf("%d", &pos);

    if (pos < 1 || pos > tamanho) {
        printf("Item invalido!\n");
        return;
    }

    printf("Digite o novo valor para o item: ");
    scanf("%d", &novo_valor);

    // Acessa a posicao usando aritmetica de ponteiros *(inventario + i)
    // E altera o valor armazenado no endereco de destino
    ** (inventario + (pos - 1)) = novo_valor;
    printf("Item %d atualizado com sucesso!\n", pos);
}

int main() {
    int vida = 100;
    int pontuacao = 250;

    // Três itens guardados no estado do jogo
    int pocao_vida = 15;
    int moedas_ouro = 50;
    int escudo_forca = 80;

    // Vetor de ponteiros guardando os enderecos dos itens
    int *inventario[3] = {&pocao_vida, &moedas_ouro, &escudo_forca};
    int tam_inventario = 3;

    int mapa[MAX_PLATAFORMAS] = {10, 20, 30, 40, 50};
    int tam_mapa = MAX_PLATAFORMAS;

    int opcao;

    do {
        printf("\n================ MENU DE TESTES ================\n");
        printf("1. Ver Estado (Vida: %d | Pontos: %d)\n", vida, pontuacao);
        printf("2. Testar Acoes (Dano, Cura, Bonus)\n");
        printf("3. Configurar e Exibir Mapa\n");
        printf("4. Explorar Mapa\n");
        printf("5. Ver Inventario (Acesso por Colchetes)\n");
        printf("6. Alterar Item (Aritmetica de Ponteiros)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nStatus Atual -> Vida: %d | Pontuacao: %d\n", vida, pontuacao);
                break;
            case 2:
                aplicar_dano(&vida, 30);
                printf("Dano aplicado! Vida: %d\n", vida);
                restaurar_vida(&vida);
                printf("Cura aplicada! Vida: %d\n", vida);
                aplicar_pontuacao_dupla(&pontuacao);
                printf("Bonus aplicado! Pontuacao: %d\n", pontuacao);
                break;
            case 3:
                ler_mapa(mapa, tam_mapa);
                mostrar_mapa(mapa, tam_mapa);
                break;
            case 4:
                explorar_mapa(mapa, tam_mapa, &pontuacao);
                break;
            case 5:
                exibir_inventario_vetor(inventario, tam_inventario);
                break;
            case 6:
                alterar_item_aritmetica(inventario, tam_inventario);
                break;
            case 0:
                printf("\nEncerrando o simulador...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}