#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

#define MAX_LINHA 256

void carregarDadosPacientes(BDPaciente *bd, const char *caminhoArquivo) {
    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL)
        return;
    char linha[MAX_LINHA];
    while (fgets(linha, MAX_LINHA, arquivo)) {
        if (strlen(linha) < 5)
            continue; 
        // Leitura do campo id (primeiro campo)
        char *campo = strtok(linha, ","); // Separa os elementos com base na 'divisoria' virgula
        if (!campo) // Se não conseguir extrair o campo, pula a linha
            continue;
        int id = atoi(campo); // Transforma a string em inteiro, armazenando-o em id
        
        campo = strtok(NULL, ","); // Lendo o segundo campo (cpf)
        if (!campo)
            continue;
        char cpf[MAX_STR];
        strcpy(cpf, campo); // Copia o conteudo do campo para a variavel cpf
        
        campo = strtok(NULL, ",");
        if (!campo)
            continue;
        char nomePaciente[MAX_STR]; // Cria a variavel nomePaciente para armazenar o conteudo do campo obtido no arquivo
        strcpy(nomePaciente, campo); // Armazena o nome do paciente
        
        campo = strtok(NULL, ","); // Separa o campo 'idade'
        if (!campo)
            continue;
        int idade = atoi(campo);
        
        campo = strtok(NULL, "\n"); // Separa o campo que contém data de cadastro
        if (!campo)
            continue;
        char dataCadastro[MAX_STR];
        strcpy(dataCadastro, campo);
        
        Paciente *novoPaciente = criarPaciente(id, cpf, nomePaciente, idade, dataCadastro);
        // No código acima, cada campo separado anteriormente é 'levado' para a função a fim de criar o novo nó e inserindo na lista
        inserirPaciente(bd, novoPaciente); // O novo nó criado é inserido na lista encadeada
    }
    fclose(arquivo);
}

void salvarDadosPacientes(BDPaciente *bd, const char *caminhoArquivo) {
    FILE *arquivo = fopen(caminhoArquivo, "w"); 
    if (arquivo == NULL)
        return;
    Paciente *atual = bd->inicio;
    while (atual) { // Percorre toda a lista encadeada criada 
        fprintf(arquivo, "%d,%s,%s,%d,%s\n", 
                atual->id, atual->cpf, atual->nome, atual->idade, atual->dataCadastro);
        atual = atual->proximo;
    }
    // Escreve todos os registros no arquivo, salvando-os e atualizando o banco de dados
    fclose(arquivo);
}
