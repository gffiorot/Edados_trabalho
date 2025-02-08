#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"

void iniciarBancoDadosPacientes(BDPaciente *bd) {
    bd->inicio = NULL;
}

Paciente* criarPaciente(int id, const char *cpf, const char *nome, int idade, const char *dataCadastro) {
    Paciente *paciente = (Paciente*) malloc(sizeof(Paciente));
    if (paciente) {
        paciente->id = id;
        strcpy(paciente->cpf, cpf);
        strcpy(paciente->nome, nome);
        paciente->idade = idade;
        strcpy(paciente->dataCadastro, dataCadastro);
        paciente->proximo = NULL;
    }
    return paciente;
}

int gerarNovoIdPaciente(BDPaciente *bd) {
    int maxId = 0;
    Paciente *atual = bd->inicio;
    while (atual) {
        if (atual->id > maxId)
            maxId = atual->id; // CORRIGIDO
        atual = atual->proximo;
    }
    return maxId + 1;
}

void inserirPaciente(BDPaciente *bd, Paciente *novoPaciente) {
    if (bd->inicio == NULL) {
        bd->inicio = novoPaciente;
    } else {
        Paciente *atual = bd->inicio;
        while (atual->proximo) {
            atual = atual->proximo;
        }
        atual->proximo = novoPaciente;
    }
}

Paciente* buscarPacientePorId(BDPaciente *bd, int id) {
    Paciente *atual = bd->inicio;
    while (atual) {
        if (atual->id == id)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void removerPaciente(BDPaciente *bd, int id) {
    Paciente *atual = bd->inicio;
    Paciente *anterior = NULL;
    while (atual) {
        if (atual->id == id) {
            if (anterior == NULL)
                bd->inicio = atual->proximo;
            else
                anterior->proximo = atual->proximo;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

void exibirListaPacientes(BDPaciente *bd) {
    //Print with correct format for spacing
    printf("%-4s | %-14s | %-15s | %-6s | %-s\n", "ID","CPF","Nome","Idade","Data_Cadastro");
    Paciente *atual = bd->inicio;
    while (atual) {
        printf("%-4d | %-14s | %-15s | %-6d | %-s\n",
               atual->id, atual->cpf, atual->nome, atual->idade, atual->dataCadastro);
        atual = atual->proximo;
    }
}
