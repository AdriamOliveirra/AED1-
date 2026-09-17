#include <stdio.h>
#include <string.h>

// Definindo o tipo próprio 'Personagem' com typedef
typedef struct {
    char nome[50];
    int nivel;
    int pontos_vida;
    int ataque;
} Personagem;

// 1. Função de consulta: exibe dados sem modificar o original
void exibir_personagem(Personagem p) {
    printf("Nome: %s | Nivel: %d | PV: %d | Ataque: %d\n", 
           p.nome, p.nivel, p.pontos_vida, p.ataque);
}

// 2. Função de consulta: calcula e retorna o poder total
int calcular_poder_total(Personagem p) {
    return (p.nivel * 10) + p.ataque;
}

// 3. Função de demonstração: altera a cópia local para provar a passagem por valor
void tentar_modificar_personagem(Personagem p) {
    p.nivel += 5;
    p.pontos_vida += 50;
    
    printf("\n--- [Dentro da Função] Cópia Alterada ---\n");
    exibir_personagem(p);
}

int main() {
    // Declaração usando apenas o tipo definido pelo typedef
    Personagem heroi = {"Aragorn", 10, 100, 25};

    printf("--- [Main] Estado Inicial ---\n");
    exibir_personagem(heroi);
    printf("Poder Total Calculado: %d\n", calcular_poder_total(heroi));

    // Chamada da função que modifica a cópia local
    tentar_modificar_personagem(heroi);

    // Comparando o estado externo após a função
    printf("\n--- [Main] Estado Após Chamada da Função ---\n");
    exibir_personagem(heroi);

    return 0;
}