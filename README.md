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
2. Considerando a presença do Makefile na pasta, digite no terminal a palavra “make” e execute o projeto teclando enter.
3. A partir do comando dito anteriormente, o programa será executado. Deve-se seguir as instruções na tela de Menu para inserir as informações de um paciente, bem como consultar, atualizar, remover ou imprimir a lista completa dos pacientes presentes no banco de dados.
4. Caso queira sair do programa, deve-se escolher a opção 'Q' OU 'q' (como está presente no Menu), o que acionará o salvamento dos dados, encerrando o programa logo em seguida."

# 4 Estrutura do Projeto 

O projeto está organizado de forma modular, com cada módulo responsável por uma parte específica da funcionalidade: 

- **main.c:** Função principal que inicializa o sistema, carrega o banco de dados e gerencia o fluxo interativo do menu. 
- **arquivo.c / arquivo.h:** Módulo responsável pela leitura e escrita dos registros em um arquivo CSV. 
- **bd_pacient.c / bd_pacient.h:** Implementa os TADs relacionados aos pacientes, com funções para criação, inserção, busca e remoção em uma lista encadeada. 
- **interface_usuario.c / interface_usuario.h:** Gerencia a interface com o usuário, apresentando o menu e tratando as entradas (incluindo validações de CPF, data e idade). 
- **Makefile**: utilizado principalmente para a criação de um executável através do comando make 

# 5 Principais TADs 

O sistema utiliza dois tipos principais para a gestão dos dados: 

- **Paciente:**   
  Representa o registro individual do paciente e contém os seguintes campos:   
  - `id`: Identificador único (gerado dinamicamente a partir do maior ID existente)   
  - `cpf`: CPF do paciente (formatado e validado)   
  - `nome`: Nome do paciente   
  - `idade`: Idade do paciente (com validação para valores negativos)   
  - `dataCadastro`: Data de cadastro no formato AAAA-MM-DD   
  - `proximo`: Ponteiro para o próximo paciente na lista (para implementação da lista encadeada) 

- **BDPaciente:**   
  Estrutura que armazena a lista encadeada de pacientes. Contém apenas o ponteiro para o início da lista, permitindo fácil manipulação dos registros com operações de inserção, remoção e busca.

# 6 Principais Decisões de Implementação 

- **Modularização do Código:**   
  A separação do código em módulos (arquivo, bd, interface) promove a organização, facilita a manutenção e possibilita a reutilização ou expansão do sistema. 

- **Validações de Dados:**   
  Foram implementadas funções para validar entradas críticas, como o CPF (garantindo que contenha 11 dígitos numéricos), a idade (não pode ser negativa) e o formato da data (AAAA-MM-DD). Isso assegura a integridade dos dados inseridos pelo usuário. 
