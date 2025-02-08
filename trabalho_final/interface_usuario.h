#ifndef INTERFACE_USUARIO_H
#define INTERFACE_USUARIO_H

#include "bd_paciente.h"

void mostrarMenuPrincipal();
int int_apenas(const char *string);
//char formatarCPF(const char *cpfEntrada);
void processarInsercaoPaciente(BDPaciente *bd);
void processarConsultaPaciente(BDPaciente *bd);
void processarAtualizacaoPaciente(BDPaciente *bd);
void processarRemocaoPaciente(BDPaciente *bd);
void exibirListaPacientes(BDPaciente *bd);

#endif

// ja modificado (nao precisa)