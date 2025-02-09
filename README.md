# Sistema de Gerenciamento de Dados

O presente projeto implementa um sistema de gerenciamento de registros de pacientes de uma clínica fictícia. O programa foi desenvolvido em linguagem C e utiliza um arquivo CSV para a persistência das informações, armazenando os dados em uma lista encadeada.

# 1. Descrição

Através do menu do sistema, é possível realizar as seguintes operações:
- Inserir um novo paciente (através da solicitação do CPF, nome, idade e data de cadastro)
- Consultar paciente (por nome ou CPF)
- Atualizar registro de um paciente já existente
- Remover paciente do banco de dados
- Imprimir a lista completa de pacientes existentes no banco de dados

Caso alguma operação realizada modifique o banco de dados, todos os dados inseridos/modificados são salvos automaticamente no arquivo CSV, bem como os a lista é atualizada caso haja a exclusão dos dados de algum paciente.

# 2. Requisitos
Deve-se ter um compilador C, além de um ambiente para execução em sistema Linux/Unix ou Windows (terminal).

# 3. Como Executar o Programa
1. Todos os arquivos fonte devem estar na mesma pasta: main.c, arquivo.c, interface_usuario.c, bd_paciente.c, arquivo.h, interface_usuario.h, bd_paciente.h.
2. Considerando a presença do Makefile na pasta, digite no terminal a palavra “make” e execute o projeto.
