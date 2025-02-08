#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "bd_paciente.h"

void carregarDadosPacientes(BDPaciente *bd, const char *caminhoArquivo);
void salvarDadosPacientes(BDPaciente *bd, const char *caminhoArquivo);

#endif
// ja modificado (nao precisa)