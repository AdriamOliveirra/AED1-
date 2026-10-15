#include <stdio.h>
#include <stdlib.h>

// Estrutura da partida
typedef struct {
    int id;
    char jogador[50];
    int pontuacao;
} Partida;

// Função para gravar os dados no fim do arquivo (Modo Anexação "a")
void salvarPartida(const char *nomeArquivo, Partida p) {
    // Modo "a" abre para escrita no final do arquivo, preservando dados antigos
    FILE *arquivo = fopen(nomeArquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    // Grava os campos em um formato textual consistente
    fprintf(arquivo, "%d %s %d\n", p.id, p.jogador, p.pontuacao);

    fclose(arquivo); // Fecha após escrita
    printf("Partida do(a) %s salva no histórico com sucesso!\n", p.jogador);
}

// Função para ler e exibir todo o histórico de partidas
void lerHistorico(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("\nHistórico vazio ou arquivo não encontrado!\n");
        return;
    }

    Partida p;
    int registrosLidos = 0;
    int resultadoLeitura;

    printf("\n--- HISTRICO COMPLETO DE PARTIDAS ---\n");

    // O laço é baseado no retorno do fscanf para evitar repetição do último registro
    while ((resultadoLeitura = fscanf(arquivo, "%d %49s %d", &p.id, p.jogador, &p.pontuacao)) == 3) {
        registrosLidos++;
        printf("[%d] ID: %d | Jogador: %s | Pontuação: %d\n", registrosLidos, p.id, p.jogador, p.pontuacao);
    }

    // Diferencia fim normal do arquivo de um dado malformado
    if (resultadoLeitura != EOF) {
        printf("\nAviso: Ocorreu um erro ao ler o arquivo (dado malformado ou corrompido)!\n");
    } else if (registrosLidos == 0) {
        printf("O histórico de partidas está vazio.\n");
    } else {
        printf("\nFim do relatório. Total de registros lidos: %d\n", registrosLidos);
    }

    fclose(arquivo); // Fecha após leitura
}

int main() {
    const char *nomeArquivo = "relatorio_partida.txt";

    // Instâncias com dados para teste incremental
    Partida partida1 = {1, "Adriam", 1500};
    Partida partida2 = {2, "Beatriz", 2100};
    Partida partida3 = {3, "Carlos", 1850};

    // Fluxo 1: Escrita incremental (Simulando várias partidas)
    salvarPartida(nomeArquivo, partida1);
    salvarPartida(nomeArquivo, partida2);
    salvarPartida(nomeArquivo, partida3);

    // Fluxo 2: Leitura do histórico completo
    lerHistorico(nomeArquivo);

    return 0;
}