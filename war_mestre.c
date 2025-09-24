/*
Programa: Simulação de WAR estruturado com Missões Estratégicas
Descrição:
  Sistema de cadastro e simulação de ataques entre territórios com missões estratégicas.
  - Cadastro dinâmico de territórios
  - Cada jogador recebe uma missão sorteada (armazenada dinamicamente)
  - Verificação automática de missão ao final de cada turno
  - Uso de ponteiros, malloc/free, modularização e comentários
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 10

// Estrutura do território
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Estrutura do jogador
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    char *missao;    // missão armazenada dinamicamente
    int missaoId;    // id da missão sorteada (para lógica de verificação)
} Jogador;

/* ---------- Protótipos ---------- */
void exibirMapa(Territorio *mapa, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);
void atribuirMissao(char **destino, char *missoes[], int totalMissoes, int *missaoId);
int verificarMissao(int missaoId, const char *corJogador, const char *corOponente, Territorio *mapa, int tamanho);
void exibirMissao(const char *nomeJogador, const char *missao);
void liberarMemoria(Territorio *mapa, Jogador *jogadores, int numJogadores);

/* ---------- Implementações ---------- */

// Exibe o banner e a lista de territórios
void exibirMapa(Territorio *mapa, int qtd) {
    printf("\n==================================================\n");
    printf("         MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("==================================================\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simula um ataque com dados (1 a 6)
// Se atacante vence: defensor perde 'perdas' tropas (valor do dado atacante).
// Se defensor fica com tropas <= 0, defensor muda de cor e recebe metade das tropas do atacante.
// Se defensor vence: atacante perde 1 tropa.
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 0) {
        printf("Atacante nao tem tropas suficientes para atacar.\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        int perdas = dadoAtacante;
        defensor->tropas -= perdas;
        if (defensor->tropas <= 0) {
            printf("VITÓRIA DO ATACANTE! %s conquistou o território %s!\n",
                   atacante->nome, defensor->nome);
            // defensor passa a pertencer ao atacante
            defensor->tropas = atacante->tropas / 2; // metade das tropas avançam
            strcpy(defensor->cor, atacante->cor);
            // atacante perde as tropas que avançaram
            atacante->tropas = atacante->tropas - defensor->tropas;
            if (atacante->tropas < 0) atacante->tropas = 0;
        } else {
            printf("VITÓRIA DO ATACANTE! O defensor perdeu %d tropas\n", perdas);
        }
    } else if (dadoDefensor > dadoAtacante) {
        int perdas = 1; // regra simples: atacante perde 1 tropa
        atacante->tropas -= perdas;
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("DEFENSOR RESISTIU! O atacante perdeu %d tropa(s).\n", perdas);
    } else {
        printf("EMPATE! Nenhuma tropa foi perdida.\n");
    }
}

// Atribui uma missão sorteada para 'destino'.
// 'destino' é um ponteiro para char*; a função aloca memória (malloc) e copia a string.
// Também preenche missaoId com o índice sorteado.
void atribuirMissao(char **destino, char *missoes[], int totalMissoes, int *missaoId) {
    if (totalMissoes <= 0) return;
    int idx = rand() % totalMissoes;
    *missaoId = idx;
    size_t len = strlen(missoes[idx]);
    *destino = (char*) malloc((len + 1) * sizeof(char));
    if (*destino == NULL) {
        printf("Erro ao alocar memoria para missao!\n");
        exit(1);
    }
    strcpy(*destino, missoes[idx]);
}

// Verifica se a missão foi cumprida.
// Recebe missaoId (para saber qual regra aplicar) e as cores do jogador e do oponente (útil para algumas missões).
// Retorna 1 se cumprida, 0 caso contrário.
int verificarMissao(int missaoId, const char *corJogador, const char *corOponente, Territorio *mapa, int tamanho) {
    int i;
    int contTerritorios = 0;
    int totalTropasJogador = 0;
    int totalTropasOponente = 0;
    int possuiCapital = 0;

    // calcula alguns agregados
    for (i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0) {
            contTerritorios++;
            totalTropasJogador += mapa[i].tropas;
        }
        if (strcmp(mapa[i].cor, corOponente) == 0) {
            totalTropasOponente += mapa[i].tropas;
        }
        // exemplo de missão que busca por um território chamado "Capital"
        if (strcmp(mapa[i].nome, "Capital") == 0 && strcmp(mapa[i].cor, corJogador) == 0) {
            possuiCapital = 1;
        }
    }

    // Interpretação das missões por id:
    // 0: "Conquistar 3 territórios"
    // 1: "Eliminar todas as tropas da cor inimiga"
    // 2: "Possuir mais de 10 tropas no total"
    // 3: "Conquistar o território chamado 'Capital'"
    // 4: "Conquistar pelo menos 2 territórios"

    switch (missaoId) {
        case 0:
            return (contTerritorios >= 3) ? 1 : 0;
        case 1:
            return (totalTropasOponente == 0) ? 1 : 0;
        case 2:
            return (totalTropasJogador > 10) ? 1 : 0;
        case 3:
            return (possuiCapital == 1) ? 1 : 0;
        case 4:
            return (contTerritorios >= 2) ? 1 : 0;
        default:
            return 0;
    }
}

// Exibe a missão do jogador (apenas uma vez, no início)
void exibirMissao(const char *nomeJogador, const char *missao) {
    printf("\n----------------------------\n");
    printf("Missao para %s:\n", nomeJogador);
    printf("%s\n", missao);
    printf("----------------------------\n");
}

// Libera memória alocada dinamicamente (mapa e missões dos jogadores)
void liberarMemoria(Territorio *mapa, Jogador *jogadores, int numJogadores) {
    if (mapa != NULL) free(mapa);
    for (int i = 0; i < numJogadores; i++) {
        if (jogadores[i].missao != NULL) {
            free(jogadores[i].missao);
            jogadores[i].missao = NULL;
        }
    }
    if (jogadores != NULL) free(jogadores);
}

/* ---------- Função principal (main) ---------- */

int main() {
    srand(time(NULL));

    int qtd;
    printf("Digite a quantidade de territorios: ");
    scanf("%d", &qtd);
    while (qtd <= 0) {
        printf("Quantidade invalida. Digite novamente: ");
        scanf("%d", &qtd);
    }
    getchar(); // limpa \n

    // Aloca mapa dinamicamente
    Territorio *mapa = (Territorio*) malloc(qtd * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < qtd; i++) {
        printf("\nCadastro do territorio %d:\n", i + 1);

        printf("Digite o nome do territorio: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Digite a cor do exercito: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpar \n
    }

    // Configuração dos jogadores (2 jogadores)
    int numJogadores = 2;
    Jogador *jogadores = (Jogador*) calloc(numJogadores, sizeof(Jogador));
    if (jogadores == NULL) {
        printf("Erro de alocacao de memoria para jogadores!\n");
        free(mapa);
        return 1;
    }

    for (int p = 0; p < numJogadores; p++) {
        printf("\nCadastro do jogador %d:\n", p + 1);
        printf("Nome do jogador: ");
        fgets(jogadores[p].nome, sizeof(jogadores[p].nome), stdin);
        jogadores[p].nome[strcspn(jogadores[p].nome, "\n")] = '\0';

        printf("Cor do jogador (use a mesma nomenclatura dos territorios): ");
        fgets(jogadores[p].cor, sizeof(jogadores[p].cor), stdin);
        jogadores[p].cor[strcspn(jogadores[p].cor, "\n")] = '\0';
        jogadores[p].missao = NULL;
        jogadores[p].missaoId = -1;
    }

    // Vetor de missões (pelo menos 5 conforme requisito)
    char *missoes[] = {
        "Conquistar 3 territorios.",
        "Eliminar todas as tropas da cor inimiga.",
        "Possuir mais de 10 tropas no total.",
        "Conquistar o territorio chamado 'Capital'.",
        "Conquistar pelo menos 2 territorios."
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Sorteia e atribui missão para cada jogador (armazenada dinamicamente)
    for (int p = 0; p < numJogadores; p++) {
        atribuirMissao(&jogadores[p].missao, missoes, totalMissoes, &jogadores[p].missaoId);
        // Exibe a missão apenas uma vez (no início)
        exibirMissao(jogadores[p].nome, jogadores[p].missao);
    }

    // Exibe o mapa inicial
    exibirMapa(mapa, qtd);

    // Loop da fase de ataque
    while (1) {
        int atacanteIdx, defensorIdx;

        printf("\nFASE DE ATAQUE\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", qtd);
        if (scanf("%d", &atacanteIdx) != 1) { // valida entrada
            printf("Entrada invalida.\n");
            while (getchar() != '\n'); // limpa
            continue;
        }

        if (atacanteIdx == 0) break; // sair do jogo

        if (atacanteIdx < 1 || atacanteIdx > qtd) {
            printf("Opcao invalida!\n");
            continue;
        }

        printf("Escolha o territorio defensor (1 a %d): ", qtd);
        if (scanf("%d", &defensorIdx) != 1) {
            printf("Entrada invalida.\n");
            while (getchar() != '\n');
            continue;
        }

        if (defensorIdx < 1 || defensorIdx > qtd || defensorIdx == atacanteIdx) {
            printf("Opcao invalida!\n");
            continue;
        }

        // Valida se atacante e defensor são de cores diferentes
        if (strcmp(mapa[atacanteIdx - 1].cor, mapa[defensorIdx - 1].cor) == 0) {
            printf("Ataque invalido: atacante e defensor possuem a mesma cor.\n");
            continue;
        }

        // Executa ataque
        atacar(&mapa[atacanteIdx - 1], &mapa[defensorIdx - 1]);

        // Exibir o mapa atualizado
        exibirMapa(mapa, qtd);

        // Verificar se algum jogador cumpriu a missão (verificação silenciosa)
        for (int p = 0; p < numJogadores; p++) {
            // determina cor oponente (assumindo 2 jogadores)
            const char *corOponente = (p == 0) ? jogadores[1].cor : jogadores[0].cor;
            if (verificarMissao(jogadores[p].missaoId, jogadores[p].cor, corOponente, mapa, qtd)) {
                printf("\n===== MISSÃO CUMPRIDA =====\n");
                printf("Jogador '%s' cumpriu a missao: %s\n", jogadores[p].nome, jogadores[p].missao);
                liberarMemoria(mapa, jogadores, numJogadores);
                printf("\nJogo encerrado. Parabens ao vencedor!\n");
                return 0;
            }
        }

        // pausa para próximo turno (aguarda Enter)
        printf("\nPressione Enter para continuar para o proximo turno...");
        while (getchar() != '\n'); // consome o \n pendente
        // agora aguarda um Enter extra
        getchar();
    }

    // Fim do jogo sem missão cumprida — libera memória
    liberarMemoria(mapa, jogadores, numJogadores);
    printf("\nJogo encerrado. Obrigado por jogar!\n");
    return 0;
}