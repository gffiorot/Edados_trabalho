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
        char *campo = strtok(linha, ",");
        if (!campo)
            continue;
        int id = atoi(campo);
        
        campo = strtok(NULL, ",");
        if (!campo)
            continue;
        char cpf[MAX_STR];
        strcpy(cpf, campo);
        
        campo = strtok(NULL, ",");
        if (!campo)
            continue;
        char nomePaciente[MAX_STR];
        strcpy(nomePaciente, campo);
        
        campo = strtok(NULL, ",");
        if (!campo)
            continue;
        int idade = atoi(campo);
        
        campo = strtok(NULL, "\n");
        if (!campo)
            continue;
        char dataCadastro[MAX_STR];
        strcpy(dataCadastro, campo);
        
        Paciente *novoPaciente = criarPaciente(id, cpf, nomePaciente, idade, dataCadastro);
        inserirPaciente(bd, novoPaciente);
    }
    fclose(arquivo);
}

void salvarDadosPacientes(BDPaciente *bd, const char *caminhoArquivo) {
    FILE *arquivo = fopen(caminhoArquivo, "w");
    if (arquivo == NULL)
        return;
    Paciente *atual = bd->inicio;
    while (atual) {
        fprintf(arquivo, "%d,%s,%s,%d,%s\n",
                atual->id, atual->cpf, atual->nome, atual->idade, atual->dataCadastro);
        atual = atual->proximo;
    }
    fclose(arquivo);
}
//ja modificado (olhar depois)