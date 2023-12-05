int main() {
    int opcao;

    do {
        printf("\n===== LocaMais - Sistema de Locadora de Veículos =====\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Veículo\n");
        printf("3. Cadastrar Locação\n");
        printf("4. Baixar Locação\n");
        printf("5. Pesquisar Cliente\n");
        printf("6. Pesquisar Veículo\n");
        printf("7. Exibir Locações de um Cliente\n");
        printf("8. Calcular Pontos de Fidelidade\n");
        printf("9. [Funcionalidade Extra]\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                // cadastrarCliente();
                break;
            case 2:
                // cadastrarVeiculo();
                break;
            case 3:
                // cadastrarLocacao();
                break;
            case 4:
                // baixarLocacao();
                break;
            case 5:
                // pesquisarCliente();
                break;
            case 6:
                // pesquisarVeiculo();
                break;
            case 7:
                // exibirLocacoesCliente();
                break;
            case 8:
                // calcularFidelidade();
                break;
            case 9:
                // funcionalidadeExtra();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}