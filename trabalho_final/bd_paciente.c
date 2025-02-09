#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"

void iniciarBancoDadosPacientes(BDPaciente *bd) {
    bd->inicio = NULL;
}

Paciente* criarPaciente(int id, const char *cpf, const char *nome, int idade, const char *dataCadastro) {
    Paciente *paciente = (Paciente*) malloc(sizeof(Paciente));
    if (paciente != NULL) {
        paciente->id = id;
        strcpy(paciente->cpf, cpf);
        strcpy(paciente->nome, nome);
        paciente->idade = idade;
        strcpy(paciente->dataCadastro, dataCadastro);
        paciente->proximo = NULL; // Prepara o próximo nó a ser inserido, caso o usuário queira.
    }
    return paciente;
}

int gerarNovoIdPaciente(BDPaciente *bd) {
    int maxId = 0;
    Paciente *atual = bd->inicio;
    while (atual != NULL) {
        if (atual->id > maxId)
            maxId = atual->id; // Encontra o elemento (paciente) com maior ID (adicionado por último)
        atual = atual->proximo; 
    }
    return maxId + 1; // Retorna o ID disponível para ser usado pelo novo suposto elemento (novo paciente)
}

void inserirPaciente(BDPaciente *bd, Paciente *novoPaciente) {
    if (bd->inicio == NULL) { // Se a lista estiver vazia..
        bd->inicio = novoPaciente;
    } else {
        Paciente *atual = bd->inicio; // Nó temporario para buscar um 'local' disponivel na lista para inserir o nó 'novoPaciente'.
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoPaciente; // Insere o novoPaciente no próximo nó disponível (vazio).
    }
}

Paciente* buscarPacientePorId(BDPaciente *bd, int id) {
    Paciente *atual = bd->inicio;
    while (atual != NULL) {
        if (atual->id == id) // Encontra o ID fornecido
            return atual; // Retorna os dados do paciente com o ID fornecido
        atual = atual->proximo;
    }
    return NULL;
}

void removerPaciente(BDPaciente *bd, int id) {
    Paciente *atual = bd->inicio;
    Paciente *anterior = NULL;
    while (atual != NULL) {
        if (atual->id == id) {
            if (anterior == NULL) // Caso o paciente for o primeiro da lista
                bd->inicio = atual->proximo; // Atualiza a lista para o próximo nó/paciente
            else
                anterior->proximo = atual->proximo;
            free(atual); // Libera memoria do paciente com o ID fornecido
            return; // Como o paciente foi removido, termina a função
        }
        anterior = atual;
        atual = atual->proximo; 
    }
}

void exibirListaPacientes(BDPaciente *bd) { // Exibe na tela todos os pacientes em formato de 'tabela'
    printf("%-4s | %-14s | %-15s | %-6s | %-s\n", "ID","CPF","Nome","Idade","Data_Cadastro"); // Cabeçalho da tabela
    Paciente *atual = bd->inicio;
    while (atual != NULL) { // Percorre os pacientes da lista, imprimindo seus dados
        printf("%-4d | %-14s | %-15s | %-6d | %-s\n",
               atual->id, atual->cpf, atual->nome, atual->idade, atual->dataCadastro);
        atual = atual->proximo;
    }
}
