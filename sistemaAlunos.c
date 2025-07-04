#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// struct aluno
struct aluno {
    char nome[50];
    char matricula[14];
};

// Função para gerar a matrícula
void gerarMatricula(char* matricula, int numAluno) {
    sprintf(matricula, "20251CECA%04d", numAluno);
}

// Função para cadastrar alunos
struct aluno* cadastroDeAlunos(int* qtdAlunos) {
    printf("Quantidade de alunos a serem cadastrados: ");
    scanf("%d", qtdAlunos);

    // Alocar memória para armazenar os alunos
    struct aluno* vetorAlunos = malloc((*qtdAlunos) * sizeof(struct aluno));

    for (int i = 0; i < *qtdAlunos; i++) {
        printf("Digite o nome do aluno %d: ", i + 1);
        scanf("%s", vetorAlunos[i].nome);

        // Gerar a matrícula do aluno
        gerarMatricula(vetorAlunos[i].matricula, i + 1);

        //printf("Matricula do aluno %d: %s\n", i + 1, vetorAlunos[i].matricula);
    }

    return vetorAlunos;
}

int main() {
    printf("----------------------------- Sistemas de Alunos ------------------------------------------------\n");
    printf("0 - SAIR DA APLICACAO\n");
    printf("1 - CADASTRAR DE ALUNOS\n");
    printf("2 - ...\n");
    printf("3 - ...\n");
    printf("4 - ...\n");
    printf("5 - ---\n");
    printf("6 - ---\n");
    printf("7 - ---\n");
    printf("8 - ---\n");
    printf("9 - ---\n");
    printf("10 - ---\n");
    printf("11 - ---\n");
    printf("12 - ---\n");
    printf("13 - SOBRE\n\n");

    printf("DIGITE A OPCAO DESEJADA: ");

    int entrada;
    scanf("%d", &entrada);

    while (entrada < 0 || entrada > 13) {
        printf("\nOPCAO INVALIDA! DIGITE NOVAMENTE: \n");
        scanf("%d", &entrada);
    }

    int qtdAlunos;

    switch(entrada) {
        case 0:
            printf("\nSaindo da aplicacao...\n");
            return 0;
            break;
        case 1:
            printf("\nOpcao 1 'Cadastro de alunos' selecionada...\n\n");
            printf("---------------------------------------------------------\n\n");
            
            struct aluno* alunos = cadastroDeAlunos(&qtdAlunos);
            printf("\nAlunos cadastrados:\n");
            for (int i = 0; i < qtdAlunos; i++) {
                printf("Nome: %s, Matricula: %s\n", alunos[i].nome, alunos[i].matricula);
            }
            // Liberar a memória alocada
            free(alunos);
            
            break;
        case 2:
            printf("\nOpcao 2 ' ' selecionada...\n");
            printf("---------------------------------------------------------\n\n");
            break;
    }
}