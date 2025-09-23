/*
Programa: Simulação de WAR estruturado
Descrição:
  Sistema de cadastro e simulação de ataques entre territórios.
  O jogador informa quantos territórios deseja cadastrar.
  Cada território tem nome, cor do exército e tropas.
  O programa exibe o estado atual do "mapa do mundo" e permite ataques
  entre territórios até que o atacante digite 0 para encerrar.

Requisitos atendidos:
  - Cadastro dinâmico de territórios
  - Exibição formatada do mapa
  - Fase de ataque com dados aleatórios
  - Atualização das tropas e controle do território
  - Uso de ponteiros e liberação de memória
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para exibir o banner
void exibirMapa(Territorio *mapa, int qtd) {
    printf("\n==================================================\n");
    printf("         MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("==================================================\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função para simular o ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        int perdas = dadoAtacante; // defensor perde tropas equivalentes ao valor do dado atacante
        defensor->tropas -= perdas;
        if (defensor->tropas <= 0) {
            printf("VITÓRIA DO ATACANTE! %s conquistou o território %s!\n",
                   atacante->nome, defensor->nome);
            defensor->tropas = atacante->tropas / 2; // metade das tropas avançam
            strcpy(defensor->cor, atacante->cor);   // muda dono
        } else {
            printf("VITÓRIA DO ATACANTE! O defensor perdeu %d tropas\n", perdas);
        }
    } else {
        atacante->tropas -= 1; // atacante perde 1 tropa
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("DEFENSOR RESISTIU! O atacante perdeu 1 tropa.\n");
    }
}

int main() {
    srand(time(NULL));
    int qtd;

    printf("Digite a quantidade de territorios: ");
    scanf("%d", &qtd);

    Territorio *mapa = (Territorio*) malloc(qtd * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < qtd; i++) {
        printf("\nCadastro do territorio %d:\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Digite a cor do exercito: ");
        scanf(" %9s", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    // Exibir o mapa inicial
    exibirMapa(mapa, qtd);

    // Loop da fase de ataque
    while (1) {
        int atacante, defensor;

        printf("\nFASE DE ATAQUE\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", qtd);
        scanf("%d", &atacante);

        if (atacante == 0) break; // sair do jogo

        if (atacante < 1 || atacante > qtd) {
            printf("Opcao invalida!\n");
            continue;
        }

        printf("Escolha o territorio defensor (1 a %d): ", qtd);
        scanf("%d", &defensor);

        if (defensor < 1 || defensor > qtd || defensor == atacante) {
            printf("Opcao invalida!\n");
            continue;
  /*
Programa: Simulação de WAR estruturado
Descrição:
  Sistema de cadastro e simulação de ataques entre territórios.
  O jogador informa quantos territórios deseja cadastrar.
  Cada território tem nome, cor do exército e tropas.
  O programa exibe o estado atual do "mapa do mundo" e permite ataques
  entre territórios até que o atacante digite 0 para encerrar.

Requisitos atendidos:
  - Cadastro dinâmico de territórios
  - Exibição formatada do mapa
  - Fase de ataque com dados aleatórios
  - Atualização das tropas e controle do território
  - Uso de ponteiros e liberação de memória
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para exibir o banner
void exibirMapa(Territorio *mapa, int qtd) {
    printf("\n==================================================\n");
    printf("         MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("==================================================\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função para simular o ataque
void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dadoAtacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        int perdas = dadoAtacante; // defensor perde tropas equivalentes ao valor do dado atacante
        defensor->tropas -= perdas;
        if (defensor->tropas <= 0) {
            printf("VITÓRIA DO ATACANTE! %s conquistou o território %s!\n",
                   atacante->nome, defensor->nome);
            defensor->tropas = atacante->tropas / 2; // metade das tropas avançam
            strcpy(defensor->cor, atacante->cor);   // muda dono
        } else {
            printf("VITÓRIA DO ATACANTE! O defensor perdeu %d tropas\n", perdas);
        }
    } else {
        atacante->tropas -= 1; // atacante perde 1 tropa
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("DEFENSOR RESISTIU! O atacante perdeu 1 tropa.\n");
    }
}

int main() {
    srand(time(NULL));
    int qtd;

    printf("Digite a quantidade de territorios: ");
    scanf("%d", &qtd);

    Territorio *mapa = (Territorio*) malloc(qtd * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < qtd; i++) {
        printf("\nCadastro do territorio %d:\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Digite a cor do exercito: ");
        scanf(" %9s", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    // Exibir o mapa inicial
    exibirMapa(mapa, qtd);

    // Loop da fase de ataque
    while (1) {
        int atacante, defensor;

        printf("\nFASE DE ATAQUE\n");
        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", qtd);
        scanf("%d", &atacante);

        if (atacante == 0) break; // sair do jogo

        if (atacante < 1 || atacante > qtd) {
            printf("Opcao invalida!\n");
            continue;
        }

        printf("Escolha o territorio defensor (1 a %d): ", qtd);
        scanf("%d", &defensor);

        if (defensor < 1 || defensor > qtd || defensor == atacante) {
            printf("Opcao invalida!\n");
            continue;
        }

        // Executa ataque
        atacar(&mapa[atacante - 1], &mapa[defensor - 1]);

        // Exibir o mapa atualizado
        exibirMapa(mapa, qtd);

        printf("\nPressione Enter para continuar para o proximo turno...");
        getchar(); // consome \n pendente
        getchar(); // aguarda enter
    }

    free(mapa); // Liberação de memória
    printf("\nJogo encerrado. Obrigado por jogar!\n");
    return 0;
}
      }

        // Executa ataque
        atacar(&mapa[atacante - 1], &mapa[defensor - 1]);

        // Exibir o mapa atualizado
        exibirMapa(mapa, qtd);

        printf("\nPressione Enter para continuar para o proximo turno...");
        getchar(); // consome \n pendente
        getchar(); // aguarda enter
    }

    free(mapa); // Liberação de memória
    printf("\nJogo encerrado. Obrigado por jogar!\n");
    return 0;
}
