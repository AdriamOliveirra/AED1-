#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do jogo
typedef struct {
    int id;
    char jogador[50];
    int pontuacao;
} Partida;

// Estrutura para gerenciar a lista/temporada no programa
typedef struct {
    Partida *partidas;
    int quantidade;
} Temporada;

// Função para cadastrar uma nova partida no vetor em memória
void cadastrarPartida(Temporada *temp) {
    Partida nova;
    printf("\n--- Cadastrar Nova Partida ---\n");
    printf("ID da partida: ");
    scanf("%d", &nova.id);
    getchar(); // Limpar buffer do teclado

    printf("Nome do jogador: ");
    fgets(nova.jogador, sizeof(nova.jogador), stdin);
    nova.jogador[strcspn(nova.jogador, "\n")] = '\0'; // Remove o \n do final

    printf("Pontuação: ");
    scanf("%d", &nova.pontuacao);

    // Realoca a memória para acomodar mais um registro
    Partida *tempPtr = realloc(temp->partidas, (temp->quantidade + 1) * sizeof(Partida));
    if (tempPtr == NULL) {
        printf("Erro ao alocar memória para a nova partida!\n");
        return;
    }

    temp->partidas = tempPtr;
    temp->partidas[temp->quantidade] = nova;
    temp->quantidade++;

    printf("Partida cadastrada com sucesso!\n");
}

// Função para listar todas as partidas em memória
void listarPartidas(const Temporada *temp) {
    printf("\n--- PARTIDAS DA TEMPORADA (%d registradas) ---\n", temp->quantidade);
    if (temp->quantidade == 0) {
        printf("Nenhuma partida em memória.\n");
        return;
    }

    for (int i = 0; i < temp->quantidade; i++) {
        printf("[%d] ID: %d | Jogador: %-15s | Pontuação: %d\n", 
               i + 1, temp->partidas[i].id, temp->partidas[i].jogador, temp->partidas[i].pontuacao);
    }
}

// Função para salvar todo o vetor em uma única operação (com metadado)
void salvarTemporada(const char *nomeArquivo, const Temporada *temp) {
    if (temp->quantidade == 0) {
        printf("\nNenhuma partida em memória para salvar.\n");
        return;
    }

    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar/abrir o arquivo para escrita!\n");
        return;
    }

    // 1. Grava a quantidade antes dos registros (Metadado)
    if (fwrite(&temp->quantidade, sizeof(int), 1, arquivo) != 1) {
        printf("Erro ao gravar metadados no arquivo.\n");
        fclose(arquivo);
        return;
    }

    // 2. Grava o vetor completo em uma única operação
    size_t gravados = fwrite(temp->partidas, sizeof(Partida), temp->quantidade, arquivo);
    
    // 3. Conferir o total devolvido por fwrite
    if (gravados == (size_t)temp->quantidade) {
        printf("\nTemporada salva com sucesso! (%d partidas gravadas em '%s')\n", temp->quantidade, nomeArquivo);
    } else {
        printf("\nErro ao gravar os registros da temporada em lote.\n");
    }

    fclose(arquivo);
}

// Função para carregar a temporada e só substituir os dados em memória se tudo der certo
void carregarTemporada(const char *nomeArquivo, Temporada *temp) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("\nErro: Não foi possível abrir o arquivo '%s'.\n", nomeArquivo);
        return;
    }

    int qtdLida = 0;

    // 1. Lê a quantidade antes dos registros
    if (fread(&qtdLida, sizeof(int), 1, arquivo) != 1) {
        printf("\nErro ao ler os metadados do arquivo (arquivo vazio ou corrompido).\n");
        fclose(arquivo);
        return;
    }

    // 2. Verificar possíveis valores inválidos ao carregar
    if (qtdLida <= 0) {
        printf("\nQuantidade inválida de registros no arquivo (%d).\n", qtdLida);
        fclose(arquivo);
        return;
    }

    // 3. Alocar espaço dinâmico temporário para a quantidade registrada
    Partida *vetorTemporario = (Partida *)malloc(qtdLida * sizeof(Partida));
    if (vetorTemporario == NULL) {
        printf("\nErro de alocação de memória ao tentar carregar a temporada.\n");
        fclose(arquivo);
        return;
    }

    // 4. Conferir o total devolvido por fread
    size_t lidos = fread(vetorTemporario, sizeof(Partida), qtdLida, arquivo);
    if (lidos != (size_t)qtdLida) {
        printf("\nErro ao ler os dados do arquivo: quantidade de dados divergente dos metadados.\n");
        // Liberar memória e fechar arquivo em caso de erro
        free(vetorTemporario);
        fclose(arquivo);
        return;
    }

    // Se chegou até aqui com sucesso, substitui os dados atuais em memória
    if (temp->partidas != NULL) {
        free(temp->partidas); // Libera o vetor antigo da memória
    }

    temp->partidas = vetorTemporario;
    temp->quantidade = qtdLida;

    fclose(arquivo);
    printf("\nTemporada carregada com sucesso! (%d partidas restauradas)\n", temp->quantidade);
}

int main() {
    const char *nomeArquivo = "temporada_completa.bin";
    Temporada temporada = {NULL, 0};
    int opcao;

    do {
        printf("\n================ MENU TEMPORADA ================\n");
        printf("1. Cadastrar Partida\n");
        printf("2. Listar Partidas em Memória\n");
        printf("3. Salvar Temporada em Arquivo Binário\n");
        printf("4. Carregar Temporada do Arquivo Binário\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPartida(&temporada);
                break;
            case 2:
                listarPartidas(&temporada);
                break;
            case 3:
                salvarTemporada(nomeArquivo, &temporada);
                break;
            case 4:
                carregarTemporada(nomeArquivo, &temporada);
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    // Liberação final de memória
    if (temporada.partidas != NULL) {
        free(temporada.partidas);
    }

    return 0;
}