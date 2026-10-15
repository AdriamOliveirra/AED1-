#include <stdio.h>
#include <stdlib.h>

// Estrutura da partida
typedef struct {
    int id;
    char jogador[50];
    int pontuacao;
} Partida;

// Função para gravar dados iniciais para teste (Modo Anexação)
void salvarPartida(const char *nomeArquivo, Partida p) {
    FILE *arquivo = fopen(nomeArquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }
    fprintf(arquivo, "%d %s %d\n", p.id, p.jogador, p.pontuacao);
    fclose(arquivo);
}

// Função para aplicar a bonificação na pontuação da partida
int aplicarBonificacao(int pontuacao) {
    // Exemplo de regra: 10% de bônus sobre a pontuação atual + 100 pontos fixos
    return (int)(pontuacao * 1.10) + 100;
}

// Função principal de processamento/transformação entre arquivos
void processarResultadosTemporada(const char *arquivoOrigem, const char *arquivoDestino) {
    // 1. Verificar retorno da abertura do arquivo de origem
    FILE *fOrigem = fopen(arquivoOrigem, "r");
    if (fOrigem == NULL) {
        printf("Erro: Não foi possível abrir o arquivo de ORIGEM '%s' para leitura.\n", arquivoOrigem);
        return; // Nenhum arquivo aberto ainda
    }

    // 2. Verificar retorno da abertura do arquivo de destino
    FILE *fDestino = fopen(arquivoDestino, "w");
    if (fDestino == NULL) {
        printf("Erro: Não foi possível criar/abrir o arquivo de DESTINO '%s' para escrita (falha de permissão ou espaço).\n", arquivoDestino);
        fclose(fOrigem); // Garante que o arquivo de origem seja fechado no caminho de erro
        return;
    }

    Partida p;
    int registrosProcessados = 0;
    int resultadoLeitura;

    printf("\n--- INICIANDO PROCESSAMENTO DA TEMPORADA ---\n");

    // 3. Processar cada registro apenas quando a leitura for completa (retorno igual a 3)
    while ((resultadoLeitura = fscanf(fOrigem, "%d %49s %d", &p.id, p.jogador, &p.pontuacao)) == 3) {
        // Aplicação do bônus documentado
        int pontuacaoAntiga = p.pontuacao;
        p.pontuacao = aplicarBonificacao(p.pontuacao);

        // Escrever os dados transformados no arquivo de destino
        fprintf(fDestino, "%d %s %d\n", p.id, p.jogador, p.pontuacao);
        registrosProcessados++;

        printf("Processado: [%s] Pontuação original: %d -> Com bônus: %d\n", p.jogador, pontuacaoAntiga, p.pontuacao);
    }

    // Validação de integridade ao final da leitura
    if (resultadoLeitura != EOF) {
        printf("\nAviso: Ocorreu uma leitura incompleta ou dado malformado no arquivo de origem!\n");
    }

    // 4. Fechar os dois arquivos no caminho de sucesso
    fclose(fOrigem);
    fclose(fDestino);

    // 5. Apresentar a quantidade de registros processados
    printf("\nProcessamento concluído com sucesso!");
    printf("\nTotal de registros processados e salvos em '%s': %d\n", arquivoDestino, registrosProcessados);
}

int main() {
    const char *origem = "relatorio_partida.txt";
    const char *destino = "relatorio_final_temporada.txt";

    // Criando alguns dados de teste na origem
    Partida p1 = {1, "Adriam", 1500};
    Partida p2 = {2, "Beatriz", 2000};
    Partida p3 = {3, "Carlos", 1200};

    salvarPartida(origem, p1);
    salvarPartida(origem, p2);
    salvarPartida(origem, p3);

    // Executando o fluxo de transformação
    processarResultadosTemporada(origem, destino);

    return 0;
}