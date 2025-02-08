#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interface_usuario.h"

void mostrarMenuPrincipal() {
    printf("\n========== SISTEMA DE GERENCIAMENTO DE PACIENTES ==========\n");
    printf("[1] Inserir paciente\n");
    printf("[2] Consultar paciente\n");
    printf("[3] Atualizar paciente\n");
    printf("[4] Remover paciente\n");
    printf("[5] Imprimir lista de pacientes\n");
    printf("[Q] Sair\n");
    printf("=============================================================\n");
    printf("Digite a opção desejada: ");
}

int int_apenas(const char *string){
    while (*string){
        if (!isdigit(*string))
            return 0;

        // vai para o proximo caracter da string
        string++;
    }
    return 1;
}


/*
char formatarCPF(const char *cpfEntrada) {
    int i, j = 0; // i percorre cpfEntrada, j percorre cpfFormatado
    char cpfFormatado;
    for (i = 0; i < 11; i++) {
        cpfFormatado[j++] = cpfEntrada[i];

        // Insere os separadores nos locais corretos
        if (i == 2 || i == 5) {
            cpfFormatado[j++] = '.';
        } else if (i == 8) {
            cpfFormatado[j++] = '-';
        }
    }
    cpfFormatado[j] = '\0'; // Finaliza a string corretamente

    return cpfFormatado;
}*/


void processarInsercaoPaciente(BDPaciente *bd) {
    char cpf[MAX_STR], nome[MAX_STR], data[MAX_STR];
    int idade;

    printf("Digite o CPF (11 números apenas): ");

    scanf("%s", cpf);
    // Validação do cpf
    while (strlen(cpf) != 11 || !int_apenas(cpf)){
        printf("CPF invalido digite 11 números: ");
        scanf("%s", cpf);
    }
    getchar();

    printf("Digite o nome: ");
    fgets(nome, MAX_STR, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite a idade: ");
    scanf("%d", &idade);
    //Validação da idade
    while (idade<0){
        printf("Idade não pode ser negativo tente novamente ");
        scanf("%d", &idade);
    }

    printf("Digite a data de cadastro (exemplo: 2022-08-24): ");
    scanf("%s", data);

    int novoID = gerarNovoIdPaciente(bd);
    Paciente *novoPaciente = criarPaciente(novoID, cpf, nome, idade, data);

    printf("Confirma os novos valores para o registro abaixo? (S/N)\n\n");
    printf("%-4s | %-14s | %-15s | %-6s | %-s\n", "ID","CPF","Nome","Idade","Data_Cadastro");
    printf("%-4d | %-14s | %-15s | %-6d | %-s\n",
           novoPaciente->id, novoPaciente->cpf, novoPaciente->nome,
           novoPaciente->idade, novoPaciente->dataCadastro);

    char resp;
    scanf(" %c", &resp);
    getchar();

    if(resp == 'S' || resp == 's') {
        inserirPaciente(bd, novoPaciente);
        printf("Paciente inserido com sucesso.\n");
    } else {
        free(novoPaciente);
        printf("Inserção cancelada.\n");
    }
}

void processarConsultaPaciente(BDPaciente *bd) {
    int opcao;
    char busca[MAX_STR];

    printf("Modo de consulta:\n1 - Por Nome\n2 - Por CPF\n3 - Voltar\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    if(opcao == 3) return;
    if(opcao == 1)
        printf("Digite o nome: ");
    else if(opcao == 2)
        printf("Digite o CPF: ");
    else {
        printf("Opção inválida.\n");
        return;
    }

    fgets(busca, MAX_STR, stdin);
    busca[strcspn(busca, "\n")] = '\0';

    Paciente *ptr = bd->inicio;
    int encontrados = 0;
    while(ptr) {
        if((opcao == 1 && strcasecmp(ptr->nome, busca) == 0) ||
           (opcao == 2 && strcasecmp(ptr->cpf, busca) == 0)) {
            printf("%-4s | %-14s | %-15s | %-6s | %-s\n", "ID","CPF","Nome","Idade","Data_Cadastro");
            printf("%-4d | %-14s | %-15s | %-6d | %-s\n",
                   ptr->id, ptr->cpf, ptr->nome, ptr->idade, ptr->dataCadastro);
            encontrados++;
        }
        ptr = ptr->proximo;
    }
    if(encontrados == 0)
        printf("Nenhum paciente encontrado.\n");
}

void processarAtualizacaoPaciente(BDPaciente *bd) {
    int idBusca;
    printf("Digite o ID do paciente a ser atualizado: ");
    scanf("%d", &idBusca);
    getchar();

    Paciente *paciente = buscarPacientePorId(bd, idBusca);
    if(!paciente) {
        printf("Paciente não encontrado.\n");
        return;
    }

    char novoCPF[MAX_STR], novoNome[MAX_STR], novaIdadeStr[MAX_STR], novaData[MAX_STR];
    printf("Digite os novos valores (ou '_' para manter o atual):\n");

    printf("CPF: ");
    scanf("%s", novoCPF);

    printf("Nome: ");
    scanf("%s", novoNome);

    printf("Idade: ");
    scanf("%s", novaIdadeStr);
    while (novaIdadeStr<0){
        printf("Idade não pode ser negativo tente novamente ");
        scanf("%s", novaIdadeStr);
    }
    printf("Data (AAAA-MM-DD): ");
    scanf("%s", novaData);
    getchar();

    if(strcmp(novoCPF, "_") != 0)
        strcpy(paciente->cpf, novoCPF);
    if(strcmp(novoNome, "_") != 0)
        strcpy(paciente->nome, novoNome);
    if(strcmp(novaIdadeStr, "_") != 0)
        paciente->idade = atoi(novaIdadeStr);
    if(strcmp(novaData, "_") != 0)
        strcpy(paciente->dataCadastro, novaData);

    printf("Confirma a atualização? (S/N)\n");
    printf("%-4s | %-14s | %-15s | %-6s | %-s\n", "ID","CPF","Nome","Idade","Data_Cadastro");
    printf("%-4d | %-14s | %-15s | %-6d | %-s\n",
           paciente->id, paciente->cpf, paciente->nome,
           paciente->idade, paciente->dataCadastro);

    char resp;
    scanf(" %c", &resp);
    getchar();
    if(resp == 'S' || resp == 's')
        printf("Registro atualizado com sucesso.\n");
    else
        printf("Atualização cancelada.\n");
}

void processarRemocaoPaciente(BDPaciente *bd) {
    int idBusca;
    exibirListaPacientes(bd);
    printf("Digite o ID do paciente a ser removido: ");
    scanf("%d", &idBusca);
    getchar();

    Paciente *paciente = buscarPacientePorId(bd, idBusca);
    if(!paciente) {
        printf("Paciente não encontrado.\n");
        return;
    }

    printf("Confirma a remoção do paciente abaixo? (S/N)\n");
    printf("%-4s | %-14s | %-15s | %-6s | %-s\n", "ID","CPF","Nome","Idade","Data_Cadastro");
    printf("%-4d | %-14s | %-15s | %-6d | %-s\n",
           paciente->id, paciente->cpf, paciente->nome,
           paciente->idade, paciente->dataCadastro);

    char resp;
    scanf(" %c", &resp);
    getchar();
    if(resp == 'S' || resp == 's') {
        removerPaciente(bd, idBusca);
        printf("Registro removido com sucesso.\n");
    } else {
        printf("Remoção cancelada.\n");
    }
}
