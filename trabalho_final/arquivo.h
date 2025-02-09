#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "bd_paciente.h"

// Função para ler os registros de pacientes de um arquivo CSV, inserindo-os logo depois na estrutura de dados do sistema.
void carregarDadosPacientes(BDPaciente *bd, const char *caminhoArquivo);

// Função responsável por salvar os registros de pacientes da estrutura de dados em um arquivo CSV, sobrescrevendo o conteúdo anterior em seguida.
void salvarDadosPacientes(BDPaciente *bd, const char *caminhoArquivo);

#endif
