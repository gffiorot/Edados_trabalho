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

// Função responsável por inicializar o banco de dados de pacientes, configurando o início da lista como NULL (vazia).
void iniciarBancoDadosPacientes(BDPaciente *bd);

// Funçao responsável por criar um novo registro de paciente com os dados fornecidos, retornando um ponteiro para a estrutura até então criada.
Paciente* criarPaciente(int id, const char *cpf, const char *nome, int idade, const char *dataCadastro);

// Função responsável por gerar um novo ID para um paciente baseado no maior ID já existente no banco de dados.
int gerarNovoIdPaciente(BDPaciente *bd);

// Função que insere um novo paciente no final da lista (encadeada) do banco de dados.
void inserirPaciente(BDPaciente *bd, Paciente *novoPaciente);

// Função que busca um paciente pelo ID fornecido e retorna um ponteiro para a estrutura correspondente (Retorna NULL se não encontrar).
Paciente* buscarPacientePorId(BDPaciente *bd, int id);

// Função que remove um paciente do banco de dados com base no ID fornecido. Libera a memória associada ao registro removido.
void removerPaciente(BDPaciente *bd, int id);

#endif
