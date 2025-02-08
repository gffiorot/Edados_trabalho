#ifndef BD_PACIENTE_H
#define BD_PACIENTE_H

#define MAX_STR 100

typedef struct Paciente {
    int id;
    char cpf[MAX_STR];
    char nome[MAX_STR];
    int idade;
    char dataCadastro[MAX_STR];
    struct Paciente *proximo;
} Paciente;

typedef struct {
    Paciente *inicio;
} BDPaciente;

// 
void iniciarBancoDadosPacientes(BDPaciente *bd);
Paciente* criarPaciente(int id, const char *cpf, const char *nome, int idade, const char *dataCadastro);
int gerarNovoIdPaciente(BDPaciente *bd);
void inserirPaciente(BDPaciente *bd, Paciente *novoPaciente);
Paciente* buscarPacientePorId(BDPaciente *bd, int id);
void removerPaciente(BDPaciente *bd, int id);

#endif
