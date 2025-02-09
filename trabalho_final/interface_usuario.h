#ifndef INTERFACE_USUARIO_H
#define INTERFACE_USUARIO_H

#include "bd_paciente.h"

// Função que exibe o menu principal do sistema com as opções disponíveis, como inserir, consultar, entre outros.
void mostrarMenuPrincipal(void);

// Função que verifica se todos os caracteres de uma string recebida são números inteiros.
int int_apenas(const char *string);

// Função que formata o CPF adicionando "." e "-" onde necessario. Precisa do CPF e uma segunda variavel pra receber o CPF formatado
void formatarCPF(const char *cpfEntrada, char *cpfFormatado);

// Serve para validar se a data recebida foi digitada no formato correto (AAAA-MM-DD)
int validar_data(const char *data);

// Função que processa a inserção de um novo paciente no banco de dados. Para isso, solicita ao usuário os dados necessários e cria um novo registro.
void processarInsercaoPaciente(BDPaciente *bd);

/* Função que processa a consulta de um paciente no banco de dados. Solicita ao usuário se ele quer pesquisar por nome ou cpf, o nome pode ser apenas o inivio, 
mas o cpf tem que ser digitado inteiro */
void processarConsultaPaciente(BDPaciente *bd);

/* Função responsável por processar a atualização dos dados de um paciente existente no banco de dados, solicitando ao usuário o ID do paciente e os novos dados
a serem atualizados. Além de confirmar no final se quer realmente atualizar*/
void processarAtualizacaoPaciente(BDPaciente *bd);

// Função que processa a remoção de um paciente do banco de dados, solicitando ao usuário o ID do paciente e removendo o registro correspondente (se encontrado).
void processarRemocaoPaciente(BDPaciente *bd);

// Função que exibe todos os pacientes cadastrados no banco de dados, mostrando informações como ID, CPF, nome, idade e data de cadastro.
void exibirListaPacientes(BDPaciente *bd);

#endif
