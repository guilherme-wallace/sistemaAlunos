#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ALUNOS 50
#define CURSO_PADRAO "CECA"
#define SEMESTRE_PADRAO 20251

typedef struct {
    char nome[50];
    char matricula[14];
    float nota1;
    float nota2;
    float media;
    int situacao; // 0-cursando, 1-aprovado, 2-reprovado
} Aluno;

Aluno turma[MAX_ALUNOS];
int totalAlunos = 0;
int proximoNumeroMatricula = 1;

void exibirSituacao(int situacao) {
    if (situacao == 0) {
        printf("Cursando\n");
    } else if (situacao == 1) {
        printf("Aprovado\n");
    } else {
        printf("Reprovado\n");
    }
}

void calcularMediaESituacao(int indiceAluno) {
    if (turma[indiceAluno].nota1 > 0 && turma[indiceAluno].nota2 > 0) {
        turma[indiceAluno].media = (turma[indiceAluno].nota1 + turma[indiceAluno].nota2) / 2.0;
        if (turma[indiceAluno].media < 6.0) {
            turma[indiceAluno].situacao = 2;
        } else {
            turma[indiceAluno].situacao = 1;
        }
        printf("Media calculada: %.2f, Nova Situacao: ", turma[indiceAluno].media);
        exibirSituacao(turma[indiceAluno].situacao);
    } else {
        turma[indiceAluno].situacao = 0; 
        printf("As duas notas ainda nao foram lancadas para calcular a media e situacao final.\n");
    }
}

void registrarNota1(int indiceAluno) {
    printf("Digite a Nota 1 para %s: ", turma[indiceAluno].nome);
    scanf("%f", &turma[indiceAluno].nota1);
    getchar();
    printf("Nota 1 registrada com sucesso para %s!\n", turma[indiceAluno].nome);
}

void registrarNota2(int indiceAluno) {
    printf("Digite a Nota 2 para %s (Nota 1 atual: %.2f): ", turma[indiceAluno].nome, turma[indiceAluno].nota1);
    scanf("%f", &turma[indiceAluno].nota2);
    getchar();
    printf("Nota 2 registrada com sucesso para %s!\n", turma[indiceAluno].nome);
    
    calcularMediaESituacao(indiceAluno);
}

void inserirUmAluno() {
    if (totalAlunos >= MAX_ALUNOS) {
        printf("\nNao e possivel inserir mais alunos. A turma esta cheia!\n");
        return;
    }

    printf("\n--- ADICIONAR ALUNO ---\n");
    
    snprintf(turma[totalAlunos].matricula, sizeof(turma[totalAlunos].matricula),
             "%d%s%04d", SEMESTRE_PADRAO, CURSO_PADRAO, proximoNumeroMatricula);
    
    printf("A matricula criada para este aluno e: %s\n", turma[totalAlunos].matricula);
    
    printf("Digite o nome do aluno: ");
    scanf(" %[^\n]", turma[totalAlunos].nome);  
    
    turma[totalAlunos].nota1 = 0.0;
    turma[totalAlunos].nota2 = 0.0;
    turma[totalAlunos].media = 0.0;
    turma[totalAlunos].situacao = 0;// 0 - Cursando

    printf("Aluno \"%s\" adicionado com sucesso!\n", turma[totalAlunos].nome);
    totalAlunos++;
    proximoNumeroMatricula++;
}

void inserirVariosAlunos() {
    char continuar = 's';

    while (continuar == 's') {
        inserirUmAluno();
        
        if (totalAlunos < MAX_ALUNOS) {
            printf("\nDeseja adicionar outro aluno? (s/n): ");
            getchar();
            scanf(" %c", &continuar);
        } else {
            printf("\nCapacidade maxima da turma atingida. Nao e possivel adicionar mais alunos.\n");
            continuar = 'n';
        }
    }
}

void imprimirDadosAluno() {
    char buscaMatricula[14];
    printf("\n--- INFORMACOES DO ALUNO ---\n");
    printf("Digite a matricula completa do aluno (ex: %d%s0001): ", SEMESTRE_PADRAO, CURSO_PADRAO);
    scanf("%s", buscaMatricula);
    getchar();

    int encontrado = 0;
    for (int i = 0; i < totalAlunos; i++) {
        if (strcmp(turma[i].matricula, buscaMatricula) == 0) {
            printf("\n--- DADOS DO ALUNO ENCONTRADO ---\n");
            printf("Matricula: %s\n", turma[i].matricula);
            printf("Nome: %s\n", turma[i].nome);
            printf("Nota 1: %.2f\n", turma[i].nota1);
            printf("Nota 2: %.2f\n", turma[i].nota2);
            printf("Media: %.2f\n", turma[i].media);
            printf("Situacao: ");
            exibirSituacao(turma[i].situacao);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Aluno com a matricula informada nao encontrado.\n");
    }
}

void imprimirRelacaoAlunos() {
    printf("\n--- LISTA DE TODOS OS ALUNOS ---\n");
    if (totalAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    for (int i = 0; i < totalAlunos; i++) {
        printf("Matricula: %s, Nome: %s, Situacao: ", turma[i].matricula, turma[i].nome);
        exibirSituacao(turma[i].situacao);
    }
}

void registrarNota1DeUmAluno() {
    char buscaMatricula[14];
    printf("\n--- REGISTRAR NOTA 1 DE UM ALUNO ---\n");
    printf("Digite a matricula completa do aluno: ");
    scanf("%s", buscaMatricula);
    getchar();

    int encontrado = 0;
    for (int i = 0; i < totalAlunos; i++) {
        if (strcmp(turma[i].matricula, buscaMatricula) == 0) {
            registrarNota1(i);
            if (turma[i].nota2 > 0) {
                printf("\nRecalculando media e situacao apos alterar Nota 1:\n");
                calcularMediaESituacao(i);
            }
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Aluno com a matricula informada nao encontrado.\n");
    }
}

void registrarNota1ParaTodosAlunos() {
    printf("\n--- REGISTRAR NOTA 1 PARA TODOS OS ALUNOS ---\n");
    if (totalAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    for (int i = 0; i < totalAlunos; i++) {
        registrarNota1(i);
        if (turma[i].nota2 > 0) {
            printf("\nRecalculando media e situacao apos alterar Nota 1 para %s:\n", turma[i].nome);
            calcularMediaESituacao(i);
        }
    }
    printf("Registro de Nota 1 para todos os alunos finalizado.\n");
}

void registrarNota2DeUmAluno() {
    char buscaMatricula[14];
    printf("\n--- REGISTRAR NOTA 2 DE UM ALUNO ---\n");
    printf("Digite a matricula completa do aluno: ");
    scanf("%s", buscaMatricula);
    getchar();

    int encontrado = 0;
    for (int i = 0; i < totalAlunos; i++) {
        if (strcmp(turma[i].matricula, buscaMatricula) == 0) {
            registrarNota2(i);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Aluno com a matricula informada nao encontrado.\n");
    }
}

void registrarNota2ParaTodosAlunos() {
    printf("\n--- REGISTRAR NOTA 2 PARA TODOS OS ALUNOS ---\n");
    if (totalAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    for (int i = 0; i < totalAlunos; i++) {
        registrarNota2(i);
    }
    printf("Registro de Nota 2 para todos os alunos finalizado.\n");
}

void recalcularMediaESituacaoGeral() {
    printf("\n--- RECALCULAR MEDIA E SITUACAO ---\n");
    if (totalAlunos == 0) {
        printf("Nenhum aluno cadastrado para recalcular.\n");
        return;
    }
    int atualizacoes = 0;
    for (int i = 0; i < totalAlunos; i++) {
        float mediaAntiga = turma[i].media;
        int situacaoAntiga = turma[i].situacao;

        calcularMediaESituacao(i); 

        if (mediaAntiga != turma[i].media || situacaoAntiga != turma[i].situacao) {
            printf("Atualizado: Matricula: %s, Nota1: %.2f, Nota2: %.2f, Media: %.2f, Situacao: ",
                   turma[i].matricula, turma[i].nota1, turma[i].nota2, turma[i].media);
            exibirSituacao(turma[i].situacao);
            atualizacoes++;
        }
    }
    printf("Recalculo finalizado. %d aluno(s) atualizado(s).\n", atualizacoes);
}

void imprimirMediaSituacaoDeUmAluno() {
    char buscaMatricula[14];
    printf("\n--- MEDIA E SITUACAO DE UM ALUNO ---\n");
    printf("Digite a matricula completa do aluno: ");
    scanf("%s", buscaMatricula);
    getchar();

    int encontrado = 0;
    for (int i = 0; i < totalAlunos; i++) {
        if (strcmp(turma[i].matricula, buscaMatricula) == 0) {
            printf("\n--- DADOS DE MEDIA E SITUACAO DO ALUNO ---\n");
            printf("Matricula: %s\n", turma[i].matricula);
            printf("Nome: %s\n", turma[i].nome);
            printf("Nota 1: %.2f\n", turma[i].nota1);
            printf("Nota 2: %.2f\n", turma[i].nota2);
            printf("Media: %.2f\n", turma[i].media);
            printf("Situacao: ");
            exibirSituacao(turma[i].situacao);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Aluno com a matricula informada nao encontrado.\n");
    }
}

void imprimirMediasSituacoesTodosAlunos() {
    printf("\n--- MEDIAS E SITUACOES DE TODOS OS ALUNOS ---\n");
    if (totalAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    for (int i = 0; i < totalAlunos; i++) {
        printf("Matricula: %s, Nome: %s, ", turma[i].matricula, turma[i].nome);
        if (turma[i].situacao == 0) { 
            printf("Situacao: Cursando\n"); 
        } else {
            printf("Media: %.2f, Situacao: ", turma[i].media);
            exibirSituacao(turma[i].situacao);
        }
    }
}

void imprimirAlunosAprovados() {
    printf("\n--- ALUNOS APROVADOS ---\n");
    if (totalAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    int encontrados = 0;
    for (int i = 0; i < totalAlunos; i++) {
        if (turma[i].situacao == 1) { 
            printf("Matricula: %s, Nome: %s, Media: %.2f\n", turma[i].matricula, turma[i].nome, turma[i].media);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhum aluno aprovado encontrado.\n");
    }
}

void imprimirAlunosReprovados() {
    printf("\n--- ALUNOS REPROVADOS ---\n");
    if (totalAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    int encontrados = 0;
    for (int i = 0; i < totalAlunos; i++) {
        if (turma[i].situacao == 2) { 
            printf("Matricula: %s, Nome: %s, Media: %.2f\n", turma[i].matricula, turma[i].nome, turma[i].media);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhum aluno reprovado encontrado.\n");
    }
}

void imprimirAlunosCursando() {
    printf("\n--- ALUNOS CURSANDO ---\n");
    if (totalAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    int encontrados = 0;
    for (int i = 0; i < totalAlunos; i++) {
        if (turma[i].situacao == 0) { 
            printf("Matricula: %s, Nome: %s\n", turma[i].matricula, turma[i].nome);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhum aluno cursando encontrado.\n");
    }
}

int main() {
    int opcao;

    do {        
        printf("\n----------------------------- SISTEMA DE GERENCIAMENTO DE ALUNOS ------------------------------------------------\n");
        printf(" 0 - SAIR DA APLICACAO\n");
        printf(" 1 - INSERIR UM REGISTRO DE ALUNO\n");
        printf(" 2 - INSERIR VARIOS REGISTROS DE ALUNOS\n");
        printf(" 3 - IMPRIMIR DADOS DE UM ALUNO\n");
        printf(" 4 - IMPRIMIR RELACAO DE ALUNOS (Matricula, Nome e Situacao)\n");
        printf(" 5 - REGISTRAR NOTA 1 DE UM ALUNO\n");
        printf(" 6 - REGISTRAR NOTA 1 PARA TODOS OS ALUNOS\n");
        printf(" 7 - REGISTRAR NOTA 2 DE UM ALUNO\n");
        printf(" 8 - REGISTRAR NOTA 2 PARA TODOS OS ALUNOS\n");
        printf(" 9 - RECALCULAR MEDIA E SITUACAO\n");
        printf("10 - IMPRIMIR MEDIA E SITUACAO DE UM ALUNO\n");
        printf("11 - IMPRIMIR MEDIAS E SITUACOES DE TODOS OS ALUNOS\n");
        printf("12 - IMPRIMIR ALUNOS APROVADOS\n");
        printf("13 - IMPRIMIR ALUNOS REPROVADOS\n");
        printf("14 - IMPRIMIR ALUNOS CURSANDO\n");
        printf("\nDIGITE A OPCAO DESEJADA: ");
        scanf("%d", &opcao); 
        getchar(); 

        switch (opcao) {
            case 0:
                printf("\nSaindo da aplicacao... Ate mais!\n");
                break;
            case 1:
                inserirUmAluno();
                break;
            case 2:
                inserirVariosAlunos();
                break;
            case 3:
                imprimirDadosAluno();
                break;
            case 4:
                imprimirRelacaoAlunos();
                break;
            case 5:
                registrarNota1DeUmAluno();
                break;
            case 6:
                registrarNota1ParaTodosAlunos();
                break;
            case 7:
                registrarNota2DeUmAluno();
                break;
            case 8:
                registrarNota2ParaTodosAlunos();
                break;
            case 9:
                recalcularMediaESituacaoGeral();
                break;
            case 10:
                imprimirMediaSituacaoDeUmAluno();
                break;
            case 11:
                imprimirMediasSituacoesTodosAlunos();
                break;
            case 12:
                imprimirAlunosAprovados();
                break;
            case 13:
                imprimirAlunosReprovados();
                break;
            case 14: 
                imprimirAlunosCursando();
                break;
            default:
                printf("\nOpcao invalida. Por favor, digite uma opcao entre 0 e 14.\n");
                break;
        }
        
        if (opcao != 0) { 
            printf("\nPressione Enter para continuar...");
            getchar(); 
        }
    } while (opcao != 0); 

    return 0; 
}
