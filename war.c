// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
/*
Programa: Cadastro de Territórios
Descrição:
  Este programa cria uma base de dados simples de territórios.
  Cada território tem nome, cor do exército e quantidade de tropas.
  O usuário pode cadastrar 5 territórios e visualizar os dados logo após o preenchimento.

Requisitos atendidos:
  - Struct Territorio com os campos: nome, cor e tropas
  - Cadastro de 5 territórios
  - Exibição dos dados cadastrados
  - Entrada clara (mensagens para o usuário)
  - Saída formatada
  - Comentários explicativos para facilitar manutenção
*/

#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército
    int tropas;        // Quantidade de tropas
} Territorio;

int main() {
    // Vetor para armazenar até 5 territórios
    Territorio territorios[5];

    printf("=== Cadastro de Territorios ===\n");

    // Loop para cadastro dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("\nCadastro do territorio %d:\n", i + 1);

        // Leitura do nome do território
        printf("Digite o nome do territorio: ");
        scanf(" %29[^\n]", territorios[i].nome); // lê até 29 caracteres (evita overflow)

        // Leitura da cor do exército
        printf("Digite a cor do exercito: ");
        scanf(" %9s", territorios[i].cor); // lê string até 9 caracteres

        // Leitura da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos territórios cadastrados
    printf("\n=== Territorios cadastrados ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    printf("\nCadastro concluido!\n");
    return 0;
}
