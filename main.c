#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
  int codigo;
  char nome[100];
  char endereco[150];
} Cliente;

typedef struct
{
  int codigo;
  char marca[50];
  char modelo[50];
  char placa[20];
} Veiculo;

typedef struct
{
  int codigoLocacao;
  int codigoCliente;
  int codigoVeiculo;
  char dataInicio[11]; // Formato DD/MM/AAAA
  char dataFim[11];    // Formato DD/MM/AAAA
} Locacao;

void cadastrarCliente()
{
  Cliente novoCliente;
  FILE *arquivo;

  printf("\nCadastro de Cliente\n");

  printf("Digite o código do cliente: ");
  scanf("%d", &novoCliente.codigo);
  getchar();

  printf("Digite o nome do cliente: ");
  fgets(novoCliente.nome, 100, stdin);
  novoCliente.nome[strcspn(novoCliente.nome, "\n")] = 0;

  printf("Digite o endereço do cliente: ");
  fgets(novoCliente.endereco, 150, stdin);
  novoCliente.endereco[strcspn(novoCliente.endereco, "\n")] = 0;

  arquivo = fopen("clientes.dat", "ab");
  if (arquivo == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo!\n");
    return;
  }

  fwrite(&novoCliente, sizeof(Cliente), 1, arquivo);

  fclose(arquivo);
  printf("Cliente cadastrado com sucesso!\n");
}

void cadastrarVeiculo()
{
  Veiculo novoVeiculo;
  FILE *arquivo;

  printf("\nCadastro de Veículo\n");

  printf("Digite o código do veículo: ");
  scanf("%d", &novoVeiculo.codigo);
  getchar();

  printf("Digite a marca do veículo: ");
  fgets(novoVeiculo.marca, 50, stdin);
  novoVeiculo.marca[strcspn(novoVeiculo.marca, "\n")] = 0;

  printf("Digite o modelo do veículo: ");
  fgets(novoVeiculo.modelo, 50, stdin);
  novoVeiculo.modelo[strcspn(novoVeiculo.modelo, "\n")] = 0;

  printf("Digite a placa do veículo: ");
  fgets(novoVeiculo.placa, 20, stdin);
  novoVeiculo.placa[strcspn(novoVeiculo.placa, "\n")] = 0;

  arquivo = fopen("veiculos.dat", "ab");
  if (arquivo == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo!\n");
    return;
  }

  fwrite(&novoVeiculo, sizeof(Veiculo), 1, arquivo);

  fclose(arquivo);
  printf("Veículo cadastrado com sucesso!\n");
}

int main()
{
  int opcao;

  do
  {
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

    switch (opcao)
    {
    case 1:
      cadastrarCliente();
      break;
    case 2:
      cadastrarVeiculo();
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
  } while (opcao != 0);

  return 0;
}