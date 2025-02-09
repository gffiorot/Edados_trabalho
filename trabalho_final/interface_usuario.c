#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interface_usuario.h"

void mostrarMenuPrincipal() {
    printf("\n=============== SISTEMA DE GERENCIAMENTO DE PACIENTES ===============\n");
    printf("[1] Inserir paciente\n");
    printf("[2] Consultar paciente\n");
    printf("[3] Atualizar paciente\n");
    printf("[4] Remover paciente\n");
    printf("[5] Imprimir lista de pacientes\n");
    printf("[Q] Sair\n");
    printf("=====================================================================\n");
    printf("Digite a opção desejada: ");
}

int int_apenas(const char *string){
    while (*string){
        // Verifica se o caracter que o ponteiro aponta é um numero, se não retorna 0
        if (!isdigit(*string))
            return 0;

        // ponteiro segue para o proximo caracter da string
        string++;
    }
    return 1;
}


void formatarCPF(const char *cpfEntrada, char *cpfFormatado) {
    int i, j = 0; // i percorre cpfEntrada, j percorre cpfFormatado

    for (i = 0; i < 11; i++) {
        cpfFormatado[j++] = cpfEntrada[i];

        // Insere os separadores nos locais corretos e proguide o apenas cpfFormatado
         if (i == 2 || i == 5) {
            cpfFormatado[j++] = '.';
        } else if (i == 8) {
            cpfFormatado[j++] = '-';
        }
    }

    cpfFormatado[j] = '\0'; // Finaliza a string corretamente
}

int validar_data(const char *data)
{   
    int i;
    while(*data)
    {   // testando se o ano é formado por numeros
        for (i=0 ;i<4 ;i++){
            if (!isdigit(*data))
                return 0;
            data++;
        }
        // Testando se tem um traço entre o ano e o mes
        if (*data != '-')
            return 0;
        data++;

        // testando se o mês é formado por numeros
        for (i=0;i<2;i++){
            if (!isdigit(*data))
                return 0;
            data++;
        }
        // Testando se tem um traço entre o mes e o dia
        if (*data != '-')
            return 0;
        data++;
        
        // testando se o dia é formado por numeros
        for (i=0;i<2;i++){
            if (!isdigit(*data))
                return 0;
            else
                data++;
        }
    
        // Testa se ja chegou no fim da string
        if (*data != '\0')
            return 0;
    }
    return 1;

}

void processarInsercaoPaciente(BDPaciente *bd) {
    char cpf_inicial[MAX_STR], cpf[MAX_STR], nome[MAX_STR], data[MAX_STR];
    int idade;

    printf("Digite o CPF (11 números apenas): ");

    scanf("%s", cpf_inicial);
    // Validação do cpf
    while (strlen(cpf_inicial) != 11 || !int_apenas(cpf_inicial)){
        printf("CPF invalido digite 11 números: ");
        scanf("%s", cpf_inicial);
    }
    getchar();
    formatarCPF(cpf_inicial,cpf);

    // Nome não precisa de validação uma vez que qualquer coisa pode ser um nome
    printf("Digite o nome: ");
    fgets(nome, MAX_STR, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite a idade: ");
    scanf("%d", &idade);
    //Validação da idade
    while (idade<0){
        printf("Idade não pode ser negativo tente novamente: ");
        scanf("%d", &idade);
    }

    printf("Digite a data de cadastro (AAAA-MM-DD): ");
    scanf("%s", data);
    //Validação da data
    while (!validar_data(data)){
        printf("Data invalida tente novamente (AAAA-MM-DD): ");
        scanf("%s", data);
    }
    getchar();

    // Da um ID ao novo paciente e fornece todos os dados
    int novoID = gerarNovoIdPaciente(bd);
    Paciente *novoPaciente = criarPaciente(novoID, cpf, nome, idade, data);

    // Confirmação se os dados estão corretos
    printf("Confirma os novos valores para o registro abaixo? (S/N)\n\n");
    printf("%-4s | %-14s | %-20s | %-6s | %-s\n", "ID","CPF","Nome","Idade","Data_Cadastro");
    printf("%-4d | %-14s | %-20s | %-6d | %-s\n",
           novoPaciente->id, novoPaciente->cpf, novoPaciente->nome,
           novoPaciente->idade, novoPaciente->dataCadastro);

    char resp;
    scanf(" %c", &resp);
    getchar();
    
    while (resp != 'S' && resp!= 's' && resp!='N' && resp!='n'){
        printf("Opção invalida tente novamente (S/N): ");
        scanf(" %c", &resp);
    }
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
    char busca[MAX_STR], cpf_busca[MAX_STR];

    printf("Modo de consulta:\n1 - Por Nome\n2 - Por CPF\n3 - Voltar\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    if(opcao == 3) return;
    if(opcao == 1)
        printf("Digite o nome: ");
    else if(opcao == 2)
        printf("Digite o CPF completo (apenas números): ");
    else {
        printf("Opção inválida.\n");
        return;
    }

    fgets(busca, MAX_STR, stdin);
    busca[strcspn(busca, "\n")] = '\0';

    // Se for CPF ele valida se esta escrito de forma correta antes de formatar
    if(opcao == 2 && strlen(busca) == 11 && int_apenas(busca))
        formatarCPF(busca,cpf_busca);

    Paciente *paciente = bd->inicio;
    int encontrados = 0;
    printf("%-4s | %-14s | %-20s | %-6s | %-s\n", "ID","CPF","Nome","Idade","Data_Cadastro");
    while(paciente) { // Se for pesquisar por nome ele printa todos os nomes do csv que contem o nome pesquisado, porem só acha o cpf se ele for digitado inteiro
        if((opcao == 1 && strcasestr(paciente->nome, busca)) ||
           (opcao == 2 && !strcasecmp(paciente->cpf, cpf_busca))) {
            printf("%-4d | %-14s | %-20s | %-6d | %-s\n",
                   paciente->id, paciente->cpf, paciente->nome, paciente->idade, paciente->dataCadastro);
            encontrados++;
        }
        paciente = paciente->proximo;
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

    char novoCPF[MAX_STR],novoCPF_inicial[MAX_STR], novoNome[MAX_STR], novaIdadeStr[MAX_STR], novaData[MAX_STR];
    printf("Digite os novos valores (ou '_' para manter o atual):\n");

    printf("CPF: ");
    scanf("%s", novoCPF_inicial);
    //Validação do CPF
    if(strcmp(novoCPF_inicial, "_"))
    {
        while (strlen(novoCPF_inicial) != 11 || !int_apenas(novoCPF_inicial)){
            printf("CPF invalido digite 11 números: ");
            scanf("%s", novoCPF_inicial);
        }
        formatarCPF(novoCPF_inicial, novoCPF);
    } else{ // caso o usuario digite "_" o 'novo dado' cadastrado sera o que ja esta no campo de dados para facilitação de atualização
        strcpy(novoCPF, paciente->cpf);
    }
    getchar();

    printf("Nome: ");
    fgets(novoNome, MAX_STR, stdin);
    novoNome[strcspn(novoNome, "\n")] = '\0';
    if (!strcmp(novoNome, "_")) // caso o usuario digite "_" o 'novo dado' cadastrado sera o que ja esta no campo de dados para facilitação de atualização
        strcpy(novoNome, paciente->nome);
    

    printf("Idade: ");
    scanf("%s", novaIdadeStr);
     //Validação da idade
    if(strcmp(novaIdadeStr, "_")){
        while (novaIdadeStr[0]=='-'){
            printf("Idade não pode ser negativo tente novamente: ");
            scanf("%s", novaIdadeStr);
        }
    } else { // caso o usuario digite "_" o 'novo dado' cadastrado sera o que ja esta no campo de dados para facilitação de atualização
        sprintf(novaIdadeStr, "%d", paciente->idade);
    }

    
    printf("Digite a data de cadastro (AAAA-MM-DD): ");
    scanf("%s", novaData);
    //Validação da Data
    if(strcmp(novaData, "_") ){
        while (!validar_data(novaData)){
            printf("Data invalida tente novamente (AAAA-MM-DD): ");
            scanf("%s", novaData);
        }
    } else { // caso o usuario digite "_" o 'novo dado' cadastrado sera o que ja esta no campo de dados para facilitação de atualização
        strcpy(novaData, paciente->dataCadastro);
    }
    getchar();


    printf("Confirma a atualização? (S/N)\n");
    printf("%-4s | %-14s | %-20s | %-6s | %-s\n", "ID","CPF","Nome","Idade","Data_Cadastro");
    printf("%-4d | %-14s | %-20s | %-6s | %-s\n", paciente->id, novoCPF, novoNome, novaIdadeStr, novaData);

    char resp;
    scanf(" %c", &resp);
    getchar();
    
    while (resp != 'S' && resp!= 's' && resp!='N' && resp!='n'){
        printf("Opção invalida tente novamente (S/N): ");
        scanf(" %c", &resp);
    }
    if(resp == 'S' || resp == 's'){
        printf("Registro atualizado com sucesso.\n");
        strcpy(paciente->cpf, novoCPF);
        strcpy(paciente->nome, novoNome);
        paciente->idade = atoi(novaIdadeStr);
        strcpy(paciente->dataCadastro, novaData);
    }
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
    printf("%-4s | %-14s | %-20s | %-6s | %-s\n", "ID","CPF","Nome","Idade","Data_Cadastro");
    printf("%-4d | %-14s | %-20s | %-6d | %-s\n",
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
