#include <stdio.h>
#include "bd_paciente.h"
#include "arquivo.h"
#include "interface_usuario.h"  

int main(void) {
    BDPaciente bd;
    char opcao;

    // Prepara o banco de dados
    iniciarBancoDadosPacientes(&bd);
    carregarDadosPacientes(&bd, "bd_paciente.csv");

    while (1) {
        mostrarMenuPrincipal();
        scanf(" %c", &opcao);
        getchar();
        printf("\n");

        // Caso o usuário opte por sair, realiza o salvamento e encerra o programa
        if (opcao == 'Q' || opcao == 'q') {
            printf("Saindo do sistema...\n");
            salvarDadosPacientes(&bd, "bd_paciente.csv");
            break;
        }

        switch (opcao) {
            case '1':
                processarInsercaoPaciente(&bd);
                break;
            case '2':
                processarConsultaPaciente(&bd);
                break;
            case '3':
                processarAtualizacaoPaciente(&bd);
                break;
            case '4':
                processarRemocaoPaciente(&bd);
                break;
            case '5':
                exibirListaPacientes(&bd);
                break;
            default:
                printf("Opção inválida.\n");
        }

        // Salva os dados se a operação alterar o banco de dados
        if(opcao == '1' || opcao == '3' || opcao == '4')
            salvarDadosPacientes(&bd, "bd_paciente.csv");
    }

    return 0;
}
