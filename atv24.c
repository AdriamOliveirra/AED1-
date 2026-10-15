#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do jogo (Somente campos persistíveis, sem endereços/ponteiros)
typedef struct {
    int id;
    char jogador[50]; // Vetor fixo (alocado diretamente na struct, não é ponteiro)
    int pontuacao;
} Partida;

// Função para gravar uma partida em arquivo BINÁRIO (Modo "wb")
void salvarPartidaBinaria(const char *nomeArquivo, const Partida *p) {
    // Abertura em modo wb (Write Binary)
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo binário para escrita!\n");
        return;
    }

    // Usando sizeof para calcular o tamanho exato e conferindo o retorno de fwrite
    size_t itensEscritos = fwrite(p, sizeof(Partida), 1, arquivo);

    if (itensEscritos == 1) {
        printf("Registro gravado com sucesso em formato binário!\n");
    } else {
        printf("Erro ao gravar o registro no arquivo binário.\n");
    }

    fclose(arquivo); // Fechamento obrigatório
}

// Função para ler e restaurar partidas do arquivo BINÁRIO (Modo "rb")
void lerHistoricoBinario(const char *nomeArquivo) {
    // Abertura em modo rb (Read Binary)
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro: Arquivo não encontrado ou falha ao abrir '%s'.\n", nomeArquivo);
        return;
    }

    Partida p;
    size_t itensLidos;
    int contador = 0;

    printf("\n--- RESTAURANDO REGISTROS DO ARQUIVO BINÁRIO ---\n");

    // Leitura registro a registro com fread e verificação de integridade
    while ((itensLidos = fread(&p, sizeof(Partida), 1, arquivo)) == 1) {
        contador++;
        printf("[%d] ID: %d | Jogador: %s | Pontuação: %d (Objeto Reconstruído)\n", 
               contador, p.id, p.jogador, p.pontuacao);
    }

    // Tratamento de arquivo vazio ou leitura incompleta
    if (contador == 0) {
        if (feof(arquivo)) {
            printf("Aviso: O arquivo binário está vazio.\n");
        } else {
            printf("Erro ao tentar ler dados do arquivo.\n");
        }
    } else if (!feof(arquivo)) {
        // Se a leitura parou antes de chegar ao EOF natural, o último registro está incompleto/corrompido
        printf("\nAviso: Registro incompleto ou corrompido detectado no final do arquivo!\n");
    } else {
        printf("\nRestauração concluída. Total de objetos lidos: %d\n", contador);
    }

    fclose(arquivo); // Fechamento obrigatório
}

int main() {
    const char *nomeArquivoBin = "partida_salva.bin";

    // 1. Criando objeto original na memória
    Partida partidaOriginal = {101, "Adriam", 3450};

    printf("=== DADOS ORIGINAIS DA MEMÓRIA ===\n");
    printf("ID: %d | Jogador: %s | Pontuação: %d\n\n", 
           partidaOriginal.id, partidaOriginal.jogador, partidaOriginal.pontuacao);

    // 2. Gravando no arquivo binário (wb)
    salvarPartidaBinaria(nomeArquivoBin, &partidaOriginal);

    // 3. Lendo do arquivo binário e reconstruindo o objeto (rb)
    lerHistoricoBinario(nomeArquivoBin);

    return 0;
}