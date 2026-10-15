#include <stdio.h>
#include <stdlib.h>

// Estrutura da partida
typedef struct {
    int id;
    char jogador[50];
    int pontuacao;
} Partida;

// Função para gravar os dados no arquivo
void salvarPartida(const char *nomeArquivo, Partida p) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    // Grava os campos em um formato textual consistente
    fprintf(arquivo, "%d %s %d\n", p.id, p.jogador, p.pontuacao);

    fclose(arquivo); // Fecha após escrita
    printf("Dados salvos com sucesso!\n\n");
}

// Função para ler e exibir os dados do arquivo
void lerPartida(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
        return;
    }

    Partida p;

    // Ler somente enquanto a operação retornar sucesso (fscanf retorna a quantidade de itens lidos)
    if (fscanf(arquivo, "%d %49s %d", &p.id, p.jogador, &p.pontuacao) == 3) {
        printf("--- Dados recuperados do arquivo ---\n");
        printf("ID: %d\n", p.id);
        printf("Jogador: %s\n", p.jogador);
        printf("Pontuacao: %d\n", p.pontuacao);
    } else {
        printf("Erro ao ler os dados do arquivo.\n");
    }

    fclose(arquivo); // Fecha após leitura
}

int main() {
    const char *nomeArquivo = "relatorio_partida.txt";

    // Instância com dados para teste
    Partida partida1 = {1, "Adriam", 1500};

    // Fluxo 1: Escrita
    salvarPartida(nomeArquivo, partida1);

    // Fluxo 2: Leitura
    lerPartida(nomeArquivo);

    return 0;
}